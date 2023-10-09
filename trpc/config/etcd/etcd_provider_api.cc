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

#include "trpc/config/etcd/etcd_provider_api.h"

#include <iostream>

#include "trpc/common/trpc_plugin.h"

#include "trpc/config/etcd/config/etcd_provider_conf.h"
#include "trpc/config/etcd/etcd_provider.h"

namespace trpc::config::etcd {

bool Init() {
  std::vector<EtcdProviderConfig> config_list;
  if (!GetAllEtcdProviderConfig(config_list)) {
    return false;
  }
  for (const auto& config : config_list) {
    TrpcPlugin::GetInstance()->RegisterConfigProvider(
        MakeRefCounted<EtcdProvider>(std::move(config)));
  }
  return true;
}

}  // namespace trpc::config::etcd
