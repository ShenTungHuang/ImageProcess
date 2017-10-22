#pragma once
#include "DIBSectionLite.h"


// PSEUDO dialog

class PSEUDO : public CDialog
{
	DECLARE_DYNAMIC(PSEUDO)

public:
	PSEUDO(CWnd* pParent = NULL);   // standard constructor
	virtual ~PSEUDO();

// Dialog Data
	enum { IDD = IDD_DIALOGPSEUDO };

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
	afx_msg void OnBnClickedButtonmaxmin();
	afx_msg void OnBnClickedButtonminmax();
	afx_msg void OnBnClickedButtonpmed();
	float m_snr;
};
