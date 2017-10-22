// DCT.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "DCT.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "string.h" 
#include <fstream>
#include <cstring>
using namespace std;


// DCT dialog

IMPLEMENT_DYNAMIC(DCT, CDialog)

DCT::DCT(CWnd* pParent /*=NULL*/)
	: CDialog(DCT::IDD, pParent)
	, m_snr(0)
{
	nGRAY=NULL;
	GRAY=NULL;
	c=NULL;
	image=NULL;
	image2=NULL;
	height=0;
	width=0;
}

DCT::~DCT()
{
	int i;
	if(GRAY)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(c)															
	{
		for(i=0;i<height;i++) delete [] c[i]; delete [] c;
	}
	if(nGRAY)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
	if(image) delete image;
	if(image2) delete image2;
}

void DCT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
}


BEGIN_MESSAGE_MAP(DCT, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONDCT, &DCT::OnBnClickedButtondct)
	ON_BN_CLICKED(IDC_BUTTONIDCT, &DCT::OnBnClickedButtonidct)
	ON_BN_CLICKED(IDC_BUTTONRDC, &DCT::OnBnClickedButtonrdc)
	ON_BN_CLICKED(IDC_BUTTONADC, &DCT::OnBnClickedButtonadc)
END_MESSAGE_MAP()


// DCT message handlers
void DCT::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}

	//開啟記憶體紀錄R、G、B

    GRAY=new double * [height]; 
    for(i=0;i<height;i++) GRAY[i]=new double [width];

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
void DCT::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void DCT::OnBnClickedButtondct()
{
	if(c)
	{
		for(int i=0;i<height;i++) delete [] c[i]; delete [] c;
	}
    c=new double * [height]; 
    for(int i=0;i<height;i++) c[i]=new double [width];

	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
    nGRAY=new double * [height]; 
    for(int i=0;i<height;i++) nGRAY[i]=new double [width];

	float pi=3.14159265424;
	float temp,a[8];

	for(int i=1;i<8;i++)
	{ a[0] = 0.3535533906; a[i] = 0.5;}

	for(int u=0;u<height;u++)
	{
		int us = static_cast<int>((u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = static_cast<int>((v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += (GRAY[us+x][vs+y]-128) * cos((2*y+1)*ve*pi/16)  * cos((2*x+1)*ue*pi/16);
					}
				}
			temp = temp*a[ue]*a[ve];
			c[u][v] = static_cast<int>(temp);
		}
	}

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			if(c[i][j] > 255) { c[i][j] = 255; }
			if(c[i][j] < 0) { c[i][j] = 0; }
			image2->SetPixel(j,i,RGB(c[i][j],c[i][j],c[i][j]));
		}		
	}image2->Draw(&dc,CPoint(276,10));


	/*for(int i=0;i<height;i++)
	{
		int ii = i%8;
		for(int j=0;j<width;j++)
		{
			int jj = j%8;
			temp = 0.0;
			for(int x=0;x<8;x++)
			{
				for(int y=0;y<8;y++)
				{
					temp += (GRAY[i][j]-128) * cos( ((2*x+1)*ii*pi)/16 ) * cos( ((2*y+1)*jj*pi)/16) ;
				}
			}
			temp = temp*a[ii]*a[jj];
			c[i][j] = temp;
		}
	}
	for(int i=0;i<256;i++)
	{
		int ii = i%8;
		for(int j=0;j<256;j++)
		{
			int jj = j%8;
			temp = 0.0;
			for(int x=0;x<8;x++)
			{
				for(int y=0;y<8;y++)
				{
					temp += a[x]*a[y]* c[x][y] * cos( ((2*x+1)*ii*pi)/16 ) * cos( ((2*y+1)*jj*pi)/16) ;
				}
			}
			temp = temp + 128;
			nGRAY[i][j] = temp;
		}
	}*/
	
	fstream file1;
	file1.open("After DCT.txt",ios::out|ios::trunc);
	for(int u=0;u<40;u++)
	{
		for(int v=0;v<40;v++)
		{
			file1<<setw(6)<<setiosflags(ios::left)<<c[u][v]<<"  ";
			if(v == 39)
				file1<<endl;
		}
	}file1.close();
	MessageBox("DCT編碼完成!!","Message",MB_OK|MB_ICONEXCLAMATION);
}

void DCT::OnBnClickedButtonidct()
{
	double C[8][8];
	double Ct[8][8];
	double pi=3.14159265424;
	double temp[8][8],temp1;

	for(int j=0;j<8;j++)
	{
		C[0][j] = 1.0/sqrt((double)8);
		Ct[j][0] = C[0][j];
	}

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			C[i][j] = sqrt(2.0/8)*cos(pi*(2*j+1)*i/(2.0*8));
			Ct[j][i] = C[i][j];
		}
	}
	for(int i=0;i<8;i++)
	{
		int jj = 0;
		for( jj = 0 ; jj < 8 ; jj++ )
		temp[i][jj] = 0.0;
		{
			for(int k=0;k<8;k++)
			{
				temp[i][jj] += ((int)GRAY[i][k]-128)*Ct[k][jj];
			}
		}
	}
	for(int i=0;i<8;i++)
	{
		int j = 0;
		for(j=0;j<8;j++)
		temp1=0.0;
		{
			for(int k=0;k<8;k++)
			{
				temp1 += C[i][k]*temp[k][j];
				nGRAY[i][j] = temp1;
			}
		}
	}


/*	if(c)
	{
		for(int i=0;i<height;i++) delete [] c[i]; delete [] c;
	}
    c=new double * [height]; 
    for(int i=0;i<height;i++) c[i]=new double [width];

	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
    nGRAY=new double * [height]; 
    for(int i=0;i<height;i++) nGRAY[i]=new double [width];

	float pi=3.14159265424;
	float temp,a[8];
	double Cos[256][8];

	for(int i=1;i<8;i++)
	{ a[0] = 0.3535533906; a[i] = 0.5;}

	for(int u=0;u<height;u++)
	{
		int us = static_cast<int>((u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = static_cast<int>((v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += (GRAY[us+x][vs+y]-128) * cos((2*y+1)*ve*pi/16)  * cos((2*x+1)*ue*pi/16);
					}
				}
			temp = temp*a[ue]*a[ve];
			c[u][v] = temp;
		}
	}
	for(int u=0;u<height;u++)
	{
		int us = (static_cast<int>(u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = (static_cast<int>(v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += a[y]*a[x]*c[us+x][vs+y] * cos((2*ve)*y*pi/16)  * cos((2*ue)*x*pi/16);
					}
				}
			temp = temp + 128;
			nGRAY[u][v] = static_cast<int>(temp);
		}
	}*/

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			if(nGRAY[i][j] > 255) { nGRAY[i][j] = 255; }
			if(nGRAY[i][j] < 0) { nGRAY[i][j] = 0; }
			image2->SetPixel(j,i,RGB(nGRAY[i][j],nGRAY[i][j],nGRAY[i][j]));
		}		
	}image2->Draw(&dc,CPoint(276,10));

	fstream file1;
	fstream file2;
	file1.open("After IDCT.txt",ios::out|ios::trunc);
	file2.open("Original intensity.txt",ios::out|ios::trunc);
	for(int u=0;u<40;u++)
	{
		for(int v=0;v<40;v++)
		{
			file1<<setw(6)<<setiosflags(ios::left)<<nGRAY[u][v]<<"  ";
			if(v == 39)
				file1<<endl;
			file2<<setw(6)<<setiosflags(ios::left)<<GRAY[u][v]<<"  ";
			if(v == 39)
				file1<<endl;
		}
	}file1.close();
	MessageBox("IDCT完成!!","Message",MB_OK|MB_ICONEXCLAMATION);

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

void DCT::OnBnClickedButtonrdc()
{
	if(c)
	{
		for(int i=0;i<height;i++) delete [] c[i]; delete [] c;
	}
    c=new double * [height]; 
    for(int i=0;i<height;i++) c[i]=new double [width];


	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
    nGRAY=new double * [height]; 
    for(int i=0;i<height;i++) nGRAY[i]=new double [width];

	float pi=3.14159265424;
	float temp,a[8];

	for(int i=1;i<8;i++)
	{ a[0] = 0.3535533906; a[i] = 0.5;}

	for(int u=0;u<height;u++)
	{
		int us = static_cast<int>((u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = static_cast<int>((v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += (GRAY[us+x][vs+y]-128) * cos((2*y+1)*ve*pi/16)  * cos((2*x+1)*ue*pi/16);
					}
				}
			temp = temp*a[ue]*a[ve];
			c[u][v] = static_cast<int>(temp);
		}
	}
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i%8 == 0 && j%8 == 0)
			{ c[i][j] = 0; }
		}
	}

	fstream file1;
	file1.open("Remove DC.txt",ios::out|ios::trunc);
	for(int u=0;u<40;u++)
	{
		for(int v=0;v<40;v++)
		{
			file1<<setw(6)<<setiosflags(ios::left)<<c[u][v]<<"  ";
			if(v == 39)
				file1<<endl;
		}
	}file1.close();

	for(int u=0;u<height;u++)
	{
		int us = (static_cast<int>(u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = (static_cast<int>(v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += a[y]*a[x]*c[us+x][vs+y] * cos((2*ve)*y*pi/16)  * cos((2*ue)*x*pi/16);
					}
				}
			temp = temp + 128;
			nGRAY[u][v] = static_cast<int>(temp);
		}
	}

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			if(nGRAY[i][j] > 255) { nGRAY[i][j] = 255; }
			if(nGRAY[i][j] < 0) { nGRAY[i][j] = 0; }
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
}

void DCT::OnBnClickedButtonadc()
{
	if(c)
	{
		for(int i=0;i<height;i++) delete [] c[i]; delete [] c;
	}
    c=new double * [height]; 
    for(int i=0;i<height;i++) c[i]=new double [width];


	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
    nGRAY=new double * [height]; 
    for(int i=0;i<height;i++) nGRAY[i]=new double [width];

	float pi=3.14159265424;
	float temp,a[8];

	for(int i=1;i<8;i++)
	{ a[0] = 0.3535533906; a[i] = 0.5;}

	for(int u=0;u<height;u++)
	{
		int us = static_cast<int>((u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = static_cast<int>((v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += (GRAY[us+x][vs+y]-128) * cos((2*y+1)*ve*pi/16)  * cos((2*x+1)*ue*pi/16);
					}
				}
			temp = temp*a[ue]*a[ve];
			c[u][v] = static_cast<int>(temp);
		}
	}
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i%8 == 0 && j%8 == 0)
			{ c[i][j] = c[i][j]; }
			else
			{ c[i][j] = 0; }
		}
	}

	fstream file2;
	file2.open("Retain DC.txt",ios::out|ios::trunc);
	for(int u=0;u<40;u++)
	{
		for(int v=0;v<40;v++)
		{
			file2<<setw(6)<<setiosflags(ios::left)<<c[u][v]<<"  ";
			if(v == 39)
				file2<<endl;
		}
	}file2.close();

	for(int u=0;u<height;u++)
	{
		int us = (static_cast<int>(u/8)*8);
		int ue = static_cast<int>( u%8 );
		for(int v=0;v<width;v++)
		{
			int vs = (static_cast<int>(v/8)*8);
			int ve = static_cast<int>( v%8 );
			temp = 0.0;
			for(int x=0;x<8;x++)
				{
					for(int y=0;y<8;y++)
					{
						temp += a[y]*a[x]*c[us+x][vs+y] * cos((2*ve)*y*pi/16)  * cos((2*ue)*x*pi/16);
					}
				}
			temp = temp + 128;
			nGRAY[u][v] = static_cast<int>(temp);
		}
	}

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			if(nGRAY[i][j] > 255) { nGRAY[i][j] = 255; }
			if(nGRAY[i][j] < 0) { nGRAY[i][j] = 0; }
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
}
