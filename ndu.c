#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "fs.h"

static int callback(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
	printf("fpath: %s\n", fpath);
	return 0;
}

int main(int argc, char* argv[]) {
	struct dir* root = dir_create("root");

	struct dir* home = dir_create("home");
	struct dir* var  = dir_create("var");

	dir_add_dir(root, home);
	dir_add_dir(root, var);

	struct dir* krpors = dir_create("krpors");
	dir_add_dir(home, krpors);

	struct file* f = file_create(".inputrc");
	dir_add_file(krpors, f);

	dir_free(root);

	int x = nftw("/home", callback, 20, 0);
}
