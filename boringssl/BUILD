# Copyright (c) 2016, Google Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
# OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

licenses(["notice"])

exports_files(["LICENSE"])

load(
    ":BUILD.generated.bzl",
    "crypto_headers",
    "crypto_internal_headers",
    "crypto_sources",
    "crypto_sources_linux_x86_64",
    "crypto_sources_mac_x86_64",
    "fips_fragments",
    "ssl_headers",
    "ssl_internal_headers",
    "ssl_c_sources",
    "ssl_cc_sources",
    "tool_sources",
    "tool_headers",
)

config_setting(
    name = "linux_x86_64",
    values = {"cpu": "k8"},
)

config_setting(
    name = "mac_x86_64",
    values = {"cpu": "darwin"},
)

config_setting(
    name = "windows",
    values = {"cpu": "x64_windows"},
    visibility = ["//visibility:public"],
)

config_setting(
    name = "windows_msvc",
    values = {"cpu": "x64_windows_msvc"},
    visibility = ["//visibility:public"],
)

boringssl_copts = select({
    ":windows": [
        "-DWIN32_LEAN_AND_MEAN",
    ],
    "//conditions:default": [
        # Assembler option --noexecstack adds .note.GNU-stack to each object to
        # ensure that binaries can be built with non-executable stack.
        "-Wa,--noexecstack",

        # This is needed on Linux systems (at least) to get rwlock in pthread.
        "-D_XOPEN_SOURCE=700",

        # This list of warnings should match those in the top-level CMakeLists.txt.
        "-Wall",
        "-Werror",
        "-Wformat=2",
        "-Wsign-compare",
        "-Wmissing-field-initializers",
        "-Wwrite-strings",
        "-Wshadow",
        "-fno-common",

        # Modern build environments should be able to set this to use atomic
        # operations for reference counting rather than locks. However, it's
        # known not to work on some Android builds.
        # "-DOPENSSL_C11_ATOMIC",
    ],
}) + select({
    ":linux_x86_64": [],
    ":mac_x86_64": [],
    "//conditions:default": ["-DOPENSSL_NO_ASM"],
})

crypto_sources_asm = select({
    ":linux_x86_64": crypto_sources_linux_x86_64,
    ":mac_x86_64": crypto_sources_mac_x86_64,
    "//conditions:default": [],
})

# For C targets only (not C++), compile with C11 support.
boringssl_copts_c11 = boringssl_copts + select({
    ":windows": [],
    ":windows_msvc": [],
    "//conditions:default": [
        "-std=c11",
        "-Wmissing-prototypes",
        "-Wold-style-definition",
        "-Wstrict-prototypes",
    ],
})

# For C targets only (not C++), compile with C11 support.
boringssl_copts_cxx = boringssl_copts + select({
    ":windows": [],
    ":windows_msvc": [],
    "//conditions:default": [
        "-std=c++11",
        "-Wmissing-declarations",
    ],
})

cc_library(
    name = "crypto",
    srcs = crypto_sources + crypto_internal_headers + crypto_sources_asm,
    hdrs = crypto_headers + fips_fragments,
    copts = boringssl_copts_c11,
    includes = ["src/include"],
    linkopts = select({
        ":mac_x86_64": [],
        ":windows": [],
        ":windows_msvc": [],
        "//conditions:default": ["-lpthread"],
    }),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "ssl",
    srcs = ssl_c_sources + ssl_internal_headers,
    hdrs = ssl_headers,
    copts = boringssl_copts_c11,
    includes = ["src/include"],
    visibility = ["//visibility:public"],
    deps = [":crypto", ":ssl_cc"],
)

cc_library(
    name = "ssl_cc",
    srcs = ssl_cc_sources + ssl_internal_headers,
    hdrs = ssl_headers,
    copts = boringssl_copts,
    includes = ["src/include"],
    deps = [":crypto"],
)

cc_binary(
    name = "bssl",
    srcs = tool_sources + tool_headers,
    copts = boringssl_copts_cxx,
    visibility = ["//visibility:public"],
    deps = [":ssl"],
)
