#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstdlib>
using namespace std;
int main()
{
 char c;

 srand(time(0));

 while(scanf("%c", &c)!=EOF) {
  if ((c=='0')||(c=='1')) {
   if((rand()%100)==99) {
    if(c=='0')printf("1");
    if(c=='1')printf("0");
    continue;
   }
  }
  printf("%c", c);
 }

 return 0;
}
