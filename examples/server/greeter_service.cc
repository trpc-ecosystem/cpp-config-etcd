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

#include "examples/server/greeter_service.h"

#include <string>

#include "trpc/config/trpc_conf.h"
#include "trpc/log/logging.h"

namespace test::helloworld {

::trpc::Status GreeterServiceImpl::SayHello(
    ::trpc::ServerContextPtr context,
    const ::trpc::test::helloworld::HelloRequest* request,
    ::trpc::test::helloworld::HelloReply* reply) {
  // Pull data to the etcd cluster
  auto salutation_config = ::trpc::config::Load(
      "salutation_config.json", ::trpc::config::WithCodec("json"),
      ::trpc::config::WithProvider("etcd1"));
  std::string reply_msg = request->msg();

  // Look for the reply statement from etcd
  std::string response = salutation_config->GetString(reply_msg, "");
  TRPC_FMT_INFO("reply msg: {}, response:{}", reply_msg, response);

  reply->set_msg(response);

  return ::trpc::kSuccStatus;
}

}  // namespace test::helloworld
