#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bblib.h"

void error(void);

int main()
{
   char lecture[100];
   char bit;
   char lu;
   FILE * fichier = fopen("bbit.txt","a+");
   BFILE * bitabit = bstart(fichier);

   if (fscanf(stdin,"%99s",lecture)!=1)
      error();
   while (strcmp(lecture,"bye")!=0)
   {
      if (strcmp(lecture,"write")==0)
      {
         if (fscanf(stdin,"%99s",lecture)!=1)
            error();
         bit = atoi(lecture);
         bitwrite(bitabit,bit);
      }
      else if (strcmp(lecture,"read")==0)
      {
         lu = bitread(bitabit);
         if(lu==-1)
            printf("Erreur : Fin de fichier.\n");
         else
            printf("Bit lu : %d\n",lu);
      }

      if (fscanf(stdin,"%99s",lecture)!=1)
         error();
   }

   bstop(bitabit);
   fclose(fichier);
   return EXIT_SUCCESS;
}

void error(void)
{
   printf("input error\r\n");
   exit(0);
}
