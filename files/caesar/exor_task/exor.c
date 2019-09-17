#define MAX_TITKOS 4096
#define OLVASAS_BUFFER 256
#define KULCS_MERET 8
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void
exor (const char kulcs[], int kulcs_meret, char titkos[], int titkos_meret)
{

  for (int i = 0; i < titkos_meret; ++i)
    {

      titkos[i] ^= kulcs[i%kulcs_meret];

    }

}

char *
szo_xor(char * szo,const char kulcs[],int index)
{
    int len=strlen(szo);
    
    for(int i=0;i<len;i++)
    {
      szo[i]^=kulcs[index%KULCS_MERET];
      index++;
    }
    return szo;
}

int
main (void)
{

  char kulcs[KULCS_MERET];
  char titkos[MAX_TITKOS];
  char *p = titkos;
  int olvasott_bajtok;
  char w[20];
  
  
  // titkos fajt berantasa
  while ((olvasott_bajtok = read (0, (void *) p, (p - titkos + OLVASAS_BUFFER < MAX_TITKOS) ? OLVASAS_BUFFER : titkos + MAX_TITKOS - p)))
    p += olvasott_bajtok;

  // maradek hely nullazasa a titkos bufferben  
  for (int i = 0; i < MAX_TITKOS - (p - titkos); ++i)
    titkos[p - titkos + i] = '\0';
  
  //printf("hossz:%d\n",strlen(titkos));

  // osszes kulcs eloallitasa
  for (int ii = '0'; ii <= '9'; ++ii)
    for (int ji = '0'; ji <= '9'; ++ji)
      for (int ki = '0'; ki <= '9'; ++ki)
	for (int li = '0'; li <= '9'; ++li)
	  for (int mi = '0'; mi <= '9'; ++mi)
	    for (int ni = '0'; ni <= '9'; ++ni)
	      for (int oi = '0'; oi <= '9'; ++oi)
		for (int pi = '0'; pi <= '9'; ++pi)
		  {
		    kulcs[0] = ii;
		    kulcs[1] = ji;
		    kulcs[2] = ki;
		    kulcs[3] = li;
		    kulcs[4] = mi;
		    kulcs[5] = ni;
		    kulcs[6] = oi;
		    kulcs[7] = pi;

		    
		    
		    for(int jj=0;jj<KULCS_MERET;jj++)
		    {
		      
		      strcpy(w,"és ");
		     if(memmem(titkos,p-titkos,szo_xor(w,kulcs,jj),strlen(w)))		//talalt =1, vagy nem=0
		      {
			  for(int kk=0;kk<KULCS_MERET;kk++)
			  {
			      strcpy(w,"amelyik ");
			      
			      if(memmem(titkos,p-titkos,szo_xor(w,kulcs,kk),strlen(w)))//talalt =1, vagy nem=0
			      {
				
				  for(int ll=0;ll<KULCS_MERET;ll++)
				  {
					strcpy(w," olyan ");
					
					if(memmem(titkos,p-titkos,szo_xor(w,kulcs,ll),strlen(w)))//talalt =1, vagy nem=0
					{//printf("%s\n",w);
					    for(int mm=0;mm<KULCS_MERET;mm++)
					    {
						  strcpy(w,"ezért ");
						  if(memmem(titkos,p-titkos,szo_xor(w,kulcs,mm),strlen(w)))	//talalt =1, vagy nem=0
						  {
						    exor(kulcs, KULCS_MERET, titkos, p - titkos);
						    printf("Kulcs: [%c%c%c%c%c%c%c%c]\nTiszta szoveg: [%s]\n",
							ii, ji, ki, li, mi, ni, oi, pi,	titkos);
						       // ujra EXOR-ozunk, igy nem kell egy masodik buffer  
						    exor(kulcs, KULCS_MERET, titkos, p - titkos);
						  }
					    }
					}
				  }
			      }
			  }
		      }
		    }
		    
		      
		    
		 
		    
		    }    

  return 0;
}
