# mloader

Created by Ryan

## About

generating load

## Run the thing

Generated scaffolding using this:
<https://github.com/nganhkhoa/generator-cpp-prebuild#readme>

```bash
cmake -H./ -B./build
make -C ./build mloader
./bin/mloader

# tests
cmake -H./ -B./build -DUNIT_TEST=ON
make -C ./build mloader-test
./bin/mloader-test
```
