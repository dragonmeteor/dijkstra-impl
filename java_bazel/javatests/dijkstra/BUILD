java_test(
    name = "GraphTest",
    srcs = ["GraphTest.java"],
    deps = [
        "//java/dijkstra:Edge",
        "//java/dijkstra:Graph",
        "@com_google_guava",
        "@com_google_truth",
        "@com_google_truth_java8",
        "@junit",
    ],
)

java_test(
    name = "BinaryHeapTest",
    srcs = ["BinaryHeapTest.java"],
    deps = [
        "//java/dijkstra:BinaryHeap",
        "@com_google_truth",
        "@com_google_truth_java8",
        "@junit",
    ],
)

java_test(
    name = "DijkstraTest",
    srcs = ["DijkstraTest.java"],
    deps = [
        "//java/dijkstra:BinaryHeap",
        "//java/dijkstra:Dijkstra",
        "//java/dijkstra:Edge",
        "//java/dijkstra:Graph",
        "@com_google_auto_value",
        "@com_google_guava",
        "@com_google_truth",
        "@com_google_truth_java8",
        "@junit",
    ],
)
