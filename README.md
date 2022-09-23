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
