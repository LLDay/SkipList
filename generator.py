import numpy as np

arr = np.arange(1000000)
np.random.shuffle(arr)

sample = open('sample.txt', 'w')
sample.writelines(str(i) + '\n' for i in arr[:-1])
sample.write(str(arr[-1]))
sample.close()