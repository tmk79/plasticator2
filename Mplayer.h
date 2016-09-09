double sTime,sDelta;
int tick=0;
int oldtick=0;
double BPM=120;
double SPEED=6;
double sQuant;

//const notes:array[0..11] of string= ('C ','C#','D ','D#','E ','F ','F#','G ','G#','A ','A#','B ');
double base_a4=440; // set A4=440Hz

double NoteToFrequency(int n)
{
	if ((n>=0)&&(n<=119)) 
	{
	return base_a4*pow(2.0,(n-57)/12);
	}
	else return -1;
}

//

void ProcessPatternString()
{
	return;
char n[22];
_itoa(tick,n,10);
//SetWindowText(hWnd0,n);


for (int i=LoopPoint;i<EntriesCount;i++)
{
	if (CmdDesc[Get(i,0)].FRoutine==&EndDraw) return;
	if (CmdDesc[Get(i,0)].FRoutine==&PlaySequence) 
	{
		int x=Get(CPos,2);
		int x1=x+Get(CPos,3);
		if (ptime>=x&&ptime<x1)//if pattern in time
			{
			//search note-line
			
			}
	}
}

}


void ProcessNote()
{

}

void ProcessSound()
{

}

void ProcessSoundTimeline(double t,double d)
{
//if (astate==-1) return;

sQuant=60/(SPEED/6*4*BPM/60);

sTime=ptime;sDelta=d;

tick=(int)(sTime/sQuant);
if (tick!=oldtick) {ProcessPatternString();oldtick=tick;}



}

