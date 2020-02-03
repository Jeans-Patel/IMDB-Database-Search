/*
* Name: Jeans Patel
* Student ID: 1053172
* E-mail: jeans@uoguelph.ca
*/
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"
#include "search.h"

int main(int argc, char const *argv[])
{
	unsigned long nameSize = 0;
	unsigned long waste = 0;
	unsigned long titleSize = 0;
	unsigned long principalSize = 0;
	struct name_basics * names1;
	struct name_basics * names2;
	struct title_basics * titles1;
	struct title_basics * titles2;
	struct title_principals * principals1;
	struct title_principals * principals2;
	struct name_tree * n_nconst;
	struct name_tree * n_primaryName;
	struct title_tree * t_tconst;
	struct title_tree * t_primaryTitle;
	struct principal_tree * p_nconst;
	struct principal_tree * p_tconst;
	FILE * nameFile;
	FILE * titleFile;
	FILE * principalFile;
	char temp[100];


	strcpy(temp, argv[1]);
	strcat(temp, "/name.basics.tsv");

	nameFile = fopen(temp, "r");
	names1 = readNames(nameFile, &nameSize);
	names2 = readNames(nameFile, &waste);
	fclose(nameFile);

	waste = 0;
	
	strcpy(temp, argv[1]);
	strcat(temp, "/title.basics.tsv");

	titleFile = fopen(temp, "r");
	titles1 = readTitles(titleFile, &titleSize);
	titles2 = readTitles(titleFile, &waste);
	fclose(titleFile);

	waste = 0;

	strcpy(temp, argv[1]);
	strcat(temp, "/title.principals.tsv");
	
	principalFile = fopen(temp, "r");
	principals1 = readPrincipals(principalFile, &principalSize);
	principals2 = readPrincipals(principalFile, &waste);
	fclose(principalFile);

	waste = 0;

	n_nconst = makeTree(names1, 0, sizeof(struct name_basics), 0, nameSize, cmp_n_nconst);
	n_primaryName = makeTree(names2, 1, sizeof(struct name_basics), 0, nameSize, cmp_n_primaryName);

	t_tconst = makeTree(titles1, 2, sizeof(struct title_basics), 0, titleSize, cmp_t_tconst);
	t_primaryTitle = makeTree(titles2, 3, sizeof(struct title_basics), 0, titleSize, cmp_t_primaryTitle);

	p_nconst = makeTree(principals1, 4, sizeof(struct title_principals), 0, principalSize, cmp_p_nconst);
	p_tconst = makeTree(principals2, 5, sizeof(struct title_principals), 0, principalSize, cmp_p_tconst);

	readUserInput(n_nconst, n_primaryName, t_tconst, t_primaryTitle, p_nconst, p_tconst);

	freeNames(names1, nameSize);
	freeNames(names2, nameSize);
	freeTitles(titles1, titleSize);
	freeTitles(titles2, titleSize);
	freePrincipals(principals1, principalSize);
	freePrincipals(principals2, principalSize);
	return 0;
}