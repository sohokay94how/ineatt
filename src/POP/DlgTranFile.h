#pragma once
#include "afxcmn.h"

// CDlgTranFile dialog
/*
 * �ļ����䣨�ϴ������أ���Ϣ������
 * ������ʾ�����ļ���Ϣ��֧�ֽ��ܡ��ܾ���ȡ�������Ȳ������ܣ�
 * ֧����ʾ�ļ����ƣ��ļ���С��������ȵȡ�
 * 
*//////////////////////////////////////////////////////

class CDlgTranFile : public CEbDialogBase
{
	DECLARE_DYNAMIC(CDlgTranFile)

public:
	typedef boost::shared_ptr<CDlgTranFile> pointer;
	CDlgTranFile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgTranFile();
	static CDlgTranFile::pointer create(CWnd* pParent)
	{
		return CDlgTranFile::pointer(new CDlgTranFile(pParent));
	}

	void SetCtrlColor(void);
	void Cancel(void);
	void UpdateFileInfo(const CCrFileInfo * pCrFileInfo);
#ifdef USES_EBCOM_TEST
	void SetFilePercent(IEB_ChatFilePercent* pChatRoomFilePercent);
#else
	void SetFilePercent(const CChatRoomFilePercent * pChatRoomFilePercent);
#endif
	//Cchatroom::pointer m_pChatRoom;
	bool m_bIsSendingFile;					// default false;
	//eb::bigint m_sResourceId;
	CCrFileInfo m_pCrFileInfo;
	//EB_CallInfo m_pCallInfo;
// Dialog Data
	enum { IDD = IDD_DLG_TRANFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CTraButton m_btnSave2CloudDrive;
	CTraButton m_btnSaveas;
	CTraButton m_btnSave;
	CTraButton m_btnReject;
	CTraButton m_btnOffFile;
	CTraButton m_btnCancel;
	CProgressST m_progPercent;

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedButtonSave2CloudDrive();
	afx_msg void OnBnClickedButtonSaveas();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonReject();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonOfffile();
	afx_msg void OnPaint();
};
