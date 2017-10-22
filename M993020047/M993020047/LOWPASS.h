#pragma once
#include "DIBSectionLite.h"


// LOWPASS dialog

class LOWPASS : public CDialog
{
	DECLARE_DYNAMIC(LOWPASS)

public:
	LOWPASS(CWnd* pParent = NULL);   // standard constructor
	virtual ~LOWPASS();

// Dialog Data
	enum { IDD = IDD_DIALOGLOWPASS };

public:
	void Setting_Picture_Info(int Height, int Width, int ** R, int ** G, int **B);

private:
	int **GRAY;
	int height;
	int width;
	CDIBSectionLite  * image;
	CDIBSectionLite  * lowimage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int div;
	int m11;
	int m12;
	int m13;
	int m14;
	int m15;
	int m16;
	int m17;
	int m21;
	int m22;
	int m23;
	int m24;
	int m25;
	int m26;
	int m27;
	int m31;
	int m32;
	int m33;
	int m34;
	int m35;
	int m36;
	int m37;
	int m41;
	int m42;
	int m43;
	int m44;
	int m45;
	int m46;
	int m47;
	int m51;
	int m52;
	int m53;
	int m54;
	int m55;
	int m56;
	int m57;
	int m61;
	int m62;
	int m63;
	int m64;
	int m65;
	int m66;
	int m67;
	int m71;
	int m72;
	int m73;
	int m74;
	int m75;
	int m76;
	int m77;
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton55();
	afx_msg void OnBnClickedButton77();
	float m_snr;
};
