bazel build ... --copt="-DDEBUG=1"

echo "begin"
./bazel-bin/examples/server/helloworld_server --config=examples/server/trpc_cpp_fiber.yaml &
sleep 3
./bazel-bin/examples/client/client --config=examples/client/trpc_cpp_fiber.yaml

sleep 3
etcdctl put test_callbake_key hello > /dev/null

sleep 5
killall helloworld_server
if [ $? -ne 0 ]; then
  echo "helloworld_server exit error"
  exit -1
fi
