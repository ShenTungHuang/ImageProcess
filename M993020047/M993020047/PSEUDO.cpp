// PSEUDO.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "PSEUDO.h"


// PSEUDO dialog

IMPLEMENT_DYNAMIC(PSEUDO, CDialog)

PSEUDO::PSEUDO(CWnd* pParent /*=NULL*/)
	: CDialog(PSEUDO::IDD, pParent)
	, m_snr(0)
{
	image=NULL;
	image2=NULL;
	GRAY=NULL;
	height=0;
	width=0;
}

PSEUDO::~PSEUDO()
{
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}

	if(image) delete image;
	if(image2) delete image2;
}

void PSEUDO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
}


BEGIN_MESSAGE_MAP(PSEUDO, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONMAXMIN, &PSEUDO::OnBnClickedButtonmaxmin)
	ON_BN_CLICKED(IDC_BUTTONMINMAX, &PSEUDO::OnBnClickedButtonminmax)
	ON_BN_CLICKED(IDC_BUTTONPMED, &PSEUDO::OnBnClickedButtonpmed)
END_MESSAGE_MAP()


// PSEUDO message handlers
void PSEUDO::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}

	//開啟記憶體紀錄R、G、B

    GRAY=new int * [height]; 
    for(i=0;i<height;i++) GRAY[i]=new int [width];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			GRAY[i][j]=(Input_R[i][j]+Input_G[i][j]+Input_B[i][j])/3;
		}
	}
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
void PSEUDO::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void PSEUDO::OnBnClickedButtonmaxmin()
{
	float single=0,noise=0;
	float SNR;
	int average;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int w=i-1;
			int x=i+1;
			int y=j-1;
			int z=j+1;

			if(w==-1) {w=height-1;}
			if(x==height) {x=0;}
			if(y==-1) {y=width-1;}
			if(z==width) {z=0;}

			int a = GRAY[i][j];
			int b = GRAY[i][y];
			int c = GRAY[i][z];
			int d = GRAY[w][j];
			int e = GRAY[x][j];

			int med = max( min(a,b,c) , min(a,b,d) , min(a,b,e) , min(a,c,d) , min(a,c,e) ,
				           min(a,d,e) , min(b,c,d) , min(b,c,e) , min(b,d,e) , min(c,d,e) );

			if(med<0) {med=0;}
			if(med>255) {med=255;}
			image2->SetPixel(j,i,RGB(med,med,med));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (med-GRAY[i][j]) * (med-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void PSEUDO::OnBnClickedButtonminmax()
{
	float single=0,noise=0;
	float SNR;
	int average;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int w=i-1;
			int x=i+1;
			int y=j-1;
			int z=j+1;

			if(w==-1) {w=height-1;}
			if(x==height) {x=0;}
			if(y==-1) {y=width-1;}
			if(z==width) {z=0;}

			int a = GRAY[i][j];
			int b = GRAY[i][y];
			int c = GRAY[i][z];
			int d = GRAY[w][j];
			int e = GRAY[x][j];

			int med = min( max(a,b,c) , max(a,b,d) , max(a,b,e) , max(a,c,d) , max(a,c,e) ,
				           max(a,d,e) , max(b,c,d) , max(b,c,e) , max(b,d,e) , max(c,d,e) );

			if(med<0) {med=0;}
			if(med>255) {med=255;}
			image2->SetPixel(j,i,RGB(med,med,med));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (med-GRAY[i][j]) * (med-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void PSEUDO::OnBnClickedButtonpmed()
{
	float single=0,noise=0;
	float SNR;
	int average;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int w=i-1;
			int x=i+1;
			int y=j-1;
			int z=j+1;

			if(w==-1) {w=height-1;}
			if(x==height) {x=0;}
			if(y==-1) {y=width-1;}
			if(z==width) {z=0;}

			int a = GRAY[i][j];
			int b = GRAY[i][y];
			int c = GRAY[i][z];
			int d = GRAY[w][j];
			int e = GRAY[x][j];

			int med1 = max( min(a,b,c) , min(a,b,d) , min(a,b,e) , min(a,c,d) , min(a,c,e) ,
				           min(a,d,e) , min(b,c,d) , min(b,c,e) , min(b,d,e) , min(c,d,e) );
			int med2 = min( max(a,b,c) , max(a,b,d) , max(a,b,e) , max(a,c,d) , max(a,c,e) ,
				           max(a,d,e) , max(b,c,d) , max(b,c,e) , max(b,d,e) , max(c,d,e) );
			int med3 = (0.5*med1)+(0.5*med2);
			if(med3<0) {med3=0;}
			if(med3>255) {med3=255;}
			image2->SetPixel(j,i,RGB(med3,med3,med3));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (med3-GRAY[i][j]) * (med3-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}
