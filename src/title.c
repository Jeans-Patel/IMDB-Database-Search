/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "title.h"

struct title_basics * readTitles(FILE * fp, unsigned long *size) {
	unsigned long i = 0;
	char tempColumn[1000];
	char tempString[1000];
	char *copyString;
	char *checkString;
	struct title_basics * titles;

	fseek(fp, 0, SEEK_SET);

	fgets(tempColumn, 1000, fp);
	while(fgets(tempColumn, 1000, fp)) {
		strcpy(tempString, tempColumn);
		checkString = strtok(tempString, "\t\n");
		checkString = strtok(NULL, "\t\n");

		if (strcmp("movie", checkString) == 0 || strcmp("Movie", checkString) == 0)
		{
			checkString = strtok(NULL, "\t\n");
			checkString = strtok(NULL, "\t\n");
			checkString = strtok(NULL, "\t\n");
			if (strcmp("0", checkString) == 0)
			{
				(*size)++;
			}
		}
	}

	fseek(fp, 0, SEEK_SET);

	titles = malloc(sizeof(struct title_basics) * (*size));

	fgets(tempColumn, 1000, fp);

	while(fgets(tempColumn, 1000, fp)) {
		strcpy(tempString, tempColumn);
		checkString = strtok(tempString, "\t\n");
		checkString = strtok(NULL, "\t\n");

		if (strcmp("movie", checkString) == 0 || strcmp("Movie", checkString) == 0)
		{
		checkString = strtok(NULL, "\t\n");
		checkString = strtok(NULL, "\t\n");
		checkString = strtok(NULL, "\t\n");
			if (strcmp("0", checkString) == 0)
			{
				copyString = strtok(tempColumn, "\t\n");
				titles[i].tconst = malloc(strlen(copyString)+1);
				strcpy(titles[i].tconst, copyString);

				copyString = strtok(NULL, "\t\n");
				copyString = strtok(NULL, "\t\n");
				titles[i].primaryTitle = malloc(strlen(copyString) + 1);
				strcpy(titles[i].primaryTitle, copyString);
				i++;
			}
		}
	}

	return titles;
}

int cmp_t_tconst(const void * a, const void * b) {
	struct title_basics * x = (struct title_basics *)a;
	struct title_basics * y = (struct title_basics *)b;
	return strcmp(x->tconst, y->tconst);
}

int cmp_t_primaryTitle(const void * a, const void * b) {
	struct title_basics * x = (struct title_basics *)a;
	struct title_basics * y = (struct title_basics *)b;
	return strcmp(x->primaryTitle, y->primaryTitle);
}

struct title_tree * make_t_tree(struct title_basics * data, int min, int max, int type) {
	int mid;
	struct title_tree * node;
	if (min > max)
	{
		return NULL;
	}

	mid = (min+max)/2;

	node = malloc(sizeof(struct title_tree));
	if (type == 2)
	{
		node->data = data[mid].tconst;
		node->titles = &data[mid];
	} else {
		node->data = data[mid].primaryTitle;
		node->titles = &data[mid];
	}

	node->left = make_t_tree(data, min, mid-1, type);
	node->right = make_t_tree(data, mid+1, max, type);

	return node;
}


void freeTitles(struct title_basics * titles, int size) {
	int i = 0;
	for (i = 0; i < size; ++i)
	{
		free(titles[i].tconst);
		free(titles[i].primaryTitle);
	}
	free(titles);
}