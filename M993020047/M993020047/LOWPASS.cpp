// LOWPASS.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "LOWPASS.h"


// LOWPASS dialog

IMPLEMENT_DYNAMIC(LOWPASS, CDialog)

LOWPASS::LOWPASS(CWnd* pParent /*=NULL*/)
	: CDialog(LOWPASS::IDD, pParent)
	, div(9)
	, m11(1)
	, m12(1)
	, m13(1)
	, m14(1)
	, m15(1)
	, m16(1)
	, m17(1)
	, m21(1)
	, m22(1)
	, m23(1)
	, m24(1)
	, m25(1)
	, m26(1)
	, m27(1)
	, m31(1)
	, m32(1)
	, m33(1)
	, m34(1)
	, m35(1)
	, m36(1)
	, m37(1)
	, m41(1)
	, m42(1)
	, m43(1)
	, m44(1)
	, m45(1)
	, m46(1)
	, m47(1)
	, m51(1)
	, m52(1)
	, m53(1)
	, m54(1)
	, m55(1)
	, m56(1)
	, m57(1)
	, m61(1)
	, m62(1)
	, m63(1)
	, m64(1)
	, m65(1)
	, m66(1)
	, m67(1)
	, m71(1)
	, m72(1)
	, m73(1)
	, m74(1)
	, m75(1)
	, m76(1)
	, m77(1)
	, m_snr(0)
{
	image=NULL;
	lowimage=NULL;
	GRAY=NULL;
	height=0;
	width=0;
}

LOWPASS::~LOWPASS()
{
	int i;
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}
	if(image) delete image;
	if(lowimage) delete lowimage;
}

void LOWPASS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
	DDX_Text(pDX, IDC_EDITdiv, div);
	DDX_Text(pDX, IDC_EDITm11, m11);
	DDX_Text(pDX, IDC_EDITm12, m12);
	DDX_Text(pDX, IDC_EDITm13, m13);
	DDX_Text(pDX, IDC_EDITm14, m14);
	DDX_Text(pDX, IDC_EDITm15, m15);
	DDX_Text(pDX, IDC_EDITm16, m16);
	DDX_Text(pDX, IDC_EDITm17, m17);
	DDX_Text(pDX, IDC_EDITm21, m21);
	DDX_Text(pDX, IDC_EDITm22, m22);
	DDX_Text(pDX, IDC_EDITm23, m23);
	DDX_Text(pDX, IDC_EDITm24, m24);
	DDX_Text(pDX, IDC_EDITm25, m25);
	DDX_Text(pDX, IDC_EDITm26, m26);
	DDX_Text(pDX, IDC_EDITm27, m27);
	DDX_Text(pDX, IDC_EDITm31, m31);
	DDX_Text(pDX, IDC_EDITm32, m32);
	DDX_Text(pDX, IDC_EDITm33, m33);
	DDX_Text(pDX, IDC_EDITm34, m34);
	DDX_Text(pDX, IDC_EDITm35, m35);
	DDX_Text(pDX, IDC_EDITm36, m36);
	DDX_Text(pDX, IDC_EDITm37, m37);
	DDX_Text(pDX, IDC_EDITm41, m41);
	DDX_Text(pDX, IDC_EDITm42, m42);
	DDX_Text(pDX, IDC_EDITm43, m43);
	DDX_Text(pDX, IDC_EDITm44, m44);
	DDX_Text(pDX, IDC_EDITm45, m45);
	DDX_Text(pDX, IDC_EDITm46, m46);
	DDX_Text(pDX, IDC_EDITm47, m47);
	DDX_Text(pDX, IDC_EDITm51, m51);
	DDX_Text(pDX, IDC_EDITm52, m52);
	DDX_Text(pDX, IDC_EDITm53, m53);
	DDX_Text(pDX, IDC_EDITm54, m54);
	DDX_Text(pDX, IDC_EDITm55, m55);
	DDX_Text(pDX, IDC_EDITm56, m56);
	DDX_Text(pDX, IDC_EDITm57, m57);
	DDX_Text(pDX, IDC_EDITm61, m61);
	DDX_Text(pDX, IDC_EDITm62, m62);
	DDX_Text(pDX, IDC_EDITm63, m63);
	DDX_Text(pDX, IDC_EDITm64, m64);
	DDX_Text(pDX, IDC_EDITm65, m65);
	DDX_Text(pDX, IDC_EDITm66, m66);
	DDX_Text(pDX, IDC_EDITm67, m67);
	DDX_Text(pDX, IDC_EDITm71, m71);
	DDX_Text(pDX, IDC_EDITm72, m72);
	DDX_Text(pDX, IDC_EDITm73, m73);
	DDX_Text(pDX, IDC_EDITm74, m74);
	DDX_Text(pDX, IDC_EDITm75, m75);
	DDX_Text(pDX, IDC_EDITm76, m76);
	DDX_Text(pDX, IDC_EDITm77, m77);
}


BEGIN_MESSAGE_MAP(LOWPASS, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON33, &LOWPASS::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON55, &LOWPASS::OnBnClickedButton55)
	ON_BN_CLICKED(IDC_BUTTON77, &LOWPASS::OnBnClickedButton77)
END_MESSAGE_MAP()


// LOWPASS message handlers
void LOWPASS::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void LOWPASS::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void LOWPASS::OnBnClickedButton33()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	int average;
	UpdateData();
	CClientDC dc(this);
	lowimage = new CDIBSectionLite();
	lowimage->CreateEmptyDIB(width,height,24);
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

			average = int( m11*GRAY[a][c] + m21*GRAY[i][c] + m31*GRAY[b][c] +
					       m12*GRAY[a][j] + m22*GRAY[i][j] + m32*GRAY[b][j] + 
					       m13*GRAY[a][d] + m23*GRAY[i][d] + m33*GRAY[b][d] )/div;
			if(average<0) {average=0;}
			if(average>255) {average=255;}
			lowimage->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}lowimage->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void LOWPASS::OnBnClickedButton55()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	int average;
	UpdateData();
	CClientDC dc(this);
	lowimage = new CDIBSectionLite();
	lowimage->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;
			int e=i-2;
			int f=i+2;
			int g=j-2;
			int h=j+2;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}
			if(e==-1) {e=height-1;}
			if(e==-2) {e=height-2;}
			if(f=height) {f=0;}
			if(f==height+1) {f=1;}
			if(g==-1) {g=width-1;}
			if(g==-2) {g=width-2;}
			if(h==width) {h=0;}
			if(h==width+1) {h=1;}

			average = int( m11*GRAY[e][g] + m21*GRAY[a][g] + m31*GRAY[i][g] + m41*GRAY[b][g] + m51*GRAY[f][g] +
					       m12*GRAY[e][c] + m22*GRAY[a][c] + m32*GRAY[i][c] + m42*GRAY[b][c] + m52*GRAY[f][c] +
					       m13*GRAY[e][j] + m23*GRAY[a][j] + m33*GRAY[i][j] + m43*GRAY[b][j] + m53*GRAY[f][j] +
						   m14*GRAY[e][d] + m24*GRAY[a][d] + m34*GRAY[i][d] + m44*GRAY[b][d] + m54*GRAY[f][d] +
						   m15*GRAY[e][h] + m25*GRAY[a][h] + m35*GRAY[i][h] + m45*GRAY[b][h] + m55*GRAY[f][h])/div;
			if(average<0) {average=0;}
			if(average>255) {average=255;}
			lowimage->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}lowimage->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void LOWPASS::OnBnClickedButton77()
{
	//計算SNR
	float single=0,noise=0;
	float SNR;
	int average;
	UpdateData();
	CClientDC dc(this);
	lowimage = new CDIBSectionLite();
	lowimage->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int a=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;
			int e=i-2;
			int f=i+2;
			int g=j-2;
			int h=j+2;
			int k=i-3;
			int l=i+3;
			int m=j-3;
			int n=j+3;

			if(a==-1) {a=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}
			if(e==-1) {e=height-1;}
			if(e==-2) {e=height-2;}
			if(f=height) {f=0;}
			if(f==height+1) {f=1;}
			if(g==-1) {g=width-1;}
			if(g==-2) {g=width-2;}
			if(h==width) {h=0;}
			if(h==width+1) {h=1;}
			if(k==-1) {k=height-1;}
			if(k==-2) {k=height-2;}
			if(k==-3) {k=height-3;}
			if(l==height) {l=0;}
			if(l==height+1) {l=1;}
			if(l==height+2) {l=2;}
			if(m==-1) {m=width-1;}
			if(m==-2) {m=width-2;}
			if(m==-3) {m=width-3;}
			if(n==width) {n=0;}
			if(n==width+1) {n=1;}
			if(n==width+2) {n=2;}

			average = int( m11*GRAY[k][m] + m21*GRAY[e][m] + m31*GRAY[a][m] + m41*GRAY[i][m] + m51*GRAY[b][m] + m61*GRAY[f][m] + m71*GRAY[l][m] +
					       m12*GRAY[k][g] + m22*GRAY[e][g] + m32*GRAY[a][g] + m42*GRAY[i][g] + m52*GRAY[b][g] + m62*GRAY[f][g] + m72*GRAY[l][g] +
					       m13*GRAY[k][c] + m23*GRAY[e][c] + m33*GRAY[a][c] + m43*GRAY[i][c] + m53*GRAY[b][c] + m63*GRAY[f][c] + m73*GRAY[l][c] +
						   m14*GRAY[k][j] + m24*GRAY[e][j] + m34*GRAY[a][j] + m44*GRAY[i][j] + m54*GRAY[b][j] + m64*GRAY[f][j] + m74*GRAY[l][j] +
						   m15*GRAY[k][d] + m25*GRAY[e][d] + m35*GRAY[a][d] + m45*GRAY[i][d] + m55*GRAY[b][d] + m65*GRAY[f][d] + m75*GRAY[l][d] +
						   m16*GRAY[k][h] + m26*GRAY[e][h] + m36*GRAY[a][h] + m46*GRAY[i][h] + m56*GRAY[b][h] + m66*GRAY[f][h] + m76*GRAY[l][h] + 
						   m17*GRAY[k][n] + m27*GRAY[e][n] + m37*GRAY[a][n] + m47*GRAY[i][n] + m57*GRAY[b][n] + m67*GRAY[f][n] + m77*GRAY[l][n])/div;
			if(average<0) {average=0;}
			if(average>255) {average=255;}
			lowimage->SetPixel(j,i,RGB(average,average,average));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (average-GRAY[i][j]) * (average-GRAY[i][j]);
		}
	}lowimage->Draw(&dc,CPoint(276,10));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}
