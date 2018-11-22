from conans import ConanFile, CMake, tools

# udevpp, bcmhost ?
class BcmHostWrapper(ConanFile):
    name = "BcmHostWrapper"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    options = {"use_bcm_host": [True, False]}
    generators = "cmake", "ycm"
    default_options = {"use_bcm_host" : False}

    def build(self):
        cmake = CMake(self)
        cmake.definitions["USE_BCM_HOST"] = "On" if self.options.use_bcm_host else "Off"
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
