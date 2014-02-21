#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int total = 0;
bool rflag = 0;

bool is_dir(const char* path) {
	struct stat statbuf;

	stat(path, &statbuf);

	if(S_ISDIR(statbuf.st_mode))
		return 1;
	else
		return 0;
}

char *extension_of(char *filename) {
	char *dot = strrchr(filename, '.');
	if(!dot || dot == filename)
		return "";
	return dot + 1;
}

void count(char *ext, char *path, bool recursively) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(path)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if((strcmp(ent->d_name,"..") != 0) && (strcmp(ent->d_name,".") != 0)) {
				if(strcmp(extension_of(ent->d_name), ext) == 0)
					total++;

				if(rflag && ent->d_type == DT_DIR) {

					char fullpath[1024];

					strcpy(fullpath, path);
					strcat(fullpath, "/");
					strcat(fullpath, ent->d_name);

					count(ext, fullpath, recursively);
				}
			}
		}
		closedir(dir);
	}
}

int main(int argc, char *argv[]) {

	if (argc != 2 && argc != 3 && argc != 4) {
		printf("usage:\n\n\tcount [-r] [extension] [where]\n");
		return 1;
	}

	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "r")) != -1)
		switch (c) {
			case 'r':
				rflag = 1;
				break;
			case '?':
				printf("-%c is not a valid argument\n", optopt);
				return 1;
				break;
		}

	if (argc == 2 + rflag)
		count(argv[1 + rflag], ".", rflag);

	if (argc == 3 + rflag)
		count(argv[1 + rflag], argv[2 + rflag], rflag);

	printf("total: %i", total);
}