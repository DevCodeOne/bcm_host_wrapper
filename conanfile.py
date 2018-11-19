from conans import ConanFile, CMake

# udevpp, bcmhost ?
class BcmHostWrapper(ConanFile):
    name = "BcmHostWrapper"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    #requires = ""
    generators = "cmake", "ycm"
    #default_options = {"Qt:shared" : True}

    def build(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = "On"
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ['bcm_host_wrapper']
