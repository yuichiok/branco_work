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
hit_energy=ecal['hit_energy'].array()

hit_energy=ak.Array(hit_energy)

index_i = []
for i in range (0 , len(hit_slab)):
    for n in range (0, len(hit_slab[i])):
        if hit_energy[i,n] > 1:
            index_i.append(i)
            
np.savetxt('index_triggers.txt',index_i)

