#include "fann.h"

/*

Creer le meilleur fichier .net (apprentissage) possible
basé sur des tests effectués au cours de l'apprentissage
en fonction du nombre de neuronnes cachés choisis en entrée.

*/
void train(struct fann *ann, char* trainFile, char *testFile, char *netFile , unsigned int max_epochs, unsigned int epochs_between_reports, float desired_error, const unsigned int num_neurons_hidden) {
        
	struct fann_train_data *trainData, *testData;
	struct fann *annBest = fann_copy(ann);
	float error;
	unsigned int i;
	char buffer[1024];
	float testError = 1;
	float testErrorBest = 1;

	trainData = fann_read_train_from_file(trainFile);
	testData = fann_read_train_from_file(testFile);
	
        	for(i = 1; i <= max_epochs; i++){ 

  		fann_shuffle_train_data(trainData); //melange les données
		error = fann_train_epoch(ann, trainData); //fait une epoque, ann : le réseaux créer, erreur : l'erreur d'apprentissage
               
		//Toute les 10 epoques 
		if(i % epochs_between_reports == 0 || error < desired_error){
                        	
			fann_test_data(ann,testData);// teste le reseau sur les donnée de test
	
			testError = fann_get_MSE(ann);
			if (testError < testErrorBest) {
				testErrorBest = testError;
				annBest = fann_copy(ann);
				printf("Epochs     %8d; trainError : %f; testError : %f;\n", i, error,testError);
			}		
                	}
		if(error < desired_error){
			break;
		}
	}
	sprintf(buffer,"%s_%u.net",netFile,num_neurons_hidden);
	fann_save(annBest, buffer);
	fann_destroy_train(trainData);
	fann_destroy_train(testData);
}


int main(int argc , char **argv) {
	unsigned int num_data;
	unsigned int num_input;
	unsigned int num_output;
	const unsigned int num_layers=3 ; //input, hidden and output
	unsigned int num_neurons_hidden;
	const float desired_error = 0.0001;
	const unsigned int max_iterations = 500;
	const unsigned int iterations_between_reports = 10;

	if (argc != 5) {
		printf("usage : train trainFile.txt testFile.txt ouputNetBasename nbrHiddenNeurons\n");
		return 0;
	}

	FILE *in= fopen(argv[1],"r");
	fscanf(in,"%d %d %d\n",&num_data,&num_input,&num_output);
	fclose(in);

	num_neurons_hidden = (unsigned int) atoi (argv[4]);

	struct fann *ann = fann_create_standard( num_layers, num_input, num_neurons_hidden, num_output);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC); 
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC); 

	train(ann, argv[1],argv[2],argv[3], max_iterations,iterations_between_reports, desired_error,num_neurons_hidden);

	fann_destroy(ann);

	return 0;
}
