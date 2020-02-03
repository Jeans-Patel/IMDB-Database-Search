/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct name_basics {
	char *nconst;
	char *primaryName;
};

struct name_tree {
	char *data;
	struct name_basics *names;
	struct name_tree *left;
	struct name_tree *right;
};

struct name_basics * readNames(FILE * fp, unsigned long * size);
int cmp_n_nconst(const void * a, const void * b);
int cmp_n_primaryName(const void * a, const void * b);
struct name_tree * make_n_tree(struct name_basics * data, int min, int max, int type);
void freeNames(struct name_basics * names, int size);
