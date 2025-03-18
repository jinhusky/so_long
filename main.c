#include "includes/so_long.h"    

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    ft_printf("Error\n ONLY ACCEPT one argument\n");
    return(1);
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
  {
    ft_printf("Error\n ERROR OPENING FILE\n");
    return (2);
  }
  int width = 0, height = 0;
  check_map_size(fd, &width, &height);
  char **map = parsing(width, height, fd);
  ft_printf("%s", map);
  

}
