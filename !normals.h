typedef void (*PVFN2)();
PVFN2 NormalRoutine;

typedef void (*PVFN3)(int gtx,int gty,int ox,int oy,int i);
PVFN3 NormalSubRoutine ;

int greedx=1,greedy=1;

struct vert_n {float x,y,z;};
vert_n v[4],n[4];

struct CUSTOMVERTEX_L { float x,y,z; };

CUSTOMVERTEX_L Vertices_L[522*522*2];

void DrawNormals()
{
for (int k=0;k<NumVerts;k++)
	{
	Vertices_L[k*2].x=pVerts[k].x;
	Vertices_L[k*2].y=pVerts[k].y;
	Vertices_L[k*2].z=pVerts[k].z;

	Vertices_L[k*2+1].x=pVerts[k].x+pVerts[k].n1/32.0;
	Vertices_L[k*2+1].y=pVerts[k].y+pVerts[k].n2/32.0;
	Vertices_L[k*2+1].z=pVerts[k].z+pVerts[k].n3/32.0;
	}

  pDevice->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_ARGB(0,0,0,255));

	pDevice->SetMaterial(&WhiteMaterial);
	pDevice->SetTexture(0,Texture[0]);

  pDevice->DrawPrimitiveUP(D3DPT_LINELIST,NumVerts,Vertices_L,sizeof(CUSTOMVERTEX_L));
}

void GetVertsSvertkaT(int gtx,int gty,int ox,int oy,int i)
{
float fl;
fl=1;

	if (oy>greedy) oy=oy-greedy;
	if (oy<0) oy=oy+greedy;

	if (gty>greedy) gty=gty-greedy;
	if (gty<0) gty=gty+greedy;

	if (ox>greedx) ox=ox-greedx;
	if (ox<0) ox=ox+greedx;

	if (gtx>greedx) gtx=gtx-greedx;
	if (gtx<0) gtx=gtx+greedx;

	v[i].x=pVerts[(int)(greedx+1)*oy+ox].x-pVerts[(int)(greedx+1)*gty+gtx].x;
	v[i].y=pVerts[(int)(greedx+1)*oy+ox].y-pVerts[(int)(greedx+1)*gty+gtx].y;
	v[i].z=pVerts[(int)(greedx+1)*oy+ox].z-pVerts[(int)(greedx+1)*gty+gtx].z;

	v[i].x*=fl;v[i].y*=fl;v[i].z*=fl;
}

void GetVertsSvertka2(int gtx,int gty,int ox,int oy,int i)
{
float fl;
fl=1;
	if (oy<=0) {oy=1;ox=ox+greedx/2;fl=-1;}
	if (oy>=greedy) {oy=greedy-1;ox=ox+greedx/2;}

	if (gty<=0) {gty=1;gtx=gtx+greedx/2;}
	if (gty>=greedy) {gty=greedy-1;gtx=gtx+greedx/2;fl=-1;}
	
	if (ox>greedx) ox=ox-greedx;
	if (ox<0) ox=ox+greedx;

	if (gtx>greedx) gtx=gtx-greedx;
	if (gtx<0) gtx=gtx+greedx;

	v[i].x=pVerts[(int)(greedx+1)*oy+ox].x-pVerts[(int)(greedx+1)*gty+gtx].x;
	v[i].y=pVerts[(int)(greedx+1)*oy+ox].y-pVerts[(int)(greedx+1)*gty+gtx].y;
	v[i].z=pVerts[(int)(greedx+1)*oy+ox].z-pVerts[(int)(greedx+1)*gty+gtx].z;

	v[i].x*=fl;v[i].y*=fl;v[i].z*=fl;
}


void GetVertsSvertkaX(int gtx,int gty,int ox,int oy,int i)
{
	//if (ox<0) ox=ox+greedx;
	//if (gtx<0) gtx=gtx+greedx;
	if (ox>greedx) ox=ox-greedx;
	if (ox<0) ox=ox+greedx;
	if (gtx>greedx) gtx=gtx-greedx;
	if (gtx<0) gtx=gtx+greedx;

	if (gty<0) gty=0;
	if (oy>greedy) oy=greedy;

	v[i].x=pVerts[(int)(greedx+1)*oy+ox].x-pVerts[(int)(greedx+1)*gty+gtx].x;
	v[i].y=pVerts[(int)(greedx+1)*oy+ox].y-pVerts[(int)(greedx+1)*gty+gtx].y;
	v[i].z=pVerts[(int)(greedx+1)*oy+ox].z-pVerts[(int)(greedx+1)*gty+gtx].z;
}

void GetVertsFlat(int gtx,int gty,int ox,int oy,int i)
{
	if (ox<0) ox=0;
	if (gtx<0) gtx=0;
	if (ox>greedx) ox=greedx;

	if (gty<0) gty=0;
	if (oy>greedy) oy=greedy;

	v[i].x=pVerts[(int)(greedx+1)*oy+ox].x-pVerts[(int)(greedx+1)*gty+gtx].x;
	v[i].y=pVerts[(int)(greedx+1)*oy+ox].y-pVerts[(int)(greedx+1)*gty+gtx].y;
	v[i].z=pVerts[(int)(greedx+1)*oy+ox].z-pVerts[(int)(greedx+1)*gty+gtx].z;
}

//считаем нормали
void CalcNormals()
{
double px1,py1,pz1,px2,py2,pz2,nax,nay,naz,nbx,nby,nbz,nx,ny,nz,sq,f;

for (int gty=0;gty<=greedy;gty++)
	{
	for (int gtx=0;gtx<=greedx;gtx++)
		{
			NormalSubRoutine(gtx-1,gty,gtx+1,gty,0);
			NormalSubRoutine(gtx,gty-1,gtx,gty+1,1); 

			//NormalSubRoutine(gtx,gty,gtx+1,gty,0);
			//NormalSubRoutine(gtx,gty,gtx,gty+1,1); 


			n[0].x=v[0].y*v[1].z-v[0].z*v[1].y;
			n[0].y=v[0].z*v[1].x-v[0].x*v[1].z;
			n[0].z=v[0].x*v[1].y-v[0].y*v[1].x;

			sq=sqrt( n[0].x *n[0].x + n[0].y * n[0].y + n[0].z * n[0].z );
			if (sq!=0)
			{
				f=1.0f/sq;
				n[0].x*=f;	n[0].y*=f;	n[0].z*=f;
			}

			pVerts[(int)(greedx+1)*gty+gtx].n1=n[0].x;
			pVerts[(int)(greedx+1)*gty+gtx].n2=n[0].y;
			pVerts[(int)(greedx+1)*gty+gtx].n3=n[0].z;

//tangent 
/*
int y1,x1;
if (gtx==greedx) x1=-greedx; else x1=1 ;
if (gty==greedy) y1=0; else y1=1; 


float t1=pVerts[(int)(greedx+1)*gty+gtx].x-pVerts[(int)(greedx+1)*gty+gtx+x1].x;
float t2=pVerts[(int)(greedx+1)*gty+gtx].y-pVerts[(int)(greedx+1)*gty+gtx+x1].y;
float t3=pVerts[(int)(greedx+1)*gty+gtx].z-pVerts[(int)(greedx+1)*gty+gtx+x1].z;

if (gtx==greedx) t1*=-1;

//normalization
			sq=sqrt( t1*t1 + t2*t2 + t3*t3 );
			if (sq!=0)
			{
				f=1.0f/sq/100.0;
				t1*=f;	t2*=f;	t3=f;
			}

float b1=pVerts[(int)(greedx+1)*gty+gtx].x-pVerts[(int)(greedx+1)*(gty+y1)+gtx].x;
float b2=pVerts[(int)(greedx+1)*gty+gtx].y-pVerts[(int)(greedx+1)*(gty+y1)+gtx].y;
float b3=pVerts[(int)(greedx+1)*gty+gtx].z-pVerts[(int)(greedx+1)*(gty+y1)+gtx].z;

if (gtx==greedx) b1*=-1;

//normalization
			sq=sqrt( t1*t1 + t2*t2 + t3*t3 );
			if (sq!=0)
			{
				f=1.0f/sq/100.0;
				t1*=f;	t2*=f;	t3=f;
			}


			*/
float duv1_x,duv2_x,duv1_y,duv2_y;

duv1_x=pVerts[(int)(greedx+1)*gty+gtx+1].u-pVerts[(int)(greedx+1)*gty+gtx].u;
duv1_y=pVerts[(int)(greedx+1)*gty+gtx+1].v-pVerts[(int)(greedx+1)*gty+gtx].v;
duv2_x=pVerts[(int)(greedx+1)*gty+gtx+(greedx+1)].u-pVerts[(int)(greedx+1)*gty+gtx].u;
duv2_y=pVerts[(int)(greedx+1)*gty+gtx+(greedx+1)].v-pVerts[(int)(greedx+1)*gty+gtx].v;

float r = 1.0f / (duv1_x * duv2_y - duv1_y * duv2_x);
float t1 = (v[0].x * duv2_y   - v[1].x * duv1_y)*r;
float t2 = (v[0].y * duv2_y   - v[1].y * duv1_y)*r;
float t3 = (v[0].z * duv2_y   - v[1].z * duv1_y)*r;

float b1 = (v[1].x * duv1_x   - v[0].x * duv2_x)*r;
float b2 = (v[1].y * duv1_x   - v[0].y * duv2_x)*r;
float b3 = (v[1].z * duv1_x   - v[0].z * duv2_x)*r;




			pVerts[(int)(greedx+1)*gty+gtx].t1=t1;
			pVerts[(int)(greedx+1)*gty+gtx].t2=t2;
			pVerts[(int)(greedx+1)*gty+gtx].t3=t3;

			pVerts[(int)(greedx+1)*gty+gtx].b1=b1;
			pVerts[(int)(greedx+1)*gty+gtx].b2=b2;
			pVerts[(int)(greedx+1)*gty+gtx].b3=b3;


//			pVerts[(int)(greedx)*gty+gtx].t1=n[0].x;
//			pVerts[(int)(greedx+1)*gty+gtx].t2=v[0].y;
//			pVerts[(int)(greedx+1)*gty+gtx].t3=v[0].z;

	//		pVerts[(int)(greedx+1)*gty+gtx].b1=v[1].x;
	//		pVerts[(int)(greedx+1)*gty+gtx].b2=v[1].y;
		//	pVerts[(int)(greedx+1)*gty+gtx].b3=v[1].z;



		}
	}
}


//считаем нормали
void CalcFlatNormals()
{
double px1,py1,pz1,px2,py2,pz2,nax,nay,naz,nbx,nby,nbz,nx,ny,nz,sq,f;

for (int gty=0;gty<=greedy;gty++)
	{
	for (int gtx=0;gtx<=greedx;gtx++)
		{
			NormalSubRoutine(gtx-1,gty,gtx+1,gty,0);
			NormalSubRoutine(gtx,gty-1,gtx,gty+1,1); 

			n[0].x=v[0].y*v[1].z-v[0].z*v[1].y;
			n[0].y=v[0].z*v[1].x-v[0].x*v[1].z;
			n[0].z=v[0].x*v[1].y-v[0].y*v[1].x;

			sq=sqrt( n[0].x *n[0].x + n[0].y * n[0].y + n[0].z * n[0].z );
			if (sq!=0)
			{
				f=1.0f/sq;
				n[0].x*=f;	n[0].y*=f;	n[0].z*=f;
			}

			pVerts[(int)(greedx+1)*gty+gtx].n1=n[0].x;
			pVerts[(int)(greedx+1)*gty+gtx].n2=n[0].y;
			pVerts[(int)(greedx+1)*gty+gtx].n3=n[0].z;

float duv1_x,duv2_x,duv1_y,duv2_y;

duv1_x=pVerts[(int)(greedx+1)*gty+gtx+1].u-pVerts[(int)(greedx+1)*gty+gtx].u;
duv1_y=pVerts[(int)(greedx+1)*gty+gtx+1].v-pVerts[(int)(greedx+1)*gty+gtx].v;
duv2_x=pVerts[(int)(greedx+1)*gty+gtx+(greedx+1)].u-pVerts[(int)(greedx+1)*gty+gtx].u;
duv2_y=pVerts[(int)(greedx+1)*gty+gtx+(greedx+1)].v-pVerts[(int)(greedx+1)*gty+gtx].v;

float r = 1.0f / (duv1_x * duv2_y - duv1_y * duv2_x);
float t1 = (v[0].x * duv2_y   - v[1].x * duv1_y)*r;
float t2 = (v[0].y * duv2_y   - v[1].y * duv1_y)*r;
float t3 = (v[0].z * duv2_y   - v[1].z * duv1_y)*r;

float b1 = (v[1].x * duv1_x   - v[0].x * duv2_x)*r;
float b2 = (v[1].y * duv1_x   - v[0].y * duv2_x)*r;
float b3 = (v[1].z * duv1_x   - v[0].z * duv2_x)*r;




			pVerts[(int)(greedx+1)*gty+gtx].t1=t1;
			pVerts[(int)(greedx+1)*gty+gtx].t2=t2;
			pVerts[(int)(greedx+1)*gty+gtx].t3=t3;

			pVerts[(int)(greedx+1)*gty+gtx].b1=b1;
			pVerts[(int)(greedx+1)*gty+gtx].b2=b2;
			pVerts[(int)(greedx+1)*gty+gtx].b3=b3;
		}
	}
}



void SvertkaTNormals()
{
NormalSubRoutine=GetVertsSvertkaT;
CalcNormals();
}

void Svertka2Normals()
{
NormalSubRoutine=GetVertsSvertka2;
CalcNormals();
}

void SvertkaXNormals()
{
NormalSubRoutine=GetVertsSvertkaX;
CalcNormals();
}

void FlatNormals()
{
NormalSubRoutine=GetVertsFlat;
CalcFlatNormals();
}

void FlatNormals4()
{
NormalSubRoutine=GetVertsFlat;
CalcFlatNormals();
}

int cube_i[6];
int cube_i2[6];

void FlatNormals2()
{
NormalSubRoutine=GetVertsFlat;
CalcFlatNormals();

double px1,py1,pz1,px2,py2,pz2,nax,nay,naz,nbx,nby,nbz,nx,ny,nz,sq,f;

for (int i=0;i<6;i++)
	{
	int ofs=cube_i[i];
	for (int gtx=0;gtx<=greedx;gtx++)
		{
			pVerts[ofs+gtx].n1=pVerts[ofs+(greedx+1)+gtx].n1;
			pVerts[ofs+gtx].n2=pVerts[ofs+(greedx+1)+gtx].n2;
			pVerts[ofs+gtx].n3=pVerts[ofs+(greedx+1)+gtx].n3;
		}
	}

for (int i=0;i<6;i++)
	{
	int ofs=cube_i2[i]-1;
	for (int gtx=0;gtx<=greedx;gtx++)
		{
			pVerts[ofs-gtx].n1=pVerts[ofs-(greedx+1)-gtx].n1;
			pVerts[ofs-gtx].n2=pVerts[ofs-(greedx+1)-gtx].n2;
			pVerts[ofs-gtx].n3=pVerts[ofs-(greedx+1)-gtx].n3;
		}
	}

}