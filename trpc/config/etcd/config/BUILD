licenses(["notice"])

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "etcd_provider_conf",
    srcs = ["etcd_provider_conf.cc"],
    hdrs = [
        "etcd_file_provider_conf_parser.h",
        "etcd_provider_conf.h",
    ],
    deps = [
        "@com_github_jbeder_yaml_cpp//:yaml-cpp",
        "@trpc_cpp//trpc/common/config:config_helper",
        "@trpc_cpp//trpc/util/log:logging",
    ],
)
