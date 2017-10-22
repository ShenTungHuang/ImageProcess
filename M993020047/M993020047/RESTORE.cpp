// RESTORE.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "RESTORE.h"


// RESTORE dialog

IMPLEMENT_DYNAMIC(RESTORE, CDialog)

RESTORE::RESTORE(CWnd* pParent /*=NULL*/)
	: CDialog(RESTORE::IDD, pParent)
	, m_FirstPoint(CPoint(0,0))
	, m_SecondPoint(CPoint(0,0))
{
	x1=0;
	y1=0;
	x2=0;
	y2=0;
	xc=0;
	yc=0;
	shapetype=0;
	cuttype=0;
	R=NULL;
	G=NULL;
	B=NULL;
	nR=NULL;
	nG=NULL;
	nB=NULL;
	image=NULL;
	image2=NULL;
	height=0;
	width=0;	
}

RESTORE::~RESTORE()
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
	if(nR)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nR[i]; delete [] nR;
	}
	if(nG)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nG[i]; delete [] nG;
	}
	if(nB)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nB[i]; delete [] nB;
	}

	if(image) delete image;
	if(image2) delete image2;
}

void RESTORE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RESTORE, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIOLINE, &RESTORE::OnBnClickedRadioline)
	ON_BN_CLICKED(IDC_RADIORECTANGLE, &RESTORE::OnBnClickedRadiorectangle)
	ON_BN_CLICKED(IDC_RADIOELLIPAE, &RESTORE::OnBnClickedRadioellipae)
	ON_BN_CLICKED(IDC_BUTTONCUT, &RESTORE::OnBnClickedButtoncut)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTONRESTORE, &RESTORE::OnBnClickedButtonrestore)
END_MESSAGE_MAP()


// RESTORE message handlers
void RESTORE::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
	if(nR)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nR[i]; delete [] nR;
	}
	if(nG)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nG[i]; delete [] nG;
	}
	if(nB)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nB[i]; delete [] nB;
	}

	//開啟記憶體紀錄R、G、B
	R=new int * [height]; 
    for(i=0;i<height;i++) R[i]=new int [width];

    G=new int * [height]; 
    for(i=0;i<height;i++) G[i]=new int [width];

    B=new int * [height]; 
    for(i=0;i<height;i++) B[i]=new int [width];

	nR=new int * [height]; 
    for(i=0;i<height;i++) nR[i]=new int [width];

    nG=new int * [height]; 
    for(i=0;i<height;i++) nG[i]=new int [width];

    nB=new int * [height]; 
    for(i=0;i<height;i++) nB[i]=new int [width];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R[i][j]=Input_R[i][j];
			G[i][j]=Input_G[i][j];
			B[i][j]=Input_B[i][j];
			nR[i][j]=Input_R[i][j];
			nG[i][j]=Input_G[i][j];
			nB[i][j]=Input_B[i][j];
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
void RESTORE::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(0,0));
}

void RESTORE::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;
	SetCapture();
	x1 = point.x;
	y1 = point.y;
}

void RESTORE::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(this == GetCapture())
		ReleaseCapture();
	m_SecondPoint;
	x2 = point.x;
	y2 = point.y;	

	CClientDC dc(this);
	CPen pen(PS_SOLID,1,RGB(255,0,0));						
	CPen *oldPen = dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);

	if(shapetype == 1)
	{ dc.MoveTo(x1,y1);    
	  dc.LineTo(x2,y2); }
	if(shapetype == 2)
	{ dc.Rectangle(x1,y1,x2,y2); }
	if(shapetype == 3)
	{ dc.Ellipse(x1,y1,x2,y2); }	
	dc.SelectObject(oldPen);
}

void RESTORE::OnMouseMove(UINT nFlags, CPoint point)
{
	if((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		x2 = point.x;
		y2 = point.y;

		CClientDC dc(this);
		image->Draw(&dc,CPoint(0,0));
		CPen pen(PS_SOLID,1,RGB(255,0,0));							
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);

		if(shapetype == 1)
		{ dc.MoveTo(x1,y1);    
		  dc.LineTo(x2,y2); }
		if(shapetype == 2)
		{ dc.Rectangle(x1,y1,x2,y2); }
		if(shapetype == 3)
		{ dc.Ellipse(x1,y1,x2,y2); }
		dc.SelectObject(oldPen);
	}
}

void RESTORE::OnBnClickedRadioline()
{
	shapetype = 1;
}

void RESTORE::OnBnClickedRadiorectangle()
{
	shapetype = 2;
}

void RESTORE::OnBnClickedRadioellipae()
{
	shapetype = 3;
}

void RESTORE::OnBnClickedButtoncut()
{
	if(shapetype == 2)
	{
		cuttype = 2;
		CClientDC dc(this);
		image2 = new CDIBSectionLite();
		image2->CreateEmptyDIB(width,height,24);
	
	    for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
		    {
				if(j>=x1 && j<=x2 && i>=y1 && i<=y2 )
				{ 
					nR[i][j] = 255;
					nG[i][j] = 0;
					nB[i][j] = 0;
					image2->SetPixel(j,i,RGB(nR[i][j],nG[i][j],nB[i][j])); }
				else
				{ image2->SetPixel(j,i,RGB(nR[i][j],nG[i][j],nB[i][j])); }
			}
		
		}image2->Draw(&dc,CPoint(0,0));

		image = new CDIBSectionLite();
		image->CreateEmptyDIB(width,height,24);
	    for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
		    {
				image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
			}
		
		}image->Draw(&dc,CPoint(266,0));
	}
}
void RESTORE::OnBnClickedButtonrestore()
{
	xc = (x2-x1)/2;
	yc = (y2-y1)/2;

	if(cuttype = 2)
	{
	    for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
		    {
				if(j>=x1 && j<=x2 && i>=y1 && i<=y2)
				{ 
					nR[i][j] = 255;
					nG[i][j] = 0;
					nB[i][j] = 0;
				}
				else
				{
					nR[i][j] = nR[i][j];
					nG[i][j] = nG[i][j];
					nB[i][j] = nB[i][j];
				}
			}
		
		}
	}

	for(int i=0;i<=y1+yc;i++)
	{
		for(int j=0;j<=x1+xc;j++)
		{
			if(j>=x1&& i>=y1)
			{
				nR[i][j] = (nR[i-1][j]+nR[i][j-1]+nR[i-1][j-1])/3;
				nG[i][j] = (nG[i-1][j]+nG[i][j-1]+nG[i-1][j-1])/3;
				nB[i][j] = (nB[i-1][j]+nB[i][j-1]+nB[i-1][j-1])/3;
			}
			else
			{
				nR[i][j] = nR[i][j];
				nG[i][j] = nG[i][j];
				nB[i][j] = nB[i][j];
			}
		}
	}
	for(int i=0;i<=y1+yc;i++)
	{
		for(int j=width-1;j>=x1+xc;j--)
		{
			if(j<=x2 && i>=y1)
			{
				nR[i][j] = (nR[i-1][j]+nR[i][j+1]+nR[i-1][j+1])/3;
				nG[i][j] = (nG[i-1][j]+nG[i][j+1]+nG[i-1][j+1])/3;
				nB[i][j] = (nB[i-1][j]+nB[i][j+1]+nB[i-1][j+1])/3;
			}
			else
			{
				nR[i][j] = nR[i][j];
				nG[i][j] = nG[i][j];
				nB[i][j] = nB[i][j];
			}
		}
	}
	for(int i=height-1;i>=y1+yc;i--)
	{
		for(int j=0;j<=x1+xc;j++)
		{
			if(j>=x1 && i<=y2)
			{
				nR[i][j] = (nR[i+1][j]+nR[i][j-1]+nR[i+1][j-1])/3;
				nG[i][j] = (nG[i+1][j]+nG[i][j-1]+nG[i+1][j-1])/3;
				nB[i][j] = (nB[i+1][j]+nB[i][j-1]+nB[i+1][j-1])/3;
			}
			else
			{
				nR[i][j] = nR[i][j];
				nG[i][j] = nG[i][j];
				nB[i][j] = nB[i][j];
			}
		}
	}
	for(int i=height-1;i>=y1+yc;i--)
	{
		for(int j=width-1;j>=x1+xc;j--)
		{
			if(j<=x2 && i<=y2)
			{
				nR[i][j] = (nR[i+1][j]+nR[i][j+1]+nR[i+1][j+1])/3;
				nG[i][j] = (nG[i+1][j]+nG[i][j+1]+nG[i+1][j+1])/3;
				nB[i][j] = (nB[i+1][j]+nB[i][j+1]+nB[i+1][j+1])/3;
			}
			else
			{
				nR[i][j] = nR[i][j];
				nG[i][j] = nG[i][j];
				nB[i][j] = nB[i][j];
			}
		}
	}

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			image2->SetPixel(j,i,RGB(nR[i][j],nG[i][j],nB[i][j]));
		}	
	}image2->Draw(&dc,CPoint(0,0));
}
