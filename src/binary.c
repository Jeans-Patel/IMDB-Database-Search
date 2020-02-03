/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

void * makeTree(void * data, int type, int size, int min, int max, int(*compar)(const void *, const void *)) {
	struct name_tree * n_tree;
	struct title_tree * t_tree;
	struct principal_tree * p_tree;

	qsort(data, max, size, compar);

	if (type == 0 || type == 1)
	{
		n_tree = make_n_tree((struct name_basics *)data, min, max-1, type);
		return n_tree;
	} else if (type == 2 || type == 3) {
		t_tree = make_t_tree((struct title_basics *)data, min, max-1, type);
		return t_tree;
	} else if (type == 4 || type == 5) {
		p_tree = make_p_tree((struct title_principals *)data, min, max-1, type);
		return p_tree;
	} 
	return NULL;
}