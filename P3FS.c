#include"P3FS.h"
#define SECTOR_SIZE 512

int correctness(char *sector)
{
	if(sector[0] == 'A')
		return 1;
	else
		return 0;
}

int loadDir(char *sector)
{
	return sector[SECTOR_SIZE - 1];
}