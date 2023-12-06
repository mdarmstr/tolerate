# tolerate module in Python
Returns sorted array of unique values within tolerance using the NumPy C API. Similar to uniquetol.m for MATLAB, but with limited functionality.

## Installation instructions

Currently only implemented on Linux-based operating systems with `gcc`.
```
$ gcc tolerate.c -shared -o tolerate.so -I{/path/to/python3.10} -I{path/to/numpy/core/include} -fPIC
```

## Basic usage 

```
>>> import numpy as np
>>> import tolerate
>>> tolerate.return_values(np.array([0.1,0.1,0.2]),0.05)
array([0.1, 0.1, 0.2])
>>> tolerate.return_values(np.array([0.1, 0.1, 0.2],0.1)
array([0.1, 0.1, 0.1])
```
## Use with unsorted NumPy array 
Record the sorted indices of the original data using `np.argsort()`, then perform and inverse sort on an empty array.

```
>>> import numpy as np
>>> import tolerate
>>> arr = np.array([0.2,0.1,0.1])
>>> ind = np.argsort(arr)
>>> unq = tolerate.return_values(arr,0.05)
>>> target_arr = np.zeros(3)
>>> target_arr[ind] = unq
>>> print(target_arr)
array([0.2,0.1,0.1])
```
