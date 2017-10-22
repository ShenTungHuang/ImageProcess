// OUTLIER.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "OUTLIER.h"


// OUTLIER dialog

IMPLEMENT_DYNAMIC(OUTLIER, CDialog)

OUTLIER::OUTLIER(CWnd* pParent /*=NULL*/)
	: CDialog(OUTLIER::IDD, pParent)
	, e(0)
	, m_snr(0)
{
	image=NULL;
	outimage=NULL;
	GRAY=NULL;
	height=0;
	width=0;
	a=NULL;
}

OUTLIER::~OUTLIER()
{
	int i;
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}
	if(a)
	{ delete a; }

	if(image) delete image;
	if(outimage) delete outimage;
}

void OUTLIER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, e);
	DDX_Text(pDX, IDC_EDIT2, m_snr);
}


BEGIN_MESSAGE_MAP(OUTLIER, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONshow, &OUTLIER::OnBnClickedButtonshow)
	ON_BN_CLICKED(IDC_BUTTONsquare, &OUTLIER::OnBnClickedButtonsquare)
	ON_BN_CLICKED(IDC_BUTTONcross, &OUTLIER::OnBnClickedButtoncross)
END_MESSAGE_MAP()


// OUTLIER message handlers
void OUTLIER::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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

void OUTLIER::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void OUTLIER::OnBnClickedButtonshow()
{
	float single=0,noise=0,noise1=0,noise2=0;
	float SNR;
	int average;
	UpdateData();
	CClientDC dc(this);
	outimage = new CDIBSectionLite();
	outimage->CreateEmptyDIB(width,height,24);
	for(int i=0;i<height;i++)
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

			average = int(GRAY[a][c] + GRAY[i][c] + GRAY[b][c] + GRAY[a][j] +
				          GRAY[b][j] + GRAY[a][d] + GRAY[i][d] + GRAY[b][d])/8;
			if(average<0) {average=0;}
			if(average>255) {average=255;}

			if( (GRAY[i][j]-average) > e )
			{
				outimage->SetPixel(j,i,RGB(average,average,average));
				noise1 += (average-GRAY[i][j]) * (average-GRAY[i][j]);
			}
			else
			{
				outimage->SetPixel(j,i,RGB(GRAY[i][j],GRAY[i][j],GRAY[i][j]));
				noise2 += (GRAY[i][j]-GRAY[i][j]) * (GRAY[i][j]-GRAY[i][j]);
			}
			single += GRAY[i][j] * GRAY[i][j];
			noise = noise1+noise2;
		}
	}outimage->Draw(&dc,CPoint(276,10));
	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
	
	
	/*for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i == 0 && j == 0)											//(0,0)
			{
				average = int(GRAY[1][1]+GRAY[1][0]+GRAY[0][1]+GRAY[height-1][0]+
					           GRAY[height-1][1]+GRAY[0][width-1]+GRAY[1][width-1]+GRAY[height-1][width-1])/8;

				if( (GRAY[i][j]-average) > e )
				{ outimage->SetPixel(i,j,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(i,j,RGB(GRAY[i][j],GRAY[i][j],GRAY[i][j])); }
			}
			else if(i == height-1 && j ==0)									//(height,0)
			{
				average = int(GRAY[height-2][0]+GRAY[height-2][1]+GRAY[height-1][1]+GRAY[0][0]+
					           GRAY[0][1]+GRAY[height-1][width-1]+GRAY[height-2][width-1]+GRAY[0][width-1])/8;

				if( (GRAY[height-1][0]-average) > e )
				{ outimage->SetPixel(height-1,0,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(height-1,0,RGB(GRAY[height-1][0],GRAY[height-1][0],GRAY[height-1][0])); }

			}
			else if(i == 0 && j == width-1)									//(0,width)
			{
				average = int(GRAY[0][width-2]+GRAY[1][width-2]+GRAY[1][width-1]+GRAY[0][0]+
					           GRAY[1][0]+GRAY[height-1][width-1]+GRAY[height-1][width-2]+GRAY[height-1][0])/8;

				if( (GRAY[0][width-1]-average) > e )
				{ outimage->SetPixel(0,width-1,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(0,width-1,RGB(GRAY[0][width-1],GRAY[0][width-1],GRAY[0][width-1])); }
			}
			else if(i == height-1 && j == width-1)								//(height,width)
			{
				average = int(GRAY[height-2][width-1]+GRAY[height-2][width-2]+GRAY[height-1][width-2]+GRAY[0][0]+
					           GRAY[height-1][0]+GRAY[height-2][0]+GRAY[0][width-2]+GRAY[0][width-1])/8;

				if( (GRAY[height-1][width-1]-average) > e )
				{ outimage->SetPixel(height-1,width-1,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(height-1,width-1,RGB(GRAY[height-1][width-1],GRAY[height-1][width-1],GRAY[height-1][width-1])); }
			}
			else if( (i > 0 && i < height-1) && j == 0 )					//up pixel
			{
				average = int(GRAY[i-1][0]+GRAY[i-1][1]+GRAY[i][1]+GRAY[i+1][1]+
					           GRAY[i+1][0]+GRAY[i-1][width-1]+GRAY[i][width-1]+GRAY[i+1][width-1])/8;

				if( (GRAY[i][0]-average) > e )
				{ outimage->SetPixel(j,0,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(j,0,RGB(GRAY[i][0],GRAY[i][0],GRAY[i][0])); }
			}
			else if( (j > 0 && j < width-1) && i == 0 )						//left pixel
			{
				average = int(GRAY[0][j-1]+GRAY[1][j-1]+GRAY[1][j]+GRAY[1][j+1]+
					           GRAY[0][j+1]+GRAY[height-1][j]+GRAY[height-1][j-1]+GRAY[height-1][j+1])/8;

				if( (GRAY[0][j]-average) > e )
				{ outimage->SetPixel(j,0,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(j,0,RGB(GRAY[0][j],GRAY[0][j],GRAY[0][j])); }
			}
			else if( (i > 0 && i < height-1) && j == width-1 )					//down pixel
			{
				average = int(GRAY[i-1][width-1]+GRAY[i-1][width-2]+GRAY[i][width-2]+GRAY[i+1][width-2]+
					           GRAY[i+1][width-1]+GRAY[i][0]+GRAY[i-1][0]+GRAY[i+1][0])/8;

				if( (GRAY[i][width-1]-average) > e )
				{ outimage->SetPixel(width-1,i,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(width-1,i,RGB(GRAY[i][width-1],GRAY[i][width-1],GRAY[i][width-1])); }
			}
			else if( (j > 0 && j < width-1) && i == height-1 )					//right pixel
			{
				average = int(GRAY[height-1][j-1]+GRAY[height-2][j-1]+GRAY[height-2][j]+GRAY[height-2][j+1]+
					           GRAY[height-1][j+1]+GRAY[0][j-1]+GRAY[0][j]+GRAY[0][j+1])/8;

				if( (GRAY[height-1][j]-average) > e )
				{ outimage->SetPixel(j,height-1,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(j,height-1,RGB(GRAY[height-1][j],GRAY[height-1][j],GRAY[height-1][j])); }
			}
			else if(i > 0 && j > 0 && i < height-1 && j < width-1)
			{
				average = int(GRAY[i-1][j-1]+GRAY[i-1][j]+GRAY[i-1][j+1]+GRAY[i][j-1]+
					           GRAY[i][j+1]+GRAY[i+1][j-1]+GRAY[i+1][j]+GRAY[i+1][j+1])/8;

				if( (GRAY[i][j]-average) > e )
				{ outimage->SetPixel(j,i,RGB(average,average,average)); }
				else
				{ outimage->SetPixel(j,i,RGB(GRAY[i][j],GRAY[i][j],GRAY[i][j])); }
			}
		}
	}outimage->Draw(&dc,CPoint(276,10));*/
}

void OUTLIER::OnBnClickedButtonsquare()
{
	float single=0,noise=0;
	float SNR;
	int *a = new int [9];
	UpdateData();
	CClientDC dc(this);
	outimage = new CDIBSectionLite();
	outimage->CreateEmptyDIB(width,height,24);
	for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int f=i-1;
			int b=i+1;
			int c=j-1;
			int d=j+1;

			if(f==-1) {f=height-1;}
			if(b==height) {b=0;}
			if(c==-1) {c=width-1;}
			if(d==width) {d=0;}

			a[0] = GRAY[f][c];
			a[1] = GRAY[i][c];
			a[2] = GRAY[b][c];
			a[3] = GRAY[f][j];
			a[4] = GRAY[i][j];
			a[5] = GRAY[b][j];
			a[6] = GRAY[f][d];
			a[7] = GRAY[i][d];
			a[8] = GRAY[b][d];

			for (int k = 9; k > 0; --k)							//Bubbler
			{
				for (int l = 0; l < k; ++l)
				{
					if (a[l] > a[l+1]) 
					{   
						int t = a[l];
						a[l] = a[l+1];
						a[l+1] = t;		
					}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
				}
			}
			single += GRAY[i][j] * GRAY[i][j];
			noise += (a[4]-GRAY[i][j]) * (a[4]-GRAY[i][j]);
		}
	}outimage->Draw(&dc,CPoint(276,10));
	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
	/*for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i == 0 && j == 0)											//(0,0)
			{
				a[0] = GRAY[1][1];
				a[1] = GRAY[1][0];
				a[2] = GRAY[0][1];
				a[3] = GRAY[height-1][0];
				a[4] = GRAY[height-1][1];
				a[5] = GRAY[0][width-1];
				a[6] = GRAY[1][width-1];
				a[7] = GRAY[height-1][width-1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-1 && j ==0)									//(height,0)
			{
				a[0] = GRAY[height-2][0];
				a[1] = GRAY[height-2][1];
				a[2] = GRAY[height-1][1];
				a[3] = GRAY[0][0];
				a[4] = GRAY[0][1];
				a[5] = GRAY[height-1][width-1];
				a[6] = GRAY[height-2][width-1];
				a[7] = GRAY[0][width-1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}

			}
			else if(i == 0 && j == width-1)									//(0,width)
			{
				a[0] = GRAY[0][width-2];
				a[1] = GRAY[1][width-2];
				a[2] = GRAY[1][width-1];
				a[3] = GRAY[0][0];
				a[4] = GRAY[1][0];
				a[5] = GRAY[height-1][width-1];
				a[6] = GRAY[height-1][width-2];
				a[7] = GRAY[height-1][0];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-1 && j == width-1)								//(height,width)
			{
				a[0] = GRAY[height-2][width-1];
				a[1] = GRAY[height-2][width-2];
				a[2] = GRAY[height-1][width-2];
				a[3] = GRAY[0][0];
				a[4] = GRAY[height-1][0];
				a[5] = GRAY[height-2][0];
				a[6] = GRAY[0][width-2];
				a[7] = GRAY[0][width-1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if( (i > 0 && i < height-1) && j == 0 )					//up pixel
			{
				a[0] = GRAY[i-1][0];
				a[1] = GRAY[i-1][1];
				a[2] = GRAY[i][1];
				a[3] = GRAY[i+1][1];
				a[4] = GRAY[i+1][0];
				a[5] = GRAY[i-1][width-1];
				a[6] = GRAY[i][width-1];
				a[7] = GRAY[i+1][width-1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if( (j > 0 && j < width-1) && i == 0 )						//left pixel
			{
				a[0] = GRAY[0][j-1];
				a[1] = GRAY[1][j-1];
				a[2] = GRAY[1][j];
				a[3] = GRAY[1][j+1];
				a[4] = GRAY[0][j+1];
				a[5] = GRAY[height-1][j];
				a[6] = GRAY[height-1][j-1];
				a[7] = GRAY[height-1][j+1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if( (i > 0 && i < height-1) && j == width-1 )					//down pixel
			{
				a[0] = GRAY[i-1][width-1];
				a[1] = GRAY[i-1][width-2];
				a[2] = GRAY[i][width-2];
				a[3] = GRAY[i+1][width-2];
				a[4] = GRAY[i+1][width-1];
				a[5] = GRAY[i][0];
				a[6] = GRAY[i-1][0];
				a[7] = GRAY[i+1][0];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if( (j > 0 && j < width-1) && i == height-1 )					//right pixel
			{
				a[0] = GRAY[height-1][j-1];
				a[1] = GRAY[height-2][j-1];
				a[2] = GRAY[height-2][j];
				a[3] = GRAY[height-2][j+1];
				a[4] = GRAY[height-1][j+1];
				a[5] = GRAY[0][j-1];
				a[6] = GRAY[0][j];
				a[7] = GRAY[0][j+1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}


			}
			else if(i > 0 && j > 0 && i < height-1 && j < width-1)
			{
				a[0] = GRAY[i-1][j-1];
				a[1] = GRAY[i-1][j];
				a[2] = GRAY[i-1][j+1];
				a[3] = GRAY[i][j-1];
				a[4] = GRAY[i][j+1];
				a[5] = GRAY[i+1][j-1];
				a[6] = GRAY[i+1][j];
				a[7] = GRAY[i+1][j+1];
				a[8] = GRAY[i][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}							
		}
	}outimage->Draw(&dc,CPoint(276,10));*/
}

void OUTLIER::OnBnClickedButtoncross()
{
	float single=0,noise=0;
	float SNR;
	int *a = new int [9];
	UpdateData();
	CClientDC dc(this);
	outimage = new CDIBSectionLite();
	outimage->CreateEmptyDIB(width,height,24);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			int q=i-1;
			int r=i+1;
			int s=j-1;
			int t=j+1;
			int u=i-2;
			int v=i+2;
			int w=j-2;
			int x=j+2;

			if(q==-1) {q=height-1;}
			if(r==height) {r=0;}
			if(s==-1) {s=width-1;}
			if(t==width) {t=0;}
			if(u==-1) {u=height-1;}
			if(v==height) {v=0;}
			if(w==-1) {w=width-1;}
			if(x==width) {x=0;}
			if(u==-2) {u=height-2;}
			if(v==height+1) {v=1;}
			if(w==-2) {w=width-2;}
			if(x==width+12) {x=1;}

			a[0] = GRAY[i][w];
			a[1] = GRAY[i][s];
			a[2] = GRAY[i][t];
			a[3] = GRAY[i][x];
			a[4] = GRAY[i][j];
			a[5] = GRAY[u][j];
			a[6] = GRAY[q][j];
			a[7] = GRAY[r][j];
			a[8] = GRAY[v][j];

			for (int k = 9; k > 0; --k)							//Bubbler
			{
				for (int l = 0; l < k; ++l)
				{
					if (a[l] > a[l+1]) 
					{   
						int t = a[l];
						a[l] = a[l+1];
						a[l+1] = t;							
					}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
				}
			}
			single += GRAY[i][j] * GRAY[i][j];
			noise += (a[4]-GRAY[i][j]) * (a[4]-GRAY[i][j]);
		}
	}outimage->Draw(&dc,CPoint(276,10));
	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();

	/*for(int i =0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			if(i == 0 && j == 0)											//(0,0)
			{
				a[0] = GRAY[0][0];
				a[1] = GRAY[1][0];
				a[2] = GRAY[2][0];
				a[3] = GRAY[0][1];
				a[4] = GRAY[0][2];
				a[5] = GRAY[0][width-1];
				a[6] = GRAY[0][width-2];
				a[7] = GRAY[height-1][0];
				a[8] = GRAY[height-2][0];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			if(i == 1 && j == 1)											//(1,1)
			{
				a[0] = GRAY[1][1];
				a[1] = GRAY[1][2];
				a[2] = GRAY[1][3];
				a[3] = GRAY[2][1];
				a[4] = GRAY[3][1];
				a[5] = GRAY[1][0];
				a[6] = GRAY[1][width-1];
				a[7] = GRAY[0][0];
				a[8] = GRAY[height-1][0];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-1 && j ==0)									//(height,0)
			{
				a[0] = GRAY[height-1][0];
				a[1] = GRAY[height-2][0];
				a[2] = GRAY[height-3][0];
				a[3] = GRAY[height-1][1];
				a[4] = GRAY[height-1][2];
				a[5] = GRAY[0][0];
				a[6] = GRAY[1][0];
				a[7] = GRAY[height-1][width-1];
				a[8] = GRAY[height-1][width-2];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-2 && j ==1)									//(height-1,1)
			{
				a[0] = GRAY[height-2][1];
				a[1] = GRAY[height-2][2];
				a[2] = GRAY[height-2][3];
				a[3] = GRAY[height-2][0];
				a[4] = GRAY[height-2][width-1];
				a[5] = GRAY[height-4][1];
				a[6] = GRAY[height-3][1];
				a[7] = GRAY[height-1][1];
				a[8] = GRAY[0][1];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == 0 && j == width-1)									//(0,width)
			{
				a[0] = GRAY[0][width-1];
				a[1] = GRAY[0][0];
				a[2] = GRAY[0][1];
				a[3] = GRAY[0][width-2];
				a[4] = GRAY[0][width-3];
				a[5] = GRAY[1][width-1];
				a[6] = GRAY[2][width-1];
				a[7] = GRAY[height-1][width-1];
				a[8] = GRAY[height-2][width-1];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == 1 && j == width-2)									//(1,width-1)
			{
				a[0] = GRAY[1][width-2];
				a[1] = GRAY[1][width-1];
				a[2] = GRAY[1][0];
				a[3] = GRAY[1][width-3];
				a[4] = GRAY[1][width-4];
				a[5] = GRAY[height-1][width-2];
				a[6] = GRAY[0][width-2];
				a[7] = GRAY[2][width-2];
				a[8] = GRAY[3][width-2];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-1 && j == width-1)								//(height,width)
			{
				a[0] = GRAY[height-1][width-1];
				a[1] = GRAY[height-1][0];
				a[2] = GRAY[height-1][1];
				a[3] = GRAY[height-1][width-2];
				a[4] = GRAY[height-1][width-3];
				a[5] = GRAY[height-2][width-1];
				a[6] = GRAY[height-3][width-1];
				a[7] = GRAY[0][width-1];
				a[8] = GRAY[1][width-1];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i == height-2 && j == width-2)								//(height-1,width-1)
			{
				a[0] = GRAY[height-2][width-4];
				a[1] = GRAY[height-2][width-3];
				a[2] = GRAY[height-2][width-2];
				a[3] = GRAY[height-2][width-1];
				a[4] = GRAY[height-2][0];
				a[5] = GRAY[height-4][width-2];
				a[6] = GRAY[height-3][width-2];
				a[7] = GRAY[height-1][width-2];
				a[8] = GRAY[0][width-2];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}
			else if(i > 1 && j > 1 && i < height-2 && j < width-2)
			{
				a[0] = GRAY[i][j-2];
				a[1] = GRAY[i][j-1];
				a[2] = GRAY[i][j];
				a[3] = GRAY[i][j+1];
				a[4] = GRAY[i][j+2];
				a[5] = GRAY[i-2][j];
				a[6] = GRAY[i-1][j];
				a[7] = GRAY[i+1][j];
				a[8] = GRAY[i+2][j];
				for (int k = 9; k > 0; --k)							//Bubbler
				{
					for (int l = 0; l < k; ++l)
					{
						if (a[l] > a[l+1]) 
						{   
							int t = a[l];
							a[l] = a[l+1];
							a[l+1] = t;
							
						}outimage->SetPixel(j,i,RGB(a[4],a[4],a[4]));
					}
				}
			}							
		}
	}outimage->Draw(&dc,CPoint(276,10));*/
}
