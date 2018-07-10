#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

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

void test2() {
	struct dir* root = dir_create("");

	traverse("/home/krpors/.config/", root);

	printf("\n\n\n");
	dir_sort_files(root, true);
	dir_print(root, 0);

	dir_free(root);
}

int main(int argc, char* argv[]) {
	test2();
}
