package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "etcd_cpp_apiv3",
    hdrs = glob(["include/etcd/**/*.hpp"]),
    srcs = glob(["lib64/libetcd-cpp-api.*"]),
    deps = [
        "@com_github_microsoft_cpprestsdk//:cpprestsdk",
    ],
)
