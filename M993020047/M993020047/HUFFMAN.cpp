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
	if(R)															//����R���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] R[i]; delete [] R;
	}
	if(G)															//����G���O����Ŷ�
	{
		for(i=0;i<height;i++) delete [] G[i]; delete [] G;
	}
	if(B)															////����B���O����Ŷ�
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

	//�ˬdR�BG�BB�O����O�_�w�g�إߡA�O�h�R��
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

	//�}�ҰO�������R�BG�BB
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


	//�}�ҰO�������R�BG�BB

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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X

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

	//�����
	for(int i=0;i<256;i++)
	{
		m_gray_histogram[i] = 0;
	}

	//�έp�ƶq
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

	float gray_probability[256];//�s����v����0�M1����
	float gray_probability_sort[256];//�Ƨ�

	//�����
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
				// �Ni�Mi+1�ǫת���m�Ȥ���
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
	int temp1=0;//�����Ƨǫ�Ĥ@�Ӥ����s����m
	//dTemp �O���v�An4Turn�O�������Ƕ���
	// �q���v�j��0�B�}�l�s�X
	

	// �q���v�j��0�B�}�l�s�X
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
		// ��sm_strCode
		for (int k=0;k<256;k++)
		{
			// �ǫ׭ȬO�_i
			if (correspondence_pixel_value[k] == i)
			{
				// �ǫ׭ȸ��p���X�r�[1
				huffman_tree[k] = "1" + huffman_tree[k];
			}
			else if (correspondence_pixel_value[k] == i+1)
			{
				// �ǫ׭ȸ��p���X�r�[0
				huffman_tree[k] = "0" + huffman_tree[k];
			}
		}
		
		// ���v�̤p����ӷ��v�ۥ[�A�O�s�bdTemp[i + 1]��
		gray_probability_sort[i+1] += gray_probability_sort[i];
		
		// ���ܬM�g���Y
		for (int k=0;k<256;k ++)
		{
			// �N��m��i���ǫ׭�i�אּ�ǫ׭�i+1
			if (correspondence_pixel_value[k] == i)
				correspondence_pixel_value[k] = i+1;
		}
		
		// ���s�Ƨ�
		for (int j=i+1;j<255;j++)
		{
			if (gray_probability_sort[j] > gray_probability_sort[j+1])
			{
				// ����
				swap(gray_probability_sort[j],gray_probability_sort[j+1]);
					
				// // �Ni�Mi+1�ǫת���m�Ȥ���
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
	// �p�⥭���X�r����
	for (int i=0;i<256;i++)
	{
		// �֥[
		AverageCodeLength += gray_probability[i] * huffman_tree[i].GetLength();
	}

	fstream file;
	file.open("Huffman tree.txt",ios::out|ios::trunc);

	file<<"�Ƕ���"<<"\t"<<"���v"<<setw(20)<<"\t"<<"�s�X"<<setw(20)<<"\t\t"<<"�X��"<<endl;
	// �K�[���
	for (int i=0;i<256;i++)
	{
		file<<i<<"\t";
	
		// �K�[�ǫ׭Ȫ����v��
		file<<setw(6)<<setiosflags(ios::left)<<gray_probability[i]<<"\t\t";
	
		// �K�[���Ұҽs�X
		file<<setw(20)<<setiosflags(ios::left)<<huffman_tree[i]<<"\t\t";//<<endl;
		
		// �K�[�X�r����
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
	MessageBox("�s�X����!!","Message",MB_OK|MB_ICONEXCLAMATION);


	//���ܦr���M�j�p�M����
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
	// TODO: �b���[�J�z���R�O�B�z�`���{���X

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

	//�q��
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


	//���ܦr���M�j�p�M����
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
