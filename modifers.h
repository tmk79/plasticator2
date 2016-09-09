//----mods

int GSel[512][512];
void CalcIndicies();
double cubicInterpolateI(double p0,double p1,double p2,double p3,double x);


#ifdef EditMode

void CalcIndicies32()
{
int k=0;int ty,tx;
for (ty=0;ty<8;ty++)
	{
	for (tx=0;tx<8;tx++)
		{
		pInds1[k+0]=ty*(8+1)+tx;
		pInds1[k+1]=ty*(8+1)+tx+1;
		pInds1[k+2]=(ty+1)*(8+1)+tx+1;		
		k+=3;
		
		pInds1[k+0]=ty*(8+1)+tx;
		pInds1[k+1]=(ty+1)*(8+1)+tx+1;
		pInds1[k+2]=(ty+1)*(8+1)+tx;		
		k+=3;
		}
	}
}

void show_mc(float x, float y, float z, float xsize,float ysize,float zsize)
{
	pVerts1[0].x=x-xsize;
	pVerts1[0].y=y-ysize;
	pVerts1[0].z=z+zsize;
	pVerts1[1].x=x-xsize;
	pVerts1[1].y=y+ysize;
	pVerts1[1].z=z+zsize;
	pVerts1[2].x=x+xsize;
	pVerts1[2].y=y+ysize;
	pVerts1[2].z=z+zsize;
	pVerts1[3].x=x+xsize;
	pVerts1[3].y=y-ysize;
	pVerts1[3].z=z+zsize;
			
	pVerts1[4].x=x-xsize;
	pVerts1[4].y=y-ysize;
	pVerts1[4].z=z-zsize;
	pVerts1[5].x=x-xsize;
	pVerts1[5].y=y+ysize;
	pVerts1[5].z=z-zsize;
	pVerts1[6].x=x+xsize;
	pVerts1[6].y=y+ysize;
	pVerts1[6].z=z-zsize;
	pVerts1[7].x=x+xsize;
	pVerts1[7].y=y-ysize;
	pVerts1[7].z=z-zsize;

	int ind[]={0,1,2,2,3,0,4,5,6,6,7,4,
			   0,4,5,5,1,0,2,3,6,6,7,3};

	memcpy(pInds1,ind,3*8*4);

//			pVerts1[k].color=0x00ffffff;


	//CalcIndicies32();

 pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	pDevice->SetRenderState(D3DRS_CULLMODE, 0);
	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,8,8,pInds1,D3DFMT_INDEX32,pVerts1,sizeof(MyVertex));
if(wireframe!=1)  pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		

}

void show_ms(float x, float y, float z, float rad)
{
	//SetAlfa(0);

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	
	//pDevice->SetRenderState(D3DRS_COLORVERTEX,TRUE);
	//pDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE,D3DMCS_MATERIAL); 

int	k=0;int tx,ty;float a,b;
for (ty=0;ty<=8;ty++)
	{
	b=ty*360.0/(double)8.0;
	for (tx=0;tx<=8;tx++)
		{
		a=tx*360.0/(double)8.0;
			pVerts1[k].x=x+rad*cos(a*PI/180.0)*sin(b*PI/180.0/2.0)/2.0;
			pVerts1[k].z=z+rad*sin(a*PI/180.0)*sin(b*PI/180.0/2.0)/2.0;
			pVerts1[k].y=y+rad*cos(b*PI/180.0/2.0)/2.0;
			
			pVerts1[k].color=0x00ffffff;

			pVerts1[k].u=(double)tx/(double)(greedx);
			pVerts1[k].v=(double)ty/(double)(greedy);
		k++;
		}
	}

	CalcIndicies32();

	//pDevice->SetTexture(0,NULL);
	
	//SetMaterial(&Material[material]);
 // pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
  pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	
	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,9*9,8*8*2,pInds1,D3DFMT_INDEX32,pVerts1,sizeof(MyVertex));
if(wireframe!=1)  pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
  //pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);


//pDevice->SetPixelShader(NULL);
//pDevice->SetVertexShader(NULL);

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		

}

#endif
//--
void SetScatter()
{
scatterN=Get(CPos,1);
scatterX=Get(CPos,2);
scatterY=Get(CPos,3);
scatterZ=Get(CPos,4);
}

void IrregularGrid()
{
float n=Get(CPos,1)/10.0;
float cx=(pVerts[0].x+pVerts[greedx].x)/2.0;
float cy=(pVerts[0].y+pVerts[(greedy-1)*(greedx+1)].y)/2.0;
float sx=fabs(pVerts[0].x-pVerts[greedx].x);
float sy=fabs(pVerts[0].y-pVerts[(greedy-1)*(greedx+1)].y);

memcpy(pVerts1,pVerts,(greedx+1)*(greedy+1)*sizeof(MyVertex));
for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
		if(x>0&&x<(greedx)) {
			pVerts[y*(greedx+1)+x].x=lerp(pVerts1[y*(greedx+1)+x].x,cx,fabs(pVerts1[y*(greedx+1)+x].x-cx)/sx*n);
//			pVerts[y*(greedx+1)+x].x=lerp(pVerts1[y*(greedx+1)+x].x,cx,fabs(pVerts1[y*(greedx+1)+x].x-cx)/sx*n);
		}
		if(y>0&&y<(greedy)) {
			pVerts[y*(greedx+1)+x].y=lerp(pVerts1[y*(greedx+1)+x].y,cy,fabs(pVerts1[y*(greedx+1)+x].y-cy)/sy*n);	
		}

	}
}
}

float pno[8];

float Cosine_Interpolate(float a,float b,float x)
{
float ft = x * 3.1415927;
  float f = (1 - cosf(ft)) * 0.5;
  return a*(1-f) + b*f;  
}

float Noise2D(int x, int y)
{
  int n = x + y * 57;
  n = (n<<13) ^ n;
  return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) /
      1073741824.0f);
}
float SmoothedNoise2D(float x, float y)
{
    float corners = ( Noise2D(x-1, y-1)+Noise2D(x+1, y-1)+
         Noise2D(x-1, y+1)+Noise2D(x+1, y+1) ) / 16;
    float sides   = ( Noise2D(x-1, y)  +Noise2D(x+1, y)  +
         Noise2D(x, y-1)  +Noise2D(x, y+1) ) /  8;
    float center  =  Noise2D(x, y) / 4;
    return corners + sides + center;
  }
float CompileNoise(float x, float y) {
      float int_X    = int(x);//целая часть х
      float fractional_X = x - int_X;//дробь от х
      float int_Y    = int(y);
      float fractional_Y = y - int_Y;
     float v1 = SmoothedNoise2D(int_X,     int_Y);
     float v2 = SmoothedNoise2D(int_X + 1, int_Y);
     float v3 = SmoothedNoise2D(int_X,     int_Y + 1);
     float v4 = SmoothedNoise2D(int_X + 1, int_Y + 1);
      float i1 = Cosine_Interpolate(v1 , v2 , fractional_X);
      float i2 = Cosine_Interpolate(v3 , v4 , fractional_X);
      return Cosine_Interpolate(i1 , i2 , fractional_Y);
	  //return lerp(i2,i1,fractional_Y);
}
float PerlinNoise_2D(float x,float y,float z,float factor)
{
	x=(x-.5)*z;
	y=(y-.5)*z;

   float total = 0;
   float persistence=.5f;
   float frequency = 0.125f;
   float amplitude=.5;
   //x+= (factor);
   //y+= (factor);
   for(int i=0;i<8;i++)
   {
       total += CompileNoise(x*frequency+pno[i], y*frequency) * amplitude;
       amplitude *= persistence;
       frequency*=2;
    }
    total=fabsf(total);
	return total;
}

//--
void AddPerlinH()
{
float a,b,z;float cnt=8;
int tsize=256;

a=Get(CPos,1)/1000.0;
b=Get(CPos,2)/1000.0;
z=Get(CPos,3)/100.0;
for (int q=0;q<8;q++) pno[q]=Get(CPos,5+q)/100.0;
float amp=Get(CPos,4)/100.0;


int addr=0;
if (CurrentCmd1==Sphere) Svertka2Normals();
if (CurrentCmd1==Tube) SvertkaXNormals();
if (CurrentCmd1==Flat||CurrentCmd1==SubdividedFlat) FlatNormals();
if (CurrentCmd1==Torus) SvertkaTNormals();

      for(int i=0; i<=greedy; i++)
	  {
         for(int j=0; j<=greedx; j++)
         {
            float col=PerlinNoise_2D(float(i)+a,float(j)+b,z,5);
   
			pVerts[i*(greedx+1)+j].x+=col*amp*pVerts[i*(greedx+1)+j].n1;
			pVerts[i*(greedx+1)+j].y+=col*amp*pVerts[i*(greedx+1)+j].n2;
			pVerts[i*(greedx+1)+j].z+=col*amp*pVerts[i*(greedx+1)+j].n3;

		 }
	  }
}

int loop_x,loop_y;

void MidPoint(int outV, int inV, int inV2, MyVertex* pVerts1 )
{
		pVerts[outV].x=(pVerts1[inV].x+pVerts1[inV2].x)/2.0;
		pVerts[outV].y=(pVerts1[inV].y+pVerts1[inV2].y)/2.0;
		pVerts[outV].z=(pVerts1[inV].z+pVerts1[inV2].z)/2.0;
		pVerts[outV].u=(pVerts1[inV].u+pVerts1[inV2].u)/2.0;
		pVerts[outV].v=(pVerts1[inV].v+pVerts1[inV2].v)/2.0;
				pVerts[outV].u1=(pVerts1[inV].u1+pVerts1[inV2].u1)/2.0;
				pVerts[outV].v1=(pVerts1[inV].v1+pVerts1[inV2].v1	)/2.0;
		pVerts[outV].n1=(pVerts1[inV].n1+pVerts1[inV2].n1)/2.0;
		pVerts[outV].n2=(pVerts1[inV].n2+pVerts1[inV2].n2)/2.0;
		pVerts[outV].n3=(pVerts1[inV].n3+pVerts1[inV2].n3)/2.0;
}

void MidPoint2(int outV, int inV1, int inV2, int inV3, int inV4, MyVertex* pVerts1 )
{
		pVerts[outV].x=cubicInterpolateI(pVerts1[inV1].x,pVerts1[inV2].x,pVerts1[inV3].x,pVerts1[inV4].x,.5);
		pVerts[outV].y=cubicInterpolateI(pVerts1[inV1].y,pVerts1[inV2].y,pVerts1[inV3].y,pVerts1[inV4].y,.5);
		pVerts[outV].z=cubicInterpolateI(pVerts1[inV1].z,pVerts1[inV2].z,pVerts1[inV3].z,pVerts1[inV4].z,.5);

		pVerts[outV].u=(pVerts1[inV2].u+pVerts1[inV3].u)/2.0;
		pVerts[outV].v=(pVerts1[inV2].v+pVerts1[inV3].v)/2.0;
		pVerts[outV].u1=(pVerts1[inV2].u1+pVerts1[inV3].u1)/2.0;
		pVerts[outV].v1=(pVerts1[inV2].v1+pVerts1[inV3].v1)/2.0;

		pVerts[outV].n1=(pVerts1[inV2].n1+pVerts1[inV3].n1)/2.0;
		pVerts[outV].n2=(pVerts1[inV2].n2+pVerts1[inV3].n2)/2.0;
		pVerts[outV].n3=(pVerts1[inV2].n3+pVerts1[inV3].n3)/2.0;

}

void Subdivide()
{

int iter=Get(CPos,1);
int type=Get(CPos,2);

if (iter<1) return;

int xx=greedx;int yy=greedy;


for (int t=0;t<iter;t++) 
{
xx*=2;yy*=2;
}
if ((xx+1)*(yy+1)>=512*512) return;

for (int p=0;p<iter;p++) 
{

memcpy(pVerts1,pVerts,NumVerts*sizeof(MyVertex));
memcpy(pInds1,pInds,NumInds*4);

int outI;int outV;
int inV=0;int inV2=0;
outI=0;outV=0;

for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<greedx;x++)
	{
		inV=x+(greedx+1)*y;
		outV=x*2+(greedx*2+1)*y*2;

		pVerts[outV]=pVerts1[inV];

		if (type==0) 
			MidPoint(outV+1,inV,inV+1,pVerts1);
		if (type==1) 
		{int base;
			base=(greedx+1)*y;
			int p0,p1,p2,p3;
			p0=inV-1; if(p0<base) p0=base+greedx-1;
			p1=inV; 
			p2=inV+1;
			p3=inV+2;if (p3>base+(greedx)) p3=base+1;

			if( CurrentCmd1==&Flat||CurrentCmd1==&SubdividedFlat) {
				if (x==0) p0=p1;
				if (x==greedx-1) p3=p2;
			} 

			MidPoint2(outV+1,p0,p1,p2,p3,pVerts1);
		}
	}
	//pVerts[(greedx+1)*y*2]=pVerts1[(greedx+1)*y];
	pVerts[outV+2]=pVerts1[greedx+(greedx+1)*y];
	
}

greedx=greedx*2;

for (int y=0;y<greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
		inV=x+(greedx+1)*y*2;
		inV2=inV+(greedx+1)*2;
		outV=inV+(greedx+1);

		if (type==0) MidPoint(outV,inV,inV2,pVerts);
		if (type==1) {
			int base;
			base=x;
			int p0,p1,p2,p3;
			p0=inV-(greedx+1)*2; if (p0<x) p0=x+(greedx+1)*(greedy*2-2);
			p1=inV; 
			p2=inV2;
			p3=inV2+(greedx+1)*2;if (p3>x+(greedx+1)*(greedy*2)) p3=x+(greedx+1)*2;

			//looped like sphere
			if (y==0 && CurrentCmd1==&Sphere) {
			if(x<greedx/2)	p0=inV2+(int)greedx/2; else p0=inV2-(int)greedx/2;
			}
			if (y==greedy-1 && CurrentCmd1==&Sphere) {
			if(x<greedx/2)	p3=inV+(int)greedx/2; else p3=inV-(int)greedx/2;
			}

			//looped like tube
			//if (y==0 && loop_y==0) p0=p1; 
			//if (y==greedy-1 && loop_y==0) p3=p2;
			if (y==0 && ((CurrentCmd1==&Tube)||(CurrentCmd1==&Flat)||(CurrentCmd1==&SubdividedFlat))) {
			p0=p1;
			}
			if (y==greedy-1 && ((CurrentCmd1==&Tube)||(CurrentCmd1==&Flat)||(CurrentCmd1==&SubdividedFlat))) {
			p3=p2;
			}
			MidPoint2(outV,p0,p1,p2,p3,pVerts);
		}
	}
}

greedy*=2;

CalcIndicies();

	NumVerts=(greedx+1)*(greedy+1);//чтобы не париться с заворотом посчитали 360 включительно
	NumTriangles=greedx*greedy*2;
	NumInds=NumTriangles*3;

}

}

void Smooth()
{
int iter=Get(CPos,1);
for (int i=0;i<iter;i++)
{
memcpy(pVerts1,pVerts,NumVerts*sizeof(MyVertex));

int ys,xs,startx,starty;
xs=greedx+1;ys=greedy+1;
startx=0;starty=0;
if (CurrentCmd1==&Flat||CurrentCmd1==&SubdividedFlat) {xs=greedx;ys=greedy;startx=1;starty=1;}
if (CurrentCmd1==&Tube) {xs=greedx+1;ys=greedy+1;startx=0;starty=0;}


	for (int y=starty;y<ys;y++)
	{
		for (int x=startx;x<xs;x++)
		{
			int inV=x+(greedx+1)*y;
			int up,down,left,right;
			left=inV-1;right=inV+1;up=inV-(greedx+1);down=inV+(greedx+1);
			if (x==0) left=(greedx+1)*y+greedx-1;
			if (y==0) 
			{
				up=x+(greedx+1)*(greedy-1);
				if (CurrentCmd1==&Tube)	up=x;
				if (CurrentCmd1==&Sphere) {
					if(x<greedx/2)	up=inV+(int)(greedx/2)+(greedx+1); else up=inV-(int)(greedx/2)+(greedx+1);
				}
			}
			if (x==greedx) right=(greedx+1)*y+1;
			if (y==greedy) 
			{
				down=x+greedx+1;
				if (CurrentCmd1==&Tube)	down=x+(greedx+1)*(greedy-1);
				if (CurrentCmd1==&Sphere) {
					if(x<greedx/2)	down=inV+(int)(greedx/2)-(greedx+1); else down=inV-(int)(greedx/2)-(greedx+1);
				}
			}

				pVerts[inV].x=(pVerts1[up].x+pVerts1[inV].x*4+pVerts1[down].x+pVerts1[left].x+pVerts1[right].x)/8.0;
				pVerts[inV].y=(pVerts1[up].y+pVerts1[inV].y*4+pVerts1[down].y+pVerts1[left].y+pVerts1[right].y)/8.0;
				pVerts[inV].z=(pVerts1[up].z+pVerts1[inV].z*4+pVerts1[down].z+pVerts1[left].z+pVerts1[right].z)/8.0;

				pVerts[inV].n1=(pVerts1[up].n1+pVerts1[inV].n1*4+pVerts1[down].n1+pVerts1[left].n1+pVerts1[right].n1)/8.0;
				pVerts[inV].n2=(pVerts1[up].n2+pVerts1[inV].n2*4+pVerts1[down].n2+pVerts1[left].n2+pVerts1[right].n2)/8.0;
				pVerts[inV].n3=(pVerts1[up].n3+pVerts1[inV].n3*4+pVerts1[down].n3+pVerts1[left].n3+pVerts1[right].n3)/8.0;

		}
	}
}
}




/*
float EdgeLen(float x, float y, float z,float x1,float y1, float z1)
{
return (sqrt((z1-z)*(z1-z)+((x1-x)*(x1-x)+(y1-y)*(y1-y))));
}

int MaxEdge(int i)
{


float len[3];

	len[0]=EdgeLen(pVerts1[pInds1[i+0]].x,pVerts1[pInds1[i+0]].y,pVerts1[pInds1[i+0]].z,pVerts1[pInds1[i+1]].x,pVerts1[pInds1[i+1]].y,pVerts1[pInds1[i+1]].z);
	len[1]=EdgeLen(pVerts1[pInds1[i+1]].x,pVerts1[pInds1[i+1]].y,pVerts1[pInds1[i+1]].z,pVerts1[pInds1[i+2]].x,pVerts1[pInds1[i+2]].y,pVerts1[pInds1[i+2]].z);
	len[2]=EdgeLen(pVerts1[pInds1[i+0]].x,pVerts1[pInds1[i+0]].y,pVerts1[pInds1[i+0]].z,pVerts1[pInds1[i+2]].x,pVerts1[pInds1[i+2]].y,pVerts1[pInds1[i+2]].z);

	if (len[2]>len[0]&&len[2]>len[1]) return 2;
	if (len[1]>len[0]&&len[1]>len[2]) return 1;

	return 0;
}

void Subdivide()
{
memcpy(pVerts1,pVerts,NumVerts*sizeof(MyVertex));
memcpy(pInds1,pInds,NumInds*4);

int outI;int outV;
outI=0;outV=0;

for (int i=0;i<NumInds;i+=3)
{
int a=MaxEdge(i);

int p1,p2;
p1=0;p2=0;

if (a==0) {p1=0;p2=1;}
if (a==1) {p1=1;p2=2;}
if (a==2) {p1=0;p2=2;}
//--

	pVerts[outV+0]=pVerts1[pInds1[i+0]];
	pVerts[outV+1]=pVerts1[pInds1[i+1]];
	pVerts[outV+2]=pVerts1[pInds1[i+2]];
	

	pVerts[outV+3].x=(pVerts1[pInds1[i+p1]].x+pVerts1[pInds1[i+p2]].x)/2.0;
	pVerts[outV+3].y=(pVerts1[pInds1[i+p1]].y+pVerts1[pInds1[i+p2]].y)/2.0;
	pVerts[outV+3].z=(pVerts1[pInds1[i+p1]].z+pVerts1[pInds1[i+p2]].z)/2.0;
	pVerts[outV+3].u=(pVerts1[pInds1[i+p1]].u+pVerts1[pInds1[i+p2]].u)/2.0;
	pVerts[outV+3].v=(pVerts1[pInds1[i+p1]].v+pVerts1[pInds1[i+p2]].v)/2.0;
	pVerts[outV+3].n1=(pVerts1[pInds1[i+p1]].n1+pVerts1[pInds1[i+p2]].n1)/2.0;
	pVerts[outV+3].n2=(pVerts1[pInds1[i+p1]].n2+pVerts1[pInds1[i+p2]].n2)/2.0;
	pVerts[outV+3].n3=(pVerts1[pInds1[i+p1]].n3+pVerts1[pInds1[i+p2]].n3)/2.0;
	pVerts[outV+3].color=pVerts1[pInds1[i+p1]].color;

	outV+=4;

//--
if (a==0)
{
	pInds[outI+0]=i/3*4+0;
	pInds[outI+1]=i/3*4+3;
	pInds[outI+2]=i/3*4+2;

	pInds[outI+3]=i/3*4+3;
	pInds[outI+4]=i/3*4+1;
	pInds[outI+5]=i/3*4+2;
}

if (a==1)
{
	pInds[outI+0]=i/3*4+0;
	pInds[outI+1]=i/3*4+1;
	pInds[outI+2]=i/3*4+3;

	pInds[outI+3]=i/3*4+3;
	pInds[outI+4]=i/3*4+2;
	pInds[outI+5]=i/3*4+0;
}

if (a==2)
{
	pInds[outI+0]=i/3*4+0;
	pInds[outI+1]=i/3*4+1;
	pInds[outI+2]=i/3*4+3;

	pInds[outI+3]=i/3*4+1;
	pInds[outI+4]=i/3*4+2;
	pInds[outI+5]=i/3*4+3;
}


//	pInds[outI+3]=outI+0;
//	pInds[outI+4]=outI+1;
//	pInds[outI+5]=outI+2;

	outI+=6;

}


NumVerts=outV;
NumInds=outI;
NumTriangles=outI/3;


}*/

void Loft()
{
int c= Get(CPos,1);

for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
	pVerts[x+y*(greedx+1)].x+=curvearray_x[c][y];
	pVerts[x+y*(greedx+1)].y+=curvearray_y[c][y];
	pVerts[x+y*(greedx+1)].z+=curvearray_z[c][y];
	}
}

}

void InvertSelection()
{

for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
		GSel[y][x]=255-GSel[y][x];
	}

}

}

void NoiseSelection()
{
int stepx=Get(CPos,1);
int stepy=Get(CPos,2);
int ofsx=Get(CPos,3);
int ofsy=Get(CPos,4);
if (ofsx<0) ofsx=0;
if (ofsy<0) ofsy=0;

if (stepx*stepy==0) return;

for (int y=ofsy;y<=greedy;y+=stepy)
{
	for (int x=ofsx;x<=greedx;x+=stepx)
	{
		GSel[y][x]=0;
	}

}

}


void RemoveSelection()
{

for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
		GSel[y][x]=0;
	}

}

}

void SelectAll()
{

for (int y=0;y<=greedy;y++)
{
	for (int x=0;x<=greedx;x++)
	{
		GSel[y][x]=255;
	}

}

}


void SelectG_Sphere()
{
int type=Get(CPos,1);
float sx,sy,sz,rad,dx,dy,dz;
float len;
sx=Get(CPos,2)/1000.0;
sy=Get(CPos,3)/1000.0;
sz=Get(CPos,4)/1000.0;
rad=Get(CPos,5)/1000.0;

#ifdef EditMode
if (Pos==CPos) show_ms(sx,sy,sz,rad);
#endif 

rad/=2.0;
float q=Get(CPos,6)+255;
int it=Get(CPos,7);

for (int y=0;y<=greedy;y++)
{
for (int x=0;x<=greedx;x++)
	{
	dx=pVerts[y*(greedx+1)+x].x-sx;
		dy=pVerts[y*(greedx+1)+x].y-sy;
			dz=pVerts[y*(greedx+1)+x].z-sz;

			len=sqrt(dx*dx+dz*dz+dy*dy);
	
	if (len<rad)
		{
		switch (type)
			{
			case 0:	
			case 1:	
				{
				if (it==0) GSel[y][x]=clamp(q*(1-len/rad),0,255);
				if (it==1) GSel[y][x]=clamp(q*(.5*sin((1-len/rad)*PI-PI/2.0)+.5),0,255);
				if (it==2) GSel[y][x]=clamp(q*exp((1-len/rad)*5-4),0,1255);
				if (it==3) GSel[y][x]=255;
				break;
				}
			case 2:	
				{
				GSel[y][x]=0;
				break;
				}

			}
		}
	else
	{
		if (type==0) {GSel[y][x]=0;}
	}
			

	}
}

}


void SelectG_Cube()
{
int type=Get(CPos,1);
float sx,sy,sz,rad,dx,dy,dz;
float len;
sx=Get(CPos,2)/1000.0;
sy=Get(CPos,3)/1000.0;
sz=Get(CPos,4)/1000.0;
float xsize=Get(CPos,5)/1000.0;
float ysize=Get(CPos,6)/1000.0;
float zsize=Get(CPos,7)/1000.0;
xsize/=2.0;
ysize/=2.0;
zsize/=2.0;

#ifdef EditMode
if (Pos==CPos) show_mc(sx,sy,sz,xsize,ysize,zsize);
#endif 


rad=(xsize+ysize+zsize)/3.0;

float q=Get(CPos,8)+255;
int it=Get(CPos,9);


for (int y=0;y<=greedy;y++)
{
for (int x=0;x<=greedx;x++)
	{
	dx=fabs(pVerts[y*(greedx+1)+x].x-sx);
		dy=fabs(pVerts[y*(greedx+1)+x].y-sy);
			dz=fabs(pVerts[y*(greedx+1)+x].z-sz);

			len=sqrt(dx*dx+dz*dz+dy*dy);
	
	if (dx<xsize&&dy<ysize&&dz<zsize)
		{
		switch (type)
			{
			case 0:	
			case 1:	
				{
				if (it==0) GSel[y][x]=clamp(q*(1-len/rad),0,255);
				if (it==1) GSel[y][x]=clamp(q*(.5*sin((1-len/rad)*PI-PI/2.0)+.5),0,255);
				if (it==2) GSel[y][x]=clamp(q*exp((1-len/rad)*5-4),0,1255);
				if (it==3) GSel[y][x]=255;
				break;
				}
			case 2:	
				{
				GSel[y][x]=0;
				break;
				}

			}
		}
	else
	{
		if (type==0) {GSel[y][x]=0;}
	}
			

	}
}

}

#ifdef EditMode
void iSphere(float _x,float _y, float _z, float _sz);
#endif

void Point()
{
curve_x[curve_len]=Get(CPos,1)/1000.0;
curve_y[curve_len]=Get(CPos,2)/1000.0;
curve_z[curve_len]=Get(CPos,3)/1000.0;

#ifdef EditMode
float sz;

//if ((Pos-CurveCmdPos)==(CPos-CurveCmdPos)) sz=.02; else sz=.01;


pDevice->SetTexture(0,WhiteTexture);
SetAlfa(0);
//iSphere(curve_x[curve_len],curve_y[curve_len],curve_z[curve_len],sz);


#endif


	curve_len++;
}


void MultiTexture()
{
	//1 stage   2 texture 3 transform 4 mixer
	//pDevice->SetTexture(Get(CPos,1),Texture[Get(CPos,2)]);
	SetTexture(Get(CPos,1),Get(CPos,2),2);

	pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_TEXTURETRANSFORMFLAGS,D3DTTFF_COUNT2 );			 
	if (Get(CPos,3)==0)
	{
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_PASSTHRU );
	}

	if (Get(CPos,3)==1)
	{
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR );
	}

	if (Get(CPos,3)==2)
	{
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_SPHEREMAP );
	}

	int mm[10]={D3DTOP_MODULATE,D3DTOP_MODULATE2X,D3DTOP_MODULATE4X,D3DTOP_ADD,D3DTOP_ADDSIGNED,
			D3DTOP_ADDSIGNED2X, D3DTOP_SUBTRACT,D3DTOP_ADDSMOOTH,D3DTOP_MODULATEALPHA_ADDCOLOR,D3DTOP_DOTPRODUCT3};
    

	if (Get(CPos,4)>=0&&Get(CPos,4)<10) 
	{
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLOROP, mm[Get(CPos,4)]);
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_ALPHAOP, mm[Get(CPos,4)]);
	}

	if (Get(CPos,4)==10&&Get(CPos,1)>0)
	{
		pDevice->SetTextureStageState( Get(CPos,1)-1, D3DTSS_COLOROP, D3DTOP_MODULATE );
		pDevice->SetTextureStageState( Get(CPos,1)-1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( Get(CPos,1)-1, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pDevice->SetTextureStageState( Get(CPos,1)-1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1 );
		pDevice->SetTextureStageState( Get(CPos,1)-1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE ); 

		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLOROP, D3DTOP_BUMPENVMAP);
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLORARG2, D3DTA_CURRENT );

		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_BUMPENVMAT00, F2DW(1.0f) );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_BUMPENVMAT01, F2DW(0.0f) );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_BUMPENVMAT10, F2DW(0.0f) );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_BUMPENVMAT11, F2DW(1.0f) );	

	}
	if (Get(CPos,4)==11&&Get(CPos,1)>0)
	{
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLOROP, D3DTOP_MODULATE  );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_COLORARG2, D3DTA_DIFFUSE  );
	
	}
	
	if (Get(CPos,3)==0) pDevice->SetTextureStageState( Get(CPos,1), D3DTSS_TEXCOORDINDEX,Get(CPos,5) );

	

}

void TWaves()
{
int w=greedx+1;
int h=greedy+1;
float xamp=Get(CPos,1)/1000.0;
float yamp=Get(CPos,2)/1000.0;
float fx=Get(CPos,3)*PI/180.0;
float fy=Get(CPos,4)*PI/180.0;
int stage=Get(CPos,6);

float rx,ry,dx,dy;

if (Get(CPos,5)==0)
{
  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
			if (stage==0){
			pVerts[tx+ty*w].v+=xamp*sin((float)tx/(float)w*2*PI+fx);
			pVerts[tx+ty*w].u+=yamp*sin((float)ty/(float)w*2*PI+fy);
			}
			if (stage==1){
			pVerts[tx+ty*w].v1+=xamp*sin((float)tx/(float)w*2*PI+fx);
			pVerts[tx+ty*w].u1+=yamp*sin((float)ty/(float)w*2*PI+fy);
			}
		}
	}
}
else
{
  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
			if (stage==0){
			pVerts[tx+ty*w].u+=xamp*sin((float)tx/(float)w*2*PI+fx);
			pVerts[tx+ty*w].v+=yamp*sin((float)ty/(float)w*2*PI+fy);
			}
			if (stage==1){
			pVerts[tx+ty*w].u1+=xamp*sin((float)tx/(float)w*2*PI+fx);
			pVerts[tx+ty*w].v1+=yamp*sin((float)ty/(float)w*2*PI+fy);
			}

		}
	}
}

}


void TLenz()
{
int w=greedx+1;
int h=greedy+1;
//float x=Get(CPos,1)+w/2;
//float y=-Get(CPos,2)+h/2;
float x=Get(CPos,1)*greedx/3000+w/2.0;
float y=-Get(CPos,2)*greedy/4000+h/2.0;


float rad=Get(CPos,3);
float force=4*(Get(CPos,4))/128.0;
//int f=Get(CPos,5);

int stage=Get(CPos,5);
float angle,pd,rx,ry,dx,dy;

if (x<0||x>=w||y<0||y>=w||rad==0) return;

  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
			pd=sqrt((x-tx)*(x-tx)+(y-ty)*(y-ty));

			if (pd<=fabs(rad))
			{
				angle=1+force*(rad-pd)/rad;	
				
			if (stage==0){
				rx=pVerts[tx+ty*w].u-x*(1/(float)w);ry=pVerts[tx+ty*w].v-y*(1/(float)h);
				pVerts[tx+ty*w].u=rx*angle+x*(1/(float)w);
				pVerts[tx+ty*w].v=ry*angle+y*(1/(float)h);
			}
			if (stage==1){
				rx=pVerts[tx+ty*w].u1-x*(1/(float)w);ry=pVerts[tx+ty*w].v1-y*(1/(float)h);
				pVerts[tx+ty*w].u1=rx*angle+x*(1/(float)w);
				pVerts[tx+ty*w].v1=ry*angle+y*(1/(float)h);
			}
			}
		}
	}


}

void TTwirl()
{

int w=greedx+1;
int h=greedy+1;

float x=Get(CPos,1)*greedx/3000+w/2.0;
float y=-Get(CPos,2)*greedy/4000+h/2.0;
float rad=Get(CPos,3);
float force=Get(CPos,4)/10.0;
int f=Get(CPos,5);
float angle,pd,rx,ry,dx,dy;

int stage=Get(CPos,6);

if (x<0||x>=w||y<0||y>=h||rad==0) return;

  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
			pd=sqrt((float)((x-tx)*(x-tx)+(y-ty)*(y-ty)));

			if (pd<=rad)
			{
				angle=(rad-pd)/rad*PI;	
				angle=force*sin(angle*f)/100.0;
				
				if (stage==0){
			    rx=pVerts[tx+ty*w].u-x/(float)w;
				ry=pVerts[tx+ty*w].v-y/(float)h;
				pVerts[tx+ty*w].u=ry*sin(angle)+rx*cos(angle)+x/(float)w;
				pVerts[tx+ty*w].v=ry*cos(angle)-rx*sin(angle)+y/(float)h;
				}
				if (stage==1){
			    rx=pVerts[tx+ty*w].u1-x/(float)w;
				ry=pVerts[tx+ty*w].v1-y/(float)h;
				pVerts[tx+ty*w].u1=ry*sin(angle)+rx*cos(angle)+x/(float)w;
				pVerts[tx+ty*w].v1=ry*cos(angle)-rx*sin(angle)+y/(float)h;
				}
			}
		}
	}


}

void TRotate()
{

int w=greedx+1;
int h=greedy+1;

float force=Get(CPos,1)/10.0;
float angle,pd,rx,ry,dx,dy;
float x,y;
x=0;y=0;
int stage=Get(CPos,2);

//if (x<0||x>=w||y<0||y>=h||rad==0) return;

  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
				angle=force*3.14/180.0;
				
				if (stage==0){
			    rx=pVerts[tx+ty*w].u-x/(float)w;
				ry=pVerts[tx+ty*w].v-y/(float)h;
				pVerts[tx+ty*w].u=ry*sin(angle)+rx*cos(angle)+x/(float)w;
				pVerts[tx+ty*w].v=ry*cos(angle)-rx*sin(angle)+y/(float)h;
				}
				if (stage==1){
			    rx=pVerts[tx+ty*w].u1-x/(float)w;
				ry=pVerts[tx+ty*w].v1-y/(float)h;
				pVerts[tx+ty*w].u1=ry*sin(angle)+rx*cos(angle)+x/(float)w;
				pVerts[tx+ty*w].v1=ry*cos(angle)-rx*sin(angle)+y/(float)h;
				
			}
		}
	}


}

void TZoom()
{

int w=greedx+1;
int h=greedy+1;

float u=1+Get(CPos,1)/100.0;
float v=1+Get(CPos,2)/100.0;
float angle,pd,rx,ry,dx,dy;
float x,y;
x=0;y=0;
int stage=Get(CPos,3);

//if (x<0||x>=w||y<0||y>=h||rad==0) return;

  for (int ty=0;ty<h;ty++)
	{
		for (int tx=0;tx<w;tx++)
		{
				if (stage==0){
			    rx=pVerts[tx+ty*w].u;
				ry=pVerts[tx+ty*w].v;
				pVerts[tx+ty*w].u=rx*u;
				pVerts[tx+ty*w].v=ry*v;
				}
				if (stage==1){
			    rx=pVerts[tx+ty*w].u1;
				ry=pVerts[tx+ty*w].v1;
				pVerts[tx+ty*w].u1=rx*u;
				pVerts[tx+ty*w].v1=ry*v;
				
			}
		}
	}


}

typedef float (*PVFNt)(float a);
float tsin(float a) {return sin(a);}
float tasin(float a) {return fabs(sin(a));}

void SinWaves()
{
float amp,x,y,freq,ofsx,ofsy;int type;
amp=Get(CPos,1)/1000.0;
freq=Get(CPos,2);
ofsx=Get(CPos,3)/180.0*PI;
ofsy=Get(CPos,4)/180.0*PI;
type=Get(CPos,5);
float f=Get(CPos,6)/100.0;
float s=Get(CPos,7);

PVFNt sinus;
if (s==0) sinus=&tsin; else sinus=&tasin;

if (type==0)
{
	for (y=0;y<=greedy;y++)
	{
		for (x=0;x<=greedx;x++)
		{
		pVerts[(int)(y*(greedx+1)+x)].y=pVerts[(int)(y*(greedx+1)+x)].y*(1+amp*sinus(x/greedx*PI*freq+ofsx))*(1+amp*sinus(y/greedy*PI*freq+ofsy));
		}
	}
}
if (type==1)
{
	for (y=0;y<=greedy;y++)
	{
		for (x=0;x<=greedx;x++)
		{
		float dx=pVerts[(int)(y*(greedx+1)+x)].x-ofsx;
		float dz=pVerts[(int)(y*(greedx+1)+x)].z-ofsy;

		float dist=sqrt(dx*dx+dz*dz);
		pVerts[(int)(y*(greedx+1)+x)].y=pVerts[(int)(y*(greedx+1)+x)].y*(1+amp*sinus(dist*PI*freq+f))*(1+amp*sinus(dist*PI*freq+f));
		}
	}
}


}


void RWave()
{
float amp,amp2,x,y,freqx,freqy,ofsx,ofsy;int type;
amp=Get(CPos,1)/1000.0;
amp2=Get(CPos,2)/1000.0;
freqx=Get(CPos,3);
freqy=Get(CPos,4);
ofsx=Get(CPos,5)/180.0*PI;
ofsy=Get(CPos,6)/180.0*PI;
type=Get(CPos,7);

if (type==0)
{
	for (y=0;y<greedy;y++)
	{
		for (x=0;x<greedx;x++)
		{
		pVerts[(int)(y*greedx+x)].x=pVerts[(int)(y*greedx+x)].x*(1+amp*sin(x/greedx*PI*freqx+ofsx))*(1+amp2*sin(y/greedy*PI*freqy+ofsy));
		pVerts[(int)(y*greedx+x)].y=pVerts[(int)(y*greedx+x)].y*(1+amp*sin(x/greedx*PI*freqx+ofsx))*(1+amp2*sin(y/greedy*PI*freqy+ofsy));
		pVerts[(int)(y*greedx+x)].z=pVerts[(int)(y*greedx+x)].z*(1+amp*sin(x/greedx*PI*freqx+ofsx))*(1+amp2*sin(y/greedy*PI*freqy+ofsy));
		}
	}
}

if (type==1)
{
	for (y=0;y<greedy;y++)
	{
		for (x=0;x<greedx;x++)
		{
		pVerts[(int)(y*greedx+x)].x=pVerts[(int)(y*greedx+x)].x*(1-amp*fabs(sin(x/greedx*PI*freqx+ofsx)))*(1-amp2*fabs(sin(y/greedy*PI*freqy+ofsy)));
		pVerts[(int)(y*greedx+x)].y=pVerts[(int)(y*greedx+x)].y*(1-amp*fabs(sin(x/greedx*PI*freqx+ofsx)))*(1-amp2*fabs(sin(y/greedy*PI*freqy+ofsy)));
		pVerts[(int)(y*greedx+x)].z=pVerts[(int)(y*greedx+x)].z*(1-amp*fabs(sin(x/greedx*PI*freqx+ofsx)))*(1-amp2*fabs(sin(y/greedy*PI*freqy+ofsy)));
		}
	}
}

	
}


void LoftW()
{
int h;
h=greedy;if (h>16) h=16;
	int i=0;
	for (int py=0;py<=h;py++)
	{
		float w=Get(CPos,1+py)/100.0;
		for (int px=0;px<=greedx;px++)
		{
			pVerts[i].x*=1+w;
			pVerts[i].z*=1+w;
			i++;
		}
	}
}


void LoftY()
{
int h;
h=greedy;if (h>16) h=16;
	int i=0;
	for (int py=0;py<=h;py++)
	{
		float w=Get(CPos,1+py)/1000.0;
		for (int px=0;px<=greedx;px++)
		{
			pVerts[i].y+=w;
			i++;
		}
	}
}

void Zoom()
{
float x,y,z;
x=Get(CPos,1)/1000.0;
	y=Get(CPos,2)/1000.0;
	z=Get(CPos,3)/1000.0;
	int i=0;
	for (int py=0;py<=greedy;py++)
	{
		for (int px=0;px<=greedx;px++)
		{
			float q=GSel[py][px]/256.0;	
			pVerts[i].x*=1+x*q;
			pVerts[i].y*=1+y*q;
			pVerts[i].z*=1+z*q;
			i++;
		}
	}
}

void Skew()
{
	float x,y,z;
	x=Get(CPos,1)/1000.0;
	y=Get(CPos,2)/1000.0;
	z=Get(CPos,3)/1000.0;

	int i=0;

	for (int py=0;py<=greedy;py++)
	{
		for (int px=0;px<=greedx;px++)
		{
			float q=GSel[py][px]/256.0;	
			pVerts[i].x+=x*q*pVerts[i].y;
			pVerts[i].y+=y*q*pVerts[i].x;
			pVerts[i].z+=z*q*pVerts[i].y;
			i++;
		}
	}
}

void Trapezium()
{
	float x,y,z;
	x=Get(CPos,1)/1000.0;
	y=Get(CPos,2)/1000.0;
	z=Get(CPos,3)/1000.0;

	int i=0;

	for (int py=0;py<=greedy;py++)
	{
		for (int px=0;px<=greedx;px++)
		{
			float q=GSel[py][px]/256.0;	
			pVerts[i].x*=1+x*q*pVerts[i].y;
			pVerts[i].y*=1+y*q*pVerts[i].x;
			pVerts[i].z*=1+z*q*pVerts[i].y;
			i++;
		}
	}
}

void Move()
{
float x,y,z;
//SelectAll();
x=Get(CPos,1)/1000.0;
	y=Get(CPos,2)/1000.0;
	z=Get(CPos,3)/1000.0;
//for (int i=0;i<NumVerts;i++)
	int i=0;
	for (int py=0;py<=greedy;py++)
	{
		for (int px=0;px<=greedx;px++)
		{
		//if (GSel[(int)(i/greedx)][i%greedx]==1)
			float q=GSel[py][px]/256.0;
			{
			pVerts[i].x+=x*q;
			pVerts[i].y+=y*q;
			pVerts[i].z+=z*q;
			}
			i++;
		}
	}
}

void CopyUVtoUV1()
{
	for (int i=0;i<NumVerts;i++) {pVerts[i].u1=pVerts[i].u;pVerts[i].v1=pVerts[i].v;}
}

void TRoll()
{
float x,y,z;
x=Get(CPos,1)/1000.0;
	y=Get(CPos,2)/1000.0;
	int stage = Get(CPos,3);

for (int i=0;i<NumVerts;i++)
	{
		if (stage==0){ pVerts[i].u+=x;	pVerts[i].v+=y;}
		if (stage==1){ pVerts[i].u1+=x;	pVerts[i].v1+=y;}

	}
}

void Tile()
{
float x,y,z;
x=Get(CPos,1);
	y=Get(CPos,2);
int stage=Get(CPos,3);

for (int i=0;i<NumVerts;i++)
	{
		if (stage==0){pVerts[i].u*=x;pVerts[i].v*=y;}
		if (stage==1){pVerts[i].u1*=x;pVerts[i].v1*=y;}

	}
}

void TFlip()
{
int axis;
axis=Get(CPos,1);
int stage=Get(CPos,2);	
if (axis==0)
{
	for (int i=0;i<NumVerts;i++)
	{
	if (stage==0) pVerts[i].u*=-1;
	if (stage==1) pVerts[i].u1*=-1;
	}
}
else
{
	for (int i=0;i<NumVerts;i++)
	{
	if (stage==0) pVerts[i].v*=-1;
	if (stage==1) pVerts[i].v1*=-1;
	}
}

}



void Rotate()
{
float x,y,z,dx,dy,dz,angle;int axis;int i;
	angle=((double)Get(CPos,1))*PI/1800.0;
	axis=Get(CPos,2);
	if (axis<0||axis>2) return;
	dx=Get(CPos,3)/1000.0;
	dy=Get(CPos,4)/1000.0;
	dz=Get(CPos,5)/1000.0;
	float astp=Get(CPos,6)/10.0;
		
switch(axis)
	{
		case 0:
		i=0;
		for (int py=0;py<=greedy;py++)
		{
			for (int px=0;px<=greedx;px++)
			{
				float q=GSel[py][px]/256.0;
				x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
				pVerts[i].z=z+dz;
				pVerts[i].x=lerp(y*sin(angle)+x*cos(angle)+dx,pVerts[i].x,q);
				pVerts[i].y=lerp(y*cos(angle)-x*sin(angle)+dy,pVerts[i].y,q);
				i++;
			}
		}
			break;
		case 1:
			i=0;
			for (int py=0;py<=greedy;py++)
			{
				for (int px=0;px<=greedx;px++)
				{
				float q=GSel[py][px]/256.0;
				x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
				pVerts[i].y=y+dy;
				pVerts[i].x=lerp(z*sin(angle)+x*cos(angle)+dx,pVerts[i].x,q);
				pVerts[i].z=lerp(z*cos(angle)-x*sin(angle)+dz,pVerts[i].z,q);
				i++;
				}
			}
			break;
		case 2:
			i=0;
			for (int py=0;py<=greedy;py++)
			{
				for (int px=0;px<=greedx;px++)
				{
				float q=GSel[py][px]/256.0;
				x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
				pVerts[i].x=x+dx;
				pVerts[i].y=lerp(z*sin(angle)+y*cos(angle)+dy,pVerts[i].y,q);
				pVerts[i].z=lerp(z*cos(angle)-y*sin(angle)+dz,pVerts[i].z,q);
				i++;
				}
			}
			break;
	}
}

void SXYtoUV()
{
int stage=Get(CPos,1);
float scaleU=1-Get(CPos,2)/1000.0;
float scaleV=1-Get(CPos,3)/1000.0;
int type=Get(CPos,4);
int i;
if (type==0) {
for (i=0;i<NumVerts;i++) {
	if (stage==0){
		pVerts[i].u=(asin(pVerts[i].x)/PI)*scaleU+.5;
		pVerts[i].v=(asin(pVerts[i].y)/PI)*scaleV+.5;
		}
	if (stage==1){
		pVerts[i].u1=pVerts[i].n1*scaleU;
		pVerts[i].v1=pVerts[i].n2*scaleV;
		}
	}
}
}

void XYZtoUV()
{
int stage=Get(CPos,1);
float scaleU=1-Get(CPos,2)/1000.0;
float scaleV=1-Get(CPos,3)/1000.0;
int type=Get(CPos,4);
int i;
if (type==0) {
for (i=0;i<NumVerts;i++) {
	if (stage==0){
		pVerts[i].u=pVerts[i].x*scaleU;
		pVerts[i].v=pVerts[i].y*scaleV;
		}
	if (stage==1){
		pVerts[i].u1=pVerts[i].x*scaleU;
		pVerts[i].v1=pVerts[i].y*scaleV;
		}
	}
}

if (type==1) {
for (i=0;i<NumVerts;i++) {
	if (stage==0){
		pVerts[i].u=pVerts[i].x*scaleU;
		pVerts[i].v=pVerts[i].z*scaleV;
		}
	if (stage==1){
		pVerts[i].u1=pVerts[i].x*scaleU;
		pVerts[i].v1=pVerts[i].z*scaleV;
		}
	}
}

if (type==2) {
for (i=0;i<NumVerts;i++) {
	if (stage==0){
		pVerts[i].u=pVerts[i].y*scaleU;
		pVerts[i].v=pVerts[i].z*scaleV;
		}
	if (stage==1){
		pVerts[i].u1=pVerts[i].y*scaleU;
		pVerts[i].v1=pVerts[i].z*scaleV;
		}
	}
}

}

void WTwirl()
{
float x,y,z,dx,dy,dz,angle,a,amp;int axis;int i;
	angle=Get(CPos,1)*PI/180.0;
	axis=Get(CPos,2);
	if (axis<0||axis>2) return;
	dx=Get(CPos,3)/1000.0;
	dy=Get(CPos,4)/1000.0;
	dz=Get(CPos,5)/1000.0;
	amp=Get(CPos,6)/1000.0;
switch(axis)
	{
		case 0:
			for (i=0;i<NumVerts;i++)
			{
			a=angle+pVerts[i].z*amp;
			x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
			pVerts[i].z=z+dz;
			pVerts[i].x=y*sin(a)+x*cos(a)+dx;
			pVerts[i].y=y*cos(a)-x*sin(a)+dy;
			}
			break;
		case 1:
			for (i=0;i<NumVerts;i++)
			{
			a=angle+pVerts[i].y*amp;
			x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
			pVerts[i].y=y+dy;
			pVerts[i].x=z*sin(a)+x*cos(a)+dx;
			pVerts[i].z=z*cos(a)-x*sin(a)+dz;
			}
			break;
		case 2:
			for (i=0;i<NumVerts;i++)
			{
			a=angle+pVerts[i].x*amp;
			x=pVerts[i].x-dx;y=pVerts[i].y-dy;z=pVerts[i].z-dz;
			pVerts[i].x=x+dx;
			pVerts[i].y=z*sin(a)+y*cos(a)+dy;
			pVerts[i].z=z*cos(a)-y*sin(a)+dz;
			}
			break;
	}
}

void QCRotate()
{
float qamp,aa,x,y,z,dx,dy,dz,angle;int axis;int i;
	angle=Get(CPos,1)*PI/180.0;
	axis=Get(CPos,2);
	if (axis<0||axis>2) return;
	qamp=Get(CPos,3);
	aa=angle;

		for (i=0;i<NumVerts;i+=4)
			{
			dx=(pVerts[i].x+pVerts[i+1].x)/2.0;
			dy=(pVerts[i].y+pVerts[i+3].y)/2.0;;
			dz=(pVerts[i].z+pVerts[i+2].z)/2.0;
				
				angle=aa+sin(i/30.0)*qamp*PI/180.0;
			
				for (int qcc=0;qcc<4;qcc++)
				{

				switch(axis)
				{
				case 0:
					x=pVerts[i+qcc].x-dx;y=pVerts[i+qcc].y-dy;z=pVerts[i+qcc].z-dz;
					pVerts[i+qcc].z=z+dz;
					pVerts[i+qcc].x=y*sin(angle)+x*cos(angle)+dx;
					pVerts[i+qcc].y=y*cos(angle)-x*sin(angle)+dz;
					break;
				case 1:
					x=pVerts[i+qcc].x-dx;y=pVerts[i+qcc].y-dy;z=pVerts[i+qcc].z-dz;
					pVerts[i+qcc].y=y+dy;
					pVerts[i+qcc].x=z*sin(angle)+x*cos(angle)+dx;
					pVerts[i+qcc].z=z*cos(angle)-x*sin(angle)+dz;
					break;
				case 2:
					x=pVerts[i+qcc].x-dx;y=pVerts[i+qcc].y-dy;z=pVerts[i+qcc].z-dz;
					pVerts[i+qcc].x=x+dx;
					pVerts[i+qcc].y=z*sin(angle)+y*cos(angle)+dy;
					pVerts[i+qcc].z=z*cos(angle)-y*sin(angle)+dz;
					break;
				}

				}
		}
}

//----
void PartOut()
{
//int count=Get(CPos,1);

//if (count<NumTriangles&&count>=0) NumTriangles=count;

vbout_start=Get(CPos,1);
vbout_end=Get(CPos,2);
}

void Limit()
{
float x=Get(CPos,1)/1000.0;
float y=Get(CPos,2)/1000.0;
float z=Get(CPos,3)/1000.0;
float xs=Get(CPos,4)/1000.0;
float ys=Get(CPos,5)/1000.0;
float zs=Get(CPos,6)/1000.0;

int i;
		i=0;
		for (int py=0;py<=greedy;py++)
		{
			for (int px=0;px<=greedx;px++)
			{
				float q=GSel[py][px]/256.0;
				if (pVerts[i].x>(x+xs)) pVerts[i].x=lerp(x+xs,pVerts[i].x,q);
				if (pVerts[i].x<(x-xs)) pVerts[i].x=lerp(x-xs,pVerts[i].x,q);

				if (pVerts[i].y>(y+ys)) pVerts[i].y=lerp(y+ys,pVerts[i].y,q);
				if (pVerts[i].y<(y-ys)) pVerts[i].y=lerp(y-ys,pVerts[i].y,q);

				if (pVerts[i].z>(z+zs)) pVerts[i].z=lerp(z+zs,pVerts[i].z,q);
				if (pVerts[i].z<(z-zs)) pVerts[i].z=lerp(z-zs,pVerts[i].z,q);
				i++;
			}
		}


}


void _SetShader(int sn)
{
int texture=sh_tex;
int texture1=sh_tex1;
int texture2=sh_tex2;

int material=sh_mat;
float height=sh_height;
//int sn=Get(CPos,1);

if (sn<0) return;
if(CustomPS[sn]==NULL||CustomVS[sn]==NULL) return;
//pDevice->SetVertexShader(Shader_VSBase3D);

D3DMATRIX w;D3DXMATRIX ma,mb,mc;
ma=World;mb=View;
D3DXMatrixMultiply(&ma,&ma,&mb);
mb=Projection;mc=ma;
D3DXMatrixMultiply(&ma,&ma,&mb);
w=ma;

D3DXHANDLE h0,h1;
h0 = pCtC[sn]->GetConstantByName(NULL, "matWorldView");
pCtC[sn]->SetMatrix(pDevice, h0, &mc);


h0 = pCtC[sn]->GetConstantByName(NULL, "matWorldViewProjection");
pCtC[sn]->SetMatrix(pDevice, h0, &ma);

ma=View;
h0 = pCtC[sn]->GetConstantByName(NULL, "matView");
pCtC[sn]->SetMatrix(pDevice, h0, &ma);

    D3DXVECTOR4 ambientMtrl;
     D3DXVECTOR4 diffuseMtrl;
	 D3DXVECTOR4 specMtrl;

	ambientMtrl.x=Material[material].Ambient.r;
	ambientMtrl.y=Material[material].Ambient.g;
	ambientMtrl.z=Material[material].Ambient.b;
	ambientMtrl.w=Material[material].Ambient.a;

h0 = pCtC[sn]->GetConstantByName(NULL, "ambient");

     pCtC[sn]->SetVector(pDevice, h0, &ambientMtrl);

	diffuseMtrl.x=Material[material].Diffuse.r;
	diffuseMtrl.y=Material[material].Diffuse.g;
	diffuseMtrl.z=Material[material].Diffuse.b;
	diffuseMtrl.w=Material[material].Diffuse.a;

h0 = pCtC[sn]->GetConstantByName(NULL, "diffuse");

     pCtC[sn]->SetVector(pDevice, h0, &diffuseMtrl);


	specMtrl.x=Material[material].Specular.r;
	specMtrl.y=Material[material].Specular.g;
	specMtrl.z=Material[material].Specular.b;
	specMtrl.w=Material[material].Specular.a;

h0 = pCtC[sn]->GetConstantByName(NULL, "specular");

     pCtC[sn]->SetVector(pDevice, h0, &specMtrl);


	 float sp=Material[material].Power/10.0;
h0 = pCtC[sn]->GetConstantByName(NULL, "specularPower");
     pCtC[sn]->SetFloat(pDevice, h0, sp);

	 D3DXVECTOR4 vecLight;
	 vecLight.x=SceneLight[0].Direction.x;
	 vecLight.y=SceneLight[0].Direction.y;
	 vecLight.z=SceneLight[0].Direction.z;
	 vecLight.w=0;
 //D3DXVECTOR4 vecLight(-0.57f, 0.57f, -0.57f, 0.0f);


h0 = pCtC[sn]->GetConstantByName(NULL, "vecLight");

     pCtC[sn]->SetVector(pDevice, h0, &vecLight);

 //float height= Get(CPos,5)/255.0;
h0 = pCtC[sn]->GetConstantByName(NULL, "height");

     pCtC[sn]->SetFloat(pDevice, h0, height);

	 float bumpV=sh_bumpV;
h0 = pCtC[sn]->GetConstantByName(NULL, "bumpV");

     pCtC[sn]->SetFloat(pDevice, h0, bumpV);

float duv,nuv;
duv=1+sh_dUV/10.0;nuv=1+sh_nUV/10.0;
h0 = pCtCp[sn]->GetConstantByName(NULL, "dUV");

     pCtCp[sn]->SetFloat(pDevice, h0, duv);

h0 = pCtCp[sn]->GetConstantByName(NULL, "nUV");

     pCtCp[sn]->SetFloat(pDevice, h0, nuv);


//видовой вектор
D3DXMATRIX mat_world, mat_view;
mat_world=World;mat_view=View;
D3DXMATRIX mat_temp,mat_view_inverse;
D3DXVECTOR4  view_pos;
//mat_temp = mat_world * mat_view;
D3DXMatrixMultiply(&mat_temp,&mat_world,&mat_view);
D3DXMatrixInverse(&mat_view_inverse,NULL,&mat_temp);
D3DXVec4Transform(&view_pos,(D3DXVECTOR4*)&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),&mat_view_inverse);


h0 = pCtC[sn]->GetConstantByName(NULL, "vecViewPos");

     pCtC[sn]->SetVector(pDevice, h0, &view_pos);

ma=World;
h0 = pCtC[sn]->GetConstantByName(NULL, "matWorld");
pCtC[sn]->SetMatrix(pDevice, h0, &ma);

//--------
{


D3DMATRIX w;D3DXMATRIX ma,mb,mc;
ma=World;mb=View;
D3DXMatrixMultiply(&ma,&ma,&mb);
mb=Projection;mc=ma;
D3DXMatrixMultiply(&ma,&ma,&mb);
w=ma;

D3DXHANDLE h0,h1;
h0 = pCtCp[sn]->GetConstantByName(NULL, "matWorldView");
pCtCp[sn]->SetMatrix(pDevice, h0, &mc);


h0 = pCtCp[sn]->GetConstantByName(NULL, "matWorldViewProjection");
pCtCp[sn]->SetMatrix(pDevice, h0, &ma);

ma=View;
h0 = pCtCp[sn]->GetConstantByName(NULL, "matView");
pCtCp[sn]->SetMatrix(pDevice, h0, &ma);

    D3DXVECTOR4 ambientMtrl;
     D3DXVECTOR4 diffuseMtrl;
	 D3DXVECTOR4 specMtrl;

	ambientMtrl.x=Material[material].Ambient.r;
	ambientMtrl.y=Material[material].Ambient.g;
	ambientMtrl.z=Material[material].Ambient.b;
	ambientMtrl.w=Material[material].Ambient.a;

h0 = pCtCp[sn]->GetConstantByName(NULL, "ambient");

     pCtCp[sn]->SetVector(pDevice, h0, &ambientMtrl);

	diffuseMtrl.x=Material[material].Diffuse.r;
	diffuseMtrl.y=Material[material].Diffuse.g;
	diffuseMtrl.z=Material[material].Diffuse.b;
	diffuseMtrl.w=Material[material].Diffuse.a;

h0 = pCtCp[sn]->GetConstantByName(NULL, "diffuse");

     pCtCp[sn]->SetVector(pDevice, h0, &diffuseMtrl);


	specMtrl.x=Material[material].Specular.r;
	specMtrl.y=Material[material].Specular.g;
	specMtrl.z=Material[material].Specular.b;
	specMtrl.w=Material[material].Specular.a;

h0 = pCtCp[sn]->GetConstantByName(NULL, "specular");

     pCtCp[sn]->SetVector(pDevice, h0, &specMtrl);

	 float sp=Material[material].Power/10.0;
h0 = pCtCp[sn]->GetConstantByName(NULL, "specularPower");
     pCtCp[sn]->SetFloat(pDevice, h0, sp);



	 D3DXVECTOR4 vecLight;
	 vecLight.x=SceneLight[0].Direction.x;
	 vecLight.y=SceneLight[0].Direction.y;
	 vecLight.z=SceneLight[0].Direction.z;
	 vecLight.w=0;
 //D3DXVECTOR4 vecLight(-0.57f, 0.57f, -0.57f, 0.0f);


h0 = pCtCp[sn]->GetConstantByName(NULL, "vecLight");

     pCtCp[sn]->SetVector(pDevice, h0, &vecLight);

 //float height= Get(CPos,5)/255.0;
h0 = pCtCp[sn]->GetConstantByName(NULL, "height");

     pCtCp[sn]->SetFloat(pDevice, h0, height);

	 float bumpV=sh_bumpV;
h0 = pCtCp[sn]->GetConstantByName(NULL, "bumpV");

     pCtCp[sn]->SetFloat(pDevice, h0, bumpV);


duv=1+sh_dUV/10.0;nuv=1+sh_nUV/10.0;
h0 = pCtCp[sn]->GetConstantByName(NULL, "dUV");

     pCtCp[sn]->SetFloat(pDevice, h0, duv);

h0 = pCtCp[sn]->GetConstantByName(NULL, "nUV");

     pCtCp[sn]->SetFloat(pDevice, h0, nuv);

//видовой вектор
D3DXMATRIX mat_world, mat_view;
mat_world=World;mat_view=View;
D3DXMATRIX mat_temp,mat_view_inverse;
D3DXVECTOR4  view_pos;
//mat_temp = mat_world * mat_view;
D3DXMatrixMultiply(&mat_temp,&mat_world,&mat_view);
D3DXMatrixInverse(&mat_view_inverse,NULL,&mat_temp);
D3DXVec4Transform(&view_pos,(D3DXVECTOR4*)&D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),&mat_view_inverse);


h0 = pCtCp[sn]->GetConstantByName(NULL, "vecViewPos");

     pCtCp[sn]->SetVector(pDevice, h0, &view_pos);

ma=World;
h0 = pCtCp[sn]->GetConstantByName(NULL, "matWorld");
pCtCp[sn]->SetMatrix(pDevice, h0, &ma);

}

//------

pDevice->SetTexture(D3DVERTEXTEXTURESAMPLER0, Texture[texture]);
pDevice->SetTexture(D3DVERTEXTEXTURESAMPLER1, Texture[texture1]);

pDevice->SetTexture(1, Texture[texture1]);
  pDevice->SetSamplerState(1,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(1,D3DSAMP_MINFILTER,2);


  pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER0,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(D3DVERTEXTEXTURESAMPLER1,D3DSAMP_MINFILTER,2);

pDevice->SetTexture(2, Texture[texture2]);
  pDevice->SetSamplerState(2,D3DSAMP_MAGFILTER,2);
  pDevice->SetSamplerState(2,D3DSAMP_MINFILTER,2);


//pDevice->SetTexture(6, Texture[sh_scr]);
//pDevice->SetTexture(7, Texture[sh_z]);
  SetTexture(6,sh_scr,0);
  SetTexture(7,sh_z,0);

//pDevice->SetPixelShader(Shader_PSBase3D);
  pDevice->SetVertexShader(CustomVS[sn]);
  pDevice->SetPixelShader(CustomPS[sn]);



}



void CompileShaderToSlot()
{
int slot=Get(CPos,1);
memcpy(SSTable+64*slot,Pack+CPos+256-33,33);
currentShader=CPos;
//CompileShaderFF(SSTable+64*slot,slot);
				int result=ReCompileShaders(shaderText,shaderTextLen,SSTable+64*slot);
//				if (result==0) MessageBox(hWnd0,"Compiled Ok",SSTable+64*slot,0);
				if (result==1) MessageBox(hWnd0,"vs error",SSTable+64*slot,0);
				if (result==2) MessageBox(hWnd0,"ps error",SSTable+64*slot,0);
				if (result==3) MessageBox(hWnd0,"error",SSTable+64*slot,0);
}

void SetShader()
{

	if (Get(CPos,1)==0)
	{
		pDevice->SetPixelShader(NULL);
		pDevice->SetVertexShader(NULL);
		setshader_flag=0;
	}
	if (Get(CPos,1)>0)
	{
		CurrentShader=Get(CPos,1);
		setshader_flag=1;
		sh_mat=Get(CPos,4);
		sh_tex=Get(CPos,2);
		sh_tex1=Get(CPos,3);
		sh_tex2=Get(CPos,6);
		sh_height=Get(CPos,5)/255.0;
		sh_bumpV=Get(CPos,7)/10.0;
		sh_scr=Get(CPos,8);
		sh_z=Get(CPos,9);
		sh_dUV=Get(CPos,10);
		sh_nUV=Get(CPos,11);
		_SetShader(CurrentShader);
	}

}

