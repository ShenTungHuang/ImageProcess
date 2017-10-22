#pragma once
#include "DIBSectionLite.h"


// DCT dialog

class DCT : public CDialog
{
	DECLARE_DYNAMIC(DCT)

public:
	DCT(CWnd* pParent = NULL);   // standard constructor
	virtual ~DCT();

// Dialog Data
	enum { IDD = IDD_DIALOGDCT };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	double **GRAY;
	double **nGRAY;
	double **c;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtondct();
	afx_msg void OnBnClickedButtonidct();
	afx_msg void OnBnClickedButtonrdc();
	afx_msg void OnBnClickedButtonadc();
	short m_snr;
};
