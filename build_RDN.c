#include "fann.h"

int main(int argc, char *argv [])
{
	if (argc != 3)
	{
		printf ("Please enter the args\n./exec data output\n");
		return 0;
	}

    const unsigned int num_input = 256;
    const unsigned int num_output = 7;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 12;
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 500000;
    const unsigned int epochs_between_reports = 1000;

    struct fann *ann = fann_create_standard(num_layers, num_input,
        num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, argv [1], max_epochs,
        epochs_between_reports, desired_error);

    fann_save(ann, argv [2]);

    fann_destroy(ann);

    return 0;
}
