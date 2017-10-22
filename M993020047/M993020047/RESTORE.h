#pragma once
#include "DIBSectionLite.h"


// RESTORE dialog

class RESTORE : public CDialog
{
	DECLARE_DYNAMIC(RESTORE)

public:
	RESTORE(CWnd* pParent = NULL);   // standard constructor
	virtual ~RESTORE();

// Dialog Data
	enum { IDD = IDD_DIALOGRESTORE };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);
	int xc;
	int yc;

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **nR;
	int **nG;
	int **nB;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;

protected:
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	int x1;
	int y1;
	int x2;
	int y2;
	int shapetype;
	int cuttype;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRadioline();
	afx_msg void OnBnClickedRadiorectangle();
	afx_msg void OnBnClickedRadioellipae();
	afx_msg void OnBnClickedButtoncut();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonrestore();
};
