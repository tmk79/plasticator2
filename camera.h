//-camera 



float cam_a;

void SetView(int i)
{
if (i==1) pDevice->SetTransform(D3DTS_VIEW, &StartMatrix); 
if (i==0) 
{
#ifdef EditMode
	if (camstate==-1) 
		{
			pDevice->SetTransform(D3DTS_VIEW, &View2); 
		}
		else
		{
			pDevice->SetTransform(D3DTS_VIEW, &View); 
		}
#endif

#ifndef EditMode
pDevice->SetTransform(D3DTS_VIEW, &View);
#endif
}
}

void SetWorld(int i)
{
if (i==1) pDevice->SetTransform(D3DTS_WORLD, &StartMatrix); 
if (i==0) pDevice->SetTransform(D3DTS_WORLD, &World); 
}


void SetProjecton(int t)
{
	float Vw=1;
	float Vh;
	if (t==0) Vh=screen_height/screen_width;
	if (t==1) Vh=1;
	if (t==2) Vh=800.0f/1280.0;

	//if (camstate==-1)
	{

	if (t==0)
	{
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

		return;
	}
	
	if (t==1)
	{
		float Zf=100*8;
		float Zn=0.5f;
		D3DMATRIX Projection2 = 
		{
			2*Zn/Vw, 0, 0, 0,
			0, 2*Zn/Vh, 0, 0,
			0, 0, Zf/(Zf-Zn*2), 1,
			0, 0, -Zf/(Zf-Zn)*Zn/32, 0,//+cam_zoom,
		};

		Projection=Projection2;
		pDevice->SetTransform(D3DTS_PROJECTION, &Projection);

		return;
	}


	}
}

