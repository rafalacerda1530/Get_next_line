#include "get_next_line.h"

int main(void)
{
  char  *line;
  int   fd1;

  fd1 = open("text.txt", O_RDONLY);

  get_next_line(fd1, &line);
  printf("%s\n", line);
  free(line);

  get_next_line(fd1, &line);
  printf("%s\n", line);
  free(line);

  get_next_line(fd1, &line);
  printf("%s\n", line);
  free(line);

  get_next_line(fd1, &line);
  printf("%s\n", line);
  free(line);

}