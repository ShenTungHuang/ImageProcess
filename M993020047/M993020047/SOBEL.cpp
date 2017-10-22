// SOBEL.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "SOBEL.h"


// SOBEL dialog

IMPLEMENT_DYNAMIC(SOBEL, CDialog)

SOBEL::SOBEL(CWnd* pParent /*=NULL*/)
	: CDialog(SOBEL::IDD, pParent)
	, m_snr(0)
{
	image=NULL;
	image2=NULL;
	GRAY=NULL;
	height=0;
	width=0;
}

SOBEL::~SOBEL()
{
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}

	if(image) delete image;
	if(image2) delete image2;
}

void SOBEL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
}


BEGIN_MESSAGE_MAP(SOBEL, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON5, &SOBEL::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &SOBEL::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &SOBEL::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &SOBEL::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &SOBEL::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &SOBEL::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &SOBEL::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &SOBEL::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &SOBEL::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &SOBEL::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &SOBEL::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &SOBEL::OnBnClickedButton16)
END_MESSAGE_MAP()


// SOBEL message handlers
void SOBEL::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void SOBEL::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void SOBEL::OnBnClickedButton5()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-1)*GRAY[a][c] + (-2)*GRAY[i][c] + (-1)*GRAY[b][c] +
					       0*GRAY[a][j] + 0*GRAY[i][j] + 0*GRAY[b][j] + 
					       1*GRAY[a][d] + 2*GRAY[i][d] + 1*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton6()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-1)*GRAY[a][c] + 0*GRAY[i][c] + 1*GRAY[b][c] +
					       (-2)*GRAY[a][j] + 0*GRAY[i][j] + 2*GRAY[b][j] + 
					       (-1)*GRAY[a][d] + 0*GRAY[i][d] + 1*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton7()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	double average;
	double average2;
	double average3;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
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

			average = ( (-1)*GRAY[a][c] + 0*GRAY[i][c] + 1*GRAY[b][c] +
					  (-2)*GRAY[a][j] + 0*GRAY[i][j] + 2*GRAY[b][j] + 
					  (-1)*GRAY[a][d] + 0*GRAY[i][d] + 1*GRAY[b][d] );

			average2 = ( (-1)*GRAY[a][c] + (-2)*GRAY[i][c] + (-1)*GRAY[b][c] +
					   0*GRAY[a][j] + 0*GRAY[i][j] + 0*GRAY[b][j] + 
					   1*GRAY[a][d] + 2*GRAY[i][d] + 1*GRAY[b][d] );

			average3 = sqrt( (average*average) + (average2*average2) );
			
			if(average3>255) {average3=255;}
			if(average3<0) {average3=0;}

			image2->SetPixel(j,i,RGB(average3,average3,average3));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average3-GRAY[i][j]) * (average3-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton8()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-2)*GRAY[a][c] + (-1)*GRAY[i][c] + 0*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       0*GRAY[a][d] + 1*GRAY[i][d] + 2*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton9()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( 0*GRAY[a][c] + 1*GRAY[i][c] + 2*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       (-2)*GRAY[a][d] + (-1)*GRAY[i][d] + 0*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton10()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	double average;
	double average2;
	double average3;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
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

			average =    ( (-2)*GRAY[a][c] + (-1)*GRAY[i][c] + 0*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       0*GRAY[a][d] + 1*GRAY[i][d] + 2*GRAY[b][d] );

			average2 =    ( 0*GRAY[a][c] + 1*GRAY[i][c] + 2*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       (-2)*GRAY[a][d] + (-1)*GRAY[i][d] + 0*GRAY[b][d] );

			average3 = sqrt( (average*average) + (average2*average2) );
			
			if(average3>255) {average3=255;}
			if(average3<0) {average3=0;}

			image2->SetPixel(j,i,RGB(average3,average3,average3));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average3-GRAY[i][j]) * (average3-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton11()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-1)*GRAY[a][c] + (-1)*GRAY[i][c] + (-1)*GRAY[b][c] +
					       0*GRAY[a][j] + 0*GRAY[i][j] + 0*GRAY[b][j] + 
					       1*GRAY[a][d] + 1*GRAY[i][d] + 1*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton12()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-1)*GRAY[a][c] + 0*GRAY[i][c] + 1*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       (-1)*GRAY[a][d] + 0*GRAY[i][d] + 1*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton13()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	double average;
	double average2;
	double average3;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
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

			average = ( (-1)*GRAY[a][c] + 0*GRAY[i][c] + 1*GRAY[b][c] +
					  (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					  (-1)*GRAY[a][d] + 0*GRAY[i][d] + 1*GRAY[b][d] );

			average2 = ( (-1)*GRAY[a][c] + (-1)*GRAY[i][c] + (-1)*GRAY[b][c] +
					   0*GRAY[a][j] + 0*GRAY[i][j] + 0*GRAY[b][j] + 
					   1*GRAY[a][d] + 1*GRAY[i][d] + 1*GRAY[b][d] );

			average3 = sqrt( (average*average) + (average2*average2) );
			
			if(average3>255) {average3=255;}
			if(average3<0) {average3=0;}

			image2->SetPixel(j,i,RGB(average3,average3,average3));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average3-GRAY[i][j]) * (average3-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton14()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( (-1)*GRAY[a][c] + (-1)*GRAY[i][c] + 0*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       0*GRAY[a][d] + 1*GRAY[i][d] + 1*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton15()
{
	//計算SNR
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
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			average = int( 0*GRAY[a][c] + 1*GRAY[i][c] + 1*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       (-1)*GRAY[a][d] + (-1)*GRAY[i][d] + 0*GRAY[b][d] );
			
			if(average>255) {average=255;}
			if(average<0) {average=0;}

			image2->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void SOBEL::OnBnClickedButton16()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	double average;
	double average2;
	double average3;
	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
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

			average =    ( (-1)*GRAY[a][c] + (-1)*GRAY[i][c] + 0*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       0*GRAY[a][d] + 1*GRAY[i][d] + 1*GRAY[b][d] );

			average2 =    ( 0*GRAY[a][c] + 1*GRAY[i][c] + 1*GRAY[b][c] +
					       (-1)*GRAY[a][j] + 0*GRAY[i][j] + 1*GRAY[b][j] + 
					       (-1)*GRAY[a][d] + (-1)*GRAY[i][d] + 0*GRAY[b][d] );

			average3 = sqrt( (average*average) + (average2*average2) );
			
			if(average3>255) {average3=255;}
			if(average3<0) {average3=0;}

			image2->SetPixel(j,i,RGB(average3,average3,average3));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average3-GRAY[i][j]) * (average3-GRAY[i][j]);
		}
	}image2->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}
