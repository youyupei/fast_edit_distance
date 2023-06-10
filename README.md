# fast_edit_distance
A implementation of edit distance with improved runtime. Implemented using C and cython.

## Highlight:
This edit distance calculation is significantly faster than most of existing python package.
It enables a max edit distance search, specifically, if you have a query sequence and wanted 
to find the most similar item in a long list, you could set a maximum edit distance and enable
a fast search.

## Installation:
```
python3 setup.py build
python3 setup.py install --user
```
## Usage:
```
from fast_edit_distance import edit_distance

# example
edit_distance(string1, string2, max_ed=5)
```

