#include"P3console.h"
#include"LibDisk.h"
#include"P3FS.h"

#define MAX_FILE_SIZE 30

Directory currentDir;

int main(int argc, char *argv[])
{
	if(argc == 1)
	{	
		
		char answer;
		char* answerString[16];
		char* diskName[16];
		printf("No disk specified to load, do you want to create a new one?\n[Y/n]");
		while(answer != 'Y' && answer != 'n' && answer != 'q')
		{
			scanf(stdin, "%c", &answer);
			printf("\n");
		}
		if(answer == 'Y')
		{
			printf("\nEnter the name, it can't be longer than 16 characters\n");
			scanf(stdin, "%s", &answerString);
			strcpy(diskName, answerString);
			Disk_Init();
			Disk_Save(diskName);
			printf("\nDo you want to read that disk\n[Y/n]");
			while(answer != 'Y' && answer != 'n' && answer != 'q')
			{
				scanf(stdin, "%c", &answer);
				printf("\n");
			}
			if(answer != 'Y')
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
	
	char* buffer[MAX_FILE_SIZE];
	
	Disk_Read(0, buffer[0]);
	if(correctness(buffer[0]) != 1)
	{
		printf(stderr, "Unknown file system");
		Disk_Save(diskName);
		return 0;
	}
	
	Disk_Read(1, buffer[0]);
	
	int t;
	int i = 0;
	while((t = loadDir(buffer[i]) != 0)
	{	
		i++;
		Disk_Read(t, buffer[i]);
	}
	
	if(i > 30)
	{
		printf(stderr, "Fatal filesystem error");
		Disk_Save(diskName);
		return 0;
	}
	
	openDir(buffer
	
	
	return 0;
}