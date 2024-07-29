load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "OpenMP_Mult",
    srcs = ["OpenMP_Mult.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
    ],
    copts = [
        "-fopenmp",
    ],
    linkopts = [
        "-fopenmp",
    ],
)

cc_binary(
    name = "For_Mult",
    srcs = ["For_Mult.cc"],
    deps = [
        "@com_google_benchmark//:benchmark",
    ],
    copts = [
        "-fopenmp",
    ],
    linkopts = [
        "-fopenmp",
    ],
)
