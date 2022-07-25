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
index=np.loadtxt('index.txt')


#making some arrays 
event=ecal["event"].array() #donne le nombre d'evenenements
nhit_slab=ecal["nhit_slab"].array() #donne le nombre de slabs actives
hit_slab=ecal["hit_slab"].array() #donne le numero de la slab hit
hit_x=ecal["hit_x"].array() #donne toutes les positions de x pour un y donne
hit_y=ecal["hit_y"].array()
hit_z=ecal["hit_z"].array()


#Tableau du nombre de hit par slab

hit_y=ak.Array(hit_y)
hits=[]
for i in range (0,len(hit_y)):
    if i in index:
        hits.append(hit_y[i])
hits=ak.Array(hits)

OUT= uproot.create('position_y.root')
OUT['hits']=hits
test=OUT['hits']
