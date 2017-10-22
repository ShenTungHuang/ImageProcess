// HUFFMAN.cpp : implementation file
//

#include "stdafx.h"
#include "M993020047.h"
#include "HUFFMAN.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include "string.h" 
#include <fstream>
#include <cstring>
using namespace std;


// HUFFMAN dialog

IMPLEMENT_DYNAMIC(HUFFMAN, CDialog)

HUFFMAN::HUFFMAN(CWnd* pParent /*=NULL*/)
	: CDialog(HUFFMAN::IDD, pParent)
{
	R=NULL;
	G=NULL;
	B=NULL;
	image=NULL;
	image2=NULL;
	GRAY=NULL;
	height=0;
	width=0;
	m_Huffman=NULL;
	show_Huffman=NULL;
}

HUFFMAN::~HUFFMAN()
{
	int i;
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i] ; delete [] GRAY;
	}
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
	if(m_Huffman)															
	{
		for(i=0;i<height;i++) delete [] m_Huffman[i]; delete [] m_Huffman;
	}

	if(image) delete image;
	if(image2) delete image2;
	if(show_Huffman) delete show_Huffman;
}

void HUFFMAN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HUFFMAN, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTONencoding, &HUFFMAN::OnBnClickedButtonencoding)
	ON_BN_CLICKED(IDC_BUTTONdecoding, &HUFFMAN::OnBnClickedButtondecoding)
END_MESSAGE_MAP()


// HUFFMAN message handlers
void HUFFMAN::Setting_Picture_Info(int Height, int Width, int ** Input_R, int ** Input_G, int ** Input_B)
{	
	int i,j;
	width=Width; height=Height;

	//檢查R、G、B記憶體是否已經建立，是則刪除
	if(GRAY)
	{
		for(i=0;i<height;i++) delete [] GRAY[i]; delete [] GRAY;
	}
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
void HUFFMAN::OnPaint()
{
	CPaintDC dc(this);
	image->Draw(&dc,CPoint(10,10));
}

void HUFFMAN::OnBnClickedButtonencoding()
{
	// TODO: 在此加入您的命令處理常式程式碼

	int **R2=new int * [height];

	for(int i=0;i<height;i++)
	{
		R2[i]=new int [width];
	}

	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{	
			R2[i][j] = (int)(0.3*R[i][j]+0.3*G[i][j]+0.4*B[i][j]);
		}	
	}

	int m_gray_histogram[256];

	//給初值
	for(int i=0;i<256;i++)
	{
		m_gray_histogram[i] = 0;
	}

	//統計數量
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(R2[i][j] == k)
				{
					m_gray_histogram[k]++;
				}
			}
		}
	}

	float gray_probability[256];//存放機率介於0和1之間
	float gray_probability_sort[256];//排序

	//給初值
	for(int i=0;i<256;i++)
	{
		gray_probability[i] = 0;
		gray_probability_sort[i] = 0;
	}

	int totalpixel_value=height*width;
	for(int i=0;i<256;i++)
	{
		gray_probability[i]=(float)m_gray_histogram[i]/(float)totalpixel_value;
		gray_probability_sort[i]=gray_probability[i];
	}

	int correspondence_pixel_value[256];
	correspondence_pixel_value[0]=0;
	for(int i=1;i<256;i++)
		correspondence_pixel_value[i]=correspondence_pixel_value[i-1]+1;


	for (int j=0;j<255;j++)
	{
		for (int i=0;i<255-j;i++)
		{
			if (gray_probability_sort[i] >gray_probability_sort[i+1])
			{
				swap(gray_probability_sort[i],gray_probability_sort[i+1]);
				swap(correspondence_pixel_value[i],correspondence_pixel_value[i+1]);
				// 將i和i+1灰度的位置值互換
				/*for (int k=0;k<256;k++)
				{				
					if (correspondence_pixel_value[k] == i)
						correspondence_pixel_value[k] = i + 1;
					else if (correspondence_pixel_value[k] == i + 1)
						correspondence_pixel_value[k] = i;
				}*/
			}
		}
	}
	
	//CString	* m_strCode;
	//m_strCode = new CString[256];
	int temp1=0;//紀錄排序後第一個不為零的位置
	//dTemp 是機率，n4Turn是對應的灰階值
	// 從概率大於0處開始編碼
	

	// 從概率大於0處開始編碼
	for (int i= 0;i<256;i++)
	{
		if(gray_probability_sort[i] > 0)
		{
			temp1=i;
			break;
		}
	}
	
	for(int i=temp1;i<255;i++)
	{
		// 更新m_strCode
		for (int k=0;k<256;k++)
		{
			// 灰度值是否i
			if (correspondence_pixel_value[k] == i)
			{
				// 灰度值較小的碼字加1
				huffman_tree[k] = "1" + huffman_tree[k];
			}
			else if (correspondence_pixel_value[k] == i+1)
			{
				// 灰度值較小的碼字加0
				huffman_tree[k] = "0" + huffman_tree[k];
			}
		}
		
		// 概率最小的兩個概率相加，保存在dTemp[i + 1]中
		gray_probability_sort[i+1] += gray_probability_sort[i];
		
		// 改變映射關係
		for (int k=0;k<256;k ++)
		{
			// 將位置為i的灰度值i改為灰度值i+1
			if (correspondence_pixel_value[k] == i)
				correspondence_pixel_value[k] = i+1;
		}
		
		// 重新排序
		for (int j=i+1;j<255;j++)
		{
			if (gray_probability_sort[j] > gray_probability_sort[j+1])
			{
				// 互換
				swap(gray_probability_sort[j],gray_probability_sort[j+1]);
					
				// // 將i和i+1灰度的位置值互換
				for (int k=0;k<256;k++)
				{
					if (correspondence_pixel_value[k] == j)
						correspondence_pixel_value[k] = j + 1;
					else if (correspondence_pixel_value[k] == j + 1)
						correspondence_pixel_value[k] = j;
				}
			}
			else
				break;
		}
	}	
	
	AverageCodeLength=0;
	// 計算平均碼字長度
	for (int i=0;i<256;i++)
	{
		// 累加
		AverageCodeLength += gray_probability[i] * huffman_tree[i].GetLength();
	}

	fstream file;
	file.open("Huffman tree.txt",ios::out|ios::trunc);

	file<<"灰階值"<<"\t"<<"機率"<<setw(20)<<"\t"<<"編碼"<<setw(20)<<"\t\t"<<"碼長"<<endl;
	// 添加顯示
	for (int i=0;i<256;i++)
	{
		file<<i<<"\t";
	
		// 添加灰度值的概率值
		file<<setw(6)<<setiosflags(ios::left)<<gray_probability[i]<<"\t\t";
	
		// 添加哈夫曼編碼
		file<<setw(20)<<setiosflags(ios::left)<<huffman_tree[i]<<"\t\t";//<<endl;
		
		// 添加碼字長度
		file<<setw(20)<<setiosflags(ios::left)<<huffman_tree[i].GetLength()<<endl;
		
	}	
	
	file.close();


	fstream file1;
	file1.open("Huffman code.txt",ios::out|ios::trunc);
	fstream file2;
	file2.open("pixel.txt",ios::out|ios::trunc);
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			for(int k=0;k<256;k++)
			{
				if(R2[i][j] == k)
				{
					file1<<huffman_tree[k];
					file2<<huffman_tree[k]<<endl;
				}
			}
		}
	}

	file1.close();
	file2.close();
	MessageBox("編碼完成!!","Message",MB_OK|MB_ICONEXCLAMATION);


	//改變字型和大小和粗體
	/*CClientDC dc(this);
	LOGFONT lf;
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight=140;
	lf.lfWeight=FW_BLACK;
	lf.lfItalic=TRUE;
	::lstrcpy(lf.lfFaceName,("Times New Roman"));
	CFont font;
	font.CreatePointFontIndirect(&lf);
	dc.SelectObject(&font);
	dc.TextOutA(width+90,100,CString("Cr:"));

	compress_ratio=0;
	compress_ratio=8/AverageCodeLength;
	CString str;
	str.Format(_T("%.3f"),compress_ratio);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOutA(width+120,100,str);*/

	for(int i=0;i<height;i++) delete [] R2 [i];
	delete [] R2;
}

void HUFFMAN::OnBnClickedButtondecoding()
{
	// TODO: 在此加入您的命令處理常式程式碼

	if(m_Huffman)															
	{
		for(int i=0;i<height;i++) delete [] m_Huffman[i]; delete [] m_Huffman;
	}

	m_Huffman=new int * [height]; 
    for(int i=0;i<height;i++) m_Huffman[i]=new int [width];
	
	fstream file;
	file.open("pixel.txt",ios::in);
	
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)	
		{
			m_Huffman[i][j]=0;
			char tt[100];
			file>>tt;
			CString huffman_code=(CString)tt;
			for(int k=0;k<256;k++)
			{
				if(huffman_tree[k]==huffman_code)
					m_Huffman[i][j]=k;
			}
			huffman_code.Empty();
		}
	}
	file.close();
	
	
	if(show_Huffman)	delete [] show_Huffman;

	//秀圖
	CClientDC dc(this);
	show_Huffman=new CDIBSectionLite();
	show_Huffman->CreateEmptyDIB(width,height,24);
	for(int i=0;i<height;i++) 
	{
		for(int j=0;j<width;j++)
		{
			show_Huffman->SetPixel(j,i,RGB(m_Huffman[i][j],m_Huffman[i][j],m_Huffman[i][j]));
		}
	}show_Huffman->Draw(&dc,CPoint(width+160,10));


	//改變字型和大小和粗體
	/*LOGFONT lf;
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight=140;
	lf.lfWeight=FW_BLACK;
	lf.lfItalic=TRUE;
	::lstrcpy(lf.lfFaceName,("Times New Roman"));
	CFont font;
	font.CreatePointFontIndirect(&lf);
	dc.SelectObject(&font);
	dc.TextOutA(width+90,height+15,CString("Cr:"));

	compress_ratio=0;
	compress_ratio=8/AverageCodeLength;
	CString str;
	str.Format(_T("%.3f"),compress_ratio);
	dc.SetTextColor(RGB(255,0,0));
	dc.TextOutA(width+120,height+15,str);*/
}
