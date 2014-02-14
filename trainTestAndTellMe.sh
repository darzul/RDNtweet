#!/bin/bash

if test -z "$1" 
then
     echo "Veuillez entrer le nombre de neuronnes cachées souhaités en arguments [3 - 100]"
     exit  
fi

nbrNeurons=$1
./bestTrain trainDataSet.txt testDataSet.txt neuronsDataTrained $nbrNeurons
./test.exe testDataSet neuronsDataTrained_$nbrNeurons.net | ./confusionMatrix.pl > stats_$nbrNeurons.txt
