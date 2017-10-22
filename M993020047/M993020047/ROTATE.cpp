// ROTATE.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "ROTATE.h"


// ROTATE dialog

IMPLEMENT_DYNAMIC(ROTATE, CDialog)

ROTATE::ROTATE(CWnd* pParent /*=NULL*/)
	: CDialog(ROTATE::IDD, pParent)
	, degree(0)
{
	R=NULL;
	G=NULL;
	B=NULL;
	X=NULL;
	Y=NULL;
	bg=NULL;
	holeimage=NULL;
	noholeimage=NULL;
	height=0;
	width=0;
}

ROTATE::~ROTATE()
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
	if(X)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] X[i]; delete [] X;
	}
	if(Y)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] Y[i]; delete [] Y;
	}
	/*if(X_1)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] X_1[i]; delete [] X_1;
	}
	if(Y_1)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] Y_1[i]; delete [] Y_1;
	}
	if(X_2)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] X_2[i]; delete [] X_2;
	}
	if(Y_2)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] Y_2[i]; delete [] Y_2;
	}*/

	if(bg) delete bg;
	if(image) delete image;
	if(holeimage) delete holeimage;
	if(noholeimage) delete noholeimage;
}

void ROTATE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, degree);
}


BEGIN_MESSAGE_MAP(ROTATE, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONWITHHOLE, &ROTATE::OnBnClickedButtonwithhole)
	ON_BN_CLICKED(IDC_BUTTONWITHOUTHOLE, &ROTATE::OnBnClickedButtonwithouthole)
END_MESSAGE_MAP()


// ROTATE message handlers
void ROTATE::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
void ROTATE::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(0,0));
}

void ROTATE::OnBnClickedButtonwithhole()
{
	UpdateData();
	rad=(3.14159)*degree/180;
	int length = height*sin(rad) + height*cos(rad);
	int length_bg = height*sin((3.14159)*45/180) + height*cos((3.14159)*45/180);

	CClientDC dc(this);
	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(length_bg,length_bg,24);
	for(int i=0;i<length_bg;i++) 
	{
		for(int j=0;j<length_bg;j++)
		 {
			bg->SetPixel(j,i,RGB(236,233,216));
		 }
	
	}bg->Draw(&dc,CPoint(266,0));

	holeimage = new CDIBSectionLite();
	holeimage->CreateEmptyDIB(length,length,24);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int y = ( (j-width/2)*sin(-rad) + (i-height/2)*cos(-rad) );
			int	x = ( (j-width/2)*cos(-rad) - (i-height/2)*sin(-rad) );

			holeimage->SetPixel(x+length/2,y+length/2,RGB(R[i][j],G[i][j],B[i][j]));
		}
	}holeimage->Draw(&dc,CPoint(266,0));
}

void ROTATE::OnBnClickedButtonwithouthole()
{
	UpdateData();
	rad=(3.14159)*degree/180;
	int length = height*sin(rad) + height*cos(rad);
	int length_bg = height*sin((3.14159)*45/180) + height*cos((3.14159)*45/180);

	/*X=new int * [height]; 
    for(int i=0;i<height;i++) X[i]=new int [width];

    Y=new int * [height]; 
    for(int i=0;i<height;i++) Y[i]=new int [width];*/

	CClientDC dc(this);
	bg = new CDIBSectionLite();
	bg->CreateEmptyDIB(length_bg,length_bg,24);
	for(int i=0;i<length_bg;i++) 
	{
		for(int j=0;j<length_bg;j++)
		 {
			bg->SetPixel(j,i,RGB(236,233,216));
		 }
	
	}bg->Draw(&dc,CPoint(638,0));

	noholeimage = new CDIBSectionLite();
	noholeimage->CreateEmptyDIB(length,length,24);
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<length;j++)
		{
			//int y = ( (j)*sin(rad) + (i)*cos(rad) );// + width+height*sin((degree-180)*3.14159/180)*cos((degree-180)*3.14159/180)-1;
			//int	x = ( (j)*cos(rad) - (i)*sin(rad) );// + +height-height*sin((degree-180)*3.14159/180)*sin((degree-180)*3.14159/180);
			
			int y =(int)((i)*cos(rad)-(j)*sin(rad)+height*sin(rad)*sin(rad));
			int x =(int)((j)*cos(rad)+(i)*sin(rad)-height*sin(rad)*cos(rad));

			if(y>=0 && x>=0 && y<width && x<height)
			{
				noholeimage->SetPixel(i,j,RGB(R[x][y],G[x][y],B[x][y]));
			}
		}
	}noholeimage->Draw(&dc,CPoint(638,0));



	/*Ymin=0;	Xmin=0;	Ymax=0; Xmax=0;
	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{
			X[i][j] = 0;
			Y[i][j] = 0;
			X[i][j] = j*cos(rad) - i*sin(rad);
			Y[i][j] = j*sin(rad) + i*cos(rad);
			if(X[i][j]<Xmin) {Xmin = X[i][j];}
			if(Y[i][j]<Ymin) {Ymin = Y[i][j];}
			if(X[i][j]>Xmax) {Xmax = X[i][j];}
			if(Y[i][j]>Ymax) {Ymax = Y[i][j];}
		}
	}

	X_1=new int * [Ymax - Ymin +1]; 
    for(int i=0;i<(Ymax - Ymin +1);i++) X_1[i]=new int [Xmax - Xmin +1];

    Y_1=new int * [Ymax - Ymin +1]; 
    for(int i=0;i<(Ymax - Ymin +1);i++) Y_1[i]=new int [Xmax - Xmin +1];

	X_2=new int * [Ymax - Ymin +1]; 
    for(int i=0;i<(Ymax - Ymin +1);i++) X_2[i]=new int [Xmax - Xmin +1];

    Y_2=new int * [Ymax - Ymin +1]; 
    for(int i=0;i<(Ymax - Ymin +1);i++) Y_2[i]=new int [Xmax - Xmin +1];
	noholeimage = new CDIBSectionLite();
	noholeimage->CreateEmptyDIB(length,length,24);
	for(int i=0;i<(Ymax-Ymin+1);i++) 		
	{
		for(int j=0;j<(Xmax-Xmin+1);j++)
		{
			X_1[i][j] = 0;
			Y_1[i][j] = 0;
			X_1[i][j] = Xmin+j;
			Y_1[i][j] = Ymin+i;
			X_2[i][j] = (X_1[i][j])*cos(-rad) - (Y_1[i][j])*sin(-rad);
			Y_2[i][j] = (X_1[i][j])*sin(-rad) + (Y_1[i][j])*cos(-rad);
			if(X_2[i][j]<width && Y_2[i][j]<height && X_2[i][j]>=0 && Y_2[i][j]>=0)
			{
				noholeimage->SetPixel(X_1[i][j]-Xmin,Y_1[i][j]-Ymin,RGB(R[Y_2[i][j]][X_2[i][j]],G[Y_2[i][j]][X_2[i][j]],B[Y_2[i][j]][X_2[i][j]]));
			}
		}
	}noholeimage->Draw(&dc,CPoint(638,0));*/
}
