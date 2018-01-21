#include"impl.h"

int chars_to_int(unsigned char c[2])
{
	int wynik = 0;
	wynik += (int) c[0];
	wynik += ((int) c[1])*256;
	return wynik;
}

void int_to_chars(int n, unsigned char c[2])
{
	c[1] = (unsigned char) (n/256);
	c[0] = (unsigned char) (n%256);
}

int first_free()
{
	//printf("in first_free()\n");
	char sectorBuffer[SECTOR_SIZE];
	unsigned char PS[2];
	unsigned char PWS[1];
	unsigned char tt[2];
	int int_PS;
	int int_PWS;
	Disk_Read(0, sectorBuffer);
	PS[0] = sectorBuffer[13];
	PS[1] = sectorBuffer[14];
	int_PS = chars_to_int(PS);
	PWS[0] = sectorBuffer[15];
	PWS[1] = sectorBuffer[16];
	int_PWS = chars_to_int(PWS);
	Disk_Read(int_PS, sectorBuffer);
	//printf("    ??%d, %d\n", int_PS, int_PWS);
	tt[0] = sectorBuffer[int_PWS];
	tt[1] = sectorBuffer[int_PWS + 1];
	//printf("    %d\n", chars_to_int(tt));
	return chars_to_int(tt);	
} 

void use_first_free()
{
	char sectorBuffer[SECTOR_SIZE];
	unsigned char PS[2];
	unsigned char PWS[1];
	int int_PS;
	int int_PWS;
	Disk_Read(0, sectorBuffer);
	PS[0] = sectorBuffer[13];
	PS[1] = sectorBuffer[14];
	int_PS = chars_to_int(PS);
	PWS[0] = sectorBuffer[15];
	PWS[1] = sectorBuffer[16];
	int_PWS = chars_to_int(PWS);
	if(int_PWS < SECTOR_SIZE - 2)
		int_PWS += 2;
	else
	{
		int_PWS = 0; 
		if(int_PS < NUM_SECTORS/(SECTOR_SIZE/2)+1)
			int_PS++;
		else
			int_PWS = 1;
	}
	int_to_chars(int_PS, PS);
	sectorBuffer[13] = PS[0];
	sectorBuffer[14] = PS[1];
	Disk_Write(0, sectorBuffer);
	int_to_chars(int_PWS, PWS);
	sectorBuffer[15] = PWS[0];
	sectorBuffer[16] = PWS[1];
	Disk_Write(0, sectorBuffer);
	
	//printf("in use: \n     %d, %d, \n", int_PS, int_PWS);
	//printf("     %d\n", first_free());
}










