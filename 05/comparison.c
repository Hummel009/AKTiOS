#include <bits/types/FILE.h>
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int compareFile(FILE *fPtr1, FILE *fPtr2) {
	char ch1, ch2;
	do {
		ch1 = fgetc(fPtr1);
		ch2 = fgetc(fPtr2);
		if (ch1 != ch2) {
			return -1;
		}
	} while (ch1 != EOF && ch2 != EOF);
	if (ch1 == EOF && ch2 == EOF) {
		return 0;
	} else {
		return -1;
	}
}

int main(int argc, char *argv[]) {
	DIR *d;
	struct dirent *dir;
	struct stat info;

	char paths[255][255];
	char names[255][255];
	char abs_path[PATH_MAX];
	int n = 0;

	d = opendir(argv[1]);
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strcmp(dir->d_name, ".") != 0
					&& strcmp(dir->d_name, "..") != 0) {
				snprintf(abs_path, PATH_MAX, "%s/%s", argv[1], dir->d_name);
				stat(abs_path, &info);

				char *loc1 = argv[2];
				char *loc2 = argv[3];

				int i1 = strtol(loc1, &loc1, 10);
				int i2 = strtol(loc2, &loc2, 10);

				if (info.st_size > i1 && info.st_size < i2) {
					strcpy(names[n], dir->d_name);
					strcpy(paths[n], abs_path);
					n++;
				}

			}
		}
	}
	closedir(d);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				FILE *f1 = fopen(paths[i], "r");
				FILE *f2 = fopen(paths[j], "r");
				if (compareFile(f1, f2) == 0) {
					printf("%s = %s\n", names[i], names[j]);
				} else {
					printf("%s != %s\n", names[i], names[j]);
				}
				fclose(f1);
				fclose(f2);
			}
		}
	}
	return 0;
}
