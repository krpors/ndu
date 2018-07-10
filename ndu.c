#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

#if 0
void test1() {
	struct dir* root = dir_create("root");

	struct file* file1 = file_create("one");
	file1->size = 20;

	struct file* file2 = file_create("two");
	file2->size = 40;

	struct file* file3 = file_create("three");
	file3->size = 10;

	dir_add_file(root, file1);
	dir_add_file(root, file2);
	dir_add_file(root, file3);

	dir_print(root, 0);
	dir_sort_files(root, true);
	dir_print(root, 0);

	dir_free(root);
}
#endif

void dir_lol(struct dir* d) {
	for (int i = 0; i < d->dirlen; i++) {
		dir_lol(d->dirs[i]);
		// add the size of the subdirectory to the parent.
		// This will make sure the sizes of all subdirectories
		// are added to the grand total of parents.
		d->size += d->dirs[i]->size;
	}

	for (int i = 0; i < d->filelen; i++) {
		d->size += d->files[i]->size;
	}
}

void test2() {
	struct dir* root = dir_load_tree("/home/krpors/Temp/exampledir");

	dir_sort_files(root, true);
	dir_lol(root);
	printf("Root is %s (%li)\n", root->name, root->size);
	dir_print(root, 1);

	dir_free(root);
}

int main(int argc, char* argv[]) {
	test2();
}
