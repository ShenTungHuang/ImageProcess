// BITPLANE.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "BITPLANE.h"


// BITPLANE dialog

IMPLEMENT_DYNAMIC(BITPLANE, CDialog)

BITPLANE::BITPLANE(CWnd* pParent /*=NULL*/)
	: CDialog(BITPLANE::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	GG=NULL;
	GGP=NULL;
	bpimage=NULL;
	gcimage=NULL;
	height=0;
	width=0;
}

BITPLANE::~BITPLANE()
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
	if(B)															//釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] B[i]; delete [] B;
	}
	if(GG)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] GG[i]; delete [] GG;
	}
	if(GGP)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] GGP[i]; delete [] GGP;
	}

	if(bpimage) delete bpimage;
	if(gcimage) delete gcimage;
}

void BITPLANE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BITPLANE, CDialog)
	ON_BN_CLICKED(IDC_RADIO1ST, &BITPLANE::OnBnClickedRadio1st)
	ON_BN_CLICKED(IDC_RADIO2ND, &BITPLANE::OnBnClickedRadio2nd)
	ON_BN_CLICKED(IDC_RADIO3TH, &BITPLANE::OnBnClickedRadio3th)
	ON_BN_CLICKED(IDC_RADIO4TH, &BITPLANE::OnBnClickedRadio4th)
	ON_BN_CLICKED(IDC_RADIO5TH, &BITPLANE::OnBnClickedRadio5th)
	ON_BN_CLICKED(IDC_RADIO6TH, &BITPLANE::OnBnClickedRadio6th)
	ON_BN_CLICKED(IDC_RADIO7TH, &BITPLANE::OnBnClickedRadio7th)
	ON_BN_CLICKED(IDC_RADIO8TH, &BITPLANE::OnBnClickedRadio8th)
	ON_BN_CLICKED(IDC_RADIOCOMBINE, &BITPLANE::OnBnClickedRadiocombine)
END_MESSAGE_MAP()


// BITPLANE message handlers
void BITPLANE::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
	if(GG)
	{
		for(i=0;i<height;i++) delete [] GG[i]; delete [] GG;
	}
	if(GGP)
	{
		for(i=0;i<height;i++) delete [] GGP[i]; delete [] GGP;
	}

	//開啟記憶體紀錄R、G、B
	R=new int * [height]; 
    for(i=0;i<height;i++) R[i]=new int [width];

    G=new int * [height]; 
    for(i=0;i<height;i++) G[i]=new int [width];

    B=new int * [height]; 
    for(i=0;i<height;i++) B[i]=new int [width];

    GG=new int * [height]; 
    for(i=0;i<height;i++) GG[i]=new int [width];

    GGP=new int * [height]; 
    for(i=0;i<height;i++) GGP[i]=new int [width];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R[i][j]=Input_R[i][j];
			G[i][j]=Input_G[i][j];
			B[i][j]=Input_B[i][j];
			GG[i][j]=(Input_R[i][j]+Input_G[i][j]+Input_B[i][j])/3;
            int B8=(((0X80)&(GG[i][j]))/128);
			int B7=(((0X40)&(GG[i][j]))/64);
			int B6=(((0X20)&(GG[i][j]))/32);
			int B5=(((0X10)&(GG[i][j]))/16);
			int B4=(((0X08)&(GG[i][j]))/8);
			int B3=(((0X04)&(GG[i][j]))/4);
			int B2=(((0X02)&(GG[i][j]))/2);
			int B1=((0X01)&(GG[i][j]));
			if (B8==B7)
				B7=0;
			else
			    B7=1;
			if (B7==B6)
				B6=0;
			else
			    B6=1;
			if (B6==B5)
				B5=0;
			else
			    B5=1;
			if (B5==B4)
				B4=0;
			else
			    B4=1;
			if (B4==B3)
				B3=0;
			else
			    B3=1;
			if (B3==B2)
				B2=0;
			else
			    B2=1;
			if (B2==B1)
				B1=0;
			else
			    B1=1;
            GGP[i][j]=((B8*128)+(B7*64)+(B6*32)+(B5*16)+(B4*8)+(B3*4)+(B2*2)+B1);

		}
	}
}

void BITPLANE::OnBnClickedRadio1st()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
	gcimage = new CDIBSectionLite();
	gcimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X01)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X01)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio2nd()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X02)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

         if( ((0X02)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio3th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X04)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));
			
			if( ((0X04)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio4th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X08)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X08)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio5th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X10)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X10)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio6th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X20)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X20)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio7th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X40)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X40)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadio8th()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X80)&(GG[i][j]))==0 )
               bpimage->SetPixel(j,i,RGB(0,0,0));
			else
               bpimage->SetPixel(j,i,RGB(255,255,255));

			if( ((0X80)&(GGP[i][j]))==0 )
               gcimage->SetPixel(j,i,RGB(0,0,0));
			else
               gcimage->SetPixel(j,i,RGB(255,255,255));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}

void BITPLANE::OnBnClickedRadiocombine()
{
	CClientDC dc(this);
	bpimage = new CDIBSectionLite();
	bpimage->CreateEmptyDIB(width,height,24);
	gcimage = new CDIBSectionLite();
	gcimage->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            bpimage->SetPixel(j,i,RGB(GG[i][j],GG[i][j],GG[i][j]));
			gcimage->SetPixel(j,i,RGB(GGP[i][j],GGP[i][j],GGP[i][j]));
		   }
	  }
	bpimage->Draw(&dc,CPoint(10,20));
	gcimage->Draw(&dc,CPoint(341,20));
}
