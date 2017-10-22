#pragma once
#include "DIBSectionLite.h"


// BITPLANE dialog

class BITPLANE : public CDialog
{
	DECLARE_DYNAMIC(BITPLANE)

public:
	BITPLANE(CWnd* pParent = NULL);   // standard constructor
	virtual ~BITPLANE();

// Dialog Data
	enum { IDD = IDD_DIALOGBITPLAN };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **GG;
	int **GGP;
	CDIBSectionLite  *bpimage;
	CDIBSectionLite  *gcimage;

	int height;
	int width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1st();
	afx_msg void OnBnClickedRadio2nd();
	afx_msg void OnBnClickedRadio3th();
	afx_msg void OnBnClickedRadio4th();
	afx_msg void OnBnClickedRadio5th();
	afx_msg void OnBnClickedRadio6th();
	afx_msg void OnBnClickedRadio7th();
	afx_msg void OnBnClickedRadio8th();
	afx_msg void OnBnClickedRadiocombine();
};
