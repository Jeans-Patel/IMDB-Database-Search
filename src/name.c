/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "name.h"

struct name_basics * readNames(FILE * fp, unsigned long *size) {
	int i = 0;
	int check = 0;
	char tempColumn[1000];
	char tempString[1000];
	char *copyString;
	char *isActor;
	struct name_basics * names;

	fseek(fp, 0, SEEK_SET);

	while(fgets(tempColumn, 500, fp)) {
		isActor = strtok(tempColumn, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");

		isActor = strtok(isActor, ",");
		while (isActor != NULL) {
			if (strcmp("actor", isActor) == 0 || strcmp("actress", isActor) == 0)
			{
				if (check == 0)
				{
					(*size)++;
				}
				check = 1;
			}
			isActor = strtok(NULL, ",");
		}
		check = 0;
	}

	fseek(fp, 0, SEEK_SET);

	names = malloc(sizeof(struct name_basics) * (*size));

	fgets(tempColumn, 500, fp);

	while(fgets(tempColumn, 500, fp)) {
		strcpy(tempString, tempColumn);
		isActor = strtok(tempString, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(NULL, "\t");
		isActor = strtok(isActor, ",");
		while (isActor != NULL) {
			if (strcmp("actor", isActor) == 0 || strcmp("actress", isActor) == 0)
			{
				if (check == 0)
				{				
					copyString = strtok(tempColumn, "\t");
					names[i].nconst = malloc(strlen(copyString) + 1);
					strcpy(names[i].nconst, copyString);

					copyString = strtok(NULL, "\t");
					names[i].primaryName = malloc(strlen(copyString) + 1);
					strcpy(names[i].primaryName, copyString);
					i++;
				}
				check = 1;
			}
			isActor = strtok(NULL, ",");
		}
		check = 0;
	}

	return names;
}

int cmp_n_nconst(const void * a, const void * b) {
	struct name_basics * x = (struct name_basics *)a;
	struct name_basics * y = (struct name_basics *)b;
	return strcmp(x->nconst, y->nconst);
}

int cmp_n_primaryName(const void * a, const void * b) {
	struct name_basics * x = (struct name_basics *)a;
	struct name_basics * y = (struct name_basics *)b;
	return strcmp(x->primaryName, y->primaryName);
}

struct name_tree * make_n_tree(struct name_basics * data, int min, int max, int type) {
	int mid;
	struct name_tree * node;
	if (min > max)
	{
		return NULL;
	}

	mid = (min+max)/2;

	node = malloc(sizeof(struct name_tree));
	if (type == 0)
	{
		node->data = data[mid].nconst;
		node->names = &data[mid];
	} else {
		node->data = data[mid].primaryName;
		node->names = &data[mid];
	}

	node->left = make_n_tree(data, min, mid-1, type);
	node->right = make_n_tree(data, mid+1, max, type);

	return node;
}

void freeNames(struct name_basics * names, int size) {
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		free(names[i].nconst);
		free(names[i].primaryName);
	}
	free(names);
}