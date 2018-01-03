#include<string.h>

typedef struct directory{
	char* files[];
	int sectors[];     //i-th file first sector is i-th sector
	
} Directory;