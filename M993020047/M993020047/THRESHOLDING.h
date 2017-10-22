#pragma once
#include "DIBSectionLite.h"


// THRESHOLDING dialog

class THRESHOLDING : public CDialog
{
	DECLARE_DYNAMIC(THRESHOLDING)

public:
	THRESHOLDING(CWnd* pParent = NULL);   // standard constructor
	virtual ~THRESHOLDING();

// Dialog Data
	enum { IDD = IDD_DIALOGTHRESHOLDING };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int height;
	int width;
	double hist[256];
	double vw[256];
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;
	CDIBSectionLite  * image3;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int thresh;
	CScrollBar threshlim;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEdit1();
	int otsu;
	afx_msg void OnBnClickedButtonot();
	float m_snr;
};
