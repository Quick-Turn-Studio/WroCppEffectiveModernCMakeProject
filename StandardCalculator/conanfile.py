from conans import ConanFile, CMake


class SevenIDEConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "gtest/1.11.0", "nlohmann_json/3.10.4", "catch2/2.13.7"
    generators = "cmake_find_package"
    default_options = {"libpng:shared": True}

    def config_options(self):
        if self.settings.os == "Windows":
            self.options["gtest"].shared = True
        else:
            self.options["gtest"].shared = False
