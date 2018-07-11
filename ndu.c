#include <errno.h>
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

void test2(const char* rootdir) {
	struct dir* root = dir_load_tree(rootdir);
	if (root == NULL) {
		fprintf(stderr, "%s: %s\n", rootdir, strerror(errno));
		exit(1);
	}

	dir_analyze_sizes(root);

	dir_sort_all(root, true);

	printf("%s (%li)\n", root->name, root->size);
	dir_print(root, 1);

	dir_free(root);
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "gimme one dir plx\n");
		exit(1);
	}

	test2(argv[1]);
}
