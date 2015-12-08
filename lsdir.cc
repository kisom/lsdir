#include <sys/types.h>
#include <sys/dir.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <list>
#include <iostream>

using namespace std;


static void
lsdir(const char *path)
{
	list<string>		 paths;
	list<string>::iterator	 it;
	DIR			*dirp = NULL;
	struct dirent		*ent = NULL;

	dirp = opendir(path);
	if (NULL == dirp) {
		perror("opendir");
		return;
	}

	while (NULL != (ent = readdir(dirp))) {
		if (DT_DIR != ent->d_type) {
			continue;
		}

		if (0 == strncmp(ent->d_name, "..", 3)) {
			continue;
		} else if (0 == strncmp(ent->d_name, ".", 2)) {
			continue;
		}

		paths.push_back(string(ent->d_name));
	}

	closedir(dirp);

	if (0 == paths.size()) {
		return;
	}

	paths.sort();
	cout << path << ":\n";
	for (it = paths.begin(); it != paths.end(); it++) {
		cout << "\t" << *it << endl;
	}
}



int
main(int argc, char *argv[])
{
	int	 i = 1;
	char	*path = NULL;

	if (argc == 1) {
		path = getcwd(NULL, 0);
		if (NULL == path) {
			cerr << "Couldn't find the current working directory.\n";
			exit(EXIT_FAILURE);
		}
		lsdir(path);
	} else {
		for (path = argv[i]; i < argc; i++) {
			lsdir(path);
		}
	}

	return 0;
}
