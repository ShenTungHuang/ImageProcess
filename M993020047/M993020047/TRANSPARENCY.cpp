// TRANSPARENCY.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "TRANSPARENCY.h"


// TRANSPARENCY dialog

IMPLEMENT_DYNAMIC(TRANSPARENCY, CDialog)

TRANSPARENCY::TRANSPARENCY(CWnd* pParent /*=NULL*/)
	: CDialog(TRANSPARENCY::IDD, pParent)
	, per(0)
	, m_FirstPoint(CPoint(0,0))
	, m_SecondPoint(CPoint(0,0))
{
	tshape=0;
	change=0;
	x1=0;
	y1=0;
	x2=0;
	y2=0;
	R=NULL;
	G=NULL;
	B=NULL;
	R2=NULL;
	G2=NULL;
	B2=NULL;
	image=NULL;
	image2=NULL;
	image3=NULL;
	height=0;
	width=0;
	height2=0;
	width2=0;
}

TRANSPARENCY::~TRANSPARENCY()
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

	if(R2)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] R2[i]; delete [] R2;
	}
	if(G2)															//釋放G的記憶體空間
	{
		for(i=0;i<height;i++) delete [] G2[i]; delete [] G2;
	}
	if(B2)															////釋放B的記憶體空間
	{
		for(i=0;i<height;i++) delete [] B2[i]; delete [] B2;
	}

	if(image) delete image;
	if(image2) delete image2;
	if(image3) delete image3;
}

void TRANSPARENCY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, percentagelim);
	DDX_Text(pDX, IDC_EDIT1, per);
	DDV_MinMaxInt(pDX, per, 0, 100);
}


BEGIN_MESSAGE_MAP(TRANSPARENCY, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &TRANSPARENCY::OnBnClickedButtonopen)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT1, &TRANSPARENCY::OnEnChangeEdit1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_RADIOLINE, &TRANSPARENCY::OnBnClickedRadioline)
	ON_BN_CLICKED(IDC_RADIORECT, &TRANSPARENCY::OnBnClickedRadiorect)
	ON_BN_CLICKED(IDC_RADIOELL, &TRANSPARENCY::OnBnClickedRadioell)
	ON_BN_CLICKED(IDC_BUTTONcur, &TRANSPARENCY::OnBnClickedButtoncur)
	ON_BN_CLICKED(IDC_RADIOci, &TRANSPARENCY::OnBnClickedRadioci)
	ON_BN_CLICKED(IDC_RADIOco, &TRANSPARENCY::OnBnClickedRadioco)
END_MESSAGE_MAP()

BOOL TRANSPARENCY::OnInitDialog()
{
	CDialog::OnInitDialog();
	percentagelim.SetScrollRange(0,100);
	return(TRUE);
}

// TRANSPARENCY message handlers
void TRANSPARENCY::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
	}
}
void TRANSPARENCY::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void TRANSPARENCY::OnBnClickedButtonopen()
{
	CFileDialog dialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,CString("PCX檔案(*.pcx)|*.pcx||"),NULL);
	if(dialog.DoModal()==IDOK)
	{
		CFile file;
		file.Open(dialog.GetFileName(),CFile::modeRead);              
        file.Read(&PCXheader,128);

		if(PCXheader.manufacturer==0x0a) //if the picture file was PCX format
		{
			width2=(PCXheader.Xmax-PCXheader.Xmin)+1;
	        height2=(PCXheader.Ymax-PCXheader.Ymin)+1;
            bpl=PCXheader.bytes_per_line;
            
			file.Seek(-769,CFile::end); //to seek the minus 769 bytes from the end of the file
			file.Read(&cb,1); //to read the control byte with 1 byte
			
		    Palette_data=new unsigned char [768]; //to set the size of the Palette_data array with 768 bytes

			if(cb==0x0c) //if the PCX file had the 256 color palette
		    {
				file.Seek(-768,CFile::end); //to seek the minus 768 bytes from the end of the file
			    file.Read(Palette_data,768); //to read the palette_data array 
		    	RLE_value=(double)((file.GetLength())-128-769); //to save the value of the RLE to RLE_value array  
			}
		    else //if the PCX file had no the 256 color palette
			{
				RLE_value=double(file.GetLength()-128); //to save the value of the RLE to RLE_value array			
			}

		    pcx_data=new unsigned char [RLE_value]; //to set the size of the pcx_data array
		    pixel_value=new unsigned char [1]; //to set the size of the pixel_value array with 1 byte

            file.Seek(128,CFile::begin); //to seek the 128 bytes from the top of the file
            file.Read(pcx_data,RLE_value); //to read pcx_data with the size of the RLE_value
		}
	}
            
	int count,index=0;
	for(int i=0;i<RLE_value;i++)
	{
		count=0;
		if((pcx_data[i] & 0xc0)==0xc0) //if the upper 2 bits of the RLE was 11
		{
			count=(int)(pcx_data[i] & /*0x3f*/63); //to save how many times repeated
		    pixel_value=(unsigned char*)realloc(pixel_value,_msize(pixel_value)+sizeof(char)*(count)); //to extend the array
            for(int j=0;j<count;j++)
			{
				pixel_value[index]=pcx_data[i+1];
				index++;
			}
            i++;
		}
		else //if the upper 2 bits of the RLE was not 11
		{
			count=1;
            pixel_value=(unsigned char*)realloc(pixel_value,_msize(pixel_value)+sizeof(char)*count);
            pixel_value[index]=pcx_data[i];	
	        index++;
		}
	}

	R2=new int * [height2]; 
    for(int i=0;i<height2;i++) R2[i]=new int [width2];

    G2=new int * [height2]; 
    for(int i=0;i<height2;i++) G2[i]=new int [width2];

    B2=new int * [height2]; 
    for(int i=0;i<height2;i++) B2[i]=new int [width2];

	if(cb==0x0c && (int)PCXheader.color_planes==1)
    {			
		for(int i=0;i<height2;i++) 
		{
			for(int j=0;j<width2;j++)
			{
				R2[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width2])*3];
	            G2[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width2])*3+1];
		        B2[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width2])*3+2];
			}
		}
	}
	else
	{
		for(int i=0;i<height2;i++) 
		{
			for(int j=0;j<width2;j++)
			{
				R2[i][j]=(int)pixel_value[j+((i)*width2*3)];
		        G2[i][j]=(int)pixel_value[j+(width2*1)+((i)*width2*3)];
		        B2[i][j]=(int)pixel_value[j+(width2*2)+((i)*width2*3)];
			}			    
		}				
	}

	CClientDC dc(this);
	image2 = new CDIBSectionLite();
	image2->CreateEmptyDIB(width2,height2,24);

    for(int i=0;i<height2;i++) 
	{
		for(int j=0;j<width2;j++)
	    {
			image2->SetPixel(j,i,RGB(R2[i][j],G2[i][j],B2[i][j]));
		}
		
	}image2->Draw(&dc,CPoint(276,10));	
}

void TRANSPARENCY::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
		per = (int)hScrollPos;
		if(R2 && G2 && B2)
		{
			CClientDC dc(this); // device context for painting
			int width_s;
			int height_s;
			if(width2>width)
			{
				width_s=width;
			}
			else
			{
				width_s=width2;
			}
			if(height2>height)
			{
				height_s=height;
			}
			else
			{
				height_s=height2;
			}

			image3 = new CDIBSectionLite();
			image3->CreateEmptyDIB(width2,height2,24);
			for(int i=0;i<width_s;i++) 
			{
				for(int j=0;j<height_s;j++)
				{				
					if(tshape == 2  &&  change == 1)
					{
						if(j>=x1-10 && j<=x2-10 && i>=y1-10 && i<=y2-10 )
						{image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));}
						else
						{	image3->SetPixel(j,i,
							RGB(R2[i][j],G2[i][j],B2[i][j]));}
					}
					else if(tshape == 2  &&  change == 2)
					{
						if(j>=x1-10 && j<=x2-10 && i>=y1-10 && i<=y2-10 )
						{	image3->SetPixel(j,i,
							RGB(R2[i][j],G2[i][j],B2[i][j]));}
						else
						{image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));}
					}
					else
					{
						image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));
					}
				}
			}image3->Draw(&dc,CPoint(276,276));	
		}

		UpdateData(FALSE);
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void TRANSPARENCY::OnEnChangeEdit1()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。
	UpdateData();
	if(per<=100 && per>=0)
	{

		percentagelim.SetScrollPos(per);
		if(R2 && G2 && B2)
		{
			CClientDC dc(this); // device context for painting
			int width_s;
			int height_s;
			if(width2>width)
			{
				width_s=width;
			}
			else
			{
				width_s=width2;
			}
			if(height2>height)
			{
				height_s=height;
			}
			else
			{
				height_s=height2;
			}
			for(int i=0;i<height_s;i++) 
			{
				for(int j=0;j<width_s;j++)
				{			
					if(tshape == 2  &&  change == 1)
					{
						if(j>=x1-10 && j<=x2-10 && i>=y1-10 && i<=y2-10 )
						{image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));}
						else
						{	image3->SetPixel(j,i,
							RGB(R2[i][j],G2[i][j],B2[i][j]));}
					}
					else if(tshape == 2  &&  change == 2)
					{
						if(j>=x1-10 && j<=x2-10 && i>=y1-10 && i<=y2-10 )
						{	image3->SetPixel(j,i,
							RGB(R2[i][j],G2[i][j],B2[i][j]));}
						else
						{image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));}
					}
					else
					{
						image3->SetPixel(j,i,
							RGB(int(double((100-per)*R[i][j]+per*R2[i][j])/100),
							int(double((100-per)*G[i][j]+per*G2[i][j])/100),
							int(double((100-per)*B[i][j]+per*B2[i][j])/100)));
					}
				}
			}image3->Draw(&dc,CPoint(276,276));
		}
	}
}
void TRANSPARENCY::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_FirstPoint = point;
	SetCapture();
	x1 = point.x;
	y1 = point.y;
}

void TRANSPARENCY::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(this == GetCapture())
		ReleaseCapture();
	m_SecondPoint;
	x2 = point.x;
	y2 = point.y;

	CClientDC dc(this);
	CPen pen(PS_DOT,1,RGB(255,0,0));						
	CPen *oldPen = dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);

	if(tshape == 1)
	{ dc.MoveTo(x1,y1);    
	  dc.LineTo(x2,y2); }
	if(tshape == 2)
	{ dc.Rectangle(x1,y1,x2,y2); }
	if(tshape == 3)
	{ dc.Ellipse(x1,y1,x2,y2); }	
	dc.SelectObject(oldPen);
}

void TRANSPARENCY::OnMouseMove(UINT nFlags, CPoint point)
{
	if((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		x2 = point.x;
		y2 = point.y;

		CClientDC dc(this);
		image->Draw(&dc,CPoint(10,10));
		CPen pen(PS_DOT,1,RGB(255,0,0));						
		CPen *oldPen = dc.SelectObject(&pen);
		dc.SelectStockObject(NULL_BRUSH);

		if(tshape == 1)
		{ dc.MoveTo(x1,y1);    
		  dc.LineTo(x2,y2); }
		if(tshape == 2)
		{ dc.Rectangle(x1,y1,x2,y2); }
		if(tshape == 3)
		{ dc.Ellipse(x1,y1,x2,y2); }
		dc.SelectObject(oldPen);
	}
}

void TRANSPARENCY::OnBnClickedRadioline()
{
	tshape = 1;
}

void TRANSPARENCY::OnBnClickedRadiorect()
{
	tshape = 2;
}

void TRANSPARENCY::OnBnClickedRadioell()
{
	tshape = 3;
}

void TRANSPARENCY::OnBnClickedButtoncur()
{
	if(tshape == 2)
	{
		CClientDC dc(this);
		image = new CDIBSectionLite();
		image->CreateEmptyDIB(width,height,24);
	
	    for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
		    {
				if(j>=x1-10 && j<=x2-10 && i>=y1-10 && i<=y2-10 )
				{ image->SetPixel(j,i,RGB(255,255,255)); }
				else
				image->SetPixel(j,i,RGB(R[i][j],G[i][j],B[i][j]));
			}
		
		}image->Draw(&dc,CPoint(10,10));
	}
}

void TRANSPARENCY::OnBnClickedRadioci()
{
	change = 1;
}

void TRANSPARENCY::OnBnClickedRadioco()
{
	change = 2;
}
