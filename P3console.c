#include"P3console.h"
#include"LibDisk.h"



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
	
	char command[64];
	char subcommand[16];
	char object1[16];
	char object2[16];
	int commandNumber = 16;
	int quitv = 0;
	while(quitv == 0)
	{
		quitv = quit(command);
		commandNumber = extract_command(subcommand, command, object1, object2);
		switch(commandNumber)
		{
			case 0:			//ls
			
				printf("\n%s >>> ", path);
				break;
			case 1:			//cd
			
				printf("\n%s >>> ", path);
				break;
			case 2:			//mkdir
				
				break;
			case 3:			//rmdir
		
				printf("\n%s >>> ", path);
				break;
			case 4:			//mv
			
				printf("\n%s >>> ", path);
				break;
			case 5:			//cp
			
				printf("\n%s >>> ", path);
				break;
			case 6:			//rm
			
				printf("\n%s >>> ", path);
				break;
			case 7:			//open
			
				printf("\n%s >>> ", path);
				break;
			
		}
		commandNumber = 16;
	}
	
	printf("\n");
	return 0;
}


int quit(char command[64])
{
	return (command[0] == 'q' && command[1] == 'u' && command[2] == 'i' && command[3] == 't') ? 1 : 0;
}


int extract_command(char subcommand[16], char command[64], char object1[16], char object2[16])
{
	int i = 0;
	int d = 0;
	int dwa = 0;
	int commandNumber;
	while(command[i<=63 ? i : 63] == ' ')
		i++;
	
	if(i == 64)
		return 16;
	
	if(command[i] == 'l' && command[i+1 <= 63 ? i+1 : 63 ] == 's' && command[i+2 <= 63 ? i + 2 : 63] == ' ')
	{commandNumber = 0; strcpy(subcommand, "ls"); d = i+3;}

	if(command[i] == 'c' && command[i+1 <= 63 ? i+1 : 63 ] == 'd' && command[i+2 <= 63 ? i + 2 : 63] == ' ')
	{commandNumber = 1; strcpy(subcommand, "cd"); d = i+ 3;}

	if(command[i] == 'm' && command[i+1 <= 63 ? i+1 : 63 ] == 'k' && command[i+2 <= 63 ? i + 2 : 63] == 'd' && command[i+3 <= 63 ? i+3 : 63 ] == 'i' && command[i+4 <= 63 ? i+4 : 63 ] == 'r' && command[i+5 <= 63 ? i + 5 : 63] == ' ')
	{commandNumber = 2; strcpy(subcommand, "mkdir"); d = i+6;}

	if(command[i] == 'r' && command[i+1 <= 63 ? i+1 : 63 ] == 'm' && command[i+2 <= 63 ? i + 2 : 63] == 'd' && command[i+3 <= 63 ? i+3 : 63 ] == 'i' && command[i+4 <= 63 ? i+4 : 63 ] == 'r' && command[i+5 <= 63 ? i + 5 : 63] == ' ')
	{commandNumber = 3; strcpy(subcommand, "rmdir"); d = i+6;}

	if(command[i] == 'm' && command[i+1 <= 63 ? i+1 : 63 ] == 'v' && command[i+2 <= 63 ? i + 2 : 63] == ' ')
	{commandNumber = 4; strcpy(subcommand, "mv"); d = i+3; dwa = 1;}

	if(command[i] == 'c' && command[i+1 <= 63 ? i+1 : 63 ] == 'p' && command[i+2 <= 63 ? i + 2 : 63] == ' ')
	{commandNumber = 5; strcpy(subcommand, "cp"); d = i+3; dwa = 1;}

	if(command[i] == 'r' && command[i+1 <= 63 ? i+1 : 63 ] == 'm' && command[i+2 <= 63 ? i + 2 : 63] == ' ')
	{commandNumber = 6; strcpy(subcommand, "rm"); d = i+3;}

	if(command[i] == 'o' && command[i+1 <= 63 ? i+1 : 63 ] == 'p' && command[i+2 <= 63 ? i + 2 : 63] == 'e' && command[i+3 <= 63 ? i+3 : 63 ] == 'n' && command[i+4 <= 63 ? i+4 : 63 ] == ' ')
	{commandNumber = 7; strcpy(subcommand, "open"); d = i+5;}
	 	
	while(command[d<=63 ? d : 63] == ' ')
		d++;
	if(i == 64)
		return 16;

	int y;
	for(y = d; y < 64 && command[y] != ' '; y++)
		object1[y-d] = command[y];
	
	if(dwa == 1)
		for(d = (y++);y < 64 && command[y] != ' '; y++)
			object2[y - d] = command[y];
			
	return commandNumber;
		
		
}