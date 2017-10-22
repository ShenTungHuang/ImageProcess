#pragma once
#include "DIBSectionLite.h"


// HISTOGRAMEQUALIZATION dialog

class HISTOGRAMEQUALIZATION : public CDialog
{
	DECLARE_DYNAMIC(HISTOGRAMEQUALIZATION)

public:
	HISTOGRAMEQUALIZATION(CWnd* pParent = NULL);   // standard constructor
	virtual ~HISTOGRAMEQUALIZATION();

// Dialog Data
	enum { IDD = IDD_DIALOGHISTOGRAMEQUALIZATION };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int **nGRAY;
	int count[256];
	int count1[256];
	int PDF[256];
	int PDF1[256];
	int CDF[256];
	int CDF1[256];
	int height;
	int width;
	int max;
	int max1;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	float m_snr;
};
