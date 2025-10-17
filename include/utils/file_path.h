#ifndef TERMINATED_BY_C_FILE_PATH_H
#define TERMINATED_BY_C_FILE_PATH_H

#include <stdlib.h>
#include <string.h>
#include <sec_api/stdio_s.h>

static const char* get_path_relative_to_exe(const char* exe_path, const char* asset_name) {
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    // on windows
    _splitpath_s(exe_path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

    // alloc mem for fullpath
    size_t path_len = strlen(drive) + strlen(dir) + strlen(asset_name) + 1;
    char* full_path = (char*)malloc(path_len);

    if (full_path) {
        sprintf_s(full_path, path_len, "%s%s%s", drive, dir, asset_name);
    }
    return full_path;
}

#endif //TERMINATED_BY_C_FILE_PATH_H