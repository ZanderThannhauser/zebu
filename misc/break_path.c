
#include <debug.h>

#include "sopenat.h"
#include "break_path.h"

struct br_rettype break_path(int old_dirfd, const char* path)
{
	int dirfd, fd;
	ENTER;
	
	dpvs(path);
	
	char* slash = rindex(path, '/');
	
	if (slash)
	{
		char* path_dup = sstrdup(path);
		
		path_dup[slash - path] = '\0';
		
		dpvs(path_dup);
		
		dirfd = sopenat(old_dirfd, path_dup, O_PATH);
		
		char* filename = slash + 1;
		
		dpvs(filename);
		
		fd = sopenat(dirfd, filename, O_RDONLY);
		
		free(path_dup);
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

