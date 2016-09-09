inline DWORD F2DW( FLOAT f ) { return *((DWORD*)&f); }

int CurveCmdPos;
#ifdef EditMode
void show_ms(float x, float y, float z, float rad);
#endif
int scatterN,scatterX,scatterY,scatterZ;
int sh_mat,sh_tex,sh_tex1,sh_tex2;float sh_height,sh_bumpV,sh_scr,sh_z,sh_dUV,sh_nUV;
int setshader_flag=0;
int CurrentShader=0;
int lastShaderApplied=0;
int ApplyShaderPos=0;
int CurrentShaderPos=0;
int CurrentShaderSlot=0;
int InstanceNum=0;
int OverrideShaderFlag=0;
int OverrideShaderN=0;
int sceneStart=0;
int sceneFinish=0;

char ShaderVars[64][64][32];
int ShaderVarsType[64][64];
char vsname[64][64];char psname[64][64];
int ApplyShaderIndex,ShaderPostIndex;
ID3DXBuffer* errv,*errp;
void _SetShader(int sn);
void _ApplyShader(int shader,int cp);

D3DMATRIX cv;//timeliner matrix
int current_rt=-1;
int mipgenflag=0;

//usquare pixel, full texture

int CPC_IT=0;

	int trk_octave=5;
	int trk_sample=0;
	int trk_volume=64;
	int trk_step=1;
	int trk_notecmd;
	int trk_major=8;
	int trk_minor=4;
	int trk_channelcmd;
	int	trk_endseqcmd;

int timelinematrix;

void Camera();

void NText(char* in,float tracking,int inx, int iny,int inwh);
void NTextLen(char* in,float tracking,int inx, int iny,int inwh);
void NaviBox(int _x,int _y,int _w,int _h,int r,int g,int b);
void TFlat(int inx,int iny, int fw,int fh);

void BlackQuad();
void WhiteQuad();

int WriteAlpha_flag;
int AlphaMode;

int override_tm_flag=-1;

int vbout_start,vbout_end;

#include "animation.h"

void SetMaterial(D3DMATERIAL9* Material)
{
if (override_tm_flag==1) return;
pDevice->SetMaterial(Material);
}

float sign(float a)
{
if (a!=0) return a/fabs(a);
return 0;
}

int clampI(int x,int min,int max)
{
if (x>max)return max;
if (x<min)return min;
return x;
}


float clamp(float x,float min,float max)
{
if (x>max)return max;
if (x<min)return min;
return x;
}

float frac(float x)
{
float a;
a=x-(int)x;
return a;
}

float ffrac(float x)
{
float a;
a=x-(int)x;
return fabs(a);
}

float lerp(float x1,float x2,float a)
{
return (x1*a+x2*(1.0-a));
}

float lerp3(float x1,float x2,float x3,float x)
{
return (clamp(1-x*2,0,1)*x1+(clamp(x*2,0,1)-clamp((x-.5),0,1)*2)*x2+clamp((x-.5)*2,0,1)*x3);
}

int clampmode=0;

void ZBufDisable()
{
pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE);
pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
}

void ZBufEnable()
{
pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
}


int currentVBtoadd=-1;

int HeadN,HeadMat,HeadTex,HeadFlag,HeadExtractPosFlag;

void SetVBsHead()
{
HeadFlag=1;
HeadN=Get(CPos,1);
HeadTex=Get(CPos,2);
HeadMat=Get(CPos,3);
HeadExtractPosFlag=Get(CPos,4);
}

void StartAddToVB()
{
int vbi;
vbi=Get(CPos,1);
if (vbi<0||vbi>maxvb) return;

VBNumVerts[Get(CPos,1)]=0;// количество вершин
VBNumTriangles[Get(CPos,1)]=0;// количество треугольников
VBNumInds[Get(CPos,1)]=0;// количество индексов.

currentVBtoadd=vbi;
}

void EndAddToVB()
{
currentVBtoadd=-1;
}

void WriteAlpha_(int a)
{
if (a==2) 
	{
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA);
		WriteAlpha_flag=1;
	}


if (a==1) 
	{
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
		WriteAlpha_flag=1;
	}
if (a==0) 
	{
		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
		WriteAlpha_flag=0;
	}
}

void WriteAlpha(int a)
{
WriteAlpha_(a);
}

void WriteAlpha()
{
int a=Get(CPos,1);
WriteAlpha_(a);
}

D3DVIEWPORT9 vp;

float width,height;

void SetVp_(int j)
{
	/*D3DCLIPSTATUS9 c;
	c.ClipIntersection=D3DCS_TOP ;
	c.ClipUnion=D3DCS_TOP ;
	pDevice->SetClipStatus(&c );*///wtf?

  if (j==0)
  {
  width=1;height=1;
	vp.X      = 0;
	vp.Y      = 0;
	vp.Width  = screen_width;
	vp.Height = screen_height;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;
	

	  pDevice->SetViewport(&vp);
  }
  if (j==1)
  {
	width=screen_width/screen_height;height=1;
	  //width=1;height=1;

	vp.X      = (screen_width-512)/2;
	vp.Y      = (screen_height-512)/2;
	vp.Width  = 512;
	vp.Height = 512;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;

	  pDevice->SetViewport(&vp);
  }
  if (j==2)
  {
  width=1;height=1;
	vp.X      = 0;
	vp.Y      = 0;
	vp.Width  = 1280;
	vp.Height = 800;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;

	  pDevice->SetViewport(&vp);
  }
if (j==3)
{
	width=1;height=1;

	vp.X      = 0;
	vp.Y      = 0;
	vp.Width  = 1024;
	vp.Height = 1024;
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;

	  pDevice->SetViewport(&vp);

}

}

void SetVp()
{
SetVp_(Get(CPos,1));
}


void SetViewport()
{
	width=1;height=1;

	vp.X      = Get(CPos,1);
	vp.Y      = Get(CPos,2);
	vp.Width  = Get(CPos,3);
	vp.Height = Get(CPos,4);
	vp.MinZ   = 0.0f;
	vp.MaxZ   = 1.0f;

	  pDevice->SetViewport(&vp);
}

/*void SaveStage()
{
RECT SourceRect,DestRect;

if (width==height)
{
SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
SetRect(&DestRect, 0, (1024-screen_height)/4, 512, 512-(1024-screen_height)/4);

		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		TextureStage[CPos-ScenePos]->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,&DestRect,D3DTEXF_NONE);
}
else
{
SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
SetRect(&DestRect, 0, 0, 512, 512);

		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		TextureStage[CPos-ScenePos]->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,NULL,D3DTEXF_NONE);
}


}*/

//to region in dest. texture. square pixel
void CpyToPrev(int i)
{
RECT SourceRect,DestRect;

		if (width==height)
		{
		SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y);
		SetRect(&DestRect, 0, (screen_width-screen_height)/4, 512, 512-(screen_width-screen_height)/4);
		}
		else
		{
		SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
		SetRect(&DestRect, 0, 0, 512, 512);
		}

		LPDIRECT3DSURFACE9 RT,RT2;
		if (i==0) PrevStageTexture->GetSurfaceLevel(0,&RT2);
		if (i==1) PrevStageTexture2->GetSurfaceLevel(0,&RT2);
		if (i==2) PrevStageTexture3->GetSurfaceLevel(0,&RT2);

		if (current_rt==-1) {
			pDevice->GetRenderTarget(0,&RT); 
			pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)CPC_IT);
		}
		else { 
			Texture[current_rt]->GetSurfaceLevel(0,&RT);
			pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		}

		//pDevice->GetRenderTarget(0,&RT);

		//pDevice->StretchRect(RT,&SourceRect,RT2,&DestRect,D3DTEXF_LINEAR);
		RT->Release();
		RT2->Release();


}

void MipGen(LPDIRECT3DTEXTURE9 tex)
{
	LPDIRECT3DSURFACE9 RT,RT2;
	HRESULT h;
		for (int x=0;x<8;x++)//for 512x512
		{
		tex->GetSurfaceLevel(0+x,&RT);
		tex->GetSurfaceLevel(1+x,&RT2);
		h=pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_LINEAR);
		if (h!=D3D_OK) MessageBox (hWndView,"err","err",0);
		RT->Release();
		RT2->Release();
		}
}

void MipGenT(int t)
{int iter=5;
int r=32;
while (r<tex_res[t]){ r*=2;iter++;}
	LPDIRECT3DSURFACE9 RT,RT2;
	HRESULT h;
		for (int x=0;x<iter;x++)//for 512x512
		{
		Texture[t]->GetSurfaceLevel(0+x,&RT);
		Texture[t]->GetSurfaceLevel(1+x,&RT2);
		h=pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_LINEAR);
		if (h!=D3D_OK) MessageBox (hWndView,"err","err",0);
		RT->Release();
		RT2->Release();
		}
}

int CpyToPrevFp()
{
int tr=0;

	if (current_rt>=0) 
	{

		RECT SourceRect,DestRect;

		LPDIRECT3DSURFACE9 RT,RT2;
		int r=tex_res[current_rt];
		//int tr=ln(r)/ln(2)-5;
		
		if (r==32) tr=0;
		if (r==64) tr=1;
		if (r==128) tr=2;
		if (r==256) tr=3;
		if (r==512) tr=4;
		if (r==1024) tr=5;
		if (r==2048) tr=6;
		PrevStageFp[tr]->GetSurfaceLevel(0,&RT2);
		Texture[current_rt]->GetSurfaceLevel(0,&RT);
		pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		RT->Release();
		RT2->Release();
	}

	return tr;
}

void CpyToPrev2(int i)
{
	//CPC_IT=0;
RECT SourceRect,DestRect;



		LPDIRECT3DSURFACE9 RT,RT2;

SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y);

		if (i==0) PrevStageTexture->GetSurfaceLevel(0,&RT2);
		if (i==1) PrevStageTexture2->GetSurfaceLevel(0,&RT2);
		if (i==2) PrevStageTexture3->GetSurfaceLevel(0,&RT2);

		if (current_rt==-1) {
			pDevice->GetRenderTarget(0,&RT); 
			pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)CPC_IT);
		}
		else { 
			Texture[current_rt]->GetSurfaceLevel(0,&RT);
			pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		}


		//pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)CPC_IT);//subtexel control?
		//pDevice->StretchRect(RT,NULL,RT2,NULL,(D3DTEXTUREFILTERTYPE)CPC_IT);//subtexel control?

		RT->Release();
		RT2->Release();

	if (mipgenflag==0) return;

		if (i==0) MipGen(PrevStageTexture);
		if (i==1) MipGen(PrevStageTexture2);
		if (i==2) MipGen(PrevStageTexture3);

}

void SetHQFiltersTex()
{
	if (Get(CPos,1)==0)
	{
	PrevStageTexture=PrevStageTextureLQ;
	PrevStageTexture2=PrevStageTexture2LQ;
	PrevStageTexture3=PrevStageTexture3LQ;
	}
	
	if (Get(CPos,1)==1)
	{
	PrevStageTexture=PrevStageTextureHQ;
	PrevStageTexture2=PrevStageTexture2HQ;
	PrevStageTexture3=PrevStageTexture3HQ;
	}

	if (Get(CPos,1)==2)
	{
	PrevStageTexture=PrevStageTextureHQ2;
	PrevStageTexture2=PrevStageTexture2HQ2;
	PrevStageTexture3=PrevStageTexture3HQ2;
	}

}

void CpyToPrev()
{
CpyToPrev(0);
}

void OverrideTM()
{
if (Get(CPos,2)==1) override_tm_flag=1;
if (Get(CPos,2)==0) override_tm_flag=-1;

int num;num=Get(CPos,3);

int pslot=0;
int stage;stage=Get(CPos,1);

if (num>255) goto mat;
if (stage<0||stage>7) goto mat;
if (pslot<0||pslot>2) goto mat;

if (num<0) 
	{
	CpyToPrev2(pslot);
	if (pslot==0) pDevice->SetTexture(stage,PrevStageTexture);
	if (pslot==1) pDevice->SetTexture(stage,PrevStageTexture2);
	if (pslot==2) pDevice->SetTexture(stage,PrevStageTexture3);
	}
else
	pDevice->SetTexture(stage,Texture[num]);

mat:
num=Get(CPos,4);
if (num>=0&&num<255) pDevice->SetMaterial(&Material[num]);
}

void SetTexture(int stage,int num,int pslot)
{
if (override_tm_flag==1) return;
if (num>255) return;
if (stage<0||stage>7) return;
if (pslot<0||pslot>2) return;

if (num<0) 
	{
		
	if (num==-1)
		{
		CpyToPrev2(pslot);
		if (pslot==0) pDevice->SetTexture(stage,PrevStageTexture);
		if (pslot==1) pDevice->SetTexture(stage,PrevStageTexture2);
		if (pslot==2) pDevice->SetTexture(stage,PrevStageTexture3);
		}
	if (num==-2) pDevice->SetTexture(stage,FontTexture);
	if (num==-3) pDevice->SetTexture(stage,pINTZDST);
	}
else
	pDevice->SetTexture(stage,Texture[num]);
}

void AnimP();

float freq[100],amp[100],phase[100],clampmax[100],clampmin[100];


void ZWriteMod()
{
if (Get(CPos,1)==0) pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
if (Get(CPos,1)==1) pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
}

void SetAlfa(int A)
{
	AlphaMode=A;

	if (A==0)
		{
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		}

		if (A>0&&A<6)
		{
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_BLENDOP,A);
		}
		
		if (A==6)
		{
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		//to remove later
		if (A==7)
		{
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD );
			pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		
}





void SetAlfa()
{
SetAlfa(Get(CPos,1));
}



void ApplyMods();
int curve_len;
int curve_q;
double curve_x [1024];
double curve_y [1024];
double curve_z [1024];

float curvearray_x [256][1024*10];
float curvearray_y [256][1024*10];
float curvearray_z [256][1024*10];
int curvearray_clen[256];


void FillVB(int vbi)
{
void * pBuf;

//-Directly Mapping Texels to Pixels
//for (int i=0;i<NumVerts;i++)
{
//pVerts[i].x-=1.0/256.0;
//pVerts[i].y+=1.0/256.0;
//pVerts[i].x+=.50/1024.0;
//pVerts[i].y+=.5/768.0;

//pVerts[i].u-=.25/512.0;
//pVerts[i].v+=.5/768.0;

}

//--
if (vbi<0||vbi>=100) {MessageBox(hWndView,"fillvb","error",0);return;}
					
					 pVB[vbi]->Lock( 0, sizeof(MyVertex) * NumVerts, &pBuf, 0 );
					  memcpy( pBuf, pVerts, sizeof(MyVertex) * NumVerts);
					pVB[vbi]->Unlock();
					
					pIB[vbi]->Lock( 0, sizeof(int) * NumInds, &pBuf, 0 );
						memcpy( pBuf, pInds, sizeof(int) * NumInds);
					pIB[vbi]->Unlock();
}




void Clear()
{
pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(Get(CPos,1),Get(CPos,2),Get(CPos,3),Get(CPos,4)),8.0f,0);


}



void SetRT()
{
	int rt=Get(CPos,1);
	if (rt==-1)
	{
		LPDIRECT3DSURFACE9 RT;
		pDevice->GetRenderTarget(0,&RT);
		//Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT);
		if (RT!=mainRT) RT->Release();
		pDevice->SetRenderTarget(0,mainRT);
		SetVp_(0);
		current_rt=-1;
	}
	if (rt>=0&&rt<maxtex)
	{
		LPDIRECT3DSURFACE9 RT;
		Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT);
		pDevice->SetRenderTarget(0,RT);
		RT->Release();
		current_rt=Get(CPos,1);
		
		//pDevice->SetDepthStencilSurface(zbuf2);
	}

}

void SetPrj()
{
SetProjecton(Get(CPos,1));
}

void Scene()
{

//timelinematrix=0;
for(int h=0;h<21;h++){freq[h]=0;phase[h]=0;amp[h]=0;}//reset anim
for(int h=1;h<21;h++) {clampmax[h]=32767;clampmin[h]=-32767;}
clampmode=0;

  ScenePos=CPos;

#ifdef EditMode
  SetView(Get(CPos,1));
#endif
  SetWorld(Get(CPos,1));
  LPDIRECT3DSURFACE9 trt;
  pDevice->GetRenderTarget(0,&trt);
  if (Get(CPos,3) ==0)
  {
	  if (trt==mainRT) 
	  {
		  if (Get(CPos,1)==1)  SetProjecton(1); 
		  else SetProjecton(0);
	  } else {
		  SetProjecton(0);
	  }
  }

  if (Get(CPos,1)==1) World=StartMatrix;

	if (Get(CPos,1)==1)	pDevice->SetTransform(D3DTS_VIEW, &StartMatrix); 

  pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  pDevice->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
  pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
  pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
  pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,2);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	if (Get(CPos,1)==1) WriteAlpha(0); else WriteAlpha(1);
  pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255,255,255,255));
  pDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_SELECTARG1 );
  pDevice->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
  pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE); 
  pDevice->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);  
  pDevice->SetRenderState(D3DRS_AMBIENT,0x00ffffff);
  pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
  pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE );
for (int z=0;z<8;z++) pDevice->LightEnable(z,FALSE); 
    pDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
  pDevice->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);
  pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
  
  pDevice->SetFVF(D3DFVF_MYVERTEX);
  if (Get(CPos,2)==0) SetVp_(Get(CPos,1));
  pDevice->Clear(0,NULL, D3DCLEAR_ZBUFFER,0,8.0f,0);
}

void PreCalc()
{Scene();
}

void ZClear()
{
	pDevice->Clear(0,NULL, D3DCLEAR_ZBUFFER,0,8.0f,0);
}

int MaxRecurrenceLevel=64;

void SetMaxRecurrenceLevel()
{
if (MaxRecurrenceLevel>1&&MaxRecurrenceLevel<=64) MaxRecurrenceLevel=Get(CPos,1);
}




void ShowScene()
{

int sccount;
if (nGet(CPos+2*2)==1)
{
	int x,x1;
	x=nGet(CPos+3*2);
	x1=x+nGet(CPos+5*2);
	if (ptime<x||ptime>x1) return;

	sceneStart=x;
	sceneFinish=x1;

}

sccount=0;
	
if (nGet(CPos+1*2)<1) return;
if (stackpos>=MaxRecurrenceLevel) return;

//for (int i=CPos+1;i<EntriesCount;i++)
int i=0;
//for (int i=1;i<EntriesCount;i++)


while (i<EntriesCount*CellSize)
	{	
		
	if (nGet(i)==0) return;

	if (CmdDesc[nGet(i)].FRoutine==Scene) 
	{

		sccount++;
	}
	if (sccount==nGet(CPos+1*2)) 
		{


		stack[stackpos]=CPos;
		stackpos++;

		CPos=i;
		
		return;
		}
	//if (CmdDesc[Get(i,0)].FSize!=CellSize) i+=CmdDesc[Get(i,0)].FSize/CellSize-1;
	i+=CmdDesc[nGet(i)].FSize;


	}

}

void EndScene()
{

#ifdef EditMode
		//preview
	int sc=0;int j=0;
	while (nGet(j)!=0)
	{
		if (j>=CPos) break;
		if (CmdDesc[nGet(j)].FRoutine==Scene) sc++;
		j+=CmdDesc[nGet(j)].FSize;
	}
	
		{
		LPDIRECT3DSURFACE9 RT,RT2;

		HRESULT h0;
		h0=Scenes[sc]->GetSurfaceLevel(0,&RT2);

		if (current_rt==-1) {
			HRESULT h,h2;
			h=pDevice->GetRenderTarget(0,&RT); 
			h2=pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		}
		else { 
			Texture[current_rt]->GetSurfaceLevel(0,&RT);
			pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		}

		RT->Release();
		RT2->Release();
		}
		//
#endif


//	pDevice->SetRenderTarget(0,mainRT);
currentVBtoadd=-1;

	if (stackpos>0) 
	{
	stackpos--;
	CPos=stack[stackpos]+CmdDesc[nGet(stack[stackpos])].FSize;
	}

}

void EndDraw()
{
int t=nGet(CPos+9*2);

}


void Post()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
CpyToPrev2(0);
//BlackQuad();
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

float px=Get(CPos,1);float py=Get(CPos,2);
int tpx=Get(CPos,1);int tpy=Get(CPos,2);

greedx=px;greedy=py;

int vc=0;
float x,y,sx,sy;

if (px==0||py==0) return;

y=2; sx=4.0/px;sy=-4.0/py;
float v,dv;
v=0;dv=1.0/py;
px++;py++;
tpx++;tpy++;

vc=0;

	int i,j;
	for(i=0;i<py;i++)
		{	
		x=-2;
			for(j=0;j<px;j++)
			{
				pVerts[vc].x=x;pVerts[vc].y=y;pVerts[vc].z=0;
				pVerts[vc].u=(x+2)/4.0;
				
				pVerts[vc].v=v;
				
				pVerts[vc].color=0x00ffffff;
				vc++;
				x+=sx;
			}
		v+=dv;
		y+=sy;
		}

	NumVerts=vc;

	vc=0;
	for(i=0;i<py-1;i++)
		{	
			for(j=0;j<px-1;j+=1)
			{
				pInds[vc+0]=i*tpx+j;
				pInds[vc+1]=i*tpx+j+1;
				pInds[vc+2]=(i+1)*tpx+j;
				pInds[vc+3]=i*tpx+j+1;
				pInds[vc+4]=(i+1)*tpx+j+1;
				pInds[vc+5]=(i+1)*tpx+j;
				vc+=6;
				
			}
		}
	NumInds=vc;
	NumTriangles=vc/3;

//pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(0,0,0,0),8.0f,0);

	pDevice->SetTexture(0,PrevStageTexture);
	SetAlfa(Get(CPos,3));
				
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetMaterial(&WhiteMaterial);

	ApplyMods();
	FillVB(0);
	
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
		
//pDevice->SetTransform(D3DTS_VIEW, &View);
SetView(0);
}



void Cells()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

switch(Get(CPos,1))
	{
	case 0:{
			WhiteQuad();
			pDevice->SetTexture(0,IRGradTexture);
			SetAlfa(4);
			break;}
	case 1:{
			BlackQuad();		
			pDevice->SetTexture(0,RGradTexture);
			SetAlfa(5);
			break;}

	}

	pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;
//float v = float(GetTickCount()%0xffff)/0xffff * 3.141593f * 20;
int count=Get(CPos,2);
int CellSize=Get(CPos,3);
int SqSize=Get(CPos,4);
float Phaze=Get(CPos,5)/100.0;

float tx,ty,tz;

	double x,y,z,w,h;int r,g,b;
	
	if (count<1) return;

	w=CellSize/1000.0;
	h=CellSize/1000.0;
	r=255;
	g=255;
	b=255;

for (int i=0;i<count;i++)
{
	tx=SqSize*sin(((float)i)*3.0+Phaze*PI/180.0)/1000.0;
	ty=SqSize*sin(((float)i)*8.0+Phaze*PI/180.0)/1000.0;
	x=tx;
	y=ty;
	z=0;
	
	pVerts[0+i*4].x=x-w/2.0;pVerts[0+i*4].y=y-h/2.0;pVerts[0+i*4].z=z;
	pVerts[1+i*4].x=x+w/2.0;pVerts[1+i*4].y=y-h/2.0;pVerts[1+i*4].z=z;
	pVerts[2+i*4].x=x+w/2.0;pVerts[2+i*4].y=y+h/2.0;pVerts[2+i*4].z=z;
	pVerts[3+i*4].x=x-w/2.0;pVerts[3+i*4].y=y+h/2.0;pVerts[3+i*4].z=z;

			pVerts[0+i*4].u=0;pVerts[0+i*4].v=0;
			pVerts[1+i*4].u=1;pVerts[1+i*4].v=0;
			pVerts[2+i*4].u=1;pVerts[2+i*4].v=1;
			pVerts[3+i*4].u=0;pVerts[3+i*4].v=1;

	pVerts[0+i*4].color=0x00ffffff;
	pVerts[1+i*4].color=0x00ffffff;
	pVerts[2+i*4].color=0x00ffffff;
	pVerts[3+i*4].color=0x00ffffff;

	pVerts[0+i*4].n1=0;pVerts[0+i*4].n2=0;pVerts[0+i*4].n3=0;
	pVerts[1+i*4].n1=0;pVerts[1+i*4].n2=0;pVerts[1+i*4].n3=0;
	pVerts[2+i*4].n1=0;pVerts[2+i*4].n2=0;pVerts[2+i*4].n3=0;
	pVerts[3+i*4].n1=0;pVerts[3+i*4].n2=0;pVerts[3+i*4].n3=0;

	pInds[0+i*6]=0+i*4;pInds[1+i*6]=1+i*4;pInds[2+i*6]=2+i*4;
	pInds[3+i*6]=0+i*4;pInds[4+i*6]=2+i*4;pInds[5+i*6]=3+i*4;
}

	
pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	
	SetMaterial(&WhiteMaterial);

	NumVerts=4*count;
	NumInds=6*count;
	NumTriangles=2*count;

//FlatNormals();
	ApplyMods();
	FillVB(0);
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}

void AddStars()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

int objectX,objectY,objectZ;
//float v = float(GetTickCount()%0xffff)/0xffff * 3.141593f * 20;
int count=Get(CPos,1);

int tx,ty,tz;

	double x,y,z,w,h;int r,g,b;
	
	if (count<1) return;

		SetAlfa(1);

srand(0);
for (int i=0;i<count;i++)
{
	//tx=rand()%10;pVerts[i].x=tx;
	//tx=rand()%10;pVerts[i].y=tx;
	tx=32768*sin((float)i);ty=32768*cos((float)i);
	tx=tx&0xff;ty=ty&0xff;


	pVerts[i].x=(tx/128.0*2-2);
	pVerts[i].y=width*(ty/128.0*1.5-1.5);
	pVerts[i].z=0;

	pVerts[i].color=0x00ffffff;

	pVerts[i].n1=0;
}

			pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
			pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_BLENDOP,1);

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	
	SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,NULL);

	NumVerts=count;

			
					void * pBuf;
				
					pVB[0]->Lock( 0, sizeof(MyVertex) * NumVerts, &pBuf, 0 );
					  memcpy( pBuf, pVerts, sizeof(MyVertex) * NumVerts);
					pVB[0]->Unlock();
					
					pIB[0]->Lock( 0, sizeof(int) * NumInds, &pBuf, 0 );
						memcpy( pBuf, pInds, sizeof(int) * NumInds);
					pIB[0]->Unlock();
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	

	pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, NumVerts);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}

double cubicInterpolate (double p[4], double x) {
	return p[1] + 0.5 * x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

double cubicInterpolateI (double p0,double p1,double p2,double p3, double x) {
	return p1 + 0.5 * x*(p2 - p0 + x*(2.0*p0 - 5.0*p1 + 4.0*p2 - p3 + x*(3.0*(p1 - p2) + p3 - p0)));
}

void TimeLine();

void Curve()
{
CurveCmdPos=CPos;

if (timelinematrix==1)
	{
	pDevice->SetTransform(D3DTS_VIEW,&cv);
		pDevice->SetTransform(D3DTS_WORLD,&World);
	}	


//pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
//if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
curve_len=1;
int objectX,objectY,objectZ;
//float v = float(GetTickCount()%0xffff)/0xffff * 3.141593f * 20;

int tx,ty,tz;

	double x,y,z,w,h;int r,g,b;
	
	int q=Get(CPos,1)+1;

		SetAlfa(Get(CPos,2));

int fill=Get(CPos,3);

int color=Get(CPos,6)|Get(CPos,5)<<8|Get(CPos,4)<<16;

	ApplyMods();
	
	if (curve_len<2) return;

	if (fill==0)
	{
	curve_x[0]=curve_x[1];
	curve_y[0]=curve_y[1];
	curve_z[0]=curve_z[1];
	curve_x[curve_len]=curve_x[curve_len-1];
	curve_y[curve_len]=curve_y[curve_len-1];
	curve_z[curve_len]=curve_z[curve_len-1];
	curve_x[curve_len+1]=curve_x[curve_len];
	curve_y[curve_len+1]=curve_y[curve_len];
	curve_z[curve_len+1]=curve_z[curve_len];
	}
	else
	{
	curve_x[curve_len]=curve_x[1];
	curve_y[curve_len]=curve_y[1];
	curve_z[curve_len]=curve_z[1];
	curve_x[curve_len+1]=curve_x[2];
	curve_y[curve_len+1]=curve_y[2];
	curve_z[curve_len+1]=curve_z[2];
	curve_x[0]=curve_x[curve_len-1];
	curve_y[0]=curve_y[curve_len-1];
	curve_z[0]=curve_z[curve_len-1];
	}
//	curve_len++;


	for (int i=0;i<curve_len*q;i+=q)
	{
		for (int j=0;j<q;j++)
		{
		pVerts[i+j].x=cubicInterpolate(&curve_x[i/q],(float)j/(float)q);
		pVerts[i+j].y=cubicInterpolate(&curve_y[i/q],(float)j/(float)q);
		pVerts[i+j].z=cubicInterpolate(&curve_z[i/q],(float)j/(float)q);
		//pVerts[i+j].z=0;
		pVerts[i+j].color=color;
		}
	
	}

	curve_q=q;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	
	SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,NULL);

	NumVerts=(curve_len-1)*q-1;

			void * pBuf;
		
			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts+1), &pBuf, 0 );
			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts+1));
			pVB[0]->Unlock();
					
					
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	if (fill==0)	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, NumVerts-1);
	if (fill==1) 	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, NumVerts-2);

	//if (height!=width) SetView(0);
		//pDevice->SetTransform(D3DTS_VIEW, &View);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
}


void Text()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
double rw=width;
  LPDIRECT3DSURFACE9 trt;
  pDevice->GetRenderTarget(0,&trt);
  if (trt!=mainRT) width=4/3.0;
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;
float tracking=Get(CPos,10);

	double x,y,z,w,h;int r,g,b;
	objectX=x=width*Get(CPos,1)/1000.0;
	objectY=y=height*Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	w=width*Get(CPos,4)/1000.0;
	h=height*Get(CPos,5)/1000.0;


int ti;float ofsx;
ofsx=0;
for (ti=0;ti<32;ti++)
{
	int letter;
	letter=*(BYTE*)(Pack+CPos+256-33+ti);
	if (letter==0) {goto q;}
	letter-=32;

	pVerts[ti*4+0].x=x-w/2.0+ofsx;pVerts[ti*4+0].y=y+h/2.0;pVerts[ti*4+0].z=z;
	pVerts[ti*4+1].x=x+w/2.0+ofsx;pVerts[ti*4+1].y=y+h/2.0;pVerts[ti*4+1].z=z;
	pVerts[ti*4+2].x=x+w/2.0+ofsx;pVerts[ti*4+2].y=y-h/2.0;pVerts[ti*4+2].z=z;
	pVerts[ti*4+3].x=x-w/2.0+ofsx;pVerts[ti*4+3].y=y-h/2.0;pVerts[ti*4+3].z=z;

	ofsx=ofsx+w*((float)FontPTable[letter])/32.0+tracking/1000;

	int laddr_u,laddr_v;
	float fladdr_u,fladdr_v,qs;

	laddr_u= letter/16;
	laddr_v= letter-laddr_u*16;
	fladdr_u=laddr_u*32/512.0+6/512.0;
	fladdr_v=laddr_v*32/512.0-1/512.0;
	qs=32.0/512.0;

			pVerts[ti*4+0].u=fladdr_u;pVerts[ti*4+0].v=fladdr_v;
			pVerts[ti*4+1].u=fladdr_u+qs;pVerts[ti*4+1].v=fladdr_v;
			pVerts[ti*4+2].u=fladdr_u+qs;pVerts[ti*4+2].v=fladdr_v+qs;
			pVerts[ti*4+3].u=fladdr_u;pVerts[ti*4+3].v=fladdr_v+qs;


    int argb=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

	pVerts[ti*4+0].color=argb;
	pVerts[ti*4+1].color=argb;
	pVerts[ti*4+2].color=argb;
	pVerts[ti*4+3].color=argb;

	pInds[ti*6+0]=ti*4+0;pInds[ti*6+1]=ti*4+1;pInds[ti*6+2]=ti*4+2;
	pInds[ti*6+3]=ti*4+0;pInds[ti*6+4]=ti*4+2;pInds[ti*6+5]=ti*4+3;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	//pDevice->SetTexture(0,FontTexture);
	SetTexture(0,Get(CPos,11),0);

	SetMaterial(&WhiteMaterial);
			
		SetAlfa(Get(CPos,9));

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);
}
q:;
if (Get(CPos,12)==1)
{
if (ptime>= Get(CPos,13))
	{
	ti=min(ti,(ptime-Get(CPos,13))*Get(CPos,14)*.01);
	}
else
	{
	ti=0;
	}
	
}


	NumVerts=4*ti;
	NumInds=6*ti;
	NumTriangles=2*ti;

//FlatNormals();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			ApplyMods();	
					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	width=rw;
}

void LoadText()
{
	char t[100];
		strcpy(t,(char*)(Pack+CPos+256-33));

#ifdef EditMode
				FILE *fp;
				fp = fopen(t, "rb");
				if (fp!=NULL)
				{
				fread(textblock,1,10000,fp);
				fclose(fp);
				}
#else
HRSRC		rec;
HGLOBAL		handle;
rec = FindResource(NULL, MAKEINTRESOURCE(IDR_RAW5),"RAW");
handle = LoadResource(NULL, rec);
memcpy(textblock,LockResource(handle), SizeofResource(NULL, rec));

#endif

}

void TextBlock()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
double rw=width;
  LPDIRECT3DSURFACE9 trt;
  pDevice->GetRenderTarget(0,&trt);
  if (trt!=mainRT) width=4/3.0;
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;
float tracking=Get(CPos,10);

	double x,y,z,w,h;int r,g,b;
	objectX=x=width*Get(CPos,1)/1000.0;
	objectY=y=height*Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	w=width*Get(CPos,4)/1000.0;
	h=height*Get(CPos,5)/1000.0;

int lead=Get(CPos,11);
int start=Get(CPos,12);
int end=Get(CPos,13);
if (start<0) return;

int ti;float ofsx;float ofsy;
ofsx=0;ofsy=0;int counter=0;
ti=0;

float offset;offset=0;

				if (Get(CPos,16)==1) 
				{
					offset=0;
					int p=0;
					while (p<10000&&*(BYTE*)(textblock+counter+start+p)!=0x0d&&
									*(BYTE*)(textblock+counter+start+p)!=0)
					{
						if (*(BYTE*)(textblock+counter+start+p)!=32) offset+=w*((float)FontPTable[*(BYTE*)(textblock+counter+start+p)-32])/32.0+tracking/1000.0;
						else offset+=w*((float)24)/32.0+tracking/1000.0;
						p++;
					}
					offset=-offset/2;
				}

for (counter=0;counter<10000;counter++)
{
	int letter,letter1;
rr:	letter=*(BYTE*)(textblock+counter+start);
	letter1=*(BYTE*)(textblock+counter+start+1);


	if (letter==0) {goto q;}
	//if (letter==0x0d&&letter1==0x0a) 
	//if (letter1==0x0a) {}
	if (letter==0x0d)
		{
			if (Get(CPos,14)==0)
			{
			ofsy+=lead/1000.0;ofsx=0;counter+=2;
			
			//if (*(BYTE*)(textblock+counter+start)==0x0a) counter++;
				if (Get(CPos,16)==1) 
				{
					offset=0;
					int p=0;
					while (p<10000&&*(BYTE*)(textblock+counter+start+p)!=0x0d&&
									*(BYTE*)(textblock+counter+start+p)!=0)
					{
						if (*(BYTE*)(textblock+counter+start+p)!=32) offset+=w*((float)FontPTable[*(BYTE*)(textblock+counter+start+p)-32])/32.0+tracking/1000.0;
						else offset+=w*((float)24)/32.0+tracking/1000.0;
						p++;
					}
					offset=-offset/2;
				}
			
			goto rr;
			}
			else
			{
			letter=32;
			}
		}

	if ((ti+start)>=(end+start)) {goto q;}
	letter-=32;

	pVerts[ti*4+0].x=x-w/2.0+ofsx+offset;pVerts[ti*4+0].y=y+h/2.0-ofsy;pVerts[ti*4+0].z=z;
	pVerts[ti*4+1].x=x+w/2.0+ofsx+offset;pVerts[ti*4+1].y=y+h/2.0-ofsy;pVerts[ti*4+1].z=z;
	pVerts[ti*4+2].x=x+w/2.0+ofsx+offset;pVerts[ti*4+2].y=y-h/2.0-ofsy;pVerts[ti*4+2].z=z;
	pVerts[ti*4+3].x=x-w/2.0+ofsx+offset;pVerts[ti*4+3].y=y-h/2.0-ofsy;pVerts[ti*4+3].z=z;

	ofsx=ofsx+w*((float)FontPTable[letter])/32.0+tracking/1000;

	int laddr_u,laddr_v;
	float fladdr_u,fladdr_v,qs;

	laddr_u= letter/16;
	laddr_v= letter-laddr_u*16;
	fladdr_u=laddr_u*32/512.0+6/512.0;
	fladdr_v=laddr_v*32/512.0-1/512.0;
	qs=32.0/512.0;

			pVerts[ti*4+0].u=fladdr_u;pVerts[ti*4+0].v=fladdr_v;
			pVerts[ti*4+1].u=fladdr_u+qs;pVerts[ti*4+1].v=fladdr_v;
			pVerts[ti*4+2].u=fladdr_u+qs;pVerts[ti*4+2].v=fladdr_v+qs;
			pVerts[ti*4+3].u=fladdr_u;pVerts[ti*4+3].v=fladdr_v+qs;


    int argb=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

	pVerts[ti*4+0].color=argb;
	pVerts[ti*4+1].color=argb;
	pVerts[ti*4+2].color=argb;
	pVerts[ti*4+3].color=argb;

	pInds[ti*6+0]=ti*4+0;pInds[ti*6+1]=ti*4+1;pInds[ti*6+2]=ti*4+2;
	pInds[ti*6+3]=ti*4+0;pInds[ti*6+4]=ti*4+2;pInds[ti*6+5]=ti*4+3;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	//pDevice->SetTexture(0,FontTexture);
	SetTexture(0,Get(CPos,15),0);

	SetMaterial(&WhiteMaterial);
			
		SetAlfa(Get(CPos,9));

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);
	ti++;
}
q:;
	NumVerts=4*ti;
	NumInds=6*ti;
	NumTriangles=2*ti;
	greedx=1;greedy=NumVerts/2;

//FlatNormals();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			ApplyMods();	
					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	width=rw;
}


void AddParticle()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;


	double x,y,z,w,h;int r,g,b;
	objectX=x=width*Get(CPos,1)/1000.0;
	objectY=y=height*Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	w=Get(CPos,4)/1000.0;
	h=Get(CPos,5)/1000.0;

	pVerts[0].x=x-w/2.0;pVerts[0].y=y-h/2.0;pVerts[0].z=z;
	pVerts[1].x=x+w/2.0;pVerts[1].y=y-h/2.0;pVerts[1].z=z;
	pVerts[2].x=x+w/2.0;pVerts[2].y=y+h/2.0;pVerts[2].z=z;
	pVerts[3].x=x-w/2.0;pVerts[3].y=y+h/2.0;pVerts[3].z=z;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

int argb=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

	pVerts[0].color=argb;
	pVerts[1].color=argb;
	pVerts[2].color=argb;
	pVerts[3].color=argb;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;


	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	pDevice->SetTexture(0,RGradTexture);


	SetMaterial(&WhiteMaterial);
		
	SetAlfa(Get(CPos,9));

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

	//FlatNormals();
	//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
	ApplyMods();	
	FillVB(0);
	//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

void Box()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

int vbi;
vbi=CPos;
int objectX,objectY,objectZ;


	double x,y,z,w,h;int r,g,b;
	objectX=x=width*Get(CPos,1)/1000.0;
	objectY=y=height*Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	w=Get(CPos,4)/1000.0;
	h=Get(CPos,5)/1000.0;
	r=Get(CPos,6);
	g=Get(CPos,7);
	b=Get(CPos,8);


	pVerts[0].x=x-w/2.0;pVerts[0].y=y-h/2.0;pVerts[0].z=z;
	pVerts[1].x=x+w/2.0;pVerts[1].y=y-h/2.0;pVerts[1].z=z;
	pVerts[2].x=x+w/2.0;pVerts[2].y=y+h/2.0;pVerts[2].z=z;
	pVerts[3].x=x-w/2.0;pVerts[3].y=y+h/2.0;pVerts[3].z=z;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

 int argb=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

	pVerts[0].color=argb;
	pVerts[1].color=argb;
	pVerts[2].color=argb;
	pVerts[3].color=argb;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

//	pDevice->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_ARGB(0,r,g,b));

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetAlfa(Get(CPos,9));

		pDevice->SetTexture(0,NULL);
	SetMaterial(&WhiteMaterial);


	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

//FlatNormals();
	ApplyMods();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
				FillVB(0);
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);

	//pDevice->SetPixelShader(NULL);
	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

void Ellipse()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

//int vbi;
//vbi=CPos;
int objectX,objectY,objectZ;


	double x,y,z,w,h;int r,g,b;
	objectX=x=width*Get(CPos,1)/1000.0;
	objectY=y=height*Get(CPos,2)/1000.0;
	
	w=Get(CPos,3)/1000.0/2.0;
	h=Get(CPos,4)/1000.0/2.0;
	int q=Get(CPos,5);


	int argb=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

	pVerts[0].x=x;pVerts[0].y=y;pVerts[0].z=0;pVerts[0].color=argb;
	float step=360/(double)q;

	if (q<2) return;
int i=1;
for (i=1;i<=q;i++)
{
	pVerts[i].x=x+w*sin(step*(i-1)*PI/180.0);
	pVerts[i].y=y+h*cos(step*(i-1)*PI/180.0);
	
	
	pVerts[i].z=0;
	pVerts[i].color=argb;
}

	

	pVerts[i].x=0;pVerts[0].y=y+h;pVerts[i].z=0;pVerts[i].color=argb;

//i++;
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);


SetAlfa(Get(CPos,9));

		pDevice->SetTexture(0,NULL);
	SetMaterial(&WhiteMaterial);



	NumVerts=i;
		;
ApplyMods();
//FlatNormals();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
				
					void * pBuf;
//vbi=0;


					pVB[0]->Lock( 0, sizeof(MyVertex) * NumVerts, &pBuf, 0 );
					  memcpy( pBuf, pVerts, sizeof(MyVertex) * NumVerts);
					pVB[0]->Unlock();
					
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
		
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, NumVerts-2);
	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

void Plasm()
{
	pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
int vbi;int count=Get(CPos,1);
vbi=CPos;
int objectX,objectY,objectZ;


	double x,y,z,w,h;int r,g,b;

	w=4;
	h=3*width;


	int rgba1=D3DCOLOR_RGBA(Get(CPos,2),Get(CPos,3),Get(CPos,4),0);

	pVerts[0].x=-w/2.0;pVerts[0].y=-h/2.0;pVerts[0].z=0;
	pVerts[1].x=w/2.0;pVerts[1].y=-h/2.0;pVerts[1].z=0;
	pVerts[2].x=w/2.0;pVerts[2].y=h/2.0;pVerts[2].z=0;
	pVerts[3].x=-w/2.0;pVerts[3].y=h/2.0;pVerts[3].z=0;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=count;pVerts[1].v=0;
			pVerts[2].u=count;pVerts[2].v=count;
			pVerts[3].u=0;pVerts[3].v=count;

	pVerts[0].color=rgba1;
	pVerts[1].color=rgba1;
	pVerts[2].color=rgba1;
	pVerts[3].color=rgba1;


	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	
SetAlfa(Get(CPos,5));

		pDevice->SetTexture(0,PlasmTexture);
	SetMaterial(&WhiteMaterial);


	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

//FlatNormals();
ApplyMods();
				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
				FillVB(0);
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}



void TMixer()
{
//  pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,0);
 // pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,0);
 // pDevice->SetSamplerState(1,D3DSAMP_MAGFILTER,0);
 // pDevice->SetSamplerState(1,D3DSAMP_MINFILTER,0);

	CpyToPrev2(0);

	//if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);



	pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
	pDevice->SetTransform(D3DTS_WORLD, &StartMatrix);
int vbi;int s1,s2;
vbi=CPos;

s1=Get(CPos,1);
s2=Get(CPos,2);

	double x,y,z,w,h;

	w=4;h=4;

	if (width==height) {w=4;h=4*(1/screen_ratio);} else {w=4;h=4;}
	//if (width==height) {h=3;w=4;}

	

	int rgba1=D3DCOLOR_RGBA(Get(CPos,4),Get(CPos,4),Get(CPos,4),0);
	int rgba2=D3DCOLOR_RGBA(Get(CPos,5),Get(CPos,5),Get(CPos,5),0);

	pVerts[0].x=-w/2.0;pVerts[0].y=h/2.0;pVerts[0].z=0;
	pVerts[1].x=w/2.0-.5/screen_width;pVerts[1].y=h/2.0;pVerts[1].z=0;
	pVerts[2].x=w/2.0-.5/screen_width;pVerts[2].y=-h/2.0+.5/screen_height;pVerts[2].z=0;
	pVerts[3].x=-w/2.0;pVerts[3].y=-h/2.0+.5/screen_height;pVerts[3].z=0;

//	for (int i=0;i<4;i++)
///	{
//	pVerts[i].x-=.5/1024.0;
//	pVerts[i].y+=.5/768.0;
//	pVerts[i].x+=1/256.0;
//	pVerts[i].y-=1/256.0;
//	}

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	for (int i=0;i<4;i++)
	{
//	pVerts[i].u+=.5/512.0;
//	pVerts[i].v+=.5/512.0;

	pVerts[i].u+=.5/2048.0;
	pVerts[i].v+=.5/2048.0;

	}

	pVerts[0].color=rgba1;
	pVerts[1].color=rgba1;
	pVerts[2].color=rgba1;
	pVerts[3].color=rgba1;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

//

		pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_CURRENT );
		pDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );

	SetAlfa(0);
		

	//pDevice->SetTexture(0,Texture[s1]);
	SetTexture(0,s1,0);

	
	SetMaterial(&WhiteMaterial);

		pDevice->SetTextureStageState( 1, D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2 );			 
		pDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU );

		int mm[15]={1,2,3,4,5,D3DTOP_MODULATE,D3DTOP_MODULATE2X,D3DTOP_MODULATE4X,D3DTOP_ADD,D3DTOP_ADDSIGNED,
			D3DTOP_ADDSIGNED2X, D3DTOP_SUBTRACT,D3DTOP_ADDSMOOTH,D3DTOP_MODULATEALPHA_ADDCOLOR,D3DTOP_DOTPRODUCT3};
    
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	if (Get(CPos,3)>=0&&Get(CPos,3)<5) 
	{

		
		FillVB(0);
		
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);			
		
		SetAlfa(mm[Get(CPos,3)]);
		
		pVerts[0].color=rgba2;
		pVerts[1].color=rgba2;
		pVerts[2].color=rgba2;
		pVerts[3].color=rgba2;

		FillVB(0);
		//pDevice->SetTexture(0,Texture[s2]);
		SetTexture(0,s2,0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);			


	}

	if (Get(CPos,3)>=5&&Get(CPos,3)<16) 
	{

		pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, mm[Get(CPos,3)]);
	
		FillVB(0);
		//pDevice->SetTexture(1,Texture[s2]);
		SetTexture(1,s2,1);
		
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);			
		pDevice->SetTextureStageState( 1, D3DTSS_COLOROP,D3DTOP_DISABLE  );			 
	}

	if (Get(CPos,3)==16)
	{
		FillVB(0);

		pDevice->SetTexture( 0, PrevStageTexture );
		//pDevice->SetTexture( 1, Texture[s1]);
		//pDevice->SetTexture( 2, Texture[s2]);
		SetTexture(1,s1,0);
		SetTexture(2,s2,1);

		// Stage 0: The base texture
		pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ); 

		// Stage 1: T.
		pDevice->SetTextureStageState( 1, D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU );

		pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_BUMPENVMAP);
		pDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );

		// Stage 2: 
		pDevice->SetTextureStageState( 2, D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU );

		pDevice->SetTextureStageState( 2, D3DTSS_COLOROP, D3DTOP_MODULATE  );
		pDevice->SetTextureStageState( 2, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( 2, D3DTSS_COLORARG2, D3DTA_DIFFUSE  );

		pDevice->SetTextureStageState( 1, D3DTSS_BUMPENVMAT00, F2DW(1.0f) );
		pDevice->SetTextureStageState( 1, D3DTSS_BUMPENVMAT01, F2DW(0.0f) );
		pDevice->SetTextureStageState( 1, D3DTSS_BUMPENVMAT10, F2DW(0.0f) );
		pDevice->SetTextureStageState( 1, D3DTSS_BUMPENVMAT11, F2DW(1.0f) );	

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	pDevice->SetTexture(1,NULL);
	
	//pDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_DISABLE  );			 
	pDevice->SetTextureStageState( 1, D3DTSS_COLOROP,D3DTOP_DISABLE  );			 
	pDevice->SetTextureStageState( 2, D3DTSS_COLOROP,D3DTOP_DISABLE  );		

	}


//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
		
  pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,2);
  pDevice->SetSamplerState(1,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(1,D3DSAMP_MINFILTER,2);
}

//obsolete
void Crossfade ()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
float px=3;float py=3;
int tpx=3;int tpy=3;

int h=3*width;int w=4;int vc=0;
float x,y,sx,sy;

float ofsx=(-2000+Get(CPos,1))/1000.0;
int axis=Get(CPos,2);


RECT SourceRect;
SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );


		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		PrevStageTexture->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,NULL,D3DTEXF_NONE);
		RT->Release();
		RT2->Release();

		pDevice->SetTexture(0,PrevStageTexture);

y=-1.5*width; sx=4.0/px;sy=width*3.0/py;

px++;py++;
tpx++;tpy++;

vc=0;

int i,j;

if (axis==0)
{
	for(i=0;i<py;i++)
	{	
	x=-2;
		for(j=0;j<px;j++)
		{
			pVerts[vc].x=-x;pVerts[vc].u=(-x+2)/4.0;
			if (j==1) {pVerts[vc].x=-ofsx;pVerts[vc].u=(-ofsx+2)/4.0;}
			if (j==2) {pVerts[vc].x=ofsx;pVerts[vc].u=(ofsx+2)/4.0;}
			
			pVerts[vc].y=-y;pVerts[vc].z=0;

			pVerts[vc].v=(float)i/(py-1);

			pVerts[vc].color=0x00ffffff;
			if (j==0||j==3) pVerts[vc].color=0x00808080;
			vc++;
			x+=sx;
		}
	y+=sy;
	}
}
else
{
	for(i=0;i<py;i++)
	{	
	x=-2;
		for(j=0;j<px;j++)
		{
			pVerts[vc].y=y;pVerts[vc].v=1-(float)i/(py-1);
		
			if (width!=height)
			{
			if (i==1) {pVerts[vc].y=ofsx;pVerts[vc].v=(-ofsx+2)/4.0;}
			if (i==2) {pVerts[vc].y=-ofsx;pVerts[vc].v=(ofsx+2)/4.0;}
			}
			else
			{
			if (i==1) {pVerts[vc].y=ofsx;pVerts[vc].v=(-ofsx+1.5)/3.0;}
			if (i==2) {pVerts[vc].y=-ofsx;pVerts[vc].v=(ofsx+1.5)/3.0;}
			}

			pVerts[vc].x=-x;pVerts[vc].z=0;
			pVerts[vc].u=-(float)j/(px-1);
			pVerts[vc].color=0x00ffffff;
			if (i==0||i==3) pVerts[vc].color=0x00808080;
			vc++;
			x+=sx;
		}
	y+=sy;
	}
}

NumVerts=vc;

vc=0;
for(i=0;i<py-1;i++)
	{	
		for(j=0;j<px-1;j+=1)
		{
			pInds[vc+0]=i*tpx+j;
			pInds[vc+1]=i*tpx+j+1;
			pInds[vc+2]=(i+1)*tpx+j;
			pInds[vc+3]=i*tpx+j+1;
			pInds[vc+4]=(i+1)*tpx+j+1;
			pInds[vc+5]=(i+1)*tpx+j;
			vc+=6;
			
		}
	}
NumInds=vc;
NumTriangles=vc/3;

	SetAlfa(0);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1); 
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	SetMaterial(&WhiteMaterial);


FillVB(0);
	
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);

//---------

	y=-1.5*width;vc=0;

if (axis==0)
{
	for(i=0;i<py;i++)
	{	
	x=-2;
		for(j=0;j<px;j++)
		{
			pVerts[vc].x=-x;pVerts[vc].y=-y;pVerts[vc].z=0;
			pVerts[vc].u=(x+2)/4.0;

			pVerts[vc].v=(float)i/(py-1);

			pVerts[vc].color=0;
			if (j==1) {pVerts[vc].x=-ofsx;pVerts[vc].u=(ofsx+2)/4.0;}
			if (j==2) {pVerts[vc].x=ofsx;pVerts[vc].u=(-ofsx+2)/4.0;}			
			if (j==0||j==3) pVerts[vc].color=0x00808080;;
			vc++;
			x+=sx;
		}
	y+=sy;
	}
}
else
{
	for(i=0;i<py;i++)
	{	
	x=-2;
		for(j=0;j<px;j++)
		{
			pVerts[vc].y=-y;pVerts[vc].v=1-(float)i/(py-1);
		
			if (width!=height)
			{
			if (i==1) {pVerts[vc].y=-ofsx;pVerts[vc].v=(-ofsx+2)/4.0;}
			if (i==2) {pVerts[vc].y=ofsx;pVerts[vc].v=(ofsx+2)/4.0;}
			}
			else
			{
			if (i==1) {pVerts[vc].y=-ofsx;pVerts[vc].v=(-ofsx+1.5)/3.0;}
			if (i==2) {pVerts[vc].y=ofsx;pVerts[vc].v=(ofsx+1.5)/3.0;}
			}

			pVerts[vc].x=-x;pVerts[vc].z=0;
			pVerts[vc].u=-(float)j/(px-1);
			pVerts[vc].color=0x00808080;
			if (i==1||i==2) pVerts[vc].color=0;
			vc++;
			x+=sx;
		}
	y+=sy;
	}
}
FillVB(0);
SetAlfa(1);
pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}









void MpGrad()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
//CpyToPrev();
//BlackQuad();
//pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

float px=Get(CPos,1);float py=1;//Get(CPos,2);
int tpx=Get(CPos,1);int tpy=1;//Get(CPos,2);

greedx=px;greedy=py;

int vc=0;
float x,y,sx,sy;

if (px==0||py==0) return;

y=2; sx=4.0/px;sy=-4.0/py;
float v,dv;
v=0;dv=1.0/py;
px++;py++;
tpx++;tpy++;

vc=0;

	int i,j;
	for(i=0;i<py;i++)
		{	
		x=-2;
			for(j=0;j<px;j++)
			{
				pVerts[vc].x=x;pVerts[vc].y=y;pVerts[vc].z=0;
				pVerts[vc].u=(x+2)/4.0;
				
				pVerts[vc].v=v;
				
				pVerts[vc].color=Get32(CPos,2+j);
				vc++;
				x+=sx;
			}
		v+=dv;
		y+=sy;
		}

	NumVerts=vc;

	vc=0;
	for(i=0;i<py-1;i++)
		{	
			for(j=0;j<px-1;j+=1)
			{
				pInds[vc+0]=i*tpx+j;
				pInds[vc+1]=i*tpx+j+1;
				pInds[vc+2]=(i+1)*tpx+j;
				pInds[vc+3]=i*tpx+j+1;
				pInds[vc+4]=(i+1)*tpx+j+1;
				pInds[vc+5]=(i+1)*tpx+j;
				vc+=6;
				
			}
		}
	NumInds=vc;
	NumTriangles=vc/3;

//pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(0,0,0,0),8.0f,0);

	pDevice->SetTexture(0,WhiteTexture);
	SetAlfa(0);
				
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetMaterial(&WhiteMaterial);

	ApplyMods();
	FillVB(0);
	
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
		
//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}

//obsolete
void LGradient()
{
int vbi;
	pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	int rgba1=D3DCOLOR_RGBA(Get(CPos,1),Get(CPos,2),Get(CPos,3),0);
	int rgba2=D3DCOLOR_RGBA(Get(CPos,4),Get(CPos,5),Get(CPos,6),0);

	double x,y,z,w,h;int r,g,b;

	w=4;
	h=4;//*width;

	pVerts[0].x=-w/2.0;pVerts[0].y=-h/2.0;pVerts[0].z=0;
	pVerts[1].x=w/2.0;pVerts[1].y=-h/2.0;pVerts[1].z=0;
	pVerts[2].x=w/2.0;pVerts[2].y=h/2.0;pVerts[2].z=0;
	pVerts[3].x=-w/2.0;pVerts[3].y=h/2.0;pVerts[3].z=0;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	pVerts[0].color=rgba1;
	pVerts[1].color=rgba1;
	pVerts[2].color=rgba2;
	pVerts[3].color=rgba2;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;


	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);
	 
		SetAlfa(Get(CPos,7));	
		pDevice->SetTexture(0,WhiteTexture);
	SetMaterial(&WhiteMaterial);


	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

	//FlatNormals();

	//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
	ApplyMods();				
	FillVB(0);
					
	//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}




void Chess()
{
int vbi;
int CountX=Get(CPos,1);
int CountY=Get(CPos,2);
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
	double w,h,x,y,z;int r,g,b;
int i=0;
if (CountX<1||CountY<1) return;

	w=4.0/((double)CountX);
	h=4.0/((double)CountY);//*width;

int t,tt;

	int rgba1=D3DCOLOR_RGBA(Get(CPos,3),Get(CPos,4),Get(CPos,5),0);
	int rgba2=D3DCOLOR_RGBA(Get(CPos,6),Get(CPos,7),Get(CPos,8),0);

y=-2;//*width;
for (tt=0;tt<CountY;tt++)
{
   x=-2.0;
   
  for (t=0;t<CountX;t++)
  {

	pVerts[0+i*4].x=x;pVerts[0+i*4].y=y;pVerts[0+i*4].z=0;
	pVerts[1+i*4].x=x+w;pVerts[1+i*4].y=y;pVerts[1+i*4].z=0;
	pVerts[2+i*4].x=x+w;pVerts[2+i*4].y=y+h;pVerts[2+i*4].z=0;
	pVerts[3+i*4].x=x;pVerts[3+i*4].y=y+h;pVerts[3+i*4].z=0;

			pVerts[0+i*4].u=0;pVerts[0+i*4].v=0;
			pVerts[1+i*4].u=1;pVerts[1+i*4].v=0;
			pVerts[2+i*4].u=1;pVerts[2+i*4].v=1;
			pVerts[3+i*4].u=0;pVerts[3+i*4].v=1;

	if ((((int)(t/2))*2+tt)==(t+((int)(tt/2))*2))
	{
	pVerts[0+i*4].color=rgba1;
	pVerts[1+i*4].color=rgba1;
	pVerts[2+i*4].color=rgba1;
	pVerts[3+i*4].color=rgba1;
	}
	else
	{
	pVerts[0+i*4].color=rgba2;
	pVerts[1+i*4].color=rgba2;
	pVerts[2+i*4].color=rgba2;
	pVerts[3+i*4].color=rgba2;
	}



	pInds[0+i*6]=0+i*4;pInds[1+i*6]=1+i*4;pInds[2+i*6]=2+i*4;
	pInds[3+i*6]=0+i*4;pInds[4+i*6]=2+i*4;pInds[5+i*6]=3+i*4;

	x+=w;
	i++;
	}
y+=h;
}
	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetAlfa(Get(CPos,9));	 
	
		pDevice->SetTexture(0,NULL);
	SetMaterial(&WhiteMaterial);


	NumVerts=4*(i);
	NumInds=6*(i);
	NumTriangles=2*(i);

//FlatNormals();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем

	ApplyMods();
				
					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

int AnimaType=0;

void SetFreq(){for(int h=1;h<21;h++) freq[h]=Get(CPos,h);}
void SetAmp(){for(int h=1;h<21;h++) {amp[h]=Get(CPos,h);}}
void SetPhase(){for(int h=1;h<21;h++) phase[h]=Get(CPos,h);}

void AnimaClampMax()
{
for(int h=1;h<21;h++) {clampmax[h]=Get(CPos,h);}
}

void AnimaClampMin()
{
for(int h=1;h<21;h++) {clampmin[h]=Get(CPos,h);}
}



void AnimaClampMode()
{
clampmode=Get(CPos,1);
}

short pclamp(short a,int j)
{
if (clampmode==1)
{
if (a>clampmax[j]) return clampmax[j];
if (a<clampmin[j]) return clampmin[j];
}

return a;
}


void AnimaSin () {AnimaType=0;}
void AnimaLinear () {AnimaType=1;}
void AnimaPow2 () {AnimaType=2;}
void AnimaPow3 () {AnimaType=3;}
void AnimaSqrt () {AnimaType=4;}
void AnimaRandom () {AnimaType=5;}
void Anima2Sqrt () {AnimaType=6;}
void AnimaAbsSin () {AnimaType=8;}

int splinenum[100];
void AnimaSpline () 
{
AnimaType=7;
for(int h=1;h<21;h++) splinenum[h]=Get(CPos,h);
}


void AnimP()
{
//	return;
//double a;float b;
float a;float b;

if (CmdDesc[Get(CPos,0)].FRoutine==AnimaClampMax) return;
if (CmdDesc[Get(CPos,0)].FRoutine==AnimaClampMin) return;
if (CmdDesc[Get(CPos,0)].FRoutine==AnimaClampMode) return;
if (CmdDesc[Get(CPos,0)].FRoutine==SetFreq) return;
if (CmdDesc[Get(CPos,0)].FRoutine==SetAmp) return;
if (CmdDesc[Get(CPos,0)].FRoutine==SetPhase) return;
if (CmdDesc[Get(CPos,0)].FRoutine==AnimaSpline) return;


if (AnimaType==7)
{
			short i;
			i= 0;

	for(int j=1;j<21;j++)
	{
		if (freq[j]!=0)
		{
			int a;
			a=*(short*)(RExchange+CPos+j*2);
			float x,y;y=0;
			//x=freq[j]*ptime/1000.0;
			x=ptime/1000.0;
			//x=gtime;
			int sp=splinenum[j];
			//sp=0;

			//search interval
			for (int k=0;k<1024*10-1;k++)
			{
				int cal=curvearray_clen[sp]-2;
				if (cal>1000) cal=1000;
				if (x>curvearray_x[sp][cal]) {y=curvearray_x[sp][cal];break;}
				if (x<0) {y=curvearray_x[sp][0];break;}

			if (x>curvearray_x[sp][k]&&x<=curvearray_x[sp][k+1]) 
				{
				y=lerp(curvearray_y[sp][k+1],curvearray_y[sp][k],(x-curvearray_x[sp][k])/(curvearray_x[sp][k+1]-curvearray_x[sp][k]));
				break;
				}	

			}
			a+=y*1000;
			Put(CPos,j,a);
		}
	}
}

if (AnimaType==5)
{
			short i;
			i= 0;

	for(int j=1;j<21;j++)
	{
		if (freq[j]!=0)
		{
			
			Put(CPos,j,(short)pclamp((rand()*2-32767)*amp[j]/32768,j));
		}
	}
}
if (AnimaType==8)
{
	for(int j=1;j<21;j++)
	{
		a=*(short*)(RExchange+CPos+j*2)+amp[j]*fabs(sin(ptime*freq[j]*amp[j]/1000.0/10.0/100.0+phase[j]*PI/180.0));	
		a=pclamp(a,j);
		Put(CPos,j,(int)a);
	}
}

if (AnimaType==0)
{
	for(int j=1;j<21;j++)
	{
		a=*(short*)(RExchange+CPos+j*2)+amp[j]*sin(ptime*freq[j]*amp[j]/1000.0/10.0/100.0+phase[j]*PI/180.0);	
		a=pclamp(a,j);
		Put(CPos,j,(int)a);
	}
}
if (AnimaType==1)
{
	
	double r;
	for(int j=1;j<21;j++)
	{
	if (freq[j]!=0)
		{
			r=(((double)ptime)*freq[j]/100.0)*amp[j]/1000.0/10.0+phase[j];
			b=r-amp[j]*((int)(r/amp[j]));
			b=b+*(short*)(RExchange+CPos+j*2);
			b=pclamp(b,j);
			Put(CPos,j,(int)b);
		}
	}
}

if (AnimaType==2)
{
	
	double r,f,g,h; short p;
	for(int j=1;j<21;j++)
	{
	if (freq[j]!=0)
		{
			r=(((double)ptime)*freq[j])*amp[j]/1000.0/10.0+phase[j];
			f=r-amp[j]*((int)(r/amp[j]));
			g=((f/(double)amp[j])*(f/(double)amp[j]))*(double)amp[j];
			h=g+*(short*)(RExchange+CPos+j*2);
			p=(short)h;
			p=pclamp(p,j);
			Put(CPos,j,p);
		}
	}
}

if (AnimaType==3)
{
	
	double r,f,g,h; short p;
	for(int j=1;j<21;j++)
	{
	if (freq[j]!=0)
		{
			r=(((double)ptime)*freq[j])*amp[j]/1000.0/10.0+phase[j];
			f=r-amp[j]*((int)(r/amp[j]));
			g=((f/(double)amp[j])*(f/(double)amp[j])*(f/(double)amp[j]))*(double)amp[j];
			h=g+*(short*)(RExchange+CPos+j*2);
			p=(short)h;
			p=pclamp(p,j);
			Put(CPos,j,p);
		}
	}
}

if (AnimaType==4)
{
	
	double r,f,g,h; short p;
	for(int j=1;j<21;j++)
	{
	if (freq[j]!=0)
		{
			r=(((double)ptime)*freq[j])*amp[j]/1000.0/10.0+phase[j];
			f=r-amp[j]*((int)(r/amp[j]));
			g=(sqrt(sqrt((f/(double)amp[j]))))*(double)amp[j];
			h=g+*(short*)(RExchange+CPos+j*2);
			p=(short)h;
			p=pclamp(p,j);
			Put(CPos,j,p);
		}
	}
}

if (AnimaType==6)
{
	
	double r,f,g,h; short p;
	for(int j=1;j<21;j++)
	{
	if (freq[j]!=0)
		{
			r=(((double)ptime)*freq[j])*amp[j]/1000.0/10.0+phase[j];
			f=r-amp[j]*((int)(r/amp[j]));
			g=((sqrt((f/(double)amp[j]))))*(double)amp[j];
			h=g+*(short*)(RExchange+CPos+j*2);
			p=(short)h;
			p=pclamp(p,j);
			Put(CPos,j,p);
		}
	}
}


}



void TextureToTexture()
{
	
	//if (Get(CPos,1)<0||Get(CPos,1)>255) return;
	if (Get(CPos,1)>255) return;
	if (Get(CPos,1)<0) return;

		RECT SourceRect;
		RECT DestRect;
		SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
		
		SetRect(&DestRect, 0, 0, 512, 512);


		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT2);
		//pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)Get(CPos,2));

		if (current_rt==-1) {
			pDevice->GetRenderTarget(0,&RT); 
			pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)Get(CPos,2));
		}
		else { 
			Texture[current_rt]->GetSurfaceLevel(0,&RT);
			pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_NONE);
		}

		RT->Release();
		RT2->Release();

		//pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)Get(CPos,2));

		//D3DXSaveTextureToFile(destfile,0,Texture[Get(CPos,1)],NULL);
		//D3DXSaveSurfaceToFile("shot.bmp",D3DXIFF_BMP ,RT2,NULL,&DestRect);
		
		//Texture[Get(CPos,1)]->GenerateMipSubLevels();//??? или где бы ее воткнуть...
		
		if (Get(CPos,3)==1) MipGenT(Get(CPos,1));
}


void CreateMipMaps()
{
if (current_rt>=0)
{
MipGenT(current_rt);
}

}

void ScreenToTexture()
{
	if (Get(CPos,1)<0||Get(CPos,1)>255) return;

		RECT SourceRect;
		SetRect(&SourceRect, 0, 0, screen_width, screen_height );
		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,NULL,(D3DTEXTUREFILTERTYPE)Get(CPos,2));
		RT->Release();
		RT2->Release();

		if (Get(CPos,3)==1) MipGenT(Get(CPos,1));
}


void CalcIndicies()
{
int k=0;int ty,tx;
for (ty=0;ty<greedy;ty++)
	{
	for (tx=0;tx<greedx;tx++)
		{
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=ty*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx+1;		
		k+=3;
		
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=(ty+1)*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx;		
		k+=3;
		}
	}
}

void Flat()
{
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;

if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double x,y,z,w,h;int r,g,b;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	w=width*Get(CPos,4)/1000.0;
	h=height*Get(CPos,5)/1000.0;

	int k=0;
greedx=1;greedy=1;

for (int ty=greedy;ty>=0;ty--)
	{
	for (int tx=0;tx<=greedx;tx++)
		{
			pVerts[k].x=x+w*tx/greedx-w/2.0;
			pVerts[k].z=z;
			pVerts[k].y=y+h*ty/greedy-h/2.0;
			
			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(greedx);
			pVerts[k].v=(double)ty/(double)(greedy);
		k++;
		}
	}

	CalcIndicies();

	NumVerts=(greedx+1)*(greedy+1);
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);

	//pDevice->SetTexture(0,FontTexture);
	SetTexture(0,Get(CPos,6),0);

	SetMaterial(&Material[Get(CPos,7)]);
		
	SetAlfa(Get(CPos,9));

	NumVerts=4;
	NumInds=6;
	NumTriangles=2;





				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			ApplyMods();	

			FlatNormals();

					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
//	DrawNormals();
}

void FillMaterial()
{
	int m;
	m=Get(CPos,1);

// Set the RGBA for ambient reflection.
Material[m].Ambient.r = Get(CPos,2)/256.0;
Material[m].Ambient.g = Get(CPos,3)/256.0;
Material[m].Ambient.b = Get(CPos,4)/256.0;
Material[m].Ambient.a = Get(CPos,5)/256.0;
	
// Set the RGBA for diffuse reflection.
Material[m].Diffuse.r = Get(CPos,6)/256.0;
Material[m].Diffuse.g = Get(CPos,7)/256.0;
Material[m].Diffuse.b = Get(CPos,8)/256.0;
Material[m].Diffuse.a = Get(CPos,9)/256.0;

// Set the color and sharpness of specular highlights.
Material[m].Specular.r = Get(CPos,10)/256.0;
Material[m].Specular.g = Get(CPos,11)/256.0;
Material[m].Specular.b = Get(CPos,12)/256.0;
Material[m].Power = Get(CPos,13);

// Set the RGBA for emissive color.
Material[m].Emissive.r = Get(CPos,14)/256.0;
Material[m].Emissive.g = Get(CPos,15)/256.0;
Material[m].Emissive.b = Get(CPos,16)/256.0;
Material[m].Emissive.a = Get(CPos,17)/256.0;

}

void PointLight()
{
int m;m=Get(CPos,1);
SceneLight[m].Type=D3DLIGHT_POINT;

SceneLight[m].Direction.x=0.0;
SceneLight[m].Direction.y=0.0;
SceneLight[m].Direction.z=0.0;

SceneLight[m].Position.x=Get(CPos,2)/1000.0;
SceneLight[m].Position.y=Get(CPos,3)/1000.0;
SceneLight[m].Position.z=Get(CPos,4)/1000.0+1;
SceneLight[m].Range=Get(CPos,5)/1000.0;

SceneLight[m].Ambient.r=Get(CPos,6)/256.0;
SceneLight[m].Ambient.g=Get(CPos,7)/256.0;
SceneLight[m].Ambient.b=Get(CPos,8)/256.0;

SceneLight[m].Diffuse.r=Get(CPos,9)/256.0;
SceneLight[m].Diffuse.g=Get(CPos,10)/256.0;
SceneLight[m].Diffuse.b=Get(CPos,11)/256.0;

SceneLight[m].Specular.r=Get(CPos,12)/256.0;
SceneLight[m].Specular.g=Get(CPos,13)/256.0;
SceneLight[m].Specular.b=Get(CPos,14)/256.0;

SceneLight[m].Attenuation0=Get(CPos,15)/256.0;
SceneLight[m].Attenuation1=Get(CPos,16)/256.0;
SceneLight[m].Attenuation2=Get(CPos,17)/256.0;



pDevice->LightEnable(m,TRUE); 
pDevice->SetLight(m,&SceneLight[m]);

//interface
#ifdef EditMode 
if (Pos==CPos)
{
	pDevice->SetTexture(0,NULL);
	show_ms(SceneLight[m].Position.x,SceneLight[m].Position.y,SceneLight[m].Position.z-1,0.02);
}
#endif
}


void DirectionalLight()
{
int m;m=Get(CPos,1);
SceneLight[m].Type=D3DLIGHT_DIRECTIONAL;
	
	SceneLight[m].Attenuation0=0;
	SceneLight[m].Attenuation1=1;
	SceneLight[m].Attenuation2=1;
	SceneLight[m].Falloff=1;

SceneLight[m].Direction.x=-Get(CPos,2)/1000.0;
SceneLight[m].Direction.y=-Get(CPos,3)/1000.0;
SceneLight[m].Direction.z=-Get(CPos,4)/1000.0;

SceneLight[m].Ambient.r=Get(CPos,5)/256.0;
SceneLight[m].Ambient.g=Get(CPos,6)/256.0;
SceneLight[m].Ambient.b=Get(CPos,7)/256.0;

SceneLight[m].Diffuse.r=Get(CPos,8)/256.0;
SceneLight[m].Diffuse.g=Get(CPos,9)/256.0;
SceneLight[m].Diffuse.b=Get(CPos,10)/256.0;

SceneLight[m].Specular.r=Get(CPos,11)/256.0;
SceneLight[m].Specular.g=Get(CPos,12)/256.0;
SceneLight[m].Specular.b=Get(CPos,13)/256.0;

pDevice->LightEnable(m,TRUE); 
pDevice->SetLight(m,&SceneLight[m]);

//interface
#ifdef EditMode 
if (Pos==CPos)
{
	pDevice->SetTexture(0,NULL);
	show_ms(-SceneLight[m].Direction.x,-SceneLight[m].Direction.y,-SceneLight[m].Direction.z,.02);
}
#endif
}





void SetCull()
{
if (Get(CPos,1)>=0&&Get(CPos,1)<3) pDevice->SetRenderState(D3DRS_CULLMODE, Get(CPos,1)+1);	
}


//#include "rt_data.h"
void RawTriangles()
{

}

void Sphere()
{

if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);

	double a,b,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));

	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	if (greedx*greedy==0) return;

	k=0;
for (ty=0;ty<=greedy;ty++)
	{
	b=ty*360.0/(double)greedy;
	for (tx=0;tx<=greedx;tx++)
		{
		a=tx*360.0/(double)greedx;
			pVerts[k].x=x+xs*cos(a*PI/180.0)*sin(b*PI/180.0/2.0)/2.0;
			pVerts[k].z=z+zs*sin(a*PI/180.0)*sin(b*PI/180.0/2.0)/2.0;
			pVerts[k].y=y+ys*cos(b*PI/180.0/2.0)/2.0;
			
			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(greedx);
			pVerts[k].v=(double)ty/(double)(greedy);

			pVerts[k].u1=k;
		k++;
		}
	}

	CalcIndicies();

	NumVerts=(greedx+1)*(greedy+1);//чтобы не париться с заворотом посчитали 360 включительно
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;
	
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	
	ApplyMods();

	Svertka2Normals();

	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	

//pDevice->SetPixelShader(NULL);
//pDevice->SetVertexShader(NULL);


	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		

	SetAlfa(0);
if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);

}



void SubdividedCube()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

double a,b,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));

	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	if (greedx*greedy==0) return;

	k=0;

	int cgrd_x,cgrd_y;
	cgrd_x=greedx;
	cgrd_y=greedy;

for (int p=0;p<6;p++)
{
cube_i[p]=k;
for (ty=cgrd_y;ty>=0;ty--)
	{
	for (tx=0;tx<=cgrd_x;tx++)
		{
			switch (p)
			{
			case 0:
				{
				pVerts[k].x=x+xs*tx/cgrd_x-xs/2.0;
				pVerts[k].z=z-zs/2.0;
				pVerts[k].y=y+ys*ty/cgrd_y-ys/2.0;
				break;
				}
			case 1:
				{
				pVerts[k].x=x-(xs*tx/cgrd_x-xs/2.0);
				pVerts[k].z=z+zs/2.0;
				pVerts[k].y=y+ys*ty/cgrd_y-ys/2.0;
				break;
				}
			case 2:
				{
				pVerts[k].x=x+xs*tx/cgrd_x-xs/2.0;
				pVerts[k].z=z+zs*ty/cgrd_y-zs/2.0;
				pVerts[k].y=y+ys/2.0;
				break;
				}
			case 3:
				{
				pVerts[k].x=x-(xs*tx/cgrd_x-xs/2.0);
				pVerts[k].z=z+zs*ty/cgrd_y-zs/2.0;
				pVerts[k].y=y-ys/2.0;
				break;
				}
			case 4:
				{
				pVerts[k].x=x+xs/2.0;
				pVerts[k].z=z+zs*tx/cgrd_x-zs/2.0;
				pVerts[k].y=y+ys*ty/cgrd_y-ys/2.0;
				break;
				}
			case 5:
				{
				pVerts[k].x=x-xs/2.0;
				pVerts[k].z=z-(zs*tx/cgrd_x-zs/2.0);
				pVerts[k].y=y+ys*ty/cgrd_y-ys/2.0;
				break;
				}
			}
			
			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(cgrd_x);
			pVerts[k].v=(double)ty/(double)(cgrd_y);

		k++;
		}
	}
cube_i2[p]=k;
}
//inds
	k=0;

for (int p=0;p<6;p++)
{
int ofs=(cgrd_x+1)*(cgrd_y+1)*p;
for (ty=0;ty<cgrd_y;ty++)
	{
	for (tx=0;tx<cgrd_x;tx++)
		{
		pInds[k+0]=ty*(cgrd_x+1)+tx+ofs;
		pInds[k+1]=ty*(cgrd_x+1)+tx+1+ofs;
		pInds[k+2]=(ty+1)*(cgrd_x+1)+tx+1+ofs;		
		k+=3;
		
		pInds[k+0]=ty*(cgrd_x+1)+tx+ofs;
		pInds[k+1]=(ty+1)*(cgrd_x+1)+tx+1+ofs;
		pInds[k+2]=(ty+1)*(cgrd_x+1)+tx+ofs;		
		k+=3;
		}
	}
}
///

	NumVerts=(greedx+1)*(greedy+1)*6;
	NumTriangles=greedx*greedy*6*2;
	NumInds=NumTriangles*3;
	
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	greedy=(greedy+1)*6;
	
	ApplyMods();

	FlatNormals2();
	
	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	SetAlfa(0);

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);

}
void SubdividedFlat()
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

double a,b,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));

	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	if (greedx*greedy<=0) return;

	k=0;

for (ty=greedy;ty>=0;ty--)
	{
	for (tx=0;tx<=greedx;tx++)
		{
			pVerts[k].x=x+xs*tx/greedx-xs/2.0;
			pVerts[k].z=z;
			pVerts[k].y=y+ys*ty/greedy-ys/2.0;
			
			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(greedx);
			pVerts[k].v=(double)ty/(double)(greedy);
		k++;
		}
	}

	CalcIndicies();

	NumVerts=(greedx+1)*(greedy+1);
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;
	
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	
	ApplyMods();

	FlatNormals();
	//Svertka2Normals();

	FillVB(0);
					
//draw



	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	SetAlfa(0);

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);

}



void LightsOff()
{
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void LightsOn()
{
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


void Tube()
{
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double a,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));
	
	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;
	if (greedx*greedy==0) return ;

	k=0;
for (ty=0;ty<=greedy;ty++)
	{
	for (tx=0;tx<=greedx;tx++)
		{
		a=tx*360.0/(double)greedx;;
			pVerts[k].x=x+xs*sin(a*PI/180.0)/2.0;
			pVerts[k].z=z+zs*cos(a*PI/180.0)/2.0;
			pVerts[k].y=y+ys*ty/(float)greedy-ys/2.0;

			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(greedx);
			pVerts[k].v=(double)ty/(double)(greedy);

		k++;
		}
	}

{
int k=0;int ty,tx;
for (ty=0;ty<greedy;ty++)
	{
	for (tx=0;tx<greedx;tx++)
		{
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=ty*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx+1;		
		k+=3;
		
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=(ty+1)*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx;		
		k+=3;
		}

	}
}


	NumVerts=(greedx+1)*(greedy+1);//чтобы не париться с заворотом посчитали 360 включительно
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;
	
	//pDevice->SetTexture(0,Texture[texture]);
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	
	ApplyMods();

	SvertkaXNormals();

	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		;	

	SetAlfa(0);
if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);	
}

int vPoint,iPoint;double TreeScale;

void SubTree(double x,double y,double z,double scale,int TreeRec,double startAngle)
{
int rnd=Get(CPos,13);
float rotate=Get(CPos,14)/1000.0;
float breaks=Get(CPos,19)/1000.0;
int tr=Get(CPos,12);
if (TreeRec<1) return;
TreeScale=TreeRec/(float)tr;
float TreeScale1=(TreeRec-1)/(float)tr;
TreeRec--;
double a,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;

//	objectX=x=Get(CPos,1)/1000.0;
//	objectY=y=Get(CPos,2)/1000.0;
//	objectZ=z=Get(CPos,3)/1000.0;
float gravity=Get(CPos,16)/1000.0;
float angle_rand=Get(CPos,17)/1000.0;
float angle_p=1+Get(CPos,18)*(1-TreeRec/(float)Get(CPos,12));
float angle_s[33];
int b=vPoint;
int divstart=1;
int div;
if (Get(CPos,12)-TreeRec>divstart)
{
	div=1+(rand()/10000*rnd)+(1-TreeScale)*5;
	if(div<1) div=1;
}
else
{
	div=1;
}
//div=3;
float gangle;
for (int i=0;i<div;i++)
{
float angle;

if (i==0)
{
//angle=startAngle;
angle=startAngle+(angle_rand*(rand()/10000.0*((i-div/2.0))*3.14/180.0))*angle_p/100.0;
}
else
{
angle=startAngle+angle_rand*(rand()/10000.0*((i-div/2.0))*3.14/180.0);
}
angle_s[i]=angle;
float yr=1+(Get(CPos,15)/100000.0)*rand();
if (i==0) 
{
	yr=1;
}
int k=vPoint;
	for (ty=0;ty<=greedy;ty++)
	{
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0*(TreeScale+breaks)*yr;
	zs=Get(CPos,6)/1000.0;

	if (TreeRec==0) ys*=1-Get (CPos,20)*.001;

	xs=lerp(xs*TreeScale,xs*TreeScale1,1-ty/(float)(greedy+1));
	zs=lerp(zs*TreeScale,zs*TreeScale1,1-ty/(float)(greedy+1));

	if (TreeRec==0&&ty==greedy-1) xs*=1+Get (CPos,20)*.01;
	
	for (tx=0;tx<=greedx;tx++)
		{
		a=tx*360.0/(double)greedx;;
			pVerts[vPoint].x=xs*sin(a*PI/180.0)/2.0;
			pVerts[vPoint].z=zs*cos(a*PI/180.0)/2.0;
			pVerts[vPoint].y=ys*ty/(float)greedy;

			pVerts[vPoint].color=0xffffffff;

			pVerts[vPoint].u=(double)tx/(double)(greedx);
			pVerts[vPoint].v=(double)ty/(double)(greedy);
			
			float x1=pVerts[vPoint].x;
			float y1=pVerts[vPoint].y;
			float z1;
				float x2=y1*sin(angle)+x1*cos(angle);
				float y2=y1*cos(angle)-x1*sin(angle);
				float z2=pVerts[vPoint].z;


			float f=sqrt(ty/(float)(greedy+1));
			gangle=f*gravity*sign(angle);

			//if (Get(CPos,12)-TreeRec<=divstart)
			if (i==0)
			{
			gangle=rotate*sin(ty/(float)(greedy+1)*3.14*2+TreeScale)+gangle*angle_p/100.0;
			}


			//if (ty>0) 
			{
		//float xza=sin(i*rotate+f*angle_p/100.0*sign(sin(angle))+angle_p*i/10.0+tr);
			//float xza=(TreeScale*4+TreeRec)*rotate;
			float xza=f+angle*4+8*rotate*sin(ty/(float)(greedy+1)*3.14*2+TreeScale)+gangle*angle_p/100.0;;//+y*rotate*TreeScale;
			//if (Get(CPos,12)-TreeRec<=divstart)
		if (i==0)
			{
			xza=0;
			}

			float x3=x2;
			float y3=y2;
				x2=y3*sin(gangle)+x3*cos(gangle);
				y2=y3*cos(gangle)-x3*sin(gangle);
				
			//	pVerts[vPoint].y-=(1-log(1-f))*gravity/100.0;
	

				pVerts[vPoint].x=z2*sin(xza)+x2*cos(xza);
				pVerts[vPoint].z=z2*cos(xza)-x2*sin(xza);
				pVerts[vPoint].y=y2;

			//	pVerts[vPoint].x=x2;
			//	pVerts[vPoint].z=z2;
			//	pVerts[vPoint].y=y2;

			}
				

				pVerts[vPoint].x+=x;
				pVerts[vPoint].z+=z;
				pVerts[vPoint].y+=y;
			
				//pVerts[vPoint].z=z;
		vPoint++;
		}
	}
	
	
	{
	int ty,tx;
	for (ty=0;ty<greedy;ty++)
		{
		for (tx=0;tx<greedx;tx++)
			{
			pInds[iPoint+0]=k+ty*(greedx+1)+tx;
			pInds[iPoint+1]=k+ty*(greedx+1)+tx+1;
			pInds[iPoint+2]=k+(ty+1)*(greedx+1)+tx+1;		
			iPoint+=3;
			
			pInds[iPoint+0]=k+ty*(greedx+1)+tx;
			pInds[iPoint+1]=k+(ty+1)*(greedx+1)+tx+1;
			pInds[iPoint+2]=k+(ty+1)*(greedx+1)+tx;		
			iPoint+=3;
			}
		}
	}


		

//for (int j=0;j<3;j++)
//{
//		float angle=angle_s[j];
		float x2=(0+ys)*sin(angle)+x*cos(angle)+x;
		float y2=(0+ys)*cos(angle)-x*sin(angle)+y;
		float z2=z;

//	if (TreeRec>0) {
//		SubTree(x2,y2,z2,TreeScale,TreeRec);
		float mx,my,mz;
		mx=(pVerts[vPoint-1].x+pVerts[vPoint-1-greedx/2].x)/2.0;
		my=(pVerts[vPoint-1].y+pVerts[vPoint-1-greedx/2].y)/2.0;
		mz=(pVerts[vPoint-1].z+pVerts[vPoint-1-greedx/2].z)/2.0;
		SubTree(mx,my,mz,TreeScale,TreeRec,angle+gangle);
	//	}

//}


}


}

void Tree()
{
	int TreeRec=Get(CPos,12);
	srand(0);double scale=1+Get(CPos,13)/100.0;TreeScale=1;
	vPoint=0;iPoint=0;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double a,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));
	
	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;
	if (greedx*greedy==0) return ;

	SubTree(x,y,z,scale,TreeRec,0);


	//NumVerts=(greedx+1)*(greedy+1);//чтобы не париться с заворотом посчитали 360 включительно
	NumVerts=vPoint;
	//NumTriangles=greedx*greedy*2;
	NumTriangles=iPoint/3;
	NumInds=iPoint;
	
	//pDevice->SetTexture(0,Texture[texture]);
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	//greedx=1;
	greedy=NumVerts/(greedx+1);
	
	ApplyMods();

	SvertkaXNormals();

	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		;	

	SetAlfa(0);
if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);	
}


void Torus()
{
	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double a,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=Get(CPos,1)/1000.0;
	objectY=y=Get(CPos,2)/1000.0;
	objectZ=z=Get(CPos,3)/1000.0;
	xs=width*Get(CPos,4)/1000.0;
	ys=height*Get(CPos,5)/1000.0;
	zs=Get(CPos,6)/1000.0;
	texture=Get(CPos,7);
	material=Get(CPos,8);
	greedx=Get(CPos,9);
	greedy=Get(CPos,10);
	SetAlfa(Get(CPos,11));
	float angle=Get(CPos,12);
	
	if (greedx>=maxgridsize)greedx=maxgridsize-1;
	if (greedy>=maxgridsize)greedy=maxgridsize-1;
	if (greedx*greedy==0) return ;
	
	if (greedx<2) return ;
	if (greedy<2) return ;

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	k=0;
	float vx,vy,vz,b2,tmz,tmy,tmx;
	float rx,rz;
	rx=zs;
for (ty=0;ty<=greedy;ty++)
	{
	for (tx=0;tx<=greedx;tx++)
		{
		a=tx*360.0/(double)greedx+angle;;
			vx=rx+xs*sin(a*PI/180.0)/2.0;
			vz=ys*cos(a*PI/180.0)/2.0;
			vy=ty/(float)greedy-ys/2.0;

			b2=2*PI*ty/greedy;
			tmx=vx*cos(b2);
			tmy=vx*sin(b2);
			vx=tmx;vy=tmy;

	pVerts[k].x=vx+x;
	pVerts[k].y=vy+y;
	pVerts[k].z=vz+z;

			pVerts[k].color=0xffffffff;

			pVerts[k].u=(double)tx/(double)(greedx);
			pVerts[k].v=(double)ty/(double)(greedy);

		k++;
		}
	}

{
int k=0;int ty,tx;
for (ty=0;ty<greedy;ty++)
	{
	for (tx=0;tx<greedx;tx++)
		{
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=ty*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx+1;		
		k+=3;
		
		pInds[k+0]=ty*(greedx+1)+tx;
		pInds[k+1]=(ty+1)*(greedx+1)+tx+1;
		pInds[k+2]=(ty+1)*(greedx+1)+tx;		
		k+=3;
		}

	}
}


	NumVerts=(greedx+1)*(greedy+1);//чтобы не париться с заворотом посчитали 360 включительно
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;
	
	//pDevice->SetTexture(0,Texture[texture]);
	SetTexture(0,texture,0);
	
	SetMaterial(&Material[material]);
	
	
	ApplyMods();

	SvertkaTNormals();

	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		;	

	SetAlfa(0);
if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);	
}

void Fog()
{
float Start,End;
Start=Get(CPos,1)/100.0;
End=Get(CPos,2)/100.0;

pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

int fr,fg,fb;
fr=Get(CPos,3);
fg=Get(CPos,4);
fb=Get(CPos,5);

pDevice->SetRenderState(D3DRS_FOGCOLOR, (fr<<16)|(fg<<8)|(fb));
//pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR  );
pDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Start));
pDevice->SetRenderState(D3DRS_FOGEND,   *(DWORD *)(&End));
}

void DisableFog()
{
pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}



void ShaderQuad()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	
ZBufDisable();
int vbi;double w,h;	
w=2;h=2;


//double sta=1/256.0;
double stb=.5/768.0;
double sta=.5/1024.0;

vbi=CPos;

	pVerts[0].x=-w/2.0;pVerts[0].y=h/2.0;pVerts[0].z=0;
	pVerts[1].x=w/2.0;pVerts[1].y=h/2.0;pVerts[1].z=0;
	pVerts[2].x=w/2.0;pVerts[2].y=-h/2.0;pVerts[2].z=0;
	pVerts[3].x=-w/2.0;pVerts[3].y=-h/2.0;pVerts[3].z=0;

	int i;
	for (i=0;i<4;i++)
	{
//	pVerts[i].x+=.5/1024.0;
//	pVerts[i].y-=.5/768.0;
//	pVerts[i].x+=1/256.0;
//	pVerts[i].y-=1/256.0;
	}

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	for (i=0;i<4;i++)
	{
		pVerts[i].u+=.5/(double)vp.Width;
		pVerts[i].v+=.5/(double)vp.Height;
	}

	int argb=D3DCOLOR_RGBA(255,255,255,0);

	for (int i=0;i<3;i++) pVerts[i].color=argb;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

	CpyToPrev2(0);//?? double copy?
	
	SetMaterial(&WhiteMaterial);
	
	SetAlfa(0);
	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	NumVerts=4;	NumInds=6;	NumTriangles=2;

	FillVB(0);

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}

void ShaderQuad2()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	
ZBufDisable();
int vbi;double w,h;	
w=2;h=2;


double sta=1/256.0;

vbi=CPos;

	pVerts[0].x=-w/2.0;pVerts[0].y=h/2.0;pVerts[0].z=0;
	pVerts[1].x=w/2.0;pVerts[1].y=h/2.0;pVerts[1].z=0;
	pVerts[2].x=w/2.0;pVerts[2].y=-h/2.0;pVerts[2].z=0;
	pVerts[3].x=-w/2.0;pVerts[3].y=-h/2.0;pVerts[3].z=0;

	int i;
	for (i=0;i<4;i++)
	{
//	pVerts[i].x+=.5/1024.0;
//	pVerts[i].y-=.5/768.0;
//	pVerts[i].x+=.5/512.0;
//	pVerts[i].y-=.5/512.0;
	}

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	for (i=0;i<4;i++)
	{
		pVerts[i].u+=.75/(double)vp.Width;
		pVerts[i].v+=.75/(double)vp.Height;
	}


	int argb=D3DCOLOR_RGBA(255,255,255,0);

	for (int i=0;i<3;i++) pVerts[i].color=argb;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

	CpyToPrev2(0);//?? double copy?
	
	SetMaterial(&WhiteMaterial);
	
	//SetAlfa(0);
	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	NumVerts=4;	NumInds=6;	NumTriangles=2;

	FillVB(0);

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	SetView(0);
}



void BlackQuad()
{
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_NULL);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void WhiteQuad()
{
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_FULL);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

//obsolete
void TextureQuad()
{
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
SetAlfa(6);
pDevice->SetTexture(0,Texture[Get(CPos,1)]);
//	pDevice->SetTexture(0,Dragon);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_tex);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
}


void RadialDisplace()
{
	
float amp,amp2,amp3;
amp=Get(CPos,3)/512.0;
amp2=Get(CPos,4)/512.0;
amp3=Get(CPos,5)/512.0;
//pDevice->SetTexture(0,Texture[Get(CPos,1)]);
//pDevice->SetTexture(1,Texture[Get(CPos,2)]);
SetTexture(0,Get(CPos,1),0);
SetTexture(1,Get(CPos,2),1);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_RadialDisplace);
	pDevice->SetPixelShaderConstantF(0,&amp,1);
	pDevice->SetPixelShaderConstantF(1,&amp2,1);
	pDevice->SetPixelShaderConstantF(2,&amp3,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

}




void SDisplace()
{
	//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
float amp1,amp2;
amp1=Get(CPos,3)/512.0;
amp2=Get(CPos,4)/512.0;
float ox=Get(CPos,5)/1000.0;
float oy=Get(CPos,6)/1000.0;

SetTexture(0,Get(CPos,1),0);
SetTexture(1,Get(CPos,2),1);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_SDisplace);
	pDevice->SetPixelShaderConstantF(0,&amp1,1);
	pDevice->SetPixelShaderConstantF(1,&amp2,1);
	pDevice->SetPixelShaderConstantF(2,&ox,1);
	pDevice->SetPixelShaderConstantF(3,&oy,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
}


void RDisplace()
{
	//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
float amp1,amp2,amp3;
amp1=Get(CPos,3)/512.0;
amp2=Get(CPos,4)/512.0;
amp3=Get(CPos,5)/512.0;
//pDevice->SetTexture(0,Texture[Get(CPos,1)]);
//pDevice->SetTexture(1,Texture[Get(CPos,2)]);
SetTexture(0,Get(CPos,1),0);
SetTexture(1,Get(CPos,2),1);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_RDisplace);
	pDevice->SetPixelShaderConstantF(0,&amp1,1);
	pDevice->SetPixelShaderConstantF(1,&amp2,1);
	pDevice->SetPixelShaderConstantF(2,&amp3,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
}

void RGBDisplace()
{
float r1,g1,b1,r2,g2,b2;
r1=Get(CPos,3)/512.0;
g1=Get(CPos,4)/512.0;
b1=Get(CPos,5)/512.0;
r2=Get(CPos,6)/512.0;
g2=Get(CPos,7)/512.0;
b2=Get(CPos,8)/512.0;

//pDevice->SetTexture(0,Texture[Get(CPos,1)]);
//pDevice->SetTexture(1,Texture[Get(CPos,2)]);
SetTexture(0,Get(CPos,1),0);
SetTexture(1,Get(CPos,2),1);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_RGBDisplace);
	pDevice->SetPixelShaderConstantF(0,&r1,1);
	pDevice->SetPixelShaderConstantF(1,&g1,1);
	pDevice->SetPixelShaderConstantF(2,&b1,1);
	pDevice->SetPixelShaderConstantF(3,&r2,1);
	pDevice->SetPixelShaderConstantF(4,&g2,1);
	pDevice->SetPixelShaderConstantF(5,&b2,1);

ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void ShBlur()
{

int q;float px;int type;
if (width==height) px=screen_width; else px=512.0;

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
type=Get(CPos,2);
q=Get(CPos,1);

if (q==0) {CpyToPrev2(0);return;}

CPC_IT=2;

pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);

if (type==0||type==2)
{
pDevice->SetPixelShader(Shader_Blur1);
pDevice->SetPixelShaderConstantI(0,&q,1);
pDevice->SetPixelShaderConstantF(1,&px,1);
ShaderQuad();

pDevice->SetPixelShader(Shader_Blur2);
pDevice->SetPixelShaderConstantI(0,&q,1);
pDevice->SetPixelShaderConstantF(1,&px,1);
ShaderQuad();
}

if (type==0||type==1)
{
pDevice->SetPixelShader(Shader_Blur3);
pDevice->SetPixelShaderConstantI(0,&q,1);
pDevice->SetPixelShaderConstantF(1,&px,1);
ShaderQuad();

pDevice->SetPixelShader(Shader_Blur4);
pDevice->SetPixelShaderConstantI(0,&q,1);
pDevice->SetPixelShaderConstantF(1,&px,1);
ShaderQuad();
}

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

CPC_IT=0;
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
}

void Desaturate()
{
float q=Get(CPos,1)/256.0;
pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Desaturate);
pDevice->SetPixelShaderConstantF(0,&q,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void AdjustColor()
{
float Hue=Get(CPos,1)*PI/180.0;
float Saturation=Get(CPos,2)/256.0+1;
float Contrast=Get(CPos,3)/256.0;
float Brightness=Get(CPos,4)/256.0;
float HueCycles=1;
pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_AdjustColor);
pDevice->SetPixelShaderConstantF(0,&Hue,1);
pDevice->SetPixelShaderConstantF(1,&Saturation,1);
pDevice->SetPixelShaderConstantF(2,&Contrast,1);
pDevice->SetPixelShaderConstantF(3,&Brightness,1);
pDevice->SetPixelShaderConstantF(4,&HueCycles,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void CopyToAlpha()
{
int a;
pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
pDevice->SetPixelShader(Shader_SumToAlpha);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
if (a==0) WriteAlpha(0);
}

void AlphaToRGB()
{
int a;
pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
pDevice->SetPixelShader(Shader_AtoRGB);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
if (a==0) WriteAlpha(0);
}


void ModCopyToAlphaFromTexture()
{
int a;
pDevice->SetTexture(0,PrevStageTexture);
//pDevice->SetTexture(1,Texture[Get(CPos,1)]);
SetTexture(1,Get(CPos,1),1);

pDevice->SetVertexShader(Shader_VSBase);
a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);

if (Get(CPos,2)==0 )
	{
	pDevice->SetPixelShader(Shader_TModAToAlpha);
	}
if (Get(CPos,2)==1 )
	{
	pDevice->SetPixelShader(Shader_InvTModAToAlpha);
	}

ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

if (a==0) WriteAlpha(0);
}


void CopyAlphaFromTexture()
{int a;
a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);

pDevice->SetTexture(0,PrevStageTexture);
//pDevice->SetTexture(1,Texture[Get(CPos,1)]);
SetTexture(1,Get(CPos,1),1);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_CopyAFromT);

ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

if (a==0) WriteAlpha(0);
}

void newScaleColor()
{
pDevice->SetTexture(0,PrevStageTexture);
float r,g,b,a;
r=Get(CPos,1)/256.0;
g=Get(CPos,2)/256.0;
b=Get(CPos,3)/256.0;
a=Get(CPos,4)/256.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_ScaleColor);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&g,1);
pDevice->SetPixelShaderConstantF(2,&b,1);
pDevice->SetPixelShaderConstantF(3,&a,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void Contrast()
{
pDevice->SetTexture(0,PrevStageTexture);
float level,br;
level=Get(CPos,1)/256.0;
br=Get(CPos,2)/256.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Contrast);
pDevice->SetPixelShaderConstantF(0,&level,1);
pDevice->SetPixelShaderConstantF(1,&br,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void FastBlur()
{

pDevice->SetTexture(0,PrevStageTexture);
mipgenflag=1;
float r,w,bp,sc,noise;
if (PrevStageTexture==PrevStageTextureLQ) r=512; 
if (PrevStageTexture==PrevStageTextureHQ) r=1024;
if (PrevStageTexture==PrevStageTextureHQ2) r=2048;
w=Get(CPos,1);
bp=Get(CPos,3)/255.0;
sc=1+Get(CPos,4)/100.0;
noise=Get(CPos,5)/100.0;
float pt=ptime;
if (w<=0) {CpyToPrev2(0);return;}
w=(w-1)/10.0;

SetAlfa(Get(CPos,2));

pDevice->SetVertexShader(Shader_VSBase);

pDevice->SetPixelShader(Shader_FastBlur);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&w,1);
pDevice->SetPixelShaderConstantF(2,&bp,1);
pDevice->SetPixelShaderConstantF(3,&sc,1);
pDevice->SetPixelShaderConstantF(4,&noise,1);
pDevice->SetPixelShaderConstantF(5,&pt,1);

pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,2);
CPC_IT=2;
ShaderQuad2();
CPC_IT=0;
pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,0);

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
SetAlfa(0);
mipgenflag=0;
}


void newPerlin()
{
float x,y,z;
x=Get(CPos,1)/1000.0;
y=Get(CPos,2)/1000.0;
z=Get(CPos,3)/10.0;

float o1=Get(CPos,4)/100.0;pDevice->SetPixelShaderConstantF(3,&o1,1);
float o2=Get(CPos,5)/100.0;pDevice->SetPixelShaderConstantF(4,&o2,1);
float o3=Get(CPos,6)/100.0;pDevice->SetPixelShaderConstantF(5,&o3,1);
float o4=Get(CPos,7)/100.0;pDevice->SetPixelShaderConstantF(6,&o4,1);
float o5=Get(CPos,8)/100.0;pDevice->SetPixelShaderConstantF(7,&o5,1);
float o6=Get(CPos,9)/100.0;pDevice->SetPixelShaderConstantF(8,&o6,1);
float o7=Get(CPos,10)/100.0;pDevice->SetPixelShaderConstantF(9,&o7,1);
float o8=Get(CPos,11)/100.0;pDevice->SetPixelShaderConstantF(10,&o8,1);

pDevice->SetPixelShaderConstantF(0,&x,1);
pDevice->SetPixelShaderConstantF(1,&y,1);
pDevice->SetPixelShaderConstantF(2,&z,1);
//pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_NewPerlin);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void Julia()
{
pDevice->SetTexture(0,PrevStageTexture);
float a,b,c,z,st,f,f2;
a=Get(CPos,1)/256.0;
b=Get(CPos,2)/256.0;
c=Get(CPos,3);
z=Get(CPos,4)/256.0;
st=Get(CPos,5)/256.0+2;
f=Get(CPos,6)/256.0;
f2=Get(CPos,7)/256.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Julia);
pDevice->SetPixelShaderConstantF(0,&a,1);
pDevice->SetPixelShaderConstantF(1,&b,1);
pDevice->SetPixelShaderConstantF(2,&c,1);
pDevice->SetPixelShaderConstantF(3,&z,1);
pDevice->SetPixelShaderConstantF(4,&st,1);
pDevice->SetPixelShaderConstantF(5,&f,1);
pDevice->SetPixelShaderConstantF(6,&f2,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void FastMapBlur()
{
	
pDevice->SetTexture(0,PrevStageTexture);
mipgenflag=1;
float r,w,bp,sc,noise;
if (PrevStageTexture==PrevStageTextureLQ) r=512; 
if (PrevStageTexture==PrevStageTextureHQ) r=1024;
if (PrevStageTexture==PrevStageTextureHQ2) r=2048;w=Get(CPos,1);
bp=Get(CPos,3)/255.0;
sc=1+Get(CPos,4)/100.0;
noise=Get(CPos,5)/100.0;
float pt=ptime;
if (w<=0) {CpyToPrev2(0);return;}
w=(w-1)/10.0;

SetAlfa(Get(CPos,2));

SetTexture(1,Get(CPos,6),2);
float amp=Get(CPos,7)/255.0;
float phase=Get(CPos,8)/255.0;
float q=Get(CPos,9)/255.0+1;

pDevice->SetVertexShader(Shader_VSBase);

pDevice->SetPixelShader(Shader_FastMapBlur);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&w,1);
pDevice->SetPixelShaderConstantF(2,&bp,1);
pDevice->SetPixelShaderConstantF(3,&sc,1);
pDevice->SetPixelShaderConstantF(4,&noise,1);
pDevice->SetPixelShaderConstantF(5,&pt,1);

pDevice->SetPixelShaderConstantF(6,&amp,1);
pDevice->SetPixelShaderConstantF(7,&phase,1);
pDevice->SetPixelShaderConstantF(8,&q,1);

pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,2);
CPC_IT=2;
ShaderQuad2();
CPC_IT=0;
pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,0);

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
SetAlfa(0);
mipgenflag=0;
}



void SinColor()
{
pDevice->SetTexture(0,PrevStageTexture);
float r,g,b,a;
r=Get(CPos,1)/100.0;
g=Get(CPos,2)/100.0;
b=Get(CPos,3)/100.0;
a=Get(CPos,4)/100.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_SinColor);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&g,1);
pDevice->SetPixelShaderConstantF(2,&b,1);
pDevice->SetPixelShaderConstantF(3,&a,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}


void Palette()
{
pDevice->SetTexture(0,PrevStageTexture);
//pDevice->SetTexture(1,Texture[Get(CPos,1)]);
SetTexture(1,Get(CPos,1),1);
float t;
t=Get(CPos,1);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Palette);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}


void Sharp()
{
CpyToPrev2(1);
ShBlur();
float a=Get(CPos,3)/10.0+1;
CpyToPrev2(0);
pDevice->SetTexture(0,PrevStageTexture2);
pDevice->SetTexture(1,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Sharp);
pDevice->SetPixelShaderConstantF(0,&a,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}


void FixGlow()
{
CpyToPrev2(1);
ShBlur();
CpyToPrev2(0);
float a=Get(CPos,3)/10.0;
pDevice->SetTexture(0,PrevStageTexture2);
pDevice->SetTexture(1,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Glow);
pDevice->SetPixelShaderConstantF(0,&a,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void Emboss2()
{
CpyToPrev2(1);
double a;
a=Get(CPos,3);a=a*3.14/180.0;
ShBlur();
float x=(Get(CPos,1)+Get(CPos,4)/512.0)*sin(a)/512.0;
float y=(Get(CPos,1)+Get(CPos,4)/512.0)*cos(a)/512.0;
pDevice->SetTexture(0,PrevStageTexture2);
pDevice->SetTexture(1,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Emboss2);
pDevice->SetPixelShaderConstantF(0,&x,1);
pDevice->SetPixelShaderConstantF(1,&y,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void Invert()
{
int a;
a=WriteAlpha_flag;
if (a==1) WriteAlpha(0);

//CpyToPrev2(0);
pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Invert);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

if (a==1) WriteAlpha(1);
}

void InvertA()
{
//CpyToPrev2(0);
	int a;
	a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);

pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_InvertA);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

if (a==0) WriteAlpha(0);
}

void NormalMap()
{
//CpyToPrev2(0);

pDevice->SetTexture(0,PrevStageTexture);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_NormalMap);

float size=512;
pDevice->SetPixelShaderConstantF(0,&size,1);


ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

}

void ClearRGB()
{
int a;
CpyToPrev2(0);
pDevice->SetTexture(0,PrevStageTexture);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);

float r=Get(CPos,1)/255.0;
float g=Get(CPos,2)/255.0;
float b=Get(CPos,3)/255.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_ClearRGB);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&g,1);
pDevice->SetPixelShaderConstantF(2,&b,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
if (a==0) WriteAlpha(0);

}

void ClearAlpha()
{
int a;
//CpyToPrev2(0);
pDevice->SetTexture(0,PrevStageTexture);
float b=Get(CPos,1)/255.0;

a=WriteAlpha_flag;
if (a==0) WriteAlpha(1);
//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_ClearAlpha);
pDevice->SetPixelShaderConstantF(0,&b,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);
if (a==0) WriteAlpha(0);

}


void SetClamp()
{
	int stage=Get(CPos,1);

	pDevice->SetSamplerState( stage, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(Get(CPos,4),Get(CPos,5),Get(CPos,6),Get(CPos,7)) );


	switch(Get(CPos,2))
	{
	case 0:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP );
		break;
	case 1:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP );
		break;
	case 2:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSU,D3DTADDRESS_MIRROR );
		break;
	case 3:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSU,D3DTADDRESS_BORDER );
		break;
	
	}

	switch(Get(CPos,3))
	{
	case 0:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP );
		break;
	case 1:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP );
		break;
	case 2:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSV,D3DTADDRESS_MIRROR );
		break;
	case 3:
		pDevice->SetSamplerState(stage,D3DSAMP_ADDRESSV,D3DTADDRESS_BORDER );
		break;
	
	}	

}

void MainLoop()
{
LoopPoint=CPos;
PrecalcStatus=1;
MaxRecurrenceLevel=64;
}

LPD3DXMESH          g_pMesh[100];

void LoadMesh()
{
//	if (Get(CPos,1)<0||Get(CPos,1)>255) return;

		char t[100];
		strcpy(t,(char*)(Pack+CPos+256-33));
		int i;
		i=Get(CPos,1);
		if (i<0||i>=100) return;

LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( t, D3DXMESH_SYSTEMMEM,
                                   pDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, NULL,
                                   &g_pMesh[i] ) ) )
    {
		g_pMesh[i]=NULL;
		return ;
    }

	// Done with the material buffer
    pD3DXMtrlBuffer->Release();

	
	
}


void ShowMesh()
{
if (Get(CPos,1)>100||Get(CPos,1)<0) return;
if (g_pMesh[Get(CPos,1)]==NULL) return;

    D3DXMATRIXA16 matWorld, matRotate, matScale,tr;
	
	D3DXMatrixScaling(&matScale,Get(CPos,5)/10000.0,Get(CPos,5)/10000.0,Get(CPos,5)/10000.0);  
    D3DXMatrixRotationYawPitchRoll( &matRotate, Get(CPos,6) / 10.0f*PI/180.0, Get(CPos,7) / 10.0f*PI/180.0, Get(CPos,8) / 10.0f*PI/180.0 );
	D3DXMatrixTranslation(&tr,Get(CPos,2)/1000.0,Get(CPos,3)/1000.0,Get(CPos,4)/1000.0);

	D3DXMatrixMultiply(&matWorld, &matRotate, &matScale);
	D3DXMatrixMultiply(&matWorld, &matWorld, &tr);

    pDevice->SetTransform( D3DTS_WORLD, &matWorld );

	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);

	SetTexture(0,Get(CPos,9),1);
	SetMaterial(&Material[Get(CPos,10)]);
	
	SetAlfa(Get(CPos,11));
	ApplyMods();
	g_pMesh[Get(CPos,1)]->DrawSubset( 0);
	
	pDevice->SetTransform( D3DTS_WORLD, &World );	

	pDevice->SetFVF(D3DFVF_MYVERTEX);
}



void LoadTexture()
{
	if (Get(CPos,1)<0||Get(CPos,1)>255) return;

	LPDIRECT3DTEXTURE9 TDragon;

		char t[100];
		strcpy(t,(char*)(Pack+CPos+256-33));

		HRESULT hr;
		hr=D3DXCreateTextureFromFile(pDevice,t,&TDragon);//hack for testing
	
		if (hr!=S_OK) return;

		LPDIRECT3DSURFACE9 RT,RT2;
		hr=TDragon->GetSurfaceLevel(0,&RT);
		if (hr!=S_OK) return;

		hr=Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT2);
		if (hr!=S_OK) return;

		//hr=pDevice->StretchRect(RT,NULL,RT2,NULL,(D3DTEXTUREFILTERTYPE)Get(CPos,2));
		hr=D3DXLoadSurfaceFromSurface(RT2,NULL,NULL,RT,NULL,NULL,D3DX_DEFAULT ,0);
		if (hr!=S_OK) return;

		RT->Release();
		RT2->Release();

	TDragon->Release();

}


void StoreCamera()
{
//cam_bank[0]=View;

	D3DXMATRIX r,v,w;
	v=View;w=World;
	D3DXMatrixMultiply(&r,&v,&w);
	cam_bank[0]=r;

//D3DXMATRIX w,r;
//D3DXMatrixIdentity(&w);
//D3DXMatrixRotationX(&r,45*3.14/180.0);
//D3DXMatrixMultiply(&w,&w,&r);
//cam_bank[0]=w;
}

void ZtoScreen()
{
int mode=Get(CPos,1);
int tgt=Get(CPos,2);
if (mode==1) 
{
	if (tgt>=0&&tgt<maxtex)
	{
	LPDIRECT3DSURFACE9 RT;
		Texture[tgt]->GetSurfaceLevel(0,&RT);
		pDevice->SetRenderTarget(0,RT);
		RT->Release();
		current_rt=tgt;
		//pDevice->SetDepthStencilSurface(zbuf2);
		
		vp.X      = 0;
		vp.Y      = 0;
		vp.Width  = tex_res[tgt];
		vp.Height = tex_res[tgt];
		vp.MinZ   = 0.0f;
		vp.MaxZ   = 1.0f;
		pDevice->SetViewport(&vp);
	}
}

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Z);

SetTexture(0,-3,0);

float rx,ry;
if (current_rt>=0)
{
rx=tex_res[current_rt]/2048.0;
ry=rx;
if (mode==1) {rx=screen_width/2048.0;
ry=screen_height/2048.0;}
}
else
{
rx=screen_width/2048.0;
ry=screen_height/2048.0;
}
pDevice->SetPixelShaderConstantF(0,&rx,1);
pDevice->SetPixelShaderConstantF(1,&ry,1);

ShaderQuad();

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);

if (mode==1) 
	{
		LPDIRECT3DSURFACE9 RT;
		pDevice->GetRenderTarget(0,&RT);
		if (RT!=mainRT) RT->Release();
		pDevice->SetRenderTarget(0,mainRT);
		SetVp_(0);
		current_rt=-1;
	}
}

void XYZ()
{
	
SetTexture(0,Get(CPos,1),0);
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_XYZ);

D3DXMATRIX ma,mb,mc,tm;
//ma=World;
ma=View;mb=Projection;

D3DXMATRIX m1,m2;
D3DXQUATERNION q1;
D3DXVECTOR3 v0,v1;
D3DXMatrixDecompose(&v0,&q1,&v1,&ma);
D3DXVECTOR4 vv;
vv.x=-v1.x;vv.y=v1.y;vv.z=1-v1.z;vv.w=1;


D3DXHANDLE h0,h1;

h0 = pCt2->GetConstantByName(0, "tV");
pCt2->SetMatrix(pDevice, h0, &ma);

//D3DXMatrixInverse(&mb,NULL,&mb);


D3DXMatrixTranspose(&ma,&ma);;
//D3DXMatrixMultiply(&ma,&ma,&mb);

//D3DXMatrixInverse(&ma,NULL,&ma);

//D3DXMatrixMultiply(&ma,&ma,&mb);


//D3DXMatrixMultiply(&mc,&mb,&ma);

//D3DXMatrixTranspose(&mb,&mb);


mc=Projection;
//D3DXMatrixInverse(&mc,NULL,&mc);
//D3DXMatrixTranspose(&mc,&mc);
{
D3DXMATRIX r,t,t2,t3,t4,m,s,v;
s=StartMatrix;
v=View;
D3DXMatrixTranslation(&t,v._41,v._42,v._43);
D3DXMatrixTranslation(&t2,v._31,v._32,v._33);
D3DXMatrixTranslation(&t3,0,0,-1);
D3DXMatrixTranslation(&t4,0,0,1);


//D3DXMatrixRotationYawPitchRoll(&r,a,b,c);
//D3DXMatrixMultiply(&s,&s,&t2);
//D3DXMatrixMultiply(&s,&s,&r);
//D3DXMatrixMultiply(&s,&s,&t3);

//D3DXMatrixMultiply(&s,&s,&t);
//t=t+t2+t3;
D3DXVECTOR4 ft;
ft.x=v._41+v._31;
ft.y=v._42+v._32;
ft.z=v._43+v._33-1;
ft.w=0;

h0 = pCt2->GetConstantByName(0, "v1");
pCt2->SetVector(pDevice, h0, &ft);
}

h0 = pCt2->GetConstantByName(0, "tP");
pCt2->SetMatrix(pDevice, h0, &mc);

mb=Projection;
D3DXMatrixInverse(&mb,NULL,&mb);
h0 = pCt2->GetConstantByName(0, "tPi");
pCt2->SetMatrix(pDevice, h0, &mb);

//ma=World;
mb=View;
//D3DXMatrixMultiply(&ma,&ma,&mb);

//D3DXMatrixInverse(&ma,NULL,&ma);
//D3DXMatrixTranspose(&ma,&mb);
//D3DXMatrixMultiply(&ma,&ma,&m2);

//mb=Projection;
//D3DXMatrixInverse(&mb,NULL,&mb);
//D3DXMatrixMultiply(&ma,&ma,&mb);


h0 = pCt2->GetConstantByName(0, "tVI");
pCt2->SetMatrix(pDevice, h0, &ma);

float rx,ry;
if (current_rt>=0)
{
rx=tex_res[current_rt]/2048.0;
ry=rx;
}
else
{
rx=screen_width/2048.0;
ry=screen_height/2048.0;
}
h0 = pCt2->GetConstantByName(0, "rx");
pCt2->SetFloat(pDevice, h0, rx);

h0 = pCt2->GetConstantByName(0, "ry");
pCt2->SetFloat(pDevice, h0, ry);

ShaderQuad();

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

float camR[3];

void RotateCamera_(float a,float b,float c)
{
D3DXMATRIX r,t,t2,t3,t4,m,s,v;
s=StartMatrix;
v=View;
D3DXMatrixTranslation(&t,v._41,v._42,v._43);
D3DXMatrixTranslation(&t2,v._31,v._32,v._33);
D3DXMatrixTranslation(&t3,0,0,-2);
D3DXMatrixTranslation(&t4,0,0,1);


D3DXMatrixRotationYawPitchRoll(&r,a,b,c);
D3DXMatrixMultiply(&s,&s,&t2);
D3DXMatrixMultiply(&s,&s,&r);
D3DXMatrixMultiply(&s,&s,&t3);

D3DXMatrixMultiply(&s,&s,&t);
	View=s;
}


void RotateCamera()
{
float a,b,c;

a=((double)Get(CPos,1))*PI/1800.0;
b=((double)Get(CPos,2))*PI/1800.0;
c=((double)Get(CPos,3))*PI/1800.0;

camR[0]=a;
camR[1]=b;
camR[2]=c;

RotateCamera_(a,b,c);
}

void Shadow()
{
SetTexture(0,Get(CPos,1),0);
SetTexture(1,Get(CPos,2),0);
SetTexture(2,Get(CPos,3),0);

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Shadow);

D3DXMATRIX _light;
_light=cam_bank[0];

D3DXMATRIX _view;D3DXMATRIX _w;
_view=View;
_w=World;
D3DXMatrixMultiply(&_view,&_w,&_view);
//D3DXMatrixInverse(&_view,NULL,&_view);
//D3DXMatrixTranspose(&_view,&_view);

D3DXMATRIX _proj;
_proj=Projection;

D3DXMATRIX _vp;
D3DXMatrixMultiply(&_vp,&_view,&_proj);

D3DXMATRIX _lvp;
D3DXMatrixMultiply(&_lvp,&_light,&_proj);

float power=Get(CPos,5)/255.0;

D3DXHANDLE h0,h1;
h0 = pCt3->GetConstantByName(0, "light");
pCt3->SetMatrix(pDevice, h0, &_light);

h0 = pCt3->GetConstantByName(0, "view");
pCt3->SetMatrix(pDevice, h0, &_view);

h0 = pCt3->GetConstantByName(0, "proj");
pCt3->SetMatrix(pDevice, h0, &_proj);

h0 = pCt3->GetConstantByName(0, "power");
pCt3->SetFloat(pDevice, h0, power);

h0 = pCt3->GetConstantByName(0, "vp");
pCt3->SetMatrix(pDevice, h0, &_vp);

h0 = pCt3->GetConstantByName(0, "lvp");
pCt3->SetMatrix(pDevice, h0, &_lvp);

D3DXMATRIX _s2l,_lt;
D3DXMatrixTranspose(&_lt,&_view);
D3DXMatrixMultiply(&_s2l,&_lt,&_light);
//D3DXMatrixMultiply(&_s2l,&_s2l,&_proj);
h0 = pCt3->GetConstantByName(0, "s2l");
pCt3->SetMatrix(pDevice, h0, &_s2l);

			//pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
			//pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
			//pDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0|D3DWRAPCOORD_1);


ShaderQuad();

			//pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);
			//pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);
			//pDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0|D3DWRAPCOORD_1);


pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void RBlur()
{
pDevice->SetTexture(0,PrevStageTexture);
mipgenflag=1;
float r,w,bp,sc,i;
if (PrevStageTexture==PrevStageTextureLQ) r=512; 
if (PrevStageTexture==PrevStageTextureHQ) r=1024;
if (PrevStageTexture==PrevStageTextureHQ2) r=2048;
r=Get(CPos,1);
SetAlfa(Get(CPos,2));
bp=Get(CPos,3)/255.0;
sc=1+Get(CPos,4)/100.0;
i=Get(CPos,5);
float x=-Get(CPos,6)/1024.0;
float y=Get(CPos,7)/1024.0;
float dist=Get(CPos,8)/1024.0;

float pt=ptime;
//if (w<=0) {CpyToPrev2(0);return;}
//w=(w-1)/10.0;



pDevice->SetVertexShader(Shader_VSBase);

pDevice->SetPixelShader(Shader_FastRBlur);
pDevice->SetPixelShaderConstantF(0,&r,1);
pDevice->SetPixelShaderConstantF(1,&bp,1);
pDevice->SetPixelShaderConstantF(2,&sc,1);
pDevice->SetPixelShaderConstantF(3,&i,1);
pDevice->SetPixelShaderConstantF(4,&x,1);
pDevice->SetPixelShaderConstantF(5,&y,1);
pDevice->SetPixelShaderConstantF(6,&dist,1);

pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_BORDER );

pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_BORDER );
pDevice->SetSamplerState( 0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(0,0,0,0) );

pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,2);
CPC_IT=2;
ShaderQuad2();
CPC_IT=0;
pDevice->SetSamplerState(0,D3DSAMP_MIPFILTER,0);

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
SetAlfa(0);
pDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP );

pDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP );
mipgenflag=0;

}

void Halftone()
{
pDevice->SetTexture(0,PrevStageTexture);
float dpi=Get(CPos,1);
float tresh=Get(CPos,2)/256.0;
float angle=Get(CPos,3);
float color=Get(CPos,4)/256.0;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Halftone);
pDevice->SetPixelShaderConstantF(0,&dpi,1);
pDevice->SetPixelShaderConstantF(1,&tresh,1);
pDevice->SetPixelShaderConstantF(2,&angle,1);
pDevice->SetPixelShaderConstantF(3,&color,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void Posterize()
{
pDevice->SetTexture(0,PrevStageTexture);
float levels=Get(CPos,1);
if (levels<1) levels=1;
float gamma=Get(CPos,2)/256.0+.6;
if (gamma<.1) gamma=.1;
pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Posterize);
pDevice->SetPixelShaderConstantF(0,&levels,1);
pDevice->SetPixelShaderConstantF(1,&gamma,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void newCrossfade()
{
pDevice->SetTexture(0,PrevStageTexture);
float w,h;
w=Get(CPos,1)/256.0;
h=Get(CPos,2)/256.0;

if (w<=0) w=.0001;//div by zero protection
if (h<=0) h=.0001;

pDevice->SetVertexShader(Shader_VSBase);
pDevice->SetPixelShader(Shader_Crossfade);
pDevice->SetPixelShaderConstantF(0,&w,1);
pDevice->SetPixelShaderConstantF(1,&h,1);
ShaderQuad();
pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);
}

void ParticleArray()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

int vbi;
vbi=CPos;double d;
int objectX,objectY,objectZ;
//float v = float(GetTickCount()%0xffff)/0xffff * 3.141593f * 20;
int count=Get(CPos,1)*10;
objectX=Get(CPos,4);
objectY=Get(CPos,5);
objectZ=Get(CPos,6);

float Phaze=0;

float tx,ty,tz;

	double x,y,z,w,h;int r,g,b;
	
	if (count<1) return;
	if (count>maxgridsize*maxgridsize) count=maxgridsize*maxgridsize;

	w=Get(CPos,7);
	h=Get(CPos,8);
	d=Get(CPos,9);
	SetAlfa(Get(CPos,10));
	float spw=Get(CPos,11)/1000.0;
	float sph=Get(CPos,12)/1000.0;

	r=255;
	g=255;
	b=255;

	float pw;
	float ph;
	
srand(0);
for (int i=0;i<count;i++)
{
	tx=w*sin(((float)i)*0.001+Phaze*PI/180.0)*sin(((float)i)*0.0012+ptime/122.0+Phaze*PI/180.0)/1000.0;
	ty=h*sin(((float)i)*0.00111+Phaze*PI/180.0)*sin(((float)i)*0.0013+ptime/122.0+Phaze*PI/180.0)/1000.0;
	tz=d*sin(((float)i)*0.00123+Phaze*PI/180.0)*sin(((float)i)*0.00105+ptime/122.0+Phaze*PI/180.0)/1000.0;
//	tx=rand()%(int)w/1000.0;
//	ty=rand()%(int)h/1000.0;
//	tz=rand()%(int)d/1000.0;

//	tx=tx-w/2000;
//	ty=ty-h/2000;
//	tz=tz-d/2000;

	ph=sph*sin(((float)i)*1.123+Phaze*PI/180.0);
	pw=spw*sin(((float)i)*1.223+Phaze*PI/180.0);	

	x=tx+objectX;
	y=ty+objectY;
	z=tz+objectZ;
	
	pVerts[0+i*4].x=x-pw/2.0;pVerts[0+i*4].y=y-ph/2.0;pVerts[0+i*4].z=z;
	pVerts[1+i*4].x=x+pw/2.0;pVerts[1+i*4].y=y-ph/2.0;pVerts[1+i*4].z=z;
	pVerts[2+i*4].x=x+pw/2.0;pVerts[2+i*4].y=y+ph/2.0;pVerts[2+i*4].z=z;
	pVerts[3+i*4].x=x-pw/2.0;pVerts[3+i*4].y=y+ph/2.0;pVerts[3+i*4].z=z;

			pVerts[0+i*4].u=0;pVerts[0+i*4].v=0;
			pVerts[1+i*4].u=1;pVerts[1+i*4].v=0;
			pVerts[2+i*4].u=1;pVerts[2+i*4].v=1;
			pVerts[3+i*4].u=0;pVerts[3+i*4].v=1;

	pVerts[0+i*4].color=0x00ffffff;
	pVerts[1+i*4].color=0x00ffffff;
	pVerts[2+i*4].color=0x00ffffff;
	pVerts[3+i*4].color=0x00ffffff;

	pVerts[0+i*4].n1=0;pVerts[0+i*4].n2=0;pVerts[0+i*4].n3=0;
	pVerts[1+i*4].n1=0;pVerts[1+i*4].n2=0;pVerts[1+i*4].n3=0;
	pVerts[2+i*4].n1=0;pVerts[2+i*4].n2=0;pVerts[2+i*4].n3=0;
	pVerts[3+i*4].n1=0;pVerts[3+i*4].n2=0;pVerts[3+i*4].n3=0;

	pInds[0+i*6]=0+i*4;pInds[1+i*6]=1+i*4;pInds[2+i*6]=2+i*4;
	pInds[3+i*6]=0+i*4;pInds[4+i*6]=2+i*4;pInds[5+i*6]=3+i*4;
}

		pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);

	SetTexture(0,Get(CPos,2),0);
	SetMaterial(&Material[Get(CPos,3)]);

	NumVerts=4*count;
	NumInds=6*count;
	NumTriangles=2*count;


//FlatNormals();
	ApplyMods();

	greedx=sqrt((float)count);
	greedy=sqrt((float)count);
	//FlatNormals();
	Svertka2Normals();
	FillVB(0);
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

void CopyToVB()
{
int n=Get(CPos,1);
if (n<0||n>maxvb) return;
FillVB(n);
VBNumVerts[n]=NumVerts;// количество вершин
VBNumTriangles[n]=NumTriangles;// количество треугольников
VBNumInds[n]=NumInds;// количество индексов.
}




void ResizeTexture()
{
	int n=Get(CPos,1);int s=Get(CPos,2);

	if (n<0||n>maxtex) return;
	if (s<0||s>7) return;
	int r[8]={32,64,128,256,512,1024,2048,4096};
	D3DFORMAT f[5]={D3DFMT_A8R8G8B8,D3DFMT_A16B16G16R16F,D3DFMT_A32B32G32R32F,D3DFMT_A16B16G16R16};
	int ff=Get(CPos,3);
	if (ff<0||ff>3) return;

	LPDIRECT3DSURFACE9 RT;
	for (int i=0;i<6;i++)
	{
	//Texture[n]->GetSurfaceLevel(0,&RT);
	//RT->Release();
	}

	Texture[n]->Release();
	pDevice->CreateTexture(r[s],r[s],0,D3DUSAGE_RENDERTARGET,f[ff],D3DPOOL_DEFAULT,&Texture[n],NULL);

	tex_res[n]=r[s];

	
}

void ShowVB()
{

	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	SetMaterial(&Material[Get(CPos,3)]);
	
	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
 	
	vbout_start=0;
	vbout_end=NumTriangles;

	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;

	D3DXMatrixMultiply(&CMatrix,&CMatrix,&w);

	pDevice->SetTransform(D3DTS_WORLD, &CMatrix);

	//later should be "set vs "

/*	D3DXMATRIX mvp,mwv;
	D3DXMATRIX v,w,ww,r,t,t1;
	D3DXMATRIX p;
	w=World;
	v=View;
	p=Projection;
	//mvp=View;
	//MulMat(&mvp,&Projection);	
	D3DXMatrixRotationY(&r,ptime/100.0);
	D3DXMatrixTranslation(&t,0,0,1);
	D3DXMatrixTranslation(&t1,0,0,-.5);
	
	//D3DXMatrixMultiply(&ww,&w,&t1);
	//ww=w;
	
	D3DXMatrixMultiply(&ww,&v,&r);
	D3DXMatrixMultiply(&ww,&ww,&w);
	//D3DXMatrixMultiply(&ww,&ww,&v);
	
	//D3DXMatrixMultiply(&ww,&ww,&t);
	//D3DXMatrixMultiply(&ww,&p,&ww);
	D3DXMatrixMultiply(&ww,&ww,&p);
	

	D3DXHANDLE h0;
	h0 = pCt->GetConstantByName(0, "matViewProjection");
	pCt->SetMatrix(pDevice, h0, &ww);

	pDevice->SetVertexShader(Shader_VSBase3D);
	pDevice->SetPixelShader(Shader_PSBase3D);
	//pDevice->SetPixelShaderConstantF(0,&b,1);
*/
	/*if (setshader_flag==1) 
		{
			D3DMATRIX w;
			w=World;
			World=CMatrix;
			_SetShader();
			World=w;
		}	
*/
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, vbout_start*3,vbout_end-vbout_start);	
	
	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &View);

	//pDevice->SetVertexShader(NULL);
	//pDevice->SetPixelShader(NULL);
	
	pDevice->SetTransform(D3DTS_WORLD, &StartMatrix);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	setshader_flag=0;
}



void ShowVBs()
{
	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	//SetMaterial(&Material[Get(CPos,3)]);
	

	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w,p,s,RMatrix,TMatrix;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
	D3DXMatrixIdentity(&PMatrix);
	D3DXMatrixIdentity(&AMatrix);
	int cn;
	cn=Get(CPos,5);
	double rx,ry,rz;float spdx,spdy,spdz;double ay,ap,ar;
	rx=Get(CPos,6)/1000.0;
	ry=Get(CPos,7)/1000.0;
	rz=Get(CPos,8)/1000.0;
	spdx=Get(CPos,9)/1000.0;
	spdy=Get(CPos,10)/1000.0;
	spdz=Get(CPos,11)/1000.0;
	
	ay=Get(CPos,12)/1000.0;
	ap=Get(CPos,13)/1000.0;
	ar=Get(CPos,14)/1000.0;

	int m1,m2,m3,mspd;
	m1=Get(CPos,3);
	m2=Get(CPos,15);
	m3=Get(CPos,16);
	mspd=Get(CPos,17)+1;

	

	vbout_start=0;
	vbout_end=NumTriangles;

	scatterN=-1;
	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;


	D3DXMatrixIdentity(&s);

	int vbsiter=0;
	srand(0);
	while (vbsiter<cn)
	{
	float x,y,z,a1,a2,a3;
	x=.5+.5*sin(((double)rand())/100.0);
	y=.5+.5*sin(((double)rand())/100.0)*sin(((double)rand())/100.0);
	z=.5+.5*sin(((double)rand())/100.0);
	
	x=frac(x+spdx*ptime/10.0)-.5;
	y=frac(y+spdy*ptime/10.0)-.5;
	z=frac(z+spdz*ptime/10.0)-.5;
	

//	x*=vbsiter/(float)cn;//?
//	y*=vbsiter/(float)cn;//?
//	z*=vbsiter/(float)cn;//?

	x*=rx;y*=ry;z*=rz;

	if (scatterN>=0)
	{
	x+=objposbufX[scatterN][vbsiter]*(1+scatterX*.01)*.01;
	y+=objposbufY[scatterN][vbsiter]*(1+scatterY*.01)*.01;	
	z+=objposbufZ[scatterN][vbsiter]*(1+scatterZ*.01)*.01;

	}

//	a1=(ay*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a2=(ap*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a3=(ar*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;

//	a1=(ay*vbsiter+ptime/1000.0)*3.14/180.0;
//	a2=(ap*vbsiter+ptime/1000.0)*3.14/180.0;
//	a3=(ar*vbsiter+ptime/1000.0)*3.14/180.0;

	a1=(ay*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a2=(ap*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a3=(ar*vbsiter*(ptime/1000.0+10000))*3.14/180.0;

	D3DXMatrixRotationYawPitchRoll(&TMatrix,a1,a2,a3);
	D3DXMatrixTranslation(&RMatrix,x,y,z);//random matrix creation
	D3DXMatrixMultiply(&s,&s,&CMatrix);//for each
	D3DXMatrixMultiply(&p,&s,&PMatrix);//for all
	
	D3DXMatrixMultiply(&p,&p,&TMatrix);//random a apply
	D3DXMatrixMultiply(&p,&p,&RMatrix);//random matrix apply
	D3DXMatrixMultiply(&p,&p,&AMatrix);//final apply

	D3DXMatrixMultiply(&p,&p,&w);	
	pDevice->SetTransform(D3DTS_WORLD, &p);

	float lv;
	lv=frac(mspd*(float)vbsiter/(float)cn);

	TempMaterial2.Ambient.r=lerp3(Material[m1].Ambient.r,Material[m2].Ambient.r,Material[m3].Ambient.r,lv);
	TempMaterial2.Ambient.g=lerp3(Material[m1].Ambient.g,Material[m2].Ambient.g,Material[m3].Ambient.g,lv);
	TempMaterial2.Ambient.b=lerp3(Material[m1].Ambient.b,Material[m2].Ambient.b,Material[m3].Ambient.b,lv);

	TempMaterial2.Diffuse.r=lerp3(Material[m1].Diffuse.r,Material[m2].Diffuse.r,Material[m3].Diffuse.r,lv);
	TempMaterial2.Diffuse.g=lerp3(Material[m1].Diffuse.g,Material[m2].Diffuse.g,Material[m3].Diffuse.g,lv);
	TempMaterial2.Diffuse.b=lerp3(Material[m1].Diffuse.b,Material[m2].Diffuse.b,Material[m3].Diffuse.b,lv);

	TempMaterial2.Specular.r=lerp3(Material[m1].Specular.r,Material[m2].Specular.r,Material[m3].Specular.r,lv);
	TempMaterial2.Specular.g=lerp3(Material[m1].Specular.g,Material[m2].Specular.g,Material[m3].Specular.g,lv);
	TempMaterial2.Specular.b=lerp3(Material[m1].Specular.b,Material[m2].Specular.b,Material[m3].Specular.b,lv);

	TempMaterial2.Power=lerp3(Material[m1].Power,Material[m2].Power,Material[m3].Power,lv);
	
	SetMaterial(&TempMaterial2);
	
	if (setshader_flag==1) 
		{
			D3DMATRIX w;
			w=World;
			World=p;
			//instM=p;
			//_SetShader(CurrentShader);
			InstanceNum=vbsiter;
			_ApplyShader(lastShaderApplied,ApplyShaderPos);
			World=w;
		}
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, vbout_start*3,vbout_end-vbout_start);	
	vbsiter++;
	}

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &World);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	setshader_flag=0;
}

void ShowVBsL()
{
	int linepointer=0;

	float p17=Get(CPos,17)/1000.0;
	float p18=Get(CPos,18)/1000.0;
	float p19=Get(CPos,19)/1000.0;

	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	//SetMaterial(&Material[Get(CPos,3)]);
	

	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w,p,s,RMatrix,TMatrix;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
	D3DXMatrixIdentity(&PMatrix);
	D3DXMatrixIdentity(&AMatrix);
	int cn;
	cn=Get(CPos,5);
	double rx,ry,rz;float spdx,spdy,spdz;double ay,ap,ar;
	rx=Get(CPos,6)/1000.0;
	ry=Get(CPos,7)/1000.0;
	rz=Get(CPos,8)/1000.0;
	spdx=Get(CPos,9)/1000.0;
	spdy=Get(CPos,10)/1000.0;
	spdz=Get(CPos,11)/1000.0;
	
	ay=Get(CPos,12)/1000.0;
	ap=Get(CPos,13)/1000.0;
	ar=Get(CPos,14)/1000.0;

	int m1,m2,m3,mspd;
	m1=Get(CPos,3);
	m2=Get(CPos,15);
	m3=Get(CPos,16);
	mspd=1;//Get(CPos,17)+1;

	

	vbout_start=0;
	vbout_end=NumTriangles;

	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;


	D3DXMatrixIdentity(&s);

	int vbsiter=0;
	srand(0);
	while (vbsiter<cn)
	{
	float x,y,z,a1,a2,a3;
	x=.5+.5*sin(((double)rand())/100.0);
	y=.5+.5*sin(((double)rand())/100.0)*sin(((double)rand())/100.0);
	z=.5+.5*sin(((double)rand())/100.0);
	
	x=frac(x+spdx*ptime/10.0)-.5;
	y=frac(y+spdy*ptime/10.0)-.5;
	z=frac(z+spdz*ptime/10.0)-.5;

//	x*=vbsiter/(float)cn;//?
//	y*=vbsiter/(float)cn;//?
//	z*=vbsiter/(float)cn;//?

	x*=rx;y*=ry;z*=rz;
	
//	a1=(ay*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a2=(ap*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a3=(ar*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;

//	a1=(ay*vbsiter+ptime/1000.0)*3.14/180.0;
//	a2=(ap*vbsiter+ptime/1000.0)*3.14/180.0;
//	a3=(ar*vbsiter+ptime/1000.0)*3.14/180.0;

	a1=(ay*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a2=(ap*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a3=(ar*vbsiter*(ptime/1000.0+10000))*3.14/180.0;

	D3DXMatrixRotationYawPitchRoll(&TMatrix,a1,a2,a3);
	D3DXMatrixTranslation(&RMatrix,x,y,z);//random matrix creation
	D3DXMatrixMultiply(&s,&s,&CMatrix);//for each
	D3DXMatrixMultiply(&p,&s,&PMatrix);//for all
	
	D3DXMatrixMultiply(&p,&p,&TMatrix);//random a apply
	D3DXMatrixMultiply(&p,&p,&RMatrix);//random matrix apply
	D3DXMatrixMultiply(&p,&p,&AMatrix);//final apply

	D3DXMatrixMultiply(&p,&p,&w);	
	pDevice->SetTransform(D3DTS_WORLD, &p);

//lines
	D3DXVECTOR3 vec,vec2;
	D3DXQUATERNION q;
	D3DXMatrixDecompose(&vec2,&q,&vec,&p);
	pVerts[linepointer].x=p17;
	pVerts[linepointer].y=p18;
	pVerts[linepointer].z=p19;
	pVerts[linepointer].color=0x00ff0000;
	pVerts[linepointer+1].x=vec.x;
	pVerts[linepointer+1].y=vec.y;
	pVerts[linepointer+1].z=vec.z-1;
	pVerts[linepointer+1].color=0x00ff0000;
	linepointer+=2;
//
	float lv;
	lv=frac(mspd*(float)vbsiter/(float)cn);

	TempMaterial2.Ambient.r=lerp3(Material[m1].Ambient.r,Material[m2].Ambient.r,Material[m3].Ambient.r,lv);
	TempMaterial2.Ambient.g=lerp3(Material[m1].Ambient.g,Material[m2].Ambient.g,Material[m3].Ambient.g,lv);
	TempMaterial2.Ambient.b=lerp3(Material[m1].Ambient.b,Material[m2].Ambient.b,Material[m3].Ambient.b,lv);

	TempMaterial2.Diffuse.r=lerp3(Material[m1].Diffuse.r,Material[m2].Diffuse.r,Material[m3].Diffuse.r,lv);
	TempMaterial2.Diffuse.g=lerp3(Material[m1].Diffuse.g,Material[m2].Diffuse.g,Material[m3].Diffuse.g,lv);
	TempMaterial2.Diffuse.b=lerp3(Material[m1].Diffuse.b,Material[m2].Diffuse.b,Material[m3].Diffuse.b,lv);

	TempMaterial2.Specular.r=lerp3(Material[m1].Specular.r,Material[m2].Specular.r,Material[m3].Specular.r,lv);
	TempMaterial2.Specular.g=lerp3(Material[m1].Specular.g,Material[m2].Specular.g,Material[m3].Specular.g,lv);
	TempMaterial2.Specular.b=lerp3(Material[m1].Specular.b,Material[m2].Specular.b,Material[m3].Specular.b,lv);

	TempMaterial2.Power=lerp3(Material[m1].Power,Material[m2].Power,Material[m3].Power,lv);
	
	SetMaterial(&TempMaterial2);

	if (setshader_flag==1) 
		{
			D3DMATRIX w;
			w=World;
			World=p;
			_SetShader(CurrentShader);
			World=w;
		}
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, vbout_start*3,vbout_end-vbout_start);	
	vbsiter++;
	}

	

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &World);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	SetMaterial(&Material[m1]);
	pDevice->SetTexture(0,NULL);
	pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,TRUE);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, linepointer/2,pVerts,sizeof(MyVertex));


//	setshader_flag=0;
}

void ShowVBsIsolated()
{
	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	//SetMaterial(&Material[Get(CPos,3)]);
	

	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
//	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w,p,s,RMatrix,TMatrix;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
	D3DXMatrixIdentity(&PMatrix);
	D3DXMatrixIdentity(&AMatrix);
	int cn;
	cn=Get(CPos,5);
	double rx,ry,rz;float spdx,spdy,spdz;double ay,ap,ar;
	rx=Get(CPos,6)/1000.0;
	ry=Get(CPos,7)/1000.0;
	rz=Get(CPos,8)/1000.0;
	spdx=Get(CPos,9)/1000.0;
	spdy=Get(CPos,10)/1000.0;
	spdz=Get(CPos,11)/1000.0;
	
	ay=Get(CPos,12)/1000.0;
	ap=Get(CPos,13)/1000.0;
	ar=Get(CPos,14)/1000.0;

	int m1,m2,m3,mspd;
	m1=Get(CPos,3);
	m2=Get(CPos,15);
	m3=Get(CPos,16);
	mspd=Get(CPos,17)+1;

	

	vbout_start=0;
	vbout_end=NumTriangles;

	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;


	D3DXMatrixIdentity(&s);

	int vbsiter=0;
	srand(0);
	while (vbsiter<cn)
	{
	float x,y,z,a1,a2,a3;
	x=.5+.5*sin(((double)rand())/100.0);
	y=.5+.5*sin(((double)rand())/100.0)*sin(((double)rand())/100.0);
	z=.5+.5*sin(((double)rand())/100.0);
	
	x=frac(x+spdx*ptime/10.0)-.5;
	y=frac(y+spdy*ptime/10.0)-.5;
	z=frac(z+spdz*ptime/10.0)-.5;

//	x*=vbsiter/(float)cn;//?
//	y*=vbsiter/(float)cn;//?
//	z*=vbsiter/(float)cn;//?

	x*=rx;y*=ry;z*=rz;
	
//	a1=(ay*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a2=(ap*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a3=(ar*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;

//	a1=(ay*vbsiter+ptime/1000.0)*3.14/180.0;
//	a2=(ap*vbsiter+ptime/1000.0)*3.14/180.0;
//	a3=(ar*vbsiter+ptime/1000.0)*3.14/180.0;

	a1=(ay*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a2=(ap*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a3=(ar*vbsiter*(ptime/1000.0+10000))*3.14/180.0;

	D3DXMatrixRotationYawPitchRoll(&TMatrix,a1,a2,a3);
	D3DXMatrixTranslation(&RMatrix,x,y,z);//random matrix creation
	D3DXMatrixMultiply(&s,&s,&CMatrix);//for each
	D3DXMatrixMultiply(&p,&s,&PMatrix);//for all
	
	D3DXMatrixMultiply(&p,&p,&TMatrix);//random a apply
	D3DXMatrixMultiply(&p,&p,&RMatrix);//random matrix apply
	D3DXMatrixMultiply(&p,&p,&AMatrix);//final apply

	D3DXMatrixMultiply(&p,&p,&w);	
	pDevice->SetTransform(D3DTS_WORLD, &p);

	float lv;
	lv=frac(mspd*(float)vbsiter/(float)cn);

	TempMaterial2.Ambient.r=lerp3(Material[m1].Ambient.r,Material[m2].Ambient.r,Material[m3].Ambient.r,lv);
	TempMaterial2.Ambient.g=lerp3(Material[m1].Ambient.g,Material[m2].Ambient.g,Material[m3].Ambient.g,lv);
	TempMaterial2.Ambient.b=lerp3(Material[m1].Ambient.b,Material[m2].Ambient.b,Material[m3].Ambient.b,lv);

	TempMaterial2.Diffuse.r=lerp3(Material[m1].Diffuse.r,Material[m2].Diffuse.r,Material[m3].Diffuse.r,lv);
	TempMaterial2.Diffuse.g=lerp3(Material[m1].Diffuse.g,Material[m2].Diffuse.g,Material[m3].Diffuse.g,lv);
	TempMaterial2.Diffuse.b=lerp3(Material[m1].Diffuse.b,Material[m2].Diffuse.b,Material[m3].Diffuse.b,lv);

	TempMaterial2.Specular.r=lerp3(Material[m1].Specular.r,Material[m2].Specular.r,Material[m3].Specular.r,lv);
	TempMaterial2.Specular.g=lerp3(Material[m1].Specular.g,Material[m2].Specular.g,Material[m3].Specular.g,lv);
	TempMaterial2.Specular.b=lerp3(Material[m1].Specular.b,Material[m2].Specular.b,Material[m3].Specular.b,lv);

	TempMaterial2.Power=lerp3(Material[m1].Power,Material[m2].Power,Material[m3].Power,lv);
	
	SetMaterial(&TempMaterial2);

//	if (setshader_flag==1) 
		{
			D3DMATRIX w;
			w=World;
			World=p;
			//_SetShader(CurrentShader);
			_ApplyShader(lastShaderApplied,ApplyShaderPos);
			World=w;
		}
	
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, vbout_start*3,vbout_end-vbout_start);	

	//pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,TRUE);
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, vbout_start*3,vbout_end-vbout_start);	
	vbsiter++;
	}

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &World);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//	setshader_flag=0;
}


 int ramTs=0;

void MakeInstTable()
{
	int index=0;
	BYTE* addr;
	addr=texCopy;
	int size=ramTs;

	int key=Get(CPos,2);
	int channel=Get(CPos,1);
	int channelZ=Get(CPos,3);
	int bufN=Get(CPos,4);

	for(int i=0;i<maxgridsize*maxgridsize;i++)
	{
		objposbufX[bufN][i]=0;
		objposbufY[bufN][i]=0;
		objposbufZ[bufN][i]=0;
	}

	for (int y=0;y<size;y++)
	{
		for (int x=0;x<size;x++)
		{
			BYTE a;
			a=*(addr+y*4*size+x*4+channel);
			if (a==key)
			{
				objposbufX[bufN][index]=x-size/2;
				objposbufZ[bufN][index]=y-size/2;

			a=*(addr+y*4*size+x*4+channelZ);
				objposbufY[bufN][index]=a;
			index++;	
			}
		}
	}
}

void TexToRam()
{
	BYTE* addr;
	addr=texCopy;
	int size=tex_res[Get(CPos,1)];
	ramTs=size;
	int level=0;
	if(size==1024) level=1;
	if(size==512) level=2;
	if(size==256) level=3;
	if(size==128) level=4;
	if(size==64) level=5;
	if(size==32) level=6;

	    D3DLOCKED_RECT tl;
		HRESULT h;
		LPDIRECT3DSURFACE9 RT;
		h=Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT);
		h=TTt->GetSurfaceLevel(level,&TT);
		h=pDevice->GetRenderTargetData(RT,TT);
 		h=TT->LockRect(&tl,NULL,D3DLOCK_READONLY);

	for (int y=0;y<size;y++) memcpy (addr+(size-y)*4*size,(BYTE*)tl.pBits+y*tl.Pitch,size*4);//?y inverted on read or y inverted on draw

		TT->UnlockRect();

}

void CopyObjToPosBuf()
{
	int i=Get(CPos,1);
	int start=Get(CPos,2);
	//int end=NumVerts-Get(CPos,3);
	int end=VBNumVerts[currentVBtoadd]-Get(CPos,3);

	int skip=Get(CPos,4)+1;
	if (skip<1) skip=1; 
	float j=Get(CPos,2)/100.0;
	int a=0;
for (int n=start;n<end;n+=skip)
	{
		objposbufX[i][a]=pVerts[n].x*100+j*pVerts[n].n1;
	objposbufY[i][a]=pVerts[n].y*100+j*pVerts[n].n2;
	objposbufZ[i][a]=pVerts[n].z*100+j*pVerts[n].n3;
	a++;
	}
}

void ShowVBsMap3D()
{
	int pb=Get(CPos,19);
	int icn=Get(CPos,18);
	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	//SetMaterial(&Material[Get(CPos,3)]);
	

	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w,p,s,RMatrix,TMatrix,HM;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
	D3DXMatrixIdentity(&PMatrix);
	D3DXMatrixIdentity(&AMatrix);
	int cn;
	cn=Get(CPos,5);
	double rx,ry,rz;float spdx,spdy,spdz;double ay,ap,ar;
	rx=Get(CPos,6)/1000.0;
	ry=Get(CPos,7)/1000.0;
	rz=Get(CPos,8)/1000.0;
	spdx=Get(CPos,9)/1000.0;
	spdy=Get(CPos,10)/1000.0;
	spdz=Get(CPos,11)/1000.0;
	
	ay=Get(CPos,12)/1000.0;
	ap=Get(CPos,13)/1000.0;
	ar=Get(CPos,14)/1000.0;

	int m1,m2,m3,mspd;
	m1=Get(CPos,3);
	m2=Get(CPos,15);
	m3=Get(CPos,16);
	mspd=Get(CPos,17)+1;

	

	vbout_start=0;
	vbout_end=NumTriangles;

	HeadFlag=0;

	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;


	D3DXMatrixIdentity(&s);

	int vbsiter=0;
	srand(0);
	while (vbsiter<cn)
	{
	float x,y,z,a1,a2,a3;
	x=.5+.5*sin(((double)rand())/100.0);
	y=.5+.5*sin(((double)rand())/100.0)*sin(((double)rand())/100.0);
	z=.5+.5*sin(((double)rand())/100.0);
	
	x=frac(x+spdx*ptime/10.0)-.5;
	y=frac(y+spdy*ptime/10.0)-.5;
	z=frac(z+spdz*ptime/10.0)-.5;

//	x*=vbsiter/(float)cn;//?
//	y*=vbsiter/(float)cn;//?
//	z*=vbsiter/(float)cn;//?

	x*=rx;y*=ry;z*=rz;



//	a1=(ay*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a2=(ap*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;
//	a3=(ar*vbsiter*ptime/1000.0+ptime/10.0)*3.14/180.0;

//	a1=(ay*vbsiter+ptime/1000.0)*3.14/180.0;
//	a2=(ap*vbsiter+ptime/1000.0)*3.14/180.0;
//	a3=(ar*vbsiter+ptime/1000.0)*3.14/180.0;

	a1=0;//(ay*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a2=0;//(ap*vbsiter*(ptime/1000.0+10000))*3.14/180.0;
	a3=0;//(ar*vbsiter*(ptime/1000.0+10000))*3.14/180.0;

for (int int_iter=0;int_iter<icn;int_iter++)
{
	a1=(spdx*(vbsiter+int_iter))*3.14/180.0;
	a2=(spdy*(vbsiter+int_iter))*3.14/180.0;
	a3=(spdz*(vbsiter+int_iter))*3.14/180.0;

//	x=objposbufX[vbsiter]*rx+rand()/1000000.0;
//	y=objposbufY[vbsiter]*ry+rand()/1000000.0;	
//	z=objposbufZ[vbsiter]*rz+rand()/1000000.0;

	x=objposbufX[pb][vbsiter]*rx+rand()*ay/1000.0;
	y=objposbufY[pb][vbsiter]*ry+rand()*ap/1000.0;	
	z=objposbufZ[pb][vbsiter]*rz+rand()*ar/1000.0;


	D3DXMatrixRotationYawPitchRoll(&TMatrix,a1,a2,a3);
	D3DXMatrixTranslation(&RMatrix,x,y,z);//random matrix creation
	D3DXMatrixMultiply(&s,&s,&CMatrix);//for each
	D3DXMatrixMultiply(&p,&s,&PMatrix);//for all
	
	D3DXMatrixMultiply(&p,&p,&TMatrix);//random a apply
	D3DXMatrixMultiply(&p,&p,&RMatrix);//random matrix apply
	D3DXMatrixMultiply(&p,&p,&AMatrix);//final apply

	HM=p;

	D3DXMatrixMultiply(&p,&p,&w);	
	pDevice->SetTransform(D3DTS_WORLD, &p);

	float lv;
	lv=frac(mspd*(float)vbsiter/(float)cn);

	TempMaterial2.Ambient.r=lerp3(Material[m1].Ambient.r,Material[m2].Ambient.r,Material[m3].Ambient.r,lv);
	TempMaterial2.Ambient.g=lerp3(Material[m1].Ambient.g,Material[m2].Ambient.g,Material[m3].Ambient.g,lv);
	TempMaterial2.Ambient.b=lerp3(Material[m1].Ambient.b,Material[m2].Ambient.b,Material[m3].Ambient.b,lv);

	TempMaterial2.Diffuse.r=lerp3(Material[m1].Diffuse.r,Material[m2].Diffuse.r,Material[m3].Diffuse.r,lv);
	TempMaterial2.Diffuse.g=lerp3(Material[m1].Diffuse.g,Material[m2].Diffuse.g,Material[m3].Diffuse.g,lv);
	TempMaterial2.Diffuse.b=lerp3(Material[m1].Diffuse.b,Material[m2].Diffuse.b,Material[m3].Diffuse.b,lv);

	TempMaterial2.Specular.r=lerp3(Material[m1].Specular.r,Material[m2].Specular.r,Material[m3].Specular.r,lv);
	TempMaterial2.Specular.g=lerp3(Material[m1].Specular.g,Material[m2].Specular.g,Material[m3].Specular.g,lv);
	TempMaterial2.Specular.b=lerp3(Material[m1].Specular.b,Material[m2].Specular.b,Material[m3].Specular.b,lv);

	TempMaterial2.Power=lerp3(Material[m1].Power,Material[m2].Power,Material[m3].Power,lv);
	
	SetMaterial(&TempMaterial2);

	if (setshader_flag==1) 
		{
			D3DMATRIX w;
			w=World;
			World=p;
			_SetShader(CurrentShader);
			World=w;
		}

if ((vbsiter==cn-1)&&(HeadFlag==1))
{	
	pDevice->SetStreamSource( 0, pVB[HeadN], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[HeadN]);

	NumVerts=VBNumVerts[HeadN];// количество вершин
	NumTriangles=VBNumTriangles[HeadN];// количество треугольников
	NumInds=VBNumInds[HeadN];// количество индексов.

	vbout_start=0;
	vbout_end=NumTriangles;

	SetTexture(0,HeadTex,0);
	SetMaterial(&Material[HeadMat]);

	if (HeadExtractPosFlag==1) 
	{
		D3DXMATRIX pH;D3DXMATRIX s;
		D3DXMATRIX o;D3DXMatrixIdentity(&pH);
		s=HM;
		D3DXVECTOR3 vS,vT;
		D3DXQUATERNION qR;
		D3DXMatrixDecompose(&vS,&qR,&vT,&s);
	//	D3DXMatrixTranslation(&pH,vT.x,vT.y,vT.z);
		//D3DXMatrixTranslation(&o,vT.x,vT.y,vT.z);
		D3DXMatrixTranslation(&o,s._41,s._42,s._43);

		
			D3DXMatrixMultiply(&pH,&o,&w);
		pDevice->SetTransform(D3DTS_WORLD, &pH);
	
	}
}

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, vbout_start*3,vbout_end-vbout_start);	
}

	vbsiter++;
	}

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &World);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//setshader_flag=0;
}

void ShowVBs1()
{
	if (Get(CPos,1)>maxvb) return;

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	SetTexture(0,Get(CPos,2),0);
	
	SetMaterial(&Material[Get(CPos,3)]);
	
	SetAlfa(Get(CPos,4));

	pDevice->SetStreamSource( 0, pVB[Get(CPos,1)], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[Get(CPos,1)]);

	NumVerts=VBNumVerts[Get(CPos,1)];// количество вершин
	NumTriangles=VBNumTriangles[Get(CPos,1)];// количество треугольников
	NumInds=VBNumInds[Get(CPos,1)];// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	D3DXMATRIX w,p,s,RMatrix;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
	D3DXMatrixIdentity(&PMatrix);
	int cn;
	cn=Get(CPos,5);
	double rx,ry,rz;
	rx=Get(CPos,6)/1000.0;
	ry=Get(CPos,7)/1000.0;
	rz=Get(CPos,8)/1000.0;
	ApplyMods(); 
	D3DXMatrixIdentity(&s);

	int vbsiter=0;
	srand(0);
	while (vbsiter<cn)
	{

		D3DXMatrixTranslation(&RMatrix,rx*sin(((double)rand())/100.0),ry*sin(((double)rand())/100.0),rz*sin(((double)rand())/100.0));//random matrix creation
		D3DXMatrixMultiply(&s,&s,&CMatrix);//for each
		D3DXMatrixMultiply(&p,&s,&PMatrix);//for all
	
		D3DXMatrixMultiply(&p,&p,&RMatrix);//random matrix apply

		D3DXMatrixMultiply(&p,&p,&w);	
		pDevice->SetTransform(D3DTS_WORLD, &p);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);		
		vbsiter++;
	}

	if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &World);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}

void __AddToVB(int vbi)
{
if (vbi<0||vbi>maxvb) return;

if ((VBNumVerts[vbi]+NumVerts)>maxgridsize*maxgridsize) return;

for (int i=0;i<NumInds;i++)
{
pInds[i]+=VBNumVerts[vbi];
}

void * pBuf;
		HRESULT h;
		h=pVB[vbi]->Lock( (UINT)VBNumVerts[vbi]*sizeof(MyVertex), sizeof(MyVertex) * NumVerts, &pBuf,0 );
		if (h==D3D_OK)  memcpy( pBuf, pVerts, sizeof(MyVertex) * NumVerts); //else MessageBox(hWnd0,"vb","vb",0);
		pVB[vbi]->Unlock();
		
		pIB[vbi]->Lock( (UINT)VBNumInds[vbi]*4, 4 * NumInds, &pBuf,0 );
		  memcpy( pBuf, pInds,4 * NumInds);
		pIB[vbi]->Unlock();

VBNumVerts[vbi]+=NumVerts;// количество вершин
VBNumTriangles[vbi]+=NumTriangles;// количество треугольников
VBNumInds[vbi]+=NumInds;// количество индексов.
}

void _AddToVB()
{
__AddToVB(currentVBtoadd);
}

void AddToVB()
{

	__AddToVB(Get(CPos,1));

}

void CleanVB()
{
VBNumVerts[Get(CPos,1)]=0;// количество вершин
VBNumTriangles[Get(CPos,1)]=0;// количество треугольников
VBNumInds[Get(CPos,1)]=0;// количество индексов.

}

//matrix - for vb and maybe for camera&lights

void MatrixRotate()
{
D3DXMatrixRotationYawPitchRoll(&TempMatrix,Get(CPos,1)*3.14/180.0/10.0,Get(CPos,2)*3.14/180.0/10.0,Get(CPos,3)*3.14/180.0/10.0);
if (Get(CPos,4)==0) D3DXMatrixMultiply(&CMatrix,&CMatrix,&TempMatrix);
if (Get(CPos,4)==1) D3DXMatrixMultiply(&PMatrix,&PMatrix,&TempMatrix);
if (Get(CPos,4)==2) D3DXMatrixMultiply(&AMatrix,&AMatrix,&TempMatrix);
}

void MatrixScale()
{
D3DXMatrixScaling(&TempMatrix,Get(CPos,1)/1000.0,Get(CPos,2)/1000.0,Get(CPos,3)/1000.0);
if (Get(CPos,4)==0) D3DXMatrixMultiply(&CMatrix,&CMatrix,&TempMatrix);
if (Get(CPos,4)==1) D3DXMatrixMultiply(&PMatrix,&PMatrix,&TempMatrix);
if (Get(CPos,4)==2) D3DXMatrixMultiply(&AMatrix,&AMatrix,&TempMatrix);
}

void MatrixTranslate()
{
D3DXMatrixTranslation(&TempMatrix,Get(CPos,1)/1000.0,Get(CPos,2)/1000.0,Get(CPos,3)/1000.0);
if (Get(CPos,4)==0) D3DXMatrixMultiply(&CMatrix,&CMatrix,&TempMatrix);
if (Get(CPos,4)==1) D3DXMatrixMultiply(&PMatrix,&PMatrix,&TempMatrix);
if (Get(CPos,4)==2) D3DXMatrixMultiply(&AMatrix,&AMatrix,&TempMatrix);
}

//----

void CopyStartScr()
{
int w=GetSystemMetrics(SM_CXSCREEN);
int h=GetSystemMetrics(SM_CYSCREEN);


    D3DLOCKED_RECT tl;
    StartScreen->LockRect(0,&tl,NULL,D3DLOCK_DISCARD);

//	int tsx,tsy;
//	tsx=w;tsy=h;
//	if (tsx>2048) tsx=2048;
//	if (tsy>2048) tsy=2048;
	for (int y=0;y<1024;y++)
	{
		for (int x=0;x<1024;x++)
		{
		int a;
		a=GetPixel(hdcCompatible,(int)(x*w/1024.0),(int)(y*h/1024.0));
		*((BYTE*)tl.pBits+y*tl.Pitch+x*4+2)=a&0xff;
		*((BYTE*)tl.pBits+y*tl.Pitch+x*4+1)=(a>>8)&0xff;
		*((BYTE*)tl.pBits+y*tl.Pitch+x*4+0)=(a>>16)&0xff;
		}
	}
	StartScreen->UnlockRect(0);
	
	LPDIRECT3DSURFACE9 RT,RT2;
	RECT SourceRect;
	RECT DestRect;
//StartScreen->Release();
	StartScreen->GetSurfaceLevel(0,&RT);
	Texture[Get(CPos,1)]->GetSurfaceLevel(0,&RT2);
	pDevice->StretchRect(RT,NULL,RT2,NULL,D3DTEXF_LINEAR);
	//Texture[17]->Release();
	//StartScreen->Release();


}


void StoreCurve()
{
int s=Get(CPos,1);

	for (int i=0;i<curve_len*curve_q;i++)
	{
		curvearray_x[s][i]=pVerts[i].x;
		curvearray_y[s][i]=pVerts[i].y;
		curvearray_z[s][i]=pVerts[i].z;
	}
	curvearray_clen[s]=(curve_len-3)*curve_q;
	ApplyMods();
}


//--?? navi ??
int pts=0;

void EndTimeLine()
{
timelinematrix=0;
}

void TimeLine()
{
		D3DXMATRIX ct,ct1;
		ct1=View2;
		D3DXVECTOR3 sv,sv1;
		D3DXVECTOR3 m1;
		D3DXQUATERNION q1;
		D3DXMatrixDecompose(&m1,&q1,&sv,&ct1);
		D3DXMatrixIdentity(&ct1);
		D3DXVec3TransformCoord(&sv,&sv,&ct1);
		D3DXMatrixTranslation(&ct,sv.x,sv.y,sv.z);
		D3DXMatrixMultiply(&ct1,&ct1,&ct);

		D3DXMatrixIdentity(&ct);
		D3DXMatrixTranslation(&ct,-ptime/1000.0,0,0);
		//D3DXMatrixMultiply(&ct,&ct1,&ct);
		
		cv=ct;
		pDevice->SetTransform(D3DTS_VIEW,&cv);
		pDevice->SetTransform(D3DTS_WORLD,&World);
		timelinematrix=1;
}

void SetTextureFilter()
{
  pDevice->SetSamplerState(Get(CPos,1),D3DSAMP_MAGFILTER,Get(CPos,2));
  pDevice->SetSamplerState(Get(CPos,1),D3DSAMP_MINFILTER,Get(CPos,3));
  pDevice->SetSamplerState(Get(CPos,1), D3DSAMP_MIPFILTER, Get(CPos,4));
}

double GetCounter();

void TimeCursor()
{
//return;
#ifndef EditMode
	//if (astate==1)
	{
		//ptime+=1;;
		//float dt=(int)(fp_delta/(1000.0/60.0));
		
		//ptime+=dt;
		ptime=(GetCounter()-start_time)/(10*60.0/36.0)+start_ptime;

		char aa[11];
		//_itoa(dt*10,aa,10);
		//NText(aa,-10,0,0,32);
		//SetWindowText(hWnd,aa);

	}
#else
	if (astate==1)
	{
		//ptime+=1;;
		//float dt=(int)(fp_delta/(1000.0/60.0));
		
		//ptime+=dt;
		ptime=(GetCounter()-start_time)/(10*60.0/36.0)+start_ptime;

		char aa[11];
		//_itoa(dt*10,aa,10);
		//NText(aa,-10,0,0,32);
		//SetWindowText(hWnd,aa);

	}
	else
	{
	ptime=Get(CPos,1);
	}
#endif


	TimeLine();
#ifndef EditMode
	if (ptime<0) ptime=0;
	*(short*)(RExchange+CPos+1*2)=ptime;
	
#endif

#ifdef EditMode		
	if (ptime<0) ptime=0;

	*(short*)(RExchange+CPos+1*2)=ptime;

	if (tlstate==1) return;

	pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,1);
	pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,1);
			for (int u=0;u<8;u++)	
			{
			pDevice->SetSamplerState(u, D3DSAMP_MIPFILTER, 0);
			}

	LightsOff();
	ZBufDisable();

	//navi scenes
	int i=0;
	
	int anim=0;int astart=0;int astop=0;
	while(i<EntriesCount*CellSize)
	{	
		if (nGet(i)==0) break;
		if (CmdDesc[nGet(i)].FRoutine==Camera) 
			{
				if (nGet(i+2*8)==1) {

					if (Pos==i) NaviBox(Get(i,9),Get(i,10),Get(i,11),50,255,255,255); else 
						 NaviBox(Get(i,9),Get(i,10),Get(i,11),50,127,127,127);
					NText("Cam",-7,Get(i,9)+5,Get(i,10),32);
				}
			}

		if (CmdDesc[nGet(i)].FRoutine==Key) 
			{
				if (Pos>=astart&&Pos<astop) {

					if (Pos==i) NaviBox(Get(i,1),Get(i,2),22,50,255,255,255); else 
						 NaviBox(Get(i,1),Get(i,2),22,50,127,127,127);
					NText("key",-7,Get(i,1)+5,Get(i,2),32);
				}
			}

		if (CmdDesc[nGet(i)].FRoutine==Animate) 
			{
				if (Get(i,1)==1)
				{
					int linkstack[1000];
					int counterstack[1000];
					float loopofs=0;
					
					int linkstackptr=0;

					astart=i;int q=15;
					int j;j=i+CmdDesc[nGet(i)].FSize;
					int cc=0;
					float ptsx[1000];float ptsy[1000];float ptsw[1000];
					int lastj=j;
					

					while (CmdDesc[nGet(j)].FLevel==2)
					{
						if (CmdDesc[nGet(j)].FRoutine==keyLoop) 
						{
							linkstack[linkstackptr]=j+CmdDesc[nGet(j)].FSize;
							counterstack[linkstackptr]=Get(j,1);
							
							linkstackptr++;
							
						}

						if ((CmdDesc[nGet(j)].FRoutine==keyLoopEnd)&&(linkstackptr>0)) 
						{
							
							if (counterstack[linkstackptr-1]>0) 
							{
								counterstack[linkstackptr-1]--;
								j=linkstack[linkstackptr-1];
								loopofs+=Get(lastj,1)/1000.0-Get(j,1)/1000.0;
							} else
							{
								if (linkstackptr>0)	linkstackptr--;
								
							}

						}


						if (CmdDesc[nGet(j)].FRoutine==Key) 
						{
							lastj=j;
							ptsx[cc]=Get(j,1)/1000.0+loopofs;
							ptsy[cc]=Get(j,2)/1000.0;
							ptsw[cc]=Get(j,3)/10.0;

							cc++;
						}

						j+=CmdDesc[nGet(j)].FSize;

					}
					astop=j;
					
					if (Pos>=astart&&Pos<astop) 
					{
						for (int d=0;d<cc;d++)
						{
							for (int p=0;p<q;p++)
							{
								
								float li=p/(float)q;
								pVerts[d*q+p].x=lerp(ptsx[d],ptsx[clampI(d+1,0,cc)],1-li);
								float ci=cubicInterpolateI(ptsy[clampI(d-1,0,cc)],
																ptsy[clampI(d,0,cc)],
																ptsy[clampI(d+1,0,cc)],
																ptsy[clampI(d+2,0,cc)],li);
								float cw=cubicInterpolateI(ptsw[clampI(d-1,0,cc)],
																ptsw[clampI(d,0,cc)],
																ptsw[clampI(d+1,0,cc)],
																ptsw[clampI(d+2,0,cc)],li);

								float clin=lerp(ptsy[d],ptsy[clampI(d+1,0,cc)],1-li);
								pVerts[d*q+p].y=lerp(ci,clin,cw);
								pVerts[d*q+p].z=0;
								pVerts[d*q+p].color=0;
							}
						
						}

						curve_q=q;

						pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
						pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

						SetMaterial(&WhiteMaterial);
						pDevice->SetTexture(0,NULL);

						NumVerts=(cc-1)*q+1;

						void * pBuf;
					
						pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts+1), &pBuf, 0 );
						  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts+1));
						pVB[0]->Unlock();
								
						pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
						pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, NumVerts-1);
					}
				}

			}


		if (CmdDesc[nGet(i)].FRoutine==ShowScene) 
			{
				if (Get(i,2)==1)
				{
		
				NaviBox(Get(i,3),Get(i,4),Get(i,5),50,Get(i,6),Get(i,7),Get(i,8));
				char ss[44];char s[12],sss[44];
				_itoa (Get(i,1),s,10);
				strcpy (ss,"Scene ");
				strcat(ss,s);
				strcat(ss," ");

				int j;
						int sccount;
							sccount=0;
						j=0;
						while (j<EntriesCount*CellSize)
						{	
							if (Get(j,0)==0) break;;
							if (CmdDesc[Get(j,0)].FRoutine==&Scene) 
							{
								sccount++;
							}
							if (sccount==Get(i,1)) 
								{
								break;
								}
							j+=CmdDesc[nGet(j)].FSize;
						}
				memcpy(sss,Pack+j+256-33,32);
				strcat(ss,sss);
				NText(ss,-7,Get(i,3)+25,Get(i,4),32);
				}
				
			}
		i+=CmdDesc[nGet(i)].FSize;
	}
	//

	double x=ptime;
	x/=1000.0;



	SetAlfa(2);

	pVerts[0].x=x;
	pVerts[0].y=-.2;
	pVerts[0].z=0;
	pVerts[0].color=0x00ffffff;

	pVerts[1].x=x;
	pVerts[1].y=.2;
	pVerts[1].z=0;
	pVerts[1].color=0x00ffffff;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,NULL);

	NumVerts=2;

			void * pBuf;
		
			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
			pVB[0]->Unlock();
					
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, NumVerts-1);

//draw horizont null
	NumVerts=6;

	pVerts[0].x=0;
	pVerts[0].y=0;
	pVerts[0].z=0;
	pVerts[0].color=0x00ffffff;

	pVerts[1].x=32767;
	pVerts[1].y=0;
	pVerts[1].z=0;
	pVerts[1].color=0x00ffffff;
//+1
	pVerts[2].x=0;
	pVerts[2].y=256.0/1000.0;
	pVerts[2].z=0;
	pVerts[2].color=0x00ffffff;

	pVerts[3].x=32767;
	pVerts[3].y=256.0/1000.0;
	pVerts[3].z=0;
	pVerts[3].color=0x00ffffff;

	pVerts[4].x=0;
	pVerts[4].y=-256.0/1000.0;
	pVerts[4].z=0;
	pVerts[4].color=0x00ffffff;

	pVerts[5].x=32767;
	pVerts[5].y=-256.0/1000.0;
	pVerts[5].z=0;
	pVerts[5].color=0x00ffffff;

	for (int i=0;i<32767/60;i++)
	{
		pVerts[6+i*2].x=i*60/1000.0;
		pVerts[6+i*2].y=-.01;
		pVerts[6+i*2].z=0;
		pVerts[6+i*2].color=0x00ffffff;

		pVerts[6+i*2+1].x=i*60/1000.0;
		pVerts[6+i*2+1].y=.01;
		pVerts[6+i*2+1].z=0;
		pVerts[6+i*2+1].color=0x00ffffff;
	}
	
	NumVerts+=32767/60*2;

			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
			pVB[0]->Unlock();
					
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NumVerts/2);
//----------
		for (int i=0;i<32767/60/60;i++)
	{
		pVerts[i*2].x=i*60*60/1000.0;
		pVerts[i*2].y=-.05;
		pVerts[i*2].z=0;
		pVerts[i*2].color=0x00ffffff;

		pVerts[i*2+1].x=i*60*60/1000.0;
		pVerts[i*2+1].y=.05;
		pVerts[i*2+1].z=0;
		pVerts[i*2+1].color=0x00ffffff;
	}
	
	NumVerts=32767/60/60*2;

			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
			pVB[0]->Unlock();
					
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, NumVerts/2);

	if (astate==1)
	{
		
	//	pDevice->SetTransform(D3DTS_VIEW,&View);
		
	}

	char aa[11];char bb[11];char cc[111];

	for (int i=0;i<32767;i+=60*10)
	{
	_itoa((int)(i/60)-60*(int)(i/60/60),aa,10);
	_itoa((int)(i/60/60),bb,10);
	strcpy(cc,bb);
	strcat(cc,":");
	strcat(cc,aa);
	NText(cc,-7,i-12,-74,32);
	}




	pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,2);
	pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,2);

#endif


}

void TrackXYZ()
{
	if (CmdDesc[Get(CPos+CmdDesc[nGet(CPos)].FSize,0)].FRoutine==TrackXYZ) return;

	int sp=Get(CPos,1);
	
	int outx,outy,outz;
	outx=Get(CPos,2);
	outy=Get(CPos,3);
	outz=Get(CPos,4);

	float a;
	float x,y,z;
	a=ptime;

	a=a*(float)Get(CPos,5)/1000.0;

	if (a<0)a=0;
	if (Get(CPos,6)==0) if (a>(curvearray_clen[sp])) a=curvearray_clen[sp];
	if (Get(CPos,6)==1) a=frac(a/(float)curvearray_clen[sp])*curvearray_clen[sp];

	x=lerp(curvearray_x[sp][(int)a+1],curvearray_x[sp][(int)a],frac(a));
	y=lerp(curvearray_y[sp][(int)a+1],curvearray_y[sp][(int)a],frac(a));
	z=lerp(curvearray_z[sp][(int)a+1],curvearray_z[sp][(int)a],frac(a));

	x*=1000;y*=1000;z*=1000;
		
	if (outx>0) *(short*)(RExchange+(CPos+CmdDesc[nGet(CPos)].FSize)+outx*2)=x;
	if (outy>0) *(short*)(RExchange+(CPos+CmdDesc[nGet(CPos)].FSize)+outy*2)=y;
	if (outz>0) *(short*)(RExchange+(CPos+CmdDesc[nGet(CPos)].FSize)+outz*2)=z;
	
}

void ReflectCamY()
{
D3DMATRIX vm;
D3DXMATRIX vm_,out;
pDevice->GetTransform(D3DTS_VIEW,&vm);
vm_=vm;
D3DXMATRIX R;
D3DXPLANE plane(0.0f, 1.0f, 0.0f, 0.0f);

D3DXMATRIX inverseOfT;
D3DXMATRIX inverseTransposeOfT;

D3DXMatrixInverse(&inverseOfT, 0, &vm_);
D3DXMatrixTranspose(&inverseTransposeOfT, &inverseOfT);

//D3DXPlaneNormalize(&p, &p);   // Нормализация вектора нормали
D3DXPlaneTransform(&plane, &plane, &inverseTransposeOfT);

D3DXMatrixReflect(&R, &plane);
D3DXMatrixMultiply(&out,&vm_,&R);
pDevice->SetTransform(D3DTS_VIEW,&out);


}


void Spline1Camera()
{
	//if (astate==-1) return;
#ifdef EditMode
	if (camstate==-1) return;
#endif

	int sp=Get(CPos,1);
	int sp2=Get(CPos,2);

	float a;
	float x,y,z;
	a=ptime;

	a=a*(float)Get(CPos,3)/1000.0;

	if (a<0)a=0;
	if (Get(CPos,4)==0) if (a>(curvearray_clen[sp])) a=curvearray_clen[sp];
	if (Get(CPos,4)==1) a=frac(a/(float)curvearray_clen[sp])*curvearray_clen[sp];

	float eye_x=lerp(curvearray_x[sp][(int)a+1],curvearray_x[sp][(int)a],frac(a));
	float eye_y=lerp(curvearray_y[sp][(int)a+1],curvearray_y[sp][(int)a],frac(a));
	float eye_z=lerp(curvearray_z[sp][(int)a+1],curvearray_z[sp][(int)a],frac(a));

	a+=1;

	float at_x=lerp(curvearray_x[sp][(int)a+1],curvearray_x[sp][(int)a],frac(a));
	float at_y=lerp(curvearray_y[sp][(int)a+1],curvearray_y[sp][(int)a],frac(a));
	float at_z=lerp(curvearray_z[sp][(int)a+1],curvearray_z[sp][(int)a],frac(a));

	float angle=lerp(curvearray_y[sp2][(int)a+1],curvearray_y[sp2][(int)a],frac(a));

D3DXMATRIX out;
D3DXVECTOR3 eye(eye_x,eye_y,eye_z);
D3DXVECTOR3 at(at_x,at_y,at_z);
angle=angle*3.14/180.0;

D3DXVECTOR3 up_src(0,1,0);
D3DXVECTOR3 up;
D3DXMATRIX m_angle;
D3DXMatrixRotationZ(&m_angle,angle);
D3DXVec3TransformCoord(&up,&up_src,&m_angle);

D3DXMatrixLookAtLH(&out, &eye, &at, &up);
D3DXMATRIX tr;
D3DXMatrixTranslation(&tr,0,0,1);

  D3DMATRIX tr_ = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };

  pDevice->SetTransform(D3DTS_WORLD,&tr_);


D3DXMatrixMultiply(&out,&out,&tr);

View=out;
//pDevice->SetTransform(D3DTS_VIEW,&View);
SetView(0);
}

void Spline2Camera()
{
	//if (astate==-1) return;
#ifdef EditMode
	if (camstate==-1) return;
#endif

	int sp=Get(CPos,1);
	int sp2=Get(CPos,2);
	int sp3=Get(CPos,3);

	float a;
	float x,y,z;
	a=ptime;

	a=a*(float)Get(CPos,4)/1000.0;

	if (a<0)a=0;
	if (Get(CPos,5)==0) if (a>(curvearray_clen[sp])) a=curvearray_clen[sp];
	if (Get(CPos,5)==1) a=frac(a/(float)curvearray_clen[sp])*curvearray_clen[sp];

	float eye_x=lerp(curvearray_x[sp][(int)a+1],curvearray_x[sp][(int)a],frac(a));
	float eye_y=lerp(curvearray_y[sp][(int)a+1],curvearray_y[sp][(int)a],frac(a));
	float eye_z=lerp(curvearray_z[sp][(int)a+1],curvearray_z[sp][(int)a],frac(a));

	float at_x=lerp(curvearray_x[sp2][(int)a+1],curvearray_x[sp2][(int)a],frac(a));
	float at_y=lerp(curvearray_y[sp2][(int)a+1],curvearray_y[sp2][(int)a],frac(a));
	float at_z=lerp(curvearray_z[sp2][(int)a+1],curvearray_z[sp2][(int)a],frac(a));

	float angle=lerp(curvearray_y[sp3][(int)a+1],curvearray_y[sp3][(int)a],frac(a));

D3DXVECTOR3 up_src(0,1,0);
D3DXVECTOR3 up;
D3DXMATRIX m_angle;
D3DXMatrixRotationZ(&m_angle,angle*3.14/180.0);
D3DXVec3TransformCoord(&up,&up_src,&m_angle);

D3DXMATRIX out;
D3DXVECTOR3 eye(eye_x,eye_y,eye_z);
D3DXVECTOR3 at(at_x,at_y,at_z);
//D3DXVECTOR3 up(0,1,0);



D3DXMatrixLookAtLH(&out, &eye, &at, &up);
D3DXMATRIX tr;
D3DXMatrixTranslation(&tr,0,0,1);

  D3DMATRIX tr_ = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
	pDevice->SetTransform(D3DTS_WORLD,&tr_);


D3DXMatrixMultiply(&out,&out,&tr);

View=out;
//pDevice->SetTransform(D3DTS_VIEW,&View);
SetView(0);
}


void Camera()
{
//if (astate==-1) return;
#ifdef EditMode
	if (camstate==-1) return;
#endif

//time check
/*if (Get(CPos,8)==1) {
int x=Get(CPos,9);
int w=Get(CPos,11);

	if (x>ptime||(x+w)<ptime) 
	{
	return;//
	}

}*/

float eye_x=(float)Get(CPos,1)/1000.0;
float eye_y=(float)Get(CPos,2)/1000.0;
float eye_z=(float)Get(CPos,3)/1000.0;

float at_x=(float)Get(CPos,4)/1000.0;
float at_y=(float)Get(CPos,5)/1000.0;
float at_z=(float)Get(CPos,6)/1000.0;

float angle=(float)Get(CPos,7)*3.14/180.0/10.0;


if (Get(CPos,8)==1)
{

//search cameras for interpolation - move to mainloop = call once per frame
	int i=0;
	while (Get(i,0)!=0&&(CmdDesc[Get(i,0)].FRoutine!=&MainLoop)) i+=CmdDesc[nGet(i)].FSize;//search loop
		int leftcam=0;int leftindex=0;
		int rightcam=32000;int rightindex=i;

	while (Get(i,0)!=0&&(CmdDesc[Get(i,0)].FRoutine!=&EndDraw)) 
	{
			
		if (CmdDesc[Get(i,0)].FRoutine==&Camera) 
		{
		
			int x=Get(i,9);

			if (x<=ptime)//left
			{
				if (x>=leftcam) {leftcam=x;leftindex=i;}//nearest left
			}

			if (x>ptime)//right
			{
				if (x<rightcam) {rightcam=x;rightindex=i;}//nearest right
			}
		}


		i+=CmdDesc[nGet(i)].FSize;
	}

//leftleft right right for cubicInterpolation	
	
		int leftleftcam=0;int leftleftindex=leftindex;
		int rightrightcam=32000;int rightrightindex=rightindex;


	i=0;
	while (Get(i,0)!=0&&(CmdDesc[Get(i,0)].FRoutine!=&MainLoop)) i+=CmdDesc[nGet(i)].FSize;//search loop

	while (Get(i,0)!=0&&(CmdDesc[Get(i,0)].FRoutine!=&EndDraw)) 
	{
			
		if (CmdDesc[Get(i,0)].FRoutine==&Camera) 
		{
		
			int x=Get(i,9);

			if ((leftcam-x)>0&&(leftleftcam<x)) 
			{
				leftleftcam=x;leftleftindex=i;//nearest left
			}			

			if ((x-rightcam)>0&&(x<rightrightcam))//right
			{
				rightrightcam=x;rightrightindex=i;//nearest right
			}
		}


		i+=CmdDesc[nGet(i)].FSize;
	}

//---

if (CPos!=leftindex) return;

//right
float eye_x1=(float)Get(rightindex,1)/1000.0;
float eye_y1=(float)Get(rightindex,2)/1000.0;
float eye_z1=(float)Get(rightindex,3)/1000.0;

float at_x1=(float)Get(rightindex,4)/1000.0;
float at_y1=(float)Get(rightindex,5)/1000.0;
float at_z1=(float)Get(rightindex,6)/1000.0;

float angle1=(float)Get(rightindex,7)*3.14/180.0/10.0;
//
//rigthright
float eye_x2=(float)Get(rightrightindex,1)/1000.0;
float eye_y2=(float)Get(rightrightindex,2)/1000.0;
float eye_z2=(float)Get(rightrightindex,3)/1000.0;

float at_x2=(float)Get(rightrightindex,4)/1000.0;
float at_y2=(float)Get(rightrightindex,5)/1000.0;
float at_z2=(float)Get(rightrightindex,6)/1000.0;

float angle2=(float)Get(rightrightindex,7)*3.14/180.0/10.0;
//
//leftleft
float eye_x0=(float)Get(leftleftindex,1)/1000.0;
float eye_y0=(float)Get(leftleftindex,2)/1000.0;
float eye_z0=(float)Get(leftleftindex,3)/1000.0;

float at_x0=(float)Get(leftleftindex,4)/1000.0;
float at_y0=(float)Get(leftleftindex,5)/1000.0;
float at_z0=(float)Get(leftleftindex,6)/1000.0;

float angle0=(float)Get(leftleftindex,7)*3.14/180.0/10.0;
//

float s=(ptime-Get(CPos,9))/(float)(Get(rightindex,9)-Get(CPos,9));

if (Get(leftindex,13)==1) 
{
	eye_x0=eye_x;eye_y0=eye_y;eye_z0=eye_z;
	at_x0=at_x;at_y0=at_y;at_z0=at_z;
	angle0=angle;
}

if (Get(rightindex,13)==1) 
{
	eye_x2=eye_x;eye_y2=eye_y;eye_z2=eye_z;
	at_x2=at_x;at_y2=at_y;at_z2=at_z;
	angle2=angle;

	eye_x1=eye_x;eye_y1=eye_y;eye_z1=eye_z;
	at_x1=at_x;at_y1=at_y;at_z1=at_z;
	angle1=angle;

}

eye_x=cubicInterpolateI(eye_x0,eye_x,eye_x1,eye_x2,s);
eye_y=cubicInterpolateI(eye_y0,eye_y,eye_y1,eye_y2,s);
eye_z=cubicInterpolateI(eye_z0,eye_z,eye_z1,eye_z2,s);

at_x=cubicInterpolateI(at_x0,at_x,at_x1,at_x2,s);
at_y=cubicInterpolateI(at_y0,at_y,at_y1,at_y2,s);
at_z=cubicInterpolateI(at_z0,at_z,at_z1,at_z2,s);

angle=cubicInterpolateI(angle0,angle,angle1,angle2,s);



}


//
D3DXMATRIX out;
D3DXVECTOR3 eye(eye_x,eye_y,eye_z);
D3DXVECTOR3 at(at_x,at_y,at_z);

D3DXVECTOR3 up_src(0,1,0);
D3DXVECTOR3 up;
D3DXMATRIX m_angle;
D3DXMatrixRotationZ(&m_angle,angle);
D3DXVec3TransformCoord(&up,&up_src,&m_angle);

D3DXMatrixLookAtLH(&out, &eye, &at, &up);
D3DXMATRIX tr;
D3DXMatrixTranslation(&tr,0,0,1);

  D3DMATRIX tr_ = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
	pDevice->SetTransform(D3DTS_WORLD,&tr_);


D3DXMatrixMultiply(&out,&out,&tr);

View=out;
SetView(0);
}

void CameraFromLight()
{
int ls=Get(CPos,1);

float eye_x=-SceneLight[ls].Direction.x;
float eye_y=-SceneLight[ls].Direction.y;
float eye_z=-SceneLight[ls].Direction.z+1;

float at_x=0;
float at_y=0;
float at_z=0;

float angle=0;


D3DXMATRIX out;
D3DXVECTOR3 eye(eye_x,eye_y,eye_z);
D3DXVECTOR3 at(at_x,at_y,at_z);

D3DXVECTOR3 up_src(0,1,0);
D3DXVECTOR3 up;
D3DXMATRIX m_angle;
D3DXMatrixRotationZ(&m_angle,angle);
D3DXVec3TransformCoord(&up,&up_src,&m_angle);

D3DXMatrixLookAtLH(&out, &eye, &at, &up);
D3DXMATRIX tr;
D3DXMatrixTranslation(&tr,0,0,1);


  D3DMATRIX tr_ = 
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1,
  };
  
	pDevice->SetTransform(D3DTS_WORLD,&tr_);


D3DXMatrixMultiply(&out,&out,&tr);

D3DXMATRIX w,r;
D3DXMatrixIdentity(&w);

D3DMATRIX cam;
ViewCopy=View;ViewCopyF=1;
View=out;
LightMatrix=out;

SetView(0);



}


void FreeCamera()
{
/*		View=View2;
		pDevice->SetTransform(D3DTS_VIEW,&View);
		pDevice->SetTransform(D3DTS_WORLD,&World);*/
	if (ViewCopyF==1) {
		//pDevice->SetTransform(D3DTS_WORLD,&World);
		
		View=ViewCopy;
	//	if (astate==-1) View=View2; else View2=View;
		
		if (camstate==-1) View=View2;else View2=View;
		SetView(0);
		ViewCopyF=0;
		}
	else
	{
		//pDevice->SetTransform(D3DTS_WORLD,&World);
		if (astate==-1) View=View2;
		SetView(0);	
	}
}


void SetPPrj()
{
int m=Get(CPos,1);
if (m==0) 
{
	float Vw = 1;
	float Vh = 1;//
	float Zn=1000;
	float Zf=-100;

	D3DMATRIX Proj = 
	{
		2/Vw/8, 0,		0,           0,
		0,		2/Vh/8,	0,           0,
		0,		0,		1/(Zn-Zf),   0,
		0,		0,		Zn/(Zn-Zf),  1
	};
	Projection=Proj;
	pDevice->SetTransform(D3DTS_PROJECTION, &Projection);
}
else
{	float Vw = 1;
	float Vh = 1;//
	Vh=screen_height/screen_width;
		float Zf=300*8;
		float Zn=0.5f;
		D3DMATRIX Projection2 = 
		{
			2*Zn/Vw, 0, 0, 0,
			0, 2*Zn/Vh, 0, 0,
			0, 0, Zf/(Zf-Zn*2), 1+cam_zoom,
			0, 0, -Zf/(Zf-Zn)*Zn/32, 0,//+cam_zoom,
		};
		Projection=Projection2;
		pDevice->SetTransform(D3DTS_PROJECTION, &Projection);
}

//pDevice->SetTransform(D3DTS_PROJECTION, &Proj);
}


//--sound

void LoadXM()
{
#ifndef USEMEMLOAD
FSOUND_File_SetCallbacks(fileopen, fileclose, fileread, fileseek, filetell);
#else
		FSOUND_File_SetCallbacks(memopen, memclose, memread, memseek, memtell);
#endif

char n[32];
memcpy(n,Pack+CPos+256-33,32);
if (Get(CPos,1)==0) mod = FMUSIC_LoadSong(n, NULL);
if (Get(CPos,1)==1) mod = FMUSIC_LoadSong(n, sampleloadcallback);

#ifdef EditMode
useWave=0;
#endif

if (!mod) MessageBox(hWnd0,"loadxm failed","_",0);
}

void ShowSample()
{
#ifdef EditMode
memcpy(snd_mem+44,snd_pool+44,snd_samplesize*2);
int tx,ty,tz;

	double x,y,z,w,h;int r,g,b;
	
		SetAlfa(0);
	int step;
	step=32;
	int cnt=0;
	for (int i=0;i<snd_samplesize;i+=step)
	{
		pVerts[cnt].x=i/10000.0/2.5-44100/10000.0/2.5/2.0;
		pVerts[cnt].y=(*(short*)(44+snd_mem+i*2))/100000.0;
		pVerts[cnt].z=0;
		pVerts[cnt].color=0x00ffffff;
		cnt++;
	}


	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	
	SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,NULL);

	NumVerts=cnt;

			void * pBuf;
		
			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
			pVB[0]->Unlock();
					
					
//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, NumVerts-1);

	//if (height!=width) SetView(0);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
	//pDevice->SetTransform(D3DTS_VIEW, &View);
#endif
}

float tri(float x)
{
    x = x / (2.0*PI);
    x = frac(x) ;
    if( x<0.0 ) x = 1.0+x;
    if(x>=1) x=2.0-x;
    return -1.0+2.0*x;
}

float saw(float x)
{
    x = x / (2.0*PI);
    x = frac(x)*2 ;
    if(x>1) x=2.0-x;
    return -1.0+2.0*x;
}

float sqr(float x)
{
	x = x / 2.0;
    return sign(sin(x));
}

float cellnoise(float x)
{
    int n = x;
    n = (n << 13) ^ n;
    n = (n * (n * n * 15731 + 789221) + 1376312589);
    n = (n>>14) & 65535;
    return n/65535.0;
}

short int mix(short int a,short int b,short int mixtype)
{
switch(mixtype)
{
case 0:return a;
case 1:return a+b;
case 2:return b-a;
case 3:return a*b/1000.0;
case 4:
	{
		if (a>b) return 32767; else return -32767;
	}
case 5:
	{
		if (abs(a)>abs(b)) return a; else return b;
	}

}
return 0;
}

class PinkNumber 
{ 
private: 
  int max_key; 
  int key; 
  unsigned int white_values[5]; 
  unsigned int range; 
public: 
  PinkNumber(unsigned int range = 65635) 
    { 
      max_key = 0x1f; // Five bits set 
      this->range = range; 
      key = 0; 
      for (int i = 0; i < 5; i++) 
 white_values[i] = rand() % (range/5); 
    } 
  int GetNextValue() 
    { 
      int last_key = key; 
      unsigned int sum;

      key++; 
      if (key > max_key) 
 key = 0; 
      // Exclusive-Or previous value with current value. This gives 
      // a list of bits that have changed. 
      int diff = last_key ^ key; 
      sum = 0; 
      for (int i = 0; i < 5; i++) 
 { 
   // If bit changed get new random number for corresponding 
   // white_value 
   if (diff & (1 << i)) 
     white_values[i] = rand() % (range/5); 
   sum += white_values[i]; 
 } 
      return sum; 
    } 
}; 

void PinkNoise() 
{ 
	int a=Get(CPos,1);
	PinkNumber pn;
	srand(0);
	for (int i=0;i<snd_samplesize;i++)
	{
		*(short*)(snd_pool+44+i*2)=(signed short)(pn.GetNextValue()-32768)*2*a/32768;
    } 
} 

void Reverse()
{
	memcpy(snd_tmp,snd_pool+44,snd_samplesize*2);

	for (int i=0;i<snd_samplesize;i++)
	{
	*(short*)(snd_pool+44+i*2)=*(short*)(snd_tmp+snd_samplesize*2-i*2-2);
	}
}

void oscx() 
{
//*karplus
	int sign=Get(CPos,3);
	srand(0);
  int sr = 44100;
   int f = Get(CPos,1);
   if (f==0) return;
   float feedback= Get(CPos,2)/100.0+.5;
   int N = sr / f;
   int c = 1;
   int T = snd_samplesize;
   float buf[44100];
   for (int i=N-1; i>=0; i--)
      buf[i] = rand() * (1/(float)RAND_MAX) - .5;
   //buf[i]=*(short*)(snd_pool+44+i*2)/32768.0;
   int bh = 0;
	int p=0;
   for (int i=T; i>0; i--) {
	   float avg;
      short v = buf[bh] * (1<<(8*sizeof v));
      *(short*)(snd_pool+44+p*2)=v;p++;
      int nbh = bh != N-1 ? bh+1 : 0;
      if (sign==0) avg =  feedback * ((buf[bh] - buf[nbh]));
	  if (sign==1) avg =  feedback * ((buf[bh] + buf[nbh]));
      buf[bh] = avg;
      bh = nbh;
   }
   
//



} 

void Oscillator()
{
float a;
int type=Get(CPos,1);
float amp=Get(CPos,2);
float freq=Get(CPos,3);
double c=freq*360.0/44100.0*PI/180.0;

int mixtype=Get(CPos,4);

switch (type)
{
case 0://sin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=amp*sin(i*c);
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 1://abssin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=-amp+2*amp*fabs(sin(i*c/2));
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 2://triangle
	for (int i=0;i<snd_samplesize;i++)
	{
		a=amp*tri(i*c);
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 3://saw
	for (int i=0;i<snd_samplesize;i++)
	{
		a=amp*saw(i*c);
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 4://sqr
	for (int i=0;i<snd_samplesize;i++)
	{
		a=amp*sqr(i*c);
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 5://noise
	for (int i=0;i<snd_samplesize;i++)
	{
		a=amp*cellnoise(i*c);
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
}

}

void PingPongSample()
{
	for (int i=0;i<snd_samplesize/2;i++)
	{
		*(short*)(snd_pool+44+snd_samplesize*2-2-i*2)=*(short*)(snd_pool+44+i*2);
	}
}

void SetSampleSize()
{
	snd_samplesize=Get(CPos,1)*44100/100.0;
}

void Oscillator2()
{
float a;
int type=Get(CPos,1);
float amp=Get(CPos,2);
float freq=Get(CPos,3);
double c=freq*360.0/44100.0*PI/180.0;
float b;float oe=Get(CPos,4)/255.0;
int mixtype=Get(CPos,5);
switch (type)
{
case 0://sin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*sin(i*c*2)+.5*amp*sin(i*c*4)+.3*amp*sin(i*c*5)+.2*amp*sin(i*c*8)+.1*amp*sin(i*c*10)+.05*amp*sin(i*c*12);
		b=.7*amp*sin(i*c*3)+.5*amp*sin(i*c*5)+.3*amp*sin(i*c*7)+.2*amp*sin(i*c*9)+.1*amp*sin(i*c*11)+.05*amp*sin(i*c*13);
		a=(lerp(a,b,oe)+amp*sin(i*c))/2.95;
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 1://abssin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*fabs(sin(i*c*2))+.5*amp*fabs(sin(i*c*4))+.3*amp*fabs(sin(i*c*5))+.2*amp*fabs(sin(i*c*8))+.1*amp*fabs(sin(i*c*10))+.05*amp*fabs(sin(i*c*12));
		b=.7*amp*fabs(sin(i*c*3))+.5*amp*fabs(sin(i*c*5))+.3*amp*fabs(sin(i*c*7))+.2*amp*fabs(sin(i*c*9))+.1*amp*fabs(sin(i*c*11))+.05*amp*fabs(sin(i*c*13));
		a=(lerp(a,b,oe))+amp*fabs(sin(i*c))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 2://triangle
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*tri(i*c*2)+.5*amp*tri(i*c*4)+.3*amp*tri(i*c*5)+.2*amp*tri(i*c*8)+.1*amp*tri(i*c*10)+.05*amp*tri(i*c*12);
		b=.7*amp*tri(i*c*3)+.5*amp*tri(i*c*5)+.3*amp*tri(i*c*7)+.2*amp*tri(i*c*9)+.1*amp*tri(i*c*11)+.05*amp*tri(i*c*13);
		a=(lerp(a,b,oe)+amp*tri(i*c))/2.95;
		*(short*)(snd_samplesize+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 3://saw
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*saw(i*c*2)+.5*amp*saw(i*c*4)+.3*amp*saw(i*c*5)+.2*amp*saw(i*c*8)+.1*amp*saw(i*c*10)+.05*amp*saw(i*c*12);
		b=.7*amp*saw(i*c*3)+.5*amp*saw(i*c*5)+.3*amp*saw(i*c*7)+.2*amp*saw(i*c*9)+.1*amp*saw(i*c*11)+.05*amp*saw(i*c*13);
		a=(lerp(a,b,oe)+amp*saw(i*c))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 4://sqr
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*sqr(i*c*2)+.5*amp*sqr(i*c*4)+.3*amp*sqr(i*c*5)+.2*amp*sqr(i*c*8)+.1*amp*sqr(i*c*10)+.05*amp*sqr(i*c*12);
		b=.7*amp*sqr(i*c*3)+.5*amp*sqr(i*c*5)+.3*amp*sqr(i*c*7)+.2*amp*sqr(i*c*9)+.1*amp*sqr(i*c*11)+.05*amp*sqr(i*c*13);
		a=(lerp(a,b,oe)+amp*sqr(i*c))/2.95;
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 5://noise
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*cellnoise(i*c*2)+.5*amp*cellnoise(i*c*4)+.3*amp*cellnoise(i*c*5)+.2*amp*cellnoise(i*c*8)+.1*amp*cellnoise(i*c*10)+.05*amp*cellnoise(i*c*12);
		b=.7*amp*cellnoise(i*c*3)+.5*amp*cellnoise(i*c*5)+.3*amp*cellnoise(i*c*7)+.2*amp*cellnoise(i*c*9)+.1*amp*cellnoise(i*c*11)+.05*amp*cellnoise(i*c*13);
		a=(lerp(a,b,oe)+amp*cellnoise(i*c))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
}

}

void OutputSampleTo()
{
int slot=Get(CPos,1);
memcpy(snd_xm+slot*snd_maxsamplesize*2,snd_pool+44,snd_samplesize*2);

}

void Oscillator3()
{
float a;
int type=Get(CPos,1);
float amp=Get(CPos,2);
float freq=Get(CPos,3);
double c=freq*360.0/44100.0*PI/180.0;
float b;float oe=Get(CPos,4)/255.0;
float dt=Get(CPos,5)/1000.0;
int mixtype=Get(CPos,6);
switch (type)
{
case 0://sin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*sin(i*c*(2+dt))+.5*amp*sin(i*c*(4-dt))+.3*amp*sin(i*c*(5+dt))+.2*amp*sin(i*c*(8-dt))+.1*amp*sin(i*c*(10+dt))+.05*amp*sin(i*c*(12-dt));
		b=.7*amp*sin(i*c*(3+dt))+.5*amp*sin(i*c*(5-dt))+.3*amp*sin(i*c*(7+dt))+.2*amp*sin(i*c*(9-dt))+.1*amp*sin(i*c*(11+dt))+.05*amp*sin(i*c*(13-dt));
		a=(lerp(a,b,oe)+amp*sin(i*c))/2.95;
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 1://abssin
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*fabs(sin(i*c*(2+dt)))+.5*amp*fabs(sin(i*c*(4-dt)))+.3*amp*fabs(sin(i*c*(5+dt)))+.2*amp*fabs(sin(i*c*(8-dt)))+.1*amp*fabs(sin(i*c*(10+dt)))+.05*amp*fabs(sin(i*c*(12-dt)));
		b=.7*amp*fabs(sin(i*c*(3+dt)))+.5*amp*fabs(sin(i*c*(5-dt)))+.3*amp*fabs(sin(i*c*(7+dt)))+.2*amp*fabs(sin(i*c*(9-dt)))+.1*amp*fabs(sin(i*c*(11+dt)))+.05*amp*fabs(sin(i*c*(13-dt)));
		a=(lerp(a,b,oe)+amp*fabs(sin(i*c)))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 2://triangle
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*tri(i*c*(2+dt))+.5*amp*tri(i*c*(4-dt))+.3*amp*tri(i*c*(5+dt))+.2*amp*tri(i*c*(8-dt))+.1*amp*tri(i*c*(10+dt))+.05*amp*tri(i*c*(12-dt));
		b=.7*amp*tri(i*c*(3+dt))+.5*amp*tri(i*c*(5-dt))+.3*amp*tri(i*c*(7+dt))+.2*amp*tri(i*c*(9-dt))+.1*amp*tri(i*c*(11+dt))+.05*amp*tri(i*c*(13-dt));
		a=(lerp(a,b,oe)+amp*tri(i*c))/2.95;
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
case 3://saw
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*saw(i*c*(2+dt))+.5*amp*saw(i*c*(4-dt))+.3*amp*saw(i*c*(5+dt))+.2*amp*saw(i*c*(8-dt))+.1*amp*saw(i*c*(10+dt))+.05*amp*saw(i*c*(12-dt));
		b=.7*amp*saw(i*c*(3+dt))+.5*amp*saw(i*c*(5-dt))+.3*amp*saw(i*c*(7+dt))+.2*amp*saw(i*c*(9-dt))+.1*amp*saw(i*c*(11+dt))+.05*amp*saw(i*c*(13-dt));
		a=(lerp(a,b,oe)+amp*saw(i*c))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 4://sqr
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*sqr(i*c*(2+dt))+.5*amp*sqr(i*c*(4-dt))+.3*amp*sqr(i*c*(5+dt))+.2*amp*sqr(i*c*(8-dt))+.1*amp*sqr(i*c*(10+dt))+.05*amp*sqr(i*c*(12-dt));
		b=.7*amp*sqr(i*c*(3+dt))+.5*amp*sqr(i*c*(5-dt))+.3*amp*sqr(i*c*(7+dt))+.2*amp*sqr(i*c*(9-dt))+.1*amp*sqr(i*c*(11+dt))+.05*amp*sqr(i*c*(13-dt));
		a=(lerp(a,b,oe)+amp*sqr(i*c))/2.95;
		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;

case 5://noise
	for (int i=0;i<snd_samplesize;i++)
	{
		a=.7*amp*cellnoise(i*c*(2+dt))+.5*amp*cellnoise(i*c*(4-dt))+.3*amp*cellnoise(i*c*(5+dt))+.2*amp*cellnoise(i*c*(8-dt))+.1*amp*cellnoise(i*c*(10+dt))+.05*amp*cellnoise(i*c*(12-dt));
		b=.7*amp*cellnoise(i*c*(3+dt))+.5*amp*cellnoise(i*c*(5-dt))+.3*amp*cellnoise(i*c*(7+dt))+.2*amp*cellnoise(i*c*(9-dt))+.1*amp*cellnoise(i*c*(11+dt))+.05*amp*cellnoise(i*c*(13-dt));
		a=(lerp(a,b,oe)+amp*cellnoise(i*c))/2.95;

		*(short*)(snd_pool+44+i*2)=mix((short)a,*(short*)(snd_pool+44+i*2),mixtype);
	}
	break;
}

}

void Envelope()
{
int sp=Get(CPos,1);

		float y=0;float x;float a;
		for (int t=0;t<snd_samplesize;t++)
		{
		a=*(short*)(snd_pool+44+t*2);
		//search interval
			x=t/10000.0/5.0;
			x=x-44100/10000.0/2.5/2.0;
			for (int k=0;k<1024*10-1;k++)
			{
				if (x>curvearray_x[sp][curvearray_clen[sp]-2]) {y=curvearray_x[sp][curvearray_clen[sp]-2];break;}
				//if (x<0) {y=curvearray_x[sp][0];break;}

			if (x>curvearray_x[sp][k]&&x<=curvearray_x[sp][k+1]) 
				{
				y=lerp(curvearray_y[sp][k+1],curvearray_y[sp][k],(x-curvearray_x[sp][k])/(curvearray_x[sp][k+1]-curvearray_x[sp][k]));
				break;
				}	

			}
		a=a*y*3;
		*(short*)(snd_pool+44+t*2)=(short)a;
		}

}

void MixSample()
{
BYTE* m1,*m2;
short in1,in2;float c1,c2;
m1=snd_bank+snd_maxsamplesize*2*Get(CPos,1);
m2=snd_bank+snd_maxsamplesize*2*Get(CPos,2);
int ofs=Get(CPos,6)*2;
if (ofs<0) ofs=0;
c1=Get(CPos,4)/255.0;
c2=Get(CPos,5)/255.0;
float out;
switch (Get(CPos,3))
	{
	case 0:
		for (int i=0;i<snd_samplesize*2-ofs;i+=2)
		{
		in1=*(short*)(m1+i);
		in2=*(short*)(m2+i+ofs);
		out=c1*in1+c2*in2;
		if (out>32767) out=32767;
		if (out<-32767) out=-32767;
		*(short*)(snd_pool+44+i)=out;
		}
		break;
	case 1:
		for (int i=0;i<snd_samplesize*2-ofs;i+=2)
		{
		in1=*(short*)(m1+i);
		in2=*(short*)(m2+i+ofs);
		out=c1*in1-c2*in2;
		if (out>32767) out=32767;
		if (out<-32767) out=-32767;
		*(short*)(snd_pool+44+i)=out;
		}
		break;
	case 2:
		for (int i=0;i<snd_samplesize*2-ofs;i+=2)
		{
		in1=*(short*)(m1+i);
		in2=*(short*)(m2+i+ofs);
		out=c1*in1*c2*in2/255.0;
		if (out>32767) out=32767;
		if (out<-32767) out=-32767;
		*(short*)(snd_pool+44+i)=out;
		}
		break;
	}
}

void Resample()
{
int speed=Get(CPos,1)*10+Get(CPos,2);
double a;int sct;
double o1;
memcpy(snd_tmp,snd_pool,44+snd_samplesize*2);
int mixtype=Get(CPos,3);

	for (sct=0;sct<snd_samplesize;sct++) 
	{
	o1=sct/44100.0*speed;//?

	if (o1<snd_samplesize) 
		{
		a=*(short*)(snd_tmp+(int)o1*2);
		}
	else 
		{
		a=0;
		}
	*(short*)(snd_pool+sct*2)=mix((short)a,*(short*)(snd_pool+44+sct*2),mixtype);
	}
}

void RollSample()
{
short int a;int j;
int ofs=Get(CPos,1)*2;int b=Get(CPos,2);
memcpy(snd_tmp,snd_pool,44+snd_samplesize*2);
int s=Get(CPos,4);

if (Get(CPos,3)==0)
{
		for (int i=0;i<snd_samplesize;i+=1)
		{
		j=i+ofs;
		if (j<0||j>snd_samplesize) a=0;
		else
		a=*(short*)(snd_tmp+44+j*2);
		if (s==0) *(short*)(snd_pool+44+i*2)=a+b; else *(short*)(snd_pool+44+i*2)=(short)min(abs(a+b),32767)*sign(a+b);
		}
}
else
{
		for (int i=0;i<snd_samplesize;i+=1)
		{
		j=i+ofs;
		if (j<0) j+=snd_samplesize;
		if (j>snd_samplesize) j-=snd_samplesize;
		a=*(short*)(snd_tmp+44+j*2);
		if (s==0) *(short*)(snd_pool+44+i*2)=a+b; else *(short*)(snd_pool+44+i*2)=(short)min(abs(a+b),32767)*sign(a+b);
		}
}


}


void HP_Filter(signed short* inWave, signed short* outWave, int len, double freq)
// freq = cutoff frequency = 0..22050
{
int i,j;
 double *in, *out, *temp;
 in = new double[len];
 out = new double[len];
 temp = new double[257];

 for (i=0; i<len; i++)
 {
  in[i] = inWave[i];
 }

 for (i=0; i<257; i++)
 {
  if(i!=129)
  temp[i] = - (1.0/(PI*(i-129))) * sin(PI*(i-129)*freq/22050);
 }
 temp[129] = 1.0 - freq/22050;

 for (i=0; i<len; i++)
 {
  out[i] = 0;
  for (j=-128; j<129; j++)
   if ((i+j >= 0)&&(i+j < len)) out[i] += in[i+j]*temp[j+128];
 }

 for (i=0; i<len; i++)
 {
  if (out[i] < -32767) out[i] = -32767; 
  if (out[i] > 32767)  out[i] =  32767;
  outWave[i] = out[i];
 }

 delete [] in;
 delete [] out;
 delete [] temp;
}

void LP_Filter(signed short* inWave, signed short* outWave, int len, double cutoff, double resonance)
// cutoff - 0 ... 127
// resonance - 0 ... 127
// filter posted on musicdsp.org by madbrain@videotron.ca

{
	double *in, *out, v0, v1;
	v0=0;v1=0;
	in = new double[len];
	out = new double[len];

	for (int i=0; i<len; i++)
	{
		in[i] = inWave[i];
	}

	double c = pow(0.5, (128-cutoff)   / 16.0);
	double r = pow(0.5, (resonance+24) / 16.0);

	for (int i=0; i<len; i++)
	{
		v0 =  (1-r*c)*v0  -  (c)*v1  + (c)*in[i];
		v1 =  (1-r*c)*v1  +  (c)*v0;
		out[i] = v1;
		if (out[i] < -32767) out[i] = -32767; 
		if (out[i] > 32767)  out[i] =  32767;
		outWave[i] = out[i];
	}

	delete [] in;
	delete [] out;
}

void LP_Filter2(signed short* inWave, signed short* outWave, int len, double cutoff, double resonance,double cutoffSpd,double cutoffAmp,double rcSpd,double rcAmp,double Fz)
// cutoff - 0 ... 127
// resonance - 0 ... 127
// filter posted on musicdsp.org by madbrain@videotron.ca
{
	double *in, *out, v0, v1;
	in = new double[len];
	out = new double[len];
	v0=0;v1=0;

	for (int i=0; i<len; i++)
	{
		in[i] = inWave[i];
	}

	double c;
	double r;
	double rs,cs,F;
	F=((double)Fz)/255.0;

	for (int i=0; i<len; i++)
	{
		rs=(rcAmp*sin(PI*rcSpd/32.0*((double)i/(double)len)+F))/2.0;
		cs=(cutoffAmp*sin(PI*cutoffSpd/32.0*((double)i/(double)len)+F))/2.0;

		c = pow(0.5, (128-cutoff+cs)   / 16.0);
		r = pow(0.5, (resonance+rs+24) / 16.0);

		v0 =  (1-r*c)*v0  -  (c)*v1  + (c)*in[i];
		v1 =  (1-r*c)*v1  +  (c)*v0;
		out[i] = v1;
		if (out[i] < -32767) out[i] = -32767; 
		if (out[i] > 32767)  out[i] =  32767;
		outWave[i] = out[i];
	}

	delete [] in;
	delete [] out;
}

void Resonator(signed short* inWave, signed short* outWave, int len, double freq, double q, double decay)
// freq - frequency of resonance = 0 .. 22050
// q - resonance factor = 0.0 .. 1.0
// decay - decay of frequency = 0.0 .. 1.0
{
 double out, prev, pprev;
 double freq_real;

 outWave[0] = pprev = inWave[0];
 outWave[1] = prev  = 2*q*cos(PI*freq/22050)*inWave[0] + inWave[1];

 for (int i=2; i<len; i++)
 { 
  freq_real = freq*(decay*(1.0 - double(i)/double(len)) + 1.0 - decay);
  out = 2*q*cos(PI*freq_real/22050)*prev - q*q*pprev + inWave[i];
  if (out < -32767) out = -32767; 
  if (out > 32767)  out =  32767;
  outWave[i] = out;
  prev = out;
  pprev = prev;
 }
}

void Slew_Compressor(signed short* inWave, signed short* outWave, int len, double c, double lim)
// c - compress factor = 0.0 .. 1.0
// lim - limitation of slew = 0.0 .. 1.0
{
 double prev, temp, out;
 double diff;

 lim = lim*32768;
 prev = inWave[0];
 outWave[0] = prev;

 for (int i=1; i<len; i++)
 { 
  diff = inWave[i] - prev;
  if (diff > lim) diff = lim;
  if (diff < -lim) diff = -lim;
  out = prev + (1.0-c)*diff + c*diff*diff*diff/(32768*32768);
  if (out < -32767) out = -32767; 
  if (out > 32767)  out =  32767;
  outWave[i] = out;
  prev = out;
 }
}

void Distorter(signed short* inWave, signed short* outWave, int len, double c, double h, double cx)
// c - distort factor (center point) = 0.0 .. 1.0
// h - distort factor (high point)= 0.0 .. 1.0
// cx - position of center point = 0.0 .. 1.0
{
 double out;
 double t;
 
 if (cx<=0) cx = 0.001;

 for (int i=0; i<len; i++)
 {
  t = abs(inWave[i]);
  t /= 32768;

  if (t < cx) t = (1.0/cx) * t * c;
  else t = c + (1.0/(1.0-cx))*(t - cx)*(h-c);

  if (inWave[i]<0) t *= -1;
  out = t*32768;
  if (out < -32767) out = -32767; 
  if (out > 32767)  out =  32767;
  outWave[i] = out;
 }
}

void Normalization(signed short* inWave, signed short* outWave, int len)
// waveform normalizing
{
	double max;
	max = 0;
	int i;
	for (i=0; i<len; i++)
	{
		if (inWave[i]>max) max = inWave[i];
		if (inWave[i]<-max) max = -inWave[i];
	}

	for (i=0; i<len; i++)
	{
		outWave[i] = (32765.0/max)*inWave[i];
	}
}

float foldback(float in, float threshold)
{
  if (in>threshold || in<-threshold)
  {
    in= fabs(fabs(fmod(in - threshold, threshold*4)) - threshold*2) - threshold;
  }
  return in;
}

void Reverb2()
{
float n=Get(CPos,1);
float d=Get(CPos,2)/255.0;
float c=Get(CPos,3);
float inter=Get(CPos,4);
float inter_r=Get(CPos,5)/255.0;

if (n<0) return;

//int delayMilliseconds = n; 
int delaySamples = n;//(int)((float)delay%Milliseconds * 44.1f);
float decay = d;

for (int r = 0; r < c; r++)
{
for (int i = 0; i < snd_samplesize - delaySamples; i++)
{
	float p= i+delaySamples+sin((float)r/(float)c*22)*delaySamples/2+sin((float)i/(float)(snd_samplesize - delaySamples)*inter_r)*inter;
	float decay2 = decay/2+decay*i/(float)(snd_samplesize - delaySamples)/2;
	int j=((int)p)*2;
    *(short*)(snd_pool+44+i*2+delaySamples*2) = clamp((short)((float)(*(short*)(snd_pool+44+j)) * decay2)+*(short*)(snd_pool+44+i*2+delaySamples*2),-32767,32767);

}
delaySamples++;
}

	

}

void FBDistort()
{
float n=(255-Get(CPos,1))*32767/255.0;
float g=1+(Get(CPos,1))/255.0;
int a;

	for (int sct=0;sct<snd_samplesize;sct++) 
	{
	a=*(short*)(snd_pool+44+sct*2);
	*(short*)(snd_pool+44+sct*2)=foldback(a,n)*g;
	}
}

void LowCut()
{
HP_Filter((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1));
}

void HiCut()
{
LP_Filter((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2));
}


void HiCut2()
{
LP_Filter2((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2),Get(CPos,3),Get(CPos,4),Get(CPos,5),Get(CPos,6),Get(CPos,7));
}

void Res()
{
Resonator((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2)/255.0,Get(CPos,3)/255.0);
}

void Compressor()
{
Slew_Compressor((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1)/1000.0,Get(CPos,2)/1000.0);
}

void Distortion()
{
Distorter((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1)/255.0,Get(CPos,2)/255.0,Get(CPos,3)/255.0);
}

void Normalize()
{
Normalization((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize);
}

void Crossfader()
{
float a,b,c,d;
int len=Get(CPos,1);
for (int i=0;i<len;i+=2)
{
a=*(short*)(snd_pool+44+i);
b=*(short*)(snd_pool+snd_samplesize*2-2+44-i);

c=lerp(a,b,.5+(i/(float)len)/2.0);
d=lerp(a,b,.5-(i/(float)len)/2.0);

*(short*)(snd_pool+44+i)=(short)c;
*(short*)(snd_pool+88200-2+44-i)=(short)d;
}

}

//sting

float FdM[1024];//'сила натяжения, делённая на массу
float P[1024];//'позиция
float S[1024];//'скорость

int stLen;
float k1,k2;
bool EndSound;
int NN,NK;

float StTick() 
{
  int i;
  float d;

  if (EndSound ) return 0;//Then Exit Function

  P[0] = -P[1]; S[0] = -S[1];
  P[stLen] = -P[stLen - 1]; S[stLen] = -S[stLen - 1];
  //'расчёт скоростей

  for (i = 1; i< (stLen - 1);i++)
  {
    d = (P[i - 1] + P[i + 1]) * 0.5 - P[i];
    S[i] = S[i] + d * FdM[i];
  }
  //'вязкость
  for (i = 1 ;i< (stLen - 1);i++)
  {
    S[i] = S[i] * k1 + (S[i - 1] + S[i + 1]) * k2;
  }
  //'расчёт позиций
  for (i = 1 ; i<(stLen - 1);i++)
  {
	  P[i] = P[i] + S[i];
  }
  //'отбрасываем ненормализованные расчёты
  if ((abs(P[1]) < 1E-18) && (abs(P[2]) < 1E-18) && (abs(P[3]) < 1E-18)) EndSound = true;

  return (P[NN] * (1 - NK) + P[NN + 1] * NK);
}

void StStart(int sLen , float Frc , float kDemp , float kRand , float kHard )
{
  int i;
  float m;

  stLen = sLen;
  
  k1 = 1 - kDemp * 0.5;
  k2 = kDemp * 0.25;
  EndSound = false;

  srand(0);

  NK = (stLen * 0.1) * (1 - kHard) + 1;
  NN = (int)NK;
  NK = NK - NN;

  for (i = 1 ;i < stLen - 1;  i++)
  {
    m = 1 + kRand * (rand() - 0.5);
    FdM[i] = Frc / m;
  }
  
  for (i = 1 ;i< stLen / 4;i++)
  {
    S[i] = 1;
  }
}


void String_snd()
{
float len, freq, demp,randA,hard;
len=Get(CPos,1);
freq=Get(CPos,2)/100.0;
demp=Get(CPos,3)/255.0;
randA=Get(CPos,4)/10000000.0;
hard=Get(CPos,5)/255.0;
float amp=Get(CPos,6);

if (len<0||len>512) return;

for (int i=0;i<len;i++)
{
FdM[i]=0;P[i]=0;S[i]=0;
}

StStart(len,freq,demp,randA,hard);

float a;

for (int i=0;i<snd_samplesize;i++)
{
a=StTick()*amp;
a=clamp(a,-32767,32767);
*(short*)(snd_pool+44+i*2)=(short)a;
}


}


void StoreSample()
{
memcpy(snd_bank+snd_maxsamplesize*2*Get(CPos,1),snd_pool+44,snd_samplesize*2);
}

void mam_Reverb(signed short* inWave, signed short* outWave, int len, int size, double decay, double dry, double filtration)
// size - 0 ... 255 - size of reverb in 10ms, 1 = 10ms
// decay - 0 ... 1 - decay of reverb
// dry - 0 ... 1 - dry/wet, 0 = pure reverb
// filtration - 0 ... 1 - filtration value, 0 = highpass, 0.5 = no filter, 1 = lowpass
{
	double *in, *out;
	in = new double[len];
	out = new double[len];
	int i;
	for (i=0; i<len; i++)
	{
		out[i] = in[i] = inWave[i];
	}

	for (i=size*192; i<len; i++)
	{
		if (i>size*441) out[i] += -0.1*decay*((1.0 - abs(filtration - 0.5))*out[i - size*441] + (filtration - 0.5) * out[i - size*441 + 1]);
		if (i>size*377) out[i] += 0.2*decay*((1.0 - abs(filtration - 0.5))*out[i - size*377] + (filtration - 0.5) * out[i - size*377 + 1]);
		if (i>size*230) out[i] += -0.3*decay*((1.0 - abs(filtration - 0.5))*out[i - size*230] + (filtration - 0.5) * out[i - size*230 + 1]);
		out[i] += 0.4*decay*((1.0 - abs(filtration - 0.5))*out[i - size*192] + (filtration - 0.5) * out[i - size*192 + 1]);
	}

	for (i=0; i<len; i++)
	{
		out[i] = dry * in[i] + (1.0-dry) * out[i];
		if (out[i] < -32767) out[i] = -32767; 
		if (out[i] > 32767)  out[i] =  32767;
		outWave[i] = out[i];
	}

	delete [] in;
	delete [] out;
}

void mam_Chorus(signed short* inWave, signed short* outWave, int len, int voices, int max_delay, int speed, int feed, int amp)
// voices    0 .. 20 - number of voices, 0 = original
// max_delay 1 .. 255 - maximum delay in ms
// speed	 0 .. 255 - speed of chorus
// feed		 0 .. 255 - feedback
// amp		 0 .. 255 - final amplitude
{
	
	double *in, *out, delay, left_sample, right_sample, dfeed;
	in = new double[len];
	out = new double[len];
	dfeed = double(feed)/255.0;
	int i;
	for (i=0; i<len; i++)
	{
		out[i] = in[i] = inWave[i];
		out[i] *= 1.0/voices;
	}

	for (i=0; i<len; i++)
	{	
		for (int j=0; j<voices; j++)
		{	
			delay = 44.1 * max_delay * sin(0.0000001*double(i*speed) + 2.0*PI*j/double(voices));
			left_sample		= (1.0 - dfeed)*in[int(clamp(i+delay,0,len))]	+ dfeed*out[int(clamp(i+delay,0,len))];
			right_sample	= (1.0 - dfeed)*in[int(clamp(i+delay+1,0,len))]	+ dfeed*out[int(clamp(i+delay+1,0,len))];
			if ((i+delay > 0) && (i+delay < len))
				out[i] += ((1 - delay + int(delay))*in[int(clamp(i+delay,0,len))] + (delay - int(delay))*in[int(clamp(i+delay+1,0,len))])/voices;
		}
	}

	for (i=0; i<len; i++)
	{
		out[i] *= double(amp)/128.0;
		if (out[i] < -32767) out[i] = -32767; 
		if (out[i] > 32767)  out[i] =  32767;
		outWave[i] = out[i];
	}

	delete [] in;
	delete [] out;
}

#define EBUFF_SIZE  1024  
float LO_FRQ;     
float HI_FRQ;     

int e_buff[EBUFF_SIZE];
int e_head;                   /* голова кольцевого буфеpа */

long hi_acc;                  /* накопители сpеднего значения */
long lo_acc;                  /* для фвч и фнч */

int filter(int c)         /* c - амплитуда сигнала в текущий момент вpемени. */
{                             /* функция будет возвpащать новую амплитуду для записи */
                              /* в выходной поток */

    int lo_tale;              /* Хвост для фнч */
    int hi_tale;              /* Хвост ждя фвч */

    if(--e_head < 0) e_head = EBUFF_SIZE-1;    /* заносим в буфеp новое*/
    e_buff[e_head] = c;                               /* значение */

    /* ФHЧ */
    lo_tale = e_head + LO_FRQ;     /* опpеделяем последнее значение окна */
    if(lo_tale >= EBUFF_SIZE)
        lo_tale -= EBUFF_SIZE;

    lo_acc -= e_buff[lo_tale];     /* поддеpживаем сумму всех значений окна в*/
    lo_acc += c;                   /* аккумулятоpе. для каждого нового значения*/
                                   /* окно смещается */
    /* ФВЧ */
    hi_tale = e_head + HI_FRQ;     /* опpеделяем последнее значение окна */
    if(hi_tale >= EBUFF_SIZE)
        hi_tale -= EBUFF_SIZE;

    hi_acc -= e_buff[hi_tale];     /* поддеpживаем сумму всех значений окна в*/
    hi_acc += c;                   /* аккумулятоpе. для каждого нового значения*/
                                   /* окно смещается */

    /* для получения полосового фильтpа вычитаем из значения фнч значение фвч*/

    return lo_acc / (LO_FRQ+1) - hi_acc / (HI_FRQ+1);
}



void pEQ()
{

	for (int i=0;i<EBUFF_SIZE;i++)
	{
		e_buff[i]=0;
	}
	hi_acc=0;
	lo_acc=0;
	e_head=EBUFF_SIZE-1;



float gain=Get(CPos,3)/64.0;

float freq=Get(CPos,1);
float lofreq=freq-Get(CPos,2);
float hifreq=freq+Get(CPos,2);

/*if (gain<0)
{
freq=lofreq;
lofreq=hifreq;
hifreq=freq;

gain*=-1;
}*/

lofreq=clamp(lofreq,50,22050);
hifreq=clamp(hifreq,50,22050);

		LO_FRQ=44100/lofreq;
		HI_FRQ=44100/hifreq;


	for (int sct=0;sct<snd_samplesize;sct++) 
	{
		short a,b;
		a=*(short*)(snd_pool+44+sct*2);
		b=filter(a);
		//*(short*)(snd_pool+44+sct*2)=(short)(lerp(b,a,gain));
		*(short*)(snd_pool+44+sct*2)=(short)clamp(a+((float)b)*gain,-32768,32768);
	}


}

void IvanEQ(signed short* inWave, signed short* outWave, int len, int band1, int band2, int band3, int band4, int band5, int band6)
// dedicated to Ivan 'Preston' Sidoruk :)
// value 200 = 0dB (no changes in band)
//       255 = +5dB
//		   0 = -40dB
// band1 = 0..255 - 0Hz-800Hz
// band2 = 0..255 - 800Hz-1600Hz
// band3 = 0..255 - 1600Hz-3200Hz
// band4 = 0..255 - 3200Hz-6500Hz
// band5 = 0..255 - 6500Hz-11000Hz
// band6 = 0..255 - 11000Hz-22050Hz
{
	double *in, *out, *temp, d[6];
	double diff, coef;
	in = new double[len];
	out = new double[len];
	temp = new double[257];
	int i,j;
	for (i=0;i<257;i++) temp[i]=0;
	
	double f1[5] = {600.0,  1400.0, 3000.0, 6300.0, 10800.0};
	double f2[5] = {1000.0, 1800.0, 3400.0, 6700.0, 11200.0};

	d[0] = pow(100.0, (1.0/200.0)*(band1-200))-0.01;
	d[1] = pow(100.0, (1.0/200.0)*(band2-200))-0.01;
	d[2] = pow(100.0, (1.0/200.0)*(band3-200))-0.01;
	d[3] = pow(100.0, (1.0/200.0)*(band4-200))-0.01;
	d[4] = pow(100.0, (1.0/200.0)*(band5-200))-0.01;
	d[5] = pow(100.0, (1.0/200.0)*(band6-200))-0.01;

	for (i=0; i<len; i++)
	{
		in[i] = inWave[i];
	}
	
	temp[128] = d[5];
	for (j=4; j>=0; j--)
	{
		diff = (d[j] - d[j+1])/PI;
		f2[j] *= PI/22050.0;
		f1[j] *= PI/22050.0;
		temp[128] += diff*0.5*(f2[j]+f1[j]);
		for (i=1; i<129; i++)
		{
			coef = PI/(f2[j]-f1[j]);
			coef = 1.0/(2.0*i) + 0.25*(1.0/(coef-i) - 1.0/(coef+i));
			coef *= sin(f2[j]*i) + sin(f1[j]*i);
			temp[128-i] += diff*coef;
			temp[128+i] += diff*coef;
		}
	}

	for (i=0; i<len; i++)
	{
		out[i] = 0;
		for (j=-128; j<129; j++)
			if ((i+j >= 0)&&(i+j < len)) out[i] += in[i+j]*temp[j+128];
	}

	for (i=0; i<len; i++)
	{
		if (out[i] < -32767) out[i] = -32767; 
		if (out[i] > 32767)  out[i] =  32767;
		outWave[i] = out[i];
	}

	delete [] in;
	delete [] out;
	delete [] temp;
}

void Reverb()
{
mam_Reverb((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2)/255.0,Get(CPos,3)/255.0,Get(CPos,4)/255.0);
}

void Chorus()
{
mam_Chorus((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2),Get(CPos,3),Get(CPos,4),Get(CPos,5));
}




void EQ()
{
IvanEQ((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1),Get(CPos,2),Get(CPos,3),Get(CPos,4),Get(CPos,5),Get(CPos,6));
}

void EQ2()
{
IvanEQ((short*)snd_pool+44,(short*)snd_pool+44,snd_samplesize,Get(CPos,1)+200,Get(CPos,2)+200,Get(CPos,3)+200,Get(CPos,4)+200,Get(CPos,5)+200,Get(CPos,6)+200);
}


void LoadGrain()
{
	
	char t[100];
		strcpy(t,(char*)(Pack+CPos*CellSize+256-33));

		FILE *fp;
		fp = fopen(t, "rb");
		if (fp!=NULL)
		{
			fread(snd_tmp,1,snd_samplesize,fp);
			fclose(fp);

			int smp_type=*(short*)(snd_tmp+34);
			int smp_len=*(int*)(snd_tmp+40);

			for (int i=0;i<snd_samplesize;i++)
				{
				*(short*)(snd_pool+44+i*2)=0;
				}

			if (smp_type==8)
			{
			int a;
			for (int i=0;i<smp_len;i++)
				{
				a=*(BYTE*)(snd_tmp+44+i);
				*(short*)(snd_pool+44+i*2)=(short)((a-127)*255);
				}
				smp_len*=2;
			}
			else
			{
			memcpy(snd_pool+44,snd_tmp+44,smp_len);
			}


			if (Get(CPos,1)==1)
			{
				int rc=snd_samplesize/(smp_len/2)+1;
				for(int t=1;t<rc;t++)
				{
				memcpy(snd_pool+44+smp_len*t,snd_pool+44,smp_len);
				}
			}
		}
}

void EndSequence()
{
int b=9;
}

void Sequence()
{
	trk_major=Get(CPos,3);
	trk_minor=Get(CPos,4);

	int len=Get(CPos,1);
	int channels=Get(CPos,2);

	channels=1;
	if (len<0) len=0;
	if (channels<0) channels=0;

	int P=CPos+1;
	int tlen=(len+1)*channels;


	

	int cmd;

	int end;
	int t;
	for (t=P;t<EntriesCount;t++)
	{
		if (Get(t,0)==0) 
		{
			end=t;break;
		}

	}


	for (int i=0;i<tlen;i++)
	{

		cmd=Get(P+i,0);

	if ((cmd!=trk_channelcmd)&&(cmd!=trk_notecmd))
		{
					//MessageBox(hWnd,"1",NULL,0);
		memmove(Pack+(P+tlen)*CellSize,Pack+(P+i)*CellSize,(end-(P+i)+1)*CellSize);

		
		
		int j;
		for (j=0;j<tlen;j++)
			{
			Put(P+j,0,trk_notecmd);
			}

		for (j=0;j<channels;j++)
			{
			Put(P+j*(len+1),0,trk_channelcmd);
			}

		memcpy(RExchange+(P*CellSize),Pack+(P*CellSize),(EntriesCount-P)*CellSize);
				//for (int y=0;y<end;y++)			MessageBox(hWnd,CmdDesc[Get(y,0)].FName,".",0);
		return;
		}
	}


for (t=P+tlen;t<end;t++)
{
if ((Get(t,0)!=trk_channelcmd)&&(Get(t,0)!=trk_notecmd)) break;
}

if (t>(P+tlen)) 
{
//MessageBox(hWnd,"2",NULL,0);
		memmove(Pack+(P+tlen)*CellSize,Pack+t*CellSize,(end-t)*CellSize);

		for (int j=0;j<tlen;j++)
		{
		Put(P+j,0,trk_notecmd);
		}

		for (int j=0;j<tlen;j+=(len+1))
		{
		Put(P+j,0,trk_channelcmd);
		}

		Put(end-(t-(P+tlen)),0,0);

		memcpy(RExchange+(P*CellSize),Pack+(P*CellSize),(end-P)*CellSize);
}

}

void Channel()
{
	int panning=Get(CPos,1);
	int volume=Get(CPos,2);
}

void Note()
{
	int a=Get(CPos,3);
}

void StoreSequence()
{
int plen=16*256*20;
	int n=Get(CPos,1);
	//search up
	int i;int start=CPos;
	for (i=CPos;i>0;i--)
	{
		if (CmdDesc[Get(i,0)].FRoutine==&Scene) return;
		if (CmdDesc[Get(i,0)].FRoutine==&Sequence) 
		{//found start of sequence
		start=CPos;goto j;
		}
	}
j:;
/*		int len=Get(i,1);
		int chl=Get(i,2);
		int j=i+1;
		memcpy(patterns+n*plen,Pack+i,40);
		int o=40;
		for (int y=0;y<chl;y++)
		for (int x=0;x<len+1;x++)
			{
			memcpy(patterns+o+n*plen+(y+x*(len+1))*20,Pack+j,20);
			}

		}
	}
*/


}

void PlaySequence()
{
	ApplyMods();
}


//-----------


#include "modifers.h"

void ApplyMods()
{
SelectAll();
int Cfn;

next:
#ifdef EditMode
if (stageview!=0&&stageview==CPos||finalview==1&&Pos==CPos) 
{
for(int h=0;h<100;h++){freq[h]=0;phase[h]=0;amp[h]=0;}//reset anim
return;
}
#endif


Cfn=nGet(CPos+CmdDesc[nGet(CPos)].FSize);


if (Cfn==0) {return;}
if (CmdDesc[Cfn].FLevel<2) {CPos+=CmdDesc[nGet(CPos)].FSize;return;}

CPos+=CmdDesc[nGet(CPos)].FSize;

	AnimP();
	if (CmdDesc[Cfn].FRoutine!=NULL)	CmdDesc[Cfn].FRoutine();


goto next;


}


void LoadWave()
{
#ifdef EditMode
char n[32];
memcpy(n,Pack+CPos+256-33,32);
useWave=1;

				FILE *fp;
				fp = fopen(n, "rb");
				if (fp!=NULL)
				{
				fread(WaveBuffer,1,44100*60*10*2*2+256,fp);
				fclose(fp);
				}
#endif
}


int CompileShader(char* buff,int slot)
{
LPD3DXBUFFER pE,vE;

for (int p=0;p<64;p++) ShaderVarsType[slot][p]=-1;
for (int p=0;p<64;p++) ShaderVars[slot][p][0]=0;

int len=0;

//search eof
while (len<65536-4)
{
	if (*(buff+len)==0) break;
	len++;
}
if (len==0) return 0;


//search names
char* pt,*pt2;
pt=strstr(buff,"//vs:");
if (pt) {
	pt+=5;
	pt2=strstr(pt,"\n");
	if (pt2) {
			strncpy(vsname[slot],pt,31);
			if ((pt2-pt)<31) vsname[slot][pt2-pt-1]=0; else vsname[slot][31]=0;
			}
	}

pt=strstr(buff,"//ps:");
if (pt) {
	pt+=5;
	pt2=strstr(pt,"\n");
	if (pt2) {
			strncpy(psname[slot],pt,31);
			if ((pt2-pt)<31) psname[slot][pt2-pt-1]=0; else psname[slot][31]=0;
			}
	}
//

//vars

char* pt3;
char a;
char tb[256];
int vnum=2;//index is synchonized with cmd format  0=command code 1=shader name 2..n is defined by shader

pt=strstr(buff,"//vars");
if (pt) {
	pt2=strstr(pt,"\n");//start vars area
	if (pt2) {
			pt2++;
			pt=strstr(pt2,"//endvars");//end vars area
			if (pt) {
				//
				int i=0;
				while(i<pt-pt2) {//search in area only
					a=*(pt2+i);
					if (isalpha(a))//first letter
					{
						strncpy(tb,pt2+i,3);tb[3]=0;
						if (!strcmp(tb,"int"))
						{
							int n=i+3;
							while(n<pt-pt2&&*(pt2+n)==' ') n++;//skip spaces
							int ni=0;
							while(n<pt-pt2&&*(pt2+n)!=';'&&*(pt2+n)!=' ') //store name
							{
								ShaderVars[slot][vnum][ni]=*(pt2+n);
								ni++;
								n++;
							}
							ShaderVars[slot][vnum][ni]=0;
							ShaderVarsType[slot][vnum]=-1;
							vnum++;
						i=n;
						}
						else {
						strncpy(tb,pt2+i,7);tb[7]=0;
						if (!strcmp(tb,"sampler"))
						{
							int n=i+7;
							while(n<pt-pt2&&*(pt2+n)==' ') n++;//skip spaces
							int ni=0;
							while(n<pt-pt2&&*(pt2+n)!=':'&&*(pt2+n)!=' ') //store name
							{
								ShaderVars[slot][vnum][ni]=*(pt2+n);
								ni++;
								n++;
							}
							ShaderVars[slot][vnum][ni]=0;

							while(n<pt-pt2&&*(pt2+n)!='(') n++;//search (
							while(n<pt-pt2&&*(pt2+n)!='s') n++;//search s
							char sl=*(pt2+n+1);
							int slt=sl-'0';
							ShaderVarsType[slot][vnum]=slt;
							vnum++;
						i=n;
						}

						}
						i++;
					}
					else {	
						i++;
					}
				}
				
				
				//
				}
			}
	}




int retV=0;int retP=0;


	if (D3D_OK==D3DXCompileShader(buff,len-1,0,0,vsname[slot], "vs_3_0", 0, &tmp, &errv, &pCtC[slot] )) pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &CustomVS[slot] ); else retV=1;
	if (D3D_OK==D3DXCompileShader(buff,len-1,0,0,psname[slot], "ps_3_0", 0, &tmp, &errp, &pCtCp[slot] )) pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &CustomPS[slot] ) ; else retP= 1;
	
	if (retV==1&&retP==1) return 3;
	if (retP==1) return 2;
	if (retV==1) return 1;

	return 0;
}


void CreateShader()
{
	int result=CompileShader((char*)Pack+CPos+4,Get(CPos,1));
}



D3DXVECTOR4 shFogColor;
D3DXVECTOR4 shVFogColor;
float shFogStart,shFogEnd;
float shVFogStart,shVFogEnd;

void ShFogSetup()
{
shFogStart=Get(CPos,1)/32768.0;
shFogEnd=Get(CPos,2)/32768.0;
shFogColor.x=Get(CPos,3)/255.0;
shFogColor.y=Get(CPos,4)/255.0;
shFogColor.z=Get(CPos,5)/255.0;
shFogColor.w=Get(CPos,6)/255.0;

shVFogStart=Get(CPos,7)/32768.0;
shVFogEnd=Get(CPos,8)/32768.0;
shVFogColor.x=Get(CPos,9)/255.0;
shVFogColor.y=Get(CPos,10)/255.0;
shVFogColor.z=Get(CPos,11)/255.0;
shVFogColor.w=Get(CPos,12)/255.0;
}

void SetTextureForVS()
{
int sampler = Get(CPos,1);
int Tex=Get(CPos,2);
if (Tex<0||Tex>maxtex) return;
if (sampler<0||sampler>3) return;

pDevice->SetTexture(D3DVERTEXTEXTURESAMPLER0+sampler, Texture[Tex]);
}

void ApplyMaterial()
{
	D3DXHANDLE h0;
	int material=Get(CPos,1);
	int sn=lastShaderApplied;
	if (sn<1) return;

	D3DXVECTOR4 ambientMtrl;
    D3DXVECTOR4 diffuseMtrl;
	D3DXVECTOR4 specMtrl;

	ambientMtrl.x=Material[material].Ambient.r;
	ambientMtrl.y=Material[material].Ambient.g;
	ambientMtrl.z=Material[material].Ambient.b;
	ambientMtrl.w=Material[material].Ambient.a;
	h0 = pCtC[sn]->GetConstantByName(NULL, "cA");
    pCtC[sn]->SetVector(pDevice, h0, &ambientMtrl);
	h0 = pCtCp[sn]->GetConstantByName(NULL, "cA");
    pCtCp[sn]->SetVector(pDevice, h0, &ambientMtrl);

	diffuseMtrl.x=Material[material].Diffuse.r;
	diffuseMtrl.y=Material[material].Diffuse.g;
	diffuseMtrl.z=Material[material].Diffuse.b;
	diffuseMtrl.w=Material[material].Diffuse.a;
	h0 = pCtC[sn]->GetConstantByName(NULL, "cD");
    pCtC[sn]->SetVector(pDevice, h0, &diffuseMtrl);
	h0 = pCtCp[sn]->GetConstantByName(NULL, "cD");
    pCtCp[sn]->SetVector(pDevice, h0, &diffuseMtrl);

	specMtrl.x=Material[material].Specular.r;
	specMtrl.y=Material[material].Specular.g;
	specMtrl.z=Material[material].Specular.b;
	specMtrl.w=Material[material].Specular.a;
	h0 = pCtC[sn]->GetConstantByName(NULL, "cS");
    pCtC[sn]->SetVector(pDevice, h0, &specMtrl);
	h0 = pCtCp[sn]->GetConstantByName(NULL, "cS");
    pCtCp[sn]->SetVector(pDevice, h0, &specMtrl);

	float sp=Material[material].Power/10.0;
	h0 = pCtC[sn]->GetConstantByName(NULL, "cSP");
    pCtC[sn]->SetFloat(pDevice, h0, sp);
	h0 = pCtCp[sn]->GetConstantByName(NULL, "cSP");
    pCtCp[sn]->SetFloat(pDevice, h0, sp);

}



void _ApplyShader(int shader,int cp)
{
int pshader=shader;
if (OverrideShaderFlag!=0) 
{
	if (OverrideShaderN>0)	pshader=OverrideShaderN;
}


	if (shader<1) {
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);	
	setshader_flag=0;
	return;
	}

	setshader_flag=1;
	lastShaderApplied=shader;
//
	D3DXHANDLE h0;
//user vars
	for (int i=0;i<21;i++)
	{
		
		if (ShaderVars[shader][i][0]!=0&&ShaderVarsType[shader][i]==-1)
		{
		h0 = pCtC[shader]->GetConstantByName(NULL, ShaderVars[shader][i]);
		pCtC[shader]->SetInt(pDevice, h0, Get(cp,i));
		h0 = pCtCp[pshader]->GetConstantByName(NULL, ShaderVars[pshader][i]);
		pCtCp[pshader]->SetInt(pDevice, h0, Get(cp,i));
		
		}
	}
//standart vars
		int sn=shader;


		int t=ptime;
		h0 = pCtC[shader]->GetConstantByName(NULL, "time");
		pCtC[shader]->SetInt(pDevice, h0, t);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "time");
		pCtCp[pshader]->SetInt(pDevice, h0, t);

		 t=sceneStart;
		h0 = pCtC[shader]->GetConstantByName(NULL, "sceneStart");
		pCtC[shader]->SetInt(pDevice, h0, t);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "sceneStart");
		pCtCp[pshader]->SetInt(pDevice, h0, t);
		 t=sceneFinish;
		h0 = pCtC[shader]->GetConstantByName(NULL, "sceneFinish");
		pCtC[shader]->SetInt(pDevice, h0, t);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "sceneFinish");
		pCtCp[pshader]->SetInt(pDevice, h0, t);


//
		h0 = pCtC[shader]->GetConstantByName(NULL, "greedx");
		pCtC[shader]->SetInt(pDevice, h0, greedx);
		h0 = pCtC[shader]->GetConstantByName(NULL, "greedy");
		pCtC[shader]->SetInt(pDevice, h0, greedy);

//instance
		h0 = pCtC[shader]->GetConstantByName(NULL, "instN");
		pCtC[shader]->SetInt(pDevice, h0, InstanceNum);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "instN");
		pCtCp[pshader]->SetInt(pDevice, h0, InstanceNum);;


//fog
		h0 = pCtC[sn]->GetConstantByName(NULL, "FogColor");
		pCtC[sn]->SetVector(pDevice, h0, &shFogColor);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "FogColor");
		pCtCp[pshader]->SetVector(pDevice, h0, &shFogColor);

		h0 = pCtC[sn]->GetConstantByName(NULL, "VFogColor");
		pCtC[sn]->SetVector(pDevice, h0, &shVFogColor);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "VFogColor");
		pCtCp[pshader]->SetVector(pDevice, h0, &shVFogColor);

		h0 = pCtC[shader]->GetConstantByName(NULL, "FogStart");
		pCtC[shader]->SetFloat(pDevice, h0, shFogStart);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "FogStart");
		pCtCp[pshader]->SetFloat(pDevice, h0, shFogStart);
		h0 = pCtC[shader]->GetConstantByName(NULL, "FogEnd");
		pCtC[shader]->SetFloat(pDevice, h0, shFogEnd);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "FogEnd");
		pCtCp[pshader]->SetFloat(pDevice, h0, shFogEnd);


		h0 = pCtC[shader]->GetConstantByName(NULL, "VFogStart");
		pCtC[shader]->SetFloat(pDevice, h0, shVFogStart);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "VFogStart");
		pCtCp[pshader]->SetFloat(pDevice, h0, shVFogStart);
		h0 = pCtC[shader]->GetConstantByName(NULL, "VFogEnd");
		pCtC[shader]->SetFloat(pDevice, h0, shVFogEnd);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "VFogEnd");
		pCtCp[pshader]->SetFloat(pDevice, h0, shVFogEnd);

		t=screen_width;
		h0 = pCtC[shader]->GetConstantByName(NULL, "scrW");
		pCtC[shader]->SetInt(pDevice, h0, t);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "scrW");
		pCtCp[pshader]->SetInt(pDevice, h0, t);

		t=screen_height;
		h0 = pCtC[shader]->GetConstantByName(NULL, "scrH");
		pCtC[shader]->SetInt(pDevice, h0, t);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "scrH");
		pCtCp[pshader]->SetInt(pDevice, h0, t);

//camera
		D3DMATRIX w;D3DXMATRIX ma,mb,mc;
		ma=World;mb=View;

		h0 = pCtC[sn]->GetConstantByName(NULL, "mW");
		pCtC[sn]->SetMatrix(pDevice, h0, &ma);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mW");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &ma);

		D3DXMatrixMultiply(&ma,&ma,&mb);
		mb=Projection;mc=ma;
		D3DXMatrixMultiply(&ma,&ma,&mb);
		w=ma;

		h0 = pCtC[sn]->GetConstantByName(NULL, "mWV");
		pCtC[sn]->SetMatrix(pDevice, h0, &mc);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mWV");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &mc);

		h0 = pCtC[sn]->GetConstantByName(NULL, "mWVP");
		pCtC[sn]->SetMatrix(pDevice, h0, &ma);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mWVP");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &ma);

//
		D3DXMatrixTranspose(&mc,&ma);
		h0 = pCtC[sn]->GetConstantByName(NULL, "mWVPt");
		pCtC[sn]->SetMatrix(pDevice, h0, &mc);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mWVPt");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &mc);

//
		ma=View;

		h0 = pCtC[sn]->GetConstantByName(NULL, "mV");
		pCtC[sn]->SetMatrix(pDevice, h0, &ma);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mV");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &ma);

		ma=Projection;
		h0 = pCtC[sn]->GetConstantByName(NULL, "mP");
		pCtC[sn]->SetMatrix(pDevice, h0, &ma);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mP");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &ma);


		D3DXVECTOR4 vecLight;
		vecLight.x=SceneLight[0].Direction.x;
		vecLight.y=SceneLight[0].Direction.y;
		vecLight.z=SceneLight[0].Direction.z;
		vecLight.w=0;
		h0 = pCtC[sn]->GetConstantByName(NULL, "vL");
		pCtC[sn]->SetVector(pDevice, h0, &vecLight);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "vL");
		pCtCp[pshader]->SetVector(pDevice, h0, &vecLight);


		//видовой вектор
		D3DXMATRIX mat_world, mat_view;
		mat_world=World;mat_view=View;
		D3DXMATRIX mat_temp,mat_view_inverse;
		D3DXVECTOR4  view_pos;
		D3DXMatrixMultiply(&mat_temp,&mat_world,&mat_view);
		D3DXMatrixInverse(&mat_view_inverse,NULL,&mat_temp);
		D3DXVec4Transform(&view_pos,(D3DXVECTOR4*)&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),&mat_view_inverse);

		h0 = pCtC[sn]->GetConstantByName(NULL, "vVP");
	    pCtC[sn]->SetVector(pDevice, h0, &view_pos);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "vVP");
		pCtCp[pshader]->SetVector(pDevice, h0, &view_pos);

		//матрица камеры из источника света 0
		h0 = pCtC[sn]->GetConstantByName(NULL, "mL");
		pCtC[sn]->SetMatrix(pDevice, h0, &LightMatrix);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mL");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &LightMatrix);

		ma=World;		mb=LightMatrix;
		D3DXMatrixMultiply(&ma,&ma,&mb);

		float Vw=1;
	float Vh=1;
	float Zf=8*100;
	float Zn=0.5f;

	D3DMATRIX Proj = 
	{
		2/Vw/8, 0,		0,           0,
		0,		2/Vh/8,	0,           0,
		0,		0,		1/(Zn-Zf),   0,
		0,		0,		Zn/(Zn-Zf),  1
	};

		mb=Proj;
		//mb=Projection;
		D3DXMatrixMultiply(&ma,&ma,&mb);

		h0 = pCtC[sn]->GetConstantByName(NULL, "mWLP");
		pCtC[sn]->SetMatrix(pDevice, h0, &ma);
		h0 = pCtCp[pshader]->GetConstantByName(NULL, "mWLP");
		pCtCp[pshader]->SetMatrix(pDevice, h0, &ma);



		//

//textures
int s=0;
	for (int i=0;i<21;i++)
	{
		if (ShaderVars[shader][i][0]!=0&&ShaderVarsType[shader][i]>=0)
		{
			SetTexture(ShaderVarsType[shader][i],Get(cp,i),0);s++;
			//SetTexture(s,Get(CPos,i),0);s++;
		}
	}

	pDevice->SetVertexShader(CustomVS[shader]);
	pDevice->SetPixelShader(CustomPS[pshader]);
}

void ApplyShader()
{
//
	
int shader=Get(CPos,1);
_ApplyShader(shader,CPos);
ApplyShaderPos=CPos;
}

void ShaderPost()
{
pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);
int tr=CpyToPrevFp();

ApplyShader();

pDevice->SetTexture(0,PrevStageFp[tr]);

//move it to init
static MyVertex pPVerts[4];

float s=1+.5/(float)tex_res[current_rt];float st=1;//-1/(float)tex_res[current_rt];

pPVerts[0].x=-s;pPVerts[0].y=-s;pPVerts[0].z=0;pPVerts[0].u=0;pPVerts[0].v=0;
pPVerts[1].x=s;pPVerts[1].y=-s;pPVerts[1].z=0;pPVerts[1].u=st;pPVerts[1].v=0;
pPVerts[2].x=-s;pPVerts[2].y=s;pPVerts[2].z=0;pPVerts[2].u=0;pPVerts[2].v=st;
pPVerts[3].x=s;pPVerts[3].y=s;pPVerts[3].z=0;pPVerts[3].u=st;pPVerts[3].v=st;

unsigned int pPInds[6]={0,1,2,1,3,2};

//subpixel
for (int i=0;i>4;i++) {
pPVerts[i].x-=.5/(float)tex_res[current_rt];
pPVerts[i].y-=.5/(float)tex_res[current_rt];
}

					void* pBuf;
					pPVB->Lock( 0, sizeof(MyVertex) * 4, &pBuf, 0 );
					  memcpy( pBuf, pPVerts, sizeof(MyVertex) * 4);
					pPVB->Unlock();
					
					pPIB->Lock( 0, sizeof(int) * 6, &pBuf, 0 );
						memcpy( pBuf, pPInds, sizeof(int) * 6);
					pPIB->Unlock();
//

pDevice->SetStreamSource(0, pPVB, 0, sizeof(MyVertex) );
pDevice->SetIndices(pPIB);
pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

SetView(0);
}

void ShowObjFromTexture()
{
	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

	greedx=32;

	greedx=Get(CPos,1);
	greedy=Get(CPos,2);

	pDevice->SetStreamSource( 0, pTVB, 0, sizeof(TVertex) );
	pDevice->SetFVF( D3DFVF_TVERTEX );

	NumVerts=(greedx+1)*(greedy+1);// количество вершин
	NumTriangles=(greedx)*(greedy)*2;// количество треугольников

	NumInds=NumTriangles*3;// количество индексов.

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	

	D3DXMATRIX w;
	w=World;
	D3DXMatrixIdentity(&CMatrix);
 	
	vbout_start=0;
	vbout_end=NumTriangles;
int cm=CPos;
	ApplyMods(); 

	if (vbout_start<0) vbout_start=0;
	if (vbout_start>NumTriangles) vbout_start=NumTriangles;
	if (vbout_end<0) vbout_end=0;
	if (vbout_end>NumTriangles) vbout_end=NumTriangles;

	D3DXMatrixMultiply(&CMatrix,&CMatrix,&w);

	pDevice->SetTransform(D3DTS_WORLD, &CMatrix);

	pDevice->SetTexture(D3DVERTEXTEXTURESAMPLER0, Texture[Get(cm,5)]);

	if (Get(cm,3)==1)
		pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP );
	else
		pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP );

	if (Get(cm,4)==1)
		pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP );
	else
		pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP );


	//pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP );
	//pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_MINFILTER,2);
	//pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER1,D3DSAMP_MINFILTER,2);

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, vbout_start*3,vbout_end-vbout_start);	
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0,NumTriangles);	
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NumTriangles);	
	
	
//restore states&exit
	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &View);
	pDevice->SetTransform(D3DTS_WORLD, &StartMatrix);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetFVF( D3DFVF_MYVERTEX );

#ifdef EditMode
	SetWindowText(hWnd0,CmdDesc[Get(Pos,0)].FName);
	if (!strcmp(CmdDesc[Get(Pos,0)].FName,"ShaderPost"))
	{
	if ((!strcmp(vsname[Get(Pos,1)],"sel_selSphere"))||
		(!strcmp(vsname[Get(Pos,1)],"sel_AddSelSphere")))
		{
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
		show_ms(Get(Pos,2)/2000.0,Get(Pos,3)/2000.0,Get(Pos,4)/2000.0,Get(Pos,5)/1000.0);
		}
	if (!strcmp(vsname[Get(Pos,1)],"sel_selCube"))
		{
	pDevice->SetVertexShader(NULL);
	pDevice->SetPixelShader(NULL);
		show_mc(Get(Pos,2)/2000.0,Get(Pos,3)/2000.0,Get(Pos,4)/2000.0,Get(Pos,5)/2000.0,Get(Pos,6)/2000.0,Get(Pos,7)/2000.0);
		}

	}

#endif


}


void OverrideShader()
{
OverrideShaderFlag=Get(CPos,1);
OverrideShaderN=Get(CPos,2);
}


void IndexedIoIsolated()
{
int x=NumInds;
for (int p=0;p<NumVerts;p++)
	{
		pVerts1[p]=pVerts[p];
	}

int t=0;
for (int k=0;k<NumInds;k++)
	{
	pVerts[t]=pVerts1[pInds[k]];
	t++;
	}

	NumVerts=t;
	NumTriangles=t/3;
	greedx=NumVerts;greedy=1;

for (int m=0;m<NumInds;m+=3)
	{
		pVerts[m].b1=(pVerts[m].x+pVerts[m+1].x+pVerts[m+2].x)/3.0;
		pVerts[m].b2=(pVerts[m].y+pVerts[m+1].y+pVerts[m+2].y)/3.0;
		pVerts[m].b3=(pVerts[m].z+pVerts[m+1].z+pVerts[m+2].z)/3.0;

		pVerts[m+1].b1=pVerts[m].b1;
		pVerts[m+1].b2=pVerts[m].b2;
		pVerts[m+1].b3=pVerts[m].b3;

		pVerts[m+2].b1=pVerts[m].b1;
		pVerts[m+2].b2=pVerts[m].b2;
		pVerts[m+2].b3=pVerts[m].b3;

	}


}

#include "Mplayer.h"