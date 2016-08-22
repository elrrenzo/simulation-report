#ifndef PDIGITAL_H_GUARD
#define PDIGITAL_H_GUARD

void cuadrado (HPDF_Page page, double x, double y)
{
    HPDF_Page_SetRGBStroke (page, 0.0, 0.5, 0.5);
    //HPDF_Page_SetRGBFill (page, 0.5, 0.5, 0.9);
    HPDF_Page_SetRGBFill (page, 0.0, 0.3, 0.3);
    HPDF_Page_Rectangle(page, x, y, 9.5, 9.5);
	HPDF_Page_Stroke (page);
}
void cuadrado2 (HPDF_Page page, double x, double y)
{
    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.9);
    HPDF_Page_SetRGBFill (page, 0.8, 0.0, 0.7);
    HPDF_Page_Rectangle(page, x, y, 9.5, 9.5);
	HPDF_Page_Stroke (page);
}

void circulo (HPDF_Page page, double x, double y)
{
    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 1.0);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.7);
    HPDF_Page_Circle (page, x+9.5/2, y+9.5/2, 9.6/2);
	HPDF_Page_Stroke (page);
}

void triangulo (HPDF_Page page, double x, double y)
{
	//HPDF_Page_SetLineWidth (page, 30);
	HPDF_Page_SetLineCap (page, HPDF_BUTT_END);
//	HPDF_Page_SetLineJoin (page, HPDF_MITER_JOIN);
    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 0.0);
    HPDF_Page_SetRGBFill (page, 0.7, 0.0, 0.0);
    HPDF_Page_MoveTo (page, x+9.5, y);
    HPDF_Page_LineTo (page, x+9.5/2, y+9.4);
    HPDF_Page_LineTo (page, x, y);
    HPDF_Page_LineTo (page, x+9.5, y);
    HPDF_Page_LineTo (page, x+9.5/2, y+9.4);
    HPDF_Page_Stroke (page);
}
void rombo (HPDF_Page page, double x, double y)
{
	float ll=9.5;

    HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);
    HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
    HPDF_Page_MoveTo (page, x+ll, y+ll/2);
    HPDF_Page_LineTo (page, x+ll/2, y+ll+ll/8);
    HPDF_Page_LineTo (page, x, y+ll/2);
    HPDF_Page_LineTo (page, x+ll/2, y-ll/8);
    HPDF_Page_LineTo (page, x+ll, y+ll/2);
    HPDF_Page_LineTo (page, x+ll/2, y+ll+ll/8);
    HPDF_Page_Stroke (page);
}
void pentagono (HPDF_Page page, double x, double y)
{
	float ll=10.0;
	float PI=3.14159;
	x=x+ll/2;
	y=y+ll/2;

    HPDF_Page_SetRGBStroke (page, 1.0, 0.0, 1.0);
    HPDF_Page_SetRGBFill (page, 0.8, 0.0, 0.8);
    HPDF_Page_MoveTo (page, x+ll/2, y+ll/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x, y+ll/2);
    HPDF_Page_LineTo (page, x-ll/2, y+ll/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x-ll/2*cos(54*PI/180), y-ll/2*sin(54*PI/180));
    HPDF_Page_LineTo (page, x+ll/2*cos(54*PI/180), y-ll/2*sin(54*PI/180));
    HPDF_Page_LineTo (page, x+ll/2, y+ll/2*tan(18*PI/180));
    HPDF_Page_LineTo (page, x, y+ll/2);
    HPDF_Page_Stroke (page);
}
void hexagono (HPDF_Page page, double x, double y)
{
	float ll=9.5/0.866/2;
	x=x+ll*0.866;
	y=y+ll*0.866;

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

int pdigital(char archivo_str[], HPDF_Page page, HPDF_Doc pdf, int Nfila)
{
	HPDF_Rect rect;
    HPDF_Point tp;
	int i, k, len, ret;
	float distancia, tiempo, xx, yy;
	char tipo[10], sep[3];
    HPDF_Font font;
	char tiempo_str[10];
	FILE *fichero;
	char archivo_strPDF[50];
	char archivo_strDAT[50];
	
	fichero=fopen(archivo_str,"r");

		
	
	ret=0;

	yy=700;
//	yy=yy-Nfila*80;
	yy=yy-Nfila*50;
//	yy=yy-Nfila*20;

	while(fscanf(fichero,"%f", &distancia) && !feof(fichero))
	{
	
		printf("Distancia : %f\n", distancia);	
		distancia = distancia/3.5;
		k=0;	
//		while(fscanf(fichero,"%s", sep) && strcmp(sep,"&") ==0)
		while(fscanf(fichero,"%s", sep))
		{
			
			if(strcmp(sep,"&")==0)
			{
				fscanf(fichero,"%s %f", tipo, &tiempo);
				printf("Tipo : %s . Tiempo: %f\n", tipo, tiempo);
				sprintf(tiempo_str,"%2.0f",tiempo*1000);
				font=HPDF_GetFont(pdf,"Courier", NULL);
//			font=HPDF_GetFont(pdf,"Helvetica", NULL);
         		HPDF_Page_SetFontAndSize(page,font,5);
				
 		 
				if(strcmp(tipo,"FSA")==0)
				{
					circulo(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSB")==0)
				{
					triangulo(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSC")==0)
				{
					rombo(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSAB")==0)
				{
					cuadrado(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSBC")==0)
				{
					pentagono(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
				if(strcmp(tipo,"FSCA")==0)
				{
					hexagono(page,distancia*0.58+60,yy+k*12);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+60.5,yy+3+k*12);
          			HPDF_Page_ShowText(page,tiempo_str);
          			HPDF_Page_EndText(page);
					k++;
				}
			}
		//	else if(k==0)
		//	{
			//	break;
   // 		HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
//			k++;
		//	}
			else if(strcmp(sep,"\\\\")==0)
			{
				if(k==0)
				{
					font=HPDF_GetFont(pdf,"Helvetica", NULL);
         			HPDF_Page_SetFontAndSize(page,font,8);
    				HPDF_Page_SetRGBFill (page, 0.0, 1.0, 0.0);
          			HPDF_Page_BeginText(page);
          			HPDF_Page_MoveTextPos(page,distancia*0.58+62,yy+1.5+k*12);
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
			
				rect.left = distancia*0.58+60;
    	//		rect.bottom = yy+k*12;
    			rect.bottom = yy;
    			rect.right = distancia*0.58+68;
    	//		rect.top = yy+k*12+8;
    			rect.top = yy+8;

    			HPDF_Page_CreateURILinkAnnot (page, rect, archivo_strPDF);	
				break;
			
			}
		}
		ret++;
	}	


	return ret;
}
#endif
