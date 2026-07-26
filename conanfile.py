from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain

class BglShooterConan(ConanFile):
    name = "bgl-shooter"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"

    default_options = {
        "devil/*:with_opengl": True,
        "freeglut/*:with_wayland": False,
    }

    def requirements(self):
        self.requires("freeglut/3.8.0")
        self.requires("glew/2.2.0")
        self.requires("devil/1.8.0")
        self.requires("openal-soft/1.24.3", override=True)
        self.requires("freealut/1.1.0")
        self.requires("glm/1.0.1")
        self.requires("spdlog/1.14.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
