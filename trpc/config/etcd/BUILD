licenses(["notice"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "etcd_provider",
    hdrs = ["etcd_provider.h"],
    deps = [
        "//trpc/config/etcd/config:etcd_provider_conf",
        "@trpc_cpp//trpc/config:provider",
    ],
)

cc_library(
    name = "etcd_provider_api",
    srcs = ["etcd_provider_api.cc"],
    hdrs = ["etcd_provider_api.h"],
    deps = [
        ":etcd_provider",
        "@com_google_protobuf//:protobuf",
        "@com_github_etcd_cpp_apiv3_etcd_cpp_apiv3//:etcd_cpp_apiv3",
        "@trpc_cpp//trpc/common:trpc_plugin",
    ],
)

cc_test(
    name = "etcd_provider_test",
    srcs = ["etcd_provider_test.cc"],
    data = ["//trpc/config/etcd/testing:etcd_provider_test.yaml"],
    deps = [
        ":etcd_provider",
        ":etcd_provider_api",
        "//trpc/config/etcd/testing:mock_etcd_provider",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
        "@trpc_cpp//trpc/common/config:config_helper",
        "@trpc_cpp//trpc/config:provider_factory",
    ],
)
