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

#include <memory>
#include <string>

#include "examples/server/greeter_service.h"
#include "fmt/format.h"
#include "trpc/common/trpc_app.h"
#include "trpc/config/etcd/etcd_provider_api.h"

namespace test::helloworld {

class HelloWorldServer : public ::trpc::TrpcApp {
 public:
  int Initialize() override {
    const auto& config = ::trpc::TrpcConfig::GetInstance()->GetServerConfig();
    // Set the service name, which must be the same as the value of the
    // `/server/service/name` configuration item in the configuration file,
    // otherwise the framework cannot receive requests normally.
    std::string service_name = fmt::format("{}.{}.{}.{}", "trpc", config.app,
                                           config.server, "Greeter");
    TRPC_FMT_INFO("service name:{}", service_name);

    // Initializes the cls logging plugin and filters after start runtime
    ::trpc::config::etcd::Init();
    auto etcd_provider =
        ::trpc::config::ProviderFactory::GetInstance()->Get("etcd1");
    etcd_provider->Watch([](const std::string& key, const std::string& value) {
      TRPC_FMT_INFO("The key: '{}' has changed and the new value is: '{}'", key,
                    value);
    });

    RegisterService(service_name, std::make_shared<GreeterServiceImpl>());

    return 0;
  }

  void Destroy() override {}
};

}  // namespace test::helloworld

int main(int argc, char** argv) {
  test::helloworld::HelloWorldServer helloworld_server;

  helloworld_server.Main(argc, argv);
  helloworld_server.Wait();

  return 0;
}
