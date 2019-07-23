#!/usr/bin/python
from ctypes import *
litho = CDLL("./pythonlib/litholib.so")
import numpy as np
#import pandas as pd


litho.clear_design_space();
litho.read_layout("benchmark/M1_test9.glp");  #for now fixed
