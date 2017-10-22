#pragma once
#include "DIBSectionLite.h"


// SOBEL dialog

class SOBEL : public CDialog
{
	DECLARE_DYNAMIC(SOBEL)

public:
	SOBEL(CWnd* pParent = NULL);   // standard constructor
	virtual ~SOBEL();

// Dialog Data
	enum { IDD = IDD_DIALOGSOBEL };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	float m_snr;
};
