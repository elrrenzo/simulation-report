

int leer_main(char archivo_main[], char archivos[][180], char lineacomp[][180])
{
	int i;
	char linea[100];
	FILE *fichero;
    fichero=fopen(archivo_main,"r");
//	char lineacomp[100][180];
    i=0;
    while(fgets(linea, 100, fichero))
    {
		sscanf(linea, "%s", archivos[i]);
		strcpy(lineacomp[i],linea);	
//		strcpy(archivos[i],linea);
        i++;
    }

    fclose(fichero);

	return i;
}

