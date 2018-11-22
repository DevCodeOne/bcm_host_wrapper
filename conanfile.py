from conans import ConanFile, CMake, tools

# udevpp, bcmhost ?
class BcmHostWrapper(ConanFile):
    name = "BcmHostWrapper"
    version = "0.1-2"
    settings = "os", "compiler", "build_type", "arch"
    options = {"build_tests" : [True, False], "use_bcm_host": [True, False]}
    generators = "cmake", "ycm"
    default_options = {"use_bcm_host" : False, "build_tests" : True}
    exports_sources = "tests*", "include*", "src*", "CMakeLists.txt"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["USE_BCM_HOST"] = "On" if self.options.use_bcm_host else "Off"
        cmake.definitions["BUILD_TESTS"] = "On" if self.options.build_tests else "Off"
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = "On"
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy(pattern="*.h", dst="include", src="include")
        self.copy(pattern="*a", dst="lib", keep_path=False)
        self.copy(pattern="*so", dst="lib", keep_path=False)
        self.copy(pattern="*so.*", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
