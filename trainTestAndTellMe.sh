#!/bin/bash

DATA_DIR="trainData"

if test -z "$1" 
then
     echo "Veuillez entrer le nombre de neuronnes cachées souhaités en arguments [3 - 100]"
     exit  
fi

nbrNeurons=$1
./bestTrain.exe trainData/parsed_train.data $DATA_DIR/trainingBaseParsed.txt neuronsDataTrained $nbrNeurons
./test.exe $DATA_DIR/testingBaseParsed.txt neuronsDataTrained_$nbrNeurons.net | ./confusionMatrix.pl > stats_$nbrNeurons.txt
