import numpy as np

small_circle = []
for N in [9, 17, 25, 33, 41, 49]:
    small_circle += [(N-1)*np.exp(t*2j*np.pi) for t in np.linspace(0,1,N)]

for x in small_circle:
    print((round(x.real, 2), round(x.imag, 2)))