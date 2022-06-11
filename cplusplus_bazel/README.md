# ``cplusplus_bazel``: C++ Built with Bazel

First, install [Baselisk](https://github.com/bazelbuild/bazelisk) into your system. In my case, I use [Chocolatey](http://chocolatey.org), so I open the admin terminal and ran the following command.

```
> choco install bazelisk
```

Then, build the main executable by running the following command.

```
> bazel build //:main
```

After the above command finishes, you can run the executable by invoking.

```
> bazel run //:main -- <input-file-name> <output-file-name>
```

Or, you can do this as well.

```
> bazel-build/main <input-file-name> <output-file-name>
```