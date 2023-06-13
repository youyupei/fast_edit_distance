# from distutils.core import setup
# from Cython.Build import cythonize

# setup(
#     name="fast_edit_distance",
#     version="1.0",
#     ext_modules=cythonize("src/fast_edit_distance.pyx"),
# )

from setuptools import setup, find_packages
from Cython.Build import cythonize

setup(
    name='fast_edit_distance',
    version='1.0.0',
    author='Yupei You',
    author_email="youyupei@gmail.com",
    description='Implementation of edit distance calculation.',
    packages=find_packages(),
    url="https://github.com/youyupei/fast_edit_distance",
    install_requires=['cython'],
    classifiers=[
         "Programming Language :: Python :: 3",
         "License :: OSI Approved :: MIT License",
         "Operating System :: OS Independent",
     ],
    ext_modules=cythonize("src/fast_edit_distance.pyx")
)