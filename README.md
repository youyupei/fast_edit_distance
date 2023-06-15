# Fast calculation of Edit Distance (ED)
A implementation of edit distance with improved runtime. Implemented using C and cython.

## Highlight:
This edit distance calculation is significantly faster than most of existing python package.
It enables a max edit distance search, specifically, if you have a query sequence and wanted 
to find the most similar item in a long list, you could set a maximum edit distance and enable
a fast search.

## Installation:
Install using pip:
```
pip install fast-edit-distance
```
or build from sourch
```
git clone https://github.com/youyupei/fast_edit_distance.git
cd fast_edit_distance
python3 setup.py build
python3 setup.py install --user
```
## Usage:
```
from fast_edit_distance import edit_distance

# example
edit_distance(string1, string2, max_ed=5)
```

## Compare with [Levenshtein.distance](https://maxbachmann.github.io/Levenshtein/levenshtein.html#distance)
The `fast_edit_distance.edit_distance` has the same function as  [Levenshtein.distance](https://maxbachmann.github.io/Levenshtein/levenshtein.html#distance) with significantly improved runtime. Especially when people need to identied pair of strings whose ED are smaller than a number (set `max_ed` in fast_edit_distance.edit_distance). Here is the runtime test with some random sequence (Run the [test/test.py](test/test.py) to reproduce this comparison):
```
Runtime test no max ed cutoff(1_000_000 iteration):
Levenshtein.distance: 46.49s
fast_edit_distance.edit_distance: 12.75s

Runtime test with max ed cutoff 1 (1_000_000 iteration):
Levenshtein.distance: 46.45s
fast_edit_distance.edit_distance: 0.50s
```
