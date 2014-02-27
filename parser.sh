#!/bin/bash

DATA_DIR="trainData"

if [ ! -n "$1" ]
	then
		echo ./parser.sh %_data_test
		exit 0
fi

if (($1 <= 0 || $1 >= 100))
	then
		echo % must be between 0 and 100
		exit 0
fi

perc_test=$1


nb_data_fr=$(wc -l $DATA_DIR/parsed_fr.data | cut -d ' ' -f1)
nb_data_en=$(wc -l $DATA_DIR/parsed_en.data | cut -d ' ' -f1)
nb_data_de=$(wc -l $DATA_DIR/parsed_de.data | cut -d ' ' -f1)
nb_data_es=$(wc -l $DATA_DIR/parsed_es.data | cut -d ' ' -f1)
nb_data_pt=$(wc -l $DATA_DIR/parsed_pt.data | cut -d ' ' -f1)
nb_data_it=$(wc -l $DATA_DIR/parsed_it.data | cut -d ' ' -f1)
nb_data_tr=$(wc -l $DATA_DIR/parsed_tr.data | cut -d ' ' -f1)

nb_data=$(($nb_data_fr + $nb_data_en + $nb_data_de + $nb_data_es))
nb_data=$(($nb_data + $nb_data_pt + $nb_data_it + $nb_data_tr))
echo  "Total tweets: "$nb_data


echo "[Creating testing data]"

nb_data_fr_test=$(( ($nb_data_fr * $perc_test) / 100))
nb_data_en_test=$(( ($nb_data_en * $perc_test) / 100))
nb_data_de_test=$(( ($nb_data_de * $perc_test) / 100))
nb_data_es_test=$(( ($nb_data_es * $perc_test) / 100))
nb_data_pt_test=$(( ($nb_data_pt * $perc_test) / 100))
nb_data_it_test=$(( ($nb_data_it * $perc_test) / 100))
nb_data_tr_test=$(( ($nb_data_tr * $perc_test) / 100))

tail -n $nb_data_fr_test $DATA_DIR/trainData.fr.txt > $DATA_DIR/testingBase_fr.txt
tail -n $nb_data_en_test $DATA_DIR/trainData.en.txt > $DATA_DIR/testingBase_en.txt
tail -n $nb_data_de_test $DATA_DIR/trainData.de.txt > $DATA_DIR/testingBase_de.txt
tail -n $nb_data_es_test $DATA_DIR/trainData.es.txt > $DATA_DIR/testingBase_es.txt
tail -n $nb_data_pt_test $DATA_DIR/trainData.pt.txt > $DATA_DIR/testingBase_pt.txt
tail -n $nb_data_it_test $DATA_DIR/trainData.it.txt > $DATA_DIR/testingBase_it.txt
tail -n $nb_data_tr_test $DATA_DIR/trainData.tr.txt > $DATA_DIR/testingBase_tr.txt


echo -e "\n[Parsing testing data]"

echo -e "\t[FR]"
./parser.exe $DATA_DIR/testingBase_fr.txt $DATA_DIR/testingBaseParsed_fr.txt fr charset.txt testing
echo -e "\t[EN]"
./parser.exe $DATA_DIR/testingBase_en.txt $DATA_DIR/testingBaseParsed_en.txt en charset.txt testing
echo -e "\t[DE]"
./parser.exe $DATA_DIR/testingBase_de.txt $DATA_DIR/testingBaseParsed_de.txt de charset.txt testing
echo -e "\t[ES]"
./parser.exe $DATA_DIR/testingBase_es.txt $DATA_DIR/testingBaseParsed_es.txt es charset.txt testing
echo -e "\t[PT]"
./parser.exe $DATA_DIR/testingBase_pt.txt $DATA_DIR/testingBaseParsed_pt.txt pt charset.txt testing
echo -e "\t[IT]"
./parser.exe $DATA_DIR/testingBase_it.txt $DATA_DIR/testingBaseParsed_it.txt it charset.txt testing
echo -e "\t[TR]"
./parser.exe $DATA_DIR/testingBase_tr.txt $DATA_DIR/testingBaseParsed_tr.txt tr charset.txt testing

nb_input=$(head -n 1 $DATA_DIR/testingBaseParsed_fr.txt | cut -d ' ' -f2)
nb_output=$(head -n 1 $DATA_DIR/testingBaseParsed_fr.txt | cut -d ' ' -f3)


echo -e "\n[Merging testing data]"

nb_data_test=$(($nb_data_fr_test + $nb_data_en_test + $nb_data_de_test + $nb_data_es_test))
nb_data_test=$(($nb_data_test + $nb_data_pt_test + $nb_data_it_test + $nb_data_tr_test))
echo -e "\tTesting data: "$nb_data_test

echo $nb_data_test $nb_input $nb_output > $DATA_DIR/testingBaseParsed.txt

tail -n +2 $DATA_DIR/testingBaseParsed_fr.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_en.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_de.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_es.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_pt.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_it.txt >> $DATA_DIR/testingBaseParsed.txt
tail -n +2 $DATA_DIR/testingBaseParsed_tr.txt >> $DATA_DIR/testingBaseParsed.txt





echo -e "\n\n[Creating training data]"

nb_data_fr_train=$(( ($nb_data_fr * (100 - $perc_test) / 100) ))
nb_data_en_train=$(( ($nb_data_en * (100 - $perc_test) / 100) ))
nb_data_de_train=$(( ($nb_data_de * (100 - $perc_test) / 100) ))
nb_data_es_train=$(( ($nb_data_es * (100 - $perc_test) / 100) ))
nb_data_pt_train=$(( ($nb_data_pt * (100 - $perc_test) / 100) ))
nb_data_it_train=$(( ($nb_data_it * (100 - $perc_test) / 100) ))
nb_data_tr_train=$(( ($nb_data_tr * (100 - $perc_test) / 100) ))

head -n $(($nb_data_fr_train + 1)) $DATA_DIR/trainData.fr.txt | tail -n +2  > $DATA_DIR/trainingBase_fr.txt
head -n $(($nb_data_en_train + 1)) $DATA_DIR/trainData.en.txt | tail -n +2  > $DATA_DIR/trainingBase_en.txt
head -n $(($nb_data_de_train + 1)) $DATA_DIR/trainData.de.txt | tail -n +2  > $DATA_DIR/trainingBase_de.txt
head -n $(($nb_data_es_train + 1)) $DATA_DIR/trainData.es.txt | tail -n +2  > $DATA_DIR/trainingBase_es.txt
head -n $(($nb_data_pt_train + 1)) $DATA_DIR/trainData.pt.txt | tail -n +2  > $DATA_DIR/trainingBase_pt.txt
head -n $(($nb_data_it_train + 1)) $DATA_DIR/trainData.it.txt | tail -n +2  > $DATA_DIR/trainingBase_it.txt
head -n $(($nb_data_tr_train + 1)) $DATA_DIR/trainData.tr.txt | tail -n +2  > $DATA_DIR/trainingBase_tr.txt


echo -e "\n[Parsing training data]"

echo -e "\t[FR]"
./parser.exe $DATA_DIR/trainingBase_fr.txt $DATA_DIR/trainingBaseParsed_fr.txt fr charset.txt
echo -e "\t[EN]"
./parser.exe $DATA_DIR/trainingBase_en.txt $DATA_DIR/trainingBaseParsed_en.txt en charset.txt
echo -e "\t[DE]"
./parser.exe $DATA_DIR/trainingBase_de.txt $DATA_DIR/trainingBaseParsed_de.txt de charset.txt
echo -e "\t[ES]"
./parser.exe $DATA_DIR/trainingBase_es.txt $DATA_DIR/trainingBaseParsed_es.txt es charset.txt
echo -e "\t[PT]"
./parser.exe $DATA_DIR/trainingBase_pt.txt $DATA_DIR/trainingBaseParsed_pt.txt pt charset.txt
echo -e "\t[IT]"
./parser.exe $DATA_DIR/trainingBase_it.txt $DATA_DIR/trainingBaseParsed_it.txt it charset.txt
echo -e "\t[TR]"
./parser.exe $DATA_DIR/trainingBase_tr.txt $DATA_DIR/trainingBaseParsed_tr.txt tr charset.txt


echo -e "\n[Merging training data]"

nb_data_fr=$(( $(wc -l $DATA_DIR/trainingBaseParsed_fr.txt | cut -d ' ' -f1) - 1))
nb_data_en=$(( $(wc -l $DATA_DIR/trainingBaseParsed_en.txt | cut -d ' ' -f1) - 1))
nb_data_de=$(( $(wc -l $DATA_DIR/trainingBaseParsed_de.txt | cut -d ' ' -f1) - 1))
nb_data_es=$(( $(wc -l $DATA_DIR/trainingBaseParsed_es.txt | cut -d ' ' -f1) - 1))
nb_data_pt=$(( $(wc -l $DATA_DIR/trainingBaseParsed_pt.txt | cut -d ' ' -f1) - 1))
nb_data_it=$(( $(wc -l $DATA_DIR/trainingBaseParsed_it.txt | cut -d ' ' -f1) - 1))
nb_data_tr=$(( $(wc -l $DATA_DIR/trainingBaseParsed_tr.txt | cut -d ' ' -f1) - 1))

nb_data=$(($nb_data_fr + $nb_data_en + $nb_data_de + $nb_data_es))
nb_data=$(($nb_data + $nb_data_pt + $nb_data_it + $nb_data_tr))
echo  "Training data: "$nb_data

echo $nb_data $nb_input $nb_output > $DATA_DIR/trainingBaseParsed.txt

tail -n +2 $DATA_DIR/trainingBaseParsed_fr.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_en.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_de.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_es.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_pt.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_it.txt >> $DATA_DIR/trainingBaseParsed.txt
tail -n +2 $DATA_DIR/trainingBaseParsed_tr.txt >> $DATA_DIR/trainingBaseParsed.txt
