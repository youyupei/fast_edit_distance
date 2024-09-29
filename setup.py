from setuptools import setup
from Cython.Build import cythonize
import setuptools_scm

version = setuptools_scm.get_version()
setup(
    ext_modules=cythonize("src/fast_edit_distance.pyx"),
    version=version # I have to do this because setuptools_scm doesn't work with Cython (the cythonize function would modify the repo so that the version is not the same as the one in the repo)
)
