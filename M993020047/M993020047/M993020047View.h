// M993020047View.h : interface of the CM993020047View class
//


#pragma once
#include "afxext.h"
#include "DIBSectionLite.h"
#include "RGBColor.h"
#include "GRAYColor.h"
#include "NEGATIVEColor.h"
#include "REVERSE.h"
#include "ZOOM.h"
#include "BITPLANE.h"
#include "ROTATE.h"
#include "WATERMARK.h"
#include "HISTOGRAM.h"
#include "HISTOGRAMEQUALIZATION.h"
#include "TRANSPARENCY.h"
#include "THRESHOLDING.h"
#include "OUTLIER.h"
#include "HIGHTBOOST.h"
#include "LOWPASS.h"
#include "SOBEL.h"
#include "PSEUDO.h"
#include "SPECIFICATION.h"
#include "HUFFMAN.h"
#include "DCT.h"
#include "RESTORE.h"



class CM993020047View : public CView
{
//PCX Header Information
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
	CDIBSectionLite  * image;

	int **R; //to construct R array to save red value
	int **G; //to construct G array to save green value
	int **B; //to construct B array to save blue value
	int a;
	int R_Palette[256];
	int G_Palette[256];
	int B_Palette[256];


    char cb;
	int i,j,k,m,n,width,height,width1,height1,bpl,start;
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
	int shapetype;
	int cuttype;
	int pastetype;

protected: // create from serialization only
	CM993020047View();
	DECLARE_DYNCREATE(CM993020047View)

// Attributes
public:
	CM993020047Doc* GetDocument() const;

// Operations
public:

private:
	
	RGBColor * RGB_Dialog;
	GRAYColor * GRAY_Dialog;
	NEGATIVEColor * NEGATIVE_Dialog;
	REVERSE * REVERSE_Dialog;
	ZOOM * ZOOM_Dialog;
	BITPLANE * BITPLANE_Dialog;
	ROTATE * ROTATE_Dialog;
	WATERMARK * WATERMARK_Dialog;
	HISTOGRAM * HISTOGRAM_Dialog;
	HISTOGRAMEQUALIZATION * HISTOGRAMEQUALIZATION_Dialog;
	TRANSPARENCY * TRANSPARENCY_Dialog;
	THRESHOLDING * THRESHOLDING_Dialog;
	OUTLIER * OUTLIER_Dialog;
	HIGHTBOOST * HIGHTBOOST_Dialog;
	LOWPASS * LOWPASS_Dialog;
	SOBEL * SOBEL_Dialog;
	PSEUDO * PSEUDO_Dialog;
	SPECIFICATION * SPECIFICATION_Dialog;
	HUFFMAN * HUFFMAN_Dialog;
	DCT * DCT_Dialog;
	RESTORE * RESTORE_Dialog;


// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CM993020047View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnShowRgbcolor();
	afx_msg void OnShowGraycolor();
	afx_msg void OnShowNegativecolor();
	afx_msg void OnGeometryReverse();
	afx_msg void OnGeometryZoom();
	afx_msg void OnShowBitplane();
	afx_msg void OnGeometryRotate();
	afx_msg void OnShowWatermark();
	afx_msg void OnShowHistogram();

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);											//add by fei
	afx_msg void OnShowHeader();
	afx_msg void OnShowPalette();
	afx_msg void OnShowHistogramequalization();
	afx_msg void OnShowTransparency();
	afx_msg void OnShowThresholding();
	afx_msg void OnFilterOutlier();
	afx_msg void OnFilterHightboost();
	afx_msg void OnFilterLowpass();
	afx_msg void OnFilterSobelandprewitt();
	afx_msg void OnFilterPseudo();
	afx_msg void OnShowHistogramspecificationandcontrast();
	afx_msg void OnShowHuffmancompression();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShapeLine();
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeEllipse();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
public:
	afx_msg void OnEditCopy();
	afx_msg void OnShowDct();
	afx_msg void OnShowRestore();
};

#ifndef _DEBUG  // debug version in M993020047View.cpp
inline CM993020047Doc* CM993020047View::GetDocument() const
   { return reinterpret_cast<CM993020047Doc*>(m_pDocument); }
#endif

