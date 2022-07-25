import numpy as np
import matplotlib.pyplot as plt
file=np.loadtxt('good_events.txt')
plt.hist(file[2000],bins=np.arange(-0.5, 15, 1))
plt.show()