#!/bin/bash

./parser.exe trainData/trainData.fr.txt parsed_fr.data fr
./parser.exe trainData/trainData.en.txt parsed_en.data en
./parser.exe trainData/trainData.de.txt parsed_de.data de
./parser.exe trainData/trainData.es.txt parsed_es.data es
./parser.exe trainData/trainData.pt.txt parsed_pt.data pt
./parser.exe trainData/trainData.it.txt parsed_it.data it
./parser.exe trainData/trainData.tr.txt parsed_tr.data tr

nb_data_fr=$(head -n 1 parsed_fr.data | cut -d ' ' -f1)
nb_data_en=$(head -n 1 parsed_en.data | cut -d ' ' -f1)
nb_data_de=$(head -n 1 parsed_de.data | cut -d ' ' -f1)
nb_data_es=$(head -n 1 parsed_es.data | cut -d ' ' -f1)
nb_data_pt=$(head -n 1 parsed_pt.data | cut -d ' ' -f1)
nb_data_it=$(head -n 1 parsed_it.data | cut -d ' ' -f1)
nb_data_tr=$(head -n 1 parsed_tr.data | cut -d ' ' -f1)

nb_data=$(($nb_data_fr + $nb_data_en + $nb_data_de + $nb_data_es))
nb_data=$(($nb_data + $nb_data_pt + $nb_data_it + $nb_data_tr))

nb_input=$(head -n 1 parsed_fr.data | cut -d ' ' -f2)
nb_output=$(head -n 1 parsed_fr.data | cut -d ' ' -f3)

echo $nb_data $nb_input $nb_output > parsed.data

tail -n +2 parsed_fr.data >> parsed.data
tail -n +2 parsed_en.data >> parsed.data
tail -n +2 parsed_de.data >> parsed.data
tail -n +2 parsed_es.data >> parsed.data
tail -n +2 parsed_pt.data >> parsed.data
tail -n +2 parsed_it.data >> parsed.data
tail -n +2 parsed_tr.data >> parsed.data
