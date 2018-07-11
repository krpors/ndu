#ifndef NDU_FS_H
#define NDU_FS_H

/*
 * This struct contains information about a directory on the filesystem.
 */
struct dir {
	char* name; // the name of the directory

	struct dir** dirs;   // dynamic array of `dir'
	int          dirlen; // length of 'dirs'
	int          dircap; // capacity of 'dirs'

	struct file** files;   // dynamic array of `file'
	int           filelen; // length of `files'
	int           filecap; // capacity of `files'

	off_t size; // The accumulated size of ALL descendant files
	            // in the directory.
};

/*
 * File information.
 */
struct file {
	char* name; // file name
	off_t size; // size of the file.
};

/*
 * Main function to load up a tree. The `root' is the root directory to
 * initialize the tree from. A heap allocated `struct dir' is returned,
 * which must be freed with `dir_free'.
 */
struct dir* dir_load_tree(const char* root);
struct dir* dir_create(const char* name);
void dir_add_dir(struct dir* to, struct dir* what);
void dir_add_file(struct dir* to, struct file* f);
void dir_sort_dirs(struct dir* d, bool deep);
void dir_sort_files(struct dir* d, bool deep);

/*
 * This function prints out the directory `d' to the stdout. Useful for
 * debugging and seeing the structure's contents.
 */
void dir_print(const struct dir* d, int indent);

/**
 * Frees the `d' which was allocated using via `dir_create' directly or
 * `dir_load_tree'. This will recursively free all associated descendant
 * files and directories as well.
 */
void dir_free(struct dir* d);

/*
 * Creates a `file' on the heap and returns it.
 */
struct file* file_create(const char* name);

/*
 * Frees the file `f' previously allocated on the heap.
 */
void file_free(struct file* f);

#endif // NDU_FS_H
