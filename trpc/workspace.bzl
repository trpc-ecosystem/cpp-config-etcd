"""This module contains some dependency"""

# buildifier: disable=load
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def clean_dep(dep):
    return str(Label(dep))

# buildifier: disable=function-docstring-args
def config_etcd_workspace(path_prefix = "", repo_name = "", **kwargs):
    """Build rules for the trpc project

    Note: The main idea is to determine the required version of dependent software during the build process
          by passing in parameters.
    Args:
        path_prefix: Path prefix.
        repo_name: Repository name of the dependency.
        kwargs: Keyword arguments, dictionary type, mainly used to specify the version and sha256 value of
                dependent software, where the key of the keyword is constructed by the `name + version`.
                eg: protobuf_ver,zlib_ver...
    Example:
        trpc_workspace(path_prefix="", repo_name="", protobuf_ver="xxx", protobuf_sha256="xxx", ...)
        Here, `xxx` is the specific specified version. If the version is not specified through the key,
        the default value will be used. eg: protobuf_ver = kwargs.get("protobuf_ver", "3.8.0")
    """

    native.new_local_repository(
        name = "com_github_etcd_cpp_apiv3_etcd_cpp_apiv3",
        path = "/usr/local",
        build_file = "//third_party/com_github_etcd_cpp_apiv3_etcd_cpp_apiv3:etcd_cpp_apiv3.BUILD",
    )

    native.new_local_repository(
        name = "com_github_microsoft_cpprestsdk",
        path = "/usr/local",
        build_file = "//third_party/com_github_microsoft_cpprestsdk:cpprestsdk.BUILD",
    )

