// THRESHOLDING.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "THRESHOLDING.h"


// THRESHOLDING dialog

IMPLEMENT_DYNAMIC(THRESHOLDING, CDialog)

THRESHOLDING::THRESHOLDING(CWnd* pParent /*=NULL*/)
	: CDialog(THRESHOLDING::IDD, pParent)
	, thresh(0)
	, otsu(0)
	, m_snr(0)
{
	GRAY=NULL;
	image=NULL;
	image2=NULL;
	image3=NULL;
	height=0;
	width=0;
}

THRESHOLDING::~THRESHOLDING()
{
	int i;
	if(GRAY)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
	if(image) delete image;
	if(image2) delete image2;
	if(image3) delete image3;
}

void THRESHOLDING::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, threshlim);
	DDX_Text(pDX, IDC_EDIT1, thresh);
	DDV_MinMaxInt(pDX, thresh, 0, 255);
	DDX_Text(pDX, IDC_EDIT2, otsu);
	DDX_Text(pDX, IDC_EDIT3, m_snr);
}


BEGIN_MESSAGE_MAP(THRESHOLDING, CDialog)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT1, &THRESHOLDING::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTONot, &THRESHOLDING::OnBnClickedButtonot)
END_MESSAGE_MAP()

BOOL THRESHOLDING::OnInitDialog()
{
	CDialog::OnInitDialog();
	threshlim.SetScrollRange(0,255);
	return(TRUE);
}

// THRESHOLDING message handlers
void THRESHOLDING::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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

void THRESHOLDING::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void THRESHOLDING::OnBnClickedButtonot()
{

	UpdateData();	
    double u1_percent,u2_percent=0;
	double u1,u2,mean=0;
    
	for(int i=0;i<256;i++) 
	{
		hist[i]=0;
		vw[i]=0;
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(GRAY[i][j] == k)
				{
					hist[k]++;
				}
			}
		}
	}

	for(int i=0;i<256;i++) 
	{
		hist[i]=hist[i]/(height*width);
		mean+=hist[i]*i;
	}

	for(int t=0;t<256;t++)
	{
		u1=0; u2=0;
		u1_percent=0; u2_percent=0;
		for(int i=0;i<256;i++) 
	    {
			if(i<=t) 
			{
				u1+=hist[i]*i;
				u1_percent+=hist[i];
			}

			if(i>t) 
			{
				u2+=hist[i]*i;
				u2_percent+=hist[i];
			}
		}
		if(u1!=0) u1=u1/u1_percent;
	    if(u2!=0) u2=u2/u2_percent;
		vw[t]=u1_percent*(u1-mean)*(u1-mean)+u2_percent*(u2-mean)*(u2-mean);
	}

	//int Decision_Threshold;
    double t;
	for(int i=0;i<256;i++) 
	{
		if(i==0) 
		{
			t=vw[i];
            otsu=0;
		}
		if(vw[i]>t) 
		{
			t=vw[i];
			otsu=i;
		}
	}

	/*double vaw_min=10000000000000000000;
	for(int t=0;t<255;t++)
	{
		c1[t] = 0;
		for(int i=0;i<=t;i++)
		{
			c1[t] = c1[t] + hist[i];
		}
		c2[t] = 0;
		for(int i=t+1;i<256;i++)
		{
			c2[t] = c2[t] + hist[i];
		}

		q1[t]=c1[t]/65536;
		q2[t]=c2[t]/65536;


		m1[t] = 0;
		for(int i=0;i<=t;i++)
		{
			m1[t] = m1[t] +
				static_cast<double>(i)*hist[i]/
				(65536*q1[t]);
		}

		m2[t] = 0;
		for(int i=t+1;i<256;i++)
		{
			m2[t] = m2[t] +
				static_cast<double>(i)*hist[i]/
				(65536*q2[t]);
		}

		v1[t]=0;
		for(int i=0;i<=t;i++)
		{
			v1[t] = v1[t]+ 
				(static_cast<double>(i)-m1[t])*(i-m1[t])*hist[i]/
				(65536*q1[t]);
		}

		v2[t]=0;
		for(int i=t+1;i<256;i++)
		{
			v2[t] = v2[t]+ 
				(static_cast<double>(i)-m2[t])*(i-m2[t])*hist[i]/
				(65536*q2[t]);
		}

		vw[t]=v1[t]+v2[t];
		if(vw[t]<=vaw_min)
		{
			vaw_min=vw[t];
			otsu=t;
		}
	}*/
	UpdateData(FALSE);
	//計算SNR
	float single=0,noise=0;
	float SNR;
	CClientDC dc(this);
	image3 = new CDIBSectionLite();
	image3->CreateEmptyDIB(width,height,24);
	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{				
			int g = GRAY[i][j];
			if(g<otsu) {g=0;}
			if(g>otsu) {g=255;}
			image3->SetPixel(j,i,RGB(g,g,g));
			single += GRAY[i][j] * GRAY[i][j];
			noise += (g-GRAY[i][j]) * (g-GRAY[i][j]);
		}
	}image3->Draw(&dc,CPoint(276,286));

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void THRESHOLDING::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
		UINT hScrollPos = pScrollBar->GetScrollPos();
		switch(nSBCode)
		{
		case SB_THUMBTRACK:
			hScrollPos =nPos;
			break;
		case SB_PAGEDOWN: //向下跳頁捲動
			//判斷目前的位置是否還足夠向下捲動5個刻度
			if(hScrollPos <= (UINT)(255 - 10))
				hScrollPos += 10;//向下捲動5個刻度
			break;
		case SB_PAGEUP:	//向上跳頁捲動
			//判斷目前的位置是否還足夠向上捲動5個刻度
			if(hScrollPos >= (UINT)(0 + 10))
				hScrollPos -= 10;//向上捲動5個刻度
			break;
		case SB_LINEDOWN: //拉動捲軸按鈕向下拉動
			//判斷目前的位置是否還可以向下拉動
			if( hScrollPos < (UINT) 255 )
				++hScrollPos;	//向下移動1個刻度
			break;
		case SB_LINEUP:	//拉動捲軸按鈕向上拉動
			//判斷目前的位置是否還可以向上拉動
			if( hScrollPos > (UINT)0 )
				--hScrollPos; //向上移動1個刻度
			break;
		}
		pScrollBar->SetScrollPos(hScrollPos); //設定捲軸拇指盒的位置
		thresh = (int)hScrollPos;
		//計算SNR
		float single=0,noise=0;
		float SNR;
		CClientDC dc(this); // device context for painting
		image2 = new CDIBSectionLite();
		image2->CreateEmptyDIB(width,height,24);
		for(int i=0;i<width;i++) 
		{
			for(int j=0;j<height;j++)
			{
				int g = GRAY[i][j];
				if(g<thresh) {g=0;}
				if(g>thresh) {g=255;}
				image2->SetPixel(j,i,RGB(g,g,g));
				single += GRAY[i][j] * GRAY[i][j];
				noise += (g-GRAY[i][j]) * (g-GRAY[i][j]);
			}
		}image2->Draw(&dc,CPoint(276,10));	

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();

	UpdateData(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void THRESHOLDING::OnEnChangeEdit1()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。
	CClientDC dc(this);
	UpdateData();
	threshlim.SetScrollPos(thresh);
	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{				
			int g = GRAY[i][j];
			if(g<thresh) {g=0;}
			if(g>thresh) {g=255;}
			image2->SetPixel(j,i,RGB(g,g,g));
		}
	}image2->Draw(&dc,CPoint(276,10));
}