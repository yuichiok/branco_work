#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jun 20 18:02:09 2022

@author: irles
"""
#importation of libraries
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
energy=ecal['hit_energy'].array()
print(energy)
'''
#searching for indexes with atleast 10 slabs activated
index_10_layers = []
for i in range (0 , len(nhit_slab)):
    if nhit_slab[i]>= 10:
        index_10_layers.append(i)
#for a specific time
position_x=[]
max=0

for i in range (0,len(index_10_layers)): 
        position_x.append(hit_y[i])
        length=len(hit_y[i])
        if length>max:
                max=length

tab_good_events=20*np.ones([len(index_10_layers),max])
for i in range (0,len(index_10_layers)):
        for n in range (0,len(hit_slab[i,:])):
                tab_good_events[i,n]=position_x[i][n]
        
print(tab_good_events)
np.savetxt('position_y.txt',tab_good_events,fmt='%s')

all_good_events=[]

for i in range (0,len(index_10_layers)): 
        for n in range (0, len(hit_slab[i,:])):            
                all_good_events.append(hit_slab[i,n])

plt.hist(good_events[2000],bins=np.arange(-0.5, 15, 1))
plt.show()
'''