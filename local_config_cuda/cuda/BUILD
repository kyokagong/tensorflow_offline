licenses(["restricted"])  # MPL2, portions GPL v3, LGPL v3, BSD-like

package(default_visibility = ["//visibility:public"])

config_setting(
    name = "using_nvcc",
    values = {
        "define": "using_cuda_nvcc=true",
    },
)

config_setting(
    name = "using_clang",
    values = {
        "define": "using_cuda_clang=true",
    },
)

# Equivalent to using_clang && -c opt.
config_setting(
    name = "using_clang_opt",
    values = {
        "define": "using_cuda_clang=true",
        "compilation_mode": "opt",
    },
)

config_setting(
    name = "darwin",
    values = {"cpu": "darwin"},
    visibility = ["//visibility:public"],
)

config_setting(
    name = "freebsd",
    values = {"cpu": "freebsd"},
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cuda_headers",
    hdrs = [
        "cuda/cuda_config.h",
        
    ],
    includes = [
        ".",
        "cuda/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cudart_static",
    srcs = ["cuda/lib/libcudart_static.a"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkopts = select({
        ":freebsd": [],
        "//conditions:default": ["-ldl"],
    }) + [
        "-lpthread",
        "-lrt",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cuda_driver",
    srcs = ["cuda/lib/libcuda.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cudart",
    srcs = ["cuda/lib/libcudart.so"],
    data = ["cuda/lib/libcudart.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cublas",
    srcs = ["cuda/lib/libcublas.so"],
    data = ["cuda/lib/libcublas.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cusolver",
    srcs = ["cuda/lib/libcusolver.so"],
    data = ["cuda/lib/libcusolver.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkopts = ["-lgomp"],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cudnn",
    srcs = ["cuda/lib/libcudnn.so"],
    data = ["cuda/lib/libcudnn.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cufft",
    srcs = ["cuda/lib/libcufft.so"],
    data = ["cuda/lib/libcufft.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "curand",
    srcs = ["cuda/lib/libcurand.so"],
    data = ["cuda/lib/libcurand.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cuda",
    visibility = ["//visibility:public"],
    deps = [
        ":cublas",
        ":cuda_headers",
        ":cudart",
        ":cudnn",
        ":cufft",
        ":curand",
    ],
)

cc_library(
    name = "cupti_headers",
    hdrs = [
        "cuda/cuda_config.h",
        ":cuda-extras",
    ],
    includes = [
        ".",
        "cuda/extras/CUPTI/include/",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cupti_dsos",
    data = ["cuda/lib/libcupti.so"],
    includes = [
        ".",
        "cuda/include",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libdevice_root",
    data = [":cuda-nvvm"],
    visibility = ["//visibility:public"],
)


