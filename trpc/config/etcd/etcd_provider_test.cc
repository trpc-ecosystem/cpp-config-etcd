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

#include "trpc/config/etcd/etcd_provider.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "trpc/common/config/config_helper.h"

#include "trpc/config/etcd/etcd_provider_api.h"
#include "trpc/config/etcd/testing/mock_etcd_provider.h"

namespace trpc::config::etcd {

class EtcdProviderTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ASSERT_TRUE(ConfigHelper::GetInstance()->Init(
        "trpc/config/etcd/testing/etcd_provider_test.yaml"));

    std::vector<EtcdProviderConfig> config_list;
    if (!GetAllEtcdProviderConfig(config_list)) {
      return;
    }
    mock_etcd_provider_ = MakeRefCounted<MockEtcdProvider>(config_list[0]);
    ASSERT_NE(mock_etcd_provider_, nullptr);
  }

  void TearDown() override { trpc::log::Destroy(); }

  MockEtcdProviderPtr mock_etcd_provider_;
};

TEST_F(EtcdProviderTest, ReadTest) {
  std::string key = "test_key";
  std::string expected_value = "test_value";
  EXPECT_CALL(*mock_etcd_provider_, Read(key))
      .WillOnce(::testing::Return(expected_value));

  std::string actual_value = mock_etcd_provider_->Read(key);

  EXPECT_EQ(actual_value, expected_value);
}

TEST_F(EtcdProviderTest, WatchTest) {
  EXPECT_CALL(*mock_etcd_provider_, Watch(::testing::_)).Times(1);

  mock_etcd_provider_->Watch(
      [](const std::string& key, const std::string& value) {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
      });
}

}  // namespace trpc::config::etcd
