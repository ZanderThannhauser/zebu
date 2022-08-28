struct br_rettype { int dirfd, fd; };

struct br_rettype break_and_open_path(int old_dirfd, const unsigned char* path);
