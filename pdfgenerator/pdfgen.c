#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#include "hpdf.h"
#include "leer_main.h"
#include "pdigital.h"
#include "graf_sub.h"

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
float pixels(float cm)
{
	float dpi=72;
	float ret;
	ret=72*cm/2.54;
	return ret;
}
float cm(float pixels)
{
	float dpi=72;
	float ret;
	ret=pixels/72*2.54;
	return ret;
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
	int i,j;
	int indicador;
	int cant_archivos;

	char archivos[50][180];	
	char lineacomp[50][180];	

/* Variables para subestaciones y trip  */

	char nombre_sub[50][10];
	char xticks_str[50][10];
	char points_str[10];
	char good_str[10];
	char bad_str[10];
	float xtick;
	char dist_sub[50][10];
	char dispo[50][80];
	struct substa Nsub;
	float dmax, longL;

	int Ntestes, Ngraf,Nelem, Npoints;
	float ubicacion[5000];
	int trip[5000][60];
	float time_trip[5000][60];
	struct Statistics stat[200];
	float Y0;
	float SY;

	HPDF_REAL Ancho;
	HPDF_REAL Alto;
	int horizontal=0;

/* -------------------------------------  */

	char DateBuf_str[100];

	cant_archivos=leer_main(argv[1], archivos, lineacomp);

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

	Nsub=leer_subesta(archivos[0], nombre_sub, dist_sub,xticks_str);

	dmax=graf_subesta(page,pdf, nombre_sub, dist_sub, xticks_str, Nsub, pixels(3), Alto-pixels(3), Ancho-pixels(6.5));	

	Y0=Alto-pixels(4.0);
	Npoints=0;
	SY=Y0;
	longL=Ancho-pixels(6.5);
	for(i=0;i<cant_archivos-1;i++)
	{
	//	printf("%s\n",archivos[i]);
		if(archivos[i+1][0]=='"')
		{
			archivos[i+1][strlen(archivos[i+1])-1]='\0';
			font=HPDF_GetFont(pdf,"Courier-Bold", NULL);
        	HPDF_Page_SetFontAndSize(page,font,8);
        	HPDF_Page_SetRGBFill (page, 0.1, 0.1, 0.1);
        	HPDF_Page_SetRGBStroke (page, 1.0, 0.2, 0.2);
        	HPDF_Page_BeginText(page);
        	HPDF_Page_MoveTextPos(page,pixels(3.0),SY);
			SY=SY-10;
			j=0;
			do
			{
				lineacomp[i+1][j]=lineacomp[i+1][j+1];
				j++;
			}
			while(lineacomp[i+1][j+1]!='\"');
			lineacomp[i+1][j]='\0';
        	HPDF_Page_ShowText(page,lineacomp[i+1]);
        	HPDF_Page_EndText(page);
		}
		else
		{		
	
			HPDF_Page_SetLineWidth (page, 0.7);

			Nelem=pdigital(archivos[i+1], page, pdf,pixels(3),SY,longL,dmax, &stat[i],longL);
			printf("N elementos: %d. N pontos: %d\n",Nelem,stat[i].points);

			HPDF_Page_SetLineWidth (page, 0.9);
        	HPDF_Page_SetRGBStroke (page, 0.3, 0.3, 0.3);
			
			HPDF_Page_MoveTo (page, pixels(3), SY+7);
			HPDF_Page_LineTo (page, pixels(3), SY+9);
			HPDF_Page_Stroke (page);
			HPDF_Page_MoveTo (page, pixels(3), SY-Nelem*10-12+6);
			HPDF_Page_LineTo (page, pixels(3), SY-Nelem*10-12+8);
			HPDF_Page_Stroke (page);
				
			HPDF_Page_MoveTo (page, pixels(3)+longL, SY+7);
			HPDF_Page_LineTo (page, pixels(3)+longL, SY+9);
			HPDF_Page_Stroke (page);
			HPDF_Page_MoveTo (page, pixels(3)+longL, SY-Nelem*10-12+6);
			HPDF_Page_LineTo (page, pixels(3)+longL, SY-Nelem*10-12+8);
			HPDF_Page_Stroke (page);
			
			for(j=0;j<Nsub.ticks;j++)
			{
		//HPDF_Page_SetLineCap (page, HPDF_BUTT_END);
				sscanf(xticks_str[j],"%f",&xtick);
				HPDF_Page_MoveTo (page, pixels(3)+xtick*longL/dmax, SY+7);
				HPDF_Page_LineTo (page, pixels(3)+xtick*longL/dmax, SY+9);
				HPDF_Page_Stroke (page);

				HPDF_Page_MoveTo (page, pixels(3)+xtick*longL/dmax, SY-Nelem*10-12+6);
				HPDF_Page_LineTo (page, pixels(3)+xtick*longL/dmax, SY-Nelem*10-12+8);
				HPDF_Page_Stroke (page);
			}
		SY=SY-Nelem*10-18;

		}
	}
	printf("Cantidad de archivos: %d\nAlto: %4.1f cm\nAncho: %4.1f cm\n", cant_archivos, cm(Alto), cm(Ancho));

	
    /* save the document to a file */
    HPDF_SaveToFile (pdf, fname);

    /* clean up */
    HPDF_Free (pdf);

    return 0;
}

