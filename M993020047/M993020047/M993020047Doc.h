// M993020047Doc.h : interface of the CM993020047Doc class
//


#pragma once


class CM993020047Doc : public CDocument
{
protected: // create from serialization only
	CM993020047Doc();
	DECLARE_DYNCREATE(CM993020047Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CM993020047Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


