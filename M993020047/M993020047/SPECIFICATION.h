#pragma once
#include "DIBSectionLite.h"


// SPECIFICATION dialog

class SPECIFICATION : public CDialog
{
	DECLARE_DYNAMIC(SPECIFICATION)

public:
	SPECIFICATION(CWnd* pParent = NULL);   // standard constructor
	virtual ~SPECIFICATION();

// Dialog Data
	enum { IDD = IDD_DIALOGSPECIFICATION };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int **nGRAY;
	double hist[256];
	double PDF[256];
	double CDF[256];
	double dCDF[256];
	double dPDF[256];
	double z[256];
	int max;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;
	CDIBSectionLite  * bg;

protected:
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	int px1;
	int py1;
	int px2;
	int py2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonhb();
	afx_msg void OnBnClickedButtonlb();
	afx_msg void OnBnClickedButtonhc();
	afx_msg void OnBnClickedButtonlc();
	double x1;
	double x2;
	double y1;
	double y2;
	afx_msg void OnBnClickedButton1();
	float m_snr;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
