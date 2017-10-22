#pragma once
#include "DIBSectionLite.h"
#include "afxwin.h"


// WATERMARK dialog

class WATERMARK : public CDialog
{
	DECLARE_DYNAMIC(WATERMARK)

public:
	WATERMARK(CWnd* pParent = NULL);   // standard constructor
	virtual ~WATERMARK();

// Dialog Data
	enum { IDD = IDD_DIALOGWATERMARK };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int **WR;
	int **WG;
	int **WB;
	int **GG;
	int **WGG;
	int **WRGB;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * wimage;
	CDIBSectionLite  * insimage;
	CDIBSectionLite  * wbp; 

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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtoninsert();
	afx_msg void OnBnClickedRadiow1st();
	afx_msg void OnBnClickedRadiow2nd();
	afx_msg void OnBnClickedRadiow3rd();
	afx_msg void OnBnClickedRadiow4th();
	afx_msg void OnBnClickedRadiow5th();
	afx_msg void OnBnClickedRadiow6th();
	afx_msg void OnBnClickedRadiow7th();
	afx_msg void OnBnClickedRadiow8th();
	float m_snr;
};
