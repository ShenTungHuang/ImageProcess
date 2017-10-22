// RGBColor.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "RGBColor.h"


// RGBColor dialog

IMPLEMENT_DYNAMIC(RGBColor, CDialog)

RGBColor::RGBColor(CWnd* pParent /*=NULL*/)
	: CDialog(RGBColor::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	rgbimage=NULL;
	height=0;
	width=0;
}

RGBColor::~RGBColor()
{
	int i;


	if(R)															//����R���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] R[i]; delete [] R;
	}
	if(G)															//����G���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] G[i]; delete [] G;
	}
	if(B)															////����B���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] B[i]; delete [] B;
	}

	if(rgbimage) delete rgbimage;
}

void RGBColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RGBColor, CDialog)
	ON_BN_CLICKED(IDC_RADIORED, &RGBColor::OnBnClickedRadiored)
	ON_BN_CLICKED(IDC_RADIOGREEN, &RGBColor::OnBnClickedRadiogreen)
	ON_BN_CLICKED(IDC_RADIOBLUE, &RGBColor::OnBnClickedRadioblue)
END_MESSAGE_MAP()


// RGBColor message handlers
void RGBColor::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//�ˬdR�BG�BB�O����O�_�w�g�إߡA�O�h�R��
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

	//�}�ҰO�������R�BG�BB
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


void RGBColor::OnBnClickedRadiored()
{
	CClientDC dc(this);
	rgbimage = new CDIBSectionLite();
	rgbimage->CreateEmptyDIB(width,height,24);
		
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					rgbimage->SetPixel(j,i,RGB(R[i][j],0,0));
				}
			}rgbimage->Draw(&dc,CPoint(20,20));
}

void RGBColor::OnBnClickedRadiogreen()
{
	CClientDC dc(this);
	rgbimage = new CDIBSectionLite();
	rgbimage->CreateEmptyDIB(width,height,24);
		
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					rgbimage->SetPixel(j,i,RGB(0,G[i][j],0));
				}
			}rgbimage->Draw(&dc,CPoint(20,20));
}

void RGBColor::OnBnClickedRadioblue()
{
	CClientDC dc(this);
	rgbimage = new CDIBSectionLite();
	rgbimage->CreateEmptyDIB(width,height,24);
		
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					rgbimage->SetPixel(j,i,RGB(0,0,B[i][j]));
				}
			}rgbimage->Draw(&dc,CPoint(20,20));
}
