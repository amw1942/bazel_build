# bazel_build
This project is an example for demonstrating bazel build rules.

1. include path rule.
In bazel, we can control the visibility of header files. In cc_library rule,
there is 'visibility'. Here is an example. We have a git repo with the following
structure.

  +- lib
     +- frontend
     +- ir
  +- src
     +- compiler_drv

Inside lib/ir we have the following BUILD for bazel.

  cc_library(
      name = "ir",
      srcs = ["ir.cpp"],
      hdrs = ["ir.h"],
      visibility = ["//src/compiler_drv:__pkg__"],
  )

As ir.h is inside hdrs, it is an exposed header file.
Once you declare the visibility to the package in //src/compiler_drv, the
file in //src/compiler_drv:main.cpp can include ir.h like this:

  #include "lib/ir/ir.h"
  #include "lib/frontend/frontend.h"

  int main(int argc, char* argv[]) {
    ...
  }

It means that main.cpp looks at header files from the project top. BUILD is:

  cc_binary(
      name = "compiler",
      srcs = ["main.cpp"],
      deps = ["//lib/ir", "//lib/frontend"],
  )

If copts is included, we can abbreiviate the header file reference in main.cpp.

  cc_binary(
      name = "compiler",
      srcs = ["main.cpp"],
      copts = ["-Ilib"],
      deps = ["//lib/ir", "//lib/frontend"],
  )

Then, here is main.cpp:

  #include "ir/ir.h"

  int main(int argc, char* argv[]) {
    ...
  }

2. comment
'#' is used as comment header.

3. git_repository vs new_git_repository
git_repository is used when the underlying repository is already bazelized.
new_git_repository is used when the underlying repository is not bazelized.
For example, google test is already using Bazel as a build system. To fetch
it you can simply do:

  git_repository(
      name = "googletest",
      commit = "703bd9caab50b139428cea1aaff9974ebee5742e", # google test v1.10.0
      remote = "https://github.com/google/googletest",
      shallow_since = "1570114335 -0400",
  )

  cc_test(
      name = "tests",
      timeout = "short",
      srcs = ["test.cpp"],
      deps = [
        "@googletest//:gtest_main", # use googletest as a dependency
      ],
  )

https://stackoverflow.com/questions/69182889/bazel-function-git-repository-vs-new-git-repository

4. googletest
In order to use googletest, put the following in WORKSPACE.

  load(""@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

  http_archive(
      name = "com_google_googletest",
      urls = "https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"
      strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5"
  )

For each test case

  cc_test(
    name = "compiler_drv_test",
    size = "small",
    srcs = ["compiler_drv_test.cpp"],
    copts = ["-Ilib"]
    deps = ["@com_google_googletest//:gtest_main", "//lib/ir", "//lib/frontend"],
  )

visibilty applied to cc_test is the same as cc_binary.
