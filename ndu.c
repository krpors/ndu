#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#include "fs.h"

static int callback(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
	printf("fpath: %s\n", fpath);
	return 0;
}

void printdir(const char *dir, int depth) {
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	int spaces = depth*4;

	if((dp = opendir(dir)) == NULL) {
		fprintf(stderr,"cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
		/* Found a directory, but ignore . and .. */
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) {
				continue;
			}

			printf("%*s%s/\n",spaces,"",entry->d_name);
			/* Recurse at a new indent level */
			printdir(entry->d_name,depth+1);
		}
		else {
			printf("%*s%s\n",spaces,"",entry->d_name);
		}
	}
	chdir("..");
	closedir(dp);
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

	printdir("/home/krpors/Development", 0);
}
