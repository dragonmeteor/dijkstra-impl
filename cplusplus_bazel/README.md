# ``cplusplus_bazel``: C++ Built with Bazel

This is an implemention that I went out of my way to imitate Google way of writing C++.

* Using [Bazel](http://bazel.build) as the build tool.
* Following the conventions in the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html): naming things according to the Google's convention and not using exceptions.
* Using other Google libraries such as [Abseil](http://abseil.io), [GoogleTest](https://github.com/google/googletest), [Google Logging Library](https://github.com/google/glog), and [gflags](https://gflags.github.io/gflags/).

## Setting up a development environment

First, we need to install [Bazel](http://bazel.build). On Windows, run the following commands:

```
choco install bazelisk
choco install buildifier
choco install buildozer
```

Next, in VS Code, install the [Bazel plugin](https://marketplace.visualstudio.com/items?itemName=BazelBuild.vscode-bazel) and the [clangd plugin](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd). Then, set up the [Bazel compile commands extractor](https://github.com/hedronvision/bazel-compile-commands-extractor).

## Using the Rakefile

The rake file has the following commands.

```
rake build
rake run
rake test
rake refresh
```

Run the last command to so that the clangd plugin can do its job providing autocomplete.