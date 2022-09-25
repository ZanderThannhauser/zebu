
#include <fcntl.h>
#include <limits.h>
#include <string.h>

#include <debug.h>

#include "sopenat.h"
#include "break_and_open_path.h"

struct br_rettype break_and_open_path(int old_dirfd, const char* path)
{
	int dirfd, fd;
	ENTER;
	
	dpvs(path);
	
	char* slash = rindex(path, '/');
	
	if (slash)
	{
		char path_rw[PATH_MAX];
		
		strcpy(path_rw, path);
		
		path_rw[slash - path] = '\0';
		
		dpvs(path_rw);
		
		dirfd = sopenat(old_dirfd, path_rw, O_PATH);
		
		char* filename = slash + 1;
		
		dpvs(filename);
		
		fd = sopenat(dirfd, filename, O_RDONLY);
	}
	else
	{
		dirfd = old_dirfd, fd = sopenat(old_dirfd, path, O_RDONLY);
	}
	
	dpv(dirfd);
	dpv(fd);
	
	EXIT;
	return (struct br_rettype) {dirfd, fd};
}

