// usage : test testFile.txt network.net

#include "fann.h"

int maxIndex(fann_type *output, int size) {
  int i,indexMax=0;

  for(i=0;i<size;i++) {
    if (output[i] > output[indexMax])
      indexMax = i;
  }
  return indexMax;
}

int main(int argc , char **argv) {
  fann_type *calc_out;
  int i;
	
  if (argc != 4) {
    printf("usage : test evalParsed.txt network.net out.txt\n");
    return 0;
  }

	FILE *out = fopen (argv[3], "w+");

  struct fann_train_data *testData = fann_read_train_from_file(argv[1]);
  struct fann *ann = ann = fann_create_from_file(argv[2]);
  int output_size = fann_get_num_output(ann);
  int result;
  int fr=0, en=0, de=0, es=0, pt=0, it=0, tr=0, none=0;

  for(i=0;i<testData->num_data ;i++) {
    // calcul du résultat de la prédiction
    calc_out = fann_run(ann, testData->input[i]);
    // interprétation et affichage du résultat
	result = maxIndex(calc_out,output_size);

	if (result == 0)
	{
		fprintf (out, "fr\n");
		fr++;
	}
	else if (result == 1)
	{
		fprintf (out, "en\n");
		en++;
	}
	else if (result == 2)
	{
		fprintf (out, "de\n");
		de++;
	}
	else if (result == 3)
	{
		fprintf (out, "es\n");
		es++;
	}
	else if (result == 4)
	{
		fprintf (out, "pt\n");
		pt++;
	}
	else if (result == 5)
	{
		fprintf (out, "it\n");
		it++;
	}
	else if (result == 6)
	{
		fprintf (out, "tr\n");
		tr++;
	}
	else
	{
		fprintf (out, "no\n");
		none++;
	}
  }

  printf ("fr :%d\nen :%d\nde :%d\nes :%d\npt :%d\nit :%d\ntr :%d\nnone :%d\n", fr, en, de, es, pt, it, tr, none);
  fann_destroy(ann);
  fclose (out);

  return 0;
}
