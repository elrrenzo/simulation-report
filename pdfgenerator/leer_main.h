

int leer_main(char archivo_main[], char archivos[][80])
{
	int i;
	char linea[100];
	FILE *fichero;
    fichero=fopen(archivo_main,"r");
    i=0;
    while(fgets(linea, 100, fichero))
    {
		sscanf(linea, "%s", archivos[i]);
        i++;
    }

    fclose(fichero);

	return i;
}

