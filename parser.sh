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


echo "[Generating parsed data]"

./parser.exe $DATA_DIR/trainData.fr.txt $DATA_DIR/parsed_fr.data fr charset.txt
./parser.exe $DATA_DIR/trainData.en.txt $DATA_DIR/parsed_en.data en charset.txt
./parser.exe $DATA_DIR/trainData.de.txt $DATA_DIR/parsed_de.data de charset.txt
./parser.exe $DATA_DIR/trainData.es.txt $DATA_DIR/parsed_es.data es charset.txt
./parser.exe $DATA_DIR/trainData.pt.txt $DATA_DIR/parsed_pt.data pt charset.txt
./parser.exe $DATA_DIR/trainData.it.txt $DATA_DIR/parsed_it.data it charset.txt
./parser.exe $DATA_DIR/trainData.tr.txt $DATA_DIR/parsed_tr.data tr charset.txt


echo "[Merging all data files]"

nb_data_fr=$(( $(wc -l $DATA_DIR/parsed_fr.data | cut -d ' ' -f1) - 1 ))
nb_data_en=$(( $(wc -l $DATA_DIR/parsed_en.data | cut -d ' ' -f1) - 1 ))
nb_data_de=$(( $(wc -l $DATA_DIR/parsed_de.data | cut -d ' ' -f1) - 1 ))
nb_data_es=$(( $(wc -l $DATA_DIR/parsed_es.data | cut -d ' ' -f1) - 1 ))
nb_data_pt=$(( $(wc -l $DATA_DIR/parsed_pt.data | cut -d ' ' -f1) - 1 ))
nb_data_it=$(( $(wc -l $DATA_DIR/parsed_it.data | cut -d ' ' -f1) - 1 ))
nb_data_tr=$(( $(wc -l $DATA_DIR/parsed_tr.data | cut -d ' ' -f1) - 1 ))

nb_data=$(($nb_data_fr + $nb_data_en + $nb_data_de + $nb_data_es))
nb_data=$(($nb_data + $nb_data_pt + $nb_data_it + $nb_data_tr))
echo -e "\tTotal data: "$nb_data

nb_input=$(head -n 1 $DATA_DIR/parsed_fr.data | cut -d ' ' -f2)
nb_output=$(head -n 1 $DATA_DIR/parsed_fr.data | cut -d ' ' -f3)

echo $nb_data $nb_input $nb_output > $DATA_DIR/parsed.data

tail -n +2 $DATA_DIR/parsed_fr.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_en.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_de.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_es.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_pt.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_it.data >> $DATA_DIR/parsed.data
tail -n +2 $DATA_DIR/parsed_tr.data >> $DATA_DIR/parsed.data


echo "[Creating test data]"

nb_data_fr_test=$(( ($nb_data_fr * $perc_test) / 100))
nb_data_en_test=$(( ($nb_data_en * $perc_test) / 100))
nb_data_de_test=$(( ($nb_data_de * $perc_test) / 100))
nb_data_es_test=$(( ($nb_data_es * $perc_test) / 100))
nb_data_pt_test=$(( ($nb_data_pt * $perc_test) / 100))
nb_data_it_test=$(( ($nb_data_it * $perc_test) / 100))
nb_data_tr_test=$(( ($nb_data_tr * $perc_test) / 100))

nb_data_test=$(($nb_data_fr_test + $nb_data_en_test + $nb_data_de_test + $nb_data_es_test))
nb_data_test=$(($nb_data_test + $nb_data_pt_test + $nb_data_it_test + $nb_data_tr_test))
echo -e "\tTested data: "$nb_data_test

echo $nb_data_test $nb_input $nb_output > $DATA_DIR/parsed_test.data

tail -n $nb_data_fr_test $DATA_DIR/parsed_fr.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_en_test $DATA_DIR/parsed_en.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_de_test $DATA_DIR/parsed_de.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_es_test $DATA_DIR/parsed_es.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_pt_test $DATA_DIR/parsed_pt.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_it_test $DATA_DIR/parsed_it.data >> $DATA_DIR/parsed_test.data
tail -n $nb_data_tr_test $DATA_DIR/parsed_tr.data >> $DATA_DIR/parsed_test.data


echo "[Creating train data]"

nb_data_fr_train=$(( ($nb_data_fr * (100 - $perc_test) / 100) ))
nb_data_en_train=$(( ($nb_data_en * (100 - $perc_test) / 100) ))
nb_data_de_train=$(( ($nb_data_de * (100 - $perc_test) / 100) ))
nb_data_es_train=$(( ($nb_data_es * (100 - $perc_test) / 100) ))
nb_data_pt_train=$(( ($nb_data_pt * (100 - $perc_test) / 100) ))
nb_data_it_train=$(( ($nb_data_it * (100 - $perc_test) / 100) ))
nb_data_tr_train=$(( ($nb_data_tr * (100 - $perc_test) / 100) ))

nb_data_train=$(($nb_data_fr_train + $nb_data_en_train + $nb_data_de_train + $nb_data_es_train))
nb_data_train=$(($nb_data_train + $nb_data_pt_train + $nb_data_it_train + $nb_data_tr_train))
echo -e "\tTraining data: "$nb_data_train

echo $nb_data_train $nb_input $nb_output > $DATA_DIR/parsed_train.data

head -n $(($nb_data_fr_train + 1)) $DATA_DIR/parsed_fr.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_en_train + 1)) $DATA_DIR/parsed_en.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_de_train + 1)) $DATA_DIR/parsed_de.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_es_train + 1)) $DATA_DIR/parsed_es.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_pt_train + 1)) $DATA_DIR/parsed_pt.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_it_train + 1)) $DATA_DIR/parsed_it.data | tail -n +2  >> $DATA_DIR/parsed_train.data
head -n $(($nb_data_tr_train + 1)) $DATA_DIR/parsed_tr.data | tail -n +2  >> $DATA_DIR/parsed_train.data
