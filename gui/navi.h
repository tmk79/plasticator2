#include <commdlg.h>
#include <stdio.h>


//#define  _WIN32_WINNT	0x0400
#define WM_MOUSEWHEEL                   0x020A
#define WHEEL_DELTA                     120  

//окно редактировани€ команд и параметров
BOOL CALLBACK PEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK PEditProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK RenameProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

void SearchScene(int scene);
void PlayWave();
void StopWave();
char currentfile[255];

int sas=0;//save anim status

int mbofs=0;
int mbmofs=0;
int mbmflag=0;

int tbofs=0;
int tbmofs=0;
int tbmflag=0;

void SaveUndoState();
void ProcessUndo();


char cdir2[1000];
char undopath[1000];
char tmpstr[1000];

void DeselectAll()
{
int j=0;int ii=0;
while (j<EntriesCount*CellSize&&nGet(j)!=0)
	{
		SelBuffer[ii]=0;
		ii++;
		j+=CmdDesc[nGet(j)].FSize;
	}
}

int GetIndexFromPos(int pos)
{
int j=0;int ii=0;
while (j<EntriesCount*CellSize)
	{
		if (j==pos)
		{
		return ii;
		}
		ii++;
		j+=CmdDesc[nGet(j)].FSize;
	}
//MessageBox (hWnd0,"bad index","",MB_OK);
return -1;
}

int GetPosFromLocalIndex(int startp,int i)
{
int j=startp;int ii=0;
while (j<EntriesCount*CellSize)
	{
		if (ii==i)
		{
		return j;
		}
		ii++;
		j+=CmdDesc[nGet(j)].FSize;
	}
return -1;
}

void ShowNormals()
{
	 	pDevice->SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,Texture[0]);
		 int ad;

		 ad=0;
     for(int i=0; i<=greedy; i++)
	 {
         for(int j=0; j<=greedx; j++)
		 {
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z;
				ad++;
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x+pVerts[i*(greedx+1)+j].n1/27.0;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y+pVerts[i*(greedx+1)+j].n2/27.0;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z+pVerts[i*(greedx+1)+j].n3/27.0;
				 ad++;
		 }
	}
pDevice->DrawPrimitiveUP(D3DPT_LINELIST,ad,pVerts1,sizeof(MyVertex));

		 ad=0;
     for(int i=0; i<=greedy; i++)
	 {
         for(int j=0; j<=greedx; j++)
		 {
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z;
				ad++;
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x+pVerts[i*(greedx+1)+j].t1/47.0;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y+pVerts[i*(greedx+1)+j].t2/47.0;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z+pVerts[i*(greedx+1)+j].t3/47.0;
				 ad++;
		 }
	}
pDevice->DrawPrimitiveUP(D3DPT_LINELIST,ad,pVerts1,sizeof(MyVertex));

		ad=0;
     for(int i=0; i<=greedy; i++)
	 {
         for(int j=0; j<=greedx; j++)
		 {
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z;
				ad++;
			 pVerts1[ad].x=pVerts[i*(greedx+1)+j].x+pVerts[i*(greedx+1)+j].b1/47.0;
				 pVerts1[ad].y=pVerts[i*(greedx+1)+j].y+pVerts[i*(greedx+1)+j].b2/47.0;
				 pVerts1[ad].z=pVerts[i*(greedx+1)+j].z+pVerts[i*(greedx+1)+j].b3/47.0;
				 ad++;
		 }
	}


	 pDevice->DrawPrimitiveUP(D3DPT_LINELIST,ad,pVerts1,sizeof(MyVertex));
 }

void SelfLocate()
{
	char* i;strcpy(tmpstr,GetCommandLine());
	strcpy(cdir2,GetCommandLine());//строка дл€ регистрации в реестре
	i=strstr(tmpstr,".exe");while (*(i)!='\\') i--;*(i+1)=0;//отрезаем лишнее
	strcpy(cdir,tmpstr+1);
	
	strcpy(undopath,tmpstr+1);
	strcat(undopath,"undo\\");
	//MessageBox(hWnd0,undopath,"undo",MB_OK);

}

void ProcessUndo()
{
char name[1000];
if (UndoNum==0) return;

			FILE *fp;

			    OPENFILENAME ofn;
				char szFile[100] = "\0"; 
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 DataFile\0*.p4p\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
				// Display the Open dialog box. 

				char aa[100];
				_itoa(UndoNum-1,aa,10);

				strcpy(name,undopath);
				strcat(name,aa);
				
				strcat(name,".p4p");
				
				fp = fopen(name, "rb");
				fread(Pack,1,CellSize*EntriesCount,fp);
				fclose(fp);

				UndoNum--;

				Pos=PosHistory[UndoNum];

}

void WriteUndoStage()
{
PosHistory[UndoNum]=Pos;
	SaveUndoState();
UndoNum++;

}


int oldpos,oldppage;

const int CpW=20;

void FillParamSh()
{
char a[64];
	strcpy(CmdDesc[ApplyShaderIndex].FParamEnum[1][0],"off");
	strcpy(CmdDesc[ShaderPostIndex].FParamEnum[1][0],"off");
	for (int j=1;j<32;j++) 
	{
		if (vsname[j][0]!=0)
		{
		strcpy(a,(char*)vsname[j]);
		strcat(a,"/");
		strcat(a,(char*)psname[j]);
		strncpy(CmdDesc[ApplyShaderIndex].FParamEnum[1][j],a,32);
		strncpy(CmdDesc[ShaderPostIndex].FParamEnum[1][j],a,32);
		}
	}

	for (int i=2;i<21;i++)
	{
		if (ShaderVars[Get(Pos,1)][i])
		{
			strncpy(CmdDesc[ApplyShaderIndex].FParamName[i],ShaderVars[Get(Pos,1)][i],32); 
			strncpy(CmdDesc[ShaderPostIndex].FParamName[i],ShaderVars[Get(Pos,1)][i],32); 
		}
		else
		{
		strcpy(CmdDesc[ApplyShaderIndex].FParamName[i],""); 
		strcpy(CmdDesc[ShaderPostIndex].FParamName[i],""); 
		}
	}
}

void FillParamTx()
{
char a[64];


int usedt[maxtex];
int k;
for (k=0;k<maxtex;k++) usedt[k]=0;

int i=0;
while (nGet(i)!=0)
{
	if (!strcmp(CmdDesc[nGet(i)].FName,"TextureToTexture")||
		!strcmp(CmdDesc[nGet(i)].FName,"SetRenderTarget"))
	{
		int p1=nGet(i+2);
		if (Pos!=i&&p1>=0&&p1<maxtex) usedt[p1]=1;
	}

	i+=CmdDesc[nGet(i)].FSize;;
}



if 	((!strcmp(CmdDesc[nGet(Pos)].FName,"TextureToTexture"))
	 ||(!strcmp(CmdDesc[nGet(Pos)].FName,"SetRenderTarget")))
{
for (k=1;k<32;k++)
{
	if (strstr(CmdDesc[nGet(Pos)].FParamName[k],"texture"))
	for (i=0;i<maxtex;i++)
	{
		char n[32];
		_itoa(i,n,10);
		if (usedt[i]==1) strcat(n," *");

			strncpy(CmdDesc[nGet(Pos)].FParamEnum[k][i],n,32);
	}
}
}

}

void FillParamVb()
{
char a[64];


int usedt[128];
int k;
for (k=0;k<maxvb;k++) usedt[k]=0;

int i=0;
while (nGet(i)!=0)
{
	if (!strcmp(CmdDesc[nGet(i)].FName,"CopyToVB")||
		!strcmp(CmdDesc[nGet(i)].FName,"StartAddToVB"))
	{
		int p1=nGet(i+2);
		if (Pos!=i&&p1>=0&&p1<maxvb) usedt[p1]=1;
	}

	i+=CmdDesc[nGet(i)].FSize;;
}



if 	((!strcmp(CmdDesc[nGet(Pos)].FName,"CopyToVB"))
	 ||(!strcmp(CmdDesc[nGet(Pos)].FName,"StartAddToVB")))
{
for (k=1;k<32;k++)
{
	if (strstr(CmdDesc[nGet(Pos)].FParamName[k],"n"))
	for (i=0;i<maxvb;i++)
	{
		char n[32];
		_itoa(i,n,10);
		if (usedt[i]==1) strcat(n," *");

			strncpy(CmdDesc[nGet(Pos)].FParamEnum[k][i],n,32);
	}
}
}
}


void ShowParam()
{
	if (CmdDesc[nGet(Pos)].FRoutine==ApplyShader||CmdDesc[nGet(Pos)].FRoutine==ShaderPost)
	{
	FillParamSh();
	}

	FillParamVb();
	FillParamTx();

char toH[100];
{
int t=0;
while ((strlen(CmdDesc[Get(Pos,0)].FParamName[t+1+PPage*CpW])>0)&&(t<CpW))
	{
		t++;
	}
	RECT r2;
	GetWindowRect(GetDlgItem(Navi2,IDC_EDIT_P0+t),&r2);
	RECT r;
	GetWindowRect(Navi2,&r);
	if (r.bottom!=r2.bottom-12)
	{
		r.bottom=r2.bottom-12;
		SetWindowPos(Navi2,0,r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_SHOWWINDOW|SWP_NOACTIVATE );
	}

if (oldpos!=Pos) 
{
	for (int p=0;p<CpW;p++) {
		ShowWindow(GetDlgItem(Navi2,IDC_EN0+p),SW_HIDE);
		ShowWindow(GetDlgItem(Navi2,IDC_EDIT_P0+p),SW_HIDE);
	}
	


	if (t>0 )SetWindowPos(Navi2,0,r.left,r.top,r.right-r.left,r.bottom-r.top,SWP_SHOWWINDOW|SWP_NOACTIVATE ); else ShowWindow(Navi2,SW_HIDE);
	
}
	

}
oldpos=Pos;
oldppage=PPage;

for (int t=0;t<CpW;t++)
	{
	if (!strcmp(CmdDesc[Get(Pos,0)].FParamName[t+1+PPage*CpW],"rgb"))
	{
		_itoa(Get32(Pos,t+1+PPage*CpW*2),toH,16);
		SetDlgItemText(Navi2,IDC_EDIT_P0+t,toH);
	}
	else
	{
		if (strlen(CmdDesc[Get(Pos,0)].FParamName[t+1+PPage*CpW])>0) {
			if (!IsWindowVisible(GetDlgItem(Navi2,IDC_EDIT_P0+t))) ShowWindow(GetDlgItem(Navi2,IDC_EDIT_P0+t),SW_SHOWNORMAL);  
		} else {
			if (IsWindowVisible(GetDlgItem(Navi2,IDC_EDIT_P0+t))) ShowWindow(GetDlgItem(Navi2,IDC_EDIT_P0+t),SW_HIDE);
			if (IsWindowVisible(GetDlgItem(Navi2,IDC_EN0+t))) ShowWindow(GetDlgItem(Navi2,IDC_EN0+t),SW_HIDE);

		}

		SetDlgItemInt(Navi2,IDC_EDIT_P0+t,Get(Pos,t+1+PPage*CpW),TRUE);

		if (Get(Pos,t+1+PPage*CpW)>=0&&Get(Pos,t+1+PPage*CpW)<32)
		{
			if (CmdDesc[Get(Pos,0)].FParamEnum[PPage*CpW+t+1][Get(Pos,t+PPage*CpW+1)][0]!=0)
			{
				if (!IsWindowVisible(GetDlgItem(Navi2,IDC_EN0+t))) {
					ShowWindow(GetDlgItem(Navi2,IDC_EN0+t),SW_SHOWNORMAL);
					
				}
				SetDlgItemText(Navi2,IDC_EN0+t,CmdDesc[Get(Pos,0)].FParamEnum[PPage*CpW+t+1][Get(Pos,1+t+PPage*CpW)]);
			
			}
			else
			{
			if (IsWindowVisible(GetDlgItem(Navi2,IDC_EN0+t))) ShowWindow(GetDlgItem(Navi2,IDC_EN0+t),SW_HIDE);
			
			}
		}

	}

	SetDlgItemText(Navi2,IDC_NAME_P0+t,CmdDesc[Get(Pos,0)].FParamName[t+1+PPage*CpW]);
	}
/*
if (PPage<8*127) 
	{
	if (strlen(CmdDesc[Get(Pos,0)].FParamName[0+1+(PPage+1)*CpW])>0) 
						SetDlgItemText(Navi2,IDC_PF,">*"); 
							else 
								SetDlgItemText(Navi2,IDC_PF,">");
	}
if (PPage==8*127) SetDlgItemText(Navi2,IDC_PF,">");

if (PPage>0) {if (strlen(CmdDesc[Get(Pos,0)].FParamName[0+1+(PPage-1)*CpW])>0) SetDlgItemText(Navi2,IDC_PB,"*<"); else SetDlgItemText(Navi2,IDC_PB,"<");}
if (PPage==0) SetDlgItemText(Navi2,IDC_PB,"<");
*/
}


int cscn=0;

void LoadShader(char* buf)
{

	ZeroMemory(buf,65535);

				FILE *fp;

			    OPENFILENAME ofn;
				char szFile[1000] = "\0"; 
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 Shader\0*.sh\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
				// Display the Open dialog box. 
				if (GetOpenFileName(&ofn)==TRUE)
				{
				strcpy (currentfile,ofn.lpstrFile);
				fp = fopen(ofn.lpstrFile, "rb");
				fread(buf,1,65535,fp);
				fclose(fp);
				}


}
void SaveShader(char* buf,int len)
{
				FILE *fp;
				//char* name;name=new char[100];
				char name[1000];
				OPENFILENAME ofn;
			    char szFile[1000] = "\0"; 
				char ttt[1000]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 Shader\0*.sh\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 

				{
					if (GetSaveFileName(&ofn)==TRUE)
					{
					strcpy(name,ofn.lpstrFile);
					if (NULL==strstr(ofn.lpstrFile,".sh")) strcat(name,".sh");

					fp = fopen(name, "wb");
					fwrite(buf,len,1,fp);
					fclose(fp);
					}
				}
}

void SaveUndoState()
{
int cnt=0;

//for (cnt=0;cnt<EntriesCount;cnt++)
while (cnt<EntriesCount*CellSize&&nGet(cnt)!=0)
{
	cnt+=CmdDesc[nGet(cnt)].FSize;
}
cnt++;

				FILE *fp;
				//char* name;name=new char[100];
				char name[1000];
				OPENFILENAME ofn;
			    char szFile[1000] = "\0"; 
				char ttt[100]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 DataFile\0*.p4p\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 
				
				char aa[100];
				_itoa(UndoNum,aa,10);

				strcpy(name,undopath);
				strcat(name,aa);
				
				strcat(name,".p4p");

				fp = fopen(name, "wb");
				if (fp )fwrite(Pack,cnt,1,fp); else MessageBox(hWnd0,name,"can't write undo stage",MB_OK);
				fclose(fp);
				
				//delete(name);
}

void ShowFilename()
{
				char wst[255]="";
				//strcpy(wst,"FxEngine Alpha : ");
				int sl=strlen(currentfile);
				int sofs=0;
				for (int i=sl;i>0;i--)
				{
					if (currentfile[i]=='\\') {sofs=i+1;break;}
				}
				strcat (wst,currentfile+sofs); 

				SetWindowText(hWnd0,wst);
}



void SaveAs()
{
int cnt=0;

while (cnt<EntriesCount*CellSize&&nGet(cnt)!=0)
{
	cnt+=CmdDesc[nGet(cnt)].FSize;
}
cnt++;

				FILE *fp;
				//char* name;name=new char[100];
				char name[100];
				OPENFILENAME ofn;
			    char szFile[100] = "\0"; 
				char ttt[100]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 DataFile\0*.p4p\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 

				{
					if (GetSaveFileName(&ofn)==TRUE)
					{
					strcpy(name,ofn.lpstrFile);
					if (NULL==strstr(ofn.lpstrFile,".p4p")) strcat(name,".p4p");

					fp = fopen(name, "wb");
					fwrite(Pack,cnt,1,fp);
					fclose(fp);
					strcpy (currentfile,name);
					ShowFilename();
					}
				}
				//delete(name);
}

void Save()
{
int cnt=0;

while (cnt<EntriesCount*CellSize&&nGet(cnt)!=0)
{
	cnt+=CmdDesc[nGet(cnt)].FSize;
}
cnt++;

				FILE *fp;

				if (currentfile[0]!=0) 
				{
					//strcpy (ofn.lpstrFile,currentfile);
					if (NULL==strstr(currentfile,".p4p")) strcat(currentfile,".p4p");
					fp = fopen(currentfile, "wb");
					fwrite(Pack,cnt,1,fp);
					fclose(fp);
				}
				else
				{
				SaveAs();
				}
				//delete(name);
}

#include "avi.h"

void SaveAvi()
{
int cnt;

				FILE *fp;
				//char* name;name=new char[100];
				char name[300];
				OPENFILENAME ofn;
			    char szFile[100] = "\0"; 
				char ttt[100]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "avi file\0*.avi\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 
				if (GetSaveFileName(&ofn)!=TRUE)
				{

				return;			

				}
				

				strcpy(name,ofn.lpstrFile);
				if (NULL==strstr(ofn.lpstrFile,".avi")) strcat(name,".avi");

	
HDC hdcscreen=GetDC(0), hdc=CreateCompatibleDC(hdcscreen); ReleaseDC(0,hdcscreen);
BITMAPINFO bi; ZeroMemory(&bi,sizeof(bi)); BITMAPINFOHEADER &bih = bi.bmiHeader;
bih.biSize=sizeof(bih);
bih.biWidth=screen_width;
bih.biHeight=screen_height;
bih.biPlanes=1;
bih.biBitCount=24;
bih.biCompression=BI_RGB;
bih.biSizeImage = ((bih.biWidth*bih.biBitCount/8+3)&0xFFFFFFFC)*bih.biHeight;
bih.biXPelsPerMeter=10000;
bih.biYPelsPerMeter=10000;
bih.biClrUsed=0;
bih.biClrImportant=0;
void *bits; 

HBITMAP hbm2=CreateDIBSection(hdc,(BITMAPINFO*)&bih,DIB_RGB_COLORS,&bits,NULL,NULL);

camstate=1;

int j=0; int tc=0;
while (CmdDesc[Get(j,0)].FRoutine!=EndDraw)
{
	if (CmdDesc[Get(j,0)].FRoutine==TimeCursor)
	{
	tc=j;
	}
	j+=CmdDesc[Get(j,0)].FSize;
}

int fr=0;

record=1;

int fps=30;
HAVI avi = CreateAvi(name,fps,NULL);

RECT SourceRect;
	SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
	LPDIRECT3DSURFACE9 RT;
	//pDevice->GetRenderTarget(0,&RT);
	pDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&RT);


int frame=0;
while (!GetAsyncKeyState(VK_ESCAPE))
{ 
fr=(int)(frame*60.0/(float)fps);
Put(tc,1,fr);
DrawScene();
			
D3DLOCKED_RECT lc;

RT->LockRect(&lc,NULL,D3DLOCK_READONLY);

	BYTE *dbits=(BYTE*)bits;
	int scw,sch;
	scw=screen_width;
	sch=screen_height;
	for (unsigned int y=0; y<sch; y++) 
	for (unsigned int x=0; x<scw; x++) 
	{
	dbits[(sch-1-y)*(int)scw*3+x*3]=*((BYTE*)lc.pBits+lc.Pitch*y+x*4);
	dbits[(sch-1-y)*(int)scw*3+x*3+1]=*((BYTE*)lc.pBits+lc.Pitch*y+x*4+1);
	dbits[(sch-1-y)*(int)scw*3+x*3+2]=*((BYTE*)lc.pBits+lc.Pitch*y+x*4+2);
	}

RT->UnlockRect();

if (frame==0) // Set up compression just before the first frame
  { AVICOMPRESSOPTIONS opts; ZeroMemory(&opts,sizeof(opts));
    opts.fccHandler=mmioFOURCC('X','V','I','D');
    SetAviVideoCompression(avi,hbm2,&opts,true,hWndView);
  }

  AddAviFrame(avi,hbm2);

  frame++;
}
//AddAviWav(avi,"wav.wav",SND_FILENAME);
j=0;tc=-1;
while (CmdDesc[Get(j,0)].FRoutine!=EndDraw)
{
	if (CmdDesc[Get(j,0)].FRoutine==LoadWave)
	{
	tc=j;
	}
	j+=CmdDesc[Get(j,0)].FSize;
}
if (tc>0)
{
char n[32];
memcpy(n,Pack+tc+256-33,32);
//AddAviWav(avi,n,SND_FILENAME);
}
CloseAvi(avi);

  DeleteObject(hbm2);
//
//SelectObject(hdc,holdb); SelectObject(hdc,holdp);
//DeleteDC(hdc); DeleteObject(hbm); DeleteObject(hp);
//delete(name);
record=0;
}

void SaveAnim()
{
if (sas==1&&afr>=afrmax) {sas=0;act=0;afr=0;return;}

//SaveImage();
afr++;

}

void CleanProject()
{

pDevice->Clear(0,NULL, D3DCLEAR_TARGET,D3DCOLOR_RGBA(0,0,0,0),8.0f,0);

		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);

for (int i=0;i<maxtex;i++)
	{
		Texture[i]->GetSurfaceLevel(0,&RT2);
//		pDevice->StretchRect(RT,NULL,RT2,NULL,(D3DTEXTUREFILTERTYPE)0);
	}


for (int i=0;i<256;i++)
	{
		ZeroMemory(&Material[i],sizeof(Material[i]));
		ZeroMemory(&Light[i],sizeof(Light[i]));
	}

for (int i=0;i<64;i++)
	{

		VBNumVerts[i]=0;
		VBNumTriangles[i]=0;
		VBNumInds[i]=0;
	}

}

void LoadTemplate()
{
			//return;
				CleanProject();

				SetCurrentDirectory(cdir);
				PrecalcStatus=0;LoopPoint=0;
				FILE *fp;
				fp = fopen("empty.p4p", "rb");
				fread(Pack,1,CellSize*EntriesCount,fp);
				fclose(fp);
				ShowParam();

}

int Load()
{
				PrecalcStatus=0;LoopPoint=0;
				FILE *fp;

			    OPENFILENAME ofn;
				char szFile[100] = "\0"; 
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "P4 DataFile\0*.p4p\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		
				// Display the Open dialog box. 
				if (GetOpenFileName(&ofn)==TRUE)
				{
				strcpy (currentfile,ofn.lpstrFile);
				fp = fopen(ofn.lpstrFile, "rb");
				fread(Pack,1,CellSize*EntriesCount,fp);
				fclose(fp);
				strcpy (currentfile,ofn.lpstrFile);
				ShowFilename();
				return 0;
				}
				return 1;
}

void SaveSample()
{
int cnt;

				FILE *fp;
				//char* name;name=new char[100];
				char name[100];
				OPENFILENAME ofn;
			    char szFile[100] = "\0"; 
				char ttt[100]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "WAV File\0*.wav\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 
				if (GetSaveFileName(&ofn)==TRUE)
				{
				strcpy(name,ofn.lpstrFile);
				if (NULL==strstr(ofn.lpstrFile,".wav")) strcat(name,".wav");
					int size;
					size=snd_samplesize*2;
					void* wav;
					
					*(snd_pool+0)='R';
					*(snd_pool+1)='I';
					*(snd_pool+2)='F';
					*(snd_pool+3)='F';
					*(snd_pool+4)=(size +44 - 8);
					*(snd_pool+8)='W';
					*(snd_pool+9)='A';
					*(snd_pool+10)='V';
					*(snd_pool+11)='E';
					*(snd_pool+12)='f';
					*(snd_pool+13)='m';
					*(snd_pool+14)='t';
					*(snd_pool+15)=0x20;
					*(int*)(snd_pool+16)=(int)16;
					*(short*)(snd_pool+20)=(short)0x0001;//pcm
					*(short*)(snd_pool+22)=(short)1;//mono
					*(int*)(snd_pool+24)=(int)44100;
					*(int*)(snd_pool+28)=(int)44100*2;//speed?
					*(short*)(snd_pool+32)=(short)2;//bytes
					*(short*)(snd_pool+34)=(short)16;//bits
					*(snd_pool+36)='d';
					*(snd_pool+37)='a';
					*(snd_pool+38)='t';
					*(snd_pool+39)='a';
					*(int*)(snd_pool+40)=(int)size;

					fp = fopen(name, "wb");
					fwrite(snd_pool,snd_samplesize*2+44,1,fp);
					fclose(fp);			

				}
				//delete(name);
}


void SaveNamedSample(char* name,BYTE* snd_ptr,int size)
{	
	FILE *fp;
	void* wav;
	*(snd_ptr+0)='R';
	*(snd_ptr+1)='I';
	*(snd_ptr+2)='F';
	*(snd_ptr+3)='F';
	*(snd_ptr+4)=(size +44 - 8);
	*(snd_ptr+8)='W';
	*(snd_ptr+9)='A';
	*(snd_ptr+10)='V';
	*(snd_ptr+11)='E';
	*(snd_ptr+12)='f';
	*(snd_ptr+13)='m';
	*(snd_ptr+14)='t';
	*(snd_ptr+15)=0x20;
	*(int*)(snd_ptr+16)=(int)16;
	*(short*)(snd_ptr+20)=(short)0x0001;//pcm
	*(short*)(snd_ptr+22)=(short)1;//mono
	*(int*)(snd_ptr+24)=(int)44100;
	*(int*)(snd_ptr+28)=(int)44100*2;//speed?
	*(short*)(snd_ptr+32)=(short)2;//bytes
	*(short*)(snd_ptr+34)=(short)16;//bits
	*(snd_ptr+36)='d';
	*(snd_ptr+37)='a';
	*(snd_ptr+38)='t';
	*(snd_ptr+39)='a';
	*(int*)(snd_ptr+40)=(int)size*2;

	fp = fopen(name, "wb");
	fwrite(snd_ptr,size*2+44,1,fp);
	fclose(fp);	
}

void SaveAllSamples()
{
int cnt;
BYTE* snd_ptr;snd_ptr=new BYTE [snd_maxsamplesize*2+44];

int samplecounter=0;


				//char* name;name=new char[100];
				char name[100];
				OPENFILENAME ofn;
			    char szFile[100] = "\0"; 
				char ttt[100]="\0";
			
				// Initialize OPENFILENAME
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = Navi;
				ofn.lpstrFile = szFile;
				ofn.nMaxFile = sizeof(szFile);
				ofn.lpstrFilter = "WAV File\0*.wav\0";
				ofn.nFilterIndex = 1;
				ofn.lpstrFileTitle = NULL;
				ofn.nMaxFileTitle = 0;
				ofn.lpstrInitialDir = NULL;
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				// Display the Open dialog box. 
				if (GetSaveFileName(&ofn)==TRUE)
				{

					int i=0;int ssz=44100*2;
					//while ((i<EntriesCount)&&(Get(i,0)!=0))
					while (i<EntriesCount*CellSize&&nGet(i)!=0)
					{

						if (CmdDesc[Get(i,0)].FRoutine==&SetSampleSize)
						{
						ssz=Get(i,1)*44100/100.0;
						}

						if (CmdDesc[Get(i,0)].FRoutine==&OutputSampleTo)
						{

							strcpy(name,ofn.lpstrFile);
							if (NULL==strstr(ofn.lpstrFile,".wav")) 
							{
								char index[22];
								_itoa(Get(i,1),index,10);
								strcat(name,index);		
								strcat(name,".wav");
							}
							else
							{
								strncpy(name,ofn.lpstrFile,strlen(ofn.lpstrFile)-5);
								*(name+strlen(ofn.lpstrFile)-4)=0;
								char index[22];
								_itoa(Get(i,1),index,10);
								strcat(name,index);		
								strcat(name,".wav");
							
							}

							MessageBox(hWnd0,name," ",0);
							memcpy(snd_ptr+44,snd_xm+Get(i,1)*snd_maxsamplesize*2,snd_maxsamplesize*2);
							SaveNamedSample(name,snd_ptr,ssz);

							samplecounter++;

						}
						i+=CmdDesc[Get(i,0)].FSize;
		
					}

						//

			

				}
delete (snd_ptr);				
}


int compilestatus=0;


//shader editor
BOOL CALLBACK ShaderEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	 switch( msg )
	 {
	 case WM_INITDIALOG:
		 {
			 break;
		 }
	 case WM_COMMAND:
		 {
			if (LOWORD(wParam)==IDC_SE)
			{
			if (HIWORD (wParam) == EN_CHANGE)  
				{
				ZeroMemory((char*)Pack+CurrentShaderPos+4,CmdDesc[nGet(CurrentShaderPos)].FSize-4);
				int n =GetDlgItemText(hDlg,IDC_SE,(char*)Pack+CurrentShaderPos+4,CmdDesc[nGet(CurrentShaderPos)].FSize-4);
				if (n==0) break;
				int result=CompileShader((char*)Pack+CurrentShaderPos+4,Get(CurrentShaderPos,1));
				if (result==0) 
					{
						SetDlgItemText(hDlg,IDC_ERR,"Compiled Ok");
						compilestatus=0;
					}
				else 
					{
						char e[1024];
						if (errv)
						{
						strncpy(e,(char*)errv->GetBufferPointer(),1000);
						char *ept;
						//ept=strstr(e,"error");
						//if (ept)
						{
						//ept=strstr(ept,": ");
						//	if (ept)
							{	
								SetDlgItemText(hDlg,IDC_ERR,e+0);
							}
						}
						compilestatus=1;

						}
					}
				} 
			break;
			}

			switch (LOWORD(wParam))
			{
			case IDOK:
				{
				ShowWindow(hDlg,SW_HIDE);
				break;
				}
			case IDCANCEL:
				{
				memcpy((char*)Pack+CurrentShaderPos+4,shaderText,65535);

				int result=CompileShader((char*)Pack+CurrentShaderPos+4,Get(CurrentShaderPos,1));
				if (result==0) 
					{
						SetDlgItemText(hDlg,IDC_ERR,"Compiled Ok");
						compilestatus=0;
					}
				else 
					{
						char e[1024];
						if (errv)
						{
						strncpy(e,(char*)errv->GetBufferPointer(),1000);
						char *ept;
						ept=strstr(e,"error");
						if (ept) 
							{
							ept=strstr(e,": ");
							if (ept) 
								{
								SetDlgItemText(hDlg,IDC_ERR,ept+2);
								}
							}
						compilestatus=1;
						}
					}

				ShowWindow(hDlg,SW_HIDE);
				break;
				}
			case IDC_ERR:
				{
					if (compilestatus==0) break;
						char e[1024];
						strncpy(e,(char*)errv->GetBufferPointer(),1000);
						char *ept;
						char *ep;
						ep=e;
					rs:
						ept=strstr(ep,"memory(");
						if (!ept) break;
						char *pt,*pt2;
						pt2=strstr(ept+7,": ");
						if (!pt2) break;
						if (*(pt2+2)!='e') 
							{
								ep=pt2;
								goto rs;
							}
						pt=strstr(ept+7,",");
						if (!pt) break;
						char line[10];
						memcpy(line,ept+7,pt-(ept+7));
						line[pt-(ept+7)]=0;
						int el=atoi(line)-1;
						int el1=SendDlgItemMessage(hDlg,IDC_SE,EM_LINEINDEX,el,0);
						int el2=SendDlgItemMessage(hDlg,IDC_SE,EM_LINEINDEX,el+1,0);
						SendDlgItemMessage(hDlg,IDC_SE,EM_SETSEL,el1,el2-2);
						SendDlgItemMessage(hDlg,IDC_SE,EM_SCROLLCARET ,0,0);
						break;
				}
			case IDC_SHLOAD:
				{
				LoadShader((char*)Pack+CurrentShaderPos+4);
				SetDlgItemText(Shad,IDC_SE,(char*)Pack+CurrentShaderPos+4);
				SetDlgItemText(Shad,IDC_ERR," ");

				int result=CompileShader((char*)Pack+CurrentShaderPos+4,Get(CurrentShaderPos,1));
				if (result==0) 
					{
						SetDlgItemText(hDlg,IDC_ERR,"Compiled Ok");
						compilestatus=0;
					}
				else 
					{
						char e[1024];
						if (errv)
						{
						strncpy(e,(char*)errv->GetBufferPointer(),1000);
						char *ept;
						ept=strstr(e,"error");
						if (ept) 
							{
							ept=strstr(e,": ");
							if (ept) 
								{
								SetDlgItemText(hDlg,IDC_ERR,ept+2);
								}
							}
						compilestatus=1;
						}
					}
				
				break;
				}

			case IDC_SHSAVE:
				{
				int n =GetDlgItemText(hDlg,IDC_SE,(char*)Pack+CurrentShaderPos+4,CmdDesc[nGet(CurrentShaderPos)].FSize-4);
				if (n!=0) SaveShader((char*)Pack+CurrentShaderPos+4,n);
				break;
				}
			}
		}
	 }
return 0;
}

//renamer
BOOL CALLBACK RenameProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	 switch( msg )
	 {
	 case WM_INITDIALOG:
		 {
			 memcpy(t,Pack+Pos+256-33,33);
			 SetDlgItemText(hDlg,IDC_RENAMEITEM,t);
			 SetFocus(GetDlgItem(hDlg,IDC_RENAMEITEM));
			 RECT r;
			 GetWindowRect(Navi2,&r);
			 SetWindowPos(hDlg,0,r.left,r.top+44,r.right-r.left,r.bottom-r.top,SW_SHOW);
			 break;
		 }
	 case WM_COMMAND:
		 {
			switch (LOWORD(wParam))
			{
			case IDOK:
				{
				GetDlgItemText(hDlg,IDC_RENAMEITEM,t,32);
				memcpy(Pack+Pos+256-33,t,32);
				EndDialog(hDlg,TRUE);
				}
			}
		}
	 }
return 0;
}

int param123Mode;

void setParam123ToPos() {
	strcpy(param123[0],"x");
	strcpy(param123[1],"y");
	strcpy(param123[2],"z");
param123Mode=0;
}

void setParam123ToSize() {
	strcpy(param123[0],"xsize");
	strcpy(param123[1],"ysize");
	strcpy(param123[2],"zsize");
	param123Mode=1;
}
void NaviInit()
{
param123[0]=new char[32];
param123[1]=new char[32];
param123[2]=new char[32];
setParam123ToPos();

	RECT rect,rect2;
	rect.left=(GetSystemMetrics(SM_CXSCREEN)-screen_width)/2-64;
	rect.top=(GetSystemMetrics(SM_CYSCREEN)-screen_height)/2.2;
	rect.right=(GetSystemMetrics(SM_CXSCREEN)-screen_width)/2-64+screen_width;
	rect.bottom=(GetSystemMetrics(SM_CYSCREEN)-screen_height)/2.2+screen_height;
	rect2=rect;


	rect.left=(GetSystemMetrics(SM_CXSCREEN)-screen_width/2)/2;
	rect.top=(GetSystemMetrics(SM_CYSCREEN)-screen_height/2)/2;
	rect.right=(GetSystemMetrics(SM_CXSCREEN)-screen_width/2)/2+screen_width/2;
	rect.bottom=(GetSystemMetrics(SM_CYSCREEN)-screen_height/2)/2+screen_height/2;

	AdjustWindowRect(&rect,WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,FALSE);

//	MoveWindow(hWnd,rect.left, rect.top,rect.right-rect.left,rect.bottom-rect.top,TRUE);
	MoveWindow(hWndView,896, 64,rect.right-rect.left,rect.bottom-rect.top,TRUE);
//	MoveWindow(hWnd1,rect.right-rect.left+96, 64,GetSystemMetrics(SM_CXSCREEN)-(rect.right-rect.left+96),rect.bottom-rect.top,TRUE);
	//ShowWindow(hWnd1,SW_SHOW);
//	ShowWindow(hWnd1,SW_HIDE);

			D3DXMATRIX WorldMatrix,TransMatrix;
			WorldMatrix=View3;
			D3DXMatrixTranslation(&TransMatrix,-.75,.25,0);
			D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&TransMatrix);
			View3=WorldMatrix;

	//SelfLocate();
			static DLGPROC lpfnDlgProcS;
	   		lpfnDlgProcS = (DLGPROC)MakeProcInstance((FARPROC)ShaderEditProc, hInst);
			Shad = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SHADEREDIT),hWnd0, lpfnDlgProcS); 

			//SetWindowPos(Shad,HWND_TOP,20,70,57,680,SWP_SHOWWINDOW);
			ShowWindow(Shad,SW_HIDE);
			UpdateWindow(Shad);


			static DLGPROC lpfnDlgProc1;
	   		lpfnDlgProc1 = (DLGPROC)MakeProcInstance((FARPROC)PEditProc, hInst);
			Navi = CreateDialog(hInst, MAKEINTRESOURCE(IDD_NAVI),hWnd0, lpfnDlgProc1); 
			
			//SetWindowPos(Navi,HWND_TOP,20,70,57,680,SWP_SHOWWINDOW);
			ShowWindow(Navi,SW_SHOW);
			UpdateWindow(Navi);

		//окно редактировани€ команд и параметров
			
			static DLGPROC lpfnDlgProc2;
	   		lpfnDlgProc2 = (DLGPROC)MakeProcInstance((FARPROC)PEditProc2, hInst);
			Navi2 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_NAVI1),hWnd0, lpfnDlgProc2); 
			//WS_TABSTOP
			//SetWindowLong(Navi,GWL_STYLE, WS_TABSTOP);

	//		SetWindowPos(Navi,HWND_TOP,screen_width+6,0,256,screen_height,SWP_SHOWWINDOW);
	SetWindowPos(Navi2,
					HWND_TOP,
					GetSystemMetrics(SM_CXSCREEN)-256,
					70,
					210,
					485,
					SWP_SHOWWINDOW);

			ShowWindow(Navi2,SW_SHOW);
			UpdateWindow(Navi2);
	
			currentfile[0]=0;
			LoadTemplate();//грузим файл-шаблон
			ShowParam();
			SendDlgItemMessage(Navi,IDC_STACK,LB_SETSEL,TRUE,Pos);	
			WriteUndoStage();



			if (GetSystemMetrics(SM_CXSCREEN)>screen_width*1.5) {
					VNaviMode*=-1;
					
					if (VNaviMode==1) ShowWindow(hWnd1,SW_SHOW);
					else ShowWindow(hWnd1,SW_HIDE);

			}

}

void UpItem()
{

WriteUndoStage();

				int cmdsize,prevcmdsize;
				int i=VNaviScene;
				int ix=GetIndexFromPos(i);
				int previ=i;
				int previx=ix;

				int a;


				if (SelBuffer[ix+1]==1) return;

				while (nGet(i)!=0)
				{
					if (CmdDesc[nGet(i)].FRoutine==Scene&&i!=VNaviScene) break;
					
					if (SelBuffer[ix]==1)
					{
						cmdsize=CmdDesc[nGet(i)].FSize;
						prevcmdsize=CmdDesc[nGet(previ)].FSize;
						memmove(Exchange,Pack+previ,prevcmdsize);
						memmove(Exchange+prevcmdsize,Pack+i,cmdsize);
						memmove(Pack+previ,Exchange+prevcmdsize,cmdsize);
						memmove(Pack+previ+cmdsize,Exchange,prevcmdsize);
						a=SelBuffer[previx];		
						SelBuffer[previx]=SelBuffer[ix];		
						SelBuffer[ix]=a;		

						previ=i-prevcmdsize+cmdsize;
						previx=ix;
						i+=cmdsize;
						ix++;

					} else
					{
						previ=i;
						previx=ix;
						i+=CmdDesc[nGet(i)].FSize;
						ix++;
					}
				}

				int k=GetIndexFromPos(VNaviScene);
				
				while (k<EntriesCount)
				{
					if (SelBuffer[k]==1) {Pos=GetPosFromLocalIndex(0,k);break;}
					k++;
				}

				

				ShowParam();
}

void DownItem()
{
WriteUndoStage();

				int cmdsize,nextcmdsize;
				int i=VNaviScene;
				int ix=GetIndexFromPos(i);
				int nexti=i;
				int nextix=ix;

				int a;

				int k=0;int t=0;
				int pt[EntriesCount];
				int se=0;
				
				while (nGet(k)!=0)
				{	
					pt[t]=k;
					k+=CmdDesc[nGet(k)].FSize;
					t++;
				}

				se=t;

				if (SelBuffer[se-1]==1) return;


				for (int m=se-1;m>=0;m--)
				{
					if (SelBuffer[m]==1)
					{
						cmdsize=CmdDesc[nGet(pt[m])].FSize;
						nextcmdsize=CmdDesc[nGet(pt[m+1])].FSize;
						memmove(Exchange,Pack+pt[m],cmdsize);
						memmove(Exchange+cmdsize,Pack+pt[m+1],nextcmdsize);
						memmove(Pack+pt[m]+nextcmdsize,Exchange,cmdsize);
						memmove(Pack+pt[m],Exchange+cmdsize,nextcmdsize);
						a=SelBuffer[m+1];		
						SelBuffer[m+1]=SelBuffer[m];		
						SelBuffer[m]=a;		
					}
				}

				k=GetIndexFromPos(VNaviScene);
				while (k<EntriesCount)
				{
					if (SelBuffer[k]==1) {Pos=GetPosFromLocalIndex(0,k);break;}
					k++;
				}
				ShowParam();
}


//Universal command log&parameter-edit window proc
BOOL CALLBACK PEditProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

	 switch( msg )
	 {
	 case WM_KEYDOWN:
		{
		short int k;
		break;
		}
	case WM_RBUTTONUP:
		{
		break;
		}


	case WM_COMMAND:
		{
			int rs;
		
			if (LOWORD(wParam)==IDC_LIGHT||
				LOWORD(wParam)==IDC_2D||
				LOWORD(wParam)==IDC_3D||
				LOWORD(wParam)==IDC_FILTERS||
				LOWORD(wParam)==IDC_RGB||
				LOWORD(wParam)==IDC_ALPHA||
				LOWORD(wParam)==IDC_CMD||
				LOWORD(wParam)==IDC_TEXT||
				LOWORD(wParam)==IDC_TEXGEN||
				LOWORD(wParam)==IDC_ANIMA||
				LOWORD(wParam)==IDC_CAM||
				LOWORD(wParam)==IDC_XYZ||
				LOWORD(wParam)==IDC_UV||
				LOWORD(wParam)==IDC_TC||
				LOWORD(wParam)==IDC_SCN||
				LOWORD(wParam)==IDC_SND||
				LOWORD(wParam)==IDC_DYNA||
				LOWORD(wParam)==IDC_TRACK||
				LOWORD(wParam)==IDC_SFILTERS||
				LOWORD(wParam)==IDC_SELECTION)
			{
				SetFocus(GetDlgItem(Navi,IDC_STACK));
			//WriteUndoStage();
			int c;
				RECT rect;POINT pt;
				GetWindowRect(GetDlgItem(Navi,LOWORD(wParam)),&rect);
				pt.x = rect.right;
				pt.y = rect.top - 2;

				HMENU hMenu;
				hMenu = CreatePopupMenu();

				int j;

				for (j=1;j<CommandsCount;j++)
					{
					if (CmdDesc[j].FCategory==LOWORD(wParam)) 
						AppendMenu(hMenu,MF_STRING,2000+j,CmdDesc[j].FName);
					}
				for (int s=1;s<64;s++)
				{
				char tstr[4],tstr2[3];
				strncpy(tstr,vsname[s],3);tstr[3]=0;
				strncpy(tstr2,vsname[s],2);tstr2[2]=0;
				if ((!strcmp(tstr,"obj")&&LOWORD(wParam)==IDC_3D)||
				    (!strcmp(tstr,"xyz")&&LOWORD(wParam)==IDC_XYZ)||
					(!strcmp(tstr,"sel")&&LOWORD(wParam)==IDC_SELECTION)||
					(!strcmp(tstr2,"uv")&&LOWORD(wParam)==IDC_UV))
					{
						AppendMenu(hMenu,MF_STRING,2000+CommandsCount+s,vsname[s]);
					}
				}
				c=TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x-32, pt.y+24, 0, Navi, NULL);
				
				if (c!=0)
				{
					WriteUndoStage();

					c=c-2000;


					
					//??
					int t=1+2;
					for (j=1;j<CommandsCount;j++)
					{
					if (CmdDesc[j].FCategory==1) 
						{
						if (c==t) {c=j;goto xx;}
						t++;
						}
					}
					xx:;
					//
					int shn;
					shn=0;
					if (c>=CommandsCount) {
						shn=c-CommandsCount;
						c=ShaderPostIndex;
						}
			
						memmove(Pack+Pos+CmdDesc[nGet(Pos)].FSize+CmdDesc[c].FSize,
								Pack+Pos+CmdDesc[nGet(Pos)].FSize,
								EntriesCount*CellSize-Pos-CmdDesc[nGet(Pos)].FSize-CmdDesc[c].FSize);

						Pos+=CmdDesc[nGet(Pos)].FSize;


						ZeroMemory(Pack+Pos,CmdDesc[c].FSize);
						nPut(Pos,c);

					if (shn>0) {
						Put(Pos,1,shn);
						}

						//UPDATE MIXER AND SINANIM
						//int CSPos=0;int jj=Pos;
						//while (jj>0&&CmdDesc[Get(jj,0)].FRoutine!=Scene) jj--;
						//CSPos=jj;
						//for (int ii=Pos;ii<EntriesCount;ii++)
						//{
						//if (CmdDesc[Get(ii,0)].FRoutine==Scene||Get(ii,0)==0) goto sq2;
						/*if (CmdDesc[Get(ii,0)].FRoutine==Mixer) 
							{
							if ((Pos-CSPos)<=Get(ii,1)) Put(ii,1,Get(ii,1)+1);
							if ((Pos-CSPos)<=Get(ii,2)) Put(ii,2,Get(ii,2)+1);
							}
							*/
						//}
						sq2:;
						DeselectAll();
						SelBuffer[GetIndexFromPos(Pos)]=1;

						ShowParam();
				}
				// ”ничтожаем меню
				DestroyMenu(hMenu);
			 }

			switch (LOWORD(wParam))
			{
		case IDC_PLAY2:
				{
				astate=1;

					start_time=GetCounter();
					start_ptime=ptime;
				if (useWave==1)
				{
					PlayWave();
				}
				else
				{
				if (ptime==0) 
					{
					FMUSIC_PlaySong(mod);
					}
				}

				camstate=1;

				break;
				}

			case IDC_PAUSE2:
				{
				astate=-1;
				
				if (useWave==1)
				{
					StopWave();
				}
				else
				{
				FMUSIC_StopSong(mod);
				}
				break;
				}

			case IDC_STOP2:
				{camstate=-1;
				astate=-1;
				if (useWave==1)
				{
					StopWave();
				}
				else
				{
				FMUSIC_StopSong(mod);
				}
				int i=0;
				while (Get(i,0)!=0||CmdDesc[Get(i,0)].FRoutine!=&EndDraw)
					{
						if (CmdDesc[Get(i,0)].FRoutine==&TimeCursor) 
						{
						Put(i,1,0);
						*(short*)(RExchange+i+1*2)=0;
						ShowParam();
						
						break;
						}
						i+=CmdDesc[Get(i,0)].FSize;
					}

				break;
				}
		

		

		

			case IDC_UP:
				{
				UpItem();
				break;
				}

			case IDC_DOWN:
				{
				DownItem();
				break;
				}


		

			
			}
		break;
		}


		case WM_MOVE:
		break;

		case WM_SIZE:
		break;

	 }		 

return 0;
}


BOOL CALLBACK PEditProc2(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

	 switch( msg )
	 {
//		case WM_NCHITTEST:
//		{
//		LRESULT lRes = DefWindowProc(hDlg, WM_NCHITTEST, wParam, lParam);
//		if (lRes == HTCLIENT)
//			lRes = HTCAPTION;
//		return lRes;
//		}

	 case WM_MOUSEWHEEL:
		 {
			 int fwKeys = LOWORD(wParam);    // key flags
			 int zDelta = (short) HIWORD(wParam);    // wheel rotation
			 if (zDelta>0) zDelta=1; else zDelta=-1;

			 if (fwKeys ==  MK_CONTROL) zDelta*=10;
			 if (fwKeys ==  MK_SHIFT) zDelta*=100;
			 
			 if (HIWORD(GetKeyState(VK_SHIFT))>0&&HIWORD(GetKeyState(VK_CONTROL))>0) zDelta*=1000;

			 int rs;

			 for (int n=1;n<CpW+1;n++) 
				{
					if (GetFocus()==GetDlgItem(Navi2,IDC_EDIT_P0+n-1))
						{
						   Put(Pos,n+PPage*CpW,(GetDlgItemInt(Navi2,IDC_EDIT_P0+n-1,&rs,TRUE))+zDelta);
						   SetDlgItemInt(Navi2,IDC_EDIT_P0+n-1,Get(Pos,n+PPage*CpW),TRUE);
						   

						}
				}
			 ShowParam();
			break;
		 }
	case WM_COMMAND:
		{
			int rs;

			if (LOWORD(wParam)>=IDC_EDIT_P0&&LOWORD(wParam)<=IDC_EDIT_P21)
			{
			if (HIWORD (wParam) == EN_CHANGE)  
				{
				for (int n=1;n<=CpW;n++) 
				{
					if (GetFocus()==GetDlgItem(Navi2,IDC_EDIT_P0+n-1))
					{
						   if (!strcmp(CmdDesc[Get(Pos,0)].FParamName[n+PPage*CpW],"rgb"))
						   {
								int b,c;char a;
								char toh[10];
								ZeroMemory(toh,8);
								GetDlgItemText(Navi2,IDC_EDIT_P0+n-1, toh,9);
								c=0;
								for (int i=0;i<8;i++)
								{
									a=*(toh+i);
									if (a==' ') 	b=0;
									if (a==0) 	b=0;
									if (a>='0' && a<='9') 	b=a-'0';
									if (a>='A' && a<='F') 	b=a-'A'+10;
									if (a>='a' && a<='f') 	b=a-'a'+10;
									c=c|(b<<((7-i)*4));
								}
								Put32(Pos,n+PPage*CpW,c);
						   }
						   else
						   {
								Put(Pos,n+PPage*CpW,(GetDlgItemInt(Navi2,IDC_EDIT_P0+n-1,&rs,TRUE)));

							   if (CmdDesc[Get(Pos,0)].FRoutine==TimeCursor&&n==1) 
							   {
						   		start_time=GetCounter();
								if (Get(Pos,1)>=0) start_ptime=Get(Pos,1); else start_ptime=0;
							   }
						   }
					}
				}

				break;
				}
			}

			if (LOWORD(wParam)>=IDC_EN0&&LOWORD(wParam)<=IDC_EN21)
			{
			WriteUndoStage();
			int c;
				RECT rect;POINT pt;
				GetWindowRect(GetDlgItem(Navi2,LOWORD(wParam)),&rect);
				pt.x = rect.left + 22;
				pt.y = rect.top - 2;

				HMENU hMenu;
				hMenu = CreatePopupMenu();

				int j;

				for (j=0;j<64;j++)
					{
						if (CmdDesc[Get(Pos,0)].FParamEnum[1+PPage*CpW+LOWORD(wParam)-IDC_EN0][j][0]!=0) 
						{
						AppendMenu(hMenu,((16*((int)j/16)==j&&j!=0)*MF_MENUBARBREAK)|MF_STRING,2000+j,CmdDesc[Get(Pos,0)].FParamEnum[1+PPage*CpW+LOWORD(wParam)-IDC_EN0][j]);
						}
					}
				c=TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x-22, pt.y, 0, Navi2, NULL);
				
				if (c!=0) Put(Pos,1+PPage*CpW+LOWORD(wParam)-IDC_EN0,c-2000);

				ShowParam();
				
				// ”ничтожаем меню
				DestroyMenu(hMenu);			
			}


			switch (LOWORD(wParam))
			{

			case IDC_PF:
				{
				//if (PPage<15) PPage++;
				ShowParam();
				break;
				}

			case IDC_PB:
				{
				//if (PPage>0) PPage--;
				ShowParam();
				break;
				}

			case IDC_RENAME:
				{
				WriteUndoStage();
				DialogBox(hInst,MAKEINTRESOURCE(IDD_RENAME),Navi,RenameProc);
				break;
				}

			break;
			}


		case WM_MOVE:
		break;

		case WM_SIZE:
		break;

	 }		
		}

return 0;
}

//gui function!!!!
void NaviBox(int _x,int _y,int _w,int _h,int r,int g,int b)
{

int vbi;
vbi=CPos;
int objectX,objectY,objectZ;

	double x,y,z,w,h;
	objectX=x=_x/1000.0;
	objectY=y=_y/1000.0;
	objectZ=z=0;
	w=_w/1000.0;
	//h=50/1000.0;
	h=_h/1000.0;


	pVerts[0].x=x;pVerts[0].y=y-h/2.0;pVerts[0].z=z;
	pVerts[1].x=x+w;pVerts[1].y=y-h/2.0;pVerts[1].z=z;
	pVerts[2].x=x+w;pVerts[2].y=y+h/2.0;pVerts[2].z=z;
	pVerts[3].x=x;pVerts[3].y=y+h/2.0;pVerts[3].z=z;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

 int argb=D3DCOLOR_RGBA(r,g,b,0);

	pVerts[0].color=argb;
	pVerts[1].color=argb;
	pVerts[2].color=argb;
	pVerts[3].color=argb;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;

//	pDevice->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_ARGB(0,r,g,b));

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetAlfa(0);

		pDevice->SetTexture(0,NULL);
	SetMaterial(&WhiteMaterial);


	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

//FlatNormals();
//	ApplyMods();

			//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			//	FillVB(0);
			//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	//pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	//pDevice->SetIndices(pIB[0]);
	
	

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, NumVerts,NumTriangles, pInds,D3DFMT_INDEX32,pVerts,sizeof(MyVertex) );

	//pDevice->SetPixelShader(NULL);

}

void NText(char* in,float tracking,int inx, int iny,int inwh)
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

int vbi;
vbi=CPos;
int objectX,objectY,objectZ;

	double x,y,z,w,h;int r,g,b;
	objectX=x=width*inx/1000.0;
	objectY=y=height*iny/1000.0+1/256.0-.5/screen_height;
	objectZ=z=0;
	w=width*inwh/1000.0;
	h=height*inwh/1000.0;

	//y=((int)(y*screen_height))/screen_height;
	//x=(int)(x*screen_width)/screen_width;

	pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,2);
	pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,2);

int ti;float ofsx;
ofsx=0;
int ssz=strlen(in);;
for (ti=0;ti<ssz;ti++)
{
	int letter;
	//letter=*(BYTE*)(Pack+CPos*CellSize+256-33+ti);
	letter=*(BYTE*)(in+ti);
	if (letter==0) {goto q;}
	letter-=32;

	lastletterx=1000*(w/2.0+ofsx);
	pVerts[ti*4+0].x=x-w/2.0+ofsx;pVerts[ti*4+0].y=y+h/2.0;pVerts[ti*4+0].z=z;
	pVerts[ti*4+1].x=x+w/2.0+ofsx;pVerts[ti*4+1].y=y+h/2.0;pVerts[ti*4+1].z=z;
	pVerts[ti*4+2].x=x+w/2.0+ofsx;pVerts[ti*4+2].y=y-h/2.0;pVerts[ti*4+2].z=z;
	pVerts[ti*4+3].x=x-w/2.0+ofsx;pVerts[ti*4+3].y=y-h/2.0;pVerts[ti*4+3].z=z;

	ofsx=ofsx+w*((float)FontPTable[letter])/32.0+tracking/1000;

	int laddr_u,laddr_v;
	float fladdr_u,fladdr_v,qs;

	laddr_u= letter/16;
	laddr_v= letter-laddr_u*16;
	fladdr_u=laddr_u*32/512.0;
	fladdr_v=laddr_v*32/512.0;
	qs=32.0/512.0;

			pVerts[ti*4+0].u=fladdr_u;pVerts[ti*4+0].v=fladdr_v;
			pVerts[ti*4+1].u=fladdr_u+qs;pVerts[ti*4+1].v=fladdr_v;
			pVerts[ti*4+2].u=fladdr_u+qs;pVerts[ti*4+2].v=fladdr_v+qs;
			pVerts[ti*4+3].u=fladdr_u;pVerts[ti*4+3].v=fladdr_v+qs;


    int argb=D3DCOLOR_RGBA(0,0,0,0);

	pVerts[ti*4+0].color=argb;
	pVerts[ti*4+1].color=argb;
	pVerts[ti*4+2].color=argb;
	pVerts[ti*4+3].color=argb;

	pInds[ti*6+0]=ti*4+0;pInds[ti*6+1]=ti*4+1;pInds[ti*6+2]=ti*4+2;
	pInds[ti*6+3]=ti*4+0;pInds[ti*6+4]=ti*4+2;pInds[ti*6+5]=ti*4+3;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	pDevice->SetTexture(0,FontTexture);

	//pDevice->SetMaterial(&WhiteMaterial);
			
		SetAlfa(6);
	
	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);
}
q:;
	NumVerts=4*ti;
	NumInds=6*ti;
	NumTriangles=2*ti;

//FlatNormals();

				//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
		//	ApplyMods();	
			//		FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	//pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	//pDevice->SetIndices(pIB[0]);
	
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, NumVerts,NumTriangles, pInds,D3DFMT_INDEX32,pVerts,sizeof(MyVertex) );
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &View);
}


void NTextLen(char* in,float tracking,int inx, int iny,int inwh)
{

int vbi;
vbi=CPos;
int objectX,objectY,objectZ;

	double x,y,z,w,h;int r,g,b;
	objectX=x=width*inx/1000.0;
	objectY=y=height*iny/1000.0+1/256.0-.5/screen_height;
	objectZ=z=0;
	w=width*inwh/1000.0;
	h=height*inwh/1000.0;

	y=((int)(y*screen_height))/screen_height;
	x=(int)(x*screen_width)/screen_width;

int ti;float ofsx;
ofsx=0;
int ssz=strlen(in);;
for (ti=0;ti<ssz;ti++)
{
	int letter;
	letter=*(BYTE*)(in+ti);
	if (letter==0) {goto q;}
	letter-=32;
	lastletterx=1000*(w/2.0+ofsx);
	ofsx=ofsx+w*((float)FontPTable[letter])/32.0+tracking/1000;
}
q:;

}


void iSphere(float _x,float _y, float _z, float _sz)
{
if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_ALPHA|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_RED);

	double a,b,x,y,z,xs,ys,zs;int d,k,tx,ty,texture,material;
float objectX,objectY,objectZ;
	objectX=x=_x;
	objectY=y=_y;
	objectZ=z=_z;
	xs=width*_sz;
	ys=height*_sz;
	zs=_sz;
	//zs=0;
//	texture=Get(CPos,7);
//	material=Get(CPos,8);
	greedx=12;
	greedy=6;
	SetAlfa(0);

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
		k++;
		}
	}

	CalcIndicies();

	NumVerts=(greedx+1)*(greedy+1);//чтобы не паритьс€ с заворотом посчитали 360 включительно
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;
	
//	pDevSetTexture(0,texture,0);
	
//	SetMaterial(&Material[material]);
	
	
	//ApplyMods();

	Svertka2Normals();

	FillVB(0);
					
//draw

	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);	

pDevice->SetPixelShader(NULL);
pDevice->SetVertexShader(NULL);


	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		

	SetAlfa(0);
if (height!=width) SetView(0);//pDevice->SetTransform(D3DTS_VIEW, &View);
}

void TFlat(int inx,int iny, int fw,int fh)
{
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;



if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double x,y,z,w,h;int r,g,b;
	objectX=x=inx/1000.0;
	objectY=y=iny/1000.0;
	objectZ=z=0;
	//w=width*fw/1000.0*screen_height/screen_width;
	w=width*fw/1000.0;//*screen_ratio;
	h=-height*fh/1000.0;



	pVerts[0].x=x-w/2.0;pVerts[0].y=y-h/2.0;pVerts[0].z=z;
	pVerts[1].x=x+w/2.0;pVerts[1].y=y-h/2.0;pVerts[1].z=z;
	pVerts[2].x=x+w/2.0;pVerts[2].y=y+h/2.0;pVerts[2].z=z;
	pVerts[3].x=x-w/2.0;pVerts[3].y=y+h/2.0;pVerts[3].z=z;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	pVerts[0].color=0x00ffffff;
	pVerts[1].color=0x00ffffff;
	pVerts[2].color=0x00ffffff;
	pVerts[3].color=0x00ffffff;

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;


	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);

	//pDevice->SetTexture(0,Texture[Get(CPos,6)]);

	//pDevice->SetMaterial(&Material[Get(CPos,7)]);
	
		
	//SetAlfa(Get(CPos,9));
	

	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

greedx=1;greedy=1;
FlatNormals();

			//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			//ApplyMods();	
					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &View);
}

void TFlatMt(int inx,int iny, int fw,int fh,D3DMATERIAL9 mt)
{
int vbi;
vbi=CPos;
int objectX,objectY,objectZ;



if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix);

	double x,y,z,w,h;int r,g,b;
	objectX=x=inx/1000.0;
	objectY=y=iny/1000.0;
	objectZ=z=0;
	w=width*fw/1000.0;//*screen_height/screen_width;
	h=-height*fh/1000.0;



	pVerts[0].x=x-w/2.0;pVerts[0].y=y-h/2.0;pVerts[0].z=z;
	pVerts[1].x=x+w/2.0;pVerts[1].y=y-h/2.0;pVerts[1].z=z;
	pVerts[2].x=x+w/2.0;pVerts[2].y=y+h/2.0;pVerts[2].z=z;
	pVerts[3].x=x-w/2.0;pVerts[3].y=y+h/2.0;pVerts[3].z=z;

			pVerts[0].u=0;pVerts[0].v=0;
			pVerts[1].u=1;pVerts[1].v=0;
			pVerts[2].u=1;pVerts[2].v=1;
			pVerts[3].u=0;pVerts[3].v=1;

	pVerts[1].color=D3DCOLOR_RGBA((int)(255*mt.Specular.r),(int)(255*mt.Specular.g),(int)(255*mt.Specular.b),0);
	pVerts[0].color=D3DCOLOR_RGBA((int)(255*mt.Diffuse.r),(int)(255*mt.Diffuse.g),(int)(255*mt.Diffuse.b),0);
	pVerts[2].color=D3DCOLOR_RGBA((int)(255*mt.Diffuse.r),(int)(255*mt.Diffuse.g),(int)(255*mt.Diffuse.b),0);
	pVerts[3].color=D3DCOLOR_RGBA((int)(255*mt.Ambient.r),(int)(255*mt.Ambient.g),(int)(255*mt.Ambient.b),0);

	pInds[0]=0;pInds[1]=1;pInds[2]=2;
	pInds[3]=0;pInds[4]=2;pInds[5]=3;


	pDevice->SetRenderState(D3DRS_COLORVERTEX,FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL);

	//pDevice->SetTexture(0,Texture[Get(CPos,6)]);

	//pDevice->SetMaterial(&Material[Get(CPos,7)]);
	
		
	//SetAlfa(Get(CPos,9));
	

	NumVerts=4;
	NumInds=6;
	NumTriangles=2;

greedx=1;greedy=1;
FlatNormals();

			//if (VBDesc[vbi].needchangedata==0)//если в буфер не залиты данные заливаем
			//ApplyMods();	
					FillVB(0);
					
					//if (CurrentObject!=i) VBDesc[vbi].needchangedata=1;// если это не текущий ред. объект, то теперь заливка данных в буфер не нужна
				

//draw
	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	pDevice->SetIndices(pIB[0]);
	
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NumVerts, 0, NumTriangles);
	
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);

	if (height!=width) pDevice->SetTransform(D3DTS_VIEW, &View);
}


void ShowTextures()
{
if (infoview==1) return;

SetVp_(0);

pDevice->SetMaterial(&WhiteMaterial);
if (tbmflag==-1||tbmflag==1)
{
		tbmofs+=15*tbmflag;
		if (abs(tbmofs)>2*550/5)
			{
				tbmofs=0;
				tbofs+=-tbmflag;
				tbmflag=0;
				if (tbofs>255) tbofs=255;
				if (tbofs<0) tbofs=0;
			}
}


char aa[10];
for (int x=0;x<9;x++)
	{
	int tex;
	tex=x+tbofs;
	if (tex>=0&&tex<=255)
		{
		SetTexture(0,tex,0);
		SetAlfa(0);
		TFlat(-880+2*550*x/5+tbmofs,830,256,256);
		
		_itoa(tex,aa,10);
		NText(aa,-10,-880+2*550*x/5+tbmofs,980,32);

		}
	}

//textures (ind+9)
if (lowpanel==1)
{

for (int x=0;x<9;x++)
	{
	int tex;
	tex=x+tbofs+9;
	if (tex>=0&&tex<=255)
		{
		SetTexture(0,tex,0);
		SetAlfa(0);
		TFlat(-880+2*550*x/5+tbmofs,-830,256,256);
		
		_itoa(tex,aa,10);
		NText(aa,-10,-880+2*550*x/5+tbmofs,-980,32);

		}
	}

}

//double textures with alpha
if (lowpanel==0)
{

for (int x=0;x<9;x++)
	{
	int tex;
	tex=x+tbofs;
	if (tex>=0&&tex<=255)
		{
		SetTexture(0,tex,0);
		SetAlfa(6);
		TFlat(-880+2*550*x/5+tbmofs,-830,256,256);
		
		_itoa(tex,aa,10);
		NText(aa,-10,-880+2*550*x/5+tbmofs,-980,32);

		}
	}

}

//materials
if (lowpanel==2)
{

if (mbmflag==-1||mbmflag==1)
{
		mbmofs+=15*mbmflag;
		if (abs(mbmofs)>2*550/5)
			{
				mbmofs=0;
				mbofs+=-mbmflag;
				mbmflag=0;
				if (mbofs>255) mbofs=255;
				if (mbofs<0) mbofs=0;
			}
}


ZeroMemory(&TempMaterial,sizeof (D3DMATERIAL9));


for (int x=0;x<9;x++)
	{
	int tex;
	tex=x+mbofs;
	if (tex>=0&&tex<=255)
		{
		pDevice->SetTexture(0,WhiteTexture);
		SetAlfa(0);

		float mc=94;
		TempMaterial.Ambient=Material[tex].Ambient;
		pDevice->SetMaterial(&TempMaterial);
		TFlat(-880+2*550*x/5+mbmofs,-923+0*mc,256,256/3.5);
		TempMaterial.Ambient=Material[tex].Diffuse;
		pDevice->SetMaterial(&TempMaterial);
		TFlat(-880+2*550*x/5+mbmofs,-923+1*mc,256,256/3.5);
		TempMaterial.Ambient=Material[tex].Specular;
		pDevice->SetMaterial(&TempMaterial);
		TFlat(-880+2*550*x/5+mbmofs,-923+2*mc,256,256/3.5);

		_itoa(tex,aa,10);
		NText(aa,-10,-880+2*550*x/5+mbmofs,-980,32);

		}
	}

}

}

void SaveStageView(int tx)
{
RECT SourceRect,DestRect;
//pDevice->SetMaterial(&WhiteMaterial);
if (width==height)
{
SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
SetRect(&DestRect, 0, (screen_width-screen_height)/4, 512, 512-(screen_width-screen_height)/4);

		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		TextureStage[tx]->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,&DestRect,D3DTEXF_NONE);
}
else
{
SetRect(&SourceRect, vp.X, vp.Y, vp.X+vp.Width, vp.Height+vp.Y );
SetRect(&DestRect, 0, 0, 512, 512);

		LPDIRECT3DSURFACE9 RT,RT2;
		pDevice->GetRenderTarget(0,&RT);
		TextureStage[tx]->GetSurfaceLevel(0,&RT2);
		pDevice->StretchRect(RT,&SourceRect,RT2,NULL,D3DTEXF_NONE);
}
}

void ShowTexArg()
{
if (infoview==1) return;

if (stageview==0&&finalview!=1) return;
pDevice->SetMaterial(&WhiteMaterial);
SetVp_(0);

int n=1;
if (Pos==0) return;
int j;
j=-1;

			SetAlfa(7);
//			NText("current stage",-10,-940,000,32);
//			NText("current stage with alpha",-10,-940,600,32);


	for (n=1;n<20;n++)
	{
		if (strstr(CmdDesc[Get(Pos,0)].FParamName[n],"texture"))
		{
			SetAlfa(0);
			SetTexture(0,Get(Pos,n),0);
			TFlat(750,-300*j,512,512);
			
			if (j==-1) NText("first texture argument",-10,560,600,32);
			if (j==1) NText("second texture argument",-10,560,0,32);

			j=1;
		}
	}
			

}


void ShowStages()
{
if (infoview==1) return;
//if (stageview==0&&finalview!=1) return;
//if (stageview==0) return;
pDevice->SetMaterial(&WhiteMaterial);
SetVp_(0);

			SetAlfa(7);
			NText("current stage",-10,-940,000,32);
			NText("current stage with alpha",-10,-940,600,32);

			SetAlfa(0);
			pDevice->SetTexture(0,TextureStage[0]);
			TFlat(-750,-300,512,512);

			SetAlfa(6);
			pDevice->SetTexture(0,TextureStage[0]);
			TFlat(-750,300,512,512);

}

//---
void SearchSceneDown(int position)
{
int i=position;
while (i<EntriesCount*CellSize)
	{	
	if (nGet(i)==0) return;
	if (CmdDesc[nGet(i)].FRoutine==&Scene) 
		{
			VNaviScene=i;
			return;
		}
	i+=CmdDesc[Get(i,0)].FSize;
	}
}

void SearchSceneUp(int position)
{

VNaviScene=0;
int i=0;
while (i<=position)
	{	
	if (Get(i,0)==0) return;
	if (CmdDesc[nGet(i)].FRoutine==&Scene) 
		{
			VNaviScene=i;
			
		}
	i+=CmdDesc[Get(i,0)].FSize;
	}

}

void SearchScene(int scene)
{
int sccount;

sccount=0;
	
if (scene<0) return;

if (scene==0) {VNaviScene=0;return;}

int i=0;
while (i<EntriesCount*CellSize&&nGet(i)!=0)
	{	
	if (CmdDesc[nGet(i)].FRoutine==&Scene) 
	{
		sccount++;
	}
	if (sccount==scene) 
		{
		VNaviScene=i;
		return;
		}
	i+=CmdDesc[Get(i,0)].FSize;
	}
}

unsigned int linkcolor;

void ShowLink(int x,int y,int x1,int y1)
{
	pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,1);
	pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,1);

	LightsOff();
	ZBufDisable();

	if (linkcolor==0x00ffffff) SetAlfa(0); else SetAlfa(2);
	
	pVerts[0].x=x/1000.0;
	pVerts[0].y=y/1000.0;
	pVerts[0].z=0;
	pVerts[0].color=linkcolor;

	pVerts[1].x=x1/1000.0;
	pVerts[1].y=y1/1000.0;
	pVerts[1].z=0;
	pVerts[1].color=linkcolor;

	pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_COLOR1);

	SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,NULL);

	NumVerts=2;

			void * pBuf;
		
//			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
//			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
//			pVB[0]->Unlock();
					
//draw
//	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
	//pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
pDevice->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 2,1, pInds,D3DFMT_INDEX32,pVerts,sizeof(MyVertex) );


//-----
	pVerts[0].x=x1/1000.0;
	pVerts[0].y=y1/1000.0;
	pVerts[0].z=0;
	pVerts[0].color=0;

float angle;
angle=atan2((float)(x-x1),(float)(y-y1));
float x2,y2;
x2=x1+25*sin(angle+15*PI/180.0);
y2=y1+25*cos(angle+15*PI/180.0);

	pVerts[1].x=x2/1000.0;
	pVerts[1].y=y2/1000.0;
	pVerts[1].z=0;
	pVerts[1].color=linkcolor;

angle=atan2((float)(x-x1),(float)(y-y1));
x2=x1+25*sin(angle-15*PI/180.0);
y2=y1+25*cos(angle-15*PI/180.0);

	pVerts[2].x=x2/1000.0;
	pVerts[2].y=y2/1000.0;
	pVerts[2].z=0;
	pVerts[2].color=linkcolor;

	NumVerts=3;
	//SetAlfa(2);

//			pVB[0]->Lock( 0, sizeof(MyVertex) * (NumVerts), &pBuf, 0 );
//			  memcpy( pBuf, pVerts, sizeof(MyVertex) * (NumVerts));
//			pVB[0]->Unlock();

//	pDevice->SetStreamSource( 0, pVB[0], 0, sizeof(MyVertex) );
//	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 3,1, pInds,D3DFMT_INDEX32,pVerts,sizeof(MyVertex) );

	pDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,2);
	pDevice->SetSamplerState(0,D3DSAMP_MINFILTER,2);

}

int stack_h;

void ShowUsedData()
{
visualnavi=1;
int startx,starty;startx=-500;starty=200-42;
int x,y;x=startx;y=starty;
int w=240;char aa[256];char bb[256];
	
	int tex[256];int tex_y[256];
	int texcount=0;

	int mat[256];int mat_y[256];
	int matcount=0;

	int curv[256];int curv_y[256];
	int curvcount=0;

	int vb[256];int vb_y[256];
	int vbcount=0;

	int sb[256];int sb_y[256];
	int sbcount=0;


	int ystep=96;
	//int ystep=-stack_h/4;
	int color=122;

for (int i=VNaviScene+1;i<EntriesCount;i++)
	{	
	if (Get(i,0)==0) return;
	if (CmdDesc[Get(i,0)].FRoutine==&EndScene) return;
	if (CmdDesc[Get(i,0)].FRoutine==&Scene) return;

	if (i==Pos) linkcolor=0x00ffffff; else linkcolor=0;
//
	{
	int j;
	for (j=1;j<100;j++)
		{
		
		if (strstr(CmdDesc[Get(i,0)].FParamName[j],"slot"))
		{
		if (Get(i,j)<0) break;
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,j);

			for ( p=0;p<sbcount;p++)
			{
				if (a==sb[p]) {ff=1;pp=p;break;}
			}
			
			if (ff==0) 
			{				
				sb[sbcount]=a;
				sb_y[sbcount]=y;
				sbcount++;

				SetAlfa(0);
				_itoa(Get(i,j),bb,10);
				strcpy(aa,"Sample Buffer ");
				strcat(aa,bb);
				NaviBox(x-8,y+3,w-5,32+6,color,color,color);
				NText(aa,-9,x,y,28);

				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1&&
					CmdDesc[Get(i,0)].FRoutine!=&MixSample) 
					{
						ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,y+3+16);
					}
				else 
					{
						ShowLink(x-8+235,y+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
					}
				}
				
				//SetTexture(0,Get(i,j),0);SetAlfa(0);
				//TFlat(x-8-w/2-4,y+3,1024.0/768.0*(w-5)/2,(w-5)/2);
				//SetAlfa(6);
				//TFlat(x-8-w/2-4-w/2,y+3,1024.0/768.0*(w-5)/2,(w-5)/2);
				y-=w/2;
				y-=2;
				//y-=ystep;
			}
			else
			{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1&&CmdDesc[Get(i,0)].FRoutine!=&MixSample) ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,sb_y[pp]+3+16);
				else ShowLink(x-8+235,sb_y[pp]+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
			}
		
		}
		}
	}
//
	if (VNaviC==-1)
	{
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,1);

			for ( p=0;p<curvcount;p++)
			{
				if (a==curv[p]) {ff=1;pp=p;break;}
			}
			
			if (ff==0) 
			{	

			if (CmdDesc[Get(i,0)].FRoutine==&AnimaSpline)
				{
				curv[curvcount]=a;
				curv_y[curvcount]=y;
				curvcount++;

				SetAlfa(0);
				_itoa(Get(i,1),bb,10);
				strcpy(aa,"Curve ");
				strcat(aa,bb);
				NaviBox(x-8,y+3,w-5,32+6,color,color,color);
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				ShowLink(x-8+235,y+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
				NText(aa,-9,x,y,28);
				y-=ystep;
				}
			}
			else
			{
			if (CmdDesc[Get(i,0)].FRoutine==&AnimaSpline)
				{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				ShowLink(x-8+235,curv_y[pp]+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
				}
			}
	}

	if (VNaviC==-1)
	{
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,1);

			for ( p=0;p<curvcount;p++)
			{
				if (a==curv[p]) {ff=1;pp=p;break;}
			}
			
			if (ff==0) 
			{	

			if (CmdDesc[Get(i,0)].FRoutine==&StoreCurve)
				{
				curv[curvcount]=a;
				curv_y[curvcount]=y;
				curvcount++;

				SetAlfa(0);
				_itoa(Get(i,1),bb,10);
				strcpy(aa,"Curve ");
				strcat(aa,bb);
				NaviBox(x-8,y+3,w-5,32+6,color,color,color);
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,y+3+16);
				}
				NText(aa,-9,x,y,28);
				y-=ystep;
				}
			}
			else
			{
			if (CmdDesc[Get(i,0)].FRoutine==&StoreCurve)
				{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,curv_y[pp]+3+16);
				}
				}
			}
	}

	if (VNaviVB==-1)
	{
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,1);

			for ( p=0;p<vbcount;p++)
			{
				if (a==vb[p]) {ff=1;pp=p;break;}
			}
			
			if (ff==0) 
			{				
				if (CmdDesc[Get(i,0)].FRoutine==&CopyToVB||
					CmdDesc[Get(i,0)].FRoutine==&AddToVB||
					CmdDesc[Get(i,0)].FRoutine==&CleanVB||
					CmdDesc[Get(i,0)].FRoutine==&StartAddToVB||
					CmdDesc[Get(i,0)].FRoutine==&EndAddToVB)
					{
					vb[vbcount]=a;
					vb_y[vbcount]=y;
					vbcount++;

					SetAlfa(0);
					_itoa(Get(i,1),bb,10);
					strcpy(aa,"Vertex Buffer ");
					strcat(aa,bb);
					NaviBox(x-8,y+3,w-5,32+6,color,color,color);

					if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
					{
					ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,y+3+16);
					}

					NText(aa,-9,x,y,28);
					y-=ystep;
					}

				if (CmdDesc[Get(i,0)].FRoutine==&ShowVB||
					CmdDesc[Get(i,0)].FRoutine==&ShowVBs)
					{
					vb[vbcount]=a;
					vb_y[vbcount]=y;
					vbcount++;

					SetAlfa(0);
					_itoa(Get(i,1),bb,10);
					strcpy(aa,"Vertex Buffer ");
					strcat(aa,bb);
					NaviBox(x-8,y+3,w-5,32+6,color,color,color);
					
					if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
					{
					ShowLink(x-8+235,y+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
					}

					NText(aa,-9,x,y,28);
					y-=ystep;
					}
			}
			else
			{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{

				if (CmdDesc[Get(i,0)].FRoutine==&CopyToVB||
					CmdDesc[Get(i,0)].FRoutine==&AddToVB||
					CmdDesc[Get(i,0)].FRoutine==&CleanVB||
					CmdDesc[Get(i,0)].FRoutine==&StartAddToVB||
					CmdDesc[Get(i,0)].FRoutine==&EndAddToVB)
					{
					ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,vb_y[pp]+3+16);
					}

				if (CmdDesc[Get(i,0)].FRoutine==&ShowVB||
					CmdDesc[Get(i,0)].FRoutine==&ShowVBs)
					{
					ShowLink(x-8+235,vb_y[pp]+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
					}
				}
			}
	}

	if (VNaviT==-1)
	{
	int j;
	for (j=1;j<100;j++)
		{
		
		if (strstr(CmdDesc[Get(i,0)].FParamName[j],"texture"))
		{
		if (Get(i,j)==-1) break;
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,j);

			for ( p=0;p<texcount;p++)
			{
				if (a==tex[p]) {ff=1;pp=p;break;}
			}
			
			if (ff==0) 
			{				
				tex[texcount]=a;
				tex_y[texcount]=y;
				texcount++;

				SetAlfa(0);
				_itoa(Get(i,j),bb,10);
				strcpy(aa,"Texture ");
				strcat(aa,bb);
				NaviBox(x-8,y+3,w-5,32+6,color,color,color);
				NText(aa,-9,x,y,28);

				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1&&
					CmdDesc[Get(i,0)].FRoutine!=&TMixer&&
					CmdDesc[Get(i,0)].FRoutine!=&CopyAlphaFromTexture&&
					CmdDesc[Get(i,0)].FRoutine!=&ModCopyToAlphaFromTexture) 
					{
						ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,y+3+16);
					}
				else 
					{
						ShowLink(x-8+235,y+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
					}
				}
				
				SetTexture(0,Get(i,j),0);SetAlfa(0);
				TFlat(x-8-w/2-4,y+3,(w-5)/2,(w-5)/2);
				SetAlfa(6);
				TFlat(x-8-w/2-4-w/2,y+3,(w-5)/2,(w-5)/2);
				y-=w/2;
				y-=2;
				//y-=ystep;
			}
			else
			{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1&&CmdDesc[Get(i,0)].FRoutine!=&TMixer&&CmdDesc[Get(i,0)].FRoutine!=&CopyAlphaFromTexture&&CmdDesc[Get(i,0)].FRoutine!=&ModCopyToAlphaFromTexture) ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,tex_y[pp]+3+16);
				else ShowLink(x-8+235,tex_y[pp]+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
			}
		
		}
		}
	}

	if (VNaviM==-1)
	{int j;
	for (j=1;j<100;j++)
	{
		if (strstr(CmdDesc[Get(i,0)].FParamName[j],"material")||strstr(CmdDesc[Get(i,0)].FParamName[j],"Material"))
		{
		if (Get(i,j)==-1) break;
			int p;int pp;
			int ff;ff=0;
			int a;
			a=Get(i,j);

			for ( p=0;p<matcount;p++)
			{
				if (a==mat[p]) {ff=1;pp=p;break;}
			}
			
			

			if (ff==0) 
			{	
				mat[matcount]=a;
				mat_y[matcount]=y;
				matcount++;

				SetAlfa(0);
				_itoa(Get(i,j),bb,10);
				strcpy(aa,"Material ");
				strcat(aa,bb);
				NaviBox(x-8,y+3,w-5,32+6,color,color,color);
				NText(aa,-9,x,y,28);
				
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1) ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,y+3+16);
				else ShowLink(x-8+235,y+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
				
				//SetTexture(0,Get(i,j),0);SetAlfa(0);
				//TFlat(x-8-w/4-4,y+3,(w-5)/4,(w-5)/4);
				//y-=w/4;

				y-=ystep;
			}
			else
			{
				if ((VNaviL==1&&i==Pos)||(VNaviL==-1))
				{
				if (j==1) ShowLink(VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene],x-8+235,mat_y[pp]+3+16);
				else ShowLink(x-8+235,mat_y[pp]+3-16,VNaviBox_x[i-VNaviScene],VNaviBox_y[i-VNaviScene]);
				}
			}
		}
	}

	}
	if (VNaviBox_y[i-VNaviScene]<y) y=VNaviBox_y[i-VNaviScene];
	if (CmdDesc[Get(i,0)].FSize!=CellSize) i+=CmdDesc[Get(i,0)].FSize/CellSize-1;
	}
}




void ShowStack()
{
VNaviBox_count=0;
int startx,starty;startx=0;starty=200;
int x,y;x=startx;y=starty;
int w=240;
int startx_;
int i=VNaviScene;
int cmdc=0;
int prev_i=0;
int so=GetIndexFromPos(VNaviScene);

while (i<EntriesCount*CellSize)
	{	
	lastscenecmd=i;
	if (((nGet(i)==0))||(CmdDesc[nGet(i)].FRoutine==&Scene&&i>VNaviScene))
		{		
			return;
		}
	
	
	char aa[256],bb[256];

	strcpy(aa,CmdDesc[nGet(i)].FName);

	if ((CmdDesc[nGet(i)].FRoutine==ApplyShader||CmdDesc[nGet(i)].FRoutine==ShaderPost)&&vsname[Get(i,1)][0]!=0)
	{
		strcpy(aa,vsname[Get(i,1)]);
	}

//	strcat(aa," ");
//	memcpy(bb,Pack+i*CellSize+256-33,33);
//	strcat (aa,bb);
	NTextLen(aa,-9,x,y,28);
	


	if (CmdDesc[nGet(i)].FLevel==0) y-=42;
	if (CmdDesc[nGet(i)].FLevel==1) y-=42;
	if (CmdDesc[nGet(i)].FLevel==1) x=startx;
	if (CmdDesc[nGet(i)].FLevel==2&&CmdDesc[nGet(prev_i)].FLevel<2) 
		{
			//x+=lastletterx+10;
			//x=startx+42;y-=42;
		}


	SetAlfa(0);
	int color;
	color= 122;

	if (CmdDesc[nGet(i)].FLevel==2) color=160;

	if (i==Pos||1==SelBuffer[cmdc+so]) 
		{
			color=255; 
			cursor_y=y;
		}


	int cr,cg,cb;
	cr=color;cg=color;cb=color;

if (color!=255)
{
	if (CmdDesc[nGet(i)].FCategory==IDC_SCN) {cr=122;cg=122;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_CMD) {cr=122;cg=122;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_TC) {cr=122;cg=122;cb=222;}
	if (CmdDesc[nGet(i)].FCategory==IDC_3D) {cr=122;cg=222;cb=222;}
	if (CmdDesc[nGet(i)].FCategory==IDC_XYZ) {cr=222;cg=222;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_UV) {cr=122;cg=22;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_SELECTION) {cr=162;cg=112;cb=162;}
	if (CmdDesc[nGet(i)].FCategory==IDC_LIGHT) {cr=102;cg=122;cb=162;}
	if (CmdDesc[nGet(i)].FCategory==IDC_TEXGEN) {cr=122;cg=162;cb=222;}
	if (CmdDesc[nGet(i)].FCategory==IDC_2D) {cr=122;cg=122;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_TEXT) {cr=122;cg=122;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_FILTERS) {cr=122;cg=222;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_RGB) {cr=122;cg=222;cb=22;}
	if (CmdDesc[nGet(i)].FCategory==IDC_ALPHA) {cr=22;cg=122;cb=222;}
	if (CmdDesc[nGet(i)].FCategory==IDC_CAM) {cr=122;cg=122;cb=122;}
	if (CmdDesc[nGet(i)].FCategory==IDC_ANIMA) {cr=222;cg=122;cb=122;}
}

	

//---
	


	if ((i==VNaviScene||
		CmdDesc[nGet(i)].FRoutine==&MainLoop||
		CmdDesc[nGet(i)].FRoutine==&EndScene||
		CmdDesc[nGet(i)].FRoutine==&EndDraw||
		CmdDesc[nGet(i)].FRoutine==&Scene)
		&&color!=255) 
		{
		cr=255;cg=0;cb=0;
		}

		NaviBox(x-8,y+3,lastletterx+5,32+6,cr,cg,cb); 
			
	

	vstack[cmdc].left=x-8;
	vstack[cmdc].top=y+3-21;
	vstack[cmdc].right=x-8+(lastletterx+5);
	vstack[cmdc].bottom=y+3+21;

	VNaviBox_x[VNaviBox_count]=x-8;
	VNaviBox_y[VNaviBox_count]=y+3;
	VNaviBox_count++;


		NText(aa,-9,x,y,28);


	stack_h=y-starty;
	if (CmdDesc[nGet(i+CmdDesc[nGet(i)].FSize)].FLevel==2) {
		if (x>256) {x=startx+42;y-=42;} else {x+=lastletterx+10;}
		//x+=lastletterx+10;
	}
		//if (CmdDesc[Get(i,0)].FRoutine==&EndScene) return;



	//if (CmdDesc[Get(i,0)].FSize!=CellSize) i+=CmdDesc[Get(i,0)].FSize/CellSize-1;
	cmdc++;
	prev_i=i;
	i+=CmdDesc[Get(i,0)].FSize;
	}


}

int lastsceneY;

void ShowSceneList()
{

int startx,starty;startx=0;starty=220;
int x,y;x=startx;y=starty;
int w=240;
int k;k=0;VSNaviBox_count=0;

int i=0;
while (i<EntriesCount*CellSize)
	{	

	if (nGet(i)==0)
		{
			lastsceneY=y+196;return;
		}

	if (CmdDesc[nGet(i)].FRoutine==&Scene)
		{
	
		char aa[256],bb[256];
		strcpy(aa,CmdDesc[nGet(i)].FName);
		strcat(aa," ");
		_itoa(VSNaviBox_count,bb,10);
		strcat(aa,bb);
		//strcat(aa," ");
		//memcpy(bb,Pack+i*CellSize+256-33,33);
		//strcat (aa,bb);
		NTextLen(aa,-9,x,y,28);
		
		SetAlfa(0);
		int color;
		color= 122;

		if (i==VNaviScene) color=255;

		NaviBox(x-8,y+3+30,lastletterx+5,32+6+60,color,color,color); 

		NText(aa,-9,x,y,28);

		SetAlfa(0);
		//SetTexture(0,VSNaviBox_count,0);
		pDevice->SetTexture(0,Scenes[VSNaviBox_count]);
		TFlat(x+lastletterx/2-5,y+50,90,58);

		vstack_s[k].left=x-8;
		vstack_s[k].top=y+3-21;
		vstack_s[k].right=x-8+(lastletterx+5);
		vstack_s[k++].bottom=y+3+21+60;

		VSNaviBox_count++;

		//x+=lastletterx+10;
		if (x>768) {x=startx;y+=42+80;} else {x+=lastletterx+10;}

		}

	if (i==0)
		{
	
		char aa[256],bb[256];
		strcpy(aa,"Main ");
		strcat(aa," ");
		//memcpy(bb,Pack+i*CellSize+256-33,33);
		//strcat (aa,bb);
		NTextLen(aa,-9,x,y,28);
		
		SetAlfa(0);
		int color;
		color= 122;

		if (0==VNaviScene) color=255;

		NaviBox(x-8,y+3,lastletterx+5,32+6,color,color,color); 

		NText(aa,-9,x,y,28);

		vstack_s[k].left=x-8;
		vstack_s[k].top=y+3-21;
		vstack_s[k].right=x-8+(lastletterx+5);
		vstack_s[k++].bottom=y+3+21;

		VSNaviBox_count++;

		x+=lastletterx+10;

		}

	//if (CmdDesc[nGet(i)].FSize!=CellSize) i+=CmdDesc[Get(i,0)].FSize/CellSize-1;
	i+=CmdDesc[Get(i,0)].FSize;
	}

	lastsceneY=96;
}

void ShowTexturesBrowser()
{
int startx,starty;startx=32;starty=lastsceneY+20;
int x,y;x=startx;y=starty;
int w=240;
int k;k=0;
int texInColumn;
texInColumn=10;
VTexNaviBox_count=0;
for (int j=0;j<=maxtex/texInColumn;j++)
for (int i=0;i<texInColumn;i++)
	{	

		if (i+j*texInColumn<maxtex) {
	
			char aa[256],bb[256];
			_itoa(i+j*texInColumn,aa,10);
			
		
	
			//x+=lastletterx+10;
			x=i*132;
			y=j*132+starty;
			SetAlfa(0);
			SetTexture(0,j*texInColumn+i,0);
			TFlat(x,y,128-32,128-32);
			NText(aa,-9,x,y-70,28);

			vstack_tex[k].left=x-64;
			vstack_tex[k].top=y-64;
			vstack_tex[k].right=x+64;
			vstack_tex[k++].bottom=y+64;

			VTexNaviBox_count++;

		}
	}
}

//mat
void ShowMaterialsBrowser()
{
int startx,starty;startx=32;starty=lastsceneY+20;
int x,y;x=startx;y=starty;
int w=240;
int k;k=0;
int texInColumn;
texInColumn=10;
VTexNaviBox_count=0;
{
D3DMATERIAL9 mt;

	
for (int j=0;j<=maxtex/texInColumn;j++)
for (int i=0;i<texInColumn;i++)
	{	

		if (i+j*texInColumn<maxtex) {
	
			char aa[256],bb[256];
			_itoa(i+j*texInColumn,aa,10);
			
		
	
			//x+=lastletterx+10;
			x=i*132;
			y=j*132+starty;
			SetAlfa(0);
			//SetTexture(0,j*texInColumn+i,0);
			pDevice->SetTexture(0,WhiteTexture);
			mt=Material[i+j*texInColumn];
			//pDevice->SetMaterial(&mt);
			TFlatMt(x,y,128-32,128-32,mt);
			NText(aa,-9,x,y-70,28);

			vstack_tex[k].left=x-64;
			vstack_tex[k].top=y-64;
			vstack_tex[k].right=x+64;
			vstack_tex[k++].bottom=y+64;

			VTexNaviBox_count++;

		}
	}
}

}


void VisualNavi()
{

if (VNaviOn==-1) return;

SetVp_(0);

LightsOff();
ZBufDisable();

//SearchScene();
ShowStack();

//ShowUsedData();
ShowSceneList();


if (ResShowFlag==1) ShowTexturesBrowser();
if (ResShowFlag==2) ShowMaterialsBrowser();

if (StagePreview==-1) {
	NText("Current Stage",-10,-250-75,300,32);
	pDevice->SetTexture(0,CStageTexture);
	SetAlfa(0);
	TFlat(-256,500,300,300);
}

}
