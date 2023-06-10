from distutils.core import setup
from Cython.Build import cythonize

setup(
    name="fast_edit_distance",
    version="1.0",
    ext_modules=cythonize("src/fast_edit_distance.pyx"),
)