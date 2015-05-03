#include <stdio.h>

FILE* setmntent(const char* path, const char* mode) {
    return fopen(path, mode);
}

int endmntent(FILE* fp) {
    if (fp != NULL) {
        fclose(fp);
    }
    return 1;
}
