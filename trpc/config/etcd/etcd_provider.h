//
//
// Tencent is pleased to support the open source community by making tRPC available.
//
// Copyright (C) 2023 THL A29 Limited, a Tencent company.
// All rights reserved.
//
// If you have downloaded a copy of the tRPC source code from Tencent,
// please note that tRPC source code is licensed under the  Apache 2.0 License,
// A copy of the Apache 2.0 License is included in this file.
//
//

#pragma once

#include <mutex>

#include "etcd/Client.hpp"
#include "etcd/Watcher.hpp"
#include "trpc/config/default/loader.h"
#include "trpc/config/provider.h"

#include "trpc/config/etcd/config/etcd_provider_conf.h"

namespace trpc::config::etcd {

class EtcdProvider : public Provider {
 public:
  explicit EtcdProvider(EtcdProviderConfig config)
      : name_(std::move(config.name)),
        prefix_(std::move(config.prefix)),
        client_(std::move(config.endpoint)),
        callback_enabled_(true) {
    // Get the current modification index for the etcd cluster
    watch_index_ = GetCurrentModificationIndex();
  }

  std::string Name() const override { return name_; }

  std::string Read(const std::string& name) override {
    return client_.get(prefix_ + name).get().value().as_string();
  }

  void Watch(trpc::config::ProviderCallback callback) override {
    std::unique_lock callback_lock(callback_mutex_);
    callbacks_.emplace_back(std::move(callback));
    if (!watcher_) {
      // Temporarily disable callback during initialization.
      callback_enabled_ = false;
      WatchInternal();
      // Enable callback after initialization.
      callback_enabled_ = true;
    }
  }

 private:
  uint64_t GetCurrentModificationIndex() {
    auto response = client_.get(prefix_ + name_).get();
    if (response.is_ok()) {
      auto kvs = response.keys();
      if (!kvs.empty()) {
        return client_.get(kvs.front()).get().value().created_index();
      }
    }
    return 0;
  }

  void WatchCallback(::etcd::Response response) {
    std::unique_lock callback_lock(callback_mutex_);
    if (callback_enabled_) {
      for (const auto& event : response.events()) {
        for (const auto& callback : callbacks_) {
          callback(event.kv().key(), event.kv().as_string());
        }
        watch_index_ = event.kv().created_index();
      }
    }
  }

  void WatchInternal() {
    if (watcher_ && watcher_->Cancel()) {
      return;
    }
    bool skip_first = (watcher_ == nullptr);
    watcher_.reset(new ::etcd::Watcher(
        client_, prefix_, watch_index_ + 1,
        [this, skip_first](::etcd::Response response) mutable {
          if (skip_first) {
            skip_first = false;
          } else {
            WatchCallback(std::move(response));
          }
        },
        true));
    watcher_->Wait([this](bool cancelled) {
      if (!cancelled) {
        WatchInternal();
      }
    });
  }

  std::string name_;
  std::string prefix_;
  ::etcd::Client client_;
  std::unique_ptr<::etcd::Watcher> watcher_;
  std::int64_t watch_index_;

  std::mutex callback_mutex_;
  std::vector<trpc::config::ProviderCallback> callbacks_;
  bool callback_enabled_;
};

using EtcdProviderPtr = RefPtr<EtcdProvider>;

}  // namespace trpc::config::etcd
