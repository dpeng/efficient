/////////////////////////////////////////////////////////////////////////////
// Project��MYIMGAPP
// Author��NorthTibet
// Date��������, ���� 26, 2002
// Description��ͨ�����Ƶ�C++����MFC�����������ʾ���ָ�ʽ��ͼ��
//
/////////////////////////////////////////////////////////////////////////////
// View.h : interface of the CPictureView class
//
/////////////////////////////////////////////////////////////////////////////
#include "Doc.h"

/////////////////
// Picture view is a typical scroll view.
//
class CPictureView : public CScrollView {
public:
	virtual ~CPictureView();
	CPictureDoc* GetDocument() { return (CPictureDoc*)m_pDocument; }

protected:
	BOOL m_rcImage;		// rect to display image in
	UINT m_iHowScale;		// how to scale image

	CPictureView();
	void GetImageRect(CRect& rc);
	void SetScrollSizes();

	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate(); // called first time after construct

	// command/message handlers
	afx_msg void OnViewScale(UINT nID);
	afx_msg void OnUpdateViewScale(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_DYNCREATE(CPictureView)
	DECLARE_MESSAGE_MAP()
};
