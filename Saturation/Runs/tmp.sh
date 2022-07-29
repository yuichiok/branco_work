#!/bin/bash

l_energy=(10 20 40 60 80 100 150)
l_run=(320 378 375 372 367 365 355)
counter=0

for energy in ${l_energy[@]};
do
    ln -s ~/work/calice/CaliceAnalysis/data/reco/raw_siwecal_90${l_run[counter]}/full_run.root ${energy}GeV.root
    (( counter++ ))
done