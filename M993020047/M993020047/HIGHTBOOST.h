#pragma once
#include "DIBSectionLite.h"


// HIGHTBOOST dialog

class HIGHTBOOST : public CDialog
{
	DECLARE_DYNAMIC(HIGHTBOOST)

public:
	HIGHTBOOST(CWnd* pParent = NULL);   // standard constructor
	virtual ~HIGHTBOOST();

// Dialog Data
	enum { IDD = IDD_DIALOGHIGHTBOOST };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * hbimage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int A;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	float m_snr;
};
