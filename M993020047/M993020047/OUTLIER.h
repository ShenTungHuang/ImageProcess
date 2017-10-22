#pragma once
#include "DIBSectionLite.h"


// OUTLIER dialog

class OUTLIER : public CDialog
{
	DECLARE_DYNAMIC(OUTLIER)

public:
	OUTLIER(CWnd* pParent = NULL);   // standard constructor
	virtual ~OUTLIER();

// Dialog Data
	enum { IDD = IDD_DIALOGOUTLIER };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * outimage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonshow();
	afx_msg void OnBnClickedButtonsquare();
	afx_msg void OnBnClickedButtoncross();
	int e;
	int *a;
	float m_snr;
};
