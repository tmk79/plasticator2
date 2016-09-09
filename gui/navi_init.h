//---
	HWND Navi;
	HWND Navi2;
	HWND Shad;
	
	void ShowParam();
	void SaveStageView(int tx);
	void ShowTextures();
	void ShowStages();
	void ShowTexArg();
	void ShowNormals();

	int PosHistory[65535];//position history
	int SelBuffer [EntriesCount],SelBuffer2 [EntriesCount];//selections
	int CCount=0;
	int CSize=0;
	char t[256];//for convertions
	int SelCount;
	int SelCount2;
	int PPage=0;//parameter page
	int UndoNum=0;
	int Pos=0;//position in command stack gui
	//anim export
	int act=0;//frameskip for animation export
	int afr=0;//framecounter
	int afrmax=25;//framecounter
	int afrskip=4;//framecounter
	//view-----------------------
	int stageview=0;//stage viewer
	int SceneToShow=0;
	int infoview=1;
	int finalview=-1;



	int tlstate=-1;//timeline view-hide
	_int64 staticaframe=0;//static frame (+-)
	int lowpanel =0;
	double fas=0;//fucking slow animation helper
	int ResShowFlag = 0;

	int visualnavi=-1;
	RECT vstack[1000];
	RECT vstack_s[1000];
	RECT vstack_tex[1000];

	int lastletterx;
	int VNaviOn=1;
	int VNaviMode=1;
	int VNaviSelCounter=0;
	int VNaviScene=0;
	int VNaviBox_x[10000];
	int VNaviBox_y[10000];
	int VNaviBox_count;
	int VSNaviBox_count;
	int VTexNaviBox_count;

	int wireframe=-1;
	int NormalShowFlag=-1;
	int PosStore=-1;
	int StagePreview=-1;

	int VNaviT=-1;
	int VNaviM=-1;
	int VNaviVB=-1;
	int VNaviC=-1;
	int VNaviL=-1;

	int lastscenecmd=0;

char* param123[3];



//--------------------

