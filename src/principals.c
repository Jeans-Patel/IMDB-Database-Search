/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "principals.h"

struct title_principals * readPrincipals(FILE * fp, unsigned long *size) {
	int i = 0;
	char tempColumn[1000];
	char tempString[1000];
	char *copyString;
	char *checkString;
	struct title_principals * principals;

	fseek(fp, 0, SEEK_SET);

	fgets(tempColumn, 500, fp);
	while(fgets(tempColumn, 1000, fp)) {
		strcpy(tempString, tempColumn);
		checkString = strtok(tempString, "\t");
		checkString = strtok(NULL, "\t");
		checkString = strtok(NULL, "\t");
		checkString = strtok(NULL, "\t");

		if (strcmp("actor", checkString) == 0 || strcmp("actress", checkString) == 0)
		{
			(*size)++;
		}
	}

	fseek(fp, 0, SEEK_SET);

	principals = malloc(sizeof(struct title_principals) * (*size));

	fgets(tempColumn, 1000, fp);

	while(fgets(tempColumn, 1000, fp)) {
		strcpy(tempString, tempColumn);
		checkString = strtok(tempString, "\t");
		checkString = strtok(NULL, "\t");
		checkString = strtok(NULL, "\t");
		checkString = strtok(NULL, "\t");

		if (strcmp("actor", checkString) == 0 || strcmp("actress", checkString) == 0)
		{
			copyString = strtok(tempColumn, "\t");
			principals[i].tconst = malloc(strlen(copyString)+1);
			strcpy(principals[i].tconst, copyString);

			copyString = strtok(NULL, "\t");
			copyString = strtok(NULL, "\t");
			principals[i].nconst = malloc(strlen(copyString) + 1);
			strcpy(principals[i].nconst, copyString);

			copyString = strtok(NULL, "\t");
			copyString = strtok(NULL, "\t");
			copyString = strtok(NULL, "\t");
			principals[i].characters = malloc(strlen(copyString) + 1);
			strcpy(principals[i].characters, copyString);
			i++;
		}
	}

	return principals;
}

int cmp_p_nconst(const void * a, const void * b) {
	struct title_principals * x = (struct title_principals *)a;
	struct title_principals * y = (struct title_principals *)b;
	return strcmp(x->nconst, y->nconst);
}

int cmp_p_tconst(const void * a, const void * b) {
	struct title_principals * x = (struct title_principals *)a;
	struct title_principals * y = (struct title_principals *)b;
	return strcmp(x->tconst, y->tconst);
}

struct principal_tree * make_p_tree(struct title_principals * data, int min, int max, int type) {
	int mid;
	struct principal_tree * node;
	if (min > max)
	{
		return NULL;
	}

	mid = (min+max)/2;

	node = malloc(sizeof(struct principal_tree));
	if (type == 4)
	{
		node->data = data[mid].nconst;
		node->principals = &data[mid];
	} else {
		node->data = data[mid].tconst;
		node->principals = &data[mid];
	}

	node->left = make_p_tree(data, min, mid-1, type);
	node->right = make_p_tree(data, mid+1, max, type);

	return node;
}

void freePrincipals(struct title_principals * principals, int size) {
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		free(principals[i].tconst);
		free(principals[i].nconst);
		free(principals[i].characters);
	}
	free(principals);
}