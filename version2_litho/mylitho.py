#!/usr/bin/python
import sys
import numpy as np
import pandas as pd
from ctypes import *
litho = CDLL("./python_lib/litholib.so")

class rect (Structure):
	_fields_ = [("x",c_int),
				("y",c_int),
				("w",c_int),
				("h",c_int),
			   ]
#rect = rect(10,20,30,40)

# print(rect.x,rect.y)
MAX_FILE_NAME_LENGTH = 80
BACKGROUND_REAL = 0.0229
BACKGROUND_IMAG = -0.0217
MASK_REAL = 0.9771
MASK_IMAG = 0.0217
TARGET_INTENSITY = 0.225
MAX_DOSE = 1.02
MIN_DOSE = 0.98


litho.clear_design_space()
litho.read_layout("./Benchmarks/M1_test2.glp");
litho.create_csv("./M1_test2")

df = pd.read_csv('M1_test2.csv', delimiter = ',')
df.values
lx = c_int.in_dll(litho, "urx").value 
ly = c_int.in_dll(litho, "ury").value
print(df.values)





