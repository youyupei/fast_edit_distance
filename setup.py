from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize("src/fast_edit_distance.pyx")
)
