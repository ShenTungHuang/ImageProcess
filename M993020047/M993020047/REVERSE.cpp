// REVERSE.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "REVERSE.h"


// REVERSE dialog

IMPLEMENT_DYNAMIC(REVERSE, CDialog)

REVERSE::REVERSE(CWnd* pParent /*=NULL*/)
	: CDialog(REVERSE::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	reverseimage=NULL;
	height=0;
	width=0;
}

REVERSE::~REVERSE()
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

	if(reverseimage) delete reverseimage;

}

void REVERSE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(REVERSE, CDialog)
	ON_BN_CLICKED(IDC_RADIOVERTICAL, &REVERSE::OnBnClickedRadiovertical)
	ON_BN_CLICKED(IDC_RADIOHORIZONTAL, &REVERSE::OnBnClickedRadiohorizontal)
	ON_BN_CLICKED(IDC_RADIOVANDH, &REVERSE::OnBnClickedRadiovandh)
	ON_BN_CLICKED(IDC_RADIOHANDV, &REVERSE::OnBnClickedRadiohandv)
END_MESSAGE_MAP()


// REVERSE message handlers
void REVERSE::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void REVERSE::OnBnClickedRadiovertical()
{
	CClientDC dc(this);
	reverseimage = new CDIBSectionLite();
	reverseimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			reverseimage->SetPixel(255-j,i,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}reverseimage->Draw(&dc,CPoint(20,20));
}

void REVERSE::OnBnClickedRadiohorizontal()
{
	CClientDC dc(this);
	reverseimage = new CDIBSectionLite();
	reverseimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			reverseimage->SetPixel(j,255-i,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}reverseimage->Draw(&dc,CPoint(20,20));
}

void REVERSE::OnBnClickedRadiovandh()
{
	CClientDC dc(this);
	reverseimage = new CDIBSectionLite();
	reverseimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			reverseimage->SetPixel(255-i,255-j,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}reverseimage->Draw(&dc,CPoint(20,20));
}

void REVERSE::OnBnClickedRadiohandv()
{
	CClientDC dc(this);
	reverseimage = new CDIBSectionLite();
	reverseimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			reverseimage->SetPixel(i,j,RGB(R[i][j],G[i][j],B[i][j]));
		}
		
	}reverseimage->Draw(&dc,CPoint(20,20));
}
