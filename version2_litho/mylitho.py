#!/usr/bin/python
import sys
import numpy as np
from ctypes import *
litho = CDLL("./python_lib/litholib.so")


#infile  = sys.argv[1]
#outfile = sys.argv[2]
MAX_FILE_NAME_LENGTH = 80
BACKGROUND_REAL = 0.0229
BACKGROUND_IMAG = -0.0217
MASK_REAL = 0.9771
MASK_IMAG = 0.0217
TARGET_INTENSITY = 0.225
MAX_DOSE = 1.02
MIN_DOSE = 0.98


litho.clear_design_space()
litho.read_layout("./Benchmarks/M1_test1.glp");
print("%d",litho.urx)
print("%d",litho.ury)