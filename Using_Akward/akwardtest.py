import awkward as ak
from asyncio import events
import  ROOT
import uproot
import numpy as np
import matplotlib.pyplot as plt

#opening the file 

file= uproot.open('./full_run.root')
ecal= file['ecal']
ecal.keys()

#making some arrays 
event=ecal["event"].array() #donne le nombre d'evenenements
nhit_slab=ecal["nhit_slab"].array() #donne le nombre de slabs actives
hit_slab=ecal["hit_slab"].array() #donne le numero de la slab hit
hit_x=ecal["hit_x"].array() #donne toutes les positions de x pour un y donne
hit_y=ecal["hit_y"].array()
hit_z=ecal["hit_z"].array()
""""
nhit_slab=ak.Array(nhit_slab)
#searching for indexes with atleast 10 slabs activated
index_10_layers = []
for i in range (0 , len(nhit_slab)):
    if nhit_slab[i]>= 10:
        index_10_layers.append(i)

np.savetxt('index.txt',index_10_layers)
"""