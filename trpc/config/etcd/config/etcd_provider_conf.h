//
//
// Tencent is pleased to support the open source community by making tRPC available.
//
// Copyright (C) 2023 Tencent.
// All rights reserved.
//
// If you have downloaded a copy of the tRPC source code from Tencent,
// please note that tRPC source code is licensed under the  Apache 2.0 License,
// A copy of the Apache 2.0 License is included in this file.
//
//

#pragma once

#include <string>

#include "trpc/util/log/logging.h"

namespace trpc {

/// @brief The config for etcd config provider
struct EtcdProviderConfig {
  /// @brief Provider name
  std::string name = "etcd";
  /// @brief Connect endpoint
  std::string endpoint = "http://127.0.0.1:2379";
  /// @brief Node prefix
  std::string prefix = "";

  /// @brief Print the configuration
  void Display() const;
};

///@brief Parses the EtcdProviderConfig from a YAML::Node.
///@param provider The YAML::Node containing the provider configuration.
///@param config The EtcdProviderConfig object to be filled with the parsed data.
///@return true if the parsing is successful, false otherwise.
bool GetAllEtcdProviderConfig(std::vector<EtcdProviderConfig>& config);

}  // namespace trpc
