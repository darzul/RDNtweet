#!/bin/bash

if test -z "$1" 
then
     echo "Veuillez entrer le nombre de neuronnes cachées souhaités en arguments [3 - 100]"
     exit  
fi

nbrNeurons=$1
./bestTrain.exe trainData/parsed_train.data trainData/parsed_test.data neuronsDataTrained $nbrNeurons
./test.exe trainData/parsed_test.data neuronsDataTrained_$nbrNeurons.net | ./confusionMatrix.pl > stats_$nbrNeurons.txt
