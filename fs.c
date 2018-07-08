#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs.h"

struct filelist* filelist_create() {
	struct filelist* fl = malloc(sizeof(struct filelist));
	fl->cap = 1;
	fl->len = 0;
	fl->arr = malloc(sizeof(struct file));
	return fl;
}

void filelist_add(struct filelist* fl, struct file* f) {
	size_t s = sizeof(f);
	fl->arr[fl->len++] = f;

	if (fl->len >= fl->cap) {
		fl->cap *= 2;
		fl->arr = realloc(fl->arr, fl->cap * sizeof(struct file));
	}
}


void filelist_free(struct filelist* fl) {
	for (int i = 0; i < fl->len; i++) {
		free(fl->arr[i]->name);
		free(fl->arr[i]);
	}
	free(fl->arr);
	free(fl);
}

struct dir* dir_create() {
	struct dir* d = malloc(sizeof(struct dir));
	d->directories = dirlist_create();
	d->files = filelist_create();
	return d;
}

void dir_free(struct dir* d) {
	free(d->dirname);
	if (d->directories != NULL) {
		for (int i = 0; i < d->directories->len; i++) {
			dir_free(d->directories->arr[i]);
		}
	}
	free(d);
}

struct dirlist* dirlist_create() {
	struct dirlist* dl = malloc(sizeof(struct dirlist));
	dl->cap  = 1;
	dl->len = 0;
	dl->arr = malloc(sizeof(struct dir));
}

void dirlist_add(struct dirlist* dl, struct dir* d) {
	dl->arr[dl->len++] = d;

	if (dl->len >= dl->cap) {
		dl->cap *= 2;
		dl->arr = realloc(dl->arr, dl->cap * sizeof(struct dir));
	}
}

void dirlist_free(struct dirlist* d) {
	for (int i = 0; i < d->len; i++) {
		free(d->arr[i]->dirname);
		free(d->arr[i]);
	}
	free(d->arr);
	free(d);
}
