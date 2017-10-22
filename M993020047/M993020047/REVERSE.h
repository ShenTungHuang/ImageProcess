#pragma once
#include "DIBSectionLite.h"


// REVERSE dialog

class REVERSE : public CDialog
{
	DECLARE_DYNAMIC(REVERSE)

public:
	REVERSE(CWnd* pParent = NULL);   // standard constructor
	virtual ~REVERSE();

// Dialog Data
	enum { IDD = IDD_DIALOGREVERSE };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	CDIBSectionLite  *reverseimage;

	int height;
	int width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadiovertical();
	afx_msg void OnBnClickedRadiohorizontal();
	afx_msg void OnBnClickedRadiovandh();
	afx_msg void OnBnClickedRadiohandv();
};
