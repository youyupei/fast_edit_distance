from setuptools import setup, find_packages
from Cython.Build import cythonize

with open('README.md', 'r') as f:
    long_description = f.read()



setup(
    name='fast_edit_distance',
    version='1.2.1',
    author='Yupei You',
    author_email="youyupei@gmail.com",
    description='Implementation of edit distance calculation.',
    packages=find_packages(),
    long_description=long_description,
    long_description_content_type='text/markdown',
    url="https://github.com/youyupei/fast_edit_distance",
    install_requires=['cython'],
    classifiers=[
         "Programming Language :: Python :: 3",
         "License :: OSI Approved :: MIT License",
         "Operating System :: OS Independent",
     ],
    ext_modules=cythonize("src/fast_edit_distance.pyx")
)
