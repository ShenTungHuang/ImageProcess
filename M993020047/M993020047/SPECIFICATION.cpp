// SPECIFICATION.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "SPECIFICATION.h"


// SPECIFICATION dialog

IMPLEMENT_DYNAMIC(SPECIFICATION, CDialog)

SPECIFICATION::SPECIFICATION(CWnd* pParent /*=NULL*/)
	: CDialog(SPECIFICATION::IDD, pParent)
	, x1(0)
	, y1(0)
	, x2(0)
	, y2(0)
	,m_FirstPoint(CPoint(0,0))
	,m_SecondPoint(CPoint(0,0))
	, m_snr(0)
{
	px1=0;
	py1=0;
	px2=0;
	py2=0;
	GRAY=NULL;
	nGRAY=NULL;
	height=0;
	width=0;
	image=NULL;
	image2=NULL;
	bg=NULL;
}

SPECIFICATION::~SPECIFICATION()
{
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
	if(image) delete image;
	if(image2) delete image2;
	if(bg) delete bg;
}

void SPECIFICATION::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, x1);
	DDX_Text(pDX, IDC_EDIT2, y1);
	DDX_Text(pDX, IDC_EDIT3, x2);
	DDX_Text(pDX, IDC_EDIT4, y2);
	DDX_Text(pDX, IDC_EDIT5, m_snr);
}


BEGIN_MESSAGE_MAP(SPECIFICATION, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONhb, &SPECIFICATION::OnBnClickedButtonhb)
	ON_BN_CLICKED(IDC_BUTTONlb, &SPECIFICATION::OnBnClickedButtonlb)
	ON_BN_CLICKED(IDC_BUTTONhc, &SPECIFICATION::OnBnClickedButtonhc)
	ON_BN_CLICKED(IDC_BUTTONlc, &SPECIFICATION::OnBnClickedButtonlc)
	ON_BN_CLICKED(IDC_BUTTON1, &SPECIFICATION::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// SPECIFICATION message handlers
void SPECIFICATION::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j,k;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}

	//開啟記憶體紀錄R、G、B
    GRAY=new int * [height]; 
    for(i=0;i<height;i++) GRAY[i]=new int [width];
    nGRAY=new int * [height]; 
    for(i=0;i<height;i++) nGRAY[i]=new int [width];
	for(i=0;i<256;i++)
	{
		hist[i] = 0;
		PDF[i] = 0;
		CDF[i] = 0;
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			GRAY[i][j]=(Input_R[i][j]+Input_G[i][j]+Input_B[i][j])/3;
		}
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			for(k=0;k<256;k++)
			{
				if(GRAY[i][j] == k)
				{
					hist[k]++;
				}
			}
		}
	}
	for(int i=1;i<256;i++)
	{
		PDF[0] = hist[0];
		PDF[i] = PDF[i-1] + hist[i];
	}
	for(int i=0;i<256;i++)
	{ CDF[i] = ( PDF[i]*(255)/(height*width) ); }

	CClientDC dc(this);
	image = new CDIBSectionLite();
	image->CreateEmptyDIB(width,height,24);
    for(i=0;i<height;i++) 
	{
		for(j=0;j<width;j++)
	    {
			image->SetPixel(j,i,RGB(GRAY[i][j],GRAY[i][j],GRAY[i][j]));
		}		
	}
}
void SPECIFICATION::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));

	CPen pen1(PS_SOLID,1,RGB(0,0,0));						
	CPen *oldPen1 = dc.SelectObject(&pen1);
	dc.MoveTo(10,20+height);    
	dc.LineTo(10,20+height+256);
	dc.LineTo(10+width,20+height+256);
	dc.SelectObject(oldPen1);
}

void SPECIFICATION::OnBnClickedButtonhb()
{
	for(int i=0;i<256;i++)
	{
		dPDF[i] = 0;
		dPDF[i] = double(i)/32640;
	}


	dCDF[0] = 0;
	dCDF[0] = dPDF[0]*255;
	for(int i=1;i<256;i++)
	{
		dCDF[i] = 0;
		dCDF[i] = dCDF[i-1] + dPDF[i]*255;
	}

	for(int j=0;j<256;j++)
	{
		z[j] = 0;
		double minvalue=255;
		for(int i=0;i<256;i++)
		{			
			if((CDF[j]-dCDF[i])*(CDF[j]-dCDF[i])<minvalue)
			{
				minvalue=(CDF[j]-dCDF[i])*(CDF[j]-dCDF[i]);
				z[j] = i;
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
			image2->SetPixel(j,i,RGB(z[GRAY[i][j]],z[GRAY[i][j]],z[GRAY[i][j]]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GRAY[i][j] * GRAY[i][j];
			noise += (z[GRAY[i][j]]-GRAY[i][j]) * (z[GRAY[i][j]]-GRAY[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SPECIFICATION::OnBnClickedButtonlb()
{
	for(int i=0;i<256;i++)
	{
		dPDF[i] = 0;
		dPDF[i] = double(255-i)/32640;
	}


	dCDF[0] = 0;
	dCDF[0] = dPDF[0]*255;
	for(int i=1;i<256;i++)
	{
		dCDF[i] = 0;
		dCDF[i] = dCDF[i-1] + dPDF[i]*255;
	}

	for(int j=0;j<256;j++)
	{
		z[j] = 0;
		double minvalue=255;
		for(int i=0;i<256;i++)
		{			
			if((CDF[j]-dCDF[i])*(CDF[j]-dCDF[i])<minvalue)
			{
				minvalue=(CDF[j]-dCDF[i])*(CDF[j]-dCDF[i]);
				z[j] = i;
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
			image2->SetPixel(j,i,RGB(z[GRAY[i][j]],z[GRAY[i][j]],z[GRAY[i][j]]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GRAY[i][j] * GRAY[i][j];
			noise += (z[GRAY[i][j]]-GRAY[i][j]) * (z[GRAY[i][j]]-GRAY[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SPECIFICATION::OnBnClickedButtonhc()
{
	for(int i=127;i>=0;i--)
	{
		dPDF[i] = 0;
		dPDF[i] = double(128-i)/16512;
	}
	for(int i=128;i<256;i++)
	{
		dPDF[i] = 0;
		dPDF[i] = double(i-127)/16512;
	}


	dCDF[0] = 0;
	dCDF[0] = dPDF[0]*255;
	for(int i=1;i<256;i++)
	{
		dCDF[i] = 0;
		dCDF[i] = dCDF[i-1] + dPDF[i]*255;
	}

	for(int j=0;j<256;j++)
	{
		z[j] = 0;
		double minvalue=255;
		for(int i=0;i<256;i++)
		{			
			if((CDF[j]-dCDF[i])*(CDF[j]-dCDF[i])<minvalue)
			{
				minvalue=(CDF[j]-dCDF[i])*(CDF[j]-dCDF[i]);
				z[j] = i;
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
			image2->SetPixel(j,i,RGB(z[GRAY[i][j]],z[GRAY[i][j]],z[GRAY[i][j]]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GRAY[i][j] * GRAY[i][j];
			noise += (z[GRAY[i][j]]-GRAY[i][j]) * (z[GRAY[i][j]]-GRAY[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SPECIFICATION::OnBnClickedButtonlc()
{
	for(int i=0;i<=127;i++)
	{
		dPDF[i] = 0;
		dPDF[i] = double(i+1)/16512;
	}
	for(int i=128;i<256;i++)
	{
		dPDF[i] = 0;
		dPDF[i] = double(256-i)/16512;
	}


	dCDF[0] = 0;
	dCDF[0] = dPDF[0]*255;
	for(int i=1;i<256;i++)
	{
		dCDF[i] = 0;
		dCDF[i] = dCDF[i-1] + dPDF[i]*255;
	}

	for(int j=0;j<256;j++)
	{
		z[j] = 0;
		double minvalue=255;
		for(int i=0;i<256;i++)
		{			
			if((CDF[j]-dCDF[i])*(CDF[j]-dCDF[i])<minvalue)
			{
				minvalue=(CDF[j]-dCDF[i])*(CDF[j]-dCDF[i]);
				z[j] = i;
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
			image2->SetPixel(j,i,RGB(z[GRAY[i][j]],z[GRAY[i][j]],z[GRAY[i][j]]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GRAY[i][j] * GRAY[i][j];
			noise += (z[GRAY[i][j]]-GRAY[i][j]) * (z[GRAY[i][j]]-GRAY[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SPECIFICATION::OnBnClickedButton1()
{
	UpdateData();
	for(int i=0;i<=x1;i++)
	{
		//int a = x1*y1/2;
		double t1 = y1/x1;
		dPDF[i] = 0;
		dPDF[i] = double( t1*i );
	}
	for(int i=x1+1;i<=x2;i++)
	{
		//int b = (x1*y1) + ( (x2-x1)*(y2-y1)/2 );
		double t2 = (y2-y1)/(x2-x1);
		dPDF[i] = 0;
		dPDF[i] = double( y1+ ( t2*(i-x1)) );
	}
	for(int i=x2+1;i<256;i++)
	{
		//int c = (x2*y2) + ( (255-x2)*(255-y2)/2 );
		double t3 = (255-y2)/(255-x2);
		dPDF[i] = 0;
		dPDF[i] = double( y2+ ( t3*(i-x2)) );
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(GRAY[i][j] == k)
				{
					nGRAY[i][j] = dPDF[k];
				}
			}
		}
	}

	/*for(int j=0;j<256;j++)
	{
		z[j] = 0;
		double minvalue=255;
		for(int i=0;i<256;i++)
		{			
			if((CDF[j]-dCDF[i])*(CDF[j]-dCDF[i])<minvalue)
			{
				minvalue=(CDF[j]-dCDF[i])*(CDF[j]-dCDF[i]);
				z[j] = i;
			}
		}
	}*/

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			image2->SetPixel(j,i,RGB(nGRAY[i][j],nGRAY[i][j],nGRAY[i][j]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(265,265,24);
    for(int i=0;i<265;i++) 
	{
		for(int j=0;j<265;j++)
	    {
			bg->SetPixel(j,i,RGB(236,233,216));
		}
		
	}bg->Draw(&dc,CPoint(10,270));

	CPen pen1(PS_SOLID,1,RGB(0,0,0));						
	CPen *oldPen1 = dc.SelectObject(&pen1);
	dc.MoveTo(10,20+height);    
	dc.LineTo(10,20+height+256);
	dc.LineTo(10+width,20+height+256);
	dc.SelectObject(oldPen1);

	CPen pen2(PS_SOLID,2,RGB(255,0,0));						
	CPen *oldPen2 = dc.SelectObject(&pen2);
	dc.MoveTo(10,20+height+256);    
	dc.LineTo(10+x1,20+height+256-y1);
	dc.LineTo(10+x1+(x2-x1),20+height+256-y1-(y2-y1));
	dc.LineTo(10+255,20+height+256-255);
	dc.SelectObject(oldPen2);

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GRAY[i][j] * GRAY[i][j];
			noise += (nGRAY[i][j]-GRAY[i][j]) * (nGRAY[i][j]-GRAY[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SPECIFICATION::OnLButtonDown(UINT nFlags, CPoint point)
{
	//UpdateData();
	m_FirstPoint = point;
	SetCapture();
	px1 = point.x;
	py1 = point.y;
	if(px1 > 10 && px1 < 266 && py1 > 276 && py1 < 532)
	{
		CClientDC dc(this);
		x1 = px1-10;
		y1 = 256 - (py1 - 276);

		for(int i=0;i<=x1;i++)
		{
			//int a = x1*y1/2;
			double t1 = y1/x1;
			dPDF[i] = 0;
			dPDF[i] = double( t1*i );
		}
		for(int i=x1+1;i<256;i++)
		{
			//int c = (x2*y2) + ( (255-x2)*(255-y2)/2 );
			double t3 = (255-y1)/(255-x1);
			dPDF[i] = 0;
			dPDF[i] = double( y1+ ( t3*(i-x1)) );
		}
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				for(int k=0;k<256;k++)
				{
					if(GRAY[i][j] == k)
					{
						nGRAY[i][j] = dPDF[k];
					}
				}
			}
		}

		image2 = new CDIBSectionLite();
		image2->CreateEmptyDIB(width,height,24);
	    for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
		    {
				image2->SetPixel(j,i,RGB(nGRAY[i][j],nGRAY[i][j],nGRAY[i][j]));
			}		
		}image2->Draw(&dc,CPoint(276,10));

		//計算SNR
		float single=0,noise=0;
		float SNR;
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				single += GRAY[i][j] * GRAY[i][j];
				noise += (nGRAY[i][j]-GRAY[i][j]) * (nGRAY[i][j]-GRAY[i][j]);
			}
		}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();

		bg = new CDIBSectionLite();
		bg->CreateEmptyDIB(265,265,24);
	    for(int i=0;i<265;i++) 
		{
			for(int j=0;j<265;j++)
		    {
				bg->SetPixel(j,i,RGB(236,233,216));
			}
			
		}bg->Draw(&dc,CPoint(10,270));
		
		CPen pen1(PS_SOLID,1,RGB(0,0,0));						
		CPen *oldPen1 = dc.SelectObject(&pen1);
		dc.MoveTo(10,20+height);    
		dc.LineTo(10,20+height+256);
		dc.LineTo(10+width,20+height+256);
		dc.SelectObject(oldPen1);
	
		CPen pen2(PS_SOLID,2,RGB(255,0,0));						
		CPen *oldPen2 = dc.SelectObject(&pen2);
		dc.MoveTo(10,20+height+256);    
		dc.LineTo(px1,py1);
		dc.LineTo(10+255,20+height+256-255);
		dc.SelectObject(oldPen2);
	}
	if(this == GetCapture())
	ReleaseCapture();
}
