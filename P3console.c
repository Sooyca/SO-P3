#include"P3console.h"
#include"LibDisk.h"
#include"P3FS.h"



Directory currentDir;

char path[256];

int main(int argc, char *argv[])
{
	char answer;
	char answerString[16];
	char diskName[16];
	char sectorBuffer[SECTOR_SIZE];
	if(argc == 1)
	{	
		int y;
		for(y = 0; y < SECTOR_SIZE; y++)
		{
			sectorBuffer[y] = (char) 0;
		}
		printf("No disk specified to load, do you want to create a new one?\n[Y/n]\n");
		while(answer != 'Y' && answer != 'y' && answer != 'n' && answer != 'N' && answer != 'q')
		{
			scanf("%c", &answer);
		}
		if(answer == 'Y' || answer == 'y')
		{
			answer = '0';
			printf("\nEnter the name, it can't be longer than 16 characters.\n");
			scanf("%s", answerString);
			strcpy(diskName, answerString);
			Disk_Init();
			strcpy(sectorBuffer, "A mount point");
			Disk_Write(0, sectorBuffer);
			for(y = 0; y < SECTOR_SIZE; y++)
			{
				sectorBuffer[y] = (char) 0;
			}
			Disk_Save(diskName);
			printf("\nDo you want to read that disk?\n[Y/n]\n");
			while(answer != 'Y' && answer != 'n' && answer != 'q')
			{
				scanf("%c", &answer);
			}
			if(answer != 'Y' && answer != 'y')
				return 0;
		}
		else
			return 0;	
	}
	else
	{
		Disk_Init();
		strcpy(diskName, argv[1]);
		Disk_Load(diskName);
	}
	
	char buffer[MAX_FILE_SIZE][SECTOR_SIZE];
	
	Disk_Read(0, buffer[0]);
	if(correctness(buffer[0]) != 1)
	{
		printf("Unknown file system");
		Disk_Save(diskName);
		return 0;
	}
	
	Disk_Read(41, buffer[0]);
	
	int t;
	int i = 0;
	while((t = loadDir(buffer[i])) != 0)
	{	
		i++;
		Disk_Read(t, buffer[i]);
	}
	
	if(i >= 30)
	{
		printf("Fatal filesystem error");
		Disk_Save(diskName);
		return 0;
	}
	
	openDir(&currentDir, buffer, i + 1);
	
	system("clear");
	
	strcpy(path, "mount point");
	
	printf("%s >>> ", path);
	
	char command[32];
	char subcommand[16];
	char object[16];
	while(quit(command) == 0)
	{
		scanf("%s", command);
		extract_command(subcommand, command, object);
		switch(command)
		{
			case ls:
			, cd, mkdir, rmdir, mv, cp, rm:
		}
	}
	
	
	return 0;
}


int quit(char command[32])
{
	return ~strcmp("quit", command);
}


void extract_command(char subcommand[16], char command[32], char object[16])
{
	int i;
	int d;
	while(command[i<=31 ? i : 0] = ' ' && i<=31)
		i++;
	if(i == 32)
	{
		return;
	}
	else
	{
		 if(command[i] == 'l' && command[i+1 <= 31 ? i+1 : return ] == 's' && command[i+2 <= 31 ? i + 2 : return] == ' ')
		 	{strcpy(subcommand, "ls"); d = i+3}
		 
		 if(command[i] == 'c' && command[i+1 <= 31 ? i+1 : return ] == 'd' && command[i+2 <= 31 ? i + 2 : return] == ' ')
		 	{strcpy(subcommand, "cd");}
		 
		 if(command[i] == 'm' && command[i+1 <= 31 ? i+1 : return ] == 'k' && command[i+2 <= 31 ? i + 2 : return] == 'd' && command[i+3 <= 31 ? i+3 : return ] == 'i' && command[i+4 <= 31 ? i+4 : return ] == 'r' && command[i+5 <= 31 ? i + 5 : return] == ' ')
		 	{strcpy(subcommand, "mkdir");}
		 
		 if(command[i] == 'r' && command[i+1 <= 31 ? i+1 : return ] == 'm' && command[i+2 <= 31 ? i + 2 : return] == 'd' && command[i+3 <= 31 ? i+3 : return ] == 'i' && command[i+4 <= 31 ? i+4 : return ] == 'r' && command[i+5 <= 31 ? i + 5 : return] == ' ')
		 	{strcpy(subcommand, "rmdir");}
		 
		 if(command[i] == 'm' && command[i+1 <= 31 ? i+1 : return ] == 'v' && command[i+2 <= 31 ? i + 2 : return] == ' ')
		 	{strcpy(subcommand, "mv");}
		 
		 if(command[i] == 'c' && command[i+1 <= 31 ? i+1 : return ] == 'p' && command[i+2 <= 31 ? i + 2 : return] == ' ')
		 	{strcpy(subcommand, "cp");}
		 
		 if(command[i] == 'r' && command[i+1 <= 31 ? i+1 : return ] == 'm' && command[i+2 <= 31 ? i + 2 : return] == ' ')
		 	{strcpy(subcommand, "rm");}
		 
		 if(command[i] == 'r' && command[i+1 <= 31 ? i+1 : return ] == 'm' && command[i+2 <= 31 ? i + 2 : return] == 'd' && command[i+3 <= 31 ? i+3 : return ] == 'i' && command[i+4 <= 31 ? i+4 : return ] == 'r' && command[i+5 <= 31 ? i + 5 : return] == ' ')
		 	{strcpy(subcommand, "rmdir"); }
	}	
	while(command[i<=31 ? i : 0] = ' ' && i<=31)
		i++;
	if(i == 32)
	{
		return;
	}
	else
	{
		
	}
		
}