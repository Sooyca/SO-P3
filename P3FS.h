#include<stdio.h>
#include<string.h>
#include"impl.h"

#define MAX_FILE_SIZE 30
#define SECTOR_SIZE 512

typedef struct directory{
	char name[16];
	char parentName[16];
	int parentSector;
	char files[256][16];
	char filesTypes[256];
	int sectors[256];     //i-th file first sector is i-th sector
	int numberOfFiles;
} Directory;

int correctness(char *sector);

int loadDir(char *sector);

void openDir(Directory* dir, char sector[MAX_FILE_SIZE][SECTOR_SIZE], int n);



