import os
from os.path import join

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy
from conan.tools.scm import Git


class EQMSoftwareRecipe(ConanFile):
    name = "obc-eqm-sw"
    version = "1.0"
    revision_mode = "scm"

    # Optional metadata
    license = "MIT"
    author = "SpaceDot - AcubeSAT, acubesat.obc@spacedot.gr"
    url = "https://github.com/PeakSat/OBC-EQM-Software"
    description = "EQM Software for OBCcampaign test"
    topics = ("satellite", "peaksat", "obc", "obc-software")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": False, "ecss-services/*:ecss_config_file_path": os.path.abspath("inc/Platform/")}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "inc/*", "lib/*"
    generators = "CMakeDeps"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def source(self):
        git = Git(self)
        git.clone(url="git@github.com:cmcqueen/cobs-c.git", target=join(str(self.source_folder), "lib/cobs-c"))
        git = Git(self)
        git.clone(url="https://gitlab.com/acubesat/obc/atsam-component-drivers.git", target=join(str(self.source_folder), "lib/atsam-component-drivers"))
        self.run("cd lib/atsam-component-drivers && git checkout NAND-implementation")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def requirements(self):
        self.requires("etl/20.37.2")
        self.requires("logger/1.0")
        self.requires("ecss-services/0.9")
