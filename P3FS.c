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

void openDir(Directory* dir, char buffer[MAX_FILE_SIZE][SECTOR_SIZE], int n)
{
	int y;
	int i;
	int enum_files = 0;
	int enum_chars = 0;
	char t;
	char tt[2];
	if(buffer[0][16] == '*')
		(dir->filesTypes[0]) = D;
	if(buffer[0][16] == '/')
		(dir->filesTypes[0]) = f;
	for(i = 17; i<512; i++)					//first 16 chars are directory name
	{
		if((t = buffer[0][i]) != '&')
		{
			(dir->files)[enum_files][enum_chars] = t;
			enum_chars++;
		}
		else
		{	
			i++;
			tt[0] = (int) buffer[0][i];
			i++;
			tt[1] = (int) buffer[0][i];
			(dir->sectors)[enum_files] = chars_to_int(tt);
			enum_chars = 0;
			enum_files++;
			if(buffer[0][i] == '*')
				(dir->filesTypes[enum_files]) = D;
			if(buffer[0][i] == '/')
				(dir->filesTypes[enum_files]) = f;
		}
		
	}	
	for(y = 1; y<n; y++)
		for(i = 0; i<512; i++)
		{
			if((t = buffer[y][i]) != '&')
			{
				(dir->files)[enum_files][enum_chars] = t;
				enum_chars++;
			}
			else
			{
				i++;
				tt[0] = (int) buffer[y][i];
				i++;
				tt[1] = (int) buffer[y][i];
				(dir->sectors)[enum_files] = chars_to_int(tt);
				enum_chars = 0;
				enum_files++;
				if(buffer[y][i] == '*')
					(dir->filesTypes[enum_files]) = D;
				if(buffer[y][i] == '/')
					(dir->filesTypes[enum_files]) = f;
			}		
		}					
}

