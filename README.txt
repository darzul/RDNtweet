Clean all .exe and .o
make clean

Compile .c
make

Split datas, parse it and parse eval.txt
./parser.sh %data_test

Train the neural network
./trainTestAndTellMe.sh nb_neuron_hidden_couch
-> network = neuronsDataTrained_X.net
-> confusion matrix = stats_X.txt

Test eval data with the network
./testEval eval.txt neuron_network.net
