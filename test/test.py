# import time,sys
# import pandas as pd
# from edit_distance_cython import edit_distance as my_ed
# from Levenshtein import distance as ed

# test_bc = pd.read_csv('~/vol_data/github_repo/shimlab/BLAZE/test/putative_bc.csv')
# test_bc = list(test_bc.putative_bc.dropna())[:5000]
# test_bc = [x for x in test_bc]


# start_time = time.time()
# count = 0
# for i in range(len(test_bc)):
#     for j in range(i+1, len(test_bc)):
#         if ed(test_bc[i], test_bc[j]) <= 16:
#             count += 1
# end_time = time.time()

# runtime = end_time - start_time
# print("Levenshtein package: Runtime: ", runtime, "Result: ", count)

# start_time = time.time()
# count = 0
# for i in range(len(test_bc)):
#     for j in range(i+1, len(test_bc)):
#         if my_ed(test_bc[i], test_bc[j], 16) > -1:
#             count += 1
# end_time = time.time()

# runtime = end_time - start_time
# print("My ED implementation: Runtime: ", runtime, "Result: ", count)


## example

# test_bc = pd.read_csv('~/vol_data/github_repo/shimlab/BLAZE/test/putative_bc.csv')
# test_bc = list(test_bc.putative_bc.dropna())[:2000]

# start_time = time.time()
# count = 0
# for i in range(len(test_bc)):
#     for j in range(i+1, len(test_bc)):
#         ed_other = ed(test_bc[i], test_bc[j])
#         ed_my = my_ed(test_bc[i], test_bc[j], 16)
#         if (ed_my != ed_other and ed_my != -1) or (ed_my == -1 and ed_other<=16):
#             print(test_bc[i], test_bc[j],ed_my,ed_other)
#             count += 1
# end_time = time.time()

a = 'fsffvfdsbbdfvvdavavavavavavaa'
b = 'fvdaabavvvvvadvdvavavadfsfsdafvvav'

import fast_edit_distance 
import Levenshtein
import timeit

fast_edit_distance.edit_distance(a, b)



# # Measure the execution time
# execution_time = timeit.timeit(func, number=10000)
# # Print the execution time
# print("Execution time (fast_edit_distance):", execution_time)

# def func():
#     Levenshtein.distance(a, b)

# # Measure the execution time
# execution_time = timeit.timeit(func, number=10000)
# # Print the execution time
# print("Execution time (Levenshtein):", execution_time)
