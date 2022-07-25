import numpy as np
import matplotlib.pyplot as plt
file=np.loadtxt('all_good_events.txt')
plt.hist(file,bins=np.arange(-0.5, 15, 1))
plt.show()