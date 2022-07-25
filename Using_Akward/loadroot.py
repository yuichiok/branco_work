import awkward as ak
from asyncio import events
import  ROOT
import uproot
import numpy as np
import matplotlib.pyplot as plt

#opening the file 

file= uproot.open('/home/irles/Work/Saturation/full_run.root')
ecal= file['ecal']
ecal.keys()
print(ecal.keys())
index=np.loadtxt('index.txt')


#making some arrays 
event=ecal["hit_n_scas_filled"].array() #donne le nombre d'evenenements
print(event)
