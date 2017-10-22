// HISTOGRAMEQUALIZATION.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "HISTOGRAMEQUALIZATION.h"


// HISTOGRAMEQUALIZATION dialog

IMPLEMENT_DYNAMIC(HISTOGRAMEQUALIZATION, CDialog)

HISTOGRAMEQUALIZATION::HISTOGRAMEQUALIZATION(CWnd* pParent /*=NULL*/)
	: CDialog(HISTOGRAMEQUALIZATION::IDD, pParent)
	, m_snr(0)
{
	GRAY=NULL;
	nGRAY=NULL;
	height=0;
	width=0;
	max=0;
	max1=0;
	image=NULL;
	image2=NULL;
}

HISTOGRAMEQUALIZATION::~HISTOGRAMEQUALIZATION()
{
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}
	if(image) delete image;
	if(image2) delete image2;
}

void HISTOGRAMEQUALIZATION::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
}


BEGIN_MESSAGE_MAP(HISTOGRAMEQUALIZATION, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// HISTOGRAMEQUALIZATION message handlers
void HISTOGRAMEQUALIZATION::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(GRAY)
	{
		for(int i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(nGRAY)
	{
		for(int i=0;i<height;i++) delete [] nGRAY[i]; delete [] nGRAY;
	}

	//開啟記憶體紀錄R、G、B
    GRAY=new int * [height]; 
    for(i=0;i<height;i++) GRAY[i]=new int [width];
    nGRAY=new int * [height]; 
    for(i=0;i<height;i++) nGRAY[i]=new int [width];

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
void HISTOGRAMEQUALIZATION::OnPaint()
{
	for(int i =0;i<256;i++)
	{
		count[i]=0;
		PDF[i]=0;
		CDF[i]=0;
		count1[i]=0;
		PDF1[i]=0;
		CDF1[i]=0;
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(GRAY[i][j] == k)
				{
					count[k]++;
				}
			}
		}
	}
	for(int i=1;i<256;i++)
	{
		PDF[0] = count[0];
		PDF[i] = PDF[i-1] + count[i];
	}
	for(int i=0;i<256;i++)
	{ CDF[i] = ( PDF[i]*(256-1)/(height*width) ); }
	
	for(int i=0;i<256;i++)
	{
		if(count[i] > max)
			max = count[i];
	}

	CPaintDC dc(this);
	CString str;
	image->Draw(&dc,CPoint(10,10));

	CPen pen1(PS_SOLID,2,RGB(0,0,0));						//GRAY
	CPen *oldPen1 = dc.SelectObject(&pen1);
	dc.MoveTo(10+width+40,10);    
	dc.LineTo(10+width+40,height+10);
	dc.LineTo(10+width+40+width,height+10);
	dc.SelectObject(oldPen1);

	str.Format("0");    dc.TextOutA(10+width+40,height+20,str);
	str.Format("255");  dc.TextOutA(10+width+40+width,height+20,str);
	str.Format("Histogram by original image");   dc.TextOutA((width/4)+10+width+40,height+20,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen1(PS_SOLID,1,RGB(128,128,128));
		CPen *oldPen1 = dc.SelectObject(&pen1);
		dc.MoveTo(i+10+width+40,height+10);
		dc.LineTo(i+10+width+40,(height+10)-(255*count[i]/max));
	}

	CPen pen1c(PS_SOLID,2,RGB(0,0,0));						//GRAY CDF
	CPen *oldPen1c = dc.SelectObject(&pen1c);
	dc.MoveTo(100+width+280,10);    
	dc.LineTo(100+width+280,height+10);
	dc.LineTo(100+width+280+width,height+10);
	dc.SelectObject(oldPen1c);

	str.Format("0");    dc.TextOutA(100+width+280,height+20,str);
	str.Format("255");  dc.TextOutA(100+width+280+width,height+20,str);
	str.Format("CDF by original image");   dc.TextOutA((width/4)+100+width+280,height+20,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen1c(PS_SOLID,1,RGB(0,0,0));
		CPen *oldPen1c = dc.SelectObject(&pen1c);
		dc.MoveTo(i+100+width+280,height+10);
		dc.LineTo(i+100+width+280,(height+10)-(CDF[i]));
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(GRAY[i][j] == k)
				{
					nGRAY[i][j] = CDF[k];
				}
			}
		}
	}

	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
			image2->SetPixel(j,i,RGB(nGRAY[i][j],nGRAY[i][j],nGRAY[i][j]));
		}		
	}image2->Draw(&dc,CPoint(10,340));

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(nGRAY[i][j] == k)
				{
					count1[k]++;
				}
			}
		}
	}
	for(int i=1;i<256;i++)
	{
		PDF1[0] = count1[0];
		PDF1[i] = PDF1[i-1] + count1[i];
	}
	for(int i=0;i<256;i++)
	{ CDF1[i] = ( PDF1[i]*(256-1)/(height*width) ); }
	
	for(int i=0;i<256;i++)
	{
		if(count1[i] > max1)
			max1 = count1[i];
	}

	CPen pen2(PS_SOLID,2,RGB(0,0,0));						//nGRAY
	CPen *oldPen2 = dc.SelectObject(&pen2);
	dc.MoveTo(10+width+40,10+330);    
	dc.LineTo(10+width+40,height+10+330);
	dc.LineTo(10+width+40+width,height+10+330);
	dc.SelectObject(oldPen2);

	str.Format("0");    dc.TextOutA(10+width+40,height+20+330,str);
	str.Format("255");  dc.TextOutA(10+width+40+width,height+20+330,str);
	str.Format("Histogram after equalization");   dc.TextOutA((width/4)+10+width+40,height+20+330,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen2(PS_SOLID,1,RGB(128,128,128));
		CPen *oldPen2 = dc.SelectObject(&pen2);
		dc.MoveTo(i+10+width+40,height+10+330);
		dc.LineTo(i+10+width+40,(height+10+330)-(255*count1[i]/max));
	}

	CPen pen2c(PS_SOLID,2,RGB(0,0,0));						//n GRAY CDF
	CPen *oldPen2c = dc.SelectObject(&pen1c);
	dc.MoveTo(100+width+280,10+330);    
	dc.LineTo(100+width+280,height+10+330);
	dc.LineTo(100+width+280+width,height+10+330);
	dc.SelectObject(oldPen2c);

	str.Format("0");    dc.TextOutA(100+width+280,height+20+330,str);
	str.Format("255");  dc.TextOutA(100+width+280+width,height+20+330,str);
	str.Format("CDF after equalization");   dc.TextOutA((width/4)+100+width+280,height+20+330,str);

	for(int i=0;i<256;i++) 
	{
		CPen pen2c(PS_SOLID,1,RGB(0,0,0));
		CPen *oldPen2c = dc.SelectObject(&pen1c);
		dc.MoveTo(i+100+width+280,height+10+330);
		dc.LineTo(i+100+width+280,(height+10+330)-(CDF1[i]));
	}

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
