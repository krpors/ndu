#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

int main(int argc, char* argv[]) {
	struct dir* root = dir_create("/hom");

	traverse("/home/krpors/", root);

	dir_free(root);
}
