#pragma once

class CShowMsg
{
public:
	CShowMsg(void);
	~CShowMsg(void);
public:
	CBitmap m_StoreBmp;  //�洢λͼ 
	CDC m_StoreDC;    //�洢DC 
	int m_nCoordStrLen;  //�����ַ������� 
	BOOL m_bStart;
	void ShowText(CDC* pDC, CPoint Pt, LPCSTR text);
	void CopyBitmap(CDC* pDC,CPoint copyPt);
	void DrawCoord(CDC* pDC,LPCSTR coordString,CPoint drawPt);
	void DoRubberCoord(CDC* pDC);
	int m_x;
	int m_y;
	CRect m_CurRc;
	bool m_bCanShow;
};
