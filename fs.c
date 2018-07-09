#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

struct dir* dir_create(const char* name) {
	struct dir* n = malloc(sizeof(struct dir));
	n->name = strdup(name);
	n->dirlen = 0;
	n->dircap = 1;
	n->dirs = malloc(sizeof(struct dir));

	n->filelen = 0;
	n->filecap = 1;
	n->files = malloc(sizeof(struct file));
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

// TODO: this free function frees recursively. This will probably explode
// with large file structures.
void dir_free(struct dir* d) {
	free(d->name);
	for (int i = 0; i < d->dirlen; i++) {
		printf("freeing dir %s\n", d->dirs[i]->name);
		dir_free(d->dirs[i]);
	}
	for (int i = 0; i < d->filelen; i++) {
		printf("freeing file %s\n", d->files[i]->name);
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

void file_free(struct file* f) {
	free(f->name);
	free(f);
}
