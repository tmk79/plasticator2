


//DirectX init code

#include <commdlg.h>
#include <stdio.h>

float cam_zoom=0;

const int maxtex=59;
int texres=512;
int tex_res[512];
const int maxgridsize=512;

void CaptureScreen();

bool windowed=TRUE;
//bool windowed=FALSE;
//int screen_width;
//int screen_height;

double screen_width=1920;int screen_height=1080;
//double screen_width=1024;int screen_height=768;
//double screen_width=1280;int screen_height=720;

//const double screen_width=1280;int screen_height=1024;
// double screen_width=1680;int screen_height=1024;
float screen_ratio=screen_width/screen_height;

LPDIRECT3DSURFACE9 TT;
LPDIRECT3DTEXTURE9 TTt;

LPDIRECT3DSURFACE9 mainRT;
LPDIRECT3DSURFACE9 zbuf2;
IDirect3DTexture9 *pINTZDST;
//int screen_width=1280;int screen_height=800;
//float screen_ratio=1280.0/800.0;


IDirect3D9 * pD3D;
IDirect3DDevice9 * pDevice;

  D3DMATRIX StartMatrix = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 1, 1,
  };
  
   D3DMATRIX World2 = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 1, 1,
  };

  D3DMATRIX StartViewMatrix = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };

  D3DMATRIX Matrix1 = 
  {
    0, 0, -1, 0,
    0, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 1, 1,
  };

  D3DMATRIX Matrix2 = 
  {
    -1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, -1, 0,
    0, 0, 1, 1,
  };

  D3DMATRIX Matrix3 = 
  {
    0, 0, 1, 0,
    0, 1, 0, 0,
    -1, 0, 0, 0,
    0, 0, 1, 1,
  };

D3DMATRIX Projection;D3DXMATRIX ZoomMatrix;

D3DMATRIX View,View2,View3,World,IView,IWorld,TWorld,TView,m2,ViewCopy;
int ViewCopyF=0;

D3DXMATRIX CMatrix,PMatrix,TempMatrix,AMatrix,LightMatrix;

D3DXMATRIX cam_bank[256];

D3DLIGHT9 Light[256];

IDirect3DVertexBuffer9 * pVB[256];
IDirect3DIndexBuffer9 * pIB[256];

//fp post
IDirect3DVertexBuffer9 * pPVB;
IDirect3DIndexBuffer9 * pPIB;
//
IDirect3DVertexBuffer9 * pTVB;
IDirect3DIndexBuffer9 * pTIB[10];


struct MyVertex {float x, y, z, n1, n2, n3;DWORD color; float u, v,u1,v1,t1,t2,t3,b1,b2,b3;};
//#define D3DFVF_MYVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX0 | D3DFVF_TEX1 | D3DFVF_TEX2 | D3DFVF_TEX3 |D3DFVF_TEX4 )// описание формата вершины для объекта.
#define D3DFVF_MYVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX5 )// описание формата вершины для объекта.

#define D3DFVF_TVERTEX (D3DFVF_XYZ |  D3DFVF_TEX1 )// описание формата вершины для объекта.
struct TVertex {float x, y, z; float u, v;};


BYTE* texture_swp;
BYTE* texture_swp1;

int objposbufX[15][maxgridsize*maxgridsize];
int objposbufY[15][maxgridsize*maxgridsize];
int objposbufZ[15][maxgridsize*maxgridsize];

BYTE* texCopy;

BYTE* qr;

char* shaderText;

char* SSTable;


static MyVertex pVerts[maxgridsize*maxgridsize];
MyVertex pVerts1[maxgridsize*maxgridsize];

TVertex pTVR[512*512*3*2];
unsigned int pTInds[512*512*2*3];

unsigned int pInds[maxgridsize*maxgridsize*2*3];
unsigned int pInds1[maxgridsize*maxgridsize*2*3];

int NumVerts;// количество вершин
int NumTriangles;// количество треугольников
int NumInds;// количество индексов.

int VBNumVerts[256];// количество вершин
int VBNumTriangles[256];// количество треугольников
int VBNumInds[256];// количество индексов.


int maxvb;


D3DMATERIAL9 WhiteMaterial,Material[256],TempMaterial,TempMaterial2; 
int MBankZoom=screen_width*4;

BYTE* font;
BYTE* UnpackedFont;
char FontPTable[256];


D3DLIGHT9 WhiteAmbientLight,SceneLight[8];


LPDIRECT3DTEXTURE9 GuiTex;

LPDIRECT3DTEXTURE9 PrevStageTexture,PrevStageTexture2,PrevStageTexture3;
LPDIRECT3DTEXTURE9 PrevStageTextureLQ,PrevStageTexture2LQ,PrevStageTexture3LQ;
LPDIRECT3DTEXTURE9 PrevStageFp[8];
LPDIRECT3DTEXTURE9 PrevStageTextureHQ,PrevStageTexture2HQ,PrevStageTexture3HQ;
LPDIRECT3DTEXTURE9 PrevStageTextureHQ2,PrevStageTexture2HQ2,PrevStageTexture3HQ2;
LPDIRECT3DTEXTURE9 CStageTexture;

LPDIRECT3DTEXTURE9 TextureStage[256];

LPDIRECT3DTEXTURE9 Scenes[256];

LPDIRECT3DTEXTURE9 Texture[256];
int TextureSize[256];

LPDIRECT3DTEXTURE9 FontTexture;

LPDIRECT3DTEXTURE9 WhiteTexture,NoiseTexture,GradTexture,RGradTexture,IRGradTexture,ISqGradTexture,PlasmTexture,StartScreen;
IDirect3DSurface9 *pTexSurf,*ms;

int AlfaMode=0;

BYTE* textblock;

void UnpackFrom1Bit(BYTE* src,BYTE* dst)
{
	_asm{
		mov esi,src
		mov edi,dst
				
		mov edx,0xffffffff	
		mov ebx,0
		
		mov ecx,16*32 //512 pix for heigth
	lp3:
	
		push ecx
		push edi

		mov ecx,4*16 //64 PIXELS 8 BYTES 1 letter
	lp2:
		push ecx
				mov ecx,8//unpack 1 byte to 8 pix
				mov al,[esi]
			lp:
				shl al,1
				jc pixel
				mov [edi],ebx
				jmp no_pixel
		   pixel:
				mov [edi],edx
		no_pixel:
				add edi,4
				loop lp
				inc esi
		pop ecx
		loop lp2


		pop edi
		add edi,512*4// next string
		pop ecx
		loop lp3

		}
}



void LoadTextureToGPU(BYTE* src,LPDIRECT3DTEXTURE9 texture,short int size,unsigned char type)
{
    D3DLOCKED_RECT tl;
    texture->LockRect(0,&tl,NULL,D3DLOCK_DISCARD);
	for (int y=0;y<size;y++) memcpy ((BYTE*)tl.pBits+y*tl.Pitch,src+y*4*size,size*4);
	texture->UnlockRect(0);
} 



void CreateBaseTextures()
{

qr=new BYTE [256*256];


/*
{
#ifdef EditMode
	FILE* ff;
	ff=fopen("qr.tga","rb");
	if (ff==NULL) MessageBox(hWndView,"qr not loaded",0,0);
	fread(qr,1,256*256,ff);
	fclose(ff);
#else
HRSRC		rec;
HGLOBAL		handle;
rec = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW4),"RAW");
handle = LoadResource(NULL, rec);
memcpy(font,LockResource(handle), SizeofResource(NULL, rec));

#endif
int a=0;
for(int y=0;y<32;y++)
{
	for(int x=0;x<32;x++)
	{
		if (*(BYTE*)(qr+y*32+x+20)<255) {
			objposbufX[a]=x-16;
			objposbufY[a]=y-16;
			objposbufZ[a]=0;
			a++;
			}
	}
}



}*/
//

BYTE *tmp;
tmp=new BYTE [screen_width*screen_width*4];
texture_swp=new BYTE [screen_width*screen_width*4];
texture_swp1=new BYTE [screen_width*screen_width*4];
shaderText=new char[65535];
//------------------------
{
#ifdef EditMode
	FILE* ff;
	ff=fopen("basefont32.wbm","rb");
	if (ff==NULL) MessageBox(hWndView,"font not loaded",0,0);
	fread(font,1,32774,ff);
	fclose(ff);
#else
HRSRC		rec;
HGLOBAL		handle;
rec = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW4),"RAW");
handle = LoadResource(NULL, rec);
memcpy(font,LockResource(handle), SizeofResource(NULL, rec));

#endif

	//if (pDevice->CreateTexture(512,512,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&FontTexture,NULL)!=D3D_OK) MessageBox(hWnd,"font texture creation error",0,0);;
	if (pDevice->CreateTexture(512,512,0,0,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,&FontTexture,NULL)!=D3D_OK) MessageBox(hWndView,"font texture creation error",0,0);;  
	
	UnpackFrom1Bit(font+5,tmp);

//calc widths
int cw,ofsx,ofsy,t;
t=0;

for (ofsx=0;ofsx<16;ofsx++)
{
for (ofsy=0;ofsy<16;ofsy++)
	{
	cw=0;
		for (int y=0;y<32;y++)
		{
			for (int x=32;x>=0;x--)
			{
				if (*(BYTE*)(tmp+(y+ofsy*32)*512*4+x*4+ofsx*4*32)!=0&&x>cw) {cw=x;goto k;}
			}
			k:;
		}
	FontPTable[t]=cw;
	if (cw==0) FontPTable[t]=24;
	
	char* s;
	s=new char[11];
	_itoa(FontPTable[t],s,10);
	//MessageBox (Navi,s,0,0);
	
	
	t++;
	}

}

//
	LoadTextureToGPU(tmp,FontTexture,512,0);

}

//-----------------------
int fs=32;
for (int fn=0;fn<8;fn++)
{
pDevice->CreateTexture(fs,fs,0,D3DUSAGE_RENDERTARGET,D3DFMT_A32B32G32R32F,D3DPOOL_DEFAULT,&PrevStageFp[fn],NULL);
fs*=2;
}


pDevice->CreateTexture(512,512,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTextureLQ,NULL);
pDevice->CreateTexture(512,512,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture2LQ,NULL);
pDevice->CreateTexture(512,512,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture3LQ,NULL);

pDevice->CreateTexture(1024,1024,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTextureHQ,NULL);
pDevice->CreateTexture(1024,1024,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture2HQ,NULL);
pDevice->CreateTexture(1024,1024,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture3HQ,NULL);

pDevice->CreateTexture(2048,2048,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTextureHQ2,NULL);
pDevice->CreateTexture(2048,2048,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture2HQ2,NULL);
pDevice->CreateTexture(2048,2048,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PrevStageTexture3HQ2,NULL);

PrevStageTexture=PrevStageTextureLQ;
PrevStageTexture2=PrevStageTexture2LQ;
PrevStageTexture3=PrevStageTexture3LQ;

#ifdef EditMode
//pDevice->CreateTexture(2048,2048,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&GuiTex,NULL);
#endif



for( int k=0;k<maxtex;k++)
{
tex_res[k]=texres;
}

char* q;q=new char [32];	
HRESULT res;
for (int k=0;k<5;k++) 
{
res=pDevice->CreateTexture(texres,texres,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&TextureStage[k],NULL);
	
if (res!=D3D_OK)
	{	
	_itoa(res,q,10);
	MessageBox(hWndView,q,"tex",0);
	}
}

//pDevice->CreateTexture(256,256,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&Texture[0],NULL);
for (int k=0;k<maxtex;k++) 
{

res=pDevice->CreateTexture(texres,texres,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&Texture[k],NULL);

if (res!=D3D_OK)
	{	
	_itoa(res,q,10);
	MessageBox(hWndView,q,"tex",0);
	}
}

#ifdef EditMode
for (int st=0;st<64;st++) 
{
res=pDevice->CreateTexture(64,64,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&Scenes[st],NULL);

if (res!=D3D_OK)
	{	
	_itoa(res,q,10);
	MessageBox(hWndView,q,"tex",0);
	}
}
#endif


pDevice->CreateTexture(1024,1024,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&StartScreen,NULL);

pDevice->CreateTexture(32,32,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&WhiteTexture,NULL);
pDevice->CreateTexture(256,256,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&NoiseTexture,NULL);
pDevice->CreateTexture(512,512,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&RGradTexture,NULL);
pDevice->CreateTexture(512,512,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&IRGradTexture,NULL);
pDevice->CreateTexture(512,512,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&ISqGradTexture,NULL);
pDevice->CreateTexture(256,256,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&PlasmTexture,NULL);

pDevice->CreateTexture(128,128,0,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&CStageTexture,NULL);


unsigned char a,b;int i,x,y;double fa;

//генерим белое
a=255;for (i=0;i<screen_width*4;i+=4) {*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=0;}
LoadTextureToGPU(tmp,WhiteTexture,32,0);

//генерим нойс
srand(0);
for (i=0;i<65535*4;i+=4)
	{a=rand()%256;*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=a;}
LoadTextureToGPU(tmp,NoiseTexture,256,0);

srand(0);
for (i=0;i<65535;i++)
	{a=rand()%256;(BYTE)*(texture_swp+i)=a;}

//генерим партикл
i=0;
for (y=0;y<512;y++)
for (x=0;x<512;x++)
	{
	fa=sqrt((float)((x-256)*(x-256)+(y-256)*(y-256)));
	if (fa>255) fa=255;
	a=255-fa;
	b=255;
	*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=a;i+=4;
	}
LoadTextureToGPU(tmp,RGradTexture,512,0);


//генерим инвертированный партикл
i=0;
for (y=0;y<512;y++)
for (x=0;x<512;x++)
	{
	fa=sqrt((float)((x-256)*(x-256)+(y-256)*(y-256)));
	if (fa>255) fa=255;
	//fa=255-(256-fa)/2.0+(256-fa)/2.0*sin(fa/15.0);
	a=fa;
	b=255;
	*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=a;i+=4;
	}
LoadTextureToGPU(tmp,IRGradTexture,512,0);

//генерим инвертированный квадратичный партикл
i=0;int xx,yy;
for (y=0;y<512;y++)
for (x=0;x<512;x++)
	{
	xx=x-256;yy=y-256;
	fa=0;
	if (xx>yy&&xx<(256-y)) fa=yy; 
	if (xx>yy&&xx>=(256-y)) fa=256-xx; 
	if (xx<=yy&&xx>(256-y)) fa=256-yy;
	if (xx<=yy&&xx<=(256-y)) fa=xx;
		
	a=255-fa;
	b=255;
	*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=a;i+=4;
	}
	*(tmp+256*512*4+256*4+0)=0;
	*(tmp+256*512*4+256*4+1)=0;
	*(tmp+256*512*4+256*4+2)=0;
	*(tmp+256*512*4+256*4+3)=0;
LoadTextureToGPU(tmp,ISqGradTexture,512,0);

//генерим плазму
i=0;
for (y=0;y<256;y++)
for (x=0;x<256;x++)
	{
	fa=127+63.5*sin(x*360/256.0*PI/180.0)+63.5*sin(y*360/256.0*PI/180.0);
	a=fa;
	*(tmp+i)=a;*(tmp+i+1)=a;*(tmp+i+2)=a;*(tmp+i+3)=a;i+=4;
	}
LoadTextureToGPU(tmp,PlasmTexture,256,0);



delete(tmp);


//CaptureScreen();// uncomment this and hdc creation in winmain to enable

}

#ifdef EditMode

#include <Xaudio2.h>
IXAudio2* pXAudio2 = NULL;
IXAudio2MasteringVoice* pMasterVoice = NULL;
IXAudio2SourceVoice* pSourceVoice;
WAVEFORMATEXTENSIBLE wfx = {0};
XAUDIO2_BUFFER XAbuffer = {0};
WAVEFORMATEX wf={0};
int ccl=0;
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
    HANDLE hBufferEndEvent;
    VoiceCallback(): hBufferEndEvent( CreateEvent( NULL, FALSE, FALSE, NULL ) ){}
    ~VoiceCallback(){ CloseHandle( hBufferEndEvent ); }

    //Called when the voice has just finished playing a contiguous audio stream.
    void __stdcall  OnStreamEnd() {SetEvent( hBufferEndEvent);SetWindowText(hWnd0,"streamEnd"); } 


    //Unused methods are stubs
	void __stdcall OnVoiceProcessingPassEnd() {}//{ SetEvent( hBufferEndEvent);SetWindowText(hWnd0,"propcessingEnd");}
	void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) 
	{ 
		SetEvent( hBufferEndEvent);
		//ccl+=11;
		for (int i=0;i<SamplesRequired;i++)
		{
		*(snd_mem+44+i*2)=0;
		}
		
		//pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(ccl,ccl,ccl,0),8.0f,0);
		//SetWindowText(hWnd0,"processingStart");  
	}
    void __stdcall OnBufferEnd(void * pBufferContext)    { SetEvent( hBufferEndEvent);SetWindowText(hWnd0,"bufEnd");}
    void __stdcall OnBufferStart(void * pBufferContext) {  SetEvent( hBufferEndEvent);SetWindowText(hWnd0,"bufStart");  }
    void __stdcall OnLoopEnd(void * pBufferContext) {  SetEvent( hBufferEndEvent); 
	//SetWindowText(hWnd0,"loopEnd"); 
	ccl+=11;
		
	//pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(ccl,ccl,ccl,0),8.0f,0);
	}
    void __stdcall OnVoiceError(void * pBufferContext, HRESULT Error) { }
};

VoiceCallback VCB;

void XAudioInit()
{

HRESULT hr;
if ( FAILED(hr = XAudio2Create( &pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) )
    MessageBox(hWndView,"XA create fail",0,0);;

if ( FAILED(hr = pXAudio2->CreateMasteringVoice( &pMasterVoice ) ) )
    MessageBox(hWndView,"XA MVoice fail",0,0);;


} 

#endif

void Ic(int gx, int gy)
{
int k=0;int ty,tx;
for (ty=0;ty<gy-1;ty++)
	{
	for (tx=0;tx<gx-1;tx++)
		{
		pTInds[k+0]=ty*gx+tx;
		pTInds[k+1]=ty*gx+tx+1;
		pTInds[k+2]=(ty+1)*gx+tx+1;		
		k+=3;
		
		pTInds[k+0]=ty*gx+tx;
		pTInds[k+1]=(ty+1)*gx+tx+1;
		pTInds[k+2]=(ty+1)*gx+tx;		
		k+=3;
		}
	}
}

bool InitD3D(HWND hWnd)
{
  // Создание объекта Direct3D
  pD3D = Direct3DCreate9(D3D_SDK_VERSION);
  if( !pD3D)
    return false;

  // Создание устройства рендера.
  D3DPRESENT_PARAMETERS d3dpp = {0};
  d3dpp.BackBufferWidth=screen_width;
  d3dpp.BackBufferHeight=screen_height;
  d3dpp.BackBufferFormat=D3DFMT_A8R8G8B8;
  d3dpp.EnableAutoDepthStencil=TRUE ;
  //d3dpp.AutoDepthStencilFormat=D3DFMT_D16;
  d3dpp.AutoDepthStencilFormat=D3DFMT_D24X8;
  d3dpp.BackBufferCount=1; 

 // if (!windowed) 
  //d3dpp.BackBufferCount=2;

  //d3dpp.Flags=D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
  d3dpp.hDeviceWindow=hWnd;
  d3dpp.Windowed = windowed;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

 //if (!windowed) 
	 d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;


 // d3dpp.MultiSampleType=D3DMULTISAMPLE_4_SAMPLES;
//	  d3dpp.MultiSampleQuality=2;
  d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;
  //d3dpp.PresentationInterval=D3DPRESENT_INTERVAL_ONE;
  


  HRESULT hr;

  hr = pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                           D3DCREATE_HARDWARE_VERTEXPROCESSING,
                           &d3dpp, &pDevice );

  if( FAILED(hr) || !pDevice)  return false;

  pDevice->CreateDepthStencilSurface(2048,2048,D3DFMT_D24X8,D3DMULTISAMPLE_NONE,NULL,FALSE,&zbuf2,NULL);


//intz
#define FOURCC_INTZ ((D3DFORMAT)(MAKEFOURCC('I','N','T','Z')))


//hr=pDevice->CreateTexture(1024, 768, 1,
  hr=pDevice->CreateTexture(2048, 2048, 1,
D3DUSAGE_DEPTHSTENCIL, FOURCC_INTZ,
D3DPOOL_DEFAULT, &pINTZDST,
NULL);

IDirect3DSurface9 *pINTZDSTSurface;
pINTZDST->GetSurfaceLevel(0, &pINTZDSTSurface);
pDevice->SetDepthStencilSurface(pINTZDSTSurface);

//pDevice->SetTexture(0, pINTZDST);


  ZeroMemory(&WhiteMaterial,sizeof(WhiteMaterial));
  WhiteMaterial.Ambient.r=1;WhiteMaterial.Ambient.g=1;WhiteMaterial.Ambient.b=1;WhiteMaterial.Ambient.a=1;
  WhiteMaterial.Diffuse.r=1;WhiteMaterial.Diffuse.g=1;WhiteMaterial.Diffuse.b=1;WhiteMaterial.Diffuse.a=1;
  
  ZeroMemory(&WhiteAmbientLight,sizeof(WhiteAmbientLight));
  WhiteAmbientLight.Ambient.r=1;WhiteAmbientLight.Ambient.g=1;WhiteAmbientLight.Ambient.b=1;WhiteAmbientLight.Ambient.a=1;
  WhiteAmbientLight.Type=D3DLIGHT_DIRECTIONAL;
  
  pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_ARGB(0,0,0,0),8.0f,0);
	
	View=StartViewMatrix;
	View2=StartViewMatrix;
	View3=StartViewMatrix;
	World=StartViewMatrix;

	IView=StartMatrix;
	IWorld=StartMatrix;

	Pack= new BYTE [CellSize*EntriesCount] ;//10000 entries
		Exchange= new BYTE [CellSize*EntriesCount] ;//10000 entries
		Exchange2= new BYTE [CellSize*EntriesCount] ;//10000 entries
			RExchange= new BYTE [CellSize*EntriesCount] ;//10000 entries

	font=new BYTE [screen_width*screen_width];
	UnpackedFont= new BYTE[screen_width*screen_width*4];

	textblock=new BYTE [10000];

    ZeroMemory(Pack,CellSize*EntriesCount);
//
	SSTable=new char[64*64];
	ZeroMemory(SSTable,64*64);
	CreateShaders();

	// создание индексных буферов
	HRESULT h;char* ii;
	ii=new char [100];
	int sz;
	sz=maxgridsize;

	int b;
	for (b=0;b<64;b++)
	{
		_itoa(b,ii,10);
	VBNumVerts[b]=0;// количество вершин
	VBNumTriangles[b]=0;// количество треугольников
	VBNumInds[b]=0;// количество индексов.

	h=pDevice->CreateVertexBuffer( sizeof(MyVertex) * sz*sz,D3DUSAGE_WRITEONLY  , D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &pVB[b], 0 );
	if(h!=D3D_OK) { 
				MessageBox(hWnd,ii,0,0); 
				goto q;}

//sizeof(int) =4
	h=pDevice->CreateIndexBuffer( 4 * sz*sz*2*3,D3DUSAGE_WRITEONLY , D3DFMT_INDEX32 , D3DPOOL_DEFAULT,&pIB[b], 0);
	if(h!=D3D_OK) { 
				MessageBox(hWnd,ii,0,0); 
				goto q;}
		
	}
q:;

	maxvb=b-1;


	D3DXMatrixIdentity(&ZoomMatrix);

//fp
	h=pDevice->CreateVertexBuffer( sizeof(MyVertex) * 4,D3DUSAGE_WRITEONLY  , D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &pPVB, 0 );
	h=pDevice->CreateIndexBuffer( 4 * 6,D3DUSAGE_WRITEONLY , D3DFMT_INDEX32 , D3DPOOL_DEFAULT,&pPIB, 0);
//

//tobj
	pDevice->CreateVertexBuffer( sizeof(TVertex) * 512*512*3*2,D3DUSAGE_WRITEONLY  , D3DFVF_TVERTEX, D3DPOOL_DEFAULT, &pTVB, 0 );

	int v=0;int q=0;
for (int t=0;t<512*512*3*2;t++)
{
pTVR[t].x=0;pTVR[t].y=0;pTVR[t].z=0;
pTVR[t].u=q;//index
pTVR[t].v=v;//
v++;
if (v>5) {v=0;q++;}
}
			void* pBuf;
			pTVB->Lock( 0, sizeof(TVertex) * 512*512*3*2, &pBuf, 0 );
			  memcpy( pBuf, pTVR, sizeof(TVertex) * 512*512*3*2);
			pTVB->Unlock();

/*
int r=512;
for (int t=0;t<10;t++)
{
if (r<2) break;


	Ic(r,r);
r--;
	pDevice->CreateIndexBuffer( sizeof(int) * r*r*3*2,D3DUSAGE_WRITEONLY , D3DFMT_INDEX32 , D3DPOOL_DEFAULT,&pTIB[t], 0);
					void * pBuf;
					pTIB[t]->Lock( 0, sizeof(int) * r*r*3*2, &pBuf, 0 );
						memcpy( pBuf, pTInds, sizeof(int) * r*r*3*2);
					pTIB[t]->Unlock();
r++;
					
	r/=2;
}*/



//unsigned int mem=pDevice->GetAvailableTextureMem();

//maxtex=(mem/2)/(512*512*4);

//char mema[64];
//_itoa(maxtex,mema,10);
//MessageBox(hWnd,mema,0,0);

//if (maxtex>256) maxtex=256;


CreateBaseTextures();

texCopy=new BYTE [2048*2048*4];

#ifdef EditMode
XAudioInit();
#endif

//перенести в иниты основной программы
#ifdef EditMode	
SetWindowPos(hWnd,HWND_TOP,0,0,screen_width,screen_height,SWP_SHOWWINDOW);
#endif
  //test data

//  Pos=0;
		
		pDevice->GetRenderTarget(0,&mainRT);


Put(0,0,1);
LoopPoint=0;

//pDevice->CreateTexture(512,512,1,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&TT,NULL);
pDevice->CreateTexture(2048,2048,0,D3DUSAGE_DYNAMIC,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,&TTt,NULL);


//CaptureScreen();

//-------------

			View2=StartViewMatrix;
			World=StartMatrix;
			D3DXMatrixIdentity(&ZoomMatrix);




	return true;

}


void ReleaseD3D()
{
	
//	pXAudio2->StopEngine();
//pXAudio2->Release();

for (int i=0;i<maxvb;i++)
{
  if(pVB[i]) pVB[i]->Release();
  if(pIB[i]) pIB[i]->Release();
	pVB[i] = 0;pIB[i] = 0;
}

  if(pDevice)
    pDevice->Release();
  if(pD3D)
    pD3D->Release();


}




