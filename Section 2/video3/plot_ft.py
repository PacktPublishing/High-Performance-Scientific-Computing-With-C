#!/usr/bin/env python3
from sys import argv
import numpy as np
import matplotlib.pyplot as plt

if __name__ == "__main__":
    data = np.genfromtxt(argv[1])
    n = data.shape[0]
    plt.plot(np.arange(0, n/2), data[:,1][:int(n/2)]/data[:,1].max(), 'rx', label='Real FT Component')
    plt.plot(np.arange(0, n/2), data[:,2][:int(n/2)]/data[:,2].max(), 'bx', label='Imag FT Component')
    plt.plot(np.arange(0, n/2), data[:,0][:int(n/2)]/data[:,0].max(), 'ko', label='Function')
    plt.plot(np.arange(-n/2, 0), data[:,1][int(n/2):]/data[:,1].max(), 'rx')
    plt.plot(np.arange(-n/2, 0), data[:,2][int(n/2):]/data[:,2].max(), 'bx')
    plt.plot(np.arange(-n/2, 0), np.flip(data[:,0][:int(n/2)]/data[:,0].max(), 0), 'ko')
    plt.legend(loc='best')
    plt.show()
