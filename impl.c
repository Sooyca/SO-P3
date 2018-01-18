#include"impl.h"

int chars_to_int(char* c)
{
	int wynik = 0;
	wynik |= c[0];
	wynik = (wynik << 8); 
	wynik |= c[1];
	return wynik;
}

void int_to_chars(int n, char* c)
{
	c[0] = (char) 0;
	c[1] |= n;
	n = (n >> 8);
	c[0] |= n;
}