import time
import numpy as np
import fast_edit_distance 
import Levenshtein



def random_seq_generator():
    while True:
        yield ''.join(np.random.choice(['A', 'G', "C", 'T'],  size=np.random.randint(20,50)))
rand_seq = random_seq_generator()
print("Runtime test no max ed cutoff(1_000_000 iteration):")
np.random.seed(2023)
start_time = time.time()
a = next(rand_seq)
b = next(rand_seq)
l_ed = []
for i in range(1_000_000):
    l_ed.append(Levenshtein.distance(a, b))
end_time = time.time()
print(f"Levenshtein.distance: {end_time - start_time:.2f}s" )

np.random.seed(2023)
start_time = time.time()
a = next(rand_seq)
b = next(rand_seq)
fast_ed = []
for i in range(1_000_000):
    fast_ed.append(fast_edit_distance.edit_distance(a, b))
end_time = time.time()
print(f"fast_edit_distance.edit_distance: {end_time - start_time:.2f}s")
print("Result consistant?")
print("No!" if any(np.array(l_ed) != np.array(fast_ed)) else "Yes!")

print("Runtime test with max ed cutoff 1 (1_000_000 iteration):")
np.random.seed(2023)
start_time = time.time()
a = next(rand_seq)
b = next(rand_seq)
l_ed = []
for i in range(1_000_000):
    l_ed.append(Levenshtein.distance(a, b, score_cutoff=1))
end_time = time.time()
print(f"Levenshtein.distance: {end_time - start_time:.2f}s" )

np.random.seed(2023)
start_time = time.time()
a = next(rand_seq)
b = next(rand_seq)
fast_ed = []
for i in range(1_000_000):
    fast_ed.append(fast_edit_distance.edit_distance(a, b, 1))
end_time = time.time()
print(f"fast_edit_distance.edit_distance: {end_time - start_time:.2f}s")
print("Result consistant?")
print("No!" if any(np.array(l_ed) != np.array(fast_ed)) else "Yes!")
