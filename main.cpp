#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <string.h>
#include "stdafx.h"

#define EditMode

#include "resource.h"
#include <math.h>
//#define D3D_DEBUG_INFO

#include <d3d9.h>
#include <d3dx9.h>

int record=0;

#ifdef EditMode 
	int astate=-1;//start-stop anim

	int camstate=-1;//cam
	int cursor_y;
#else
	int astate=1;//start-stop anim

	int camstate=1;//cam

#endif 

HINSTANCE hInst;
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
#define MAX_LOADSTRING 100
#define PI 3.1415926535897932384626433832795

char cdir[1000];

HWND hWndView;
HWND hWnd0;
HWND hWnd1;

int snd_samplesize=44100;
int snd_samplesize_old=44100;
const int snd_maxsamplesize=44100*8;
BYTE* snd_mem;
BYTE* snd_tmp;
BYTE* snd_pool;
BYTE* snd_bank;
BYTE* snd_xm;

BYTE* patterns;


#ifdef EditMode
BYTE* WaveBuffer;
int useWave=0;
#endif

double fp_delta;



#include "soundinit.h"
void CreateShaders();

const int EntriesCount=10000;//max command stack size
HDC hdcCompatible;//for startscreen
int CPos=0;int Cfn=0;//current execution position
int ScenePos;
int LoopPoint=0;
int PrecalcStatus=0;
int CommandsCount=0; //number of available commands
int CellSize=256;//one command size

BYTE* Pack;//main command stack storage
BYTE* Exchange;//second storage for animation and editing operations
BYTE* Exchange2;//second storage for animation and editing operations
BYTE* RExchange;//storage exchanger pointer

//command struct
typedef void (*PVFN)();//func pointer type for commands
PVFN CurrentCmd0,CurrentCmd1,CurrentCmd2;
typedef struct 
	{
	char FName[32]; 
	int FLevel; 
	char FParamName[32][256];
	int FParamMin[32];
	int FParamMax[32];
	int FParamDefault[32];
	char FParamEnum[32][64][32];
	int FCategory;
	int FSize;
	PVFN FRoutine;//указатель на функцию
	} Cmd;

Cmd CmdDesc[512];

int stack[1000];//scene-calling stack
int stackpos;//scene-calling stack position

//basic commandstack i/o
void nPut(int ofs,short Value)
{
   *(short*)(Pack+ofs)=Value;
}


short nGet(int ofs)
{
short a;
//a=*(short*)(Pack+c*CellSize+p*2);

BYTE* addr; 
addr=Pack+ofs;

_asm{
	mov edx,addr
	mov ax,[edx]
	mov a,ax
	}

   return a;
}

void Put(int c, int p,short Value)
{

 //  *(short*)(Pack+c*CellSize+p*2)=Value;

     *(short*)(Pack+c+p*2)=Value;
}

short Get(int c,int p)
{
short a;
//a=*(short*)(Pack+c*CellSize+p*2);

BYTE* addr;
//addr=Pack+c*CellSize+p*2;
addr=Pack+c+p*2;

_asm{
	mov edx,addr
	mov ax,[edx]
	mov a,ax
	}

   return a;
}

void Put32(int c, int p,int Value)
{
   *(long*)(Pack+c*CellSize+p*4)=Value;
}

int Get32(int c,int p)
{
   return *(long*)(Pack+c*CellSize+p*4);
}


double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li)) MessageBox(hWndView,"timer fail",NULL,0);
//	cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}


double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}


//_int64 ptime;//global time
double ptime;//global time
double gtime;//global time for timeliner
double prevtick;//fps holder
double start_time;
double start_ptime;

ID3DXConstantTable* pCt = 0;//for v shaders
ID3DXConstantTable* pCt2 = 0;
ID3DXConstantTable* pCt3 = 0;
ID3DXConstantTable* pCtC[64];
ID3DXConstantTable* pCtCp[64];

#ifdef EditMode
#include "gui/navi_init.h"//must be removed in runtime
#endif


#include "dxinit.h"
#include "shaders.h"
#include "camera.h"
#include "!normals.h"
#include "commands.h"
#include "render.h"
#include "cmdinit.h"

#ifdef EditMode
#include "gui/navi.h"//must be removed in runtime
#endif

#include "gui/mainwindow.h" //main window operaqtions 




int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
for (int c=0;c<200;c++)curvearray_clen[c]=0;
	MSG msg;
	msg.message=NULL;

	hInstance = (HINSTANCE)GetModuleHandle(0);
	MyRegisterClass(hInstance);

	//startscreen commented for faster start
	HDC hdcScreen = CreateDC("DISPLAY", NULL, NULL, NULL); 
	int w=GetDeviceCaps(hdcScreen, HORZRES);
	int h=GetDeviceCaps(hdcScreen, VERTRES);
	hdcCompatible = CreateCompatibleDC(hdcScreen); 
	HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen,w,h); 
	SelectObject(hdcCompatible, hbmScreen);
	BitBlt(hdcCompatible,0,0,w,h,hdcScreen,0,0,SRCCOPY);
	

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) return FALSE;

	StartCounter();
//	timeBeginPeriod(1);

  while(msg.message!=WM_QUIT)
  {

	if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
      if(GetMessage(&msg, NULL, 0, 0))
      {
		{
        //TranslateMessage(&msg);
        //DispatchMessage(&msg);
		}
      }
#ifdef EditMode
	if (!IsDialogMessage(Navi2, &msg))
#endif
		{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
		}
    }
    else
	{
		double a;
		//timeBeginPeriod(1);
		//a=GetTickCount();
		//a=TimeGetTime(
#ifndef EditMode

			int ord = FMUSIC_GetOrder(mod);
			int row = FMUSIC_GetRow(mod);
			if (ord>=22&&row>60) goto exitprogramm;
		
			if (!windowed) SetCursor(NULL);
#endif


		a=GetCounter();
		fp_delta=a-prevtick;

//		ProcessSoundTimeline(a,fp_delta);

		if ((fp_delta)>(1000.0/60.0))
		{
			prevtick=a;
			DrawScene();

			
		}
	}
  }
exitprogramm:;

  FMUSIC_FreeSong(mod);
  ReleaseD3D();
	
  return msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;

	
#ifdef EditMode
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI__POINTENGINE);
#else
	wcex.hIcon			= NULL;
#endif
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);

	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.hbrBackground	= (HBRUSH)(COLOR_DESKTOP);
#ifdef EditMode
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_MAINMENU);;
#endif
	wcex.lpszClassName	= "P4";
#ifdef EditMode
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
#else 
	wcex.hIconSm		= NULL;

#endif
	/*

	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI__POINTENGINE);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_DESKTOP);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDR_MAINMENU);;
	wcex.lpszClassName	= "P4";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);
*/
	return RegisterClassEx(&wcex);
}

#ifndef EditMode


void LoadTemplate()
{
	char* tmpstr;
	char* cdir2;
	char* cdir;
	tmpstr=new char[255];
	cdir2=new char[255];
	cdir=new char[255];
	char* i;strcpy(tmpstr,GetCommandLine());
	strcpy(cdir2,GetCommandLine());//строка для регистрации в реестре
	i=strstr(tmpstr,".exe");while (*(i)!='\\') i--;*(i+1)=0;//отрезаем лишнее
	strcpy(cdir,tmpstr+1);
			//return;
				//CleanProject();

				SetCurrentDirectory(cdir);
				PrecalcStatus=0;LoopPoint=0;
				FILE *fp;
				fp = fopen("empty.p4p", "rb");
				fread(Pack,1,CellSize*EntriesCount,fp);
				fclose(fp);
//				ShowParam();

}
#endif

BOOL CALLBACK StartProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	 switch( msg )
	 {
	 case WM_INITDIALOG:
		 {
			 break;
		 }
	 case WM_COMMAND:
		 {
			switch (LOWORD(wParam))
			{
			case ID1024W:
				{
				screen_width=1280;screen_height=768;
				screen_ratio=screen_width/screen_height;
				windowed=TRUE;
				EndDialog(hDlg,TRUE);
				break;
				}
			
			case ID1024FS:
				{
				screen_width=1280;screen_height=768;
				screen_ratio=screen_width/screen_height;
				windowed=FALSE;
				EndDialog(hDlg,TRUE);
				break;
				}
			
			case IDFS:
				{
				screen_width=GetSystemMetrics(SM_CXSCREEN);screen_height=GetSystemMetrics(SM_CYSCREEN);
					screen_width=1280;screen_height=768;
				screen_ratio=screen_width/screen_height;
				windowed=FALSE;
				EndDialog(hDlg,TRUE);
				break;
				}
//			case ID_CANCEL:
//				return -100;
			}
		}
	 }
return 0;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

#ifdef EditMode
   hWnd0 = CreateWindow("P4", "FxEngine Alpha", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU |WS_CLIPCHILDREN ,
      0,0, CW_USEDEFAULT, 0, NULL, 0, hInstance, NULL);

   
   hWnd1 = CreateWindow("P4", "stack", WS_OVERLAPPED | WS_CAPTION | WS_CHILD | WS_THICKFRAME,
      0,0, 1024, 768, hWnd0, NULL, hInstance, NULL);


   hWndView = CreateWindow("P4", "view", WS_OVERLAPPED | WS_CAPTION | WS_CHILD |WS_SIZEBOX,
      0,0, CW_USEDEFAULT, 0, hWnd0, NULL, hInstance, NULL);


hWnd1=hWnd0;

   ShowWindow(hWnd0,SW_MAXIMIZE);
#endif

#ifndef EditMode

DialogBox(hInst,MAKEINTRESOURCE(IDD_STARTMENU),NULL,StartProc);

/*if (MessageBox(NULL,"Fullscreen?","Select mode",MB_YESNO)==IDYES) 
{
	screen_width=GetSystemMetrics(SM_CXSCREEN);screen_height=GetSystemMetrics(SM_CYSCREEN);
	screen_ratio=screen_width/screen_height;
	windowed=FALSE;
}
else 
{
	screen_width=1024;screen_height=768;
	screen_ratio=screen_width/screen_height;
	windowed=TRUE;
}*/


      hWndView = CreateWindow("P4", "fx engine alpha", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU |WS_CLIPCHILDREN ,
      0,0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	//  DialogBox(hInst,MAKEINTRESOURCE(IDD_STARTMENU),hWndView,StartProc);

#endif

   //ShowWindow(hWnd1,SW_SHOW);


   
   if (!hWndView) return FALSE;

#ifdef EditMode
	SelfLocate();
	SetCurrentDirectory(cdir);
#endif	



   if(!InitD3D(hWndView))
				{
					MessageBox(GetActiveWindow(),"Direct3D9 init error","DX9ENGINE", MB_OK|MB_ICONSTOP);
					PostQuitMessage(0);
				}

#ifdef EditMode
   /*
		SetCurrentDirectory(cdir);
		FILE *fp;
		fp = fopen("shaders.txt", "rb");
		  fseek (fp, 0, SEEK_END);
			int nFileLen = ftell(fp);
			fseek (fp, 0, 0);
		fread(shaderText,1,nFileLen,fp);
		*(shaderText+nFileLen+1)=0;
		fclose(fp);

		shaderTextLen=nFileLen;*/
#else
   /*
		HRSRC		recS;
		HGLOBAL		handleS;
		recS = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW6),"RAW");
		handleS = LoadResource(NULL, recS);
		memcpy(shaderText,LockResource(handleS), SizeofResource(NULL, recS));
		shaderTextLen=SizeofResource(NULL, recS);
		*/
#endif


	FillCmdDesc();//готовим дескрипторы команд
#ifdef EditMode
	NaviInit();//must be removed in runtime
#endif

#ifndef EditMode
		//LoadTemplate();




#endif

			//камера
			src.x=0;src.y=0;src.z=0;
			dst.x=0;dst.y=0;dst.z=1;

	snd_tmp=new BYTE[snd_maxsamplesize*2*2+256];
	//snd_mem=new BYTE[snd_maxsamplesize*2+256];
	snd_mem=new BYTE[44100*60*10*2+256];
#ifdef EditMode
	WaveBuffer=new BYTE[44100*60*10*2*2+256];
#endif
	snd_pool=new BYTE[snd_maxsamplesize*2*2+256];
	snd_bank=new BYTE[snd_maxsamplesize*2*64];
	snd_xm=new BYTE[snd_maxsamplesize*2*64];

	patterns=new BYTE[16*256*20*255];//note sample velocity fx1/a fx2/a fx3/a
					//Ch/len/arg/num of pt
//--------

#ifndef EditMode
//load sound path
HRSRC		rec;
HGLOBAL		handle;
rec = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW2),"RAW");
handle = LoadResource(NULL, rec);
memcpy(Pack,LockResource(handle),SizeofResource(NULL, rec));
//calc samples
DrawScene();

//music loads in command LoadXM

//load visuals
rec = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW1),"RAW");
handle = LoadResource(NULL, rec);
memcpy(Pack,LockResource(handle),SizeofResource(NULL, rec));
PrecalcStatus=0;LoopPoint=0;
DrawScene();//first run - precalc
//start


FMUSIC_PlaySong(mod);
	/*			for (int i=1;i<EntriesCount;i++)
					{
						if (Get(i,0)==0) break;
						if (CmdDesc[Get(i,0)].FRoutine==&TimeCursor) 
						{
						Put(i,1,0);
						*(short*)(RExchange+i*CellSize+1*2)=0;
					//	ShowParam();
						
						break;
						}
					}
*/
//astate=1;
StartCounter();
start_time=GetCounter();
//start_ptime=ptime;


//camstate=1;
SetWindowPos(hWndView,HWND_TOP,(GetSystemMetrics(SM_CXSCREEN)-screen_width)/2,(GetSystemMetrics(SM_CYSCREEN)-screen_height)/2,screen_width,screen_height,SWP_SHOWWINDOW);
SetWindowText(hWndView,(char*)Pack+256-33);
#endif



    return TRUE;
}





