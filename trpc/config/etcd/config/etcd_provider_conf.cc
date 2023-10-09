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

#include "trpc/config/etcd/config/etcd_provider_conf.h"

#include <iostream>

#include "trpc/config/etcd/config/etcd_file_provider_conf_parser.h"

namespace trpc {

bool GetAllEtcdProviderConfig(std::vector<EtcdProviderConfig>& config_list) {
  YAML::Node provider_list;
  if (!GetEtcdProvidersNode(provider_list)) {
    TRPC_FMT_ERROR("Get etcd providers node error!");
  }
  for (const auto& provider : provider_list) {
    EtcdProviderConfig config;
    // Convert node to EtcdProviderConfig
    if (!YAML::convert<EtcdProviderConfig>::decode(provider, config)) {
      TRPC_FMT_ERROR("Convert etcd config error!");
      return false;
    }
    config_list.push_back(std::move(config));
  }
  return true;
}

/// @brief Print the configuration
void EtcdProviderConfig::Display() const {
  std::cout << "endpoint:" << endpoint << std::endl;
  std::cout << "prefix:" << prefix << std::endl;
}

}  // namespace trpc
