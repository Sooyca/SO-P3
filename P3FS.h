#include<stdio.h>
#include"impl.h"
#include<string.h>

#define MAX_FILE_SIZE 30
#define SECTOR_SIZE 512

typedef struct directory{
	char name[16];
	char files[256][16];
	int sectors[256];     //i-th file first sector is i-th sector
	
} Directory;

int correctness(char *sector);

int loadDir(char *sector);

void openDir(Directory* dir, char sector[MAX_FILE_SIZE][SECTOR_SIZE], int n);



