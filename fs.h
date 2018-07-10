#ifndef NDU_FS_H
#define NDU_FS_H

struct dir {
	char* name;

	int          dirlen;
	int          dircap;
	struct dir** dirs;

	int           filelen;
	int           filecap;
	struct file** files;

	off_t size;
};

struct file {
	struct dir* parent;
	char*       name;
	off_t       size;
};

struct dir* dir_create(const char* name);
void dir_add_dir(struct dir* to, struct dir* what);
void dir_add_file(struct dir* to, struct file* f);
void dir_sort_files(struct dir* d, bool deep);
void dir_print(const struct dir* d, int indent);
void dir_free(struct dir* d);

/*
 * yo
 */
struct file* file_create(struct dir* parent, const char* name);
int file_comp(const void* a, const void* b);
void file_free(struct file* f);

/*
 * Traverses a directory 'root' recursively, and fills the given directory 'd'
 * with files and directories.
 */
int traverse(const char* root, struct dir* d);

#endif // NDU_FS_H
