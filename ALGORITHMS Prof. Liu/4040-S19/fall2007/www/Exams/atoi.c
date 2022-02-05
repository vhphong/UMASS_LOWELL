#include <stdio.h>
#include <string.h>

main()
{
  char s[100];
  int i;
  int v;

  gets(s);
  v = 0;
  for (i=0; i<strlen(s); i++) {
    v = v*10+(s[i]-'0');
  }

  printf("%d\n", v);
}
