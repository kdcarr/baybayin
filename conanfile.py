from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps, cmake_layout

class MyProject(ConanFile):
    name = "baybayin"
    version = "0.1"
    package_type = "header-library"

    settings = "os", "arch", "compiler", "build_type"

    def requirements(self):
        self.requires("cli11/[>=2.6.0]")
        self.requires("gtest/[>=1.14.0]")

    def layout(self):
        # Automatically manages build/Release and build/Debug folders
        cmake_layout(self)

    def generate(self):
        # Generates <Pkg>Config.cmake files for find_package()
        deps = CMakeDeps(self)
        deps.generate()

        # Generates conan_toolchain.cmake and CMakePresets.json
        tc = CMakeToolchain(self)
        tc.variables["MY_PROJECT_VERSION"] = self.version
        tc.generate()

    def build(self):
        # Allows you to use 'conan build .' as a single-entry command
        cmake = CMake(self)
        cmake.configure()
        cmake.build()