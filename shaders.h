//--------shaders code--------

static IDirect3DVertexShader9  *CustomVS[64];
static IDirect3DPixelShader9  *CustomPS[64];
int currentShader=0;
int shaderTextLen=0;

static IDirect3DVertexShader9  *Shader_VSBase; //simple vs with textel to pixel correction
static const char vs_base[] = \
"void vs_main(inout float4 Pos  : POSITION0, inout float2 uv: TEXCOORD0)"
"{"
//"uv=1/1024.0+.5+float2(.5,-.5)*Pos.xy;"
//"uv=.5/512.0+.5+float2(.5,-.5)*Pos.xy;"
//"uv-=39.0/100000.0;"
//"uv.y-=.55/768.0;"
//"uv.x-=.55/1024.0;"
"}";

static IDirect3DPixelShader9  *Shader_Posterize;
static IDirect3DPixelShader9  *Shader_Shadow;
static IDirect3DPixelShader9  *Shader_XYZ;
static IDirect3DPixelShader9  *Shader_Z;
static IDirect3DPixelShader9  *Shader_NormalMap;
static IDirect3DPixelShader9  *Shader_NewPerlin;
static IDirect3DPixelShader9  *Shader_FastMapBlur;
static IDirect3DPixelShader9  *Shader_FastBlur;
static IDirect3DPixelShader9  *Shader_FastRBlur;
static IDirect3DPixelShader9  *Shader_CopyAFromT;
static IDirect3DPixelShader9  *Shader_NULL;
static IDirect3DPixelShader9  *Shader_FULL;
static IDirect3DPixelShader9  *Shader_Blur1;
static IDirect3DPixelShader9  *Shader_Blur2;
static IDirect3DPixelShader9  *Shader_Blur3;
static IDirect3DPixelShader9  *Shader_Blur4;
static IDirect3DPixelShader9  *Shader_tex;
static IDirect3DPixelShader9  *Shader_Invert;
static IDirect3DPixelShader9  *Shader_InvertA;
static IDirect3DPixelShader9  *Shader_ClearRGB;
static IDirect3DPixelShader9  *Shader_ClearAlpha;
static IDirect3DPixelShader9  *Shader_Emboss2;
static IDirect3DPixelShader9  *Shader_Sharp;
static IDirect3DPixelShader9  *Shader_Glow;
static IDirect3DPixelShader9  *Shader_AdjustColor;
static IDirect3DPixelShader9  *Shader_SinColor;
static IDirect3DPixelShader9  *Shader_Palette;
static IDirect3DPixelShader9  *Shader_Julia;
static IDirect3DPixelShader9  *Shader_Displace;
static IDirect3DPixelShader9  *Shader_SDisplace;
static IDirect3DPixelShader9  *Shader_RDisplace;
static IDirect3DPixelShader9  *Shader_RGBDisplace;
static IDirect3DPixelShader9  *Shader_RadialDisplace;
static IDirect3DPixelShader9  *Shader_Desaturate;
static IDirect3DPixelShader9  *Shader_SumToAlpha;
static IDirect3DPixelShader9  *Shader_TModAToAlpha;
static IDirect3DPixelShader9  *Shader_InvTModAToAlpha;
static IDirect3DPixelShader9  *Shader_AtoRGB;
static IDirect3DPixelShader9  *Shader_Contrast;
static IDirect3DPixelShader9  *Shader_ScaleColor;
static IDirect3DPixelShader9  *Shader_Crossfade;
static IDirect3DPixelShader9  *Shader_Halftone;

static IDirect3DVertexShader9  *Shader_VSBase3D;
static IDirect3DPixelShader9  *Shader_PSBase3D;

ID3DXBuffer *tmp;




/*"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"float d=1-tex2D(xyz,texCoord).r;"
"float4 c=float4(texCoord.x,1-texCoord.y,d-1.0/32.0,0);"
"float4 c2=mul(c-.5,s2l);"
"float4 c3=.25*c2/(1-d+1.0/32.0)+.5;"
"float lZ=1-tex2D(lightdepth,float2(c3.x,1-c3.y)).r;"
"float shadow=0;"
"if (c2.z+.5<1-lZ) {"
//"shadow =abs(lZ)-abs(d);}"
"shadow =1;}"
//"if (shadow<0) shadow=0;"
//"if (shadow>0) shadow=0;"
//"return float4(saturate(tex2D(src,texCoord)+shadow));"
"return float4(shadow,shadow,shadow,1);"
"};";*/

static const char ps_shadow[] = \
"float4x4 view;"
"float4x4 light;"
"float4x4 proj;"
"float4x4 vp;"
"float4x4 lvp;"
"float power;"
"sampler xyz: register(s0);"
"sampler lightdepth: register(s1);"
"sampler src: register(s2);"
"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"float4 pos=tex2D(xyz,texCoord)-.5;"
//"pos.x*=4.0/3.0;"
"float4 pv=mul(pos,light);"
"pv=pv/(pv.z+1/32.0);"
//"float shadow=-(tex2D(lightdepth,pv.xy+.5).r-(pos.z+.5))/2.0;"
"float shadow=(tex2D(lightdepth,pv.xy+.5).r-(pos.z+.5));"
"if (shadow<0.1) shadow=0; else shadow=1-shadow; "
//"if (shadow<0) shadow=0;"
"if (shadow>1) shadow=1;"
"return float4(saturate(tex2D(src,texCoord)-shadow));"
//"return float4(shadow,shadow,shadow,1);"
"};";



static const char ps_z[] = \
"sampler depth: register(s0);"
"float rx;"
"float ry;"
"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"float d=((1.0-tex2D(depth,float2(texCoord.x*rx,texCoord.y*ry)).r)*32.0);"
"	return float4(d,d,d, 1.0);"
"};";

static const char ps_xyz[] = \
"float4 v1;"
"float4x4 tP;"
"float4x4 tPi;"
"float4x4 tVI;"
"float4x4 tV;"
"float rx;"
"float ry;"
"sampler depth: register(s0);"
"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"float d=1-tex2D(depth,texCoord).r;"
"float4 c=float4(texCoord.x,1-texCoord.y,d-1.0/32.0,0);"
"float4 c2=mul(c-.5,tVI);"
"float4 c3=.25*c2/(1-d+1.0/32.0)+.5-v1/4;"
"	return float4(c3.x,1-c3.y,c3.z, 1.0);"
"};";

static const char ps_halftone[] = \
"sampler iChannel0: register(s0);"
"float dpi:register(c0);"
"float tresh:register(c1);"
"float angle:register(c2);"
"float color:register(c3);"
"float sind(float a)"
"{"
"	return sin(a * 3.14/180.0);"
"}"
"float cosd(float a)"
"{"
"	return cos(a * 3.14/180.0);"
"}"
"float added(float2 sh, float sa, float ca, float2 c, float d)"
"{"
"	return 0.5 + 0.25 * cos((sh.x * sa + sh.y * ca + c.x) * d) + 0.25 * cos((sh.x * ca - sh.y * sa + c.y) * d);"
"}"
"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"	float threshold = clamp(float(tresh) + 0.6, 0.0, 1.0);"
"	float2 rotationCenter = float2(0.5, 0.5);"
"	float2 shift = texCoord - rotationCenter;"
"	float rasterPattern = added(shift, sind(angle), cosd(angle), rotationCenter, dpi);"
"	float4 srcPixel = tex2D(iChannel0, texCoord);"
"	float avg = 0.2125 * srcPixel.r + 0.7154 * srcPixel.g + 0.0721 * srcPixel.b;"
"    float gray = (rasterPattern * threshold + avg - threshold) / (1.0 - threshold);"
"srcPixel=lerp(float4(1.0,1.0,1.0,1.0),srcPixel,color);"
"return float4(gray*srcPixel.r,gray*srcPixel.g,gray*srcPixel.b,1.0);"
"};";


static const char ps_normalmap[] = \
"float TextureSize: register(c0);"
"sampler BaseMap: register(s0);"
"float4 ps_main(float2 texCoord: TEXCOORD) : COLOR {"
"float4 lightness=(.3,.59,.11,1);"
"   float off = 1.0 / TextureSize;"
"   float4 s00 = tex2D(BaseMap, texCoord + float2(-off, -off));"
"   float4 s01 = tex2D(BaseMap, texCoord + float2( 0,   -off));"
"   float4 s02 = tex2D(BaseMap, texCoord + float2( off, -off));"
"   float4 s10 = tex2D(BaseMap, texCoord + float2(-off,  0));"
"   float4 s12 = tex2D(BaseMap, texCoord + float2( off,  0));"
"   float4 s20 = tex2D(BaseMap, texCoord + float2(-off,  off));"
"   float4 s21 = tex2D(BaseMap, texCoord + float2( 0,    off));"
"   float4 s22 = tex2D(BaseMap, texCoord + float2( off,  off));"
"   float4 sobelX = s00 + 2 * s10 + s20 - s02 - 2 * s12 - s22;"
"   float4 sobelY = s00 + 2 * s01 + s02 - s20 - 2 * s21 - s22;"
"   float sx = dot(sobelX, lightness);"
"   float sy = dot(sobelY, lightness);"
"   float3 normal = normalize(float3(sx, sy, 1));"
"   return float4(normal * 0.5 + 0.5, 1);"
"};";


static const char ps_newperlin[] = \
"float o1:register(c3);"
"float o2:register(c4);"
"float o3:register(c5);"
"float o4:register(c6);"
"float o5:register(c7);"
"float o6:register(c8);"
"float o7:register(c9);"
"float o8:register(c10);"
"float hash( in float n ) "
"{"
" return (frac(sin(dot(n ,float2(12.9898,78.233)*2.0)) * 43758.5453-frac(sin(n)*43758.5453)));"
"}"
"float noise( in float3 x ) "
"{"
"	float3 p = floor(x);"
"	float3 f = frac(x);"
"	f = f*f*(3.0-2.0*f);"
"	float n = p.x + p.y*57.0 + 113.0*p.z;"
"	float res = lerp(lerp(lerp( hash(n + 0.0), hash(n + 1.0),f.x),"
"			lerp( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),"
"		    lerp(lerp( hash(n+113.0), hash(n+114.0),f.x),"
"			lerp( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);"
"	return res;"
"}"
"float fbm( in float3 p )"
"{"
"	float f = 0.0;"
"	f += 0.5000*noise( p+float3(0,o1,0) ); p*=2.02;"
"	f += 0.2500*noise( p+float3(0,o2,0) ); p*=2.03;"
"	f += 0.1250*noise( p +float3(0,o3,0)); p*=2.01;"
"	f += 0.0625*noise( p+float3(0,o4,0) ); p*=2.00;"
"	f += 0.0625/2*noise( p+float3(0,o5,0) ); p*=1.99;"
"	f += 0.0625/4*noise( p+float3(0,o6,0) ); p*=1.98;"
"	f += 0.0625/8*noise( p+float3(0,o7,0) ); p*=1.97;"
"	f += 0.0625/16*noise( p+float3(0,o8,0) );"
"	return f;"
"}"
"float x:register(c0);"
"float y:register(c1);"
"float zm:register(c2);"
"float4 ps_main(float2 vp:TEXCOORD0):color"
"{"
"float2 uv = (vp-.5) * zm;"
"	float c = 0.0;"
"	c = fbm(float3(uv.x-x  , uv.y+y , 1));"
"	return  float4 (c,c,c,1);"
"}";

static const char ps_fastblur[] = \
"sampler s0: register (s0);"
"float R:register (c0);"
"float Width :register (c1);"
"float bp :register (c2);"
"float sc :register (c3);"
"float noise :register (c4);"
"float pt :register (c5);"
"float4 ps_main(float2 vp:TEXCOORD0):color"
"{"
" float rn=(frac(sin(pt+dot(vp ,float2(12.9898,78.233)*2.0)) * 43758.5453));"
"	float2 x=vp;"
"   float lod=1+Width*lerp(1,rn,noise);"
"    float4 c=(bp,bp,bp,bp);"
"    float2 off=1/R*pow(2,lod)*saturate(lod-1);"
"    c+=tex2Dlod(s0,float4(x+float2(0,0)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,1)*off,0,lod));"
"    off*=1.6;"
"    c+=tex2Dlod(s0,float4(x+float2(0,1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(0,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,0)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,0)*off,0,lod));"
"   c*=sc;"
"   c/=9;"
"    return saturate(c);"
"};";



static const char ps_fastrblur[] = \
"sampler s0: register (s0);"
"float R:register (c0);"
"float bp :register (c1);"
"float sc :register (c2);"
"float i :register (c3);"
"float xc :register (c4);"
"float yc :register (c5);"
"float Width :register (c6);"
"float4 ps_main(float2 vp:TEXCOORD0):color"
"{"
"	float2 x=vp;"
"   float lod=R;"
"float4 c=(bp,bp,bp,bp);"
"    float2 off=Width;"
"int p;"
" for (p=0;p<i;p++)"
" {"
"    c+=tex2Dlod(s0,float4((x-.5)*(1-p*off)+.5+float2(xc,yc)*p*off,0,lod+0));"
" }"
"c=c*sc/i;"
"    return saturate(c);"
"};";

//todo
static const char ps_fastmapblur[] = \
"sampler s0: register (s0);"
"sampler s1: register (s1);"
"float R:register (c0);"
"float Width :register (c1);"
"float bp :register (c2);"
"float sc :register (c3);"
"float noise :register (c4);"
"float pt :register (c5);"
"float amp :register (c6);"
"float phase :register (c7);"
"float q :register (c8);"	

"float4 ps_main(float2 vp:TEXCOORD0):color"
"{"
" float rn=(frac(sin(pt+dot(vp ,float2(12.9898,78.233)*2.0)) * 43758.5453));"
"	float2 x=vp;"
"float4 map=tex2D(s1,x);"
"map=max(map.x,max(map.y,map.z));"
"map=lerp(map,pow(cos(clamp(map*q+phase,0,1)*2*3.14)/2+.5,1),amp);"
"   float lod=1+map.x*Width*lerp(1,rn,noise);"
"    float4 c=(bp,bp,bp,bp);"
"    float2 off=1/R*pow(2,lod)*saturate(lod-1);"
"    c+=tex2Dlod(s0,float4(x+float2(0,0)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,1)*off,0,lod));"
"    off*=1.6;"
"    c+=tex2Dlod(s0,float4(x+float2(0,1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(0,-1)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(-1,0)*off,0,lod));"
"    c+=tex2Dlod(s0,float4(x+float2(1,0)*off,0,lod));"
"   c*=sc;"
"   c/=9;"
"    return saturate(c);"
"};";


static const char ps_posterize[] = \
"sampler tex1: register (s0);"
"float levels : register(c0);"
"float cGamma : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 _color = tex2D(tex1, u);"
"    float3 tc = _color.xyz;"
"    tc = pow(tc, cGamma);"
"    tc = tc * levels;"
"    tc = floor(tc);"
"    tc = tc / levels;"
"    tc = pow(tc,1.0/cGamma);"
"    return float4(tc,_color.w);"
//"return t;"
"};";


static const char ps_tex[] = \
"sampler tex1: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"return tex2D(tex1,u);"
"};";

static const char ps_crossfade[] = \
"sampler tex1: register (s0);"
"float w : register(c0);"
"float h : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=tex2D(tex1,u);"
"float4 d1=tex2D(tex1,float2(1-u.x,u.y));"
"float q=clamp(-abs(u.x-.5)+.5,0,w)/w/2;"
"float4 d2=d*(q+.5)+d1*(.5-q);"
"float4 d3=tex2D(tex1,float2(u.x,1-u.y));"
"float q2=clamp(-abs(u.y-.5)+.5,0,h)/h/2;"
"float4 d4=d2*(q2+.5)+d3*(.5-q2);"
"return d4;"
"};";


static const char ps_clearRGB[] = \
"sampler tex1: register (s0);"
"float r : register(c0);"
"float g : register(c1);"
"float b : register(c2);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=tex2D(tex1,u);"
"d.r=r;"
"d.g=g;"
"d.b=b;"
"return d;"
"};";

static const char ps_clearA[] = \
"sampler tex1: register (s0);"
"float a : register(c0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=tex2D(tex1,u);"
"d.a=a;"
"return d;"
"};";

static const char ps_invert[] = \
"sampler tex1: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=(1,1,1,1);"
"d.r=1-tex2D(tex1,u).r;"
"d.g=1-tex2D(tex1,u).g;"
"d.b=1-tex2D(tex1,u).b;"
"d.a=1-tex2D(tex1,u).a;"
"return d;"
"};";

static const char ps_scalecolor[] = \
"sampler tex1: register (s0);"
"float r : register(c0);"
"float g : register(c1);"
"float b : register(c2);"
"float a : register(c3);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=tex2D(tex1,u);"
"d.r*=r;"
"d.g*=g;"
"d.b*=b;"
"d.a*=a;"
"return d;"
"};";

static const char ps_invertA[] = \
"sampler tex1: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 d=tex2D(tex1,u);"
"d.a=1.0-d.a;"
"return d;"
"};";

static const char ps_sharp[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float a : register(c0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=tex2D(tex1,u)+a*(tex2D(tex1,u)-tex2D(tex2,u));"
"  return c;"
"};";

static const char ps_glow[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float a : register(c0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=tex2D(tex1,u)+a*tex2D(tex2,u);"
"  return c;"
"};";


static const char ps_emboss2[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float x : register(c0);"
"float y : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=.5-tex2D(tex2,u)/2+tex2D(tex2,float2(u.x+x,u.y+y))/2;"
"  return c;"
"};";

/*
static const char ps_emboss2[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float a : register(c0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=tex2D(tex2,u)*a/tex2D(tex1,u);"
"  return c;"
"};";*/


static const char ps_adjustcolor[] = \
"float3 HUEtoRGB(in float H){"
"	H=frac(H);"
"	float R = abs(H * 6 - 3) - 1;"
"	float G = 2 - abs(H * 6 - 2);"
"	float B = 2 - abs(H * 6 - 4);"
"	return saturate(float3(R,G,B));"
"}"
"float3 HSLtoRGB(in float3 HSL)"
"{"
"	float3 RGB = HUEtoRGB(HSL.x);"
"	float C = (1 - abs(2 * HSL.z - 1)) * HSL.y;"
"	return (RGB - 0.5) * C + HSL.z;"
"} "
"float3 RGBtoHSL(in float3 RGB){"
"	float3 HSL = 0;"
"	float U, V;"
"	U = -min(RGB.r, min(RGB.g, RGB.b));"
"	V = max(RGB.r, max(RGB.g, RGB.b));"
"	HSL.z = (V - U) * 0.5;"
"	float C = V + U;"
"	if (C != 0){"
"		float3 Delta = (V - RGB) / C;"
"		Delta.rgb -= Delta.brg;"
"		Delta.rgb += float3(2,4,6);"
"		Delta.brg = step(V, RGB) * Delta.brg;"
"		HSL.x = max(Delta.r, max(Delta.g, Delta.b));"
"		HSL.x = frac(HSL.x / 6);"
"		HSL.y = C / (1 - abs(2 * HSL.z - 1));"
"	}"
"	return HSL;"
"}"
"sampler tex1: register (s0);"
"float Hue: register(c0);"
"float Saturation: register(c1);"
"float Contrast: register(c2);"
"float Brightness: register(c3);"
"float HueCycles: register(c4);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 c=tex2D(tex1,u);"
"    float3 h=RGBtoHSL(c.rgb);"
"    h.x=frac(h.x+Hue)*HueCycles;"
"    h.y=h.y*Saturation;"
"    c.rgb=HSLtoRGB(h);"
"    c.rgb=normalize(c.rgb)*sqrt(3)*pow(length(c.rgb)/sqrt(3),pow(2,Contrast))*pow(2,Brightness);"
"    return c;"
"}";


static const char ps_sincolor[] = \
"sampler tex1: register (s0);"
"float r : register(c0);"
"float g : register(c1);"
"float b : register(c2);"
"float a : register(c3);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=tex2D(tex1,u);"
"c.r=sin(c.r*r);"
"c.g=sin(c.g*g);"
"c.b=sin(c.b*b);"
"c.a=r*sin(c.a*a);"
"  return c;"
"};";

static const char ps_palette[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 c=tex2D(tex1,u);"
"c.r=tex2D(tex2,float2(c.r,0)).r;"
"c.g=tex2D(tex2,float2(c.g,0)).g;"
"c.b=tex2D(tex2,float2(c.b,0)).b;"
"  return c;"
"};";


static const char ps_julia[] = \
"float a : register(c0);"
"float b : register(c1);"
"float c : register(c2);"
"float z : register(c3);"
"float st : register(c4);"
"float f : register(c5);"
"float f2 : register(c6);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"  float density = c;"
"  float x = (u.x - 0.5) * z;"
"  float y = (u.y - 0.5) * z;"
"  float x2;"
"  float y2;"
"  float xy;"
"  float r = 1.0;"
"  float k=density;"
" float g;"
"float2 h;"
"float aaa;"
"  while((k > 0.0) && (r < 4.0))"
"  {"
"    x2 = x * x;"
"    y2 = y* y;"
"    xy = x * y;"
"    x = x2 - y2 + a;"
"    y = st * xy+ b;"
"h=(x-x2,y-y2);"
"aaa=(r+k)*length(h)*.01;"
"   x2+=lerp(0,x*sin(aaa)+y*cos(r+k+length(aaa)),f2);"
"   y2+=lerp(0,x*cos(aaa)-y*sin(r+k+length(aaa)),f2);"
"    r = x2+y2;"
"    k--;"
"  }"
"float jj=1-lerp(k,(4*k/r),f) / density;"
"  return float4 (jj,jj,jj,jj);"
"};";

 


static const char ps_blurV1[] = \
"sampler tex1: register (s0);"
"int q : register(c0);"
"float px : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 sum = 0;"
"    int weightSum = 0;"
"int i;"
"    for (i = 0; i < q; i++)"
"    {"
"       float2 cord = float2(u.x, u.y + (q-i-1)*2/px);"
"       sum += tex2D(tex1, cord) * (i+1);"
"       weightSum += (i+1);"
"    }"
"    sum /= weightSum;"
//"    return float4(sum.rgb, 1);"
"    return sum;"
"}";

static const char ps_blurV2[] = \
"sampler tex1: register (s0);"
"int q : register(c0);"
"float px : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 sum = 0;"
"    int weightSum = 0;"
"int i;"
"    for (i = 0; i < q; i++)"
"    {"
"       float2 cord = float2(u.x, u.y - (q-i-1)*2/px);"
"       sum += tex2D(tex1, cord) * (i+1);"
"       weightSum += (i+1);"
"    }"
"    sum /= weightSum;"
//"    return float4(sum.rgb, 1);"
"    return sum;"
"}";

static const char ps_blurH1[] = \
"sampler tex1: register (s0);"
"int q : register(c0);"
"float px : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 sum = 0;"
"    int weightSum = 0;"
"int i;"
"    for (i = 0; i < q; i++)"
"    {"
"       float2 cord = float2(u.x+ (q-i-1)*2/px, u.y );"
"       sum += tex2D(tex1, cord) * (i+1);"
"       weightSum += (i+1);"
"    }"
"    sum /= weightSum;"
//"    return float4(sum.rgb, 1);"
"    return sum;"
"}";

static const char ps_blurH2[] = \
"sampler tex1: register (s0);"
"int q : register(c0);"
"float px : register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"    float4 sum = 0;"
"    int weightSum = 0;"
"int i;"
"    for (i = 0; i < q; i++)"
"    {"
"       float2 cord = float2(u.x- (q-i-1)*2/px, u.y );"
"       sum += tex2D(tex1, cord) * (i+1);"
"       weightSum += (i+1);"
"    }"
"    sum /= weightSum;"
//"    return float4(sum.rgb, 1);"
"    return sum;"
"}";


static const char ps_rgbdisplace[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float r1 : register(c0);"
"float g1: register(c1);"
"float b1: register(c2);"
"float r2: register(c3);"
"float g2: register(c4);"
"float b2: register(c5);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex2,u);"
"vector red = tex2D (tex1,float2 (u.x+b.r*r1,u.y+b.g*r2));"
"vector green = tex2D (tex1,float2 (u.x+b.r*g1,u.y+b.g*g2));"
"vector blue = tex2D (tex1,float2 (u.x+b.r*b1,u.y+b.g*b2));"
"vector sum = vector (red.r,green.g,blue.b,b.a);"
"return sum;"
"}";

static const char ps_radialdisplace[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float amp : register(c0);"
"float amp2 : register(c1);"
"float amp3 : register(c2);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex2,u);"
"vector red = tex2D (tex1,float2 (.5+(u.x-.5)/(b.r*amp+1),.5+(u.y-.5)/(b.g*amp+1)));"
"vector green = tex2D (tex1,float2 (.5+(u.x-.5)/(b.r*amp2+1),.5+(u.y-.5)/(b.g*amp2+1)));"
"vector blue = tex2D (tex1,float2 (.5+(u.x-.5)/(b.r*amp3+1),.5+(u.y-.5)/(b.g*amp3+1)));"
"vector sum = vector (red.r,green.g,blue.b,b.a);"
"return sum;"
"}";

static const char ps_displace[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float amp1 : register(c0);"
"float amp2: register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex2,u);"
"vector a = tex2D (tex1,float2 (u.x+b.r*amp1,u.y+b.g*amp2));"
"return a;"
"}";

static const char ps_sdisplace[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float amp1 : register(c0);"
"float amp2: register(c1);"
"float ox: register(c2);"
"float oy: register(c3);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex2,float2 (u.x+ox,u.y+oy))-.5;"
"vector a = tex2D (tex1,float2 (u.x+b.r*amp1,u.y+b.g*amp2));"
"return a;"
"}";

static const char ps_rdisplace[] = \
"sampler tex1: register (s0);"
"sampler tex2: register (s1);"
"float amp1 : register(c0);"
"float amp2: register(c1);"
"float amp3: register(c2);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex2,u);"
"float j1=.5+.5*sin(amp1*b.r);"
"float j2=.5+.5*cos(amp1*b.r);"
//"vector a = tex2D (tex1,float2 (.5+(u.x-.5)/(b.r*amp1+1),.5+(u.y-.5)/(b.g*amp1+1)));"
"vector a = tex2D (tex1,float2 ( j1+(u.x-j1)/(b.r*amp1+1),j2+(u.y-j2)/(b.g*amp1+1) ) );"
"return a;"
"}";

static const char ps_null[] = \
"sampler tex: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector a = tex2D (tex,u);"
"a.r=0;"
"a.g=0;"
"a.b=0;"
"return a;"
"}";

static const char ps_full[] = \
"sampler tex: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector a = tex2D (tex,u);"
"a.r=1;"
"a.g=1;"
"a.b=1;"
"return a;"
"}";


static const char ps_desaturate[] = \
"sampler tex: register (s0);"
"float q : register (c0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector a = tex2D (tex,u);"
"float sum;"
"sum=(a.r+a.g+a.b)/3.0;"
"a.r=lerp(a.r,sum,q);"
"a.g=lerp(a.g,sum,q);"
"a.b=lerp(a.b,sum,q);"
"return a;"
"}";


static const char ps_atorgb[] = \
"sampler tex: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 a = tex2D (tex,u);"
"a.r=a.a;"
"a.g=a.a;"
"a.b=a.a;"
"return a;"
"}";

//modulate alfa (current.a, [texture.a])
static const char ps_tamodtoalpha[] = \
"sampler tex: register (s0);"
"sampler tex1: register (s1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector a = tex2D (tex1,u);"
"vector b = tex2D (tex,u);"
"b.a=a.a*b.a;"
"return b;"
"}";

//modulate alfa (current.a, 1-[texture.a])
static const char ps_invtamodtoalpha[] = \
"sampler tex: register (s0);"
"sampler tex1: register (s1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex,u);"
"vector a = tex2D (tex1,u);"
"b.a*=(1.0-a.a);"
"return b;"
"}";

static const char ps_afromt[] = \
"sampler tex: register (s0);"
"sampler tex1: register (s1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"vector b = tex2D (tex,u);"
"b.a=tex2D (tex1,u).a;"
"return b;"
"}";

static const char ps_sumtoalpha[] = \
"sampler tex: register (s0);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 a = tex2D (tex,u);"
"a.a=(a.r+a.g+a.b)/3.0;"
"return a;"
"}";

static const char ps_contrast[] = \
"sampler tex: register (s0);"
"float level : register(c0);"
"float br: register(c1);"
"float4 ps_main(float2 u:TEXCOORD0):color"
"{"
"float4 a = saturate (tex2D (tex,u)*level+br);"
"return a;"
"}";

//-----

/*"float4 ps_main(float2 u:texcoord):color"
"{"
"float ang=atan2(u.x-.5,u.y-.5);"
"float dst=1-dot(u-.5,u-.5)*4;"
"float a=sin(ang*11)*dst;"
"return float4(a,0,0,1);"
"}";



"float4 ps_main(float2 u: texcoord) : color"
"{"
"return float4 0.5*(u.y,0,0,1);"
"}";*/



//------

static const char vs_base3d[] = \
"float4x4 matWorldViewProjection;"
"float4x4 matWorld;"    //Мировая матрица."
"float4x4 matView;"    //Мировая матрица."
"float4 vecLight;"   //Позиция источника света
"float4 vecViewPos;" //Видовой вектор
"float4 vecEye;"      //Позиция наблюдателя
"float4 ambient;"
"float4 diffuse;"
"float height;"
"sampler Texture0:register (s0);"
"sampler Texture1:register (s1);"
"struct VS_INPUT"
"{"
"   float4 Position : POSITION0;"
"   float2 TexCoords : TEXCOORD;"
"   float4 Normal : NORMAL;"
"};"
"struct VS_OUTPUT "
"{"
"   float4 Position : POSITION0;"
"   float2 TexCoords : TEXCOORD;"
"	float4 color:COLOR;"
"};"
"VS_OUTPUT vs_main(VS_INPUT Input)"
"{"
"   VS_OUTPUT Output;"
"    Input.Normal.w   = 0.0f;"
"	float4 vl=normalize(vecLight);"
"	float4 vl2=normalize(vecLight);"
"	vl.w=0;"
"    vl = mul(vl, matView);"
"	Input.Normal=Input.Normal+float4(tex2Dlod(Texture1,float4(Input.TexCoords,0,0)).rgb-.5,1);"
//"	Input.Normal=float4(tex2Dlod(Texture1,float4(Input.TexCoords,0,0)).rgb-.5,1);"
"	Input.Normal=normalize(Input.Normal);"
"	float4 nm=Input.Normal;"
"     Input.Normal = mul(Input.Normal, matView);"
"   float4 ofs=tex2Dlod(Texture0,float4(Input.TexCoords,0,0));"
"	ofs.a=1.0;"
//"   Output.Position = mul(Input.Position*(1+(ofs-.5)*height),matWorldViewProjection);"
"Input.Position+=ofs.x*height*Input.Normal;"
"   Output.Position = mul(Input.Position,matWorldViewProjection);"
//"	Input.Normal=
"   Output.TexCoords = Input.TexCoords;"
"	float s = dot(vl, Input.Normal);"
"   if(s < 0.0f) s = 0.0f;"
"	nm=normalize(mul(matWorld,nm));"
"	float3 reflect_vec=reflect(-normalize(vecViewPos),nm);"
"	float sp=clamp(dot(reflect_vec, vl2),0,1);"
"	Output.color=1.2*pow(sp,16)+diffuse*s+ambient;"
"   return Output;"
"}";

static const char ps_base3d[] = \
"sampler Texture0;"
"sampler Texture1;"
"float4 ps_main(float4 color:COLOR,float4 TexCoords:TEXCOORD0) : COLOR0"
"{   "
//"float4 ofs=tex2D(Texture1, TexCoords)/4.0;"
"   return color*tex2D(Texture0, TexCoords);"
"}";


void CreateShaders()
{

D3DXCompileShader( vs_base3d, sizeof(vs_base3d)-1, 0, 0, "vs_main", "vs_3_0", 0, &tmp, 0, &pCt );
pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &Shader_VSBase3D );

D3DXCompileShader( ps_base3d, sizeof(ps_base3d)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_PSBase3D );

D3DXCompileShader( ps_posterize, sizeof(ps_posterize)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, NULL );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Posterize );



D3DXCompileShader( ps_adjustcolor, sizeof(ps_adjustcolor)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_AdjustColor );

D3DXCompileShader( ps_glow, sizeof(ps_glow)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Glow );

D3DXCompileShader( ps_emboss2, sizeof(ps_emboss2)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Emboss2 );


D3DXCompileShader( ps_sharp, sizeof(ps_sharp)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Sharp );
	
D3DXCompileShader( ps_sincolor, sizeof(ps_sincolor)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_SinColor );

D3DXCompileShader( ps_palette, sizeof(ps_palette)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Palette );


D3DXCompileShader( ps_julia, sizeof(ps_julia)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Julia );

D3DXCompileShader( vs_base, sizeof(vs_base)-1, 0, 0, "vs_main", "vs_3_0", 0, &tmp, 0, 0 );
pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &Shader_VSBase );

D3DXCompileShader( ps_desaturate, sizeof(ps_desaturate)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Desaturate );

D3DXCompileShader( ps_sumtoalpha, sizeof(ps_sumtoalpha)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_SumToAlpha );

D3DXCompileShader( ps_afromt, sizeof(ps_afromt)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_CopyAFromT );

D3DXCompileShader( ps_tamodtoalpha, sizeof(ps_tamodtoalpha)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_TModAToAlpha );

D3DXCompileShader( ps_invtamodtoalpha, sizeof(ps_invtamodtoalpha)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_InvTModAToAlpha );

D3DXCompileShader( ps_contrast, sizeof(ps_contrast)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Contrast );

D3DXCompileShader( ps_displace, sizeof(ps_displace)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Displace );

D3DXCompileShader( ps_sdisplace, sizeof(ps_sdisplace)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_SDisplace );


D3DXCompileShader( ps_rdisplace, sizeof(ps_rdisplace)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_RDisplace );


D3DXCompileShader( ps_rgbdisplace, sizeof(ps_rgbdisplace)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_RGBDisplace );

D3DXCompileShader( ps_radialdisplace, sizeof(ps_radialdisplace)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_RadialDisplace );

D3DXCompileShader( ps_blurV1, sizeof(ps_blurV1)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Blur1 );
D3DXCompileShader( ps_blurV2, sizeof(ps_blurV2)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Blur2 );
D3DXCompileShader( ps_blurH1, sizeof(ps_blurH1)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Blur3 );
D3DXCompileShader( ps_blurH2, sizeof(ps_blurH2)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Blur4 );

D3DXCompileShader( ps_null, sizeof(ps_null)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_NULL );

D3DXCompileShader( ps_full, sizeof(ps_full)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_FULL );

D3DXCompileShader( ps_tex, sizeof(ps_tex)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_tex );

D3DXCompileShader( ps_invert, sizeof(ps_invert)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Invert );

D3DXCompileShader( ps_invertA, sizeof(ps_invertA)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_InvertA );

D3DXCompileShader( ps_clearRGB, sizeof(ps_clearRGB)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_ClearRGB );

D3DXCompileShader( ps_atorgb, sizeof(ps_atorgb)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_AtoRGB );


D3DXCompileShader( ps_clearA, sizeof(ps_clearA)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_ClearAlpha );

D3DXCompileShader( ps_scalecolor, sizeof(ps_scalecolor)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_ScaleColor );

D3DXCompileShader( ps_crossfade, sizeof(ps_crossfade)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Crossfade );

D3DXCompileShader( ps_fastblur, sizeof(ps_fastblur)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_FastBlur );

D3DXCompileShader( ps_fastrblur, sizeof(ps_fastrblur)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_FastRBlur );

D3DXCompileShader( ps_fastmapblur, sizeof(ps_fastmapblur)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_FastMapBlur );

D3DXCompileShader( ps_newperlin, sizeof(ps_newperlin)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_NewPerlin );

D3DXCompileShader( ps_normalmap, sizeof(ps_normalmap)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_NormalMap );

D3DXCompileShader( ps_halftone, sizeof(ps_halftone)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Halftone );

D3DXCompileShader( ps_xyz, sizeof(ps_xyz)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, &pCt2 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_XYZ );

D3DXCompileShader( ps_shadow, sizeof(ps_shadow)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, &pCt3 );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Shadow );

D3DXCompileShader( ps_z, sizeof(ps_z)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, NULL );
pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &Shader_Z );

//custom shaders
for(int ttt=0;ttt<64;ttt++) {
CustomVS[ttt]=NULL;
CustomPS[ttt]=NULL;
}


int s=1;

//for(s=0;s<3;s++)
{
//	D3DXCompileShader( vs_custom, sizeof(vs_custom)-1, 0, 0, "vs_main", "vs_3_0", 0, &tmp, 0, &pCt );
//	if (D3D_OK==D3DXCompileShaderFromFile("shaders.txt", NULL,NULL,"vs_main", "vs_3_0", 0, &tmp, 0, &pCtC[s] )) pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &CustomVS[s] ); else MessageBox(hWnd0,"vs error","error",0);
//	if (D3D_OK==D3DXCompileShaderFromFile("shaders.txt", NULL,NULL,"ps_main", "ps_3_0", 0, &tmp, 0, 0 )) pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &CustomPS[s] );else MessageBox(hWnd0,"ps error","error",0);

	//pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &CustomVS[s] );

	//D3DXCompileShader( ps_custom, sizeof(ps_custom)-1, 0, 0, "ps_main", "ps_3_0", 0, &tmp, 0, 0 );
	//pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &CustomPS[s] );
}

}

int CompileShaderFF(char* name,int s)
{
	
char vsname[64];char psname[64];
strcpy(vsname,"vs_");
strcat(vsname,name);
strcpy(psname,"ps_");
strcat(psname,name);

	if (D3D_OK==D3DXCompileShaderFromFile("shaders.txt", NULL,NULL,vsname, "vs_3_0", 0, &tmp, 0, &pCtC[s] )) pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &CustomVS[s] ); else MessageBox(hWnd0,"vs error","error",0);
	if (D3D_OK==D3DXCompileShaderFromFile("shaders.txt", NULL,NULL,psname, "ps_3_0", 0, &tmp, 0, &pCtCp[s] )) pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &CustomPS[s] );else MessageBox(hWnd0,"ps error","error",0);
return 0;
}



int ReCompileShaders(char* buff,int len,char* name)
{
LPD3DXBUFFER pE,vE;
//to do: get error text
char vsname[64];char psname[64];
strcpy(vsname,"vs_");
strcat(vsname,name);
strcpy(psname,"ps_");
strcat(psname,name);

int s=Get(currentShader,1);
int retV=0;int retP=0;
//for(s=0;s<3;s++)
{
	if (D3D_OK==D3DXCompileShader(buff,len,0,0,vsname, "vs_3_0", 0, &tmp, 0, &pCtC[s] )) pDevice->CreateVertexShader( (DWORD*)tmp->GetBufferPointer(), &CustomVS[s] ); else retV=1;
	if (D3D_OK==D3DXCompileShader(buff,len,0,0,psname, "ps_3_0", 0, &tmp, 0, &pCtCp[s] )) pDevice->CreatePixelShader( (DWORD*)tmp->GetBufferPointer(), &CustomPS[s] ) ; else retP= 1;
	
	if (retV==1&&retP==1) return 3;
	if (retP==1) return 2;
	if (retV==1) return 1;

	return 0;
}
}
