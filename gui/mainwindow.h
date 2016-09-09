int oldX=0;
int oldY=0;
int oldZ=0;
int pressL=0;
int prx[1024],pry[1024],prz[1024];
int MouseX,MouseY;
D3DXVECTOR3 src,dst,up;
float xps,yps,zps;int cpf=0;



void SearchSceneUp(int position);


#ifdef EditMode

void PlayWave()
{
if (pSourceVoice) pSourceVoice->Stop(0,0);

					int size;
					size=snd_samplesize*2;
					size=44100*60*10*2*2;
					void* wav;
					
					*(WaveBuffer+0)='R';
					*(WaveBuffer+1)='I';
					*(WaveBuffer+2)='F';
					*(WaveBuffer+3)='F';
					*(WaveBuffer+4)=(size +44 - 8);
					*(WaveBuffer+8)='W';
					*(WaveBuffer+9)='A';
					*(WaveBuffer+10)='V';
					*(WaveBuffer+11)='E';
					*(WaveBuffer+12)='f';
					*(WaveBuffer+13)='m';
					*(WaveBuffer+14)='t';
					*(WaveBuffer+15)=0x20;
					*(int*)(WaveBuffer+16)=(int)16;
					*(short*)(WaveBuffer+20)=(short)0x0001;//pcm
					*(short*)(WaveBuffer+22)=(short)2;//stereo
					*(int*)(WaveBuffer+24)=(int)44100;
					*(int*)(WaveBuffer+28)=(int)44100*2;//speed?
					*(short*)(WaveBuffer+32)=(short)4;//bytes
					*(short*)(WaveBuffer+34)=(short)16;//bits
					*(WaveBuffer+36)='d';
					*(WaveBuffer+37)='a';
					*(WaveBuffer+38)='t';
					*(WaveBuffer+39)='a';
					*(int*)(WaveBuffer+40)=(int)size;

					wav=WaveBuffer;

					//if (playsound_key==1) {PlaySound(NULL,NULL,NULL);playsound_key*=-1;break;}
					//if (playsound_key==-1) {PlaySound((LPCSTR)wav, NULL, WaveBufferORY | SND_ASYNC | SND_NODEFAULT |SND_LOOP);playsound_key*=-1;break;}

					//PlaySound((LPCSTR)wav, NULL, WaveBufferORY |  SND_NODEFAULT |SND_LOOP);

					wf.cbSize=0;
						wf.nAvgBytesPerSec=44100*2*2;
						wf.nBlockAlign=(2*16)/8;
						wf.nChannels=2;
						wf.nSamplesPerSec=44100;
						wf.wBitsPerSample=16;
						wf.wFormatTag=WAVE_FORMAT_PCM;


						XAbuffer.AudioBytes=size;
						XAbuffer.Flags = XAUDIO2_END_OF_STREAM;
						XAbuffer.LoopBegin=0;
						XAbuffer.LoopCount=XAUDIO2_LOOP_INFINITE;
						XAbuffer.LoopLength=size;
						XAbuffer.pAudioData=WaveBuffer+44;
							XAbuffer.pContext=NULL;
							XAbuffer.PlayBegin=44100*ptime/60;///44100;
							XAbuffer.PlayLength=0;

					//XAbuffer.AudioBytes = size;  
					//XAbuffer.pAudioData = WaveBuffer;  
						//	if (playsound_key==1) {pSourceVoice->Stop(0,0);playsound_key*=-1;break;} else
							{
								HRESULT hr;

								//if( FAILED(hr = pXAudio2->CreateSourceVoice( &pSourceVoice, (WAVEFORMATEX*)&wf,0,2,&VCB ) ) ) 
								if( FAILED(hr = pXAudio2->CreateSourceVoice( &pSourceVoice, (WAVEFORMATEX*)&wf ) ) ) 
								MessageBox(hWndView,"XA SVoice fail",0,0);;

								//if( FAILED(hr = pXAudio2->RegisterForCallbacks() ) 
								//MessageBox(hWndView,"XA SVoice fail",0,0);;


								pSourceVoice->SubmitSourceBuffer( &XAbuffer );

								pSourceVoice->Start( 0 );
								//WaitForSingleObjectEx( VCB.hBufferEndEvent, INFINITE, TRUE );

								//playsound_key*=-1;break;
							}

}

void StopWave()
{
if (pSourceVoice) pSourceVoice->Stop(0,0);
}

void DrawSomeNavi()
{
			if (sas==1) act++; if (act>afrskip) act=0;
			if (sas==1&&act==0) SaveAnim();


			if (infoview==-1)
			{
			char wst[150];char nn[20];
			strcpy(wst,""); 
			if (finalview!=1&&stageview==0) strcat (wst,": final view ['] : "); 
			if (finalview==1||stageview!=0)strcat (wst,": stage view ['] : ");


			strcat (wst," animation [space] ");
			if (astate==1) 
				{
					fas+=.15;
				}

			if (fas>=4) fas=0;
			if (fas<0) fas=3.9;

			if ((int)fas==0) strcat(wst,"l");
			if ((int)fas==1) strcat(wst,"/");
			if ((int)fas==2) strcat(wst,"-");
			if ((int)fas==3) strcat(wst,"\\");

			strcat (wst," frame: ");
			_itoa(ptime,nn,10);
			strcat (wst,nn);

			if (camstate==-1) strcat (wst,": free camera [esc] : "); 
			if (camstate==1) strcat (wst,": timeline camera [esc] : "); 

			NText(wst,-10,-457,600,32);
			
			}
}


int movezmode=0;
int playsound_key=-1;
int jumpmode=0;

void NumError(int n)
{
char aa[256];
_itoa(n,aa,10);
SetWindowText(hWnd0,aa);
}

char notes[12]={'Z','S','X','D','C','V','G','B','H','N','J','M'};
char notes2[12]={'z','s','x','d','c','v','g','b','h','n','j','m'};

#endif

#ifndef EditMode
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
			//FMUSIC_FreeSong(mod);
			PostQuitMessage(0);
			};

			case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}
#endif

#ifdef EditMode
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	jumpmode=0;

	switch (message) 
	{
	//case WM_NCHITTEST:
	//{
 //   LRESULT lRes = DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam);
   // if (lRes == HTCAPTION)
      //  lRes = HTCLIENT;
    //return lRes;
	//}
	case WM_SIZE:
		//if (hWnd==hWndView)
		{
	if (hWnd==hWndView){
		RECT wr;
		GetWindowRect(hWndView,&wr);
	
		int w,h;
		h=wr.bottom-wr.top;w=h*1.7777777777;
		MoveWindow(hWndView,wr.left,wr.top,w,h,TRUE);
	}
		}
		break;

	case WM_MOVE:
		{
//			SetWindowPos(Navi,HWND_TOP,(int)(short)LOWORD(lParam),(int)(short)HIWORD(lParam),screen_width,50,SWP_SHOWWINDOW);
//			ShowWindow(Navi,SW_SHOW);
//			UpdateWindow(Navi);

//			SetWindowPos(Navi2,HWND_TOP,(int)(short)LOWORD(lParam)+screen_width+5,(int)(short)HIWORD(lParam),256,220,SWP_SHOWWINDOW);
//			ShowWindow(Navi2,SW_SHOW);
//			UpdateWindow(Navi2);
			break;
		}




	case WM_KEYUP:
	{
			switch (wParam)
			{
				case 'S': 
					break;
					
				case 'A':
					DeselectAll();
					if (PosStore>0)Pos=PosStore;
					
					ShowParam();
					PosStore=-1;
					SearchSceneUp(Pos);
					break;
				case 'Z':
					{
						movezmode=0;
						oldX=MouseX;
						oldY=MouseY;
//
						int j=VNaviScene;
						int n=GetIndexFromPos(j);
						int k=0;
						while (nGet(j)!=0)
							{
								if (CmdDesc[nGet(j)].FRoutine==Scene&&j!=VNaviScene) break;
								int q;
								if (SelBuffer[n]==1) 
								{
									q=j;
									for (int i=0;i<100;i++)
									{
										if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[0])) prx[k]=Get(q,i);
										if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[1])) pry[k]=Get(q,i);
										if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[2])) prz[k]=Get(q,i);
									}
								}
								n++;
								k++;
								j+=CmdDesc[nGet(j)].FSize;
							}

						break;
					}
			}
		break;
	}
	
	case WM_CHAR:
		{
			//if (wParam!=VK_INSERT&&wParam!=VK_SPACE&&wParam!=3&&wParam!=22) 

			if (wParam==26)//undo shortcut
			{
				SendMessage(hWnd0,WM_COMMAND,ID_EDIT_UNDO,0);
				break;
			}

			if (wParam==22)//paste
			{
				SendMessage(hWnd0,WM_COMMAND,ID_EDIT_PASTE,0);
				break;
			}	

			if (wParam==3)//copy
			{

				SendMessage(hWnd0,WM_COMMAND,ID_EDIT_COPY,0);
				break;
				
			}


		break;
		}

	case WM_KEYDOWN:
		{


			switch (wParam)
			{
			case 'N':
				NormalShowFlag*=-1;
				break;
			case 'R':
				ResShowFlag=ResShowFlag++;
				if (ResShowFlag>2) ResShowFlag=0;
				break;
			case 'T':
				break;
			case 'M':
				break;
			case 'L':
				tlstate*=-1; 
				break;
			case VK_TAB:
				VNaviOn*=-1;
				break;
			

			case VK_ESCAPE:
				camstate*=-1; 
				if (camstate==1) {SetWindowText(hWndView,"camera view");} else {SetWindowText(hWndView,"free view");}
				break;

			//anima start-stop
			case VK_SPACE:
				{
					astate*=-1; 
					start_time=GetCounter();
					start_ptime=ptime;
				
					if (useWave==1)
					{
						if (astate==1) 
							PlayWave(); 
						else 
							StopWave();
					}	

					break;
				}



			case 'K':
				if (CmdDesc[Get(Pos,0)].FRoutine==Camera) 
				{
				
					D3DXVECTOR3 eye;
					D3DXVECTOR3 at;
					D3DXVECTOR3 up;
					D3DXVECTOR3 scale,translation;
					D3DXQUATERNION rotation;
					D3DXMATRIX v=View2;
					D3DXMATRIX r,i,t;


					D3DXMatrixTranslation(&t,0,0,-1);
					D3DXMatrixMultiply(&v,&v,&t);

					D3DXMatrixInverse(&t,NULL,&v);

					eye.x=t._41;
					eye.y=t._42;
					eye.z=t._43;
					Put(Pos,1,eye.x*1000);
					Put(Pos,2,eye.y*1000);
					Put(Pos,3,eye.z*1000);

					D3DXVECTOR3 look;
					look.x=t._31;
					look.y=t._32;
					look.z=t._33;
					
					at.x=eye.x+look.x;
					at.y=eye.y+look.y;
					at.z=eye.z+look.z;
					Put(Pos,4,at.x*1000);
					Put(Pos,5,at.y*1000);
					Put(Pos,6,at.z*1000);

					up.x=t._21;
					up.y=t._22;
					up.z=t._23;

					D3DXVECTOR3 sup;
					sup.x=0;sup.y=1;sup.z=0;
					float a=-acos(D3DXVec3Dot(&sup,&up))*628;//???? magic
					
					nPut(Pos+7*2,(int)a);

					ShowParam();
				}

				break;

			case VK_LEFT:
				{
				break;
				}

			case VK_RIGHT:
				{
				break;
				}

			case VK_UP:
				{
				break;
				}

			case VK_DOWN:
				{	
				break;
				}

			case VK_DELETE:

				SendMessage(hWnd0,WM_COMMAND,ID_EDIT_DELETE,0);
				break;

			case VK_PRIOR:
				WriteUndoStage();
				SearchSceneUp(Pos);
				Pos=VNaviScene;
				break;

			case VK_NEXT:
				WriteUndoStage();
				SearchSceneDown(Pos);
				Pos=VNaviScene;
				break;

			case VK_OEM_3://"~ key"
					{
						if (stageview==0) finalview*=-1;
						break;
					}

			case 'W':
				wireframe*=-1;
				break;

			case 'A':
					{DeselectAll();
						if (PosStore==-1) PosStore=Pos;
						int i=0;
						while (i<EntriesCount*CellSize)
						{
							if (nGet(i)==0) break;
							if (CmdDesc[nGet(i)].FRoutine==&TimeCursor) 
							{
							Pos=i;
							
							SelBuffer[GetIndexFromPos(Pos)]=1;
							SearchSceneUp(Pos);
							ShowParam();				
							break;
							}
							i+=CmdDesc[nGet(i)].FSize;
						}
						break;
					}

				//reset view
				case '9':
					{
					D3DXMATRIX m;
					D3DXMatrixIdentity(&m);
					View3=m;
					break;
					}

				case '0':
					{
					View2=StartViewMatrix;
					World=StartMatrix;
					D3DXMATRIX m;
					D3DXMatrixIdentity(&m);
					//View3=m;
					D3DXMatrixIdentity(&ZoomMatrix);
					break;
					}

				case 'Q':
					StagePreview*=-1;

	
				//depth moves
				case 'Z':
				
					{
						movezmode=1;
						oldX=MouseX;
						oldZ=MouseY;

						//SelCount=SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
					int j=VNaviScene;
				int n=GetIndexFromPos(j);
				int k=0;
				while (nGet(j)!=0)
					{
						if (CmdDesc[nGet(j)].FRoutine==Scene&&j!=VNaviScene) break;
						int q;
						if (SelBuffer[n]==1) 
						{
							q=j;
							for (int i=0;i<100;i++)
							{
								if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[0])) prx[k]=Get(q,i);
								if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[1])) pry[k]=Get(q,i);
								if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[2])) prz[k]=Get(q,i);
							}
						}
						n++;k++;
						j+=CmdDesc[nGet(j)].FSize;
					}



						break;
					}
				

				case VK_F11:
				//case VK_HOME:
					{
					VNaviMode*=-1;
					
					//if (VNaviMode==1) ShowWindow(hWnd1,SW_SHOW);
					//else ShowWindow(hWnd1,SW_HIDE);
					
					break;
					}

			case VK_F5:
					{
					int size;
					size=snd_samplesize*2;
					size=44100*60*10*2;
					void* wav;
					
					*(snd_mem+0)='R';
					*(snd_mem+1)='I';
					*(snd_mem+2)='F';
					*(snd_mem+3)='F';
					*(snd_mem+4)=(size +44 - 8);
					*(snd_mem+8)='W';
					*(snd_mem+9)='A';
					*(snd_mem+10)='V';
					*(snd_mem+11)='E';
					*(snd_mem+12)='f';
					*(snd_mem+13)='m';
					*(snd_mem+14)='t';
					*(snd_mem+15)=0x20;
					*(int*)(snd_mem+16)=(int)16;
					*(short*)(snd_mem+20)=(short)0x0001;//pcm
					*(short*)(snd_mem+22)=(short)1;//mono
					*(int*)(snd_mem+24)=(int)44100;
					*(int*)(snd_mem+28)=(int)44100*2;//speed?
					*(short*)(snd_mem+32)=(short)2;//bytes
					*(short*)(snd_mem+34)=(short)16;//bits
					*(snd_mem+36)='d';
					*(snd_mem+37)='a';
					*(snd_mem+38)='t';
					*(snd_mem+39)='a';
					*(int*)(snd_mem+40)=(int)size;

					wav=snd_mem;

					//if (playsound_key==1) {PlaySound(NULL,NULL,NULL);playsound_key*=-1;break;}
					//if (playsound_key==-1) {PlaySound((LPCSTR)wav, NULL, SND_MEMORY | SND_ASYNC | SND_NODEFAULT |SND_LOOP);playsound_key*=-1;break;}

					//PlaySound((LPCSTR)wav, NULL, SND_MEMORY |  SND_NODEFAULT |SND_LOOP);

					wf.cbSize=0;
						wf.nAvgBytesPerSec=44100*2;
						wf.nBlockAlign=(1*16)/8;
						wf.nChannels=1;
						wf.nSamplesPerSec=44100;
						wf.wBitsPerSample=16;
						wf.wFormatTag=WAVE_FORMAT_PCM;


						XAbuffer.AudioBytes=size;
						XAbuffer.Flags = XAUDIO2_END_OF_STREAM;
						XAbuffer.LoopBegin=0;
						XAbuffer.LoopCount=XAUDIO2_LOOP_INFINITE;
						XAbuffer.LoopLength=snd_samplesize;
						XAbuffer.pAudioData=snd_mem+44;
							XAbuffer.pContext=NULL;
							XAbuffer.PlayBegin=0;
							XAbuffer.PlayLength=0;

					//XAbuffer.AudioBytes = size;  
					//XAbuffer.pAudioData = snd_mem;  
							if (playsound_key==1) {pSourceVoice->Stop(0,0);playsound_key*=-1;break;} else
							{
								HRESULT hr;

								//if( FAILED(hr = pXAudio2->CreateSourceVoice( &pSourceVoice, (WAVEFORMATEX*)&wf,0,2,&VCB ) ) ) 
								if( FAILED(hr = pXAudio2->CreateSourceVoice( &pSourceVoice, (WAVEFORMATEX*)&wf ) ) ) 
								MessageBox(hWndView,"XA SVoice fail",0,0);;

								//if( FAILED(hr = pXAudio2->RegisterForCallbacks() ) 
								//MessageBox(hWndView,"XA SVoice fail",0,0);;


								pSourceVoice->SubmitSourceBuffer( &XAbuffer );

								pSourceVoice->Start( 0 );
								//WaitForSingleObjectEx( VCB.hBufferEndEvent, INFINITE, TRUE );

								playsound_key*=-1;break;
							}
					break;
					}


		}
			
		break;
		}

	case WM_LBUTTONDBLCLK:
		{
		jumpmode=1;
		}
		//continue 
	case WM_LBUTTONDOWN:
		if (VNaviOn==1) 
		{
				int fwKeys = wParam;
				float winH,winW;
				RECT rect;
				if (VNaviMode==1)
				{
					GetClientRect(hWnd1,&rect);
					winH=(rect.bottom-rect.top);
					winW=(rect.right-rect.left);
				}
				else
				{
					GetClientRect(hWndView,&rect);
					winH=(rect.bottom-rect.top);
					winW=(rect.right-rect.left);
				}

			char aa[10];

			float slx=LOWORD(lParam);
			float sly=HIWORD(lParam);

			D3DXVECTOR3 mouse;
			mouse.x=(2*slx-winW)/winW;
			mouse.y=(winH-sly*2)/winH;
			mouse.z=0;

			D3DXVECTOR3 p1,p2;
			D3DXVECTOR3 pt1,pt2;
			D3DXMATRIX m,m2;
			m=World;
			m2=View3;
			D3DXMatrixMultiply(&m,&m,&m2);

			float Vw=1;
			float Vh;
			Vh=screen_height/screen_width;
				float Zf=100*8;
				float Zn=0.5f;
				D3DMATRIX Projection2 = 
				{
					2*Zn/Vw, 0, 0, 0,
					0, 2*Zn/Vh, 0, 0,
					0, 0, Zf/(Zf-Zn*2), 1+cam_zoom+.3,
					0, 0, -Zf/(Zf-Zn)*Zn/32, 0,//+cam_zoom,
				};

			m2=Projection2;
			D3DXMatrixMultiply(&m,&m,&m2);

			if (hWnd==hWnd1||VNaviMode!=1)
			{
				for (int i=0;i<VNaviBox_count;i++)
				{
					p1.x=vstack[i].left/1000.0;
					p2.x=vstack[i].right/1000.0;		
					p1.y=vstack[i].top/1000.0;
					p2.y=vstack[i].bottom/1000.0;		
					p2.z=0;p1.z=0;
					D3DXVec3TransformCoord(&pt1,&p1,&m);
					D3DXVec3TransformCoord(&pt2,&p2,&m);

					if (mouse.x>pt1.x&&mouse.x<pt2.x&&mouse.y>pt1.y&&mouse.y<pt2.y)
					{

						if (fwKeys==MK_CONTROL+1)
							{						
							int p=GetPosFromLocalIndex(VNaviScene,i);
							int j=GetIndexFromPos(p);
							SelBuffer[j]=1-SelBuffer[j];
							break;
							}

						if (fwKeys==MK_SHIFT+1)
							{
							int s=GetIndexFromPos(GetPosFromLocalIndex(VNaviScene,i));
							int n=GetIndexFromPos(Pos);

							if (n>s)
							{int a=n;n=s;s=a;}
							for (int j=n;j<=s;j++)
								{
									SelBuffer[j]=1;
								}
							break;
							}
						else //not shift not control
							{
								if (jumpmode==1)
								{
									//jump
									if (CmdDesc[nGet(GetPosFromLocalIndex(VNaviScene,i))].FRoutine==ShowScene)
									{
										SearchScene(nGet(GetPosFromLocalIndex(VNaviScene,i)+2*1));
										Pos=VNaviScene;
									}

									if (CmdDesc[nGet(Pos)].FRoutine==CreateShader)
									{
										if (Get(Pos,1)>0)
										{
										CurrentShaderPos=Pos;
										CurrentShaderSlot=Get(Pos,1);
										ShowWindow(Shad,SW_SHOW);
										memcpy(shaderText,(char*)Pack+CurrentShaderPos+4,65535);
										SetDlgItemText(Shad,IDC_SE,(char*)Pack+CurrentShaderPos+4);
										SetDlgItemText(Shad,IDC_ERR," ");
										char nm[256];char ns[256];
										_itoa(CurrentShaderSlot,ns,10);
										strcpy(nm,vsname[CurrentShaderSlot]);
										strcat(nm,"/");
										strcat(nm,(char*)psname[CurrentShaderSlot]);
										strcat(nm," slot:");
										strcat(nm,ns);
										SetWindowText(Shad,nm);
										}
									}

									if (CmdDesc[nGet(Pos)].FRoutine==ApplyShader||CmdDesc[nGet(Pos)].FRoutine==ShaderPost)
									{
										if (Get(Pos,1)>0)
										{
										int i=0; while (i<EntriesCount*CellSize&&nGet(i)!=0)
										{
											if (CmdDesc[nGet(i)].FRoutine==CreateShader)
											{
												if (Get(i,1)==Get(Pos,1))
												{
												CurrentShaderPos=i;
												CurrentShaderSlot=Get(i,1);
												ShowWindow(Shad,SW_SHOW);
												memcpy(shaderText,(char*)Pack+CurrentShaderPos+4,65535);
												SetDlgItemText(Shad,IDC_SE,(char*)Pack+CurrentShaderPos+4);
												SetDlgItemText(Shad,IDC_ERR," ");
												char nm[256];char ns[256];
												_itoa(CurrentShaderSlot,ns,10);
												strcpy(nm,vsname[CurrentShaderSlot]);
												strcat(nm,"/");
												strcat(nm,(char*)psname[CurrentShaderSlot]);
												strcat(nm," slot:");
												strcat(nm,ns);
												SetWindowText(Shad,nm);
												}
											};
											i+=CmdDesc[nGet(i)].FSize;
										}

										}
									}
								}
								else
								{
									Pos=GetPosFromLocalIndex(VNaviScene,i);
									DeselectAll();
									SelBuffer[GetIndexFromPos(Pos)]=1;
									
								}
							
						//	break;
							}
					}
					}

				
				//scenes
					for (int i=0;i<VSNaviBox_count;i++)
					{
						p1.x=vstack_s[i].left/1000.0;
						p2.x=vstack_s[i].right/1000.0;
						
						p1.y=vstack_s[i].top/1000.0;
						p2.y=vstack_s[i].bottom/1000.0;
						
						p2.z=0;p1.z=0;

						D3DXVec3TransformCoord(&pt1,&p1,&m);
						D3DXVec3TransformCoord(&pt2,&p2,&m);

						if (mouse.x>pt1.x&&mouse.x<pt2.x&&mouse.y>pt1.y&&mouse.y<pt2.y)
						{				
								SearchScene(i);
								Pos=VNaviScene;				
								DeselectAll();
								SelBuffer[GetIndexFromPos(Pos)]=1;
								break;
						}

					}
				}

		}
		//continue processing!
		case WM_RBUTTONDOWN:
			{
//
			int fwKeys = wParam;
			if (message==WM_RBUTTONDOWN&&(fwKeys==2))
				{
			
				float winH,winW;
				RECT rect;
				if (VNaviMode==1)
					{
					GetClientRect(hWnd1,&rect);
					winH=(rect.bottom-rect.top);
					winW=(rect.right-rect.left);
					}
				else
					{
					GetClientRect(hWndView,&rect);
					winH=(rect.bottom-rect.top);
					winW=(rect.right-rect.left);		
					}

				float slx=LOWORD(lParam);
				float sly=HIWORD(lParam);

				D3DXVECTOR3 mouse;
				mouse.x=(2*slx-winW)/winW;
				mouse.y=(winH-sly*2)/winH;
				mouse.z=0;

				D3DXVECTOR3 p1,p2;
				D3DXVECTOR3 pt1,pt2;
				D3DXMATRIX m,m2;
				m=World;
				//m2=View2;
				m2=View3;
				D3DXMatrixMultiply(&m,&m,&m2);

				float Vw=1;
				float Vh;
				Vh=screen_height/screen_width;
				float Zf=100*8;
				float Zn=0.5f;
				D3DMATRIX Projection2 = 
				{
					2*Zn/Vw, 0, 0, 0,
					0, 2*Zn/Vh, 0, 0,
					0, 0, Zf/(Zf-Zn*2), 1+cam_zoom+.3,
					0, 0, -Zf/(Zf-Zn)*Zn/32, 0,//+cam_zoom,
				};

				m2=Projection2;
				D3DXMatrixMultiply(&m,&m,&m2);
			}


			if (movezmode==0)
			{
			oldX=LOWORD(lParam);
			oldY=HIWORD(lParam);
			}
			else
			{
			oldX=LOWORD(lParam);
			oldZ=HIWORD(lParam);
			}


				int j=VNaviScene;
				int n=GetIndexFromPos(j);
				int k=0;
				while (nGet(j)!=0)
					{
						if (CmdDesc[nGet(j)].FRoutine==Scene&&j!=VNaviScene) break;
						if (SelBuffer[n]==1) 
						{
							for (int i=0;i<100;i++)
							{
								if (!strcmp(CmdDesc[Get(j,0)].FParamName[i],param123[0])) prx[k]=Get(j,i);
								if (!strcmp(CmdDesc[Get(j,0)].FParamName[i],param123[1])) pry[k]=Get(j,i);
								if (!strcmp(CmdDesc[Get(j,0)].FParamName[i],param123[2])) prz[k]=Get(j,i);
							}
						}
						n++;
						k++;
						j+=CmdDesc[nGet(j)].FSize;
					}
					
				
		break;
		}

	case WM_LBUTTONUP:
		{
		ShowParam();
		break;
		}

	case WM_MOUSEMOVE:
		{

		//--------------------------------

		//SetFocus(hWnd);
		int fwKeys = wParam;
		int xPos = LOWORD(lParam);  
		int yPos = HIWORD(lParam);
		int zPos = HIWORD(lParam);
		MouseX=xPos;
		MouseY=yPos;
		
		double cfx,cfy,cfz;
		cfx=3000/512;cfy=4000/512;cfz=4000/512;
		

		if (fwKeys==MK_LBUTTON)
		{
			D3DXMATRIX vm,vm2;
			if (camstate==-1) vm=View2; 
			else vm=View;

			if (CmdDesc[Get(Pos,0)].FRoutine==TimeCursor)
			{
				D3DXMatrixIdentity(&vm);
				if (useWave==1&&astate==1) PlayWave();
			}
				
				int j=VNaviScene;
				//j+=CmdDesc[nGet(j)].FSize;
				int cm=GetIndexFromPos(j);

				int k=0;

				while (nGet(j)!=0)
				{
				int q;
				if (CmdDesc[nGet(j)].FRoutine==Scene&&j!=VNaviScene) break;

				if (SelBuffer[cm]==1)
					{

							float dx,dy,dz;
							dx=(xPos-oldX)*cfx;
							dy=(yPos-oldY)*cfy;//дельты
							dz=(zPos-oldZ)*cfy;
							D3DXVECTOR3 d;

						q=j;				
		
						float sx,sy,sz;int px,py,pz;
						sx=0;sy=0;sz=0;
						px=-1;py=-1;pz=-1;
						for (int i=0;i<100;i++)
						{
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[0])) {px=i;sx=prx[k];}
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[1])) {py=i;sy=pry[k];}
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],param123[2])) {pz=i;sz=prz[k];}
						}
						D3DXVECTOR3 tp;
						tp.x=sx;tp.y=sy;tp.z=sz;
						if (param123Mode==0)
						{
							D3DXMatrixInverse(&vm2,NULL,&vm);				
							D3DXVec3TransformCoord(&d,&tp,&vm);
							if (movezmode==0) {d.x+=dx;d.y-=dy;} else {d.x+=dx;d.z-=dz;} 
							D3DXVec3TransformCoord(&tp,&d,&vm2);
						}
						else 
						{
							tp.x=sx+sx*dx/1000.0;
							tp.z=sz+sz*dx/1000.0;
							tp.y=sy+sy*dx/1000.0;
						}
						if (px>0) Put(q,px,tp.x);
						if (py>0) Put(q,py,tp.y);
						if (pz>0) Put(q,pz,tp.z);


						if (CmdDesc[nGet(Pos)].FRoutine==TimeCursor)
						{
							start_time=GetCounter();
							if (tp.x>=0) start_ptime=tp.x; else start_ptime=0;
						}
					}
					k++;
					j+=CmdDesc[nGet(j)].FSize;
					cm++;
				}
				z:;
	
		ShowParam();

		}


		float dx,dy,i,j;
		float a;D3DXMATRIX Rm,R1m,R2m;				

		//if ((fwKeys==(MK_CONTROL|MK_LBUTTON))||(fwKeys==(MK_CONTROL|MK_RBUTTON))) dy=0;
		//rotate
		/*if (fwKeys==(MK_CONTROL))
		{
			if (cpf==0){MouseX=xPos;MouseY=yPos;cpf=1;}

			dx=(xPos-MouseX)/100.0+xps;
			dy=(yPos-MouseY)/100.0+zps;
	
			float tx,ty,tz;
			tx=src.x-dst.x;tz=src.z-dst.z;
			src.x=dst.x+tx*cos(dx*PI/180.0)-tz*sin(dx*PI/180.0);
			src.z=dst.z+tx*sin(dx*PI/180.0)+tz*cos(dx*PI/180.0);
			
			up.x=0;up.y=1;up.z=0;

			D3DXMatrixLookAtLH(&Rm,&src,&dst,&up);
				//MulMat(&View,&Rm);
				View=Rm;
			}
		*/
		//moving camera
		if (fwKeys==(MK_RBUTTON)&&hWnd!=hWnd1)
		{
		D3DXMATRIX TransMatrix;
		D3DXMATRIX WorldMatrix;
		WorldMatrix=View2;
		if (movezmode==0)
			{
			D3DXMatrixTranslation(&TransMatrix,(MouseX-oldX)/100.0,-(MouseY-oldY)/100.0,0);
			D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&TransMatrix);
			//View=WorldMatrix;
			View2=WorldMatrix;
			oldX=MouseX;
			oldY=MouseY;
			}
		else
			{
			D3DXMatrixTranslation(&TransMatrix,(MouseX-oldX)/100.0,0,(MouseY-oldZ)/100.0);
			D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&TransMatrix);
			//View=WorldMatrix;
			View2=WorldMatrix;
			oldX=MouseX;
			oldZ=MouseY;
			}	
		}

		if ((fwKeys==(MK_RBUTTON|MK_SHIFT))||(fwKeys==MK_RBUTTON&&hWnd==hWnd1))
		{
		D3DXMATRIX TransMatrix;
		D3DXMATRIX WorldMatrix;
		WorldMatrix=View3;
		if (movezmode==0)
			{
			D3DXMatrixTranslation(&TransMatrix,(MouseX-oldX)/100.0,-(MouseY-oldY)/100.0,0);
			D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&TransMatrix);
			//View=WorldMatrix;
			View3=WorldMatrix;
			oldX=MouseX;
			oldY=MouseY;
			}
		else
			{
			D3DXMatrixTranslation(&TransMatrix,(MouseX-oldX)/100.0,0,(MouseY-oldZ)/100.0);
			D3DXMatrixMultiply(&WorldMatrix,&WorldMatrix,&TransMatrix);
			//View=WorldMatrix;
			View3=WorldMatrix;
			oldX=MouseX;
			oldZ=MouseY;
			}	
		}


		//rotate camera
		if (fwKeys==(MK_CONTROL|MK_LBUTTON))
		{
		D3DXMATRIX TransMatrix;
		D3DXMATRIX ViewMatrix;
		ViewMatrix=View2;
		
		int axis1,axis2; axis1=abs(MouseX-oldX);axis2=abs(MouseY-oldY);

			D3DXMatrixTranslation(&TransMatrix,0,0,-1);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			//if (axis1>axis2)
			{
			D3DXMatrixRotationY(&TransMatrix,(MouseX-oldX)/100.0);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			}
			if (axis1<axis2)
			{
//			D3DXMatrixTranslation(&TransMatrix,0,(MouseY-oldY)/100.0,0);
//			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
				//не всю! only eye
			}
			D3DXMatrixTranslation(&TransMatrix,0,0,1);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			View2=ViewMatrix;
			//View=ViewMatrix;
			oldX=MouseX;
			oldY=MouseY;

		}
		
		if (fwKeys==(MK_CONTROL|MK_RBUTTON))
		{
		int axis1,axis2; axis1=abs(MouseX-oldX);axis2=abs(MouseY-oldY);

		D3DXMATRIX TransMatrix;
		D3DXMATRIX ViewMatrix;
		ViewMatrix=View2;
			D3DXMatrixTranslation(&TransMatrix,0,0,-1);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			
			if (axis1>axis2)
			{
			D3DXMatrixRotationZ(&TransMatrix,((MouseY-oldY)+(MouseX-oldX))/100.0);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			}
			if (axis1<axis2)
			{
			D3DXMatrixRotationX(&TransMatrix,(MouseY-oldY)/100.0);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			}

			D3DXMatrixTranslation(&TransMatrix,0,0,1);
			D3DXMatrixMultiply(&ViewMatrix,&ViewMatrix,&TransMatrix);
			View2=ViewMatrix;
			//View=ViewMatrix;
			oldX=MouseX;
			oldY=MouseY;
		}

		if (hWnd!=hWnd0&&hWnd!=hWnd1) SetFocus(hWnd);

		break;
		}

		//zoom camera
		case WM_MOUSEWHEEL:
				{

				if (HIWORD(GetKeyState('D'))>0)
				{
					float d;
					d=((float)(short)HIWORD(wParam))/((float)(WHEEL_DELTA));
					if (d>0) {UpItem();} else {DownItem();}
					break;
				}

				if (LOWORD(wParam)==MK_LBUTTON)
				{
				/*	float d;
					d=((float)(short)HIWORD(wParam))/((float)(WHEEL_DELTA));

					SelCount=SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
					if (SelCount==0) break;
					
					for (int j=0;j<SelCount;j++)
					{
					int q;
					if (SelBuffer[j]==0) goto z12;
					q=SelBuffer[j];

						for (int i=0;i<100;i++)
						{
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],"xsize")) Put(q,i,Get(q,i)+d*Get(q,i)/10.0);
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],"ysize")) Put(q,i,Get(q,i)+d*Get(q,i)/10.0);
							if (!strcmp(CmdDesc[Get(q,0)].FParamName[i],"zsize")) Put(q,i,Get(q,i)+d*Get(q,i)/10.0);
						}

					}
						ShowParam();
					z12:;
					*/
					break;
				}
				if (HIWORD(GetKeyState(VK_CONTROL))>0)
					{
					/*
					D3DXMATRIX m,m2,m3;
					D3DXMATRIX TransMatrix;
					D3DXMATRIX ViewMatrix;
					float d;
					d=((float)(short)HIWORD(wParam))/((float)(WHEEL_DELTA*10));

					cam_zoom+=d;
					if (cam_zoom<0) cam_zoom=0;


					D3DXMatrixScaling(&TransMatrix,d+1,d+1,d+1);
					//D3DXMatrixTranslation(&TransMatrix,0,0,d);
					D3DXMatrixMultiply(&ZoomMatrix,&ZoomMatrix,&TransMatrix);
						

					*/
						break;
					}
				


				float d;
				d=((float)(short)HIWORD(wParam))/((float)(WHEEL_DELTA));
				d=sign(d);


				if(d<0)
				{
					if (nGet(Pos+CmdDesc[nGet(Pos)].FSize)!=0) Pos+=CmdDesc[nGet(Pos)].FSize;
				} else {
					int j=0;
					while (nGet(j)!=0)
					{
					if (j+CmdDesc[nGet(j)].FSize==Pos)
						{
							Pos=j;
							break;
						}
					j+=CmdDesc[nGet(j)].FSize;
					}
				}
				
				if (Pos<0) Pos=0;
				if (Pos<VNaviScene) SearchSceneUp(Pos);
				if (Pos>=lastscenecmd) VNaviScene=Pos;//SearchSceneDown(Pos);

				DeselectAll();
				SelBuffer[GetIndexFromPos(Pos)]=1;
				ShowParam();

				break;

				}

//		case WM_COMMAND:
//			wmId    = LOWORD(wParam); 
//			wmEvent = HIWORD(wParam); 

			// Parse the menu selections:
//			switch (wmId)
//			{
		case WM_COMMAND:
		{
			int rs;

			switch (LOWORD(wParam))
			{

			case ID_PROJECT_ULIST:
				int cls[1000];

				for (int i=0;i<CommandsCount;i++)
				{
				cls[i]=0;
				}

//				for (int i=0;i<CommandsCount;i++)
				{
				
					int adr=0;
					while(Get(adr,0)!=0)
					{
					cls[Get(adr,0)]++;
					adr+=CmdDesc[Get(adr,0)].FSize;
					}
				}
				//
				{
					char* s;
					s=new char[10000];
					strcpy(s,"unused");
					for (int i=0;i<CommandsCount;i++)
					{
					if (cls[i]==0)
						{
							strcat(s,"#define ");
							strcat(s,CmdDesc[i].FName);
							strcat(s," NULL");
							strcat(s,"\n");
						}
					else
						{
								strcat(s,"//");
								strcat(s,CmdDesc[i].FName);
								strcat(s," ");
								char ssi[10];
								_itoa(cls[i],ssi,10);
								strcat(s,ssi);					
								strcat(s,"\n");					
						}
					
					}

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
				ofn.lpstrFilter = "header\0*.h\0";
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
					if (NULL==strstr(ofn.lpstrFile,".h")) strcat(name,".h");

					fp = fopen(name, "wb");
					fwrite(s,strlen(s),1,fp);
					fclose(fp);
					//strcpy (currentfile,name);
					//ShowFilename();
					}
				}
					
					//MessageBox(hWnd,s,"ulist",MB_OK);
				}

				break;
				

			case ID_PROJECT_SAVESAMPLE:
				{
				SaveSample();
				break;
				}	
			case ID_PROJECT_SAVEALLSAMPLES:
				{
				SaveAllSamples();
				break;
				}
			case ID_VIEW_TEXTURES:
				VNaviT*=-1;
				if (VNaviT==1) 
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_TEXTURES,MF_UNCHECKED );
					}
					else
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_TEXTURES,MF_CHECKED );
					}
				break;
			case ID_VIEW_VERTEXBUFFERS:
				VNaviVB*=-1;
				if (VNaviVB==1) 
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_VERTEXBUFFERS,MF_UNCHECKED );
					}
					else
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_VERTEXBUFFERS,MF_CHECKED );
					}
				break;
			case ID_VIEW_MATERIALS:
				VNaviM*=-1;
				if (VNaviM==1) 
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_MATERIALS,MF_UNCHECKED );
					}
					else
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_MATERIALS,MF_CHECKED );
					}
				break;
			case ID_VIEW_CURVES:
				VNaviC*=-1;
				if (VNaviC==1) 
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_CURVES,MF_UNCHECKED );
					}
					else
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_CURVES,MF_CHECKED );
					}
				break;
			case ID_VIEW_ONLYCURRENTLINKS:
				VNaviL*=-1;
				if (VNaviL==1) 
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_ONLYCURRENTLINKS,MF_CHECKED );
					}
					else
					{
					CheckMenuItem(GetMenu(hWnd0),ID_VIEW_ONLYCURRENTLINKS,MF_UNCHECKED );
					}
					break;

			case ID_SCENE_INSERT:
				
				/*SearchSceneUp(Pos);
				Pos=VNaviScene;
				memmove(Pack+(Pos+2)*CellSize,Pack+(Pos)*CellSize,(EntriesCount-Pos+2)*CellSize);
				for (int i=0;i<CommandsCount;i++)
				{
					if (CmdDesc[i].FRoutine==&Scene) *(short*)(Pack+(Pos+0)*CellSize)=i;
					if (CmdDesc[i].FRoutine==&EndScene) *(short*)(Pack+(Pos+1)*CellSize)=i;
				}

					SelBuffer[0]=VNaviScene;
					SelCount=1;
				//ShowList();
				ShowParam();*/
				break;

			case ID_SCENE_DELETE:
	/*			WriteUndoStage();
				short a;int ESCm;
				ESCm=VNaviScene;

				for (int i=VNaviScene;i<EntriesCount;i++)
				{
				a=Get(i,0);
				if (a==0) break;
				if (CmdDesc[a].FRoutine==&EndScene) 
					{
					ESCm=i+1;
					memmove(Pack+VNaviScene*CellSize,Pack+ESCm*CellSize,(EntriesCount-ESCm)*CellSize);
					Pos=VNaviScene;
					SelBuffer[0]=VNaviScene;
					SelCount=1;
					break;
					}
				}*/
				
				break;

			case ID_EDIT_UNDO:
				{
				ProcessUndo();
				ShowParam();
				break;
				}

			case IDC_RENAME:
				{
				WriteUndoStage();
				DialogBox(hInst,MAKEINTRESOURCE(IDD_RENAME),Navi,RenameProc);
				break;
				}

			case IDC_SEARCH:
				{
/*
				char sstr[256],strbuf[256];
					
				ZeroMemory(sstr,256);
				GetDlgItemText(Navi,IDC_SEARCHBOX,sstr,256);

				int j;
				j=SendDlgItemMessage(Navi,IDC_STACK,LB_GETCOUNT,0,0);

				for (int i=Pos+1;i<j;i++)
					{
					SendDlgItemMessage(Navi,IDC_STACK,LB_GETTEXT,(WPARAM) i,(LPARAM) (LPCTSTR) strbuf);
					if (strstr(strbuf,sstr)!=NULL) 
						{
						Pos=i;
						SendDlgItemMessage(Navi,IDC_STACK,LB_SETSEL,FALSE,-1);		
						SendDlgItemMessage(Navi,IDC_STACK,LB_SETSEL,TRUE,Pos);
						goto k;
						}
					}
				
				k:;
				ShowParam();*/
				break;
				}

			case IDC_UP:
				{
/*				WriteUndoStage();
				//int apos=SendDlgItemMessage(Navi,IDC_STACK,LB_GETTOPINDEX,0,0);
				//SelCount=SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
				if (SelCount==0) break;
				
				for (int i=0;i<SelCount;i++)
				{
				if (SelBuffer[i]==0) goto z22;
				Pos=SelBuffer[i];
				memmove(Exchange+Pos*CellSize,Pack+Pos*CellSize,CellSize);
				memmove(Pack+Pos*CellSize,Pack+(Pos-1)*CellSize,CellSize);
				memmove(Pack+(Pos-1)*CellSize,Exchange+Pos*CellSize,CellSize);
				SelBuffer[i]--;
				}

				Pos=SelBuffer[0];
				//ShowList();
			
				for (int i=0;i<SelCount;i++)
				{
				//SendDlgItemMessage(Navi,IDC_STACK,LB_SETSEL,TRUE,SelBuffer[i]);
				}
				
				z22:;
				//SendDlgItemMessage(Navi,IDC_STACK,LB_SETTOPINDEX,apos,0);
				ShowParam();*/
				break;
				}

			case IDC_DOWN:
				{
			/*	WriteUndoStage();
				int p,i,j;
				//int apos=SendDlgItemMessage(Navi,IDC_STACK,LB_GETTOPINDEX,0,0);
				//p=SendDlgItemMessage(Navi,IDC_STACK,LB_GETCOUNT,0,0);
				//SelCount=SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
				if (SelCount==0) break;
				p=EntriesCount;

				for (i=(SelCount-1);i>=0;i--)
				{
				if (SelBuffer[i]==(p-1)) goto zz;
				Pos=SelBuffer[i];
				memmove(Exchange+Pos*CellSize,Pack+Pos*CellSize,CellSize);
				memmove(Pack+Pos*CellSize,Pack+(Pos+1)*CellSize,CellSize);
				memmove(Pack+(Pos+1)*CellSize,Exchange+Pos*CellSize,CellSize);
				SelBuffer[i]++;
				}

				Pos=SelBuffer[0];
			

				zz:;
				//SendDlgItemMessage(Navi,IDC_STACK,LB_SETTOPINDEX,apos,0);
				ShowParam();*/
				break;
				}


			case ID_EDIT_COPY:
				{
				int s=VNaviScene;
				int sI=GetIndexFromPos(VNaviScene);
				int ac=0;
				while (nGet(s)!=0)
				{
					if (CmdDesc[nGet(s)].FRoutine==Scene&&s!=VNaviScene) break;

					if (SelBuffer[sI]==1)
					{
					memcpy(Exchange2+ac,Pack+s,CmdDesc[nGet(s)].FSize);
					ac+=CmdDesc[nGet(s)].FSize;
					}

					s+=CmdDesc[nGet(s)].FSize;
					sI++;
				}
				CSize=ac;
				
				break;
				}
			case ID_EDIT_PASTE:
				{
				if (CSize==0) break;
				WriteUndoStage();
				DeselectAll();
				if (Pos<=LoopPoint) {PrecalcStatus=0;LoopPoint=0;}
				memmove(Pack+Pos+CSize,Pack+Pos,EntriesCount*CellSize-Pos-CSize);
				memmove(Pack+Pos,Exchange2,CSize);

				ShowParam();

				break;
				}
			//case IDC_DELETE:
			case ID_EDIT_DELETE:
				{					
				WriteUndoStage();

				int i=GetPosFromLocalIndex(VNaviScene,0);
				int sti=i;
				int cm=GetIndexFromPos(i);

				int p=i;int cm2=cm;

				int k;
				for ( k=0;k<EntriesCount;k++)
				{
					if (SelBuffer[k]==1) {Pos=GetPosFromLocalIndex(0,k-1);break;}
				}

				while (nGet(p)!=0)
				{
					if ((CmdDesc[nGet(p)].FRoutine==Scene)&&(p!=sti)) break;
					if (SelBuffer[cm2]==1) 
					{
						Pos=p;
						break;
					}
					cm2++;
					p+=CmdDesc[nGet(p)].FSize;
				}

				while (nGet(i)!=0)
				{
					if ((CmdDesc[nGet(i)].FRoutine==Scene)&&(i!=sti)) break;
					if (SelBuffer[cm]==1) 
					{
					memmove(Pack+i,Pack+i+CmdDesc[nGet(i)].FSize,EntriesCount*CellSize-i-CmdDesc[nGet(i)].FSize);
					for (int j=cm;j<EntriesCount;j++)
						{
						SelBuffer[j]=SelBuffer[j+1];
						}
					}
					else
					{
					i+=CmdDesc[nGet(i)].FSize;
					cm++;
					}
				}
				
				SelBuffer[k]=1;

				ShowParam();
				break;
				}

			case ID_PROJECT_NEWPROJECT:
				{
				CleanProject();
				WriteUndoStage();
				VNaviScene=0;
				Pos=0;
				SelBuffer[0]=0;
				SelCount=1;
				LoadTemplate();
				break;
				}
			case ID_PROJECT_SAVEANIMATION:
				{
				//sas=1;
				break;
				}
			
			case ID_PROJECT_SAVEAS:
				{
				SaveAs();
				break;
				}

			case ID_PROJECT_SAVE:
				{
				Save();
				break;
				}
			case ID_PROJECT_SAVESELECTED:
				{
				/*BYTE* ptr;
				SelCount=SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
				if (SelCount==0) break;;
				for (int i=0;i<SelCount;i++)
				{
				memcpy(Exchange+i*CellSize,Pack+SelBuffer[i]*CellSize,CellSize);
				}
				*(short*)(Exchange+SelCount*CellSize)=0;
				
				ptr=Pack;
				Pack=Exchange;
				Save();
				Pack=ptr;
				*/
				break;
				}
			case ID_PROJECT_LOAD:
				{
				WriteUndoStage();
				if (Load()==0)
					{
					VNaviScene=0;
					CleanProject();
					Pos=0;
					SelBuffer[0]=0;
					SelCount=1;
					ShowParam();
					}
				break;
				}
			case ID_PROJECT_INSERT:
			case IDC_LOAD2:
				{
				/*WriteUndoStage();
				SendDlgItemMessage(Navi,IDC_STACK,LB_GETSELITEMS,EntriesCount,(LPARAM) (LPINT) SelBuffer);
				Pos=SelBuffer[0];

				//
				//shift textures and materials
				int i;i=0;
					int cmd;int lasttex;
					lasttex=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;
						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"texture")) 
							{
							if (Get(i,j)>lasttex) lasttex=Get(i,j);
							}
						}
					i++;
					}

				int lastmat;lastmat=0;
				i=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;
						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"Material")) 
							{
							if (Get(i,j)>lastmat) lastmat=Get(i,j);
							}
						}
					i++;
					}

				lasttex++;lastmat++;

				//

				BYTE* ptr;
				ptr=Pack;
				Pack=Exchange;
				if (Load()==0)
				{
				i=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;
						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"texture")) 
							{
								if (Get(i,j)!=-1) Put(i,j,Get(i,j)+lasttex);
							}

							if (strstr(CmdDesc[cmd].FParamName[j],"Material")) 
							{
								Put(i,j,Get(i,j)+lastmat);
							}

						}
					i++;
					}


				Pack=ptr;
				
				for (i=0;i<EntriesCount;i++)
				{
					if (*(short*)(Exchange+i*CellSize)==0) goto pp;
				}
				pp:
			    memmove(Pack+(Pos+i+1)*CellSize,Pack+(Pos+1)*CellSize,(EntriesCount-(Pos+i+1))*CellSize);
				memcpy(Pack+(Pos+1)*CellSize,Exchange,i*CellSize);
				ShowParam();
				}
				else Pack=ptr;
				*/
				break;
				}

			case ID_PROJECT_OPTIMIZE:
				{
					/*
				WriteUndoStage();
				CleanProject();
				int cmd;
				int usedtex[256];
				int i;int k=0;
				i=0;
				
				//textures
				//search
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;

						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"texture")) 
							{
								int found;
								found=0;
								//search duplicates
								for	(int p=0;p<k;p++)
									{
										if (Get(i,j)==usedtex[p]) found=1;
									}

									if (found==0)
										{
										usedtex[k]=Get(i,j);k++;
										}
							}
						}

					i++;
					}

				//change
				i=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;

						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"texture")) 
							{
							int texn;
							texn=Get(i,j);
							if (texn!=-1)
								{
								for (int p=0;p<k;p++)
									{
									if (usedtex[p]==texn) Put(i,j,p);
									}
								}
							}
						}
					//usedtex
					i++;
					}

				//material
				//search
				k=0;i=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;

						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"Material")) 
							{
								int found;
								found=0;
								//search duplicates
								for	(int p=0;p<k;p++)
									{
										if (Get(i,j)==usedtex[p]) found=1;
									}

									if (found==0)
										{
										usedtex[k]=Get(i,j);k++;
										}
							}
						}

					i++;
					}

				//change
				i=0;
				while (i<EntriesCount)
					{
					cmd=Get(i,0);
					if (cmd==0) break;

						//in params
						for (int j=1;j<100;j++)
						{
							if (strstr(CmdDesc[cmd].FParamName[j],"Material")) 
							{
							int texn;
							texn=Get(i,j);
							if (texn!=-1)
								{
								for (int p=0;p<k;p++)
									{
									if (usedtex[p]==texn) Put(i,j,p);
									}
								}
							}
						}
					//usedtex
					i++;
					}
				Pos=0;
				SelBuffer[0]=0;
				SelCount=1;
				LoopPoint=0;
				*/
				break;
				}


			case ID_PROJECT_RECALC:
				{
				CleanProject();
				LoopPoint=0;
				break;
				}

			case ID_PROJECT_SAVEAVI:
				{
				SaveAvi();
				break;
				}

			
			}
		break;
		}				
//				default:
//				   return DefWindowProc(hWnd, message, wParam, lParam);
//			}
			break;

		case WM_DESTROY:

	
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

#endif