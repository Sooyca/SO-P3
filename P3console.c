#include"P3console.h"
#include"LibDisk.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

Directory currentDir;

char path[256];

int main(int argc, char *argv[])
{
	//printf("abcd");
	//fflush(stdout);	
	char answer;
	char answerString[16];
	char diskName[16];
	char sectorBuffer[SECTOR_SIZE];
	int y;
	int i = 0;
	unsigned char tt[2];
	/*char pp[2];
	int_to_chars(1, tt);
	pp[0] = tt[0];
	pp[1] = tt[1];
	tt[0] = pp[0];
	tt[1] = pp[1];
	printf("%d", chars_to_int(tt));*/
	if(argc == 1)
	{	
		for(y = 0; y < SECTOR_SIZE; y++)
		{
			sectorBuffer[y] = (char) 0;
		}
		printf("No disk specified to load, do you want to create a new one? [Y/n]\n");
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
			int count_queue = NUM_SECTORS/(SECTOR_SIZE/2)+2;
			int where_end_S = 0;
			int where_end_inS = 0;
			int where_flag = 0;
			for(y=1;y<= NUM_SECTORS/(SECTOR_SIZE/2)+1;y++)			//on-disk queue initialization
			{
				for(i = 0; i<=SECTOR_SIZE-2; i +=2)
				{
					int_to_chars(count_queue, tt);
					sectorBuffer[i] = tt[0];
					sectorBuffer[i+1] = tt[1];
					//printf("COunt queue: %d, y: %d, i: %d, cq: %d\n", count_queue, y, i, chars_to_int(tt)); 
					if(count_queue < NUM_SECTORS)
						count_queue++;
					if(where_flag == 0 && count_queue == NUM_SECTORS)
					{
						where_end_S = y;
						where_end_inS = i+1;
						where_flag = 1;
					}
				}
				Disk_Write(y, sectorBuffer);
				
			}
			Disk_Read(0, sectorBuffer);
			int_to_chars(1, tt);
			sectorBuffer[13] = tt[0];
			sectorBuffer[14] = tt[1];
			//Disk_Write(0, sectorBuffer);
			//Disk_Read(0, sectorBuffer);
			/*tt[0] = sectorBuffer[13];
				tt[1] = sectorBuffer[14];
				printf("?%d: \n", chars_to_int(tt));
				
			printf("first free-1: %d \n", first_free());
			tt[0] = sectorBuffer[13];
			tt[1] = sectorBuffer[14];
			printf("uwaga:%d ", chars_to_int(tt));*/
			int_to_chars(0, tt);  
			sectorBuffer[15] = tt[0];
			sectorBuffer[16] = tt[1];
			//Disk_Write(0, sectorBuffer);
			//Disk_Read(0, sectorBuffer);
			int_to_chars(where_end_S, tt);
			sectorBuffer[17] = tt[0];
			sectorBuffer[18] = tt[1];
			//Disk_Write(0, sectorBuffer);
			//Disk_Read(0, sectorBuffer);
			int_to_chars(where_end_inS, tt);
			sectorBuffer[19] = tt[0];
			sectorBuffer[20] = tt[1];
			Disk_Write(0, sectorBuffer);
			Disk_Save(diskName);
			/*Disk_Read(0, sectorBuffer);
				tt[0] = sectorBuffer[13];
				tt[1] = sectorBuffer[14];
				printf("?%d: \n", chars_to_int(tt));
			printf("first free0: %d \n", first_free());*/
			printf("\nDo you want to read that disk? [Y/n]\n");
			while(answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n' && answer != 'q')
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
	//printf("debug");
	//fflush(stdout);	
	char buffer[MAX_FILE_SIZE][SECTOR_SIZE];
	char operationbuffer[SECTOR_SIZE];
	
	Disk_Read(0, operationbuffer);
	if(correctness(operationbuffer) != 1)
	{
		printf("Unknown file system");
		Disk_Save(diskName);
		return 0;
	}
	
	//for(y = 0; 
	//printf("%d", NUM_SECTORS/(SECTOR_SIZE/2)+2);
	//fflush(stdout);	
	Disk_Read(NUM_SECTORS/(SECTOR_SIZE/2)+2, buffer[0]);
	//printf("first free2: %d \n", first_free());
	int t;
	i = 0;
	while((t = loadDir(buffer[i])) != 0 && i < 30)
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
	//printf("c");
	//system("clear");
	openDir(&currentDir, buffer, i + 1);
	//printf("b");
	
	//printf("a");
	strcpy(path, "mount point");
	//strcat(path, "mount point");
	
	
	//fflush(stdout);	
	char command[64];
	char subcommand[16];
	char object1[16];
	char object2[16];
	int commandNumber = 16;
	int quitv = 0;
	int FN = 0;
	int vfirst_free;
	while(quitv == 0)
	{	
		printf("%s >>> ", path);
		for(y = 0; y<64; y++)
			command[y] = '0';
		scanf("%s %s %s", command, object1, object2);
		//printf("command: %s\n", command);
		//printf("%d", quit(command));
		//fflush(stdout);	
		quitv = quit(command);
	//	printf("command: %s\n", command);
		
		//printf("test %s \n", subcommand);
		commandNumber = extract_command(subcommand, command, object1, object2);
		
		/*printf("command: %s\n", command);
		printf("%s \n%s \n%s \n%s\n", command, subcommand, object1, object2);
		printf("%d", commandNumber);*/
		switch(commandNumber)
		{
			case 0:			//ls
				for(y = 0; y<currentDir.numberOfFiles; y++)
					printf("%s ", (currentDir.files)[y]);
				if(currentDir.numberOfFiles == 0)
					printf("(directory is empty)");
				printf("\n");
				break;
			case 1:			//cd
				
				break;
			case 2:			//mkdir
				FN = currentDir.numberOfFiles;
				vfirst_free = first_free();
				if(FN < 256 && vfirst_free < NUM_SECTORS)
				{
					strcpy(currentDir.files[FN], object1);
					currentDir.filesTypes[FN] = 'D';
					currentDir.sectors[FN] = vfirst_free;
					use_first_free();
					strcpy(operationbuffer, object1);
					Disk_Write(vfirst_free, operationbuffer); //name of new dir
					currentDir.numberOfFiles++;
					
				}
				if(FN >= 256)
					printf("To many files in this directory.\n");
				if(vfirst_free >= NUM_SECTORS)
					printf("Disk is full, cannot add a directory. %d\n", vfirst_free);
				//fflush(stdout);
				break;
			case 3:			//rmdir
				
				break;
			case 4:			//mv
				
				break;
			case 5:			//cp
				
				break;
			case 6:			//rm
				
				break;
			case 7:			//open
				
				break;
			case 16:
				printf("minor error\n");
				break;
			
		}
		commandNumber = 16;
	}
	
	printf("\n");
	Disk_Save(diskName);
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
	int zero = 0;
	int cokolwiek = 0;
	int commandNumber = 16;
	int com_len = strlen(command);
	/*while(command[i<=63 ? i : 63] == ' ')
		i++;
	
	if(i == 64)
		return 16;
	*/
	if(command[i] == 'l' && command[i+1 <= 63 ? i+1 : 63 ] == 's')
	{commandNumber = 0; strcpy(subcommand, "ls"); d = i+3; zero = 1; cokolwiek = 1;}

	if(command[i] == 'c' && command[i+1 <= 63 ? i+1 : 63 ] == 'd')
	{commandNumber = 1; strcpy(subcommand, "cd"); d = i+ 3; cokolwiek = 1;}

	if(command[i] == 'm' && command[i+1 <= 63 ? i+1 : 63 ] == 'k' && command[i+2 <= 63 ? i + 2 : 63] == 'd' && command[i+3 <= 63 ? i+3 : 63 ] == 'i' && command[i+4 <= 63 ? i+4 : 63 ] == 'r')
	{commandNumber = 2; strcpy(subcommand, "mkdir"); d = i+6; cokolwiek = 1;}
	
	if(command[i] == 'r' && command[i+1 <= 63 ? i+1 : 63 ] == 'm')
	{commandNumber = 6; strcpy(subcommand, "rm"); d = i+3; cokolwiek = 1;}
	
	if(command[i] == 'r' && command[i+1 <= 63 ? i+1 : 63 ] == 'm' && command[i+2 <= 63 ? i + 2 : 63] == 'd' && command[i+3 <= 63 ? i+3 : 63 ] == 'i' && command[i+4 <= 63 ? i+4 : 63 ] == 'r')
	{commandNumber = 3; strcpy(subcommand, "rmdir"); d = i+6; cokolwiek = 1;}

	if(command[i] == 'm' && command[i+1 <= 63 ? i+1 : 63 ] == 'v')
	{commandNumber = 4; strcpy(subcommand, "mv"); d = i+3; dwa = 1; cokolwiek = 1;}

	if(command[i] == 'c' && command[i+1 <= 63 ? i+1 : 63 ] == 'p')
	{commandNumber = 5; strcpy(subcommand, "cp"); d = i+3; dwa = 1; cokolwiek = 1;}

	if(command[i] == 'o' && command[i+1 <= 63 ? i+1 : 63 ] == 'p' && command[i+2 <= 63 ? i + 2 : 63] == 'e' && command[i+3 <= 63 ? i+3 : 63 ] == 'n')
	{commandNumber = 7; strcpy(subcommand, "open"); d = i+5; cokolwiek = 1;}
	 	/*
	while(command[d<=63 ? d : 63] == ' ' && )
		d++;
	if(i == 64)
		return 16;
*/
	if(cokolwiek == 1)
	{
		if(zero != 1)
		{
			int y;
			for(y = d; y < 64 && command[y] != ' ' && y< com_len; y++)
				object1[y-d] = command[y];	
			if(dwa == 1)
			{
				y++;
				d = y;
				for(;y < 64 && command[y] != ' ' &&y< com_len; y++)
					object2[y - d] = command[y];
			}
		}
	}	
	return commandNumber;
		
		
}