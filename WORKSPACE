load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

new_git_repository(
    name = "ort",
    remote = "https://github.com/amw1942/onnxruntime.git",
    build_file = "//trd:ort.BUILD",
    recursive_init_submodules = True,
)

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# download googletest
http_archive(
    name = "com_google_googletest",
    urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
    strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
)

