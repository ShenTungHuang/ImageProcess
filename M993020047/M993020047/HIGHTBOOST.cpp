// HIGHTBOOST.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "HIGHTBOOST.h"


// HIGHTBOOST dialog

IMPLEMENT_DYNAMIC(HIGHTBOOST, CDialog)

HIGHTBOOST::HIGHTBOOST(CWnd* pParent /*=NULL*/)
	: CDialog(HIGHTBOOST::IDD, pParent)
	, A(0)
	, m_snr(0)
{
	image=NULL;
	hbimage=NULL;
	GRAY=NULL;
	height=0;
	width=0;
}

HIGHTBOOST::~HIGHTBOOST()
{
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}

	if(image) delete image;
	if(hbimage) delete hbimage;
}

void HIGHTBOOST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A);
	DDX_Text(pDX, IDC_EDIT2, m_snr);
}


BEGIN_MESSAGE_MAP(HIGHTBOOST, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &HIGHTBOOST::OnBnClickedButton1)
END_MESSAGE_MAP()


// HIGHTBOOST message handlers
void HIGHTBOOST::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void HIGHTBOOST::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void HIGHTBOOST::OnBnClickedButton1()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	int average;
	UpdateData();
	CClientDC dc(this);
	hbimage = new CDIBSectionLite();
	hbimage->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int(-1*GRAY[a][c] + -1*GRAY[i][c] + -1*GRAY[b][c] + -1*GRAY[a][j] +
				          A*GRAY[i][j] +
				          -1*GRAY[b][j] + -1*GRAY[a][d] + -1*GRAY[i][d] + -1*GRAY[b][d])/9;

			if(average < 0) {average = 0;}
			if(average > 255) {average = 255;}
			hbimage->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}hbimage->Draw(&dc,CPoint(276,10));




	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}
