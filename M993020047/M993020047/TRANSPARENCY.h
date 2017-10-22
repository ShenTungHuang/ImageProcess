#pragma once
#include "DIBSectionLite.h"


// TRANSPARENCY dialog

class TRANSPARENCY : public CDialog
{
	DECLARE_DYNAMIC(TRANSPARENCY)

public:
	TRANSPARENCY(CWnd* pParent = NULL);   // standard constructor
	virtual ~TRANSPARENCY();

// Dialog Data
	enum { IDD = IDD_DIALOGTRANSPARENCY };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **R2;
	int **G2;
	int **B2;
	int height;
	int width;
	int height2;
	int width2;
	CDIBSectionLite  * image;
	CDIBSectionLite  * image2;
	CDIBSectionLite  * image3;

private:
	class PCX_header
	{
	public:
		char manufacturer;
		char version;
		char encoding;
		char bits_per_pixel;
		short Xmin,Ymin;
		short Xmax,Ymax;
		short hres;
		short vres;
		char pallete[48];
		char reserved;
		char color_planes;
		short bytes_per_line;
		short pallete_type;
		char filler[58];
	};
    PCX_header PCXheader;
	PCX_header PCXsave;

    char cb;
	int k,m,n,width1,height1,bpl,start;
	double RLE_value,snr,signal,noise,s,o,r;
    unsigned char *Palette_data;
	unsigned char *pcx_data;
	unsigned char *pixel_value;

protected:
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	int x1;
	int y1;
	int x2;
	int y2;
	int change;
	int tshape;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonopen();
	int per;
	CScrollBar percentagelim;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedRadioline();
	afx_msg void OnBnClickedRadiorect();
	afx_msg void OnBnClickedRadioell();
	afx_msg void OnBnClickedButtoncur();
	afx_msg void OnBnClickedRadioci();
	afx_msg void OnBnClickedRadioco();
};
