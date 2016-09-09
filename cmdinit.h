#ifdef EditMode
#define copystring strcpy
#else
#define copystring //strcpy
#include "unused.h"
#endif

//comment CmdDesc[n].FCategory=IDC_CMD strings for extra size reduce (about 500 bytes)


void FillCmdDesc()
{
int n;n=0;
	//0=teminator
	CmdDesc[n].FLevel=0;	
	
	CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Project Properties"); 
	copystring(CmdDesc[n].FParamName[1],"resX"); 
	copystring(CmdDesc[n].FParamName[2],"ResY");
		CmdDesc[n].FLevel=0;
		CmdDesc[n].FParamMax[1]=2048;
		CmdDesc[n].FParamMax[2]=2048;
	CmdDesc[n].FRoutine=NULL;
	CmdDesc[n].FCategory=IDC_CMD;
		
		CmdDesc[n].FSize=CellSize;n++;
	
	copystring(CmdDesc[n].FName,"Scene"); 
	copystring(CmdDesc[n].FParamName[1],"Type"); 
		copystring(CmdDesc[n].FParamEnum[1][0],"screen");
		copystring(CmdDesc[n].FParamEnum[1][1],"texture");
	copystring(CmdDesc[n].FParamName[2],"autoviewport"); 
		copystring(CmdDesc[n].FParamEnum[2][0],"on");
		copystring(CmdDesc[n].FParamEnum[2][1],"off");
	copystring(CmdDesc[n].FParamName[3],"bypass proj"); 
		copystring(CmdDesc[n].FParamEnum[3][0],"off");
		copystring(CmdDesc[n].FParamEnum[3][1],"on");

	CmdDesc[n].FRoutine=Scene;
	CmdDesc[n].FCategory=IDC_SCN;
		CmdDesc[n].FLevel=0;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AddParticle"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize");
		copystring(CmdDesc[n].FParamName[5],"ysize");
		copystring(CmdDesc[n].FParamName[6],"red"); 
		copystring(CmdDesc[n].FParamName[7],"green");
		copystring(CmdDesc[n].FParamName[8],"blue");
		copystring(CmdDesc[n].FParamName[9],"Blend");
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");

		CmdDesc[n].FRoutine=AddParticle;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Box"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize");
		copystring(CmdDesc[n].FParamName[5],"ysize");
		copystring(CmdDesc[n].FParamName[6],"red"); 
		copystring(CmdDesc[n].FParamName[7],"green");
		copystring(CmdDesc[n].FParamName[8],"blue");
		copystring(CmdDesc[n].FParamName[9],"blend"); 
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");
		CmdDesc[n].FRoutine=Box;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Ellipse"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"xsize");
		copystring(CmdDesc[n].FParamName[4],"ysize");
		copystring(CmdDesc[n].FParamName[5],"Quality");
		copystring(CmdDesc[n].FParamName[6],"red"); 
		copystring(CmdDesc[n].FParamName[7],"green");
		copystring(CmdDesc[n].FParamName[8],"blue");
		copystring(CmdDesc[n].FParamName[9],"blend"); 
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");

		CmdDesc[n].FRoutine=Ellipse;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;



	copystring(CmdDesc[n].FName,"Clear"); 
		copystring(CmdDesc[n].FParamName[1],"red"); 
		copystring(CmdDesc[n].FParamName[2],"green");
		copystring(CmdDesc[n].FParamName[3],"blue"); 
		copystring(CmdDesc[n].FParamName[4],"alpha");

		CmdDesc[n].FRoutine=Clear;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetAlfaMode"); 
		copystring(CmdDesc[n].FParamName[1],"Mode"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"none");
			copystring(CmdDesc[n].FParamEnum[1][1],"add");
			copystring(CmdDesc[n].FParamEnum[1][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[1][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[1][4],"min");
			copystring(CmdDesc[n].FParamEnum[1][5],"max");
			copystring(CmdDesc[n].FParamEnum[1][6],"alpha");

		CmdDesc[n].FLevel=1;
		CmdDesc[n].FRoutine=SetAlfa;
		CmdDesc[n].FCategory=IDC_ALPHA;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Cells"); 
				
		copystring(CmdDesc[n].FParamName[1],"Type"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"normal");
			copystring(CmdDesc[n].FParamEnum[1][1],"invert");

		copystring(CmdDesc[n].FParamName[2],"Count"); 
		copystring(CmdDesc[n].FParamName[3],"CellSize"); 
		copystring(CmdDesc[n].FParamName[4],"SquareSize"); 
		copystring(CmdDesc[n].FParamName[5],"Phaze");
		CmdDesc[n].FRoutine=Cells;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;
	
		//!!!
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Plasm"); 
				
		copystring(CmdDesc[n].FParamName[1],"Repeat"); 
		copystring(CmdDesc[n].FParamName[2],"red"); 		
		copystring(CmdDesc[n].FParamName[3],"green"); 		
		copystring(CmdDesc[n].FParamName[4],"blue");
		copystring(CmdDesc[n].FParamName[5],"blend"); 		
			copystring(CmdDesc[n].FParamEnum[5][0],"none");
			copystring(CmdDesc[n].FParamEnum[5][1],"add");
			copystring(CmdDesc[n].FParamEnum[5][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[5][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[5][4],"min");
			copystring(CmdDesc[n].FParamEnum[5][5],"max");
			copystring(CmdDesc[n].FParamEnum[5][6],"alpha");

		CmdDesc[n].FRoutine=Plasm;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	//obsolete
	copystring(CmdDesc[n].FName,"LGradient"); 
		copystring(CmdDesc[n].FParamName[1],"red1"); 		
		copystring(CmdDesc[n].FParamName[2],"green1"); 		
		copystring(CmdDesc[n].FParamName[3],"blue1"); 		
		copystring(CmdDesc[n].FParamName[4],"red2"); 		
		copystring(CmdDesc[n].FParamName[5],"green2"); 		
		copystring(CmdDesc[n].FParamName[6],"blue2"); 		
		copystring(CmdDesc[n].FParamName[7],"blend"); 
			copystring(CmdDesc[n].FParamEnum[7][0],"none");
			copystring(CmdDesc[n].FParamEnum[7][1],"add");
			copystring(CmdDesc[n].FParamEnum[7][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[7][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[7][4],"min");
			copystring(CmdDesc[n].FParamEnum[7][5],"max");
			copystring(CmdDesc[n].FParamEnum[7][6],"alpha");

		CmdDesc[n].FRoutine=LGradient;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ChessField"); 
		copystring(CmdDesc[n].FParamName[1],"xCount"); 		
		copystring(CmdDesc[n].FParamName[2],"yCount"); 		
		copystring(CmdDesc[n].FParamName[3],"red1"); 		
		copystring(CmdDesc[n].FParamName[4],"green1"); 		
		copystring(CmdDesc[n].FParamName[5],"blue1"); 		
		copystring(CmdDesc[n].FParamName[6],"red2"); 		
		copystring(CmdDesc[n].FParamName[7],"green2"); 		
		copystring(CmdDesc[n].FParamName[8],"blue2"); 		
		copystring(CmdDesc[n].FParamName[9],"blend"); 
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");

		CmdDesc[n].FRoutine=Chess;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"AddStars"); 
				
		copystring(CmdDesc[n].FParamName[1],"Count"); 
		CmdDesc[n].FRoutine=AddStars;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Post"); 
				
		copystring(CmdDesc[n].FParamName[1],"greedx"); 
		copystring(CmdDesc[n].FParamName[2],"greedy"); 
		copystring(CmdDesc[n].FParamName[3],"blend"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"none");
			copystring(CmdDesc[n].FParamEnum[3][1],"add");
			copystring(CmdDesc[n].FParamEnum[3][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[3][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[3][4],"min");
			copystring(CmdDesc[n].FParamEnum[3][5],"max");
			copystring(CmdDesc[n].FParamEnum[3][6],"alpha");
		CmdDesc[n].FRoutine=Post;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;




////-------------------------------------------------
	copystring(CmdDesc[n].FName,"Move"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z");
		CmdDesc[n].FRoutine=Move;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Zoom"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z");
		CmdDesc[n].FRoutine=Zoom;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Rotate"); 
		copystring(CmdDesc[n].FParamName[1],"Angle"); 
		copystring(CmdDesc[n].FParamName[2],"Anxis"); 
		copystring(CmdDesc[n].FParamName[3],"CenterPointX"); 
		copystring(CmdDesc[n].FParamName[4],"CenterPointY"); 
		copystring(CmdDesc[n].FParamName[5],"CenterPointZ"); 
		CmdDesc[n].FRoutine=Rotate;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TTwirl"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"Rad"); 
		copystring(CmdDesc[n].FParamName[4],"Power"); 
		copystring(CmdDesc[n].FParamName[5],"freqscaller"); 
		copystring(CmdDesc[n].FParamName[6],"stage"); 
		CmdDesc[n].FRoutine=TTwirl;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TLenz"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"Rad"); 
		copystring(CmdDesc[n].FParamName[4],"Power"); 
		copystring(CmdDesc[n].FParamName[5],"stage"); 
		CmdDesc[n].FRoutine=TLenz;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"TWaves"); 
		copystring(CmdDesc[n].FParamName[1],"xAmp"); 
		copystring(CmdDesc[n].FParamName[2],"yAmp"); 
		copystring(CmdDesc[n].FParamName[3],"xPhase"); 
		copystring(CmdDesc[n].FParamName[4],"yPhase"); 
		copystring(CmdDesc[n].FParamName[5],"Type");
			copystring(CmdDesc[n].FParamEnum[5][0],"1");
			copystring(CmdDesc[n].FParamEnum[5][1],"2");
		copystring(CmdDesc[n].FParamName[6],"stage");

		CmdDesc[n].FRoutine=TWaves;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TRoll"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"stage"); 
		CmdDesc[n].FRoutine=TRoll;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TFlip"); 
		copystring(CmdDesc[n].FParamName[1],"axis"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"x");
			copystring(CmdDesc[n].FParamEnum[1][1],"y");
		copystring(CmdDesc[n].FParamName[2],"stage"); 
		CmdDesc[n].FRoutine=TFlip;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

//---

	copystring(CmdDesc[n].FName,"Invert"); 
		CmdDesc[n].FRoutine=Invert;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

		//!!!
		CmdDesc[n].FSize=CellSize;n++;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"RadialBlur"); 
		copystring(CmdDesc[n].FParamName[1],"startvalue");
		copystring(CmdDesc[n].FParamName[2],"blend");
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"add");
			copystring(CmdDesc[n].FParamEnum[2][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[2][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[2][4],"min");
			copystring(CmdDesc[n].FParamEnum[2][5],"max");
			copystring(CmdDesc[n].FParamEnum[2][6],"alpha");
		copystring(CmdDesc[n].FParamName[3],"br.pass");
		copystring(CmdDesc[n].FParamName[4],"scale");
		copystring(CmdDesc[n].FParamName[5],"iterations");
		copystring(CmdDesc[n].FParamName[6],"x");
		copystring(CmdDesc[n].FParamName[7],"y");
		copystring(CmdDesc[n].FParamName[8],"dist");

		CmdDesc[n].FRoutine=RBlur;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

		//!!!
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Tile"); 
		copystring(CmdDesc[n].FParamName[1],"w"); 
		copystring(CmdDesc[n].FParamName[2],"h"); 
		copystring(CmdDesc[n].FParamName[3],"stage"); 
		CmdDesc[n].FRoutine=Tile;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

		//!!!
		CmdDesc[n].FSize=CellSize;n++;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowScene"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"time"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"disable");
			copystring(CmdDesc[n].FParamEnum[2][1],"enable");
		copystring(CmdDesc[n].FParamName[3],"x"); 
		copystring(CmdDesc[n].FParamName[4],"y"); 
		copystring(CmdDesc[n].FParamName[5],"w"); 
		copystring(CmdDesc[n].FParamName[6],"r"); 
		copystring(CmdDesc[n].FParamName[7],"g"); 
		copystring(CmdDesc[n].FParamName[8],"b"); 
		CmdDesc[n].FRoutine=ShowScene;
		CmdDesc[n].FCategory=IDC_SCN;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EndScene"); 
		CmdDesc[n].FRoutine=EndScene;
		CmdDesc[n].FCategory=IDC_SCN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EndDraw"); 
		CmdDesc[n].FRoutine=EndDraw;
		CmdDesc[n].FCategory=IDC_SCN;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetFreq"); 
		CmdDesc[n].FRoutine=SetFreq;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		copystring(CmdDesc[n].FParamName[1],"p1"); 
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetPhase"); 
		CmdDesc[n].FRoutine=SetPhase;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetAmp"); 
		CmdDesc[n].FRoutine=SetAmp;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaSin"); 
		CmdDesc[n].FRoutine=AnimaSin;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaLinear"); 
		CmdDesc[n].FRoutine=AnimaLinear;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaAbsSin"); //to be realized later!!!!!
		CmdDesc[n].FRoutine=AnimaAbsSin;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Text"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize");
		copystring(CmdDesc[n].FParamName[5],"ysize");
		copystring(CmdDesc[n].FParamName[6],"red"); 
		copystring(CmdDesc[n].FParamName[7],"green");
		copystring(CmdDesc[n].FParamName[8],"blue");
		copystring(CmdDesc[n].FParamName[9],"Blend");
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");
		copystring(CmdDesc[n].FParamName[10],"tracking");
		copystring(CmdDesc[n].FParamName[11],"font texture");
		copystring(CmdDesc[n].FParamName[12],"time");
			copystring(CmdDesc[n].FParamEnum[12][0],"off");
			copystring(CmdDesc[n].FParamEnum[12][1],"on");
		copystring(CmdDesc[n].FParamName[13],"start");
		copystring(CmdDesc[n].FParamName[14],"speed");

		CmdDesc[n].FRoutine=Text;
		CmdDesc[n].FCategory=IDC_TEXT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"QCRotate"); 
		copystring(CmdDesc[n].FParamName[1],"Angle"); 
		copystring(CmdDesc[n].FParamName[2],"Axis");
			copystring(CmdDesc[n].FParamEnum[2][0],"x");
			copystring(CmdDesc[n].FParamEnum[2][1],"y");
			copystring(CmdDesc[n].FParamEnum[2][2],"z");
		copystring(CmdDesc[n].FParamName[3],"QAmp"); 
		CmdDesc[n].FRoutine=QCRotate;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"WTwirl"); 
		copystring(CmdDesc[n].FParamName[1],"Angle"); 
		copystring(CmdDesc[n].FParamName[2],"Anxis"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"x");
			copystring(CmdDesc[n].FParamEnum[2][1],"y");
			copystring(CmdDesc[n].FParamEnum[2][2],"z");
		copystring(CmdDesc[n].FParamName[3],"CenterPointX"); 
		copystring(CmdDesc[n].FParamName[4],"CenterPointY"); 
		copystring(CmdDesc[n].FParamName[5],"CenterPointZ"); 
		copystring(CmdDesc[n].FParamName[6],"amp"); 
		CmdDesc[n].FRoutine=WTwirl;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ZBufEnable"); 
		CmdDesc[n].FRoutine=ZBufEnable;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ZBufDisable"); 
		CmdDesc[n].FRoutine=ZBufDisable;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TextureToTexture"); 
		copystring(CmdDesc[n].FParamName[1],"texture"); 
		copystring(CmdDesc[n].FParamName[2],"Interpolation"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"point");
			copystring(CmdDesc[n].FParamEnum[2][2],"linear");
		copystring(CmdDesc[n].FParamName[3],"generate mipmap"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"no");
			copystring(CmdDesc[n].FParamEnum[3][1],"yes");
		CmdDesc[n].FRoutine=TextureToTexture;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Flat"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize");
		copystring(CmdDesc[n].FParamName[5],"ysize");
		copystring(CmdDesc[n].FParamName[6],"texture"); 
		copystring(CmdDesc[n].FParamName[7],"Material");
		copystring(CmdDesc[n].FParamName[8],"culling");
			copystring(CmdDesc[n].FParamEnum[8][0],"none");
			copystring(CmdDesc[n].FParamEnum[8][1],"front");
			copystring(CmdDesc[n].FParamEnum[8][2],"back");
		copystring(CmdDesc[n].FParamName[9],"Blend");
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");

		CmdDesc[n].FRoutine=Flat;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"FillMaterial"); 
		copystring(CmdDesc[n].FParamName[1],"Material"); 
		copystring(CmdDesc[n].FParamName[2],"Ambient r"); 
		copystring(CmdDesc[n].FParamName[3],"Ambient g"); 
		copystring(CmdDesc[n].FParamName[4],"Ambient b"); 
		copystring(CmdDesc[n].FParamName[5],"Ambient a"); 
		copystring(CmdDesc[n].FParamName[6],"Diffuse r"); 
		copystring(CmdDesc[n].FParamName[7],"Diffuse g"); 
		copystring(CmdDesc[n].FParamName[8],"Diffuse b"); 
		copystring(CmdDesc[n].FParamName[9],"Diffuse a"); 
		copystring(CmdDesc[n].FParamName[10],"Specular r"); 
		copystring(CmdDesc[n].FParamName[11],"Specular g"); 
		copystring(CmdDesc[n].FParamName[12],"Specular b"); 
		copystring(CmdDesc[n].FParamName[13],"Specular power"); 
		copystring(CmdDesc[n].FParamName[14],"Emissive r"); 
		copystring(CmdDesc[n].FParamName[15],"Emissive g"); 
		copystring(CmdDesc[n].FParamName[16],"Emissive b"); 
		copystring(CmdDesc[n].FParamName[17],"Emissive a"); 
		CmdDesc[n].FRoutine=FillMaterial;
		CmdDesc[n].FCategory=IDC_LIGHT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	
	copystring(CmdDesc[n].FName,"PointLight"); 
		copystring(CmdDesc[n].FParamName[1],"Number"); 
		copystring(CmdDesc[n].FParamName[2],"x"); 
		copystring(CmdDesc[n].FParamName[3],"y"); 
		copystring(CmdDesc[n].FParamName[4],"z"); 
		copystring(CmdDesc[n].FParamName[5],"Range"); 
		copystring(CmdDesc[n].FParamName[6],"Ambient r"); 
		copystring(CmdDesc[n].FParamName[7],"Ambient g"); 
		copystring(CmdDesc[n].FParamName[8],"Ambient b"); 
		copystring(CmdDesc[n].FParamName[9],"Diffuse r"); 
		copystring(CmdDesc[n].FParamName[10],"Diffuse g"); 
		copystring(CmdDesc[n].FParamName[11],"Diffuse b"); 
		copystring(CmdDesc[n].FParamName[12],"Specular r"); 
		copystring(CmdDesc[n].FParamName[13],"Specular g"); 
		copystring(CmdDesc[n].FParamName[14],"Specular b"); 
		copystring(CmdDesc[n].FParamName[15],"attunation 0"); 
		copystring(CmdDesc[n].FParamName[16],"attunation 1"); 
		copystring(CmdDesc[n].FParamName[17],"attunation 2"); 
		CmdDesc[n].FRoutine=PointLight;
		CmdDesc[n].FCategory=IDC_LIGHT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"DirectionalLight"); 
		copystring(CmdDesc[n].FParamName[1],"Number"); 
		copystring(CmdDesc[n].FParamName[2],"x"); 
		copystring(CmdDesc[n].FParamName[3],"y"); 
		copystring(CmdDesc[n].FParamName[4],"z"); 
		copystring(CmdDesc[n].FParamName[5],"Ambient r"); 
		copystring(CmdDesc[n].FParamName[6],"Ambient g"); 
		copystring(CmdDesc[n].FParamName[7],"Ambient b"); 
		copystring(CmdDesc[n].FParamName[8],"Diffuse r"); 
		copystring(CmdDesc[n].FParamName[9],"Diffuse g"); 
		copystring(CmdDesc[n].FParamName[10],"Diffuse b"); 
		copystring(CmdDesc[n].FParamName[11],"Specular r"); 
		copystring(CmdDesc[n].FParamName[12],"Specular g"); 
		copystring(CmdDesc[n].FParamName[13],"Specular b"); 
		CmdDesc[n].FRoutine=DirectionalLight;
		CmdDesc[n].FCategory=IDC_LIGHT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Shpere"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"zsize"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");

		CmdDesc[n].FRoutine=Sphere;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"MultiTexture"); 
		copystring(CmdDesc[n].FParamName[1],"Stage"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"Transform");
			copystring(CmdDesc[n].FParamEnum[3][0],"none");
			copystring(CmdDesc[n].FParamEnum[3][1],"camsp reflect");
			copystring(CmdDesc[n].FParamEnum[3][2],"shperemap");
		copystring(CmdDesc[n].FParamName[4],"Mixer"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"mod");
			copystring(CmdDesc[n].FParamEnum[4][1],"modX2");
			copystring(CmdDesc[n].FParamEnum[4][2],"modX4");
			copystring(CmdDesc[n].FParamEnum[4][3],"add");
			copystring(CmdDesc[n].FParamEnum[4][4],"addsign");
			copystring(CmdDesc[n].FParamEnum[4][5],"addsign2x");
			copystring(CmdDesc[n].FParamEnum[4][6],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][7],"addsmooth");
			copystring(CmdDesc[n].FParamEnum[4][8],"modAaddC");
			copystring(CmdDesc[n].FParamEnum[4][9],"dot4");
			copystring(CmdDesc[n].FParamEnum[4][10],"displace");
			copystring(CmdDesc[n].FParamEnum[4][11],"displace");
		copystring(CmdDesc[n].FParamName[5],"uv set"); 
		CmdDesc[n].FRoutine=MultiTexture;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetCull"); 
		copystring(CmdDesc[n].FParamName[1],"Type"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"none");
			copystring(CmdDesc[n].FParamEnum[1][1],"front");
			copystring(CmdDesc[n].FParamEnum[1][2],"back");
		CmdDesc[n].FRoutine=SetCull;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LightsOff"); 
		CmdDesc[n].FRoutine=LightsOff;
		CmdDesc[n].FCategory=IDC_LIGHT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LightsOn"); 
		CmdDesc[n].FRoutine=LightsOn;
		CmdDesc[n].FCategory=IDC_LIGHT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"RWave"); 
		copystring(CmdDesc[n].FParamName[1],"AmpX"); 
		copystring(CmdDesc[n].FParamName[2],"AmpY"); 
		copystring(CmdDesc[n].FParamName[3],"freq x"); 
		copystring(CmdDesc[n].FParamName[4],"freq y"); 
		copystring(CmdDesc[n].FParamName[5],"ofs x"); 
		copystring(CmdDesc[n].FParamName[6],"ofs y"); 
		copystring(CmdDesc[n].FParamName[7],"ftype");
		 copystring(CmdDesc[n].FParamEnum[7][0],"1");
		 copystring(CmdDesc[n].FParamEnum[7][1],"2");
		CmdDesc[n].FRoutine=RWave;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Tube"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"zsize"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");

		CmdDesc[n].FRoutine=Tube;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Fog"); 
		copystring(CmdDesc[n].FParamName[1],"Start"); 
		copystring(CmdDesc[n].FParamName[2],"End"); 
		copystring(CmdDesc[n].FParamName[3],"r"); 
		copystring(CmdDesc[n].FParamName[4],"g"); 
		copystring(CmdDesc[n].FParamName[5],"b"); 
		CmdDesc[n].FRoutine=Fog;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"DisableFog"); 
		CmdDesc[n].FRoutine=DisableFog;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;
		///!!!
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ScreenToTexture"); 
		copystring(CmdDesc[n].FParamName[1],"texture"); 
		copystring(CmdDesc[n].FParamName[2],"Interpolation"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"point");
			copystring(CmdDesc[n].FParamEnum[2][2],"linear");
		copystring(CmdDesc[n].FParamName[3],"generate mipmap"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"no");
			copystring(CmdDesc[n].FParamEnum[3][1],"yes");

		CmdDesc[n].FRoutine=ScreenToTexture;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ZClear"); 
		CmdDesc[n].FRoutine=ZClear;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetViewport"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"w"); 
		copystring(CmdDesc[n].FParamName[4],"h"); 
		CmdDesc[n].FRoutine=SetViewport;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Desaturate"); 
	copystring(CmdDesc[n].FParamName[1],"q");
		CmdDesc[n].FRoutine=Desaturate;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CopyToAlpha"); 
		CmdDesc[n].FRoutine=CopyToAlpha;
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Brightness/Contrast"); 
		copystring(CmdDesc[n].FParamName[1],"Contrast");
		copystring(CmdDesc[n].FParamName[2],"Brightness");
		CmdDesc[n].FRoutine=Contrast;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;
		//!!!
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"RGBDisplace"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		copystring(CmdDesc[n].FParamName[2],"texture 2");
		copystring(CmdDesc[n].FParamName[3],"r1");
		copystring(CmdDesc[n].FParamName[4],"g1");
		copystring(CmdDesc[n].FParamName[5],"b1");
		copystring(CmdDesc[n].FParamName[6],"r2");
		copystring(CmdDesc[n].FParamName[7],"g2");
		copystring(CmdDesc[n].FParamName[8],"b2");
		CmdDesc[n].FRoutine=RGBDisplace;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"RadialDisplace"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		copystring(CmdDesc[n].FParamName[2],"texture 2");
		copystring(CmdDesc[n].FParamName[3],"r");
		copystring(CmdDesc[n].FParamName[4],"g");
		copystring(CmdDesc[n].FParamName[5],"b");
		CmdDesc[n].FRoutine=RadialDisplace;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShBlur"); 
		copystring(CmdDesc[n].FParamName[1],"q");
		copystring(CmdDesc[n].FParamName[2],"type");
			copystring(CmdDesc[n].FParamEnum[2][0],"xy");
			copystring(CmdDesc[n].FParamEnum[2][1],"x");
			copystring(CmdDesc[n].FParamEnum[2][2],"y");
		CmdDesc[n].FRoutine=ShBlur;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Julia"); 
		copystring(CmdDesc[n].FParamName[1],"a");
		copystring(CmdDesc[n].FParamName[2],"b");
		copystring(CmdDesc[n].FParamName[3],"iterations");
		copystring(CmdDesc[n].FParamName[4],"zoom");
		copystring(CmdDesc[n].FParamName[5],"st");
		copystring(CmdDesc[n].FParamName[6],"fx");
		copystring(CmdDesc[n].FParamName[7],"fx2");
		CmdDesc[n].FRoutine=Julia;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"SinColor"); 
		copystring(CmdDesc[n].FParamName[1],"r");
		copystring(CmdDesc[n].FParamName[2],"g");
		copystring(CmdDesc[n].FParamName[3],"b");
		CmdDesc[n].FRoutine=SinColor;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"Palette"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		CmdDesc[n].FRoutine=Palette;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"AdjustColor"); 
		copystring(CmdDesc[n].FParamName[1],"Hue");
		copystring(CmdDesc[n].FParamName[2],"Saturation");
		copystring(CmdDesc[n].FParamName[3],"Contrast");
		copystring(CmdDesc[n].FParamName[4],"Brightness");
		CmdDesc[n].FRoutine=AdjustColor;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"Sharp"); 
		copystring(CmdDesc[n].FParamName[1],"size");
		copystring(CmdDesc[n].FParamName[2],"direction");
			copystring(CmdDesc[n].FParamEnum[2][0],"xy");
			copystring(CmdDesc[n].FParamEnum[2][1],"x");
			copystring(CmdDesc[n].FParamEnum[2][2],"y");
		copystring(CmdDesc[n].FParamName[3],"scale");
		CmdDesc[n].FRoutine=Sharp;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;
		//!!!
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"CEmboss"); 
		copystring(CmdDesc[n].FParamName[1],"size");
		copystring(CmdDesc[n].FParamName[2],"direction");
		copystring(CmdDesc[n].FParamName[3],"angle");
		copystring(CmdDesc[n].FParamName[4],"dist");
		CmdDesc[n].FRoutine=Emboss2;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"TextureQuad"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		CmdDesc[n].FRoutine=TextureQuad;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"ClearRGB"); 
		CmdDesc[n].FRoutine=ClearRGB;
		copystring(CmdDesc[n].FParamName[1],"r");
		copystring(CmdDesc[n].FParamName[2],"g");
		copystring(CmdDesc[n].FParamName[3],"b");
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"ClearAlpha"); 
		CmdDesc[n].FRoutine=ClearAlpha;
		copystring(CmdDesc[n].FParamName[1],"Alpha");
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"MpGrad"); 
		CmdDesc[n].FRoutine=MpGrad;
		copystring(CmdDesc[n].FParamName[1],"divide");
		copystring(CmdDesc[n].FParamName[2],"rgb");
		copystring(CmdDesc[n].FParamName[3],"rgb");
		copystring(CmdDesc[n].FParamName[4],"rgb");
		copystring(CmdDesc[n].FParamName[5],"rgb");
		copystring(CmdDesc[n].FParamName[6],"rgb");
		copystring(CmdDesc[n].FParamName[7],"rgb");
		copystring(CmdDesc[n].FParamName[8],"rgb");
		copystring(CmdDesc[n].FParamName[9],"rgb");
		copystring(CmdDesc[n].FParamName[10],"rgb");
		copystring(CmdDesc[n].FParamName[11],"rgb");
		copystring(CmdDesc[n].FParamName[12],"rgb");
		copystring(CmdDesc[n].FParamName[13],"rgb");
		copystring(CmdDesc[n].FParamName[14],"rgb");
		copystring(CmdDesc[n].FParamName[15],"rgb");
		copystring(CmdDesc[n].FParamName[16],"rgb");

		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"WriteAlpha"); 
		CmdDesc[n].FRoutine=WriteAlpha;
		copystring(CmdDesc[n].FParamName[1],"1-write enable");
			copystring(CmdDesc[n].FParamEnum[1][0],"disable");
			copystring(CmdDesc[n].FParamEnum[1][1],"enable");
			copystring(CmdDesc[n].FParamEnum[1][2],"A only");
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"MainLoop"); 
		CmdDesc[n].FRoutine=MainLoop;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=0;
	
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"Precalc"); 
		CmdDesc[n].FRoutine=PreCalc;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=0;
	
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"InvertAlpha"); 
		CmdDesc[n].FRoutine=InvertA;
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
	
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"ModCopyToAlphaFromTexture"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		copystring(CmdDesc[n].FParamName[2],"inv en");
			copystring(CmdDesc[n].FParamEnum[2][0],"normal");
			copystring(CmdDesc[n].FParamEnum[2][1],"inverted");
		CmdDesc[n].FRoutine=ModCopyToAlphaFromTexture;
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
	
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"RDisplace"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		copystring(CmdDesc[n].FParamName[2],"texture 2");
		copystring(CmdDesc[n].FParamName[3],"xs");
		copystring(CmdDesc[n].FParamName[4],"ys");
		copystring(CmdDesc[n].FParamName[5],"as");
		CmdDesc[n].FRoutine=RDisplace;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
	
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TMixer"); 
		copystring(CmdDesc[n].FParamName[1],"texture"); 
		copystring(CmdDesc[n].FParamName[2],"texture 2"); 
		copystring(CmdDesc[n].FParamName[3],"blend"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"add");
			copystring(CmdDesc[n].FParamEnum[3][1],"subtract");
			copystring(CmdDesc[n].FParamEnum[3][2],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[3][3],"min");
			copystring(CmdDesc[n].FParamEnum[3][4],"max");
			copystring(CmdDesc[n].FParamEnum[3][5],"mod");
			copystring(CmdDesc[n].FParamEnum[3][6],"modX2");
			copystring(CmdDesc[n].FParamEnum[3][7],"modX4");
			copystring(CmdDesc[n].FParamEnum[3][8],"add");
			copystring(CmdDesc[n].FParamEnum[3][9],"addsign");
			copystring(CmdDesc[n].FParamEnum[3][10],"addsign2x");
			copystring(CmdDesc[n].FParamEnum[3][11],"subtract");
			copystring(CmdDesc[n].FParamEnum[3][12],"addsmooth");
			copystring(CmdDesc[n].FParamEnum[3][13],"modAaddC");
			copystring(CmdDesc[n].FParamEnum[3][14],"dot3");

		copystring(CmdDesc[n].FParamName[4],"Bright1"); 
		copystring(CmdDesc[n].FParamName[5],"Bright2"); 
		CmdDesc[n].FRoutine=TMixer;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CopyAlphaFromTexture"); 
		copystring(CmdDesc[n].FParamName[1],"texture"); 
		CmdDesc[n].FRoutine=CopyAlphaFromTexture;
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoadTexture"); 
		copystring(CmdDesc[n].FParamName[1],"texture"); 
		CmdDesc[n].FRoutine=LoadTexture;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"Glow"); 
		copystring(CmdDesc[n].FParamName[1],"size");
		copystring(CmdDesc[n].FParamName[2],"direction");
			copystring(CmdDesc[n].FParamEnum[2][0],"xy");
			copystring(CmdDesc[n].FParamEnum[2][1],"x");
			copystring(CmdDesc[n].FParamEnum[2][2],"y");
		copystring(CmdDesc[n].FParamName[3],"amount");
		CmdDesc[n].FRoutine=FixGlow;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"SDisplace"); 
		copystring(CmdDesc[n].FParamName[1],"texture");
		copystring(CmdDesc[n].FParamName[2],"texture 2");
		copystring(CmdDesc[n].FParamName[3],"ampX");
		copystring(CmdDesc[n].FParamName[4],"ampY");
		copystring(CmdDesc[n].FParamName[5],"offset X");
		copystring(CmdDesc[n].FParamName[6],"offset Y");
		CmdDesc[n].FRoutine=SDisplace;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
	
		CmdDesc[n].FSize=CellSize;n++;

copystring(CmdDesc[n].FName,"AtoRGB"); 
		CmdDesc[n].FRoutine=AlphaToRGB;
		CmdDesc[n].FCategory=IDC_ALPHA;
		CmdDesc[n].FLevel=1;
	
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaPow3"); 
		CmdDesc[n].FRoutine=AnimaPow3;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaPow2"); 
		CmdDesc[n].FRoutine=AnimaPow2;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Anima4SQRT"); 
		CmdDesc[n].FRoutine=AnimaSqrt;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ScaleColor"); 
		copystring(CmdDesc[n].FParamName[1],"r"); 
		copystring(CmdDesc[n].FParamName[2],"g"); 
		copystring(CmdDesc[n].FParamName[3],"b"); 
		CmdDesc[n].FRoutine=newScaleColor;
		CmdDesc[n].FCategory=IDC_RGB;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Crossfade"); 
		copystring(CmdDesc[n].FParamName[1],"w"); 
		copystring(CmdDesc[n].FParamName[2],"h"); 
		CmdDesc[n].FRoutine=newCrossfade;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CopyToVB"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=CopyToVB;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowVB"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"blend");
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[4][4],"min");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");
			copystring(CmdDesc[n].FParamEnum[4][6],"alpha");

		CmdDesc[n].FRoutine=ShowVB;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ParticleArray"); 
		copystring(CmdDesc[n].FParamName[1],"count"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"x"); 
		copystring(CmdDesc[n].FParamName[5],"y"); 
		copystring(CmdDesc[n].FParamName[6],"z"); 
		copystring(CmdDesc[n].FParamName[7],"w"); 
		copystring(CmdDesc[n].FParamName[8],"h"); 
		copystring(CmdDesc[n].FParamName[9],"d"); 
		copystring(CmdDesc[n].FParamName[10],"blend"); 
			copystring(CmdDesc[n].FParamEnum[10][0],"none");
			copystring(CmdDesc[n].FParamEnum[10][1],"add");
			copystring(CmdDesc[n].FParamEnum[10][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[10][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[10][4],"min");
			copystring(CmdDesc[n].FParamEnum[10][5],"max");
			copystring(CmdDesc[n].FParamEnum[10][6],"alpha");

		copystring(CmdDesc[n].FParamName[11],"pw"); 
		copystring(CmdDesc[n].FParamName[12],"ph"); 
		CmdDesc[n].FRoutine=ParticleArray;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	
	copystring(CmdDesc[n].FName,"MatrixRotate"); 
		copystring(CmdDesc[n].FParamName[1],"Yaw"); 
		copystring(CmdDesc[n].FParamName[2],"Pitch"); 
		copystring(CmdDesc[n].FParamName[3],"Roll"); 
		copystring(CmdDesc[n].FParamName[4],"pre/post clone"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"pre");
			copystring(CmdDesc[n].FParamEnum[4][1],"clone");
			copystring(CmdDesc[n].FParamEnum[4][2],"post");

		CmdDesc[n].FRoutine=MatrixRotate;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"MatrixScale"); 
		copystring(CmdDesc[n].FParamName[1],"w"); 
		copystring(CmdDesc[n].FParamName[2],"h"); 
		copystring(CmdDesc[n].FParamName[3],"d"); 
		copystring(CmdDesc[n].FParamName[4],"pre/post clone"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"pre");
			copystring(CmdDesc[n].FParamEnum[4][1],"clone");
			copystring(CmdDesc[n].FParamEnum[4][2],"post");
		CmdDesc[n].FRoutine=MatrixScale;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"MatrixTranslate"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"pre/post clone"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"pre");
			copystring(CmdDesc[n].FParamEnum[4][1],"clone");
			copystring(CmdDesc[n].FParamEnum[4][2],"post");
		CmdDesc[n].FRoutine=MatrixTranslate;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowVBs"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"blend"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[4][4],"min");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");
			copystring(CmdDesc[n].FParamEnum[4][6],"alpha");

		copystring(CmdDesc[n].FParamName[5],"count"); 
		copystring(CmdDesc[n].FParamName[6],"rndXamp"); 
		copystring(CmdDesc[n].FParamName[7],"rndYamp"); 
		copystring(CmdDesc[n].FParamName[8],"rndZamp"); 
		copystring(CmdDesc[n].FParamName[9],"Xspd"); 
		copystring(CmdDesc[n].FParamName[10],"Yspd"); 
		copystring(CmdDesc[n].FParamName[11],"Zspd"); 
		copystring(CmdDesc[n].FParamName[12],"Yaw spd"); 
		copystring(CmdDesc[n].FParamName[13],"Pitch spd"); 
		copystring(CmdDesc[n].FParamName[14],"Roll spd"); 
		copystring(CmdDesc[n].FParamName[15],"Target material 1"); 
		copystring(CmdDesc[n].FParamName[16],"Target material 2"); 
		copystring(CmdDesc[n].FParamName[17],"material speed"); 


		CmdDesc[n].FRoutine=ShowVBs;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaRandom"); 
		CmdDesc[n].FRoutine=AnimaRandom;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SubdividedFlat"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"zsize"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");

		CmdDesc[n].FRoutine=SubdividedFlat;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AddToVB"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=AddToVB;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;
	
	copystring(CmdDesc[n].FName,"CleanVB"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=CleanVB;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"StartAddToVB"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=StartAddToVB;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EndAddToVB"); 
		CmdDesc[n].FRoutine=EndAddToVB;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaClampMax"); 
		CmdDesc[n].FRoutine=AnimaClampMax;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaClampMin"); 
		CmdDesc[n].FRoutine=AnimaClampMin;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"AnimaClampMode");
		copystring(CmdDesc[n].FParamName[1],"Mode"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"disabled");
			copystring(CmdDesc[n].FParamEnum[1][1],"enabled");

		CmdDesc[n].FRoutine=AnimaClampMode;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Anima2SQRT"); 
		CmdDesc[n].FRoutine=Anima2Sqrt;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetMaxRecurrenceLevel"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=SetMaxRecurrenceLevel;
		CmdDesc[n].FCategory=IDC_SCN;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoadMesh"); 
		copystring(CmdDesc[n].FParamName[1],"slot n"); 
		CmdDesc[n].FRoutine=LoadMesh;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowMesh"); 
		copystring(CmdDesc[n].FParamName[1],"slot n"); 
		copystring(CmdDesc[n].FParamName[2],"x"); 
		copystring(CmdDesc[n].FParamName[3],"y"); 
		copystring(CmdDesc[n].FParamName[4],"z"); 
		copystring(CmdDesc[n].FParamName[5],"s"); 
		copystring(CmdDesc[n].FParamName[6],"r"); 
		copystring(CmdDesc[n].FParamName[7],"r2"); 
		copystring(CmdDesc[n].FParamName[8],"r3"); 
		copystring(CmdDesc[n].FParamName[9],"tex"); 
		copystring(CmdDesc[n].FParamName[10],"mat"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
		CmdDesc[n].FRoutine=ShowMesh;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TextBlock"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize");
		copystring(CmdDesc[n].FParamName[5],"ysize");
		copystring(CmdDesc[n].FParamName[6],"red"); 
		copystring(CmdDesc[n].FParamName[7],"green");
		copystring(CmdDesc[n].FParamName[8],"blue");
		copystring(CmdDesc[n].FParamName[9],"Blend");
			copystring(CmdDesc[n].FParamEnum[9][0],"none");
			copystring(CmdDesc[n].FParamEnum[9][1],"add");
			copystring(CmdDesc[n].FParamEnum[9][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[9][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[9][4],"min");
			copystring(CmdDesc[n].FParamEnum[9][5],"max");
			copystring(CmdDesc[n].FParamEnum[9][6],"alpha");
		copystring(CmdDesc[n].FParamName[10],"tracking");
		copystring(CmdDesc[n].FParamName[11],"leading");
		copystring(CmdDesc[n].FParamName[12],"startstring");
		copystring(CmdDesc[n].FParamName[13],"endstring");
		copystring(CmdDesc[n].FParamName[14],"return");
			copystring(CmdDesc[n].FParamEnum[14][0],"yes");
			copystring(CmdDesc[n].FParamEnum[14][1],"no");
		copystring(CmdDesc[n].FParamName[15],"font texture");
		copystring(CmdDesc[n].FParamName[16],"align");
			copystring(CmdDesc[n].FParamEnum[16][0],"left");
			copystring(CmdDesc[n].FParamEnum[16][1],"center");
			copystring(CmdDesc[n].FParamEnum[16][2],"right");


		CmdDesc[n].FRoutine=TextBlock;
		CmdDesc[n].FCategory=IDC_TEXT;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoadText");
	copystring(CmdDesc[n].FParamName[1],".");
		CmdDesc[n].FRoutine=LoadText;
		CmdDesc[n].FCategory=IDC_TEXT;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"FastBlur"); 
		copystring(CmdDesc[n].FParamName[1],"value");
		copystring(CmdDesc[n].FParamName[2],"blend");
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"add");
			copystring(CmdDesc[n].FParamEnum[2][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[2][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[2][4],"min");
			copystring(CmdDesc[n].FParamEnum[2][5],"max");
			copystring(CmdDesc[n].FParamEnum[2][6],"alpha");
		copystring(CmdDesc[n].FParamName[3],"br.pass");
		copystring(CmdDesc[n].FParamName[4],"scale");
		copystring(CmdDesc[n].FParamName[5],"noise");
		CmdDesc[n].FRoutine=FastBlur;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"FastMapBlur"); 
		copystring(CmdDesc[n].FParamName[1],"value");
		copystring(CmdDesc[n].FParamName[2],"blend");
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"add");
			copystring(CmdDesc[n].FParamEnum[2][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[2][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[2][4],"min");
			copystring(CmdDesc[n].FParamEnum[2][5],"max");
			copystring(CmdDesc[n].FParamEnum[2][6],"alpha");
		copystring(CmdDesc[n].FParamName[3],"br.pass");
		copystring(CmdDesc[n].FParamName[4],"scale");
		copystring(CmdDesc[n].FParamName[5],"noise");
		copystring(CmdDesc[n].FParamName[6],"texture");
		copystring(CmdDesc[n].FParamName[7],"amp");
		copystring(CmdDesc[n].FParamName[8],"phase");
		copystring(CmdDesc[n].FParamName[9],"q");
		CmdDesc[n].FRoutine=FastMapBlur;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Point"); 
		copystring(CmdDesc[n].FParamName[1],"x");
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z");
		CmdDesc[n].FRoutine=Point;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Curve"); 
	copystring(CmdDesc[n].FParamName[1],"quality");
	copystring(CmdDesc[n].FParamName[2],"blend");
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"add");
			copystring(CmdDesc[n].FParamEnum[2][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[2][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[2][4],"min");
			copystring(CmdDesc[n].FParamEnum[2][5],"max");
			copystring(CmdDesc[n].FParamEnum[2][6],"alpha");
	copystring(CmdDesc[n].FParamName[3],"fill");
			copystring(CmdDesc[n].FParamEnum[3][0],"false");
			copystring(CmdDesc[n].FParamEnum[3][1],"true");
	copystring(CmdDesc[n].FParamName[4],"r");
	copystring(CmdDesc[n].FParamName[5],"g");
	copystring(CmdDesc[n].FParamName[6],"b");
		CmdDesc[n].FRoutine=Curve;
		CmdDesc[n].FCategory=IDC_2D;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Perlin"); 
		copystring(CmdDesc[n].FParamName[1],"x");
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z");
		copystring(CmdDesc[n].FParamName[4],"o1");
		copystring(CmdDesc[n].FParamName[5],"o2");
		copystring(CmdDesc[n].FParamName[6],"o3");
		copystring(CmdDesc[n].FParamName[7],"o4");
		copystring(CmdDesc[n].FParamName[8],"o5");
		copystring(CmdDesc[n].FParamName[9],"o6");
		copystring(CmdDesc[n].FParamName[10],"o7");
		copystring(CmdDesc[n].FParamName[11],"o8");
		CmdDesc[n].FRoutine=newPerlin;
		CmdDesc[n].FCategory=IDC_TEXGEN;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"StoreCurve"); 
		copystring(CmdDesc[n].FParamName[1],"n");
		CmdDesc[n].FRoutine=StoreCurve;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AnimaSpline"); 
		CmdDesc[n].FRoutine=AnimaSpline;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		for (int pr=1;pr<20;pr++) {copystring(CmdDesc[n].FParamName[pr],"param");}
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TimeCursor"); 
	copystring(CmdDesc[n].FParamName[1],"x");
		CmdDesc[n].FRoutine=TimeCursor;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TrackXYZ"); 
	copystring(CmdDesc[n].FParamName[1],"curve");
	copystring(CmdDesc[n].FParamName[2],"pnum for x");
	copystring(CmdDesc[n].FParamName[3],"pnum for y");
	copystring(CmdDesc[n].FParamName[4],"pnum for z");
	copystring(CmdDesc[n].FParamName[5],"speed");
	copystring(CmdDesc[n].FParamName[6],"loop");
		CmdDesc[n].FRoutine=TrackXYZ;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Camera"); 
	copystring(CmdDesc[n].FParamName[1],"src x");
	copystring(CmdDesc[n].FParamName[2],"src y");
	copystring(CmdDesc[n].FParamName[3],"src z");
	copystring(CmdDesc[n].FParamName[4],"dst x");
	copystring(CmdDesc[n].FParamName[5],"dst y");
	copystring(CmdDesc[n].FParamName[6],"dst z");
	copystring(CmdDesc[n].FParamName[7],"up");

	copystring(CmdDesc[n].FParamName[8],"time"); 
		copystring(CmdDesc[n].FParamEnum[8][0],"disable");
		copystring(CmdDesc[n].FParamEnum[8][1],"enable");
	copystring(CmdDesc[n].FParamName[9],"x"); 
	copystring(CmdDesc[n].FParamName[10],"y"); 
	copystring(CmdDesc[n].FParamName[11],"width"); 
	copystring(CmdDesc[n].FParamName[12],"slde"); 
		copystring(CmdDesc[n].FParamEnum[12][0],"none");
		copystring(CmdDesc[n].FParamEnum[12][1],"cubic");
	copystring(CmdDesc[n].FParamName[13],"break");
		copystring(CmdDesc[n].FParamEnum[13][0],"off");
		copystring(CmdDesc[n].FParamEnum[13][1],"on");

		CmdDesc[n].FRoutine=Camera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Spline2Camera"); 
	copystring(CmdDesc[n].FParamName[1],"src curve");
	copystring(CmdDesc[n].FParamName[2],"dst curve");
	copystring(CmdDesc[n].FParamName[3],"up curve");
	copystring(CmdDesc[n].FParamName[4],"speed");
	copystring(CmdDesc[n].FParamName[5],"loop");
		CmdDesc[n].FRoutine=Spline2Camera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Spline1Camera"); 
	copystring(CmdDesc[n].FParamName[1],"curve");
	copystring(CmdDesc[n].FParamName[2],"up curve");
	copystring(CmdDesc[n].FParamName[3],"speed");
	copystring(CmdDesc[n].FParamName[4],"loop");
		CmdDesc[n].FRoutine=Spline1Camera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TimeLine"); 
		CmdDesc[n].FRoutine=TimeLine;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"FreeCamera"); 
		CmdDesc[n].FRoutine=FreeCamera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetTextureFilter"); 
	copystring(CmdDesc[n].FParamName[1],"stage");
	copystring(CmdDesc[n].FParamName[2],"magfilter type");
			copystring(CmdDesc[n].FParamEnum[2][0],"none");
			copystring(CmdDesc[n].FParamEnum[2][1],"point");
			copystring(CmdDesc[n].FParamEnum[2][2],"linear");
	copystring(CmdDesc[n].FParamName[3],"minfilter type");
			copystring(CmdDesc[n].FParamEnum[3][0],"none");
			copystring(CmdDesc[n].FParamEnum[3][1],"point");
			copystring(CmdDesc[n].FParamEnum[3][2],"linear");
	copystring(CmdDesc[n].FParamName[4],"MIPfilter type");
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"point");
			copystring(CmdDesc[n].FParamEnum[4][2],"linear");

		CmdDesc[n].FRoutine=SetTextureFilter;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"OverrideTM"); 
	copystring(CmdDesc[n].FParamName[1],"stage");
	copystring(CmdDesc[n].FParamName[2],"override");
			copystring(CmdDesc[n].FParamEnum[2][0],"disabled");
			copystring(CmdDesc[n].FParamEnum[2][1],"enabled");
	copystring(CmdDesc[n].FParamName[3],"texture");
	copystring(CmdDesc[n].FParamName[4],"material");
		CmdDesc[n].FRoutine=OverrideTM;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetHQFiltersTex"); 
	copystring(CmdDesc[n].FParamName[1],"HQ");
			copystring(CmdDesc[n].FParamEnum[1][0],"512");
			copystring(CmdDesc[n].FParamEnum[1][1],"1024");
			copystring(CmdDesc[n].FParamEnum[1][2],"2048");
		CmdDesc[n].FRoutine=SetHQFiltersTex;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

//sound

	copystring(CmdDesc[n].FName,"LoadXM"); 
	copystring(CmdDesc[n].FParamName[1],"gen samples");
			copystring(CmdDesc[n].FParamEnum[1][0],"off");
			copystring(CmdDesc[n].FParamEnum[1][1],"on");

		CmdDesc[n].FRoutine=LoadXM;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Oscillator"); 
	copystring(CmdDesc[n].FParamName[1],"type");
			copystring(CmdDesc[n].FParamEnum[1][0],"sin");
			copystring(CmdDesc[n].FParamEnum[1][1],"abssin");
			copystring(CmdDesc[n].FParamEnum[1][2],"triangle");
			copystring(CmdDesc[n].FParamEnum[1][3],"saw");
			copystring(CmdDesc[n].FParamEnum[1][4],"square");
			copystring(CmdDesc[n].FParamEnum[1][5],"noise");
	copystring(CmdDesc[n].FParamName[2],"amp");
	copystring(CmdDesc[n].FParamName[3],"freq");
	copystring(CmdDesc[n].FParamName[4],"mix");
			copystring(CmdDesc[n].FParamEnum[4][0],"off");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"multiply");
			copystring(CmdDesc[n].FParamEnum[4][4],"comparator");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");

		CmdDesc[n].FRoutine=Oscillator;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowSample"); 
		CmdDesc[n].FRoutine=ShowSample;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Envelope"); 
	copystring(CmdDesc[n].FParamName[1],"curve");
		CmdDesc[n].FRoutine=Envelope;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"StoreSample"); 
	copystring(CmdDesc[n].FParamName[1],"slot");
		CmdDesc[n].FRoutine=StoreSample;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"MixSample"); 
	copystring(CmdDesc[n].FParamName[1],"slot1");
	copystring(CmdDesc[n].FParamName[2],"slot2");
	copystring(CmdDesc[n].FParamName[3],"type");
			copystring(CmdDesc[n].FParamEnum[3][0],"add");
			copystring(CmdDesc[n].FParamEnum[3][1],"subtract");
			copystring(CmdDesc[n].FParamEnum[3][2],"multiply");
	copystring(CmdDesc[n].FParamName[4],"amp1");
	copystring(CmdDesc[n].FParamName[5],"amp2");
	copystring(CmdDesc[n].FParamName[6],"offset");
		CmdDesc[n].FRoutine=MixSample;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Oscillator2"); 
	copystring(CmdDesc[n].FParamName[1],"type");
			copystring(CmdDesc[n].FParamEnum[1][0],"sin");
			copystring(CmdDesc[n].FParamEnum[1][1],"abssin");
			copystring(CmdDesc[n].FParamEnum[1][2],"triangle");
			copystring(CmdDesc[n].FParamEnum[1][3],"saw");
			copystring(CmdDesc[n].FParamEnum[1][4],"square");
			copystring(CmdDesc[n].FParamEnum[1][5],"noise");
	copystring(CmdDesc[n].FParamName[2],"amp");
	copystring(CmdDesc[n].FParamName[3],"freq");
	copystring(CmdDesc[n].FParamName[5],"odd/even");
	copystring(CmdDesc[n].FParamName[5],"mix");
			copystring(CmdDesc[n].FParamEnum[5][0],"off");
			copystring(CmdDesc[n].FParamEnum[5][1],"add");
			copystring(CmdDesc[n].FParamEnum[5][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[5][3],"multiply");
			copystring(CmdDesc[n].FParamEnum[5][4],"comparator");
			copystring(CmdDesc[n].FParamEnum[5][5],"max");
		CmdDesc[n].FRoutine=Oscillator2;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Oscillator3"); 
	copystring(CmdDesc[n].FParamName[1],"type");
			copystring(CmdDesc[n].FParamEnum[1][0],"sin");
			copystring(CmdDesc[n].FParamEnum[1][1],"abssin");
			copystring(CmdDesc[n].FParamEnum[1][2],"triangle");
			copystring(CmdDesc[n].FParamEnum[1][3],"saw");
			copystring(CmdDesc[n].FParamEnum[1][4],"square");
			copystring(CmdDesc[n].FParamEnum[1][5],"noise");
	copystring(CmdDesc[n].FParamName[2],"amp");
	copystring(CmdDesc[n].FParamName[3],"freq");
	copystring(CmdDesc[n].FParamName[4],"odd/even");
	copystring(CmdDesc[n].FParamName[5],"detune");
	copystring(CmdDesc[n].FParamName[6],"mix");
			copystring(CmdDesc[n].FParamEnum[6][0],"off");
			copystring(CmdDesc[n].FParamEnum[6][1],"add");
			copystring(CmdDesc[n].FParamEnum[6][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[6][3],"multiply");
			copystring(CmdDesc[n].FParamEnum[6][4],"comparator");
			copystring(CmdDesc[n].FParamEnum[6][5],"max");
		CmdDesc[n].FRoutine=Oscillator3;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LowCut"); 
	copystring(CmdDesc[n].FParamName[1],"freq");
		CmdDesc[n].FRoutine=LowCut;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"HiCut"); 
	copystring(CmdDesc[n].FParamName[1],"cutoff");
	copystring(CmdDesc[n].FParamName[2],"resonance");
		CmdDesc[n].FRoutine=HiCut;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"HiCut2"); 
	copystring(CmdDesc[n].FParamName[1],"cutoff");
	copystring(CmdDesc[n].FParamName[2],"resonance");
	copystring(CmdDesc[n].FParamName[3],"cutoff spd");
	copystring(CmdDesc[n].FParamName[4],"cutoff amp");
	copystring(CmdDesc[n].FParamName[5],"res spd");
	copystring(CmdDesc[n].FParamName[6],"res amp");
	copystring(CmdDesc[n].FParamName[7],"faze");
		CmdDesc[n].FRoutine=HiCut2;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Res"); 
	copystring(CmdDesc[n].FParamName[1],"freq");
	copystring(CmdDesc[n].FParamName[2],"q");
	copystring(CmdDesc[n].FParamName[3],"decay");
		CmdDesc[n].FRoutine=Res;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Compressor"); 
	copystring(CmdDesc[n].FParamName[1],"factor");
	copystring(CmdDesc[n].FParamName[2],"limit");
		CmdDesc[n].FRoutine=Compressor;
		CmdDesc[n].FCategory=IDC_DYNA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Distortion"); 
	copystring(CmdDesc[n].FParamName[1],"center p");
	copystring(CmdDesc[n].FParamName[2],"hi p");
	copystring(CmdDesc[n].FParamName[3],"position");
		CmdDesc[n].FRoutine=Distortion;
		CmdDesc[n].FCategory=IDC_DYNA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Normalize"); 
		CmdDesc[n].FRoutine=Normalize;
		CmdDesc[n].FCategory=IDC_DYNA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Crossfader"); 
	copystring(CmdDesc[n].FParamName[1],"q");
		CmdDesc[n].FRoutine=Crossfader;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Reverb"); 
	copystring(CmdDesc[n].FParamName[1],"size");
	copystring(CmdDesc[n].FParamName[2],"decay");
	copystring(CmdDesc[n].FParamName[3],"dry");
	copystring(CmdDesc[n].FParamName[4],"filtration");
		CmdDesc[n].FRoutine=Reverb;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Chorus"); 
	copystring(CmdDesc[n].FParamName[1],"voices");
	copystring(CmdDesc[n].FParamName[2],"maxdelay");
	copystring(CmdDesc[n].FParamName[3],"speed");
	copystring(CmdDesc[n].FParamName[4],"feed");
	copystring(CmdDesc[n].FParamName[5],"amp");
		CmdDesc[n].FRoutine=Chorus;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EQ"); 
	copystring(CmdDesc[n].FParamName[1],"400");
	copystring(CmdDesc[n].FParamName[2],"1200");
	copystring(CmdDesc[n].FParamName[3],"2400");
	copystring(CmdDesc[n].FParamName[4],"4800");
	copystring(CmdDesc[n].FParamName[5],"8700");
	copystring(CmdDesc[n].FParamName[6],"16500");
		CmdDesc[n].FRoutine=EQ;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoadGrain"); 
	copystring(CmdDesc[n].FParamName[1],"Loop");
			copystring(CmdDesc[n].FParamEnum[1][0],"off");
			copystring(CmdDesc[n].FParamEnum[1][1],"on");
		CmdDesc[n].FRoutine=LoadGrain;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EndTimeLine"); 
		CmdDesc[n].FRoutine=EndTimeLine;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

//-------------

	copystring(CmdDesc[n].FName,"PartOut"); 
	copystring(CmdDesc[n].FParamName[1],"start");
	copystring(CmdDesc[n].FParamName[2],"end");
		CmdDesc[n].FRoutine=PartOut;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Limit"); 
	copystring(CmdDesc[n].FParamName[1],"x");
	copystring(CmdDesc[n].FParamName[2],"y");
	copystring(CmdDesc[n].FParamName[3],"z");
	copystring(CmdDesc[n].FParamName[4],"xs");
	copystring(CmdDesc[n].FParamName[5],"ys");
	copystring(CmdDesc[n].FParamName[6],"zs");
		CmdDesc[n].FRoutine=Limit;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;
//--


	copystring(CmdDesc[n].FName,"SetShader"); 
	copystring(CmdDesc[n].FParamName[1],"shader");
			copystring(CmdDesc[n].FParamEnum[1][0],"off");
			copystring(CmdDesc[n].FParamEnum[1][1],"ligth&displace");
	copystring(CmdDesc[n].FParamName[2],"displace texture");
	copystring(CmdDesc[n].FParamName[3],"normalmap texture");
	copystring(CmdDesc[n].FParamName[4],"material");
	copystring(CmdDesc[n].FParamName[5],"disp.value");
	copystring(CmdDesc[n].FParamName[6],"envmap texture");
	copystring(CmdDesc[n].FParamName[7],"bumpV");
	copystring(CmdDesc[n].FParamName[8],"screen tex.");
	copystring(CmdDesc[n].FParamName[9],"z tex.");
	copystring(CmdDesc[n].FParamName[10],"diff scale");
	copystring(CmdDesc[n].FParamName[11],"nmap scale");

		CmdDesc[n].FRoutine=SetShader;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"NormalMap"); 
		CmdDesc[n].FRoutine=NormalMap;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SelectG_Sphere"); 
	copystring(CmdDesc[n].FParamName[1],"type");
			copystring(CmdDesc[n].FParamEnum[1][0],"set select");
			copystring(CmdDesc[n].FParamEnum[1][1],"add select");
			copystring(CmdDesc[n].FParamEnum[1][2],"subtract select");
	copystring(CmdDesc[n].FParamName[2],"x");	
	copystring(CmdDesc[n].FParamName[3],"y");
	copystring(CmdDesc[n].FParamName[4],"z");
	copystring(CmdDesc[n].FParamName[5],"rad");
	copystring(CmdDesc[n].FParamName[6],"q");
	copystring(CmdDesc[n].FParamName[7],"func");
			copystring(CmdDesc[n].FParamEnum[7][0],"linear");
			copystring(CmdDesc[n].FParamEnum[7][1],"sin");
			copystring(CmdDesc[n].FParamEnum[7][2],"exp");
			copystring(CmdDesc[n].FParamEnum[7][3],"hard");
		CmdDesc[n].FRoutine=SelectG_Sphere;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"RemoveSelection"); 
		CmdDesc[n].FRoutine=RemoveSelection;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"InvertSelection"); 
		CmdDesc[n].FRoutine=InvertSelection;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SelectAll"); 
		CmdDesc[n].FRoutine=SelectAll;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"NoiseSelection"); 
	copystring(CmdDesc[n].FParamName[1],"stepx");
	copystring(CmdDesc[n].FParamName[2],"stepy");
		copystring(CmdDesc[n].FParamName[3],"ofs x");
	copystring(CmdDesc[n].FParamName[4],"ofs y");
		CmdDesc[n].FRoutine=NoiseSelection;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Torus"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"zsize"); 
		copystring(CmdDesc[n].FParamName[6],"rad"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");
		copystring(CmdDesc[n].FParamName[12],"angle"); 

		CmdDesc[n].FRoutine=Torus;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Trapezium"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z");
		CmdDesc[n].FRoutine=Trapezium;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Skew"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z");
		CmdDesc[n].FRoutine=Skew;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SubdividedCube"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"zsize"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");

		CmdDesc[n].FRoutine=SubdividedCube;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"RollSample"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"loop"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"off");
			copystring(CmdDesc[n].FParamEnum[3][1],"on");
		copystring(CmdDesc[n].FParamName[4],"saturation"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"off");
			copystring(CmdDesc[n].FParamEnum[4][1],"on");

		CmdDesc[n].FRoutine=RollSample;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Resample"); 
		copystring(CmdDesc[n].FParamName[1],"freq hz/10"); 
		copystring(CmdDesc[n].FParamName[2],"freq hz"); 
	copystring(CmdDesc[n].FParamName[3],"mix");
			copystring(CmdDesc[n].FParamEnum[3][0],"off");
			copystring(CmdDesc[n].FParamEnum[3][1],"add");
			copystring(CmdDesc[n].FParamEnum[3][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[3][3],"multiply");
		CmdDesc[n].FRoutine=Resample;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"OutputSampleTo"); 
		copystring(CmdDesc[n].FParamName[1],"module sample"); 
		CmdDesc[n].FRoutine=OutputSampleTo;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"PingPongSample"); 
		CmdDesc[n].FRoutine=PingPongSample;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetSampleSize"); 
	copystring(CmdDesc[n].FParamName[1],"ms"); 
		CmdDesc[n].FRoutine=SetSampleSize;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Halftone"); 
	copystring(CmdDesc[n].FParamName[1],"dpi"); 
	copystring(CmdDesc[n].FParamName[2],"treshold"); 
	copystring(CmdDesc[n].FParamName[3],"angle"); 
	copystring(CmdDesc[n].FParamName[4],"color"); 
		CmdDesc[n].FRoutine=Halftone;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"XYZ->RGB"); 
	copystring(CmdDesc[n].FParamName[1],"depth texture"); 
		CmdDesc[n].FRoutine=XYZ;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"StoreCamera"); 
	copystring(CmdDesc[n].FParamName[1],"slot"); 
		CmdDesc[n].FRoutine=StoreCamera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Shadow"); 
	copystring(CmdDesc[n].FParamName[1],"depth texture"); 
	copystring(CmdDesc[n].FParamName[2],"light-depth texture"); 
	copystring(CmdDesc[n].FParamName[3],"source texture"); 
	copystring(CmdDesc[n].FParamName[4],"camera"); 
	copystring(CmdDesc[n].FParamName[5],"power"); 
		CmdDesc[n].FRoutine=Shadow;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetClamp"); 
	copystring(CmdDesc[n].FParamName[1],"stage"); 
	copystring(CmdDesc[n].FParamName[2],"modeU"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"wrap");
			copystring(CmdDesc[n].FParamEnum[2][1],"clamp");
			copystring(CmdDesc[n].FParamEnum[2][2],"mirror");
			copystring(CmdDesc[n].FParamEnum[2][3],"border");
	copystring(CmdDesc[n].FParamName[3],"modeV"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"wrap");
			copystring(CmdDesc[n].FParamEnum[3][1],"clamp");
			copystring(CmdDesc[n].FParamEnum[3][2],"mirror");
			copystring(CmdDesc[n].FParamEnum[3][3],"border");
	copystring(CmdDesc[n].FParamName[4],"border r"); 
	copystring(CmdDesc[n].FParamName[5],"border g"); 
	copystring(CmdDesc[n].FParamName[6],"border b"); 
	copystring(CmdDesc[n].FParamName[7],"border a"); 
		CmdDesc[n].FRoutine=SetClamp;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ResizeTexture");
	copystring(CmdDesc[n].FParamName[1],"n"); 
	copystring(CmdDesc[n].FParamName[2],"size"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"32");
			copystring(CmdDesc[n].FParamEnum[2][1],"64");
			copystring(CmdDesc[n].FParamEnum[2][2],"128");
			copystring(CmdDesc[n].FParamEnum[2][3],"256");
			copystring(CmdDesc[n].FParamEnum[2][4],"512");
			copystring(CmdDesc[n].FParamEnum[2][5],"1024");
			copystring(CmdDesc[n].FParamEnum[2][6],"2048");
			copystring(CmdDesc[n].FParamEnum[2][7],"4096");
	copystring(CmdDesc[n].FParamName[3],"format"); 
			copystring(CmdDesc[n].FParamEnum[3][0],"argb8");
			copystring(CmdDesc[n].FParamEnum[3][1],"argb16f");
			copystring(CmdDesc[n].FParamEnum[3][2],"argb32f");

		CmdDesc[n].FRoutine=ResizeTexture;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"SetRenderTarget");
	copystring(CmdDesc[n].FParamName[1],"texture"); 
		CmdDesc[n].FRoutine=SetRT;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ReflectCamY");
		CmdDesc[n].FRoutine=ReflectCamY;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetPrj");
	copystring(CmdDesc[n].FParamName[1],"type"); 
	copystring(CmdDesc[n].FParamEnum[1][0],"4:3");
	copystring(CmdDesc[n].FParamEnum[1][1],"1:1");

		CmdDesc[n].FRoutine=SetPrj;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ZtoTexture");
	copystring(CmdDesc[n].FParamName[1],"target"); 
	copystring(CmdDesc[n].FParamEnum[1][1],"texture");
	copystring(CmdDesc[n].FParamEnum[1][0],"screen");
	copystring(CmdDesc[n].FParamName[2],"texture");
		CmdDesc[n].FRoutine=ZtoScreen;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"String");
	copystring(CmdDesc[n].FParamName[1],"len"); 
	copystring(CmdDesc[n].FParamName[2],"freq"); 
	copystring(CmdDesc[n].FParamName[3],"demp"); 
	copystring(CmdDesc[n].FParamName[4],"rand"); 
	copystring(CmdDesc[n].FParamName[5],"hard"); 
	copystring(CmdDesc[n].FParamName[6],"amp"); 
		CmdDesc[n].FRoutine=String_snd;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Sequence");
	copystring(CmdDesc[n].FParamName[1],"lenght"); 
	copystring(CmdDesc[n].FParamName[2],"channels"); 
	copystring(CmdDesc[n].FParamName[3],"major hilight"); 
	copystring(CmdDesc[n].FParamName[4],"minor hilight"); 
		CmdDesc[n].FRoutine=Sequence;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Channel");
		CmdDesc[n].FRoutine=Channel;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		trk_channelcmd=n;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"         ");
	copystring(CmdDesc[n].FParamName[1],"n"); 
	copystring(CmdDesc[n].FParamName[2],"velocity"); 
	CmdDesc[n].FRoutine=Note;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		trk_notecmd=n;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"StoreSequence");
	copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=StoreSequence;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"PlaySequence");
	copystring(CmdDesc[n].FParamName[1],"n"); 
	copystring(CmdDesc[n].FParamName[2],"x"); 
	copystring(CmdDesc[n].FParamName[3],"y"); 
	copystring(CmdDesc[n].FParamName[4],"width"); 
	//copystring(CmdDesc[n].FParamName[5],"start note"); 
		CmdDesc[n].FRoutine=PlaySequence;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"EndSequence");
		CmdDesc[n].FRoutine=EndSequence;
		CmdDesc[n].FCategory=IDC_TRACK;
		CmdDesc[n].FLevel=1;
		trk_endseqcmd=n;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"FBDistort");
	copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=FBDistort;
		CmdDesc[n].FCategory=IDC_DYNA;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Reverb2");
	copystring(CmdDesc[n].FParamName[1],"delay"); 
	copystring(CmdDesc[n].FParamName[2],"decay"); 
	copystring(CmdDesc[n].FParamName[3],"copies"); 
	copystring(CmdDesc[n].FParamName[4],"inter_amp"); 
	copystring(CmdDesc[n].FParamName[5],"inter_speed"); 
		CmdDesc[n].FRoutine=Reverb2;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"EQ2"); 
	copystring(CmdDesc[n].FParamName[1],"400");
	copystring(CmdDesc[n].FParamName[2],"1200");
	copystring(CmdDesc[n].FParamName[3],"2400");
	copystring(CmdDesc[n].FParamName[4],"4800");
	copystring(CmdDesc[n].FParamName[5],"8700");
	copystring(CmdDesc[n].FParamName[6],"16500");
		CmdDesc[n].FRoutine=EQ2;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"pEQ"); 
	copystring(CmdDesc[n].FParamName[1],"freq");
	copystring(CmdDesc[n].FParamName[2],"q");
	copystring(CmdDesc[n].FParamName[3],"gain");
		CmdDesc[n].FRoutine=pEQ;
		CmdDesc[n].FCategory=IDC_SFILTERS;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ZWriteMod"); 
	copystring(CmdDesc[n].FParamName[1],"mode"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"disable");
			copystring(CmdDesc[n].FParamEnum[1][1],"enable");
		CmdDesc[n].FRoutine=ZWriteMod;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Posterize"); 
	copystring(CmdDesc[n].FParamName[1],"levels"); 
	copystring(CmdDesc[n].FParamName[2],"gamma"); 
		CmdDesc[n].FRoutine=Posterize;
		CmdDesc[n].FCategory=IDC_FILTERS;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CopyStartScr"); 
	copystring(CmdDesc[n].FParamName[1],"texture"); 
		CmdDesc[n].FRoutine=CopyStartScr;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Subdivide"); 
	copystring(CmdDesc[n].FParamName[1],"iterations"); 
	copystring(CmdDesc[n].FParamName[2],"smooth"); 
			copystring(CmdDesc[n].FParamEnum[2][0],"disable");
			copystring(CmdDesc[n].FParamEnum[2][1],"enable");
		CmdDesc[n].FRoutine=Subdivide;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Smooth");
	copystring(CmdDesc[n].FParamName[1],"iterations");
		CmdDesc[n].FRoutine=Smooth;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SelectG_cube"); 
	copystring(CmdDesc[n].FParamName[1],"type");
			copystring(CmdDesc[n].FParamEnum[1][0],"set select");
			copystring(CmdDesc[n].FParamEnum[1][1],"add select");
			copystring(CmdDesc[n].FParamEnum[1][2],"subtract select");
	copystring(CmdDesc[n].FParamName[2],"x");	
	copystring(CmdDesc[n].FParamName[3],"y");
	copystring(CmdDesc[n].FParamName[4],"z");
	copystring(CmdDesc[n].FParamName[5],"xsize");
	copystring(CmdDesc[n].FParamName[6],"ysize");
	copystring(CmdDesc[n].FParamName[7],"zsize");
	copystring(CmdDesc[n].FParamName[8],"q");
	copystring(CmdDesc[n].FParamName[9],"func");
			copystring(CmdDesc[n].FParamEnum[9][0],"linear");
			copystring(CmdDesc[n].FParamEnum[9][1],"sin");
			copystring(CmdDesc[n].FParamEnum[9][2],"exp");
			copystring(CmdDesc[n].FParamEnum[9][3],"hard");
		CmdDesc[n].FRoutine=SelectG_Cube;
		CmdDesc[n].FCategory=IDC_SELECTION;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CopyUVtoUV1"); 
		CmdDesc[n].FRoutine=CopyUVtoUV1;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"XYZtoUV"); 
	copystring(CmdDesc[n].FParamName[1],"stage");
	copystring(CmdDesc[n].FParamName[2],"scale u");
	copystring(CmdDesc[n].FParamName[3],"scale v");
	copystring(CmdDesc[n].FParamName[4],"type");
			copystring(CmdDesc[n].FParamEnum[4][0],"xy");
			copystring(CmdDesc[n].FParamEnum[4][1],"xz");
			copystring(CmdDesc[n].FParamEnum[4][2],"yz");

		CmdDesc[n].FRoutine=XYZtoUV;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SXYtoUV"); 
	copystring(CmdDesc[n].FParamName[1],"stage");
	copystring(CmdDesc[n].FParamName[2],"scale u");
	copystring(CmdDesc[n].FParamName[3],"scale v");
	copystring(CmdDesc[n].FParamName[4],"type");
			copystring(CmdDesc[n].FParamEnum[4][0],"xy");
			copystring(CmdDesc[n].FParamEnum[4][1],"xz");
			copystring(CmdDesc[n].FParamEnum[4][2],"yz");

		CmdDesc[n].FRoutine=SXYtoUV;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SinWaves"); 
	copystring(CmdDesc[n].FParamName[1],"amp");
	copystring(CmdDesc[n].FParamName[2],"freq");
	copystring(CmdDesc[n].FParamName[3],"x");
	copystring(CmdDesc[n].FParamName[4],"y");
	copystring(CmdDesc[n].FParamName[5],"type");
			copystring(CmdDesc[n].FParamEnum[5][0],"xy");
			copystring(CmdDesc[n].FParamEnum[5][1],"radial");
	copystring(CmdDesc[n].FParamName[6],"f");
	copystring(CmdDesc[n].FParamName[7],"abs");
			copystring(CmdDesc[n].FParamEnum[7][0],"off");
			copystring(CmdDesc[n].FParamEnum[7][1],"on");

		CmdDesc[n].FRoutine=SinWaves;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"AddPerlinH"); 
		copystring(CmdDesc[n].FParamName[1],"x");
		copystring(CmdDesc[n].FParamName[2],"y");
		copystring(CmdDesc[n].FParamName[3],"z");
		copystring(CmdDesc[n].FParamName[4],"amp");
		copystring(CmdDesc[n].FParamName[5],"o1");
		copystring(CmdDesc[n].FParamName[6],"o2");
		copystring(CmdDesc[n].FParamName[7],"o3");
		copystring(CmdDesc[n].FParamName[8],"o4");
		copystring(CmdDesc[n].FParamName[9],"o5");
		copystring(CmdDesc[n].FParamName[10],"o6");
		copystring(CmdDesc[n].FParamName[11],"o7");
		copystring(CmdDesc[n].FParamName[12],"o8");
		CmdDesc[n].FRoutine=AddPerlinH;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CompileShaderToSlot");
		copystring(CmdDesc[n].FParamName[1],"slot");
		CmdDesc[n].FRoutine=CompileShaderToSlot;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
	CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"IrregularGrid");
		copystring(CmdDesc[n].FParamName[1],"n");
		CmdDesc[n].FRoutine=IrregularGrid;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
	CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"CreateMipMaps");
		CmdDesc[n].FRoutine=CreateMipMaps;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
	CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"RotateCamera");
		copystring(CmdDesc[n].FParamName[1],"Yaw");
		copystring(CmdDesc[n].FParamName[2],"Pitch");
		copystring(CmdDesc[n].FParamName[3],"Roll");
		CmdDesc[n].FRoutine=RotateCamera;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
	CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"ShowVBsMap3D"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"blend"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[4][4],"min");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");
			copystring(CmdDesc[n].FParamEnum[4][6],"alpha");

		copystring(CmdDesc[n].FParamName[5],"count"); 
		copystring(CmdDesc[n].FParamName[6],"rndXamp"); 
		copystring(CmdDesc[n].FParamName[7],"rndYamp"); 
		copystring(CmdDesc[n].FParamName[8],"rndZamp"); 
		copystring(CmdDesc[n].FParamName[9],"Xspd"); 
		copystring(CmdDesc[n].FParamName[10],"Yspd"); 
		copystring(CmdDesc[n].FParamName[11],"Zspd"); 
		copystring(CmdDesc[n].FParamName[12],"Yaw spd"); 
		copystring(CmdDesc[n].FParamName[13],"Pitch spd"); 
		copystring(CmdDesc[n].FParamName[14],"Roll spd"); 
		copystring(CmdDesc[n].FParamName[15],"Target material 1"); 
		copystring(CmdDesc[n].FParamName[16],"Target material 2"); 
		copystring(CmdDesc[n].FParamName[17],"material speed"); 
		copystring(CmdDesc[n].FParamName[18],"int.count"); 
		copystring(CmdDesc[n].FParamName[19],"posbuffer"); 
	

		CmdDesc[n].FRoutine=ShowVBsMap3D;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

		copystring(CmdDesc[n].FName,"CopyObjToPosBuf"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
			copystring(CmdDesc[n].FParamName[2],"offset"); 
		copystring(CmdDesc[n].FParamName[2],"start offset"); 
		copystring(CmdDesc[n].FParamName[3],"end offset"); 
		copystring(CmdDesc[n].FParamName[4],"skip"); 

		CmdDesc[n].FRoutine=CopyObjToPosBuf;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;


		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"XYZ by Curve"); 
	copystring(CmdDesc[n].FParamName[1],"n");
		CmdDesc[n].FRoutine=Loft;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Set VBs Head"); 
	copystring(CmdDesc[n].FParamName[1],"vb n");
	copystring(CmdDesc[n].FParamName[2],"texture");
	copystring(CmdDesc[n].FParamName[3],"material");
	copystring(CmdDesc[n].FParamName[4],"extract pos only");
		copystring(CmdDesc[n].FParamEnum[4][0],"no");
		copystring(CmdDesc[n].FParamEnum[4][1],"yes");
		CmdDesc[n].FRoutine=SetVBsHead;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"PinkNoise"); 
	copystring(CmdDesc[n].FParamName[1],"amp");
		CmdDesc[n].FRoutine=PinkNoise;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Carplus"); 
	copystring(CmdDesc[n].FParamName[1],"freq");
	copystring(CmdDesc[n].FParamName[2],"feedback");
	copystring(CmdDesc[n].FParamName[3],"operation");
		copystring(CmdDesc[n].FParamEnum[3][0],"minus");
		copystring(CmdDesc[n].FParamEnum[3][1],"plus");
		CmdDesc[n].FRoutine=oscx;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"Reverse"); 
		CmdDesc[n].FRoutine=Reverse;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"Tree"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"zsize"); 
		copystring(CmdDesc[n].FParamName[7],"texture"); 
		copystring(CmdDesc[n].FParamName[8],"Material"); 
		copystring(CmdDesc[n].FParamName[9],"Greed x"); 
		copystring(CmdDesc[n].FParamName[10],"Greed y"); 
		copystring(CmdDesc[n].FParamName[11],"blend"); 
			copystring(CmdDesc[n].FParamEnum[11][0],"none");
			copystring(CmdDesc[n].FParamEnum[11][1],"add");
			copystring(CmdDesc[n].FParamEnum[11][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[11][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[11][4],"min");
			copystring(CmdDesc[n].FParamEnum[11][5],"max");
			copystring(CmdDesc[n].FParamEnum[11][6],"alpha");
		copystring(CmdDesc[n].FParamName[12],"divide N"); 
		copystring(CmdDesc[n].FParamName[13],"divide rnd"); 
		copystring(CmdDesc[n].FParamName[14],"rotate"); 
		copystring(CmdDesc[n].FParamName[15],"rand H"); 
		copystring(CmdDesc[n].FParamName[16],"gravity"); 
		copystring(CmdDesc[n].FParamName[17],"angle"); 
		copystring(CmdDesc[n].FParamName[18],"angle_p"); 
		copystring(CmdDesc[n].FParamName[19],"breaks"); 
		copystring(CmdDesc[n].FParamName[20],"la"); 

		CmdDesc[n].FRoutine=Tree;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"LoftW"); 
	copystring(CmdDesc[n].FParamName[1],"w"); 
	copystring(CmdDesc[n].FParamName[2],"w"); 
	copystring(CmdDesc[n].FParamName[3],"w"); 
	copystring(CmdDesc[n].FParamName[4],"w"); 
	copystring(CmdDesc[n].FParamName[5],"w"); 
	copystring(CmdDesc[n].FParamName[6],"w"); 
	copystring(CmdDesc[n].FParamName[7],"w"); 
	copystring(CmdDesc[n].FParamName[8],"w"); 
	copystring(CmdDesc[n].FParamName[9],"w"); 
	copystring(CmdDesc[n].FParamName[10],"w"); 
	copystring(CmdDesc[n].FParamName[11],"w"); 
	copystring(CmdDesc[n].FParamName[12],"w"); 
	copystring(CmdDesc[n].FParamName[13],"w"); 
	copystring(CmdDesc[n].FParamName[14],"w"); 
	copystring(CmdDesc[n].FParamName[15],"w"); 
	copystring(CmdDesc[n].FParamName[16],"w"); 
		CmdDesc[n].FRoutine=LoftW;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoftY"); 
	copystring(CmdDesc[n].FParamName[1],"h"); 
	copystring(CmdDesc[n].FParamName[2],"h"); 
	copystring(CmdDesc[n].FParamName[3],"h"); 
	copystring(CmdDesc[n].FParamName[4],"h"); 
	copystring(CmdDesc[n].FParamName[5],"h"); 
	copystring(CmdDesc[n].FParamName[6],"h"); 
	copystring(CmdDesc[n].FParamName[7],"h"); 
	copystring(CmdDesc[n].FParamName[8],"h"); 
	copystring(CmdDesc[n].FParamName[9],"h"); 
	copystring(CmdDesc[n].FParamName[10],"h"); 
	copystring(CmdDesc[n].FParamName[11],"h"); 
	copystring(CmdDesc[n].FParamName[12],"h"); 
	copystring(CmdDesc[n].FParamName[13],"h"); 
	copystring(CmdDesc[n].FParamName[14],"h"); 
	copystring(CmdDesc[n].FParamName[15],"h"); 
	copystring(CmdDesc[n].FParamName[16],"h"); 
		CmdDesc[n].FRoutine=LoftY;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"LoadWave");  
		CmdDesc[n].FRoutine=LoadWave;
		CmdDesc[n].FCategory=IDC_SND;
		CmdDesc[n].FLevel=1;
		copystring(CmdDesc[n].FParamName[1],"w"); 
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"TRotate"); 
		copystring(CmdDesc[n].FParamName[1],"a"); 
		copystring(CmdDesc[n].FParamName[2],"stage"); 
		CmdDesc[n].FRoutine=TRotate;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		
		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"TZoom"); 
		copystring(CmdDesc[n].FParamName[1],"u"); 
		copystring(CmdDesc[n].FParamName[2],"v"); 
		copystring(CmdDesc[n].FParamName[3],"stage"); 
		CmdDesc[n].FRoutine=TZoom;
		CmdDesc[n].FCategory=IDC_UV;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"CreateShader"); 
		copystring(CmdDesc[n].FParamName[1],"target slot"); 
		CmdDesc[n].FRoutine=CreateShader;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize+65536;
		n++;

	copystring(CmdDesc[n].FName,"ApplyShader"); 
		copystring(CmdDesc[n].FParamName[1],"shader"); 
		CmdDesc[n].FRoutine=ApplyShader;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		ApplyShaderIndex=n;
		n++;

	copystring(CmdDesc[n].FName,"ApplyMaterial"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		CmdDesc[n].FRoutine=ApplyMaterial;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;

	copystring(CmdDesc[n].FName,"ShFogSetup"); 
		copystring(CmdDesc[n].FParamName[1],"start"); 
		copystring(CmdDesc[n].FParamName[2],"end"); 
		copystring(CmdDesc[n].FParamName[3],"r"); 
		copystring(CmdDesc[n].FParamName[4],"g"); 
		copystring(CmdDesc[n].FParamName[5],"b");
		copystring(CmdDesc[n].FParamName[6],"a");
		copystring(CmdDesc[n].FParamName[7],"vstart"); 
		copystring(CmdDesc[n].FParamName[8],"vend"); 
		copystring(CmdDesc[n].FParamName[9],"r"); 
		copystring(CmdDesc[n].FParamName[10],"g"); 
		copystring(CmdDesc[n].FParamName[11],"b"); 
		copystring(CmdDesc[n].FParamName[12],"a"); 
		CmdDesc[n].FRoutine=ShFogSetup;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;
		n++;

	copystring(CmdDesc[n].FName,"SetTextureForVS"); 
		copystring(CmdDesc[n].FParamName[1],"sampler"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		CmdDesc[n].FRoutine=SetTextureForVS;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;

		copystring(CmdDesc[n].FName,"ShaderPost"); 
		copystring(CmdDesc[n].FParamName[1],"shader"); 
		CmdDesc[n].FRoutine=ShaderPost;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;
		ShaderPostIndex=n;
		n++;	

		copystring(CmdDesc[n].FName,"ShowObjFromTexture"); 
		copystring(CmdDesc[n].FParamName[1],"greed x"); 
		copystring(CmdDesc[n].FParamName[2],"greed y"); 
		copystring(CmdDesc[n].FParamName[3],"h loop");
			copystring(CmdDesc[n].FParamEnum[3][0],"off");
			copystring(CmdDesc[n].FParamEnum[3][1],"on");
		copystring(CmdDesc[n].FParamName[4],"w loop"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"off");
			copystring(CmdDesc[n].FParamEnum[4][1],"on");
		copystring(CmdDesc[n].FParamName[5],"source texture"); 
		CmdDesc[n].FRoutine=ShowObjFromTexture;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;
		
		n++;	


		copystring(CmdDesc[n].FName,"CameraFromLight"); 
		copystring(CmdDesc[n].FParamName[1],"light"); 
		CmdDesc[n].FRoutine=CameraFromLight;
		CmdDesc[n].FCategory=IDC_CAM;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;
		
		n++;



		copystring(CmdDesc[n].FName,"OverrideShader"); 
		copystring(CmdDesc[n].FParamName[1],"enable"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"off");
			copystring(CmdDesc[n].FParamEnum[1][1],"on");
		copystring(CmdDesc[n].FParamName[2],"n"); 
		CmdDesc[n].FRoutine=OverrideShader;
		CmdDesc[n].FCategory=IDC_CMD;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;
		
		n++;

		copystring(CmdDesc[n].FName,"Animate"); 
		copystring(CmdDesc[n].FParamName[1],"func"); 
			copystring(CmdDesc[n].FParamEnum[1][0],"off");
			copystring(CmdDesc[n].FParamEnum[1][1],"curve");
			copystring(CmdDesc[n].FParamEnum[1][2],"sin");
		copystring(CmdDesc[n].FParamName[2],"param n"); 
		copystring(CmdDesc[n].FParamName[3],"freq"); 
		copystring(CmdDesc[n].FParamName[4],"amp"); 
		copystring(CmdDesc[n].FParamName[5],"phase"); 
		copystring(CmdDesc[n].FParamName[6],"global time"); 
			copystring(CmdDesc[n].FParamEnum[6][0],"off");
			copystring(CmdDesc[n].FParamEnum[6][1],"on");
		copystring(CmdDesc[n].FParamName[7],"loop count"); 
		copystring(CmdDesc[n].FParamName[8],"loop start"); 
		copystring(CmdDesc[n].FParamName[9],"loop end"); 
		CmdDesc[n].FRoutine=Animate;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		
		n++;

		copystring(CmdDesc[n].FName,"Key"); 
		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"weight"); 
		copystring(CmdDesc[n].FParamName[4],"p weight"); 
		copystring(CmdDesc[n].FParamName[5],"n weight"); 
		CmdDesc[n].FRoutine=Key;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;

		copystring(CmdDesc[n].FName,"SetPPrj"); 
		copystring(CmdDesc[n].FParamName[1],"t"); 
		CmdDesc[n].FRoutine=SetPPrj;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;

		copystring(CmdDesc[n].FName,"keyLoop"); 
		copystring(CmdDesc[n].FParamName[1],"count"); 
		CmdDesc[n].FRoutine=keyLoop;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;
		
		copystring(CmdDesc[n].FName,"keyLoopEnd"); 
		CmdDesc[n].FRoutine=keyLoopEnd;
		CmdDesc[n].FCategory=IDC_ANIMA;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;
		n++;

		copystring(CmdDesc[n].FName,"rawTriangles"); 
		CmdDesc[n].FRoutine=RawTriangles;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;
		CmdDesc[n].FSize=CellSize;

		copystring(CmdDesc[n].FParamName[1],"x"); 
		copystring(CmdDesc[n].FParamName[2],"y"); 
		copystring(CmdDesc[n].FParamName[3],"z"); 
		copystring(CmdDesc[n].FParamName[4],"xsize"); 
		copystring(CmdDesc[n].FParamName[5],"ysize"); 
		copystring(CmdDesc[n].FParamName[6],"texture"); 
		copystring(CmdDesc[n].FParamName[7],"Material"); 
		copystring(CmdDesc[n].FParamName[8],"blend"); 
			copystring(CmdDesc[n].FParamEnum[8][0],"none");
			copystring(CmdDesc[n].FParamEnum[8][1],"add");
			copystring(CmdDesc[n].FParamEnum[8][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[8][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[8][4],"min");
			copystring(CmdDesc[n].FParamEnum[8][5],"max");
			copystring(CmdDesc[n].FParamEnum[8][6],"alpha");
		copystring(CmdDesc[n].FParamName[9],"tsize"); 
		n++;

	copystring(CmdDesc[n].FName,"ShowVBsIsolated"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"blend"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[4][4],"min");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");
			copystring(CmdDesc[n].FParamEnum[4][6],"alpha");

		copystring(CmdDesc[n].FParamName[5],"count"); 
		copystring(CmdDesc[n].FParamName[6],"rndXamp"); 
		copystring(CmdDesc[n].FParamName[7],"rndYamp"); 
		copystring(CmdDesc[n].FParamName[8],"rndZamp"); 
		copystring(CmdDesc[n].FParamName[9],"Xspd"); 
		copystring(CmdDesc[n].FParamName[10],"Yspd"); 
		copystring(CmdDesc[n].FParamName[11],"Zspd"); 
		copystring(CmdDesc[n].FParamName[12],"Yaw spd"); 
		copystring(CmdDesc[n].FParamName[13],"Pitch spd"); 
		copystring(CmdDesc[n].FParamName[14],"Roll spd"); 
		copystring(CmdDesc[n].FParamName[15],"Target material 1"); 
		copystring(CmdDesc[n].FParamName[16],"Target material 2"); 
		copystring(CmdDesc[n].FParamName[17],"material speed"); 


		CmdDesc[n].FRoutine=ShowVBsIsolated;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;




	copystring(CmdDesc[n].FName,"ShowVBsL"); 
		copystring(CmdDesc[n].FParamName[1],"n"); 
		copystring(CmdDesc[n].FParamName[2],"texture"); 
		copystring(CmdDesc[n].FParamName[3],"material"); 
		copystring(CmdDesc[n].FParamName[4],"blend"); 
			copystring(CmdDesc[n].FParamEnum[4][0],"none");
			copystring(CmdDesc[n].FParamEnum[4][1],"add");
			copystring(CmdDesc[n].FParamEnum[4][2],"subtract");
			copystring(CmdDesc[n].FParamEnum[4][3],"revsubtract");
			copystring(CmdDesc[n].FParamEnum[4][4],"min");
			copystring(CmdDesc[n].FParamEnum[4][5],"max");
			copystring(CmdDesc[n].FParamEnum[4][6],"alpha");

		copystring(CmdDesc[n].FParamName[5],"count"); 
		copystring(CmdDesc[n].FParamName[6],"rndXamp"); 
		copystring(CmdDesc[n].FParamName[7],"rndYamp"); 
		copystring(CmdDesc[n].FParamName[8],"rndZamp"); 
		copystring(CmdDesc[n].FParamName[9],"Xspd"); 
		copystring(CmdDesc[n].FParamName[10],"Yspd"); 
		copystring(CmdDesc[n].FParamName[11],"Zspd"); 
		copystring(CmdDesc[n].FParamName[12],"Yaw spd"); 
		copystring(CmdDesc[n].FParamName[13],"Pitch spd"); 
		copystring(CmdDesc[n].FParamName[14],"Roll spd"); 
		copystring(CmdDesc[n].FParamName[15],"Target material 1"); 
		copystring(CmdDesc[n].FParamName[16],"Target material 2"); 
		copystring(CmdDesc[n].FParamName[17],"x"); 
		copystring(CmdDesc[n].FParamName[18],"y"); 
		copystring(CmdDesc[n].FParamName[19],"z"); 
		copystring(CmdDesc[n].FParamName[20],"treshold"); 


		CmdDesc[n].FRoutine=ShowVBsL;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"IndexedIoIsolated"); 
		CmdDesc[n].FRoutine=IndexedIoIsolated;
		CmdDesc[n].FCategory=IDC_3D;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;


	copystring(CmdDesc[n].FName,"texToRam"); 
	copystring(CmdDesc[n].FParamName[1],"srcTex"); 
		CmdDesc[n].FRoutine=TexToRam;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"MakeInstTable"); 
	copystring(CmdDesc[n].FParamName[1],"channelXZ"); 
		copystring(CmdDesc[n].FParamEnum[1][0],"b");
		copystring(CmdDesc[n].FParamEnum[1][1],"g");
		copystring(CmdDesc[n].FParamEnum[1][2],"r");
		copystring(CmdDesc[n].FParamEnum[1][3],"a");
	copystring(CmdDesc[n].FParamName[2],"key"); 
	copystring(CmdDesc[n].FParamName[3],"channelY"); 
		copystring(CmdDesc[n].FParamEnum[3][0],"b");
		copystring(CmdDesc[n].FParamEnum[3][1],"g");
		copystring(CmdDesc[n].FParamEnum[3][2],"r");
		copystring(CmdDesc[n].FParamEnum[3][3],"a");
	copystring(CmdDesc[n].FParamName[4],"outBufN"); 
		CmdDesc[n].FRoutine=MakeInstTable;
		CmdDesc[n].FCategory=IDC_TC;
		CmdDesc[n].FLevel=1;

		CmdDesc[n].FSize=CellSize;n++;

	copystring(CmdDesc[n].FName,"SetScatter"); 
	copystring(CmdDesc[n].FParamName[1],"posbufN"); 
	copystring(CmdDesc[n].FParamName[2],"scaleX"); 
	copystring(CmdDesc[n].FParamName[3],"scaleY"); 
	copystring(CmdDesc[n].FParamName[4],"scaleZ"); 
		CmdDesc[n].FRoutine=SetScatter;
		CmdDesc[n].FCategory=IDC_XYZ;
		CmdDesc[n].FLevel=2;
		CmdDesc[n].FSize=CellSize;n++;


		CommandsCount=n;



}





#ifndef EditMode
#include "reused.h"
#endif