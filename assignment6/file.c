#include <stdio.h>
int main()
{
  int x, y;
  FILE *fp;
  fp = fopen("Assignment#6-io/input1.graph", "r+");
  for (int i = 0; i < 5; i++)
  {
    fscanf(fp, "%d %d\n", &x, &y);
    printf("%d %d\n", x, y);
  }
  return 0;
}