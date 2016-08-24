#ifndef PDIGITAL_H_GUARD
#define PDIGITAL_H_GUARD

struct Statistics{
	int points;
	float good;
	float bad;
};
void cuadrado (HPDF_Page page, double x, double y, double sz)
{
    HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.5);
    //HPDF_Page_SetRGBFill (page, 0.5, 0.5, 0.9);
    HPDF_Page_SetRGBFill (page, 0.0, 0.3, 0.3);
    HPDF_Page_Rectangle(page, x-sz/2, y-sz/2, sz, sz);
	HPDF_Page_Stroke (page);
}
void cuadrado2 (HPDF_Page page, double x, double y)
{
    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.9);
    HPDF_Page_SetRGBFill (page, 0.8, 0.0, 0.7);
    HPDF_Page_Rectangle(page, x, y, 9.5, 9.5);
	HPDF_Page_Stroke (page);
}

void circulo (HPDF_Page page, double x, double y, double sz)
{
    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 1.0);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.7);
    HPDF_Page_Circle (page, x, y, sz/2);
	HPDF_Page_Stroke (page);
}

void triangulo (HPDF_Page page, double x, double y, double sz)
{
	//HPDF_Page_SetLineWidth (page, 30);
	HPDF_Page_SetLineCap (page, HPDF_BUTT_END);
//	HPDF_Page_SetLineJoin (page, HPDF_MITER_JOIN);
    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.0);
    HPDF_Page_SetRGBFill (page, 0.7, 0.0, 0.0);
    HPDF_Page_MoveTo (page, x+sz/2, y-sz/4*sqrt(3));
    HPDF_Page_LineTo (page, x, y+sz/4*sqrt(3));
    HPDF_Page_LineTo (page, x-sz/2, y-sz/4*sqrt(3));
    HPDF_Page_LineTo (page, x+sz/2, y-sz/4*sqrt(3));
    HPDF_Page_LineTo (page, x, y+sz/4*sqrt(3));
    HPDF_Page_Stroke (page);
}
void rombo (HPDF_Page page, double x, double y, double sz)
{
    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
    HPDF_Page_MoveTo (page, x+sz/2, y);
    HPDF_Page_LineTo (page, x, y+sz/2+sz/8);
    HPDF_Page_LineTo (page, x-sz/2, y);
    HPDF_Page_LineTo (page, x, y-sz/2-sz/8);
    HPDF_Page_LineTo (page, x+sz/2, y);
    HPDF_Page_LineTo (page, x, y+sz/2+sz/8);
    HPDF_Page_Stroke (page);
}
void pentagono (HPDF_Page page, double x, double y, double sz)
{
//	float ll=10.0;
	float PI=3.14159;
	//y=y+sz/2-(sz/2-sz/2*cos(36*PI/180))*0.75;

    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 1.0);
    HPDF_Page_SetRGBFill (page, 0.8, 0.0, 0.8);
    HPDF_Page_MoveTo (page, x+sz/2, y+sz/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x, y+sz/2);
    HPDF_Page_LineTo (page, x-sz/2, y+sz/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x-sz/2*cos(54*PI/180), y-sz/2*sin(54*PI/180));
    HPDF_Page_LineTo (page, x+sz/2*cos(54*PI/180), y-sz/2*sin(54*PI/180));
    HPDF_Page_LineTo (page, x+sz/2, y+sz/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x, y+sz/2);
    HPDF_Page_Stroke (page);
}
void hexagono (HPDF_Page page, double x, double y, double sz)
{
//	float ll=9.5/0.866/2;
//	x=x+ll*0.866;
//	y=y+ll*0.866;
	float ll=sz/2;
//	y=y+ll;

    HPDF_Page_SetRGBStroke (page, 1.0, 0.645, 0.0);
    HPDF_Page_SetRGBFill (page, 0.8, 0.5, 0.0);
    HPDF_Page_MoveTo (page, x+ll, y);
    HPDF_Page_LineTo (page, x+ll/2, y+0.866*ll);
    HPDF_Page_LineTo (page, x-ll/2, y+0.866*ll);
    HPDF_Page_LineTo (page, x-ll, y);
    HPDF_Page_LineTo (page, x-ll/2, y-0.866*ll);
    HPDF_Page_LineTo (page, x+ll/2, y-0.866*ll);
    HPDF_Page_LineTo (page, x+ll, y);
    HPDF_Page_LineTo (page, x+ll/2, y+0.866*ll);
    HPDF_Page_Stroke (page);
}

int pdigital(char archivo_str[], HPDF_Page page, HPDF_Doc pdf, float x0, 
			float y0, float wplot, float dmax, struct Statistics *stat, float longitud)
{
	HPDF_Rect rect;
    HPDF_Point tp;
	int i, k, len, ret,Npoints;
	float distancia, tiempo, xx, yy,factor,tw;
	char tipo[10], sep[3];
    HPDF_Font font;
	char tiempo_str[10];
	FILE *fichero;
	char archivo_strPDF[50];
	char archivo_strDAT[50];
	char Npoints_str[10];
	char tfalta_str[4];
	char buffer[50];
	struct Statistics N;	
	fichero=fopen(archivo_str,"r");

	ret=0;
	N.points=0;
	factor=wplot/dmax;
//	yy=yy-Nfila*80;
	yy=y0;

	font=HPDF_GetFont(pdf,"Times-Roman", NULL);
    HPDF_Page_SetFontAndSize(page,font,8);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);

	fscanf(fichero,"%s",tfalta_str);
	
	HPDF_Page_BeginText(page);
	tw=HPDF_Page_TextWidth(page,tfalta_str);
    HPDF_Page_MoveTextPos(page,x0-10-tw,y0-3);
    HPDF_Page_ShowText(page,tfalta_str);
    HPDF_Page_EndText(page);

	
	font=HPDF_GetFont(pdf,"Courier", NULL);
	while(fscanf(fichero,"%f", &distancia) && !feof(fichero))
	{
//		printf("Distancia : %f\n", distancia);	Comment the DISTANCE
		//distancia = distancia/3.5;
		k=0;	
//		while(fscanf(fichero,"%s", sep) && strcmp(sep,"&") ==0)
		while(fscanf(fichero,"%s", sep))
		{
         	HPDF_Page_SetFontAndSize(page,font,5);
			if(strcmp(sep,"&")==0)
			{	
				fscanf(fichero,"%s %f", tipo, &tiempo);
		//		printf("Tipo : %s . Tiempo: %f\n", tipo, tiempo); Comment the Time
				sprintf(tiempo_str,"%.0f",tiempo*1000);
				tw=HPDF_Page_TextWidth(page,tiempo_str);
//			font=HPDF_GetFont(pdf,"Helvetica", NULL);
 		 
				if(strcmp(tipo,"FSA")==0)
				{
					circulo(page,distancia*factor+x0,yy-k*12,9.5);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-k*12-1.75);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSB")==0)
				{
					triangulo(page,distancia*factor+x0,yy-k*12,9.5);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-3-k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSC")==0)
				{
					rombo(page,distancia*factor+x0,yy-k*12,9.5);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-1.5-k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSAB")==0)
				{
					cuadrado(page,distancia*factor+x0,yy-k*12,9.5);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-k*12-2);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSBC")==0)
				{
					pentagono(page,distancia*factor+x0,yy-k*12,10);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-1.5-k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSCA")==0)
				{
					hexagono(page,distancia*factor+x0,yy-k*12,10);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0-tw/2,yy-1.7-k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
			}

			else if(strcmp(sep,"\\\\")==0)
			{
				if(k==0)
				{
					font=HPDF_GetFont(pdf,"Helvetica", NULL);
         			HPDF_Page_SetFontAndSize(page,font,8);
    				HPDF_Page_SetRGBFill (page, 0.0, 1.0, 0.0);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*factor+x0+2,yy+1.5-k*12);
          			HPDF_Page_ShowText(page,"X");
          			HPDF_Page_EndText(page);
				}
				fscanf(fichero,"%s", archivo_strDAT);
				strcpy(archivo_strPDF,"./");
				strcat(archivo_strPDF,archivo_strDAT);
	
				len=strlen(archivo_strPDF);

				archivo_strPDF[len-3]='p';
				archivo_strPDF[len-2]='d';
				archivo_strPDF[len-1]='f';
			
				rect.left = distancia*factor+x0-4;
    	//		rect.bottom = yy+k*12;
    			rect.bottom = yy-4;
    			rect.right = distancia*factor+x0+4;
    	//		rect.top = yy+k*12+8;
    			rect.top = yy+4;

    			HPDF_Page_CreateURILinkAnnot (page, rect, archivo_strPDF);	
				break;
			}
		}
		N.points++;
		if(k>ret)
		{
			ret=k;
		}

	}	
	sprintf(Npoints_str,"%d",N.points);
    font=HPDF_GetFont(pdf,"Times-Roman", NULL);
    HPDF_Page_SetFontAndSize(page,font,8);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page,x0+longitud+10,yy-3);
    HPDF_Page_ShowText(page,Npoints_str);
    HPDF_Page_EndText(page);
	
	*stat=N;	

	return ret;
}
#endif
