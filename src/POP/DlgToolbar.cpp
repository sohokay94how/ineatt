// DlgToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "POP.h"
#include "DlgToolbar.h"


// CDlgToolbar dialog

IMPLEMENT_DYNAMIC(CDlgToolbar, CEbDialogBase)

CDlgToolbar::CDlgToolbar(CWnd* pParent /*=NULL*/)
	: CEbDialogBase(CDlgToolbar::IDD, pParent)
{
	m_nDataType = EB_MR_CTRL_DATA_TYPE_URL;
	m_nMsgId = 0;
	m_nMsgFromUserId = 0;
	m_nMsgType = MRT_UNKNOWN;
	m_nMsgReadFlag = 0;
	m_nButtonCount = 0;
	m_hMsgWnd = NULL;
	m_pCallback = NULL;
	m_bChildMode = false;
}

CDlgToolbar::~CDlgToolbar()
{
}

void CDlgToolbar::DoDataExchange(CDataExchange* pDX)
{
	CEbDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_1, m_btnOpen1);
	DDX_Control(pDX, IDC_BTN_2, m_btnOpen2);
	DDX_Control(pDX, IDC_BTN_3, m_btnOpen3);
	DDX_Control(pDX, IDC_BTN_4, m_btnOpen4);
	DDX_Control(pDX, IDC_BTN_5, m_btnOpen5);
	DDX_Control(pDX, IDC_BTN_6, m_btnOpen6);
	DDX_Control(pDX, IDC_BTN_7, m_btnOpen7);
	DDX_Control(pDX, IDC_BTN_8, m_btnOpen8);
}


BEGIN_MESSAGE_MAP(CDlgToolbar, CEbDialogBase)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_1, &CDlgToolbar::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_2, &CDlgToolbar::OnBnClickedBtn2)
	ON_BN_CLICKED(IDC_BTN_3, &CDlgToolbar::OnBnClickedBtn3)
	ON_BN_CLICKED(IDC_BTN_4, &CDlgToolbar::OnBnClickedBtn4)
	ON_BN_CLICKED(IDC_BTN_5, &CDlgToolbar::OnBnClickedBtn5)
	ON_BN_CLICKED(IDC_BTN_6, &CDlgToolbar::OnBnClickedBtn6)
	ON_BN_CLICKED(IDC_BTN_7, &CDlgToolbar::OnBnClickedBtn7)
	ON_BN_CLICKED(IDC_BTN_8, &CDlgToolbar::OnBnClickedBtn8)
END_MESSAGE_MAP()

void CDlgToolbar::SetCtrlColor(bool bInvalidate)
{
	//m_btnOpen1.SetDrawPanel(true,theDefaultBtnWhiteColor,theApp.GetBgColor(),theApp.GetMainColor());
	//m_btnOpen1.SetDrawLine(5,1,0,theDefaultFlatLine2Color,theApp.GetMainColor(),theApp.GetPreColor());
	//m_btnOpen2.SetDrawLine(5,1,0,theDefaultFlatLine2Color,theApp.GetMainColor(),theApp.GetPreColor());
	//m_btnOpen3.SetDrawLine(5,1,0,theDefaultFlatLine2Color,theApp.GetMainColor(),theApp.GetPreColor());
	//m_btnOpen4.SetDrawLine(5,1,0,theDefaultFlatLine2Color,theApp.GetMainColor(),theApp.GetPreColor());
	m_btnOpen1.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen1.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen2.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen2.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen3.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen3.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen4.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen4.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen5.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen5.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen6.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen6.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen7.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen7.SetPreTextColor(theApp.GetPreColor());
	m_btnOpen8.SetHotTextColor(theApp.GetMainColor());
	m_btnOpen8.SetPreTextColor(theApp.GetPreColor());

	if (bInvalidate)
		this->Invalidate();
}
int CDlgToolbar::SetMoveEnterData(EB_MR_CTRL_DATA_TYPE nDataType, const std::string& sString, mycp::bigint nMsgId, bool& pOutChangeData)
{
	pOutChangeData = m_nDataType != nDataType || m_sMoveEnterString != sString || m_nMsgId!=nMsgId;
	if (!pOutChangeData) return m_nButtonCount;	// 4;
	m_nDataType = nDataType;
	m_sMoveEnterString = sString;
	m_nMsgId = nMsgId;
	m_nMsgFromUserId = 0;
	m_nMsgType = MRT_UNKNOWN;
	m_nMsgReadFlag = 0;
	if (m_nMsgId>0)
	{
		CString sSql;
		sSql.Format(_T("select from_uid,read_flag,msg_type FROM msg_record_t WHERE msg_id=%lld LIMIT 1"),m_nMsgId);
		int nCookie = 0;
		theApp.m_pBoUsers->select(sSql, nCookie);
		cgcValueInfo::pointer pRecord = theApp.m_pBoUsers->last(nCookie);
		if (pRecord.get()!=NULL)
		{
			m_nMsgFromUserId = pRecord->getVector()[0]->getBigIntValue();
			m_nMsgReadFlag = pRecord->getVector()[1]->getIntValue();
			m_nMsgType = (MSG_RECORD_TYPE)pRecord->getVector()[2]->getIntValue();
			theApp.m_pBoUsers->reset(nCookie);
		}
	}
	m_nButtonCount = 4;
	switch (m_nDataType)
	{
	//case EB_MR_CTRL_DATA_TYPE_DELETE_MSGID:
	//	{
	//		m_nButtonCount = 1;
	//		m_btnOpen1.SetWindowText(_T("????"));
	//		m_btnOpen1.SetToolTipText(_T("????????????????"));
	//		m_btnOpen1.ShowWindow(SW_SHOW);
	//		m_btnOpen2.ShowWindow(SW_HIDE);
	//		m_btnOpen3.ShowWindow(SW_HIDE);
	//		m_btnOpen4.ShowWindow(SW_HIDE);
	//	}break;
	//case EB_MR_CTRL_DATA_TYPE_SEND_MSGID:
	//	{
	//		m_nButtonCount = 2;
	//		m_btnOpen1.SetWindowText(_T("????"));
	//		m_btnOpen1.SetToolTipText(_T("????????????????"));
	//		m_btnOpen2.SetWindowText(_T("????"));
	//		m_btnOpen2.SetToolTipText(_T("????????"));
	//		m_btnOpen1.ShowWindow(SW_SHOW);
	//		m_btnOpen2.ShowWindow(SW_SHOW);
	//		m_btnOpen3.ShowWindow(SW_HIDE);
	//		m_btnOpen4.ShowWindow(SW_HIDE);
	//	}break;
	case EB_MR_CTRL_DATA_TYPE_URL:
		{
			if (!theApp.GetHideMainFrame()) 
			{
				m_btnOpen1.SetWindowText(_T("??????"));
				m_btnOpen1.SetToolTipText(_T("??????????????????"));
				m_btnOpen1.ShowWindow(SW_SHOW);
			}else
			{
				m_nButtonCount -= 1;
				m_btnOpen1.ShowWindow(SW_HIDE);
			}
			m_btnOpen2.SetWindowText(_T("??????"));
			m_btnOpen2.SetToolTipText(_T("??????????????????"));
			m_btnOpen2.ShowWindow(SW_SHOW);
			if (m_bChildMode)
			{
				m_btnOpen3.SetWindowText(_T("????????"));
				m_btnOpen3.SetToolTipText(_T("????????????????????????"));
				m_btnOpen3.ShowWindow(SW_SHOW);
			}else
			{
				m_nButtonCount -= 1;
				m_btnOpen3.ShowWindow(SW_HIDE);
			}
			m_btnOpen4.SetWindowText(_T("????"));
			m_btnOpen4.SetToolTipText(_T("????????????"));
			m_btnOpen4.ShowWindow(SW_SHOW);
		}break;
	case EB_MR_CTRL_DATA_TYPE_IMAGE:
		{
			m_btnOpen1.SetWindowText(_T("????"));
			m_btnOpen1.SetToolTipText(_T("????????"));
			m_btnOpen2.SetWindowText(_T("????????"));
			m_btnOpen2.SetToolTipText(_T("????????????????????"));
			m_btnOpen3.SetWindowText(_T("????"));
			m_btnOpen3.SetToolTipText(_T("????????????????"));
			m_btnOpen4.SetWindowText(_T("??????..."));
			m_btnOpen4.SetToolTipText(_T("??????????..."));
			m_btnOpen1.ShowWindow(SW_SHOW);
			m_btnOpen2.ShowWindow(SW_SHOW);
			m_btnOpen3.ShowWindow(SW_SHOW);
			m_btnOpen4.ShowWindow(SW_SHOW);
		}break;
	case EB_MR_CTRL_DATA_TYPE_FILE:
		{
			m_btnOpen1.SetWindowText(_T("????"));
			m_btnOpen1.SetToolTipText(_T("????????"));
			m_btnOpen2.SetWindowText(_T("????????"));
			m_btnOpen2.SetToolTipText(_T("????????????????"));
			m_btnOpen3.SetWindowText(_T("????"));
			m_btnOpen3.SetToolTipText(_T("????????????????"));
			m_btnOpen4.SetWindowText(_T("??????..."));
			m_btnOpen4.SetToolTipText(_T("??????????..."));
			m_btnOpen1.ShowWindow(SW_SHOW);
			m_btnOpen2.ShowWindow(SW_SHOW);
			m_btnOpen3.ShowWindow(SW_SHOW);
			m_btnOpen4.ShowWindow(SW_SHOW);
		}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			m_nButtonCount = 2;
			m_btnOpen3.SetWindowText(_T("????"));
			m_btnOpen3.SetToolTipText(_T("????????????????????"));
			m_btnOpen4.SetWindowText(_T("??????..."));
			m_btnOpen4.SetToolTipText(_T("??????????????????"));
			m_btnOpen1.ShowWindow(SW_HIDE);
			m_btnOpen2.ShowWindow(SW_HIDE);
			m_btnOpen3.ShowWindow(SW_SHOW);
			m_btnOpen4.ShowWindow(SW_SHOW);

			if (theApp.BuildChatCopySubscribeFuncList()>0)
			{
				for (size_t i=0;i<theApp.m_pChatCopySubscribeFuncList.size();i++)
				{
					const EB_SubscribeFuncInfo & pSubscribeFuncInfo = theApp.m_pChatCopySubscribeFuncList[i];
					if (i==0)
					{
						m_nButtonCount++;
						m_btnOpen1.SetWindowText(pSubscribeFuncInfo.m_sFunctionName.c_str());
						CString sTipText;
						sTipText.Format(_T("????????????%s"),pSubscribeFuncInfo.m_sFunctionName.c_str());
						m_btnOpen1.SetToolTipText(sTipText);
						m_btnOpen1.ShowWindow(SW_SHOW);
					}
					else if (i==1)
					{
						m_nButtonCount++;
						m_btnOpen2.SetWindowText(pSubscribeFuncInfo.m_sFunctionName.c_str());
						CString sTipText;
						sTipText.Format(_T("????????????%s"),pSubscribeFuncInfo.m_sFunctionName.c_str());
						m_btnOpen2.SetToolTipText(sTipText);
						m_btnOpen2.ShowWindow(SW_SHOW);
					}
					else
					{
						break;
					}
				}
			}

		}break;
	default:
		break;
	}
	if (m_nMsgId>0)
	{
		m_nButtonCount += 1;
		m_btnOpen5.SetWindowText(_T("????"));
		m_btnOpen5.SetToolTipText(_T("????????????????"));
		m_btnOpen5.ShowWindow(SW_SHOW);
		if (m_nMsgFromUserId==theApp.GetLogonUserId() && m_nMsgType!=MRT_RESOURCE && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0 && m_pCallInfo.GetCallId()>0)
		{
			m_nButtonCount += 1;
			m_btnOpen6.SetWindowText(_T("????"));
			m_btnOpen6.SetToolTipText(_T("????????"));
			m_btnOpen6.ShowWindow(SW_SHOW);
		}else
		{
			m_btnOpen6.ShowWindow(SW_HIDE);
		}
		if (m_pCallInfo.GetCallId()>0 && IsCanCollectRecordType((MSG_RECORD_TYPE)m_nMsgType) && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0)
		{
			m_nButtonCount += 1;
			m_btnOpen7.SetWindowText(_T("????"));
			m_btnOpen7.SetToolTipText(_T("??????????????????"));
			m_btnOpen7.ShowWindow(SW_SHOW);
			//if (m_pCallInfo.m_sGroupCode>0)
			//{
			//	m_nButtonCount += 1;
			//	m_btnOpen8.SetWindowText(_T("??????"));
			//	m_btnOpen8.SetToolTipText(_T("????????????????"));
			//	m_btnOpen8.ShowWindow(SW_SHOW);
			//}else
			{
				m_btnOpen8.ShowWindow(SW_HIDE);
			}
		}else
		{
			m_btnOpen7.ShowWindow(SW_HIDE);
			m_btnOpen8.ShowWindow(SW_HIDE);
		}
	}else
	{
		m_btnOpen5.ShowWindow(SW_HIDE);
		m_btnOpen6.ShowWindow(SW_HIDE);
		m_btnOpen7.ShowWindow(SW_HIDE);
		m_btnOpen8.ShowWindow(SW_HIDE);
	}
	m_btnOpen1.Invalidate();
	m_btnOpen2.Invalidate();
	m_btnOpen3.Invalidate();
	m_btnOpen4.Invalidate();
	m_btnOpen5.Invalidate();
	m_btnOpen6.Invalidate();
	m_btnOpen7.Invalidate();
	m_btnOpen8.Invalidate();
	theApp.InvalidateParentRect(&m_btnOpen1);
	theApp.InvalidateParentRect(&m_btnOpen2);
	theApp.InvalidateParentRect(&m_btnOpen3);
	theApp.InvalidateParentRect(&m_btnOpen4);
	theApp.InvalidateParentRect(&m_btnOpen5);
	theApp.InvalidateParentRect(&m_btnOpen6);
	theApp.InvalidateParentRect(&m_btnOpen7);
	theApp.InvalidateParentRect(&m_btnOpen8);
	return m_nButtonCount;
}
void CDlgToolbar::SetMsgHwnd(HWND hWnd, CToolbarCallback* pCallback)
{
	m_hMsgWnd = hWnd;
	m_pCallback = pCallback;
}
void CDlgToolbar::HideReset(void)
{
	if (this->GetSafeHwnd()!=NULL)
	{
		ShowWindow(SW_HIDE);
		m_nDataType = EB_MR_CTRL_DATA_TYPE_URL;
		m_sMoveEnterString.clear();
	}
}
void CDlgToolbar::SetChildMode(bool bChildMode)
{
	m_bChildMode = bChildMode;
}

// CDlgToolbar message handlers

BOOL CDlgToolbar::OnInitDialog()
{
	CEbDialogBase::OnInitDialog();

	// TODO:  Add extra initialization here

	this->GetDlgItem(IDC_BUTTON_NULL)->MoveWindow(0,0,0,0);
	m_btnOpen1.ShowWindow(SW_SHOW);
	m_btnOpen1.SetAutoSize(false);
	m_btnOpen1.SetTextHotMove(true);
	m_btnOpen1.SetDrawPanelRgn(false);
	m_btnOpen1.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen2.ShowWindow(SW_SHOW);
	m_btnOpen2.SetAutoSize(false);
	m_btnOpen2.SetTextHotMove(true);
	m_btnOpen2.SetDrawPanelRgn(false);
	m_btnOpen2.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen3.ShowWindow(SW_SHOW);
	m_btnOpen3.SetAutoSize(false);
	m_btnOpen3.SetTextHotMove(true);
	m_btnOpen3.SetDrawPanelRgn(false);
	m_btnOpen3.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen4.ShowWindow(SW_SHOW);
	m_btnOpen4.SetAutoSize(false);
	m_btnOpen4.SetTextHotMove(true);
	m_btnOpen4.SetDrawPanelRgn(false);
	m_btnOpen4.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen5.ShowWindow(SW_SHOW);
	m_btnOpen5.SetAutoSize(false);
	m_btnOpen5.SetTextHotMove(true);
	m_btnOpen5.SetDrawPanelRgn(false);
	m_btnOpen5.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen6.ShowWindow(SW_HIDE);
	m_btnOpen6.SetAutoSize(false);
	m_btnOpen6.SetTextHotMove(true);
	m_btnOpen6.SetDrawPanelRgn(false);
	m_btnOpen6.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen7.ShowWindow(SW_HIDE);
	m_btnOpen7.SetAutoSize(false);
	m_btnOpen7.SetTextHotMove(true);
	m_btnOpen7.SetDrawPanelRgn(false);
	m_btnOpen7.SetNorTextColor(theDefaultFlatBlackTextColor);
	m_btnOpen8.ShowWindow(SW_HIDE);
	m_btnOpen8.SetAutoSize(false);
	m_btnOpen8.SetTextHotMove(true);
	m_btnOpen8.SetDrawPanelRgn(false);
	m_btnOpen8.SetNorTextColor(theDefaultFlatBlackTextColor);

	SetCtrlColor(false);

	//const int POS_DLG_LOGIN_WIDTH = 80;
	//const int POS_DLG_LOGIN_HEIGHT = 42;
	//CRect rectClient;
	//this->GetWindowRect(&rectClient);
	//rectClient.right = rectClient.left + POS_DLG_LOGIN_WIDTH;
	//rectClient.bottom = rectClient.top + POS_DLG_LOGIN_HEIGHT;
	//this->MoveWindow(&rectClient);
	SetCircle();

	SetDlgChildFont(theDefaultDialogFontSize,theFontFace.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgToolbar::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CEbDialogBase::OnClose();
}

void CDlgToolbar::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CEbDialogBase::OnTimer(nIDEvent);
}
const int const_left_interval = 6;
const int const_top_interval = 6;
const int const_btn_width1 = 55;
const int const_btn_width2 = 55;
const int const_btn_height = 20;

void CDlgToolbar::OnPaint()
{
	if (IsIconic())
	{
		//CPaintDC dc(this); // ????????????????????

		//SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//// ????????????????????????
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;

		//// ????????
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // ????????????????????
		CRect rectClient;
		this->GetClientRect(&rectClient);
		CSkinMemDC memDC(&dc, rectClient);
		this->ClearBgDrawInfo();
		this->AddBgDrawInfo(CEbBackDrawInfo(0,1.0,false,false,0,theDefaultBtnWhiteColor));
		this->DrawPopBg(&memDC, theApp.GetMainColor(),1,0,0,theDefaultFlatLineColor);

		//Gdiplus::Pen pen(Gdiplus::Color(64,64,64));
		//Gdiplus::Graphics graphics(memDC.m_hDC);
		//if (m_nButtonCount>=2)
		//{
		//	const int x = const_left_interval+const_btn_width1*1+1;
		//	graphics.DrawLine(&pen,x,const_top_interval+2,x,const_top_interval+12);
		//}
		//if (m_nButtonCount>=3)
		//{
		//	const int x = const_left_interval+const_btn_width1*2+1;
		//	graphics.DrawLine(&pen,x,const_top_interval+2,x,const_top_interval+12);
		//}
		//if (m_nButtonCount>=4)
		//{
		//	const int x = const_left_interval+const_btn_width1*3+1;
		//	graphics.DrawLine(&pen,x,const_top_interval+2,x,const_top_interval+12);
		//}
	}
}

void CDlgToolbar::OnSize(UINT nType, int cx, int cy)
{
	CEbDialogBase::OnSize(nType, cx, cy);

	int x = const_left_interval;
	int y = const_top_interval;
	const int const_btn_interval = 0;
	switch (m_nDataType)
	{
	//case EB_MR_CTRL_DATA_TYPE_DELETE_MSGID:
	//	m_btnOpen1.MovePoint(x,y,const_btn_width2,const_btn_height);
	//	break;
	//case EB_MR_CTRL_DATA_TYPE_SEND_MSGID:
	//	{
	//		m_btnOpen1.MovePoint(x,y,const_btn_width2,const_btn_height);
	//		x += (const_btn_width2+const_btn_interval);
	//		m_btnOpen2.MovePoint(x,y,const_btn_width2,const_btn_height);
	//	}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			const size_t nChatCopyFuncSize = theApp.m_pChatCopySubscribeFuncList.size();
			if (nChatCopyFuncSize>=1)
			{
				m_btnOpen1.MovePoint(x,y,const_btn_width2,const_btn_height);
				x += (const_btn_width2+const_btn_interval);
			}
			if (nChatCopyFuncSize>=2)
			{
				m_btnOpen2.MovePoint(x,y,const_btn_width2,const_btn_height);
				x += (const_btn_width2+const_btn_interval);
			}
			m_btnOpen3.MovePoint(x,y,const_btn_width2,const_btn_height);
			x += (const_btn_width2+const_btn_interval);
			m_btnOpen4.MovePoint(x,y,const_btn_width2,const_btn_height);

		}break;
	default:
		{
			const bool bHideBtn1 = (theApp.GetHideMainFrame()&&m_nDataType==EB_MR_CTRL_DATA_TYPE_URL)?true:false;
			const bool bHideBtn3 = (!m_bChildMode&&m_nDataType==EB_MR_CTRL_DATA_TYPE_URL)?true:false;
			if (!bHideBtn1)
			{
				m_btnOpen1.MovePoint(x,y,const_btn_width1,const_btn_height);
				x += (const_btn_width1+const_btn_interval);
			}
			m_btnOpen2.MovePoint(x,y,const_btn_width1,const_btn_height);
			x += (const_btn_width1+const_btn_interval);
			if (!bHideBtn3)
			{
				m_btnOpen3.MovePoint(x,y,const_btn_width2,const_btn_height);
				x += (const_btn_width2+const_btn_interval);
			}
			m_btnOpen4.MovePoint(x,y,const_btn_width2,const_btn_height);
		}break;
	}

	if (m_nMsgId>0)
	{
		x += (const_btn_width1+const_btn_interval);
		m_btnOpen5.MovePoint(x,y,const_btn_width2,const_btn_height);
		if (m_nMsgFromUserId==theApp.GetLogonUserId() && m_nMsgType!=MRT_RESOURCE && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0 && m_pCallInfo.GetCallId()>0)
		{
			x += (const_btn_width1+const_btn_interval);
			m_btnOpen6.MovePoint(x,y,const_btn_width2,const_btn_height);
		}
		if (m_pCallInfo.GetCallId()>0 && IsCanCollectRecordType((MSG_RECORD_TYPE)m_nMsgType) && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0)
		{
			x += (const_btn_width1+const_btn_interval);
			m_btnOpen7.MovePoint(x,y,const_btn_width2,const_btn_height);
			//if (m_pCallInfo.m_sGroupCode>0)
			//{
			//	x += (const_btn_width1+const_btn_interval);
			//	m_btnOpen8.MovePoint(x,y,const_btn_width2,const_btn_height);
			//}
		}
	}
}

void CDlgToolbar::OnBnClickedBtn1()
{
	if (m_sMoveEnterString.empty() && m_nDataType!=EB_MR_CTRL_DATA_TYPE_SELECT_STRING)
		return;

	switch (m_nDataType)
	{
	//case EB_MR_CTRL_DATA_TYPE_DELETE_MSGID:
	//case EB_MR_CTRL_DATA_TYPE_SEND_MSGID:
	//	{
	//		// ????????????????
	//		const mycp::bigint nMsgId = cgc_atoi64(m_sMoveEnterString.c_str());

	//	}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			const tstring sSelectString(m_pCallback->GetSelectString());
			if (!sSelectString.empty() && theApp.m_pChatCopySubscribeFuncList.size()>=1)
			{
				const EB_SubscribeFuncInfo& pSubscribeFuncInfo = theApp.m_pChatCopySubscribeFuncList[0];
				if (theApp.OpenSubscribeFuncWindow(pSubscribeFuncInfo,libEbc::ACP2UTF8(sSelectString.c_str()),"",NULL))
				{
					HideReset();
				}
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_URL:
		{
			COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(m_sMoveEnterString.string(),"");
			pOpenAppUrlInfo->m_bSaveBrowseTitle = true;
			theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
			HideReset();
		}break;
	case EB_MR_CTRL_DATA_TYPE_IMAGE:
		{
			if (::PathFileExists(m_sMoveEnterString.c_str()))
			{
				if (m_sMoveEnterString.find(".")==std::string::npos)
				{
					const CString& strSystemDir = theApp.GetSysPath();
					const CString strRundll = strSystemDir + "\\rundll32.exe";
					CString strParm;
					strParm.Format("%s//shimgvw.dll imageview_fullscreen %s", strSystemDir, m_sMoveEnterString.c_str());
					COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo((LPCTSTR)strRundll,(LPCTSTR)strParm,"");
					theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
					//ShellExecute(NULL, "Open", strRundll, strParm, NULL, SW_SHOW);
				}else
				{
					COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(m_sMoveEnterString.string(),"",m_sMoveEnterString.string());
					theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
					//ShellExecute(NULL, "open", m_sMoveEnterString.c_str(), NULL, m_sMoveEnterString.c_str(),SW_SHOW);
				}
			}else
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
			}
			HideReset();
		}break;
	case EB_MR_CTRL_DATA_TYPE_FILE:
		{
			if (::PathFileExists(m_sMoveEnterString.c_str()))
			{
				COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(m_sMoveEnterString.string(),"",m_sMoveEnterString.string());
				theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
				//ShellExecute(NULL, "open", m_sMoveEnterString.c_str(), NULL, m_sMoveEnterString.c_str(),SW_SHOW);
			}else
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
			}
			HideReset();
		}break;
	default:
		break;
	}
	this->GetDlgItem(IDC_BUTTON_NULL)->SetFocus();
}
int CopyFileToClipboard(const char szFileName[])
{
	UINT uDropEffect;
	HGLOBAL hGblEffect;
	LPDWORD lpdDropEffect;
	DROPFILES stDrop;

	HGLOBAL hGblFiles;
	LPSTR lpData;

	uDropEffect = RegisterClipboardFormat("Preferred DropEffect");
	hGblEffect = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE,sizeof(DWORD));
	lpdDropEffect = (LPDWORD)GlobalLock(hGblEffect);
	*lpdDropEffect = DROPEFFECT_COPY;//????; ????????DROPEFFECT_MOVE
	GlobalUnlock(hGblEffect);

	stDrop.pFiles = sizeof(DROPFILES);
	stDrop.pt.x = 0;
	stDrop.pt.y = 0;
	stDrop.fNC = FALSE;
	stDrop.fWide = FALSE;

	hGblFiles = GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE,\
		sizeof(DROPFILES)+strlen(szFileName)+2);
	lpData = (LPSTR)GlobalLock(hGblFiles);
	memcpy(lpData,&stDrop,sizeof(DROPFILES));
	strcpy(lpData+sizeof(DROPFILES),szFileName);
	GlobalUnlock(hGblFiles);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_HDROP,hGblFiles);
	SetClipboardData(uDropEffect,hGblEffect);
	CloseClipboard();

	return 1;
}
void CDlgToolbar::OnBnClickedBtn2()
{
	if (m_sMoveEnterString.empty() && m_nDataType!=EB_MR_CTRL_DATA_TYPE_SELECT_STRING)
		return;
	switch (m_nDataType)
	{
	//case EB_MR_CTRL_DATA_TYPE_DELETE_MSGID:
	//	{
	//		// disable
	//	}break;
	//case EB_MR_CTRL_DATA_TYPE_SEND_MSGID:
	//	{
	//		// ????????????
	//		const mycp::bigint nMsgId = cgc_atoi64(m_sMoveEnterString.c_str());
	//		if (nMsgId==0 || this->m_pCallInfo.GetCallId()==0) break;
	//		theEBAppClient.EB_RequestWithdawMsg(m_pCallInfo.GetCallId(), nMsgId);
	//	}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			const tstring sSelectString(m_pCallback->GetSelectString());
			if (!sSelectString.empty() && theApp.m_pChatCopySubscribeFuncList.size()>=2)
			{
				const EB_SubscribeFuncInfo& pSubscribeFuncInfo = theApp.m_pChatCopySubscribeFuncList[1];
				if (theApp.OpenSubscribeFuncWindow(pSubscribeFuncInfo,libEbc::ACP2UTF8(sSelectString.c_str()),"",NULL))
				{
					HideReset();
				}
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_URL:
		{
			COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(m_sMoveEnterString.string(),"",m_sMoveEnterString.string());
			theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
			//ShellExecute(NULL, "open", m_sMoveEnterString.c_str(), NULL, m_sMoveEnterString.c_str(),SW_SHOW);
			HideReset();
		}break;
	case EB_MR_CTRL_DATA_TYPE_IMAGE:
	case EB_MR_CTRL_DATA_TYPE_FILE:
		{
			if (::PathFileExists(m_sMoveEnterString.c_str()))
			{
				tstring sPath = "/select, \""+m_sMoveEnterString;
				sPath += "\"";
				//COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo("explorer",sPath.string(),"");
				//theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
				ShellExecute(NULL, NULL, "explorer", sPath.c_str(), NULL, SW_SHOW);
			}else
			{
				const std::string::size_type find = m_sMoveEnterString.rfind('\\');
				if (find!=std::wstring::npos)
				{
					const tstring sPath = m_sMoveEnterString.substr(0,find+1);
					//COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(sPath.string(),"",sPath.string());
					//theApp.m_pMainWnd->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
					ShellExecute(NULL, "open", sPath.c_str(), NULL, sPath.c_str(), SW_SHOW);
				}
			}
			HideReset();
		}break;
	default:
		break;
	}
	this->GetDlgItem(IDC_BUTTON_NULL)->SetFocus();
}
void CDlgToolbar::OnBnClickedBtn3()
{
	switch (m_nDataType)
	{
	case EB_MR_CTRL_DATA_TYPE_URL:
		{
			if (m_sMoveEnterString.empty())
				return;
			COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(m_sMoveEnterString.string(),"");
			pOpenAppUrlInfo->m_bSaveBrowseTitle = true;
			::PostMessage(m_hMsgWnd,EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
			HideReset();
		}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			const tstring sSelectString(m_pCallback->GetSelectString());
			if( OpenClipboard() )
			{
				EmptyClipboard();
				HGLOBAL clipbuffer = GlobalAlloc(GMEM_DDESHARE, sSelectString.size()+1);
				char * buffer = (char*)GlobalLock(clipbuffer);
				strcpy(buffer, sSelectString.c_str());
				GlobalUnlock(clipbuffer);
				SetClipboardData(CF_TEXT,clipbuffer);
				CloseClipboard();
				HideReset();
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_IMAGE:
		{
			// ??????????
			if (!::PathFileExists(m_sMoveEnterString.c_str()))
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
				break;
			}
			if ( OpenClipboard() )
			{
				USES_CONVERSION;
				Gdiplus::Bitmap * pImage = Gdiplus::Bitmap::FromFile(A2W(m_sMoveEnterString.c_str()),FALSE);
				if (pImage!=NULL)
				{
					EmptyClipboard();
					// **???????????? WORD QQ ????????????
					PAINTSTRUCT ps;
					HDC hDC = ::BeginPaint(this->GetSafeHwnd(),&ps);
					HDC dcMem = ::CreateCompatibleDC(hDC);
					HBITMAP bitmap = ::CreateCompatibleBitmap(hDC,pImage->GetWidth(),pImage->GetHeight());
					SelectObject(dcMem,(HGDIOBJ)bitmap);
					Gdiplus::Graphics graphics(dcMem);
					graphics.DrawImage(pImage,0,0,pImage->GetWidth(),pImage->GetHeight());
					SetClipboardData(CF_BITMAP,bitmap);
					CloseClipboard();
					EndPaint(&ps);
					DeleteObject(bitmap);
					DeleteDC(dcMem);
					delete pImage;
					HideReset();
				}else
				{
					CloseClipboard();
					CDlgMessageBox::EbMessageBox(this,"","??????????????\r\n????????",CDlgMessageBox::IMAGE_WARNING,5);
				}
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_FILE:
		{
			// ????????
			if (!::PathFileExists(m_sMoveEnterString.c_str()))
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
				break;
			}
			CopyFileToClipboard(m_sMoveEnterString.c_str());
			HideReset();
		}break;
	default:
		break;
	}
	this->GetDlgItem(IDC_BUTTON_NULL)->SetFocus();
}
void CDlgToolbar::OnBnClickedBtn4()
{
	switch (m_nDataType)
	{
	case EB_MR_CTRL_DATA_TYPE_URL:
		{
			if (m_sMoveEnterString.empty())
				return;
			if( OpenClipboard() )
			{
				EmptyClipboard();
				HGLOBAL clipbuffer;
				clipbuffer = GlobalAlloc(GMEM_DDESHARE, m_sMoveEnterString.size()+1);
				char * buffer = (char*)GlobalLock(clipbuffer);
				strcpy(buffer, m_sMoveEnterString.c_str());
				GlobalUnlock(clipbuffer);
				SetClipboardData(CF_TEXT,clipbuffer);
				CloseClipboard();
				HideReset();
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_IMAGE:
		{
			if (!::PathFileExists(m_sMoveEnterString.c_str()))
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
				break;
			}
			const tstring sStringTemp(m_sMoveEnterString);

			// ????????
			wchar_t szFileName[MAX_PATH*2] = {0} ; 
			const time_t tNow = time(0);
			const struct tm *newtime = localtime(&tNow);
			_swprintf(szFileName,L"EB????%04d%02d%02d%02d%02d%02d",newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec);

			OPENFILENAMEW ofn={0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = m_hWnd;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof(szFileName);
			ofn.lpstrFilter = L"PNG (*.png)\0*.png\0JPEG (*.jpg)\0*.jpg\0BMP (*.bmp)\0*.bmp\0\0";
			ofn.lpstrDefExt = L"png";
			ofn.Flags = OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST;
			if (GetSaveFileNameW(&ofn)==TRUE ) 
			{
				std::wstring sExt(ofn.lpstrFile);
				sExt = sExt.substr(sExt.size()-3);
				CLSID                           codecClsid;
				if (sExt==L"png" || sExt==L"PNG")
					libEbc::GetCodecClsid(L"image/png",   &codecClsid);
				else if (sExt==L"bmp" || sExt==L"BMP")
					libEbc::GetCodecClsid(L"image/bmp",   &codecClsid);
				else
					libEbc::GetCodecClsid(L"image/jpeg",   &codecClsid);

				USES_CONVERSION;
				Gdiplus::Image   image(A2W(sStringTemp.c_str()));
				image.Save(ofn.lpstrFile, &codecClsid);
				HideReset();
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_FILE:
		{
			if (!::PathFileExists(m_sMoveEnterString.c_str()))
			{
				CString sText;
				sText.Format(_T("????????????????\r\n%s"),m_sMoveEnterString.c_str());
				CDlgMessageBox::EbMessageBox(this,"",sText,CDlgMessageBox::IMAGE_WARNING,5);
				break;
			}
			const tstring sStringTemp(m_sMoveEnterString);
			const tstring sFileName(libEbc::GetFileName(sStringTemp));
			tstring sNameTemp;
			tstring sFileExt;
			libEbc::GetFileExt(sFileName,sNameTemp,sFileExt);

			// ????????
			char szFileName[MAX_PATH*2] = {0} ; 
			strcpy(szFileName,sFileName.c_str());
			char sFilter[120];
			if (sFileExt.empty())
				strcpy(sFilter,"All Files (*.*)\0*.*\0\0");
			else
			{
				std::transform(sFileExt.begin(), sFileExt.end(), sFileExt.begin(), tolower);
				tstring sFileExtUpper(sFileExt);
				std::transform(sFileExtUpper.begin(), sFileExtUpper.end(), sFileExtUpper.begin(), toupper);
				sprintf(sFilter,"%s (*.%s)\0*.%s\0All Files (*.*)\0*.*\0\0",sFileExtUpper.c_str(),sFileExt.c_str(),sFileExt.c_str());
			}

			OPENFILENAME ofn={0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = m_hWnd;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof(szFileName);
			ofn.lpstrFilter = sFilter;
			ofn.lpstrDefExt = sFileExt.c_str();
			ofn.Flags = OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST;
			if (GetSaveFileName(&ofn)==TRUE ) 
			{
				CopyFile(sStringTemp.c_str(),ofn.lpstrFile,FALSE);
				HideReset();
			}
		}break;
	case EB_MR_CTRL_DATA_TYPE_SELECT_STRING:
		{
			const tstring sSelectString(m_pCallback->GetSelectString());
			if (sSelectString.empty())
			{
				//HideReset();
				break;
			}
			TCHAR szFileName[MAX_PATH*2] = {0} ; 
			const time_t tNow = time(0);
			const struct tm *newtime = localtime(&tNow);
			sprintf(szFileName,"EB????%04d%02d%02d%02d%02d%02d",newtime->tm_year+1900,newtime->tm_mon+1,newtime->tm_mday,newtime->tm_hour,newtime->tm_min,newtime->tm_sec);

			OPENFILENAME ofn={0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = m_hWnd;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = sizeof(szFileName);
			ofn.lpstrFilter = "????????(*.txt)\0\0";
			ofn.lpstrDefExt = "txt";   
			ofn.Flags = OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST;
			if (GetSaveFileName(&ofn)==TRUE ) 
			{
				FILE * f = fopen(ofn.lpstrFile,"w");
				if (f!=NULL)
				{
					fwrite(sSelectString.c_str(),1,sSelectString.size(),f);
					fclose(f);
					// open it
					ShellExecute(NULL, "open", ofn.lpstrFile, NULL, NULL,SW_SHOW);
					HideReset();
				}
			}
		}break;
	default:
		break;
	}
	this->GetDlgItem(IDC_BUTTON_NULL)->SetFocus();
}
void CDlgToolbar::OnBnClickedBtn5()
{
	if (m_nMsgId>0)
	{
		HideReset();
		// ????????????????
		if (m_pCallback!=NULL)
		{
			if (CDlgMessageBox::EbDoModal(this,"????????????","????????????????????????",CDlgMessageBox::IMAGE_QUESTION)==IDOK)
			{
				m_pCallback->OnDeleteMsg(m_nMsgId);
			}
		}
	}
}

void CDlgToolbar::OnBnClickedBtn6()
{
	if (m_nMsgId==0) return;
	if (m_nMsgFromUserId==theApp.GetLogonUserId() && m_nMsgType!=MRT_RESOURCE && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0 && m_pCallInfo.GetCallId()>0)
	{
		HideReset();
		theEBAppClient.EB_RequestWithdrawMsg(m_pCallInfo.GetCallId(), m_nMsgId);
	}
}
void CDlgToolbar::OnBnClickedBtn7()
{
	if (m_nMsgId==0) return;
	if (m_pCallInfo.GetCallId()>0 && IsCanCollectRecordType((MSG_RECORD_TYPE)m_nMsgType) && (m_nMsgReadFlag&EBC_READ_FLAG_WITHDRAW)==0)
	{
		// ????????
		HideReset();
		theEBAppClient.EB_RequestCollectMsg(m_pCallInfo.GetCallId(), m_nMsgId, false);
	}
}
void CDlgToolbar::OnBnClickedBtn8()
{
	//if (m_nMsgId==0) return;
	//if (m_pCallInfo.GetCallId()>0 && m_pCallInfo.m_sGroupCode>0)
	//{
	//	HideReset();
	//	theEBAppClient.EB_RequestCollectMsg(m_pCallInfo.GetCallId(), m_nMsgId, true);
	//}
}
