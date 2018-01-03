#include"P3console.h"
#include"LibDisk.h"
#include"p3FS.h"

int main(int argc, char *argv[])
{
	if(argc == 1)
	{	
		
		char answer;
		char* answerString[16];
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
			Disk_Init();
			Disk_Save(answerString);
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
		Disk_Load(argv[1]);
	}
	
	
	
	return 0;
}