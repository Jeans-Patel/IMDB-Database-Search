/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readUserInput(struct name_tree * n_nconst, struct name_tree * n_primaryName, struct title_tree * t_tconst, struct title_tree * t_primaryTitle, struct principal_tree * p_nconst, struct principal_tree * p_tconst);
void searchName_primary(struct name_tree * n_primaryName, char * check, char ** actors, int * numActors);
char * searchName_nconst(struct name_tree * n_nconst, char * check);
char * searchTitle_primary(struct title_tree * t_primaryTitle, char * check);
char * searchTitle_tconst(struct title_tree * t_tconst, char * check);
void searchPrincipal_nconst(struct principal_tree * p_nconst, char * check, char ** characters, char ** list_tconst, int * found);
void searchPrincipal_tconst(struct principal_tree * p_tconst, char * check, char ** characters, char ** list_nconst, int * found);