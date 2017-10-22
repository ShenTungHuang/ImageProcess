// WATERMARK.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "WATERMARK.h"


// WATERMARK dialog

IMPLEMENT_DYNAMIC(WATERMARK, CDialog)

WATERMARK::WATERMARK(CWnd* pParent /*=NULL*/)
	: CDialog(WATERMARK::IDD, pParent)
	, m_snr(0)
{
	R=NULL;
	G=NULL;
	B=NULL;
	WRGB=NULL;
	wimage=NULL;
	insimage=NULL;
	wbp=NULL;
	GG=NULL;
	WGG=NULL;
	height=0;
	width=0;
}

WATERMARK::~WATERMARK()
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
	if(WGG)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] WGG[i]; delete [] WGG;
	}
	if(WRGB)															//釋放R的記憶體空間
	{
		for(i=0;i<height;i++) delete [] WRGB[i]; delete [] WRGB;
	}

	if(image) delete image;
	if(wimage) delete wimage;
	if(insimage) delete insimage;
	if(wbp) delete wbp;
}

void WATERMARK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_snr);
}


BEGIN_MESSAGE_MAP(WATERMARK, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONOPEN, &WATERMARK::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTONINSERT, &WATERMARK::OnBnClickedButtoninsert)
	ON_BN_CLICKED(IDC_RADIOw1st, &WATERMARK::OnBnClickedRadiow1st)
	ON_BN_CLICKED(IDC_RADIOw2nd, &WATERMARK::OnBnClickedRadiow2nd)
	ON_BN_CLICKED(IDC_RADIOw3rd, &WATERMARK::OnBnClickedRadiow3rd)
	ON_BN_CLICKED(IDC_RADIOw4th, &WATERMARK::OnBnClickedRadiow4th)
	ON_BN_CLICKED(IDC_RADIOw5th, &WATERMARK::OnBnClickedRadiow5th)
	ON_BN_CLICKED(IDC_RADIOw6th, &WATERMARK::OnBnClickedRadiow6th)
	ON_BN_CLICKED(IDC_RADIOw7th, &WATERMARK::OnBnClickedRadiow7th)
	ON_BN_CLICKED(IDC_RADIOw8th, &WATERMARK::OnBnClickedRadiow8th)
END_MESSAGE_MAP()


// WATERMARK message handlers
void WATERMARK::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
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
	if(WGG)
	{
		for(i=0;i<height;i++) delete [] WGG[i]; delete [] WGG;
	}
	if(WRGB)
	{
		for(i=0;i<height;i++) delete [] WRGB[i]; delete [] WRGB;
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

    WGG=new int * [height]; 
    for(i=0;i<height;i++) WGG[i]=new int [width];

	WRGB=new int * [height]; 
    for(i=0;i<height;i++) WRGB[i]=new int [width];

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
		}
	}

	CClientDC dc(this);
	image = new CDIBSectionLite();
	image->CreateEmptyDIB(width,height,24);
    for(i=0;i<height;i++) 
	{
		for(j=0;j<width;j++)
	    {
			image->SetPixel(j,i,RGB(GG[i][j],GG[i][j],GG[i][j]));
		}
		
	}image->Draw(&dc,CPoint(0,0));

}
void WATERMARK::OnPaint()
{
	CPaintDC dc(this); 
	image->Draw(&dc,CPoint(0,0));
}

void WATERMARK::OnBnClickedButtonopen()
{
	CFileDialog dialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,CString("PCX檔案(*.pcx)|*.pcx||"),NULL);
	if(dialog.DoModal()==IDOK)
	{
		CFile file;
		file.Open(dialog.GetFileName(),CFile::modeRead);              
        file.Read(&PCXheader,128);

		if(PCXheader.manufacturer==0x0a) //if the picture file was PCX format
		{
			width=(PCXheader.Xmax-PCXheader.Xmin)+1;
	        height=(PCXheader.Ymax-PCXheader.Ymin)+1;
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

	WR=new int * [height]; 
    for(int i=0;i<height;i++) WR[i]=new int [width];

    WG=new int * [height]; 
    for(int i=0;i<height;i++) WG[i]=new int [width];

    WB=new int * [height]; 
    for(int i=0;i<height;i++) WB[i]=new int [width];

	if(cb==0x0c && (int)PCXheader.color_planes==1)
    {			
		for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
			{
				WR[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3];
	            WG[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3+1];
		        WB[i][j]=(int)Palette_data[(pixel_value[(j)+(i)*width])*3+2];
			}
		}
	}
	else
	{
		for(int i=0;i<height;i++) 
		{
			for(int j=0;j<width;j++)
			{
				WR[i][j]=(int)pixel_value[j+((i)*width*3)];
		        WG[i][j]=(int)pixel_value[j+(width*1)+((i)*width*3)];
		        WB[i][j]=(int)pixel_value[j+(width*2)+((i)*width*3)];
			}			    
		}				
	}

	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			WGG[i][j]=(WR[i][j]+WG[i][j]+WB[i][j])/3;
            int WB8=(((0X80)&(GG[i][j]))/128);
			int WB7=(((0X40)&(GG[i][j]))/64);
			int WB6=(((0X20)&(GG[i][j]))/32);
			int WB5=(((0X10)&(GG[i][j]))/16);
			int WB4=(((0X08)&(GG[i][j]))/8);
			int WB3=(((0X04)&(GG[i][j]))/4);
			int WB2=(((0X02)&(GG[i][j]))/2);
			int WB1=((0X01)&(GG[i][j]));
		}
	}

	CClientDC dc(this);
	wimage = new CDIBSectionLite();
	wimage->CreateEmptyDIB(width,height,24);

    for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
	    {
            if( ((0X80)&(WGG[i][j]))==0 )
               wimage->SetPixel(j,i,RGB(0,0,0));
			else
               wimage->SetPixel(j,i,RGB(255,255,255));
		}
		
	}wimage->Draw(&dc,CPoint(266,0));
}

void WATERMARK::OnBnClickedButtoninsert()
{
	CClientDC dc(this);
	insimage = new CDIBSectionLite();
	insimage->CreateEmptyDIB(width,height,24);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
            int B8=(((0X80)&(GG[i][j]))/128);
			int B7=(((0X40)&(GG[i][j]))/64);
			int B6=(((0X20)&(GG[i][j]))/32);
			int B5=(((0X10)&(GG[i][j]))/16);
			int B4=(((0X08)&(GG[i][j]))/8);
			int B3=(((0X04)&(GG[i][j]))/4);
			int B2=(((0X02)&(GG[i][j]))/2);
			int B1=((0X01)&(GG[i][j]));
            int WB8=(((0X80)&(WGG[i][j]))/128);
			WRGB[i][j]=((B8*128)+(B7*64)+(B6*32)+(B5*16)+(B4*8)+(B3*4)+(B2*2)+WB8);
			insimage->SetPixel(j,i,RGB(WRGB[i][j],WRGB[i][j],WRGB[i][j]));
		}
	}insimage->Draw(&dc,CPoint(532,0));

	//計算SNR
	float single=0,noise=0;
	float SNR;
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			single += GG[i][j] * GG[i][j];
			noise += (WRGB[i][j]-GG[i][j]) * (WRGB[i][j]-GG[i][j]);
		}
	}

	SNR=10*log10(single/noise);
	m_snr = SNR;
	UpdateData(false); UpdateWindow();
}

void WATERMARK::OnBnClickedRadiow1st()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X01)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(266,266));
}

void WATERMARK::OnBnClickedRadiow2nd()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X02)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(532,266));
}

void WATERMARK::OnBnClickedRadiow3rd()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X04)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(266,266));
}

void WATERMARK::OnBnClickedRadiow4th()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X08)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(532,266));
}

void WATERMARK::OnBnClickedRadiow5th()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X10)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(266,266));
}

void WATERMARK::OnBnClickedRadiow6th()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X20)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(532,266));
}

void WATERMARK::OnBnClickedRadiow7th()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X40)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(266,266));
}

void WATERMARK::OnBnClickedRadiow8th()
{
	CClientDC dc(this);
	wbp = new CDIBSectionLite();
	wbp->CreateEmptyDIB(width,height,24);
    for(int i=0;i<height;i++) 
	  {
		  for(int j=0;j<width;j++)
		   { 
            if( ((0X80)&(WRGB[i][j]))==0 )
               wbp->SetPixel(j,i,RGB(0,0,0));
			else
               wbp->SetPixel(j,i,RGB(255,255,255));
		   }
	  }wbp->Draw(&dc,CPoint(532,266));
}
