#ifndef NDU_FS_H
#define NDU_FS_H

struct file {
	char* name;
};

/*
 * Directory.
 */
struct dir {
	char* dirname;

	struct dirlist*  directories;
	struct filelist* files;
};


struct dir* dir_create();
void dir_free(struct dir* d);



struct filelist {
	struct file** arr;
	int cap;
	int len;
};

struct filelist* filelist_create();
void filelist_add(struct filelist* fl, struct file* f);
void filelist_free(struct filelist* fl);

struct dirlist {
	struct dir** arr;
	int cap;
	int len;
};

struct dirlist* dirlist_create();
void dirlist_add(struct dirlist* dl, struct dir* d);
void dirlist_free(struct dirlist* d);

#endif // NDU_FS_H
