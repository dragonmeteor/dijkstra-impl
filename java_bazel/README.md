``java_bazel``: Java Built with Bazel

This implementation imitates the way Java software is developed at Google.

## Setting up a development environment

First, we need to install [Bazel](http://bazel.build). On Windows, run the following commands:

```
choco install bazelisk
choco install buildifier
choco install buildozer
```

Install the [Bazel plugin](https://ij.bazel.build/) in Intellij IDEA. Then, do "File > Import Bazel Project..." and
import the ``java_bazel`` directory.