#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<errno.h>
#include<zlib.h>

int main(int argc, char *argv[]) {
    //Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 2) {
        fprintf(stderr, "Usage: ./program.sh <command> [<args>]\n");
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "init") == 0) {
        if (mkdir(".git", 0755) == -1 || // means read and execute access for everyone and also write access for the owner of the file
            mkdir(".git/objects", 0755) == -1 || // Where blobs, trees and commits were storage
            mkdir(".git/refs", 0755) == -1) { // Where are the references (branchs, tags)

            fprintf(stderr, "Failed to create directories %s\n", strerror(errno));
            return 1;
        }

        FILE *headFile = fopen(".git/HEAD", "w");
        if (headFile == NULL) {
            fprintf(stderr, "Failed to create .git/HEAD file: %s\n", strerror(errno));
            return 1;
        }
        fprintf(headFile, "ref: refs/heads/main\n");
        fclose(headFile);
    }
    else {
        fprintf(stderr, "Unknown command %s\n", command);
        return 0;
    }

    return 0;
}
