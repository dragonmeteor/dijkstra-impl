cc_library(
    name = "graph",
    srcs = [
        "graph.cc",
    ],
    hdrs = [
        "graph.h",
    ],
    deps = [
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
    ],
)

cc_test(
    name = "graph_test",
    srcs = [
        "graph_test.cc",
    ],
    deps = [
        ":graph",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "load_input",
    srcs = [
        "load_input.cc",
    ],
    hdrs = [
        "load_input.h",
    ],
    deps = [
        ":graph",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
    ],
)

cc_library(
    name = "binary_heap",
    hdrs = [
        "binary_heap.h",
    ],
    deps = [
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
    ],
)

cc_test(
    name = "binary_heap_test",
    srcs = [
        "binary_heap_test.cc",
    ],
    deps = [
        ":binary_heap",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "dijkstra",
    srcs = [
        "dijkstra.cc",
    ],
    hdrs = [
        "dijkstra.h",
    ],
    deps = [
        ":binary_heap",
        ":graph",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/strings",
    ],
)

cc_binary(
    name = "main",
    srcs = [
        "main.cc",
    ],
    deps = [
        ":dijkstra",
        ":graph",
        ":load_input",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
    ],
)
