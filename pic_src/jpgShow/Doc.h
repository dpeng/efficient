/////////////////////////////////////////////////////////////////////////////
// Project��MYIMGAPP
// Author��NorthTibet
// Date��������, ���� 26, 2002
// Description��ͨ�����Ƶ�C++����MFC�����������ʾ���ָ�ʽ��ͼ��
//
/////////////////////////////////////////////////////////////////////////////
// Doc.h : interface of the CPictureDoc class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Picture.h"

/////////////////
// Typical MFC doc class. Holds the picture in CPicture.
//
class CPictureDoc : public CDocument {
public:
	virtual ~CPictureDoc();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();

	CPicture* GetPicture() {
		return &m_pict;
	}

protected:
	CPicture	m_pict; // the picture
	CPictureDoc();
	DECLARE_DYNCREATE(CPictureDoc)
	DECLARE_MESSAGE_MAP()
};
