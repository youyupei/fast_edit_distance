# cython: language_level=3
# edit_distance_cython.pyx
cdef extern from "edit_distance_c.c":
    int edit_distance_c(char* word1, char* word2, int max_ed, int check_mat) 

cpdef int edit_distance(str word1, str word2, int max_ed, bint check_mat=False):
    cdef bytes w1 = word1.encode('utf-8')
    cdef bytes w2 = word2.encode('utf-8')
    return edit_distance_c(w1, w2, max_ed, check_mat)
