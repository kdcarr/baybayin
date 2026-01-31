# ᜊᜌ᜔ᜊᜌᜒᜈ᜔ (Baybayin-Core)


```shell
conan profile detect --force
edit ~/.conan2/profiles/default, set compiler.cppstd=20
conan install . --build=missing -s build_type=Release #-s compiler.cppstd=20
cmake --build --preset conan-release

#conan install . -s build_type=Release --build=missing
#conan install . -s build_type=Debug --build=missing

#cmake --build --preset conan-release
#cmake --build --preset conan-debug
```
