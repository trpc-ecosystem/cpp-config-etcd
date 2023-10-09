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

#include "trpc/config/etcd/etcd_provider.h"

namespace trpc::config::etcd {

class MockEtcdProvider : public EtcdProvider {
 public:
  explicit MockEtcdProvider(EtcdProviderConfig config)
      : EtcdProvider(std::move(config)) {}

  MOCK_METHOD(std::string, Read, (const std::string&), (override));
  MOCK_METHOD(void, Watch, (trpc::config::ProviderCallback), (override));
};

using MockEtcdProviderPtr = RefPtr<MockEtcdProvider>;

}  // namespace trpc::config::etcd