// ZOOM.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "ZOOM.h"


// ZOOM dialog

IMPLEMENT_DYNAMIC(ZOOM, CDialog)

ZOOM::ZOOM(CWnd* pParent /*=NULL*/)
	: CDialog(ZOOM::IDD, pParent)
	, zz(0)
{
	R=NULL;
	G=NULL;
	B=NULL;
	ZR=NULL;
	ZG=NULL;
	ZB=NULL;
	height=0;
	width=0;
	zoomimage=NULL;
	bg=NULL;
}

ZOOM::~ZOOM()
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
	if(B)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] B[i]; delete [] B;
	}
	if(ZR)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] ZR[i]; delete [] ZR;
	}
	if(ZG)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] ZG[i]; delete [] ZG;
	}
	if(ZB)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] ZB[i]; delete [] ZB;
	}

	if(image) delete image;
	if(zoomimage) delete zoomimage;
	if(bg) delete bg;
}

void ZOOM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, zz);
}


BEGIN_MESSAGE_MAP(ZOOM, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONdularge, &ZOOM::OnBnClickedButtondularge)
	ON_BN_CLICKED(IDC_BUTTONdusmall, &ZOOM::OnBnClickedButtondusmall)
	ON_BN_CLICKED(IDC_BUTTONinlarge, &ZOOM::OnBnClickedButtoninlarge)
	ON_BN_CLICKED(IDC_BUTTONinsmall, &ZOOM::OnBnClickedButtoninsmall)
END_MESSAGE_MAP()


// ZOOM message handlers
void ZOOM::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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

	CClientDC dc(this);
	image = new CDIBSectionLite();
	image->CreateEmptyDIB(width,height,24);
    for(i=0;i<height;i++) 
	{
		for(j=0;j<width;j++)
	    {
			image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}image->Draw(&dc,CPoint(0,0));

}
void ZOOM::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(0,0));
}


void ZOOM::OnBnClickedButtondularge()
{
	CClientDC dc(this);
	UpdateData(true);
	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(width*5,height*5,24);

    for(int i=0;i<height*5;i++) 
	{
		for(int j=0;j<width*5;j++)
	    {
			bg->SetPixel(j,i,RGB(236,233,216));
		}
		
	}bg->Draw(&dc,CPoint(256,0));

	zoomimage = new CDIBSectionLite();
	zoomimage->CreateEmptyDIB(width*zz,height*zz,24);
		for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
			{
				for(int hh=0;hh<zz;hh++)
				{
					for(int cc=0;cc<zz;cc++)
					{
						zoomimage->SetPixel(j*zz+cc,i*zz+hh,RGB(R[i][j],G[i][j],B[i][j]));
					}
				}
			}
		}zoomimage->Draw(&dc,CPoint(266,0));
}

void ZOOM::OnBnClickedButtondusmall()
{
	CClientDC dc(this);
	UpdateData(true);
	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(width*5,height*5,24);

    for(int i=0;i<height*5;i++) 
	{
		for(int j=0;j<width*5;j++)
	    {
			bg->SetPixel(j,i,RGB(236,233,216));
		}
		
	}bg->Draw(&dc,CPoint(256,0));

	zoomimage = new CDIBSectionLite();
	zoomimage->CreateEmptyDIB(width/zz,height/zz,24);
		for(int i=0;i<height/zz;i++) 
		{
			for(int j=0;j<width/zz;j++)
			{
				for(int hh=0;hh<zz;hh++)
				{
					for(int cc=0;cc<zz;cc++)
					{
						zoomimage->SetPixel(j,i,RGB(R[i*zz+cc][j*zz+hh],G[i*zz+cc][j*zz+hh],B[i*zz+cc][j*zz+hh]));
					}
				}
			}
		}zoomimage->Draw(&dc,CPoint(266,0));
}

void ZOOM::OnBnClickedButtoninlarge()
{
	CClientDC dc(this);
	UpdateData(true);

	if(ZR)															//釋放R的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZR[i]; delete [] ZR;
	}
	if(ZG)															//釋放G的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZG[i]; delete [] ZG;
	}
	if(ZB)															////釋放B的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZB[i]; delete [] ZB;
	}

	ZR=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZR[i]=new int [width*zz];

    ZG=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZG[i]=new int [width*zz];

    ZB=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZB[i]=new int [width*zz];

	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{
		    ZR[i*zz][j*zz]=R[i][j];
            ZG[i*zz][j*zz]=G[i][j];
            ZB[i*zz][j*zz]=B[i][j];
		}
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width*zz;j++)
		{
			for(int h=1;h<zz;h++)
			{
				if((i*zz)+zz<width*zz)
				{
					ZR[i*zz+h][j]=ZR[i*zz][j]+(h*((ZR[i*zz+zz][j]-ZR[i*zz][j])/zz));
					ZG[i*zz+h][j]=ZG[i*zz][j]+(h*((ZG[i*zz+zz][j]-ZG[i*zz][j])/zz));
					ZB[i*zz+h][j]=ZB[i*zz][j]+(h*((ZB[i*zz+zz][j]-ZB[i*zz][j])/zz));
				}
				else
				{
					ZR[i*zz+h][j]=(ZR[0][j]+ZR[i*zz][j])/2;
					ZG[i*zz+h][j]=(ZG[0][j]+ZG[i*zz][j])/2;
					ZB[i*zz+h][j]=(ZB[0][j]+ZB[i*zz][j])/2;
				}
			}
		}
	}

	for(int i=0;i<height*zz;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=1;k<zz;k++)
			{
				if((j*zz)+zz<width*zz)
				{
					ZR[i][j*zz+k]=ZR[i][j*zz]+(k*((ZR[i][j*zz+zz]-ZR[i][j*zz])/zz));
					ZG[i][j*zz+k]=ZG[i][j*zz]+(k*((ZG[i][j*zz+zz]-ZG[i][j*zz])/zz));
					ZB[i][j*zz+k]=ZB[i][j*zz]+(k*((ZB[i][j*zz+zz]-ZB[i][j*zz])/zz));
				}
				else
				{
					ZR[i][j*zz+k]=(ZR[i][0]+ZR[i][j*zz])/2;
					ZG[i][j*zz+k]=(ZG[i][0]+ZG[i][j*zz])/2;
					ZB[i][j*zz+k]=(ZB[i][0]+ZB[i][j*zz])/2;
				}
			}
		}
	}
	
	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(width*5,height*5,24);

    for(int i=0;i<height*5;i++) 
	{
		for(int j=0;j<width*5;j++)
	    {
			bg->SetPixel(j,i,RGB(236,233,216));
		}
		
	}bg->Draw(&dc,CPoint(256,0));


	zoomimage = new CDIBSectionLite();
	zoomimage->CreateEmptyDIB(width*zz,height*zz,24);
	for(int i=0;i<height*zz;i++)
	{
		for(int j=0;j<width*zz;j++)
		{
			zoomimage->SetPixel(j,i,RGB(ZR[i][j],ZG[i][j],ZB[i][j]));  
		}
	}zoomimage->Draw(&dc,CPoint(266,0)); 
}

void ZOOM::OnBnClickedButtoninsmall()
{
	CClientDC dc(this);
	UpdateData(true);

	if(ZR)															//釋放R的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZR[i]; delete [] ZR;
	}
	if(ZG)															//釋放G的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZG[i]; delete [] ZG;
	}
	if(ZB)															////釋放B的記憶體空間
	{
		for(int i=0;i<height*zz;i++) delete [] ZB[i]; delete [] ZB;
	}

	ZR=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZR[i]=new int [width*zz];

    ZG=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZG[i]=new int [width*zz];

    ZB=new int * [height*zz]; 
    for(int i=0;i<height*zz;i++) ZB[i]=new int [width*zz];

	for(int i=0;i<height/zz;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int h=0;h<zz;h++)
			{
				if(i*zz+h+1<height)
				{
					ZR[i][j]=(int)((R[i*zz+h][j]+R[i*zz+h+1][j])/2);
					ZG[i][j]=(int)((G[i*zz+h][j]+G[i*zz+h+1][j])/2);
					ZB[i][j]=(int)((B[i*zz+h][j]+B[i*zz+h+1][j])/2);
				}
				else
				{
					ZR[i][j]=(int)((R[i*zz+h][j]+R[0][j])/2);
					ZG[i][j]=(int)((G[i*zz+h][j]+G[0][j])/2);
					ZB[i][j]=(int)((B[i*zz+h][j]+B[0][j])/2);
				}
			}
		}
	}

	for(int i=0;i<height/zz;i++)
	{
		for(int j=0;j<width/zz;j++)
		{
			for(int k=0;k<zz;k++)
			{
				if(j*zz+k+1<width)
				{
					ZR[i][j]=(int)((ZR[i][j*zz+k]+ZR[i][j*zz+k+1])/2);
					ZG[i][j]=(int)((ZG[i][j*zz+k]+ZG[i][j*zz+k+1])/2);
					ZB[i][j]=(int)((ZB[i][j*zz+k]+ZB[i][j*zz+k+1])/2);
				}
				else
				{
					ZR[i][j]=(int)((ZR[i][j*zz+k]+ZR[i][0])/2);
					ZG[i][j]=(int)((ZG[i][j*zz+k]+ZG[i][0])/2);
					ZB[i][j]=(int)((ZB[i][j*zz+k]+ZB[i][0])/2);
				}
			}
		}
	}

	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(width*5,height*5,24);

    for(int i=0;i<height*5;i++) 
	{
		for(int j=0;j<width*5;j++)
	    {
			bg->SetPixel(j,i,RGB(236,233,216));
		}
		
	}bg->Draw(&dc,CPoint(256,0));


	zoomimage = new CDIBSectionLite();
	zoomimage->CreateEmptyDIB(width/zz,height/zz,24);
	for(int i=0;i<height/zz;i++)
	{
		for(int j=0;j<width/zz;j++)
		{
			zoomimage->SetPixel(j,i,RGB(ZR[i][j],ZG[i][j],ZB[i][j]));
		}
	}zoomimage->Draw(&dc,CPoint(266,0));
}
