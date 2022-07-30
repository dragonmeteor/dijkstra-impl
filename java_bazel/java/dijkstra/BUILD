package(
    default_visibility = [
        "//javatests/dijkstra:__pkg__",
    ],
)

java_library(
    name = "Edge",
    srcs = ["Edge.java"],
    deps = [
        "@com_google_auto_value",
    ],
)

java_library(
    name = "Graph",
    srcs = ["Graph.java"],
    deps = [
        ":Edge",
        "@com_google_auto_value",
        "@com_google_guava",
    ],
)

java_library(
    name = "BinaryHeap",
    srcs = ["BinaryHeap.java"],
    deps = [
        "@com_google_auto_value",
        "@com_google_guava",
    ],
)

java_library(
    name = "Dijkstra",
    srcs = ["Dijkstra.java"],
    deps = [
        ":BinaryHeap",
        ":Edge",
        ":Graph",
        "@com_google_auto_value",
        "@com_google_guava",
    ],
)

java_binary(
    name = "Main",
    srcs = ["Main.java"],
    deps = [
        ":Dijkstra",
        ":Edge",
        ":Graph",
        "@com_google_guava",
    ],
)
