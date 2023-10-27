[English](./README.md)

# 前言

[Etcd](https://etcd.io/) 是一个高可用的键值存储系统，用于共享配置和服务发现。它是由 CoreOS 开发的，用于分布式系统的配置管理和服务发现。为了方便用户对接Etcd系统，我们提供了Etcd数据源插件，用户可以轻松地从 etcd 集群中加载配置数据，并在程序中使用这些数据。

# 使用说明

详细的使用例子可以参考：[Etcd examples](./examples/)。

## 引入依赖

### Bazel

1. 引入仓库

   在项目的`WORKSPACE`文件中，引入`cpp-config-etcd`仓库及其依赖：
    ```
    load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

    git_repository(
        name = "trpc_cpp",
        remote = "https://github.com/trpc-group/trpc-cpp.git",
        branch = "main",
    )
   
    load("@trpc_cpp//trpc:workspace.bzl", "trpc_workspace")
    trpc_workspace()
    
    git_repository(
        name = "cpp-config-etcd",
        remote = "https://github.com/trpc-ecosystem/cpp-config-etcd.git",
        branch = "main",
    )
   
   load("@etcd-provider//trpc:workspace.bzl", "config_etcd_workspace")
   config_etcd_workspace()
    ```

   [etcd-client-cpp](https://github.com/etcd-cpp-apiv3/etcd-cpp-apiv3)依赖的第三方库很多，完全基于源码进行bazel编译很麻烦。为了简化编译流程，我们通过本地库的方式来引入etcd-client-cpp和其必须的依赖库grpc、rest等。编译之前用户需要先将etcd-client-cpp和相关依赖安装到/usr/local目录下。

2. 引入插件

   在需要用到Etcd的目标中引入“`trpc/config/etcd:etcd_provider_api`”依赖。例如：
    ```
   cc_binary(
       name = "helloworld_server",
       srcs = ["helloworld_server.cc"],
       deps = [
           "@cpp-config-etcd//trpc/config/etcd:etcd_provider",
           ...
       ],
   )
    ```

### Cmake

暂不支持。

## 插件配置

要使用Etcd插件，必须在框架配置文件中加上插件配置：
```yaml
plugins:
   config:
      etcd:
         providers:
            - name: etcd1
              endpoint: "http://127.0.0.1:2379"
              prefix: ""
```

以下是这些配置项的详细说明：

| 配置项   | 类型   | 默认值               | 说明                                                         |
| -------- | ------ | -------------------- | ------------------------------------------------------------ |
| name     | string | 无默认值，必须设置   | etcd 提供者的名称，用于在代码中通过 `::trpc::config::WithProvider` 函数指定使用哪个 etcd 提供者 |
| endpoint | string | 无默认值，必须设置   | etcd 集群的访问地址，格式为 "http://ip:port"                |
| prefix   | string | 空字符串（可选配置） | etcd 中存储配置数据的键的前缀，用于区分不同的配置数据       |

## 初始化

etcd-provider 插件提供了插件注册的接口 `::trpc::config::etcd::Init()`，用户需要在框架启动前调用该接口进行初始化。

对于服务端场景，用户需要在服务启动的 `TrpcApp::RegisterPlugins` 函数中调用：

    ```cpp
    #include "trpc/config/etcd/etcd_provider_api.h"
    
    class HelloworldServer : public ::trpc::TrpcApp {
     public:
      ...
      int RegisterPlugins() override {
        ::trpc::config::etcd::Init();
        return 0;
      }
    };
    ```

2. 对于纯客户端场景，需要在启动框架配置初始化后，框架其他模块启动前调用：

    ```cpp
    #include "trpc/config/etcd/etcd_provider_api.h"

    int main(int argc, char* argv[]) {
      ParseClientConfig(argc, argv);

      ::trpc::config::etcd::Init();

      return ::trpc::RunInTrpcRuntime([]() { return Run(); });
    }
    ```

## 注意事项

* 在使用 etcd-provider 插件之前，您需要确保已正确安装并配置了 etcd 集群。此外，您还需要了解如何使用 etcdctl 工具来设置键值对。以下是有关这两个方面的简要说明：

# 安装 etcd 集群
1. 访问 etcd 的官方 [GitHub](https://github.com/etcd-io/etcd) 仓库：etcd GitHub。在页面上，您可以找到有关安装和部署 etcd 集群的详细指南。您可以根据您的操作系统和环境选择相应的安装方法。

2. 对于简单的测试和开发用途，您可以在本地运行一个单节点的 etcd 集群。请参阅 etcd 官方文档 中的 "Getting Started" 部分以了解如何在本地启动一个 etcd 实例。

3. 对于生产环境，建议您部署一个多节点的 etcd 集群，以确保高可用性和数据一致性。请参阅 etcd 官方文档 中的 "Runtime Configuration" 部分以了解如何配置和部署一个多节点 etcd 集群。

# 使用 etcdctl 工具设置键值对

* etcdctl 是 etcd 的命令行客户端工具，用于与 etcd 集群进行交互。您可以使用 etcdctl 工具来设置、获取、删除和监视键值对。请确保您已正确安装了 etcdctl，具体安装方法请参考 etcd 官方文档。
* 使用 etcdctl 设置键值对的基本语法如下：
    ```shell
    etcdctl put <key> <value>
    ```
  例如，要设置一个名为 "salutation_config.json" 的键，其值为配置数据，您可以执行以下命令：
    ```shell
    etcdctl put salutation_config.json '{"hello": "world"}'
    ```
* 使用 etcdctl 获取键值对的基本语法如下：
    ```shell
    etcdctl get <key>
    ```
  例如，要获取名为 "salutation_config.json" 的键的值，您可以执行以下命令：
    ```shell
    etcdctl get salutation_config.json
    ```
* 更多关于 etcdctl 工具的使用方法，请参考 [Etcd](https://etcd.io/docs/) 官方文档 中的 [Interacting with etcd](https://etcd.io/docs/v3.5/dev-guide/interacting_v3/) 部分。
