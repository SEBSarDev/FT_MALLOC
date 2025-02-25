#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	ft_itoa_base(size_t n, char *base_to)
{
	size_t	len_base;

	len_base = strlen(base_to);
	if (n >= len_base)
	{
		ft_itoa_base(n / len_base, base_to);
		n = n % len_base;
	}
	write(1, &base_to[n], 1);
}

int      main()
{
   int   i;
   char  *addr;
   char  *adr[1024];

  i = 0;
   while (i < 1024)
   {
      adr[i] = (char*)malloc(1024);
      adr[i][0] = 42;
     write(1, "i : ", 4);
      ft_itoa_base(i, "0123456789");
      write(1, "\n", 1);
      i++;
   }
   i = 0;
   while (i < 1024)
   {
      addr = (char*)malloc(1024);
      addr[0] = 42;
      free(addr);
      i++;
      write(1, "j : ", 4);
      ft_itoa_base(i, "0123456789");
      write(1, "\n", 1);
      
   }
   free(adr[130]);
     i = 0;
   while (i < 1024)
   {
      if (i == 130)
         i++;
          write(1, "k : ", 4);
      ft_itoa_base(i, "0123456789");
      write(1, "\n", 1);
 free(adr[i]);
      i++;
      
   }


   return (0);
}