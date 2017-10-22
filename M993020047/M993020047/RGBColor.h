#pragma once
#include "DIBSectionLite.h"


// RGBColor dialog

class RGBColor : public CDialog
{
	DECLARE_DYNAMIC(RGBColor)

public:
	RGBColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~RGBColor();

// Dialog Data
	enum { IDD = IDD_DIALOGRGB };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	CDIBSectionLite  *rgbimage;


	int height;
	int width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadiored();
	afx_msg void OnBnClickedRadiogreen();
	afx_msg void OnBnClickedRadioblue();
};
