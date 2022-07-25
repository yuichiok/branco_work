import numpy as np
import matplotlib.pyplot as plt 
thickness = 500e-6
file = np.loadtxt('/home/irles/Work/Saturation/320um/1MIP/1MIP_500um_BV150_DV10_W1_H500_SP300_SW200_G1.3_T300_A0_D0_BW0_C2_L2_GS0.3_BBBW0.7_MIPU81_1.txt')
imax = np.max( file[:,1] )
print( imax )
tmax = np.min( file[:,0] )
print( tmax )
current = np.linspace(0,imax,100)
tmin = tmax - thickness/3e8
print(tmin)
time = np.linspace(tmin,tmax,100) 
#plt.plot(file[:,0],file[:,1])
plt.xscale('log')
plt.plot(time,current)
plt.xscale('log')
plt.show()
print(tmax-tmin)