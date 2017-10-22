#pragma once
#include "DIBSectionLite.h"


// NEGATIVEColor dialog

class NEGATIVEColor : public CDialog
{
	DECLARE_DYNAMIC(NEGATIVEColor)

public:
	NEGATIVEColor(CWnd* pParent = NULL);   // standard constructor
	virtual ~NEGATIVEColor();

// Dialog Data
	enum { IDD = IDD_DIALOGNEGATIVE };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **G_r;
	int **G_g;
	int **G_b;
	CDIBSectionLite  *negativeimage;



	int height;
	int width;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioncolor();
	afx_msg void OnBnClickedRadiongray();
};
