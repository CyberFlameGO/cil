#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string.h>

#include "../src/cil_lexer.h"
#include "../src/cil_tree.h"
#include "../src/cil.h"
#include "../src/cil_parser.h"

int main(int argc, char *argv[])
{
	struct stat filedata;
	struct cil_tree *tree;
	uint32_t file_size;
	char *buffer;
	FILE *file;

	if (argc > 1) {
		file = fopen(argv[1], "r");
		if (!file) {
			fprintf(stderr, "Could not open file\n");
			return SEPOL_ERR;
		}
		if (stat(argv[1], &filedata) == -1) {
			printf("Could not stat file\n");
			return SEPOL_ERR;
		}	
		file_size = filedata.st_size;
	
		buffer = malloc(file_size + 2);
		fread(buffer, file_size, 1, file);
		memset(buffer+file_size, 0, 2);
		fclose(file);

		cil_parser(buffer, file_size+2, &tree);
		cil_tree_print(tree->root, 0);
	}

	return SEPOL_OK;
}
