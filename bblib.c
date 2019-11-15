#include <stdio.h>
#include <stdlib.h>
#include "bblib.h"

int fin_fichier = 0;

BFILE *bstart(FILE * fichier)
{
   BFILE * bb_access = malloc(sizeof(BFILE));
   bb_access->fichier = fichier;
   bb_access->bufferLecture = 0;
   bb_access->bufferEcriture = 0;
   bb_access->nbBitsBufferEcriture=0;
   bb_access->nbBitsBufferLecture=0;
   bb_access->tete=0;
   return bb_access;
}

int bstop(BFILE * bfichier)
{

   printf("Fermeture de l'accès bb, il y a %d bits a écrire ! \n",bfichier->nbBitsBufferEcriture);
   //On doit finir d'écrire dans le fichier
   if(bfichier->nbBitsBufferEcriture!=0)
   {
      fseek(bfichier->fichier,0,SEEK_END);
      fwrite(&(bfichier->bufferEcriture),1,1,bfichier->fichier);

      printf("Nouvel octet écrit ! \n");
   }
   free(bfichier);
   return 0;
}

char bitread(BFILE * fichier)
{

   char ret;
   int i;

   if(beof(fichier))
      return -1;

   printf("Lecture d'un bit buffer : %d bits encore présents\n",fichier->nbBitsBufferLecture);

   if(fichier->nbBitsBufferLecture==0)
   {
      rewind(fichier->fichier);
      fseek(fichier->fichier,fichier->tete,SEEK_SET);
      if(fgetc(fichier->fichier)==EOF)
      {
         fin_fichier=1;
         return -1;
      }
      fseek(fichier->fichier,-1,SEEK_CUR);
      fread(&(fichier->bufferLecture),1,1,fichier->fichier);
      fichier->nbBitsBufferLecture=8;
      fichier->tete++;
      printf("Nouvel octet lu : ");
      for(i=7;i>=0;i--)
      {
         printf("%d", fichier->bufferLecture>>i & 1);
      }
      printf("\n");
   }

   ret = fichier->bufferLecture>>(fichier->nbBitsBufferLecture-1) & 1;
   fichier->nbBitsBufferLecture--;

   return ret;
}

int bitwrite(BFILE * fichier, char bit)
{
   int i;

   printf("Ecriture d'un bit buffer (%d) : %d bits présents \n",bit,fichier->nbBitsBufferEcriture);

   if(bit==0) //C'est un zéro
   {
      //RIEN A FAIRE
   }
   else if(bit==1)
   {
      fichier->bufferEcriture |= (1<<(7-fichier->nbBitsBufferEcriture));
   }
   else
   {
      return -1;
   }

   printf("Etat du buffer d'écriture : ");
   for(i=7;i>=0;i--)
   {
      printf("%d", fichier->bufferEcriture>>i & 1);
   }
   printf("\n");

   fichier->nbBitsBufferEcriture++;

   if(fichier->nbBitsBufferEcriture==8)
   {
      printf("Nouvel octet écrit :");
      for(i=7;i>=0;i--)
      {
         printf("%d", fichier->bufferEcriture>>i & 1);
      }
      printf("\n");
      fseek(fichier->fichier,0,SEEK_END);
      fwrite(&(fichier->bufferEcriture),1,1,fichier->fichier);
      fichier->nbBitsBufferEcriture=0;
      fichier->bufferEcriture=0;
   }

   return 0;

}

int beof(BFILE * fichier)
{
   return fin_fichier;
}
