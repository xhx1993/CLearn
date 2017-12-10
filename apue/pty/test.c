#include <stdio.h> 
/*
union 
{ 
	int i; 
	char x[2]; 
}a; 

int main() 
{ 
	a.x[0] = 10; 
	a.x[1] = 1; 
	printf("%d",a.i); 
	return 0;
} 
*/

int
main()
{
	const int i = 7;
	char *ptr = &i;
	*ptr = 8;
	printf("%d\n", i);
	return 0;
}
