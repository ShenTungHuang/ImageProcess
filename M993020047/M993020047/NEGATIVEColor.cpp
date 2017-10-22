// NEGATIVEColor.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "NEGATIVEColor.h"


// NEGATIVEColor dialog

IMPLEMENT_DYNAMIC(NEGATIVEColor, CDialog)

NEGATIVEColor::NEGATIVEColor(CWnd* pParent /*=NULL*/)
	: CDialog(NEGATIVEColor::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	G_r=NULL;
	G_g=NULL;
	G_b=NULL;
	negativeimage=NULL;
}

NEGATIVEColor::~NEGATIVEColor()
{
	int i;
	height=0;
	width=0;

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

	if(G_r)															//����R���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] G_r[i]; delete [] G_r;
	}
	if(G_g)															//����G���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] G_g[i]; delete [] G_g;
	}
	if(G_b)															////����B���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] G_b[i]; delete [] G_b;
	}

	if(negativeimage) delete negativeimage;
}

void NEGATIVEColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NEGATIVEColor, CDialog)
	ON_BN_CLICKED(IDC_RADIONCOLOR, &NEGATIVEColor::OnBnClickedRadioncolor)
	ON_BN_CLICKED(IDC_RADIONGRAY, &NEGATIVEColor::OnBnClickedRadiongray)
END_MESSAGE_MAP()


// NEGATIVEColor message handlers
void NEGATIVEColor::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void NEGATIVEColor::OnBnClickedRadioncolor()
{
	CClientDC dc(this);
	negativeimage = new CDIBSectionLite();
	negativeimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			negativeimage->SetPixel(j,i,RGB(255-R[i][j],255-G[i][j],255-B[i][j]));
		}
		
	}negativeimage->Draw(&dc,CPoint(20,20));	
}

void NEGATIVEColor::OnBnClickedRadiongray()
{
	G_r=new int * [height]; 
	for(int i=0;i<height;i++) G_r[i]=new int [width];    //�إ�R���Ŷ�	

	G_g=new int * [height]; 
	for(int i=0;i<height;i++) G_g[i]=new int [width];    //�إ�G���Ŷ�

	G_b=new int * [height]; 
	for(int i=0;i<height;i++) G_b[i]=new int [width];    //�إ�B���Ŷ�

	CClientDC dc(this);
	negativeimage = new CDIBSectionLite();
	negativeimage->CreateEmptyDIB(width,height,24);
		    for(int i=0;i<height;i++) 
			{
				for(int j=0;j<width;j++)
			    {
					G_r[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					G_g[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					G_b[i][j]=(R[i][j]+G[i][j]+B[i][j])/3;
					negativeimage->SetPixel(j,i,RGB(255-G_r[i][j],255-G_g[i][j],255-G_b[i][j]));
				}
			}negativeimage->Draw(&dc,CPoint(20,20));
}
