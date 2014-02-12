char ** removeDouble (char ** tweetTable, int size) {
	
	int i, j;
	for (i =0; i < size; i++){
		for (j=i+1; j< size ;j++){
			if (strcmp(tweetTable[i],tweetTable[j]) ){
				tweetTable[j]=NULL;
			}
		}
	}
	return tweetTable;
}


char ** removeURL(char ** tweetTable, int size) {
	int i, j, length;
	char * pch, *pch2, *save;
	for (i =0; i < size; i++){
		if (tweetTable[i] != NULL){
			pch = strstr (tweetTable[i],"http://");
			pch2 = strchr (pch,' ');
			save=pch;
			while (pch != pch2 ){
				*pch=' ';
				pch++;
			
			}
		}
	}

	return tweetTable;
}
