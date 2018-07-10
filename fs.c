#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fs.h"

struct dir* dir_load_tree(const char* root) {
	struct dir* tree = dir_create("Root");
	traverse(root, tree);
	return tree;
}

struct dir* dir_create(const char* name) {
	struct dir* n = malloc(sizeof(struct dir));
	n->name = strdup(name);
	n->dirlen = 0;
	n->dircap = 1;
	n->dirs = malloc(sizeof(struct dir));

	n->filelen = 0;
	n->filecap = 1;
	n->files = malloc(sizeof(struct file));

	n->size = 0;
	return n;
}

void dir_add_dir(struct dir* to, struct dir* what) {
	to->dirs[to->dirlen++] = what;

	if (to->dirlen >= to->dircap) {
		to->dircap *= 2;
		to->dirs = realloc(to->dirs, to->dircap * sizeof(struct dir));
	}
}

void dir_add_file(struct dir* to, struct file* f) {
	to->files[to->filelen++] = f;

	if (to->filelen >= to->filecap) {
		to->filecap *= 2;
		to->files = realloc(to->files, to->filecap * sizeof(struct file));
	}

}

void dir_sort_files(struct dir* d, bool deep) {
	qsort(d->files, d->filelen, sizeof(struct file*), file_comp);
	if (deep) {
		// if a 'deep sort' is requested, traverse through the whole
		// chain of subdirectories.
		for (int i = 0; i < d->dirlen; i++) {
			dir_sort_files(d->dirs[i], true);
		}
	}
}

void dir_print(const struct dir* d, int indent) {
	int spaces = indent * 4;
	for (int i = 0; i < d->dirlen; i++) {
		struct dir* subdir = d->dirs[i];
		printf("%*s%s (%li)\n", spaces, "", subdir->name, subdir->size);
		dir_print(subdir, indent + 1);
	}

	for (int i = 0; i < d->filelen; i++) {
		struct file* f = d->files[i];
		printf("%*s%s (%li)\n", spaces, "", f->name, f->size);
	}

}

// TODO: this free function frees recursively. This will probably explode
// with large file structures.
void dir_free(struct dir* d) {
	free(d->name);
	for (int i = 0; i < d->dirlen; i++) {
		//printf("freeing dir %s\n", d->dirs[i]->name);
		dir_free(d->dirs[i]);
	}
	for (int i = 0; i < d->filelen; i++) {
		//d
		//printf("freeing file %s\n", d->files[i]->name);
		file_free(d->files[i]);
	}
	free(d->dirs);
	free(d->files);
	free(d);
}


struct file* file_create(const char* name) {
	struct file* f = malloc(sizeof(struct file));
	f->name = strdup(name);
	return f;
}


static int file_comp(const void* a, const void* b) {
	// The voids are disguised as a pointer to a pointer, since the
	// 'files' struct field is an array.
	const struct file* aa = *(struct file**) a;
	const struct file* bb = *(struct file**) b;

	return bb->size - aa->size;
}

void file_free(struct file* f) {
	free(f->name);
	free(f);
}

static int traverse(const char* dir, struct dir* root) {
	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) {
		return 1;
	}
	chdir(dir);
	while ((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf);
		if (S_ISDIR(statbuf.st_mode)) {
			// Found a directory, but ignore . and ..
			if(strcmp(".", entry->d_name) == 0 || strcmp("..",entry->d_name) == 0) {
				continue;
			}

			struct dir* bleh = dir_create(entry->d_name);
			dir_add_dir(root, bleh);

			//printf("%*s%s/\n", spaces, "", entry->d_name);
			// Recurse.
			traverse(entry->d_name, bleh);
		}

		if (S_ISREG(statbuf.st_mode)) {
			//printf("%*s%s (size = %li)\n", spaces, "", entry->d_name, statbuf.st_size);
			struct file* f = file_create(entry->d_name);
			f->size = statbuf.st_size;
			dir_add_file(root, f);
		}
	}
	chdir("..");
	closedir(dp);
	return 0;

}
