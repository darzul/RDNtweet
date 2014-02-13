#!/bin/bash

./parser.exe trainData/trainData.fr.txt parsed_fr.data fr
./parser.exe trainData/trainData.en.txt parsed_en.data en
./parser.exe trainData/trainData.de.txt parsed_de.data de
./parser.exe trainData/trainData.es.txt parsed_es.data es
./parser.exe trainData/trainData.pt.txt parsed_pt.data pt
./parser.exe trainData/trainData.it.txt parsed_it.data it
./parser.exe trainData/trainData.tr.txt parsed_tr.data tr
