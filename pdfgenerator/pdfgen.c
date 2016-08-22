#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#include "hpdf.h"
#include "leer_main.h"
#include "pdigital.h"

jmp_buf env;

#ifdef HPDF_DLL
void  __stdcall
#else
void
#endif
error_handler  (HPDF_STATUS   error_no,
                HPDF_STATUS   detail_no,
                void         *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%u\n", (HPDF_UINT)error_no,
                (HPDF_UINT)detail_no);
    longjmp(env, 1);
}

int main (int argc, char **argv)
{
    const char* page_title = "Line Example";

    HPDF_Doc  pdf;
    HPDF_Font font;
    HPDF_Page page;
    char fname[256];

// Variables para LOGO

    HPDF_Image logo;
    double iw;
    double ih;

//---------------------------
	
    float tw;
	int i;
	int indicador;
	int cant_archivos;

	char archivos[50][80];	

/* Variables para subestaciones y trip  */

	char nombre_sub[50][10];
	char dist_sub[50][10];
	char dispo[50][80];
	int Nsub;
	float dmax;

	int Ntestes, Ngraf;
	float ubicacion[5000];
	int trip[5000][60];
	float time_trip[5000][60];

	float Y0;
	
	HPDF_REAL Ancho;
	HPDF_REAL Alto;
	int horizontal=0;

/* -------------------------------------  */

	char DateBuf_str[100];

	cant_archivos=leer_main(argv[1], archivos);

    strcpy (fname, argv[2]);
    strcat (fname, ".pdf");

    pdf = HPDF_New (error_handler, NULL);
    if (!pdf) {
        printf ("error: cannot create PdfDoc object\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }


    /* create default-font */
    font = HPDF_GetFont (pdf, "Helvetica", NULL);

    /* add a new page object. */
    page = HPDF_AddPage (pdf);
	HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);


	Ancho=HPDF_Page_GetWidth(page);
	Alto=HPDF_Page_GetHeight(page);


	Y0=Alto-200;
	for(i=0;i<cant_archivos;i++)
	{
		printf("%s\n",archivos[i]);
		Ntestes=pdigital(archivos[i], page, pdf,i);
	}

	printf("Cantidad de archivos: %d\n Alto: %f\n Ancho: %f \n", cant_archivos, Alto, Ancho);

	
    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}

