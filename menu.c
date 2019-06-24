#include <stdio.h>
#include <conio.h>

int menu( char *t[])
{
	
   int k,i=1;
	 char ch;
	 
	 printf ("\n%s\n",t[0]);
	 while (t[i])
	 {
		 printf("\n<%d> - %s", i, t[i]);
		 i++;
	 }
	 printf ("\n\nИзберете опция 1-6:");
	 do
	 {
 
	  ch=_getch();
		k=ch-'0';
	 } while(k<=0 || k >i);
	printf("%c\n",ch);
	fflush(stdin);
 return ch-'0';
}



