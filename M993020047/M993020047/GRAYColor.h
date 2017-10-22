#pragma once
#include "DIBSectionLite.h"


// GRAYColor dialog

class GRAYColor : public CDialog
{
	DECLARE_DYNAMIC(GRAYColor)

public:
	GRAYColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~GRAYColor();

// Dialog Data
	enum { IDD = IDD_DIALOGGRAY };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **G_r;
	int **G_g;
	int **G_b;
	CDIBSectionLite  *grayimage;

	int height;
	int width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio2level();
	afx_msg void OnBnClickedRadio4level();
	afx_msg void OnBnClickedRadio8level();
	afx_msg void OnBnClickedRadio16level();
	afx_msg void OnBnClickedRadio32level();
	afx_msg void OnBnClickedRadio64level();
	afx_msg void OnBnClickedRadio128level();
	afx_msg void OnBnClickedRadio256level();
};
