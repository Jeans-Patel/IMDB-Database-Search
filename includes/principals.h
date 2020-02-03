/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct title_principals {
	char *tconst;
	char *nconst;
	char *characters;
};

struct principal_tree {
	char *data;
	struct title_principals *principals;
	struct principal_tree *left;
	struct principal_tree *right;
};

struct title_principals * readPrincipals(FILE * fp, unsigned long * size);
int cmp_p_nconst(const void * a, const void * b);
int cmp_p_tconst(const void * a, const void * b);
struct principal_tree * make_p_tree(struct title_principals * data, int min, int max, int type);
void freePrincipals(struct title_principals * principals, int size);