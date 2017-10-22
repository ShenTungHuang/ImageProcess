#pragma once
#include "DIBSectionLite.h"


// HUFFMAN dialog

class HUFFMAN : public CDialog
{
	DECLARE_DYNAMIC(HUFFMAN)

public:
	HUFFMAN(CWnd* pParent = NULL);   // standard constructor
	virtual ~HUFFMAN();

// Dialog Data
	enum { IDD = IDD_DIALOGHUFFMAN };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **GRAY;
	int height;
	int width;
	int ** R2;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;
	CDIBSectionLite  * show_Huffman;

public:
	CString	huffman_tree[256];//����huffman_tree
	float AverageCodeLength;//�s�񥭧��X��
	int** m_Huffman;//����Huffman�ѽX�᪺��
	float compress_ratio;//�s�����Y��
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonencoding();
	afx_msg void OnBnClickedButtondecoding();
};
