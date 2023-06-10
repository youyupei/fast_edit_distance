# cython: language_level=3
# edit_distance_cython.pyx
import sys


cdef extern from "edit_distance_c.c":
    int edit_distance_c(char* word1, char* word2, int max_ed, int check_mat) 

cpdef int edit_distance(str word1, str word2, max_ed=None, bint check_mat=False):
    """
    Calculate edit distance of two strings with same length. It allows early stop if
    a max_ed is reached. Efficient in both runtime and memory when e.g. searching a similar
    item from a library.

    Parameters:
    - word1, word2: The two strings to compare.
    - max_ed: The maximum edit distance allowed. Default: None
    For developer only:  
    - check_mat: check the dynamic programing process for trouble shooting

    Returns:
    Edit distance. If a `max_ed` is set, the function will return -1 if the 
    edit distance is large than the maximum.
    """
    try:
        assert len(word1) == len(word2), "The input strings must have same length!"
    except AssertionError as e:
        print(f'Error:{e}')
        sys.exit(1)
    cdef int max_ed_c
    max_ed_c = max_ed if max_ed else max(len(word1), len(word2))
    
    cdef bytes w1 = word1.encode('utf-8')
    cdef bytes w2 = word2.encode('utf-8')
    return edit_distance_c(w1, w2, max_ed_c, check_mat)

