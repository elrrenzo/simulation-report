#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char **argv)
{
	FILE *archivoPL4, *archivoDAT; //DAT to read by PGFPLOTS and GNUPLOT (NOT by TPBIG)
	archivoPL4=fopen(argv[1],"r");
	archivoDAT=fopen(argv[2],"w");
	
	char linea[5000];
	char palabra[20];
	char header[3][100][10];
	char header2[100][30];
	int n,k,j;
	char flags[100];

	n=0;
	while(fscanf(archivoPL4,"%s",palabra) && strcmp(palabra,"in")!=0)
	{
		strcpy(header[0][n],palabra);
		flags[n]=' ';
		if(palabra[0]=='V')
		{
			flags[n]='v';
		}
		if(palabra[0]=='I')
		{
			flags[n]='i';
		}
		n=n+1;
		flags[n+1]='\0';
	}
	
	strcpy(header[1][0],"Time");
	for(k=1;k<n;k++)
	{
		fscanf(archivoPL4,"%s",palabra);
		strcpy(header[1][k],palabra);
	}

	fscanf(archivoPL4,"%s",palabra);
	strcpy(header[2][0]," ");
	for(k=1;k<n;k++)
	{
		if(header[0][k][2]=='n')
		{
			strcpy(header[2][k]," ");
		}
		else
		{
			fscanf(archivoPL4,"%s",palabra);
			strcpy(header[2][k],palabra);
		}	
	}
		
	for(k=0;k<n;k++)
	{
		if(strcmp(header[1][k],"MODELS")==0)
		{
			sprintf(header2[k],"%s",header[2][k]);	
			if(header2[k][0]=='D')
			{
				header2[k][0]=tolower(header2[k][0]);			
			}
		}
		else
		{
			sprintf(header2[k],"%c%s%s",flags[k],header[1][k],header[2][k]);	
			if(strcmp(header[1][k],"PIVOT")==0)
			{
				header2[k][0]='s';			
			}
		}
	}
	
	for(k=0;k<n;k++)
	{
		fprintf(archivoDAT,"%s ",header2[k]);
	}
	fprintf(archivoDAT,"\n");

	fscanf(archivoPL4,"%s",palabra);
    fgets(linea,5000, archivoPL4);
	fprintf(archivoDAT,"     %s%s",palabra,linea);
	
	while(fgets(linea,5000,archivoPL4) && (linea[2]=='-' && linea[3]=='9')==0)
	{
		fprintf(archivoDAT,"%s",linea);
	}
	
	fclose(archivoPL4);
	fclose(archivoDAT);
	return 0;
}
