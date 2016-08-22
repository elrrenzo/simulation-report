#include<stdio.h>
#include<string.h>

struct TiempoI{
	float tiempo;
	int index;
};

void insertion_sort(float array1[],struct TiempoI Tiempo[],int n)
{
	int i,j;
	struct TiempoI t;
	for(i=0;i<n;i++)
	{
		Tiempo[i].tiempo=array1[i];
		Tiempo[i].index=i;
	}
	for (i = 1 ; i <n; i++) 
	{
    	j = i;
    	while ( j > 0 && Tiempo[j].tiempo < Tiempo[j-1].tiempo) 
		{
      		t       = Tiempo[j];
      		Tiempo[j]= Tiempo[j-1];
      		Tiempo[j-1]= t;
      		j--;
    	}
  	}
}

int primera_linea(FILE *archivoDAT,int *flags, char nombres[][20],char palabra[])
{
	int ret,n,j;
	char letra;

	fscanf(archivoDAT,"%s",palabra);
	flags[0]=0;   //Sinal para tempo
	fscanf(archivoDAT,"%c",&letra);
	
	n=1;
	j=0;	
	while(letra !='\n')
	{
		do
		{
			fscanf(archivoDAT,"%c",&letra);
		}
		while(letra==' ' || letra=='\t');

		fscanf(archivoDAT,"%s",palabra);
		flags[n]=999;
		if(letra=='d')
		{
			flags[n]=1;
			sscanf(palabra,"%s",nombres[j]);
			//sprintf(&nombres[j],"%s",palabra);
			j++;
		}
		if(letra=='s')
			flags[n]=2;

	//	printf("%s\n",palabra);
		n++;
	}
	ret=n-1;
	return ret;
}

int main(int argc, char **argv)
{
	FILE *archivoDAT, *archivoDIG; //DAT to read by PGFPLOTS and GNUPLOT (NOT by TPBIG) //
	archivoDAT=fopen(argv[1],"r");
	archivoDIG=fopen(argv[2],"a"); //DIG to plot by HaruPDF
	
	char linea[5000];
	char palabra[20];
	char letra;
	char *token;
	int n,k,j,i;
	int flags[100];
	int cambio;
	char nombres[100][20];

	float distancia;
	sscanf(argv[3],"%f",&distancia);

	float TimeBuffer1, SwitchBuffer1, DigitalBuffer1[20],DigitalTime[20];
	float TimeBuffer2, SwitchBuffer2, DigitalBuffer2[20],Buffer;
	struct TiempoI DTWithIndex[20];
	n=primera_linea(archivoDAT,flags,nombres,palabra);

	sscanf(palabra,"%f",&Buffer);
			
//	for(k=0;k<n;k++)
//	{
//		printf("%d\n",flags[k]);
//	}

	j=0; //Inicializando
	for(k=0;k<n;k++)
	{
		if(flags[k]==0)
		{
			TimeBuffer2=Buffer;
		}	
		if(flags[k]==2)
		{
			SwitchBuffer2=Buffer;
		
		}
		if(flags[k]==1)
		{
			DigitalBuffer2[j]=Buffer;
			j++;
		}
		fscanf(archivoDAT,"%f",&Buffer);
	}

	while(!feof(archivoDAT))
	{	
		j=0; //Inicializando
		for(k=0;k<n;k++)
		{
			if(flags[k]==0)
			{
				TimeBuffer1=Buffer;
			}	
			if(flags[k]==2)
			{
				SwitchBuffer1=Buffer;
				if(SwitchBuffer1 != SwitchBuffer2)
				{
					TimeBuffer2=TimeBuffer1;
				}	
				SwitchBuffer2=SwitchBuffer1;	
			}
			if(flags[k]==1)
			{
				DigitalBuffer1[j]=Buffer;
				if(DigitalBuffer1[j] != DigitalBuffer2[j])
				{
					DigitalTime[j]=TimeBuffer1-TimeBuffer2;			
				}
	
				DigitalBuffer2[j]=DigitalBuffer1[j];	
				j++;
			}
			fscanf(archivoDAT,"%f",&Buffer);
		}
	}

	insertion_sort(DigitalTime,DTWithIndex,j);	
	
	fprintf(archivoDIG,"%6.2f ",distancia);
	for(k=0;k<j;k++)
	{
		if(DTWithIndex[k].tiempo!=0.0)
		{
			fprintf(archivoDIG,"& %s %10.7f ",nombres[DTWithIndex[k].index],DTWithIndex[k].tiempo);
		}
	}
	fprintf(archivoDIG,"\\\\ %s\n",argv[1]);

	fclose(archivoDIG);
	fclose(archivoDAT);
	return 0;
}
