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

#include "include/yaml-cpp/yaml.h"
#include "trpc/common/config/config_helper.h"

#include "trpc/config/etcd/config/etcd_provider_conf.h"

namespace YAML {

bool GetEtcdProvidersNode(YAML::Node& providers) {
  if (!trpc::ConfigHelper::GetInstance()->GetNode(
          {"plugins", "config", "etcd", "providers"}, providers)) {
    return false;
  }
  return true;
}

template <>
struct convert<trpc::EtcdProviderConfig> {
  static YAML::Node encode(const trpc::EtcdProviderConfig& conf) {
    YAML::Node node;
    node["name"] = conf.name;
    node["endpoint"] = conf.endpoint;
    node["prefix"] = conf.prefix;
    return node;
  }

  static bool decode(const YAML::Node& node,
                     trpc::EtcdProviderConfig& conf) {  // NOLINT
    if (node["name"]) {
      conf.name = node["name"].as<std::string>();
    }
    if (node["endpoint"]) {
      conf.endpoint = node["endpoint"].as<std::string>();
    }
    if (node["prefix"]) {
      conf.prefix = node["prefix"].as<std::string>();
    }
    return true;
  }
};

}  // namespace YAML
