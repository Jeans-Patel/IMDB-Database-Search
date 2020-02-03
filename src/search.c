/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "name.h"
#include "title.h"
#include "principals.h"
#include "search.h"

void readUserInput(struct name_tree * n_nconst, struct name_tree * n_primaryName, struct title_tree * t_tconst, struct title_tree * t_primaryTitle, struct principal_tree * p_nconst, struct principal_tree * p_tconst) {
	char input[1000];
	char *check;
	char *holder;
	char **characters;
	char **constvalues;
	char **actors;
	int i = 0;
	int instances = 0;
	int nameFlag = 0;
	int numActors = 0;

	actors = malloc(sizeof(char *) * 100);
	characters = malloc(sizeof(char *) * 500);
	constvalues = malloc(sizeof(char *) * 500);

	printf("> ");
	fgets(input, 1000, stdin);

	check = strtok(input, " ");

	while (check[0] == '\0')
	{
		check++;
	}

	if (strcmp(check, "name") == 0 || strcmp(check, "title") == 0)
	{
		if (strcmp(check, "name") == 0)
		{
			nameFlag = 1;
		}

		check = strtok(NULL, "\n");

		i = 0;

		while (check[0] == ' ')
		{
			check++;
		}

		i = strlen(check) - 1;
		while(check[i] == ' ') {
			check[i] = '\0';
			i--;
		}


		if (check == NULL)
		{
			printf("invalid input\n");
		}
		else if (nameFlag == 1)
		{
			searchName_primary(n_primaryName, check, actors, &numActors);
			for (i = 0; i < numActors; ++i)
			{
				searchPrincipal_nconst(p_nconst, actors[i], characters, constvalues, &instances);
			}
			for (i = 0; i < instances; ++i)
			{
				holder = searchTitle_tconst(t_tconst, constvalues[i]);
				if (holder != NULL)
				{
					printf("%s : %s", holder, characters[i]);
				}
			}
			if (i == 0)
			{
				printf("Does not exist in the database\n");
			}
		}
		else
		{
			holder = searchTitle_primary(t_primaryTitle, check);
			searchPrincipal_tconst(p_tconst, holder, characters, constvalues, &instances);
			for (i = 0; i < instances; ++i)
			{
				holder = searchName_nconst(n_nconst, constvalues[i]);
				if (holder != NULL)
				{
					printf("%s : %s", holder, characters[i]);
				}
			}
			if (i == 0)
			{
				printf("Does not exist in the database\n");
			}
		}
	}
	else {
		printf("invalid input\n");
	}

	free(characters);
	free(constvalues);
}

void searchName_primary(struct name_tree * n_primaryName, char * check, char ** actors, int * numActors) {
	if (n_primaryName != NULL)
	{
		if (strcmp(check, n_primaryName->data) == 0)
		{
			actors[*numActors] = (n_primaryName->names)->nconst;
			(*numActors)++;
			if (n_primaryName->right != NULL)
			{
				searchName_primary(n_primaryName->right, check, actors, numActors);
			}
			if (n_primaryName->left != NULL)
			{
				searchName_primary(n_primaryName->left, check, actors, numActors);
			}
			return;
		}
		else if (strcmp(check, n_primaryName->data) > 0)
		{
			searchName_primary(n_primaryName->right, check, actors, numActors);
			return;
		}
		else
		{
			searchName_primary(n_primaryName->left, check, actors, numActors);
			return;
		}
	}
	else {
		return;
	}
}

char * searchName_nconst(struct name_tree * n_nconst, char * check) {
	if (n_nconst != NULL)
	{
		if (strcmp(check, n_nconst->data) == 0)
		{
			return (n_nconst->names)->primaryName;
		}
		else if (strcmp(check, n_nconst->data) > 0)
		{
			return searchName_nconst(n_nconst->right, check);
		}
		else
		{
			return searchName_nconst(n_nconst->left, check);
		}
	}
	else {
		return NULL;
	}
}

char * searchTitle_primary(struct title_tree * t_primaryTitle, char * check) {
	if (t_primaryTitle != NULL)
		{
			if (strcmp(check, t_primaryTitle->data) == 0)
			{
				return (t_primaryTitle->titles)->tconst;
			}
			else if (strcmp(check, t_primaryTitle->data) > 0)
			{
				return searchTitle_primary(t_primaryTitle->right, check);
			}
			else
			{
				return searchTitle_primary(t_primaryTitle->left, check);
			}
		}
	else {
		return NULL;
	}
}

char * searchTitle_tconst(struct title_tree * t_tconst, char * check) {
	if (t_tconst != NULL)
		{
			if (strcmp(check, t_tconst->data) == 0)
			{
				return (t_tconst->titles)->primaryTitle;
			}
			else if (strcmp(check, t_tconst->data) > 0)
			{
				return searchTitle_tconst(t_tconst->right, check);
			}
			else
			{
				return searchTitle_tconst(t_tconst->left, check);
			}
		}
	else {
		return NULL;
	}
}

void searchPrincipal_nconst(struct principal_tree * p_nconst, char * check, char ** characters, char ** list_tconst, int * found) {
	if (p_nconst != NULL)
	{
		if (strcmp(check, p_nconst->data) == 0)
		{
			characters[*found] = (p_nconst->principals)->characters;
			list_tconst[*found] = (p_nconst->principals)->tconst;
			(*found)++;
			if (p_nconst->right != NULL)
			{
				searchPrincipal_nconst(p_nconst->right, check, characters, list_tconst, found);
			}
			if (p_nconst->left != NULL)
			{
				searchPrincipal_nconst(p_nconst->left, check, characters, list_tconst, found);
			}
			return;
		}
		else if (strcmp(check, p_nconst->data) > 0)
		{
			searchPrincipal_nconst(p_nconst->right, check, characters, list_tconst, found);
			return;
		}
		else
		{
			searchPrincipal_nconst(p_nconst->left, check, characters, list_tconst, found);
			return;
		}
	}
	else {
		return;
	}
}

void searchPrincipal_tconst(struct principal_tree * p_tconst, char * check, char ** characters, char ** list_nconst, int * found) {
	if (p_tconst != NULL)
	{
		if (strcmp(check, p_tconst->data) == 0)
		{
			characters[*found] = (p_tconst->principals)->characters;
			list_nconst[*found] = (p_tconst->principals)->nconst;
			(*found)++;
			if (p_tconst->right != NULL)
			{
				searchPrincipal_tconst(p_tconst->right, check, characters, list_nconst, found);
			}
			if (p_tconst->left != NULL)
			{
				searchPrincipal_tconst(p_tconst->left, check, characters, list_nconst, found);
			}
			return;
		}
		else if (strcmp(check, p_tconst->data) > 0)
		{
			searchPrincipal_tconst(p_tconst->right, check, characters, list_nconst, found);
			return;
		}
		else
		{
			searchPrincipal_tconst(p_tconst->left, check, characters, list_nconst, found);
			return;
		}
	}
	else {
		return;
	}
}