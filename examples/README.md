# etcd provider demo

This example demonstrates how to use etcd to store and retrieve key-value pairs in a client and server program. The example includes a simple client and server program.

## File Structure

```shell
$ tree examples/config/etcd/
examples/config/etcd/
├── client
│   ├── BUILD
│   ├── client.cc
│   └── trpc_cpp_fiber.yaml
└── server
    ├── BUILD
    ├── greeter_service.cc
    ├── greeter_service.h
    ├── helloworld.proto
    ├── helloworld_server.cc
    └── trpc_cpp_fiber.yaml
└── run.sh
```
## Running the Example

* Prerequisites
  This example assumes that you have an etcd cluster running at IP 127.0.0.1 and port 2379. If you haven't set up an etcd cluster yet, please follow the etcd official documentation to install and start an etcd cluster.

* Set key-value pairs
  Use the etcdctl command-line tool to set key-value pairs. Here are some examples of setting different key-value pairs:

Set the server_config.yaml key value in YAML format:
```shell
etcdctl --endpoints http://127.0.0.1:2379 put server_config.yaml "ip: 127.0.0.1\nport: 10001"
```
Set the salutation_config.json key value in JSON format with multiple fields:
```shell
etcdctl --endpoints http://127.0.0.1:2379 put salutation_config.json '{"hello": "nice to meet you!", "goodbye": "see you later!", "thanks": "thank you!", "congratulations": "congrats!"}'
```

* Compilation

We can run the following command to start the server and proxy program.

```shell
./bazel-bin/examples/etcd/server/helloworld_server --config=examples/etcd/server/trpc_cpp_fiber.yaml
```

* Run the client program

We can run the following command to start the client program.

```shell
./bazel-bin/examples/etcd/client/client --config=examples/etcd/server/trpc_cpp_fiber.yaml
```
