#!/bin/bash

if test -z "$1" 
then
     echo "Veuillez entrer le nombre de neuronnes cachées souhaités"
fi

nbrNeurons = $1
./bestTrain trainDataSet.txt testDataSet.txt neuronsDataTrained $nbrNeurons
./test.exe testDataSet neuronsDataTrained_$nbrNeurons.net > prediction.txt
./confusionMatrix.pl < prediction.txt > stats_$nbrNeurons.txt
