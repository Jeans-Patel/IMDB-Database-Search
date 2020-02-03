/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct title_basics {
	char *tconst;
	char *primaryTitle;
};

struct title_tree {
	char *data;
	struct title_basics *titles;
	struct title_tree *left;
	struct title_tree *right;
};

struct title_basics * readTitles(FILE * fp, unsigned long * size);
int cmp_t_tconst(const void * a, const void * b);
int cmp_t_primaryTitle(const void * a, const void * b);
struct title_tree * make_t_tree(struct title_basics * data, int min, int max, int type);
void freeTitles(struct title_basics * titles, int size);