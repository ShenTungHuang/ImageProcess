#pragma once
#include "DIBSectionLite.h"
#include "afxwin.h"


// ZOOM dialog

class ZOOM : public CDialog
{
	DECLARE_DYNAMIC(ZOOM)

public:
	ZOOM(CWnd* pParent = NULL);   // standard constructor
	virtual ~ZOOM();

// Dialog Data
	enum { IDD = IDD_DIALOGZOOM };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **ZR;
	int **ZG;
	int **ZB;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * zoomimage;
	CDIBSectionLite  * bg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int zz;
	afx_msg void OnBnClickedButtondularge();
	afx_msg void OnBnClickedButtondusmall();
	afx_msg void OnBnClickedButtoninlarge();
	afx_msg void OnBnClickedButtoninsmall();
};
