#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

int main(int argc, char* argv[]) {
	struct dirlist* a = dirlist_create();

	for (int i = 0; i < 500; i++) {
		struct dir* d = malloc(sizeof(struct dir));
		d->dirname = malloc(30 * sizeof(char));
		snprintf(d->dirname, 30, "dir %d", i);
		// printf("Adding dir %d\n", i);
		dirlist_add(a, d);
	}

	printf("cap: %d, len: %d\n", a->cap, a->len);

	for(int i = 0; i < a->len; i++) {
		// printf("%s\n", a->arr[i]->dirname);
	}

	dirlist_free(a);
}
