# Unit Tests

## Guide to Run Unit Tests for scheme
```
TeXmacs -x "(run-all-tests)" -q
```
or launch a Scheme session and then run `(run-all-tests)`.

## Guide to Run Unit Tests for cpp

First, download Google Test from [https://github.com/google/googletest/releases] and copy the subdirectory `google-test` to `tests\gtest`

Then, compile the whole project. If `tests\gtest` is properly installed, CMake will detect it and build all test `cpp` files in the `test` directory.
```
cd texmacs/
mkdir build/ && cd build/
cmake ..
make -j8
```

Then, run your unit tests:
```
ctest // run all
ctest -R analyze // run unit tests with name containing `analyze`
```

### Advanced Topic
You may also run the unit tests via the binaries under `${cmake_build_dir}/tests/`
``` bash
tests/converter_test
```

However, this specify unit test will fail. For `utf8_to_cork`, we need to set
the `TEXMACS_PATH` to find the dictionaries. You may specify it manually:
``` bash
TEXMACS_PATH=/path/to/somewhere tests/converter_test
```

Or just using ctest(we've set the necessary environment variables):
``` bash
ctest -R converter_test
```
