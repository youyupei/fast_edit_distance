
import numpy as np
import fast_edit_distance 
import Levenshtein
import timeit


def random_seq_generator():
    while True:
        yield ''.join(np.random.choice(['A', 'G', "C", 'T'],  size=np.random.randint(20,50)))
rand_seq = random_seq_generator()
print("Checking the consistency between Levenshtein package and fast_edit_distance package...")

np.random.seed(2023)
a = next(rand_seq)
b = next(rand_seq)
for i in range(1_000_000):
    l_ed = Levenshtein.distance(a, b)
    fast_ed = fast_edit_distance.edit_distance(a, b)
    if l_ed != fast_ed:
        print(l_ed == fast_ed)
        print(a,b, l_ed, fast_ed)
        break

