#ifndef PATHPARSER_H
#define PATHPARSER_H

struct path_root
{
    int drive_no;
    struct path_part *first;
};

struct path_part
{
    const char *part;
    struct path_part *next;
};


struct path_root* pathparser_parse(const char* path, const char* current_directory_path);
char *strpath_root(struct path_root *root);
#endif
