#include <stdio.h>
int main(void)
{
int i;
char input;
for(i=0;i<2;i++)
{
printf("pleast input a character:\n");
scanf("%c",&input);
switch(input){
case 'a':
printf("you input a.\n");
case 'b':
printf("you input b.\n");
default:
printf("what you input don't belong to the judgement of the program.\n");
}
}
return 0;
}
