#!/usr/bin/python

import numpy as np
import os,sys
import random

size = sys.argv[1]

f1 = open("input1.in","w")
f2 = open("input2.in","w")
f3 = open("reference.in","w")

matrix1 = []
matrix2 = []
for i in range(int(size)):
    arr1 = []
    arr2 = []
    for j in range(int(size)):
        num = random.randint(0,5)
        num2 = random.randint(0,5)
        arr1.append(num)
        arr2.append(num2)
        f1.write(str(num) + " ")
        f2.write(str(num2) + " ")
    f1.write("\n")
    f2.write("\n")
    matrix1.append(arr1)
    matrix2.append(arr2)

m1 = np.array(matrix1)
m2 = np.array(matrix2)
result = np.matmul(m1,m2)

for i in result:
    for j in i:
        f3.write(str(j) + " ")
    f3.write("\n")

f1.close()
f2.close()
f3.close()


