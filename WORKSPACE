workspace(
    name = "com_github_trpc_ecosystem_cpp_config_etcd",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "trpc_cpp",
    branch = "main",
    remote = "https://github.com/trpc-group/trpc-cpp.git",
)

load("@trpc_cpp//trpc:workspace.bzl", "trpc_workspace")

trpc_workspace()

load("//trpc:workspace.bzl", "config_etcd_workspace")

config_etcd_workspace()
