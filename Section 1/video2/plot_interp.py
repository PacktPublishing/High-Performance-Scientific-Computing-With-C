#!/usr/bin/env python3
from sys import argv
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    data = np.genfromtxt(argv[1])
    plt.plot(data[:,0], data[:, 1], 'k.-')
    plt.plot(data[:,0][::10], data[:,1][::10], 'ro')
    plt.show()
