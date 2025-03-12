#include "includes/so_long.h"    
#include <fcntl.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    ft_printf("Error\n ONLY ACCEPT one argument");
    return(1);
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    ft_printf("Error\n ERROR OPENING FILE");
    return (2);
  }
  init_map(fd);
  

}
