// HISTOGRAM.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "HISTOGRAM.h"


// HISTOGRAM dialog

IMPLEMENT_DYNAMIC(HISTOGRAM, CDialog)

HISTOGRAM::HISTOGRAM(CWnd* pParent /*=NULL*/)
	: CDialog(HISTOGRAM::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	GRAY=NULL;
	height=0;
	width=0;
	rmax=0;
	gmax=0;
	bmax=0;
	grmax=0;
}

HISTOGRAM::~HISTOGRAM()
{
	if(R)															//釋放R的記憶體空間
	{
		for(int i=0;i<height;i++) delete [] R[i]; delete [] R;
	}
	if(G)															//釋放G的記憶體空間
	{
		for(int i=0;i<height;i++) delete [] G[i]; delete [] G;
	}
	if(B)															////釋放B的記憶體空間
	{
		for(int i=0;i<height;i++) delete [] B[i]; delete [] B;
	}
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
}

void HISTOGRAM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HISTOGRAM, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HISTOGRAM message handlers
void HISTOGRAM::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}

	//開啟記憶體紀錄R、G、B
	R=new int * [height]; 
    for(i=0;i<height;i++) R[i]=new int [width];

    G=new int * [height]; 
    for(i=0;i<height;i++) G[i]=new int [width];

    B=new int * [height]; 
    for(i=0;i<height;i++) B[i]=new int [width];

    GRAY=new int * [height]; 
    for(i=0;i<height;i++) GRAY[i]=new int [width];

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			R[i][j]=Input_R[i][j];
			G[i][j]=Input_G[i][j];
			B[i][j]=Input_B[i][j];
		}
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			GRAY[i][j]=(Input_R[i][j]+Input_G[i][j]+Input_B[i][j])/3;
		}
	}
}
void HISTOGRAM::OnPaint()
{
	for(int i =0;i<256;i++)
	{
		rcount[i]=0;
		gcount[i]=0;
		bcount[i]=0;
		grcount[i]=0;
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(R[i][j] == k)
				{
					rcount[k]++;
				}
				if(G[i][j] == k)
				{
					gcount[k]++;
				}
				if(B[i][j] == k)
				{
					bcount[k]++;
				}
				if(GRAY[i][j] == k)
				{
					grcount[k]++;
				}
			}
		}
	}

	
	for(int i=0;i<256;i++)
	{
		if(rcount[i] > rmax)
			rmax = rcount[i];
		if(gcount[i] > gmax)
			gmax = gcount[i];
		if(bcount[i] > bmax)
			bmax = bcount[i];
		if(grcount[i] > grmax)
			grmax = grcount[i];
	}

	CPaintDC dc(this);

	CPen penR(PS_SOLID,2,RGB(0,0,0));						//RED
	CPen *oldPenR = dc.SelectObject(&penR);
	dc.MoveTo(10,10);    
	dc.LineTo(10,height+10);
	dc.LineTo(width+10,height+10);
	dc.SelectObject(oldPenR);

	CString str;
	str.Format("0");    dc.TextOutA(10,height+20,str);
	str.Format("255");  dc.TextOutA(width+10,height+20,str);
	str.Format("Histogram of RED");   dc.TextOutA(width/4,height+20,str);

	for(int i=0;i<256;i++) 
	{	
		CPen pen(PS_SOLID,1,RGB(255,0,0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.MoveTo(i+10,height+10);
		dc.LineTo(i+10,(height+10)-(255*rcount[i]/rmax));
	}


	CPen penG(PS_SOLID,2,RGB(0,0,0));						//GREEN
	CPen *oldPenG = dc.SelectObject(&penG);
	dc.MoveTo(10+width+80,10);    
	dc.LineTo(10+width+80,height+10);
	dc.LineTo(10+width+80+width,height+10);
	dc.SelectObject(oldPenG);

	str.Format("0");    dc.TextOutA(10+width+80,height+20,str);
	str.Format("255");  dc.TextOutA(10+width+80+width,height+20,str);
	str.Format("Histogram of GREEN");   dc.TextOutA((width/4)+10+width+80,height+20,str);

	for(int i=0;i<256;i++) 
	{	
		CPen pen(PS_SOLID,1,RGB(0,255,0));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.MoveTo(i+10+width+80,height+10);
		dc.LineTo(i+10+width+80,(height+10)-(255*gcount[i]/gmax));
	}


	CPen penB(PS_SOLID,2,RGB(0,0,0));						//BLUE
	CPen *oldPenB = dc.SelectObject(&penB);
	dc.MoveTo(10,10+height+80);    
	dc.LineTo(10,height+10+height+80);
	dc.LineTo(width+10,height+10+height+80);
	dc.SelectObject(oldPenB);

	str.Format("0");    dc.TextOutA(10,height+20+80+height,str);
	str.Format("255");  dc.TextOutA(width+10,height+20+80+height,str);
	str.Format("Histogram of BLUE");   dc.TextOutA(width/4,height+20+height+80,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen(PS_SOLID,1,RGB(0,0,255));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.MoveTo(i+10,height+10+height+80);
		dc.LineTo(i+10,(height+10+height+80)-(255*bcount[i]/bmax));
	}


	CPen penGR(PS_SOLID,2,RGB(0,0,0));						//GRAY
	CPen *oldPenGR = dc.SelectObject(&penGR);
	dc.MoveTo(10+width+80,10+height+80);    
	dc.LineTo(10+width+80,height+10+height+80);
	dc.LineTo(10+width+80+width,height+10+height+80);
	dc.SelectObject(oldPenGR);

	str.Format("0");    dc.TextOutA(10+width+80,height+20+80+height,str);
	str.Format("255");  dc.TextOutA(10+width+80+width,height+20+80+height,str);
	str.Format("Histogram of GRAY");   dc.TextOutA((width/4)+10+width+80,height+20+height+80,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen(PS_SOLID,1,RGB(128,128,128));
		CPen *oldPen = dc.SelectObject(&pen);
		dc.MoveTo(i+10+width+80,height+10+height+80);
		dc.LineTo(i+10+width+80,(height+10+height+80)-(255*grcount[i]/grmax));
	}
}
