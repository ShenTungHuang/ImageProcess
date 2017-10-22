#pragma once
#include "DIBSectionLite.h"


// ROTATE dialog

class ROTATE : public CDialog
{
	DECLARE_DYNAMIC(ROTATE)

public:
	ROTATE(CWnd* pParent = NULL);   // standard constructor
	virtual ~ROTATE();

// Dialog Data
	enum { IDD = IDD_DIALOGROTATE };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **Y;
	int **X;
	int **X_1;
	int **X_2;
	int **Y_1;
	int	**Y_2;
	double rad;
	int Ymin, Xmin, Ymax, Xmax;
	CDIBSectionLite  *image;
	CDIBSectionLite  *bg;
	CDIBSectionLite  *holeimage;
	CDIBSectionLite  *noholeimage;


	int height;
	int width;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonwithhole();
	double degree;
	afx_msg void OnBnClickedButtonwithouthole();
};
