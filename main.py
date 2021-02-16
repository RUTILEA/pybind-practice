import mod
import cv2
import time
import numpy as np

print(mod.add(2, 3))
print(mod.make_array())

print(mod.multiply(mod.make_array(), mod.make_array()))


def calc():
    array = np.array([[1,2,3],[4,5,6],[7,8,9]])
    for i in range(0,int(1e6)):
        np.linalg.det(array)


start = time.time()
mod.calc()
end = time.time()
print(end - start)


start = time.time()
calc()
end = time.time()
print(end - start)
