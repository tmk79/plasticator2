#include <mmsystem.h>


void DrawScene();
void DrawSomeNavi();
void VisualNavi();

// переменные для отображения FPS
	static DWORD fps_previous_time;
	static int count_fps;
	static int print_count_fps;
	static DWORD fps_current_time;
	static char FPS_[256] = {0};
	static RECT rc;
	static float fps_start_time = 0;
	double lasttime;
	double timetime;
	double loct,locpt;
	int fc=0;
	double newpt;

void CalcFPS()
{

	//fps_current_time = GetTickCount () - fps_start_time;
	fps_current_time = GetCounter() - fps_start_time;
	
	
	count_fps++;
		

	if (fps_current_time >= (fps_previous_time + 1000.0))
		{
		print_count_fps = count_fps;
		fps_previous_time = fps_current_time;
		count_fps = 0;
		
		
		}
	char aa[100];
	int a;
	a=print_count_fps;
	//_itoa(a,aa,10);
	//SetWindowText(hWndView, aa);

}

__int64 CurrentTick;
__int64 PrevTick;

int tm1,tm2;

double perftimer,prefdelta;
double perfpercent;


void DrawScene()
{

if (fc==0) perftimer=GetCounter();

if (camstate==-1) View=View2;

timelinematrix=0;
#ifdef EditMode
visualnavi=-1;
#endif
  pDevice->BeginScene();

CPos=0;Cfn=0;;
ScenePos=0;
stackpos=0;
int a;


if (PrecalcStatus==1) 
	{
	if (CmdDesc[nGet(LoopPoint)].FRoutine==MainLoop) CPos=LoopPoint;
	}

#ifdef EditMode
if (SceneToShow!=0) //gui call
{
	CPos=SceneToShow;
	//pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(127,127,127,0),8.0f,0);
}
#endif

//backup for animation
BYTE* chp;
memcpy(RExchange,Pack,CellSize*EntriesCount);//!!! move to start playing or sometinhg like it
chp=RExchange;
RExchange=Pack;
Pack=chp;

//if (astate==1) ptime+=1; //else ptime=staticaframe; //if animation stopped
//to do later
//if (print_count_fps>=60) ptime+=1;
//if (print_count_fps<60&&print_count_fps>30) ptime+=2;


next:

Cfn=nGet(CPos);

	a=CPos;
	
	if (CmdDesc[Cfn].FRoutine!=NULL)
	{
		AnimP();
#ifdef EditMode
//		if (wireframe==1&&CPos==Pos) pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
//		if (wireframe==1&&CPos==Pos+1) pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		if (wireframe==1) pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		if (wireframe!=1) pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);

#endif
#ifndef EditMode
		pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
#endif
		
		CurrentCmd1=CmdDesc[Cfn].FRoutine;
//int lp,lcp;
//lp=Pos;lcp=CPos;

//if (lp==lcp&&fc==0) locpt=GetCounter();

//int nco=lp+CmdDesc[Cfn].FSize;

//while (CmdDesc[nGet(nco)].FLevel==2)
//{
//	nco+=CmdDesc[nGet(nco)].FSize;
//}

//if (nco==lcp&&fc==0) loct=GetCounter();

		CmdDesc[Cfn].FRoutine();



#ifdef EditMode
		if (NormalShowFlag==1&&CmdDesc[Cfn].FCategory==IDC_3D) ShowNormals();
#endif
		if (currentVBtoadd>0)//accumulate geometry in vb
		{
			if (CmdDesc[Cfn].FRoutine!=StartAddToVB&&
				CmdDesc[Cfn].FRoutine!=AddToVB&&
				CmdDesc[Cfn].FLevel==1)
				{
				_AddToVB();
				}
		}

		for (int u=1;u<8;u++)	
		{
		pDevice->SetTextureStageState( u, D3DTSS_COLOROP,D3DTOP_DISABLE  );			 
		}

	}

#ifdef EditMode//fix+1
	if (Pos==CPos) 
	{
		
		LPDIRECT3DSURFACE9 RT,RT2;

		HRESULT h0;
		h0=CStageTexture->GetSurfaceLevel(0,&RT2);

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

#endif

	if (Cfn==0||//terminator
		CmdDesc[Cfn].FRoutine==EndDraw//end drawing
#ifdef EditMode
		||(stageview!=0&&stageview==CPos)||//gui check
		(SceneToShow!=0&&CmdDesc[Cfn].FRoutine==EndScene&&stackpos==0)||//gui check. isolatied sceneview
		(finalview==1&&Pos==CPos)//gui check. for stage-viewing
#endif
		)

		{


	if (record==1)
		{
		pDevice->EndScene();

			pDevice->Present( NULL,NULL, hWndView, NULL );

			chp=RExchange;
			RExchange=Pack;
			Pack=chp;
			return;
		}

			for (int u=0;u<8;u++)	
			{
			pDevice->SetSamplerState(u, D3DSAMP_MIPFILTER, 0);
			}

			pDevice->SetRenderTarget(0,mainRT);
			SetView(0);
			SetVp_(0);
#ifdef EditMode
			if (VNaviMode==1)
#endif
			{
			pDevice->EndScene();
			pDevice->Present(NULL, NULL, hWndView, NULL );

#ifdef EditMode
			pDevice->BeginScene();
			pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(155,155,155,55),8.0f,0);
			
#endif
			}
//#endif
			pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
			pDevice->SetPixelShader(NULL);
			pDevice->SetVertexShader(NULL);
			for (int u=1;u<8;u++)	
			{
			pDevice->SetTextureStageState( u, D3DTSS_COLOROP,D3DTOP_DISABLE  );			 
			pDevice->SetTextureStageState( u, D3DTSS_ALPHAOP,D3DTOP_DISABLE  );			 
				//		pDevice->SetSamplerState(u, D3DSAMP_MIPFILTER, 0);
			}
			pDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_MODULATE  );			 


			//CalcFPS();
			override_tm_flag=-1;
			WriteAlpha(0);
			pDevice->SetTextureStageState( 0, D3DTSS_COLOROP,D3DTOP_MODULATE  );			 

			float cz;
			cz=cam_zoom+.3;
			cam_zoom=0;
			//reset all for drawing info 
			SetView(1);
			SetWorld(1);
			SetProjecton(1);
			ZClear();
			DisableFog();

			pDevice->SetTransform(D3DTS_VIEW, &StartViewMatrix); 
			LightsOn();
			for (int z=0;z<8;z++) pDevice->LightEnable(z,FALSE);

			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

#ifdef EditMode
			float z=cam_zoom;
			cam_zoom+=1;

			ShowStages();//gui call, must be removed in runtime
			ShowTextures();//gui call, must be removed in runtime
			DrawSomeNavi();//gui call, must be removed in runtime
			cam_zoom=cz;
#endif
			//if (CmdDesc[Get(Pos,0)].FLevel==1||!strcmp(CmdDesc[Get(Pos,0)].FName,"MultiTexture")) ShowTexArg();//gui call, must be removed in runtime

			LightsOff();//?? scene resets it
			
			

			FreeCamera();
			SetView(0);
			SetWorld(0);
			SetProjecton(0);
			ZClear();
			pDevice->SetTransform(D3DTS_VIEW, &View3); 

#ifdef EditMode

if (fc==0) newpt=GetCounter();
double ff=1000.0/60.0;
double perfpercent=1000*(newpt-perftimer);

float llc=loct-locpt;

			VisualNavi();

char aa[33];
int d,s;
_itoa((int)(perfpercent),aa,10);

//aa=_fcvt(perfpercent,10,&d,&s);
//char d1[40],d2[10];
//strncpy(d1,aa,d);
//d1[d]=0;
//strcat(d1,",");
//strncpy(d1,aa+d,1);


CalcFPS();

if (CmdDesc[nGet(Pos)].FLevel!=2)
{
	float x,y;
	//x=-50;y=cursor_y-210;
	x=-50;y=0;

	NText("frame time",-10,x-273,y+250,32); NText(aa,-10,x-123,y+250,32);

	_itoa(print_count_fps,aa,10);

	NText("fps",-10,x-273,y+210,32);
	NText(aa,-10,x-213,y+210,32);


//	NText("cmd time",-10,x-273,y+170,32);
	_itoa((int)1000*(llc),aa,10);
//	NText(aa,-10,x-143,y+170,32);

	double fff=1000*(llc)/perfpercent;
	_itoa((int)100*fff,aa,10);
	strcat(aa,"%");
//	NText(aa,-10,x-53,y+170,32);

	//_itoa((int)100*(locpt),aa,10);
	//NText(aa,-10,-173,10,32);
}
	fc++;if (fc>10) fc=0;


cam_zoom=z;


#endif
			
			pDevice->EndScene();
#ifdef EditMode
			if (VNaviMode==1)
			{
			//pDevice->Present( NULL, NULL, NULL, NULL );
			RECT wrc;
			GetClientRect(hWnd0,&wrc);
			//pDevice->Present( NULL,&wrc, hWnd0, NULL );

			pDevice->Present( NULL,&wrc, hWnd0, NULL );
			
			}
			else 
#endif
			{
			pDevice->Present( NULL,NULL, hWndView, NULL );
			}
			chp=RExchange;
			RExchange=Pack;
			Pack=chp;
			
			
			return;
		}


	if (CPos==a) 
	{
		CPos+=CmdDesc[nGet(CPos)].FSize;

	}
	

goto next;


}