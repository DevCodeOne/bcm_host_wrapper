from conans import ConanFile, CMake

# udevpp, bcmhost ?
class BcmHostWrapper(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    #requires = ""
    generators = "cmake", "ycm"
    #default_options = {"Qt:shared" : True}

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
