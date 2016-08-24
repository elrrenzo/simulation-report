struct substa{
	int bus;
	int ticks;
};

float
graf_subesta 	(HPDF_Page 	page, HPDF_Doc pdf,
				char 		nombres_str[][10], char		distancias_str[][10], 
				char xticks_str[][10], struct substa NS, double x0, double y0, double longitud)
{
	int i,N,Nt;
	float dist_float, dist_max;
	float xtick;
	float x, y, tw,xx;

	HPDF_Font font;
	
	N=NS.bus;
	Nt=NS.ticks;
	sscanf(distancias_str[N-1], "%f", &dist_max);

	HPDF_Page_SetLineWidth(page,2);	
	HPDF_Page_SetRGBStroke(page,0.5,0.0,0.5);

	HPDF_Page_MoveTo(page, x0, y0);
	HPDF_Page_LineTo(page, x0+longitud, y0);
	HPDF_Page_Stroke(page);	

	HPDF_Page_SetLineWidth(page,2);	
	HPDF_Page_SetRGBStroke(page,0.7,0.0,0.0);
	HPDF_Page_SetRGBFill(page,0.0,0.0,0.5);

	y=y0-2.5;
	for(i=0;i<N;i++)
	{
		HPDF_Page_SetRGBFill(page,0.0,1.0,0.0);
		sscanf(distancias_str[i], "%f", &dist_float);
		x=x0+dist_float/dist_max*longitud-2.5;
		HPDF_Page_Rectangle(page,x,y,5,5); 
		HPDF_Page_FillStroke(page);	
	
		font=HPDF_GetFont(pdf,"Helvetica-Bold", NULL);
//		HPDF_Page_SetFontAndSize(page,font,6);
		HPDF_Page_SetFontAndSize(page,font,8);
		HPDF_Page_SetRGBFill(page,0.0,0.0,0.0);
	
		tw=HPDF_Page_TextWidth(page, nombres_str[i]);
	
		HPDF_Page_BeginText(page);
		HPDF_Page_MoveTextPos(page,x-tw/2+2.5,y+9);
		HPDF_Page_ShowText(page,nombres_str[i]);
		HPDF_Page_EndText(page);

		font=HPDF_GetFont(pdf,"Courier", NULL);
		HPDF_Page_SetFontAndSize(page,font,7);
		tw=HPDF_Page_TextWidth(page, distancias_str[i]);
		HPDF_Page_BeginText(page);
		HPDF_Page_MoveTextPos(page,x-tw/2+2.5,y-9);
		HPDF_Page_ShowText(page,distancias_str[i]);

		HPDF_Page_EndText(page);
 
	}
	for(i=0;i<Nt;i++)
	{	
		
		HPDF_Page_SetLineWidth (page, 0.7);
		HPDF_Page_SetRGBFill (page, 0.0, 0.0, 0.0);
		HPDF_Page_SetRGBStroke (page, 0.0, 0.0, 0.0);
		sscanf(xticks_str[i],"%f",&xtick);
       	
		xx=x0+xtick*longitud/dist_max;
		HPDF_Page_MoveTo (page, xx, y0);
       	HPDF_Page_LineTo (page, xx, y0-4);
        HPDF_Page_Stroke (page);

		tw=HPDF_Page_TextWidth(page, xticks_str[i]);
		HPDF_Page_BeginText(page);
		HPDF_Page_MoveTextPos(page,xx-tw/2,y-9);
		HPDF_Page_ShowText(page,xticks_str[i]);
        HPDF_Page_EndText(page);
	}	

	return dist_max;
}

struct substa
leer_subesta	(char archivo_str[],char sub_str[][10],
				char dist_str[][10], char xticks_str[][10])
{
	struct substa ret;
	
	FILE *fichero;
	fichero=fopen(archivo_str,"r");
	char buffer[10];
	
	char linea[100];

	ret.bus=0;
	ret.ticks=0;

	while(fgets(linea, 100, fichero))
	{
		if(linea[0]=='-')
		{
			sscanf(linea,"%s %s",buffer,xticks_str[ret.ticks]);	
			ret.ticks++;
		}
		else
		{
			sscanf(linea, "%s %s", sub_str[ret.bus], dist_str[ret.bus]);
			ret.bus++;
		}
	}

	return ret;

}


