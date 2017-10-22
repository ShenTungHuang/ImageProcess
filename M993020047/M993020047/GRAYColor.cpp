// GRAYColor.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "GRAYColor.h"


// GRAYColor dialog

IMPLEMENT_DYNAMIC(GRAYColor, CDialog)

GRAYColor::GRAYColor(CWnd* pParent /*=NULL*/)
	: CDialog(GRAYColor::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	G_r=NULL;
	G_g=NULL;
	G_b=NULL;
	grayimage=NULL;
	height=0;
	width=0;

}

GRAYColor::~GRAYColor()
{
	int i;

	if(R)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] R[i]; delete [] R;
	}
	if(G)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] G[i]; delete [] G;
	}
	if(B)															//釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] B[i]; delete [] B;
	}

	if(G_r)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] G_r[i]; delete [] G_r;
	}
	if(G_g)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] G_g[i]; delete [] G_g;
	}
	if(G_b)															//釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] G_b[i]; delete [] G_b;
	}

	if(grayimage) delete grayimage;

}

void GRAYColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GRAYColor, CDialog)
	ON_BN_CLICKED(IDC_RADIO2level, &GRAYColor::OnBnClickedRadio2level)
	ON_BN_CLICKED(IDC_RADIO4level, &GRAYColor::OnBnClickedRadio4level)
	ON_BN_CLICKED(IDC_RADIO8level, &GRAYColor::OnBnClickedRadio8level)
	ON_BN_CLICKED(IDC_RADIO16level, &GRAYColor::OnBnClickedRadio16level)
	ON_BN_CLICKED(IDC_RADIO32level, &GRAYColor::OnBnClickedRadio32level)
	ON_BN_CLICKED(IDC_RADIO64level, &GRAYColor::OnBnClickedRadio64level)
	ON_BN_CLICKED(IDC_RADIO128level, &GRAYColor::OnBnClickedRadio128level)
	ON_BN_CLICKED(IDC_RADIO256level, &GRAYColor::OnBnClickedRadio256level)
END_MESSAGE_MAP()


// GRAYColor message handlers
void GRAYColor::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(R) 
	{
		for(i=0;i<height;i++) delete [] R[i]; delete [] R;
	}
	if(G)
	{
		for(i=0;i<height;i++) delete [] G[i]; delete [] G;
	}
	if(B)
	{
		for(i=0;i<height;i++) delete [] B[i]; delete [] B;
	}

	//開啟記憶體紀錄R、G、B
	R=new int * [height]; 
    for(i=0;i<height;i++) R[i]=new int [width];

    G=new int * [height]; 
    for(i=0;i<height;i++) G[i]=new int [width];

    B=new int * [height]; 
    for(i=0;i<height;i++) B[i]=new int [width];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R[i][j]=Input_R[i][j];
			G[i][j]=Input_G[i][j];
			B[i][j]=Input_B[i][j];
		}
	}
}
void GRAYColor::OnBnClickedRadio2level()
{	
		G_r=new int * [height]; 
		for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

		G_g=new int * [height]; 
		for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

		G_b=new int * [height]; 
		for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

		CClientDC dc(this);
		grayimage = new CDIBSectionLite();
		grayimage->CreateEmptyDIB(width,height,24);

		for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
			{
				G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

			if (G_r[i][j] <= 125 )
				G_r[i][j] = 0;
			else
			  G_r[i][j] = 255;

				grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
			}
		}
		grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio4level()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

				if (G_r[i][j] <= 64 )
				{
					if(G_r[i][j] <= 32)
						G_r[i][j] = 0;
					else
						G_r[i][j] = 64;
				}
				else if(G_r[i][j] > 64 && G_r[i][j] <= 128)
				{
					if(G_r[i][j] <= 96)
						G_r[i][j] = 64;
					else
						G_r[i][j] = 128;
				}

				else if (G_r[i][j] > 128 && G_r[i][j] <= 190)
				{
					if(G_r[i][j] <= 160)
						G_r[i][j] = 128;
					else
						G_r[i][j] = 190;
				}
				else
				{
					if(G_r[i][j] <= 222)
						G_r[i][j] = 190;
					else
						G_r[i][j] = 255;
				}

					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio8level()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

				if (G_r[i][j] <= 32 )
				{
					if(G_r[i][j] <= 16)
						G_r[i][j] = 0;
					else
						G_r[i][j] = 32;
				}
				else if(G_r[i][j] > 32 && G_r[i][j] <= 64)
				{
					if(G_r[i][j] <= 48)
						G_r[i][j] = 32;
					else
						G_r[i][j] = 64;
				}

				else if (G_r[i][j] > 64 && G_r[i][j] <= 96)
				{
					if(G_r[i][j] <= 80)
						G_r[i][j] = 64;
					else
						G_r[i][j] = 96;
				}
				else if(G_r[i][j] > 96 && G_r[i][j] <= 128)
				{
					if(G_r[i][j] <= 112)
						G_r[i][j] = 96;
					else
						G_r[i][j] = 128;
				}

				else if (G_r[i][j] > 128 && G_r[i][j] <= 160)
				{
					if(G_r[i][j] <= 144)
						G_r[i][j] = 128;
					else
						G_r[i][j] = 160;
				}
				else if(G_r[i][j] > 160 && G_r[i][j] <= 192)
				{
					if(G_r[i][j] <= 176)
						G_r[i][j] = 160;
					else
						G_r[i][j] = 192;
				}

				else if (G_r[i][j] > 192 && G_r[i][j] <= 224)
				{
					if(G_r[i][j] <= 208)
						G_r[i][j] = 192;
					else
						G_r[i][j] = 224;
				}				
				else
				{
					if(G_r[i][j] <= 240)
						G_r[i][j] = 224;
					else
						G_r[i][j] = 255;
				}

					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio16level()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

				if (G_r[i][j] <= 16 )
				{
					if(G_r[i][j] <= 8)
						G_r[i][j] = 0;
					else
						G_r[i][j] = 16;
				}
				else if(G_r[i][j] > 16 && G_r[i][j] <= 32)
				{
					if(G_r[i][j] <= 24)
						G_r[i][j] = 16;
					else
						G_r[i][j] = 32;
				}

				else if (G_r[i][j] > 32 && G_r[i][j] <= 48)
				{
					if(G_r[i][j] <= 40)
						G_r[i][j] = 32;
					else
						G_r[i][j] = 48;
				}
				else if(G_r[i][j] > 48 && G_r[i][j] <= 64)
				{
					if(G_r[i][j] <= 56)
						G_r[i][j] = 48;
					else
						G_r[i][j] = 64;
				}

				else if (G_r[i][j] > 64 && G_r[i][j] <= 80)
				{
					if(G_r[i][j] <= 72)
						G_r[i][j] = 64;
					else
						G_r[i][j] = 80;
				}
				else if(G_r[i][j] > 80 && G_r[i][j] <= 96)
				{
					if(G_r[i][j] <= 88)
						G_r[i][j] = 80;
					else
						G_r[i][j] = 96;
				}

				else if (G_r[i][j] > 96 && G_r[i][j] <= 112)
				{
					if(G_r[i][j] <= 104)
						G_r[i][j] = 96;
					else
						G_r[i][j] = 112;
				}
				else if(G_r[i][j] > 112 && G_r[i][j] <= 128)
				{
					if(G_r[i][j] <= 120)
						G_r[i][j] = 112;
					else
						G_r[i][j] = 128;
				}
				else if (G_r[i][j] > 128 && G_r[i][j] <= 144)
				{
					if(G_r[i][j] <= 136)
						G_r[i][j] = 128;
					else
						G_r[i][j] = 144;
				}
				else if(G_r[i][j] > 144 && G_r[i][j] <= 160)
				{
					if(G_r[i][j] <= 152)
						G_r[i][j] = 144;
					else
						G_r[i][j] = 160;
				}
				else if (G_r[i][j] > 160 && G_r[i][j] <= 176)
				{
					if(G_r[i][j] <= 168)
						G_r[i][j] = 160;
					else
						G_r[i][j] = 176;
				}
				else if(G_r[i][j] > 176 && G_r[i][j] <= 192)
				{
					if(G_r[i][j] <= 184)
						G_r[i][j] = 176;
					else
						G_r[i][j] = 192;
				}
				else if (G_r[i][j] > 192 && G_r[i][j] <= 208)
				{
					if(G_r[i][j] <= 200)
						G_r[i][j] = 192;
					else
						G_r[i][j] = 208;
				}
				else if(G_r[i][j] > 208 && G_r[i][j] <= 224)
				{
					if(G_r[i][j] <= 216)
						G_r[i][j] = 208;
					else
						G_r[i][j] = 224;
				}
				else if (G_r[i][j] > 224 && G_r[i][j] <= 240)
				{
					if(G_r[i][j] <= 232)
						G_r[i][j] = 224;
					else
						G_r[i][j] = 240;
				}
				else
				{
					if(G_r[i][j] <= 240)
						G_r[i][j] = 224;
					else
						G_r[i][j] = 255;
				}

					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio32level()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

				if (G_r[i][j] <= 8 )
				{
					if(G_r[i][j] <= 4)
						G_r[i][j] = 0;
					else
						G_r[i][j] = 8;
				}
				else if(G_r[i][j] > 8 && G_r[i][j] <= 16)
				{
					if(G_r[i][j] <= 12)
						G_r[i][j] = 8;
					else
						G_r[i][j] = 16;
				}

				else if (G_r[i][j] > 16 && G_r[i][j] <= 24)
				{
					if(G_r[i][j] <= 20)
						G_r[i][j] = 16;
					else
						G_r[i][j] = 24;
				}
				else if(G_r[i][j] > 24 && G_r[i][j] <= 32)
				{
					if(G_r[i][j] <= 28)
						G_r[i][j] = 24;
					else
						G_r[i][j] = 32;
				}

				else if (G_r[i][j] > 32 && G_r[i][j] <= 40)
				{
					if(G_r[i][j] <= 36)
						G_r[i][j] = 32;
					else
						G_r[i][j] = 40;
				}
				else if(G_r[i][j] > 40 && G_r[i][j] <= 48)
				{
					if(G_r[i][j] <= 44)
						G_r[i][j] = 40;
					else
						G_r[i][j] = 48;
				}

				else if (G_r[i][j] > 48 && G_r[i][j] <= 56)
				{
					if(G_r[i][j] <= 52)
						G_r[i][j] = 48;
					else
						G_r[i][j] = 56;
				}
				else if(G_r[i][j] > 56 && G_r[i][j] <= 64)
				{
					if(G_r[i][j] <= 60)
						G_r[i][j] = 56;
					else
						G_r[i][j] = 64;
				}
				else if (G_r[i][j] > 64 && G_r[i][j] <= 72)
				{
					if(G_r[i][j] <= 68)
						G_r[i][j] = 64;
					else
						G_r[i][j] = 72;
				}
				else if(G_r[i][j] > 72 && G_r[i][j] <= 80)
				{
					if(G_r[i][j] <= 76)
						G_r[i][j] = 72;
					else
						G_r[i][j] = 80;
				}
				else if (G_r[i][j] > 80 && G_r[i][j] <= 88)
				{
					if(G_r[i][j] <= 84)
						G_r[i][j] = 80;
					else
						G_r[i][j] = 88;
				}
				else if(G_r[i][j] > 88 && G_r[i][j] <= 96)
				{
					if(G_r[i][j] <= 92)
						G_r[i][j] = 88;
					else
						G_r[i][j] = 96;
				}
				else if (G_r[i][j] > 96 && G_r[i][j] <= 104)
				{
					if(G_r[i][j] <= 100)
						G_r[i][j] = 96;
					else
						G_r[i][j] = 104;
				}
				else if(G_r[i][j] > 104 && G_r[i][j] <= 112)
				{
					if(G_r[i][j] <= 108)
						G_r[i][j] = 104;
					else
						G_r[i][j] = 112;
				}
				else if (G_r[i][j] > 112 && G_r[i][j] <= 120)
				{
					if(G_r[i][j] <= 116)
						G_r[i][j] = 112;
					else
						G_r[i][j] = 120;
				}
				else if(G_r[i][j] > 120 && G_r[i][j] <= 128)
				{
					if(G_r[i][j] <= 124)
						G_r[i][j] = 120;
					else
						G_r[i][j] = 128;
				}
				else if (G_r[i][j] > 128 && G_r[i][j] <= 136)
				{
					if(G_r[i][j] <= 132)
						G_r[i][j] = 128;
					else
						G_r[i][j] = 136;
				}
				else if(G_r[i][j] > 136 && G_r[i][j] <= 144)
				{
					if(G_r[i][j] <= 140)
						G_r[i][j] = 136;
					else
						G_r[i][j] = 144;
				}
				else if (G_r[i][j] > 144 && G_r[i][j] <= 152)
				{
					if(G_r[i][j] <= 148)
						G_r[i][j] = 144;
					else
						G_r[i][j] = 152;
				}
				else if(G_r[i][j] > 152 && G_r[i][j] <= 160)
				{
					if(G_r[i][j] <= 156)
						G_r[i][j] = 152;
					else
						G_r[i][j] = 160;
				}
				else if (G_r[i][j] > 160 && G_r[i][j] <= 168)
				{
					if(G_r[i][j] <= 164)
						G_r[i][j] = 160;
					else
						G_r[i][j] = 168;
				}
				else if(G_r[i][j] > 168 && G_r[i][j] <= 176)
				{
					if(G_r[i][j] <= 172)
						G_r[i][j] = 168;
					else
						G_r[i][j] = 176;
				}
				else if (G_r[i][j] > 176 && G_r[i][j] <= 184)
				{
					if(G_r[i][j] <= 180)
						G_r[i][j] = 176;
					else
						G_r[i][j] = 184;
				}
				else if(G_r[i][j] > 184 && G_r[i][j] <= 192)
				{
					if(G_r[i][j] <= 188)
						G_r[i][j] = 184;
					else
						G_r[i][j] = 192;
				}
				else if (G_r[i][j] > 192 && G_r[i][j] <= 200)
				{
					if(G_r[i][j] <= 196)
						G_r[i][j] = 192;
					else
						G_r[i][j] = 200;
				}
				else if(G_r[i][j] > 200 && G_r[i][j] <= 208)
				{
					if(G_r[i][j] <= 204)
						G_r[i][j] = 200;
					else
						G_r[i][j] = 208;
				}
				else if (G_r[i][j] > 208 && G_r[i][j] <= 216)
				{
					if(G_r[i][j] <= 212)
						G_r[i][j] = 208;
					else
						G_r[i][j] = 216;
				}
				else if(G_r[i][j] > 216 && G_r[i][j] <= 224)
				{
					if(G_r[i][j] <= 220)
						G_r[i][j] = 216;
					else
						G_r[i][j] = 224;
				}
				else if (G_r[i][j] > 224 && G_r[i][j] <= 232)
				{
					if(G_r[i][j] <= 228)
						G_r[i][j] = 224;
					else
						G_r[i][j] = 232;
				}
				else if(G_r[i][j] > 232 && G_r[i][j] <= 240)
				{
					if(G_r[i][j] <= 236)
						G_r[i][j] = 232;
					else
						G_r[i][j] = 240;
				}
				else if (G_r[i][j] > 240 && G_r[i][j] <= 248)
				{
					if(G_r[i][j] <= 244)
						G_r[i][j] = 240;
					else
						G_r[i][j] = 248;
				}
				else
				{
					if(G_r[i][j] <= 252)
						G_r[i][j] = 248;
					else
						G_r[i][j] = 255;
				}

					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio64level()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

				if (G_r[i][j] <= 4 )
				{
					if(G_r[i][j] <= 2)
						G_r[i][j] = 0;
					else
						G_r[i][j] = 4;
				}
				else if(G_r[i][j] >4 && G_r[i][j] <= 8)
				{
					if(G_r[i][j] <= 6)
						G_r[i][j] = 4;
					else
						G_r[i][j] = 8;
				}

				else if (G_r[i][j] > 8 && G_r[i][j] <= 12)
				{
					if(G_r[i][j] <= 10)
						G_r[i][j] = 8;
					else
						G_r[i][j] = 12;
				}
				else if(G_r[i][j] > 12 && G_r[i][j] <= 16)
				{
					if(G_r[i][j] <= 14)
						G_r[i][j] = 12;
					else
						G_r[i][j] = 16;
				}

				else if (G_r[i][j] > 16 && G_r[i][j] <= 20)
				{
					if(G_r[i][j] <= 18)
						G_r[i][j] = 16;
					else
						G_r[i][j] = 20;
				}
				else if(G_r[i][j] > 20 && G_r[i][j] <= 24)
				{
					if(G_r[i][j] <= 22)
						G_r[i][j] = 20;
					else
						G_r[i][j] = 24;
				}

				else if (G_r[i][j] > 24 && G_r[i][j] <= 28)
				{
					if(G_r[i][j] <= 26)
						G_r[i][j] = 24;
					else
						G_r[i][j] = 28;
				}
				else if(G_r[i][j] > 28 && G_r[i][j] <= 32)
				{
					if(G_r[i][j] <= 30)
						G_r[i][j] = 28;
					else
						G_r[i][j] = 32;
				}
				else if (G_r[i][j] > 32 && G_r[i][j] <= 36)
				{
					if(G_r[i][j] <= 34)
						G_r[i][j] = 32;
					else
						G_r[i][j] = 36;
				}
				else if(G_r[i][j] > 36 && G_r[i][j] <= 40)
				{
					if(G_r[i][j] <= 38)
						G_r[i][j] = 36;
					else
						G_r[i][j] = 40;
				}
				else if (G_r[i][j] > 40 && G_r[i][j] <= 44)
				{
					if(G_r[i][j] <= 42)
						G_r[i][j] = 40;
					else
						G_r[i][j] = 44;
				}
				else if(G_r[i][j] > 44 && G_r[i][j] <= 48)
				{
					if(G_r[i][j] <= 46)
						G_r[i][j] = 44;
					else
						G_r[i][j] = 48;
				}
				else if (G_r[i][j] > 48 && G_r[i][j] <= 52)
				{
					if(G_r[i][j] <= 50)
						G_r[i][j] = 48;
					else
						G_r[i][j] = 52;
				}
				else if(G_r[i][j] > 52 && G_r[i][j] <= 56)
				{
					if(G_r[i][j] <= 54)
						G_r[i][j] = 52;
					else
						G_r[i][j] = 56;
				}
				else if (G_r[i][j] > 56 && G_r[i][j] <= 60)
				{
					if(G_r[i][j] <= 58)
						G_r[i][j] = 56;
					else
						G_r[i][j] = 60;
				}
				else if(G_r[i][j] > 60 && G_r[i][j] <= 64)
				{
					if(G_r[i][j] <= 62)
						G_r[i][j] = 60;
					else
						G_r[i][j] = 64;
				}
				else if (G_r[i][j] > 64 && G_r[i][j] <= 68)
				{
					if(G_r[i][j] <= 66)
						G_r[i][j] = 64;
					else
						G_r[i][j] = 68;
				}
				else if(G_r[i][j] > 68 && G_r[i][j] <= 72)
				{
					if(G_r[i][j] <= 70)
						G_r[i][j] = 68;
					else
						G_r[i][j] = 72;
				}
				else if (G_r[i][j] > 72 && G_r[i][j] <= 76)
				{
					if(G_r[i][j] <= 74)
						G_r[i][j] = 72;
					else
						G_r[i][j] = 76;
				}
				else if(G_r[i][j] > 76 && G_r[i][j] <= 80)
				{
					if(G_r[i][j] <= 78)
						G_r[i][j] = 76;
					else
						G_r[i][j] = 80;
				}
				else if (G_r[i][j] > 80 && G_r[i][j] <= 84)
				{
					if(G_r[i][j] <= 82)
						G_r[i][j] = 80;
					else
						G_r[i][j] = 84;
				}
				else if(G_r[i][j] > 84 && G_r[i][j] <= 88)
				{
					if(G_r[i][j] <= 86)
						G_r[i][j] = 84;
					else
						G_r[i][j] = 88;
				}
				else if (G_r[i][j] > 88 && G_r[i][j] <= 92)
				{
					if(G_r[i][j] <= 90)
						G_r[i][j] = 88;
					else
						G_r[i][j] = 92;
				}
				else if(G_r[i][j] > 92 && G_r[i][j] <= 96)
				{
					if(G_r[i][j] <= 94)
						G_r[i][j] = 92;
					else
						G_r[i][j] = 96;
				}
				else if (G_r[i][j] > 96 && G_r[i][j] <= 100)
				{
					if(G_r[i][j] <= 98)
						G_r[i][j] = 96;
					else
						G_r[i][j] = 100;
				}
				else if(G_r[i][j] > 100 && G_r[i][j] <= 104)
				{
					if(G_r[i][j] <= 102)
						G_r[i][j] = 100;
					else
						G_r[i][j] = 104;
				}
				else if (G_r[i][j] > 104 && G_r[i][j] <= 108)
				{
					if(G_r[i][j] <= 106)
						G_r[i][j] = 104;
					else
						G_r[i][j] = 108;
				}
				else if(G_r[i][j] > 108 && G_r[i][j] <= 112)
				{
					if(G_r[i][j] <= 110)
						G_r[i][j] = 108;
					else
						G_r[i][j] = 112;
				}
				else if (G_r[i][j] > 112 && G_r[i][j] <= 116)
				{
					if(G_r[i][j] <= 114)
						G_r[i][j] = 112;
					else
						G_r[i][j] = 116;
				}
				else if(G_r[i][j] > 116 && G_r[i][j] <= 120)
				{
					if(G_r[i][j] <= 118)
						G_r[i][j] = 116;
					else
						G_r[i][j] = 120;
				}
				else if (G_r[i][j] > 120 && G_r[i][j] <= 124)
				{
					if(G_r[i][j] <= 122)
						G_r[i][j] = 120;
					else
						G_r[i][j] = 124;
				}
				else if(G_r[i][j] > 124 && G_r[i][j] <= 128)
				{
					if(G_r[i][j] <= 126)
						G_r[i][j] = 124;
					else
						G_r[i][j] = 128;
				}
				else if (G_r[i][j] > 128 && G_r[i][j] <= 132)
				{
					if(G_r[i][j] <= 130)
						G_r[i][j] = 128;
					else
						G_r[i][j] = 132;
				}
				else if(G_r[i][j] > 132 && G_r[i][j] <= 136)
				{
					if(G_r[i][j] <= 134)
						G_r[i][j] = 132;
					else
						G_r[i][j] = 136;
				}
				else if(G_r[i][j] > 136 && G_r[i][j] <= 140)
				{
					if(G_r[i][j] <= 138)
						G_r[i][j] = 136;
					else
						G_r[i][j] = 140;
				}
				else if (G_r[i][j] > 140 && G_r[i][j] <= 144)
				{
					if(G_r[i][j] <= 142)
						G_r[i][j] = 140;
					else
						G_r[i][j] = 144;
				}
				else if(G_r[i][j] > 144 && G_r[i][j] <= 148)
				{
					if(G_r[i][j] <= 146)
						G_r[i][j] = 144;
					else
						G_r[i][j] = 148;
				}
				else if(G_r[i][j] > 148 && G_r[i][j] <= 152)
				{
					if(G_r[i][j] <= 150)
						G_r[i][j] = 148;
					else
						G_r[i][j] = 152;
				}
				else if (G_r[i][j] > 152 && G_r[i][j] <= 156)
				{
					if(G_r[i][j] <= 154)
						G_r[i][j] = 152;
					else
						G_r[i][j] = 156;
				}
				else if(G_r[i][j] > 156 && G_r[i][j] <= 160)
				{
					if(G_r[i][j] <= 158)
						G_r[i][j] = 156;
					else
						G_r[i][j] = 160;
				}
				else if(G_r[i][j] > 160 && G_r[i][j] <= 164)
				{
					if(G_r[i][j] <= 162)
						G_r[i][j] = 160;
					else
						G_r[i][j] = 164;
				}
				else if (G_r[i][j] > 164 && G_r[i][j] <= 168)
				{
					if(G_r[i][j] <= 166)
						G_r[i][j] = 164;
					else
						G_r[i][j] = 168;
				}
				else if(G_r[i][j] > 168 && G_r[i][j] <= 172)
				{
					if(G_r[i][j] <= 170)
						G_r[i][j] = 168;
					else
						G_r[i][j] = 172;
				}
				else if(G_r[i][j] > 172 && G_r[i][j] <= 176)
				{
					if(G_r[i][j] <= 174)
						G_r[i][j] = 172;
					else
						G_r[i][j] = 176;
				}
				else if (G_r[i][j] > 176 && G_r[i][j] <= 180)
				{
					if(G_r[i][j] <= 178)
						G_r[i][j] = 176;
					else
						G_r[i][j] = 180;
				}
				else if(G_r[i][j] > 180 && G_r[i][j] <= 184)
				{
					if(G_r[i][j] <= 182)
						G_r[i][j] = 180;
					else
						G_r[i][j] = 184;
					}
				else if(G_r[i][j] > 184 && G_r[i][j] <= 188)
				{
					if(G_r[i][j] <= 186)
						G_r[i][j] = 184;
					else
						G_r[i][j] = 188;
				}
				else if (G_r[i][j] > 188 && G_r[i][j] <= 192)
				{
					if(G_r[i][j] <= 190)
						G_r[i][j] = 188;
					else
						G_r[i][j] = 192;
				}
				else if(G_r[i][j] > 192 && G_r[i][j] <= 196)
				{
					if(G_r[i][j] <= 194)
						G_r[i][j] = 192;
					else
						G_r[i][j] = 196;
				}
				else if(G_r[i][j] > 196 && G_r[i][j] <= 200)
				{
					if(G_r[i][j] <= 198)
						G_r[i][j] = 196;
					else
						G_r[i][j] = 200;
				}
				else if (G_r[i][j] > 200 && G_r[i][j] <= 204)
				{
					if(G_r[i][j] <= 202)
						G_r[i][j] = 200;
					else
						G_r[i][j] = 204;
				}
				else if(G_r[i][j] > 204 && G_r[i][j] <= 208)
				{
					if(G_r[i][j] <= 206)
						G_r[i][j] = 204;
					else
						G_r[i][j] = 208;
				}
				else if(G_r[i][j] > 208 && G_r[i][j] <= 212)
				{
					if(G_r[i][j] <= 210)
						G_r[i][j] = 208;
					else
						G_r[i][j] = 212;
				}
				else if (G_r[i][j] > 212 && G_r[i][j] <= 216)
				{
					if(G_r[i][j] <= 214)
						G_r[i][j] = 212;
					else
						G_r[i][j] = 216;
				}
				else if(G_r[i][j] > 216 && G_r[i][j] <= 220)
				{
					if(G_r[i][j] <= 218)
						G_r[i][j] = 216;
					else
						G_r[i][j] = 220;
				}
				else if(G_r[i][j] > 220 && G_r[i][j] <= 224)
				{
					if(G_r[i][j] <= 222)
						G_r[i][j] = 220;
					else
						G_r[i][j] = 224;
				}
				else if (G_r[i][j] > 224 && G_r[i][j] <= 228)
				{
					if(G_r[i][j] <= 226)
						G_r[i][j] = 224;
					else
						G_r[i][j] = 228;
				}
				else if(G_r[i][j] > 228 && G_r[i][j] <= 232)
				{
					if(G_r[i][j] <= 230)
						G_r[i][j] = 228;
					else
						G_r[i][j] = 232;
				}
				else if(G_r[i][j] > 232 && G_r[i][j] <= 236)
				{
					if(G_r[i][j] <= 234)
						G_r[i][j] = 232;
					else
						G_r[i][j] = 236;
				}
				else if (G_r[i][j] > 236 && G_r[i][j] <= 240)
				{
					if(G_r[i][j] <= 238)
						G_r[i][j] = 236;
					else
						G_r[i][j] = 240;
				}
				else if(G_r[i][j] > 240 && G_r[i][j] <= 244)
				{
					if(G_r[i][j] <= 242)
						G_r[i][j] = 240;
					else
						G_r[i][j] = 244;
				}
				else if(G_r[i][j] > 244 && G_r[i][j] <= 248)
				{
					if(G_r[i][j] <= 246)
						G_r[i][j] = 244;
					else
						G_r[i][j] = 248;
				}
				else if (G_r[i][j] > 248 && G_r[i][j] <= 252)
				{
					if(G_r[i][j] <= 250)
						G_r[i][j] = 248;
					else
						G_r[i][j] = 252;
				}
				else if(G_r[i][j] > 252 && G_r[i][j] <= 255)
				{
					if(G_r[i][j] <= 254)
						G_r[i][j] = 252;
					else
						G_r[i][j] = 255;
				}						
				else
				{
					if(G_r[i][j] <= 252)
						G_r[i][j] = 248;
					else
						G_r[i][j] = 255;
				}

					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_r[i][j],G_r[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}

void GRAYColor::OnBnClickedRadio128level()
{
	/*G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	gray=new int * [height]; 
	for(int i=0;i<height;i++) gray[i]=new int [width];    //建立gray的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;

					for(int k=0;k<64;k++)
					{
						int H=0;
						H=k*256/128;
						if(G_r[i][j]>=H && G_r[i][j]<H+256/128)
						{ gray[i][j]=H; }
					}
					for(int k=64;k<128;k++)
					{
						int H=0;
						H=k*256/128;
						if(G_r[i][j]>=H && G_r[i][j]<=H+256/128)
						{ gray[i][j]=H+256/128; }
					}

					grayimage->SetPixel(j,i,RGB(gray[i][j],gray[i][j],gray[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));*/
}

void GRAYColor::OnBnClickedRadio256level()
{	
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //建立R的空間	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //建立G的空間

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //建立B的空間

	CClientDC dc(this);
	grayimage = new CDIBSectionLite();
	grayimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					G_g[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					G_b[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					grayimage->SetPixel(j,i,RGB(G_r[i][j],G_g[i][j],G_b[i][j]));
				}
			}grayimage->Draw(&dc,CPoint(10,10));
}
