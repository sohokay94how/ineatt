// PanelSearch.cpp : implementation file
//

#include "stdafx.h"
#include "POP.h"
#include "PanelSearch.h"
#include "PanelSearchResult.h"

#define TIMERID_EDIT_SEARCH				0x137
#define TIMERID_CALL_SEARCH_SEL_ALL		0x13A
#define TIMERID_SELECT_FIRST_SEARCH		0x13B

// CPanelSearch dialog

IMPLEMENT_DYNAMIC(CPanelSearch, CEbDialogBase)

CPanelSearch::CPanelSearch(CWnd* pParent /*=NULL*/)
	: CEbDialogBase(CPanelSearch::IDD, pParent)
{
	m_bParentMouseMove = FALSE;
	m_bCanSearch = true;
	m_pPanelSearchResult = NULL;

}

CPanelSearch::~CPanelSearch()
{
}

void CPanelSearch::DoDataExchange(CDataExchange* pDX)
{
	CEbDialogBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_GOBACK, m_btnGoBack);
	DDX_Control(pDX, IDC_BUTTON_GOFORWARD, m_btnGoForward);
	DDX_Control(pDX, IDC_BUTTON_REFRESH, m_btnRefresh);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_OPTIONS, m_btnOptions);
	DDX_Control(pDX, IDC_EDIT_SEARCH, m_editSearch);
}


BEGIN_MESSAGE_MAP(CPanelSearch, CEbDialogBase)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CPanelSearch::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CPanelSearch::OnBnClickedButtonStop)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CPanelSearch::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDC_BUTTON_OPTIONS, &CPanelSearch::OnBnClickedButtonOptions)
	ON_BN_CLICKED(IDC_BUTTON_GOBACK, &CPanelSearch::OnBnClickedButtonGoback)
	ON_BN_CLICKED(IDC_BUTTON_GOFORWARD, &CPanelSearch::OnBnClickedButtonGoforward)
	ON_WM_DESTROY()
	ON_COMMAND(EB_COMMAND_CLEAR_CHROME_TEMPFILE, &OnCmdClearChromeTempFile)
	ON_COMMAND(EB_COMMAND_CLEAR_IE_TEMPFILE, &OnCmdClearIeTempFile)
	ON_COMMAND(EB_COMMAND_SAVE_HISTORY, &OnCmdSaveHistory)
	ON_COMMAND(EB_COMMAND_CLEAR_HISTORY, &OnCmdClearHistory)
	ON_COMMAND(EB_COMMAND_CHANGE_BROWSER_TYPE, &OnCmdChangeBrowserType)
	ON_COMMAND(EB_COMMAND_FILE_MANAGER, &OnCmdFileManager)
	ON_COMMAND(EB_COMMAND_SEARCH_BAIDU, &OnCmdSearchBaidu)
	ON_COMMAND(EB_COMMAND_SEARCH_SOGOU, &OnCmdSearchSogou)
	ON_COMMAND(EB_COMMAND_SEARCH_360, &OnCmdSearch360)
	ON_MESSAGE(EB_COMMAND_CHANGE_APP_URL, OnMsgChangeAppUrl)
	ON_MESSAGE(EB_COMMAND_SEARCH_SET_FOCUS_SEL, OnMsgSearchSetFocusSel)
	ON_MESSAGE(EB_COMMAND_SHOW_REFRESH_OR_STOP, OnMsgShowRefreshOrStop)
	//ON_WM_INITMENUPOPUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CPanelSearch message handlers

void CPanelSearch::SetSearchEditShow(bool bShow)
{
	m_editSearch.ShowWindow(bShow?SW_SHOW:SW_HIDE);
}

void CPanelSearch::OnBnClickedButtonRefresh()
{
	this->GetParent()->PostMessage(EB_COMMAND_REFRESH_OR_STOP_URL);
}
void CPanelSearch::OnBnClickedButtonStop()
{
	this->GetParent()->PostMessage(EB_COMMAND_REFRESH_OR_STOP_URL);
}
void CPanelSearch::OnSize(UINT nType, int cx, int cy)
{
	CEbDialogBase::OnSize(nType, cx, cy);
	const int const_btn_width = 18;
	int x = 0;
	m_btnGoBack.MovePoint(x,0);
	x += const_btn_width+2;
	m_btnGoForward.MovePoint(x,0);
	x += const_btn_width+2;
	m_btnRefresh.MovePoint(x,0);
	if (m_btnStop.GetSafeHwnd()!=NULL)
	{
		m_btnStop.MoveWindow(x,0,const_btn_width,const_btn_width);
	}
	//x += const_btn_width+2;
	//m_btnOptions.MovePoint(x,0);
	const int const_search_width = cx-x-const_btn_width*2-12;
	if (m_editSearch.GetSafeHwnd()!=NULL)
	{
		x += const_btn_width+4;
		m_editSearch.MoveWindow(x,0,const_search_width,21);
	}
	x += const_search_width+2;
	m_btnOptions.MovePoint(x,0);
	this->HideSearchResult();
	//if (m_pPanelSearchResult!=NULL && m_pPanelSearchResult->GetSafeHwnd()!=NULL && m_pPanelSearchResult->IsWindowVisible())
	//{
	//	CRect searchRect;
	//	m_editSearch.GetWindowRect(&searchRect);
	//	//CRect rect;
	//	//this->GetParent()->GetWindowRect(&rect);
	//	//searchRect.right = rect.right;
	//	searchRect.top = searchRect.bottom+2;
	//	searchRect.bottom = cy-1;
	//	m_pPanelSearchResult->MoveWindow(&searchRect);
	//}
}

BOOL CPanelSearch::OnInitDialog()
{
	CEbDialogBase::OnInitDialog();
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW,0);
	//this->EnableToolTips();
	//this->SetToolTipText(IDC_BUTTON_GOBACK,_T("ת����һҳ"));

	this->SetMouseMove(FALSE);
	this->SetParentMouseMove(TRUE);
	//this->EnableToolTips();
	//this->SetToolTipText(IDC_EDIT_SEARCH,_T("�����û����ʺš���ϵ�˺������¼������/��������Ӧ��"));

	//this->SetBgColor(RGB(255,255,255));
	m_btnGoBack.Load(IDB_PNG_BTN_GOBACK72X18);
	m_btnGoBack.SetWindowText(_T(""));
	m_btnGoBack.SetToolTipText(_T("ת����һҳ"));
	m_btnGoForward.Load(IDB_PNG_BTN_GOFORWARD72X18);
	m_btnGoForward.SetWindowText(_T(""));
	m_btnGoForward.SetToolTipText(_T("ת����һҳ"));
	m_btnRefresh.Load(IDB_PNG_BTN_REFRESH72X18);
	m_btnRefresh.SetWindowText(_T(""));
	m_btnRefresh.SetToolTipText(_T("ˢ�£�F5��"));
	m_btnStop.SetDrawClosePic(true,RGB(224,224,223),theDefaultBtnCloseColor,-1,-1,2,4);
	m_btnStop.SetWindowText(_T(""));
	m_btnStop.SetToolTipText(_T("ֹͣ����"));
	OnMsgShowRefreshOrStop(1,0);	// 1=show fresh
	m_btnOptions.Load(IDB_PNG_BTN_ARROWDOWN72X18);
	m_btnOptions.SetWindowText(_T(""));
	m_btnOptions.SetToolTipText(_T("ѡ��"));

	m_editSearch.SetRectangleColor(theApp.GetMainColor(),theDefaultFlatLineColor);
	//m_editSearch.SetRectangleColor(theApp.GetMainColor(),theDefaultFlatBgColor);
	m_editSearch.SetTextColor(RGB(61,61,61));
	//m_editSearch.SetPromptText(_T("�����û��������¼������Ӧ��(/)"));

	this->SetCircle(false);
	SetDlgChildFont(theDefaultDialogFontSize,theFontFace.c_str());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CPanelSearch::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	CRect rectClient;
	this->GetClientRect(&rectClient);
	CSkinMemDC memDC(&dc, rectClient);
	this->ClearBgDrawInfo();
	this->DrawPopBg(&memDC, theDefaultFlatBgColor,0);
	//this->DrawPopBg(&memDC, RGB(255,255,255),0);
	m_editSearch.Invalidate();
}

void CPanelSearch::OnBnClickedButtonOptions()
{
	const bool bCanSaveHistory = this->GetParent()->SendMessage(EB_COMMAND_QUERY_CAN_SAVE_HISTORY)==1?true:false;
#ifdef USES_LIBCEF
	const EB_BROWSER_TYPE nCurrentBrowserType = (EB_BROWSER_TYPE)this->GetParent()->SendMessage(EB_COMMAND_QUERY_BROWSER_TYPE);
	CString sChangeBrowserText;
	if (nCurrentBrowserType==EB_BROWSER_TYPE_CEF)
	{
		if (theApp.GetIeException())
			sChangeBrowserText = _T("��ǰ�ȸ� &Chrome �������ʾ");
		else
			sChangeBrowserText = _T("�л�΢�� I&E �������ʾ");
	}else
	{
		sChangeBrowserText = _T("�л��ȸ� &Chrome �������ʾ");
	}
#endif
	CNewMenu m_pOptionsMenu;
	//CNewMenu pSearchMenu;
	//if (pSearchMenu.GetSafeHmenu()==NULL)
	//{
	//	pSearchMenu.CreatePopupMenu();
	//	pSearchMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_SEARCH_BAIDU,_T("�ٶ�����(&B)"));
	//	pSearchMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_SEARCH_SOGOU,_T("�ѹ�����(&S)"));
	//	pSearchMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_SEARCH_360,_T("360����(&3)"));
	//}

	if (m_pOptionsMenu.GetSafeHmenu()==NULL)
	{
		m_pOptionsMenu.CreatePopupMenu();
#ifdef USES_LIBCEF
		//m_pOptionsMenu.SetBitmapBackground(RGB(192,192,192));
		const UINT nUID = nCurrentBrowserType==EB_BROWSER_TYPE_CEF?IDB_BITMAP_BROWSER_IE:IDB_BITMAP_BROWSER_CHROME;
		m_pOptionsMenu.InsertODMenu(0, sChangeBrowserText, MF_BYPOSITION , EB_COMMAND_CHANGE_BROWSER_TYPE, nUID);
		//m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_CHANGE_BROWSER_TYPE,sChangeBrowserText,ConvertIconToBitmap(hIcon));
		m_pOptionsMenu.AppendMenu(MF_SEPARATOR);
#endif
		m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_SAVE_HISTORY,_T("���浱ǰ�����¼"));
		m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_CLEAR_HISTORY,_T("������������¼"));
		m_pOptionsMenu.AppendMenu(MF_SEPARATOR);
#ifdef USES_LIBCEF
		m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_CLEAR_CHROME_TEMPFILE,_T("��� Chrome ���ػ���..."));
#endif
		m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_CLEAR_IE_TEMPFILE,_T("��� IE ��ʷ��¼..."));
	}else
	{
#ifdef USES_LIBCEF
		m_pOptionsMenu.ModifyODMenu(0,MF_BYPOSITION,EB_COMMAND_CHANGE_BROWSER_TYPE,sChangeBrowserText);
		//m_pOptionsMenu.ModifyMenu(0,MF_BYPOSITION,EB_COMMAND_CHANGE_BROWSER_TYPE,sChangeBrowserText);
#endif
	}
	//m_pOptionsMenu.AppendMenu(MF_SEPARATOR);
	//m_pOptionsMenu.AppendMenu(MF_POPUP,(UINT)pSearchMenu.m_hMenu,_T("����"));
	m_pOptionsMenu.AppendMenu(MF_SEPARATOR);
	m_pOptionsMenu.AppendMenu(MF_BYCOMMAND,EB_COMMAND_FILE_MANAGER,_T("�ļ��������"));

	m_pOptionsMenu.EnableMenuItem(EB_COMMAND_SAVE_HISTORY,bCanSaveHistory?MF_BYCOMMAND|MF_ENABLED:MF_BYCOMMAND|MF_GRAYED);
	const bool bExistHistoryUrl = theApp.m_pBoUsers->select("SELECT last_time FROM url_record_t LIMIT 1;")>0?true:false;
	m_pOptionsMenu.EnableMenuItem(EB_COMMAND_CLEAR_HISTORY,bExistHistoryUrl?MF_BYCOMMAND|MF_ENABLED:MF_BYCOMMAND|MF_GRAYED);

	CPoint point;
	GetCursorPos(&point);
#ifdef USES_SUPPORT_UI_STYLE
	m_pOptionsMenu.TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTALIGN,point.x,point.y,this);
#else
	m_pOptionsMenu.TrackPopupMenu(TPM_LEFTBUTTON|TPM_LEFTALIGN,point.x,point.y,this);
#endif
}

void CPanelSearch::OnBnClickedButtonGoback()
{
	this->GetParent()->PostMessage(EB_COMMAND_GO_BACK);
}

void CPanelSearch::OnBnClickedButtonGoforward()
{
	this->GetParent()->PostMessage(EB_COMMAND_GO_FORWARD);
}

void CPanelSearch::OnDestroy()
{
	//if (m_pOptionsMenu.GetSafeHmenu()!=NULL)
	//	m_pOptionsMenu.DestroyMenu();

	if (m_pPanelSearchResult!=NULL)
	{
		m_pPanelSearchResult->DestroyWindow();
		delete m_pPanelSearchResult;
		m_pPanelSearchResult = NULL;
	}
	CEbDialogBase::OnDestroy();
}
//bool DeleteDirectory(const char* strDirName,bool bDeleteRootDir)
//{
//	CFileFind tempFind;
//	char strTempFileFind[MAX_PATH];
//	sprintf(strTempFileFind,"%s\\*.*", strDirName);
//	BOOL IsFinded = tempFind.FindFile(strTempFileFind);
//	while (IsFinded)
//	{
//		IsFinded = tempFind.FindNextFile();
//		if (!tempFind.IsDots()) 
//		{
//			if (tempFind.IsDirectory())
//			{
//				if (!DeleteDirectory(tempFind.GetFilePath(),true))
//					continue;//return false;
//			}
//			else
//			{
//				if (!DeleteFile(tempFind.GetFilePath()))
//					continue;
//			}
//		}
//	}
//	tempFind.Close();
//	if (!bDeleteRootDir) return true;
//
//	if(!RemoveDirectory(strDirName))
//	{
//		return false;
//	}
//	return true;
//}
//#include "wininet.h"
//#include "UrlHist.h"
//
////BOOL DeleteUrlCache(DEL_CACHE_TYPE type);
////BOOL EmptyDirectory(LPCTSTR szPath, BOOL bDeleteDesktopIni = FALSE, BOOL bWipeIndexDat = FALSE);
////���һ��Ŀ¼BOOL IsWindowsNT();
////�ж�ϵͳBOOL IsWindows2k();BOOL GetUserSid(PSID* ppSid);
////void GetSidString(PSID pSid, LPTSTR szBuffer);
////BOOL GetOldSD(HKEY hKey, LPCTSTR pszSubKey, BYTE** pSD);
////BOOL CreateNewSD(PSID pSid, SECURITY_DESCRIPTOR* pSD, PACL* ppDacl);
////BOOL RegSetPrivilege(HKEY hKey, LPCTSTR pszSubKey, SECURITY_DESCRIPTOR* pSD, BOOL bRecursive);
////BOOL WipeFile(LPCTSTR szDir, LPCTSTR szFile); 
//BOOL DelTempFiles(void)
//{
//	BOOL bResult = FALSE;
//	BOOL bDone = FALSE;
//	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;
//	DWORD dwTrySize, dwEntrySize = 4096;	// start buffer size
//	HANDLE hCacheDir = NULL;
//	DWORD dwError = ERROR_INSUFFICIENT_BUFFER;
//	do {
//		switch (dwError)
//		{
//			// need a bigger buffer 
//		case ERROR_INSUFFICIENT_BUFFER:
//			delete [] lpCacheEntry;
//			lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
//			lpCacheEntry->dwStructSize = dwEntrySize;
//			dwTrySize = dwEntrySize;
//			BOOL bSuccess;
//			if (hCacheDir == NULL)
//				bSuccess = (hCacheDir = FindFirstUrlCacheEntry(NULL, lpCacheEntry, &dwTrySize)) != NULL;
//			else
//				bSuccess = FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize);
//			if (bSuccess)
//				dwError = ERROR_SUCCESS;
//			else
//			{
//				dwError = GetLastError();
//				dwEntrySize = dwTrySize;
//				// use new size returned
//			}break;
//			// we are done 
//		case ERROR_NO_MORE_ITEMS:
//			bDone = TRUE;
//			bResult = TRUE;
//			break;
//			// we have got an entry 
//		case ERROR_SUCCESS: // don''''''''''''''''t delete cookie entry 
//			if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
//				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName); // get ready for next entry
//			dwTrySize = dwEntrySize;
//			if (FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize))
//				dwError = ERROR_SUCCESS;
//			else
//			{
//				dwError = GetLastError();
//				dwEntrySize = dwTrySize; // use new size returned 
//			}break; // unknown error 
//		default:
//			bDone = TRUE;
//			break;
//		}
//		if (bDone)
//		{
//			delete []lpCacheEntry;
//			if (hCacheDir)
//				FindCloseUrlCache(hCacheDir);
//		}
//	} while (!bDone);
//	return bResult;
//} 

void CPanelSearch::OnCmdClearChromeTempFile()
{
	if (CDlgMessageBox::EbDoModal(this,_T("��� Chrome ���ػ���"),_T("��ȷ��Ҫ��� Chrome ��������ػ�����"),CDlgMessageBox::IMAGE_QUESTION,false,0)==IDOK)
	{
#ifdef USES_LIBCEF_USER_CACHE
		WritePrivateProfileString("default","clear_chrome_cache","1",theApp.GetUserSettingIniFile());
#else
		WritePrivateProfileString("system","clear_chrome_cache","1",theApp.GetSettingIniFile());
#endif
		CDlgMessageBox::EbMessageBox(this,"","�������ɹ���\r\n�����ͻ��˺���Ч��",CDlgMessageBox::IMAGE_INFORMATION,3);
	}
	//deleteDir(theApp.GetCefCachePath());
}
void CPanelSearch::OnCmdClearIeTempFile()
{
	if (CDlgMessageBox::EbDoModal(this,_T("��� IE ��ʷ��¼"),_T("��ȷ��Ҫ��� IE �������ʷ��¼��"),CDlgMessageBox::IMAGE_QUESTION,false,0)!=IDOK)
		return;

	// ���IE��ʱ�ļ�
	//����ClearMyTracksByProcess �ɽ���ѡ������ ��
	//Temporary Internet Files  ��Internet��ʱ�ļ���
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 8
	//Cookies
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 2
	//History (��ʷ��¼)
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 1
	// Form. Data �������ݣ�
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 16
	// Passwords (���룩
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 32
	// Delete All  ��ȫ��ɾ����
	//RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 255
	//
	//Delete All - "Also delete files and settings stored by add-ons"
	//
	//    RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 4351

	ShellExecute(NULL, "open", "rundll32.exe", " InetCpl.cpl,ClearMyTracksByProcess 255", "", SW_HIDE);

	//// 1�����IE��ʱ�ļ�
	//TCHAR szPath[MAX_PATH];
	//if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE, FALSE))
	//{
	//	//�õ���ʱĿ¼���������.
	//	DeleteDirectory(szPath,true);
	//}
	////DelTempFiles();
	//// 2��Cookie�����
	//if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_COOKIES, FALSE))
	//{
	//	//�õ�Ŀ¼������� 
	//	DeleteDirectory(szPath,true);
	//}

}

void CPanelSearch::OnCmdSaveHistory()
{
#ifdef USES_LIBCEF
	this->GetParent()->PostMessage(EB_COMMAND_SAVE_HISTORY);
#endif
}
void CPanelSearch::OnCmdClearHistory()
{
	theApp.m_pBoUsers->execute("DELETE FROM url_record_t;");
	//DeleteDirectory(theApp.GetAppImgTempPath(),false);
}
void CPanelSearch::OnCmdChangeBrowserType()
{
	this->GetParent()->PostMessage(EB_COMMAND_CHANGE_BROWSER_TYPE);
}
void CPanelSearch::OnCmdSearchBaidu()
{
	COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo("https://www.baidu.com","");
	pOpenAppUrlInfo->m_bSaveBrowseTitle = false;
	theApp.GetMainWnd()->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
}
void CPanelSearch::OnCmdSearchSogou()
{
	COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo("https://www.sogou.com","");
	pOpenAppUrlInfo->m_bSaveBrowseTitle = false;
	theApp.GetMainWnd()->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
}
void CPanelSearch::OnCmdSearch360()
{
	COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo("https://www.so.com","");
	pOpenAppUrlInfo->m_bSaveBrowseTitle = false;
	theApp.GetMainWnd()->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
}
void CPanelSearch::OnCmdFileManager()
{
	theApp.GetMainWnd()->PostMessage(EB_COMMAND_FILE_MANAGER, 0, 0);
}

//
//CBitmap* CPanelSearch::ConvertIconToBitmap(HICON hIcon)
//{
//    CDC dc;
//    CBitmap bmp;
//    CClientDC ClientDC(this);
//    dc.CreateCompatibleDC(&ClientDC);
//    bmp.CreateCompatibleBitmap(&ClientDC, 16, 16);
//    CBitmap* pOldBmp = (CBitmap*)dc.SelectObject(&bmp);
//    ::DrawIconEx(dc.GetSafeHdc(), 0, 0, hIcon, 16, 16, 0, (HBRUSH)RGB(255, 255, 255), DI_NORMAL);
//    dc.SelectObject(pOldBmp);
//    dc.DeleteDC();
//    HBITMAP hBitmap = (HBITMAP)::CopyImage((HANDLE)((HBITMAP)bmp), 
//			IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
//
//    return CBitmap::FromHandle(hBitmap);
//}
//void CPanelSearch::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
//{
//	//CNewFrame<CEbDialogBase>::OnInitMenuPopup(pPopupMenu,nIndex,bSysMenu);
//	CEbDialogBase::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
//
//	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BROWSER_IE);
//	pPopupMenu->SetMenuItemBitmaps(EB_COMMAND_CHANGE_BROWSER_TYPE,MF_BYCOMMAND,ConvertIconToBitmap(hIcon),NULL);
//}

void CPanelSearch::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bParentMouseMove && this->GetParent()!=NULL)
		this->GetParent()->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));	

	CEbDialogBase::OnLButtonDown(nFlags, point);
}

HBRUSH CPanelSearch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hBrush = CEbDialogBase::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID()==IDC_EDIT_SEARCH)
	{
		pDC->SetBkMode(TRANSPARENT);
		hBrush = CreateSolidBrush(theDefaultFlatBgColor);   //   ����ɫ
	}
	return hBrush;
}
LRESULT CPanelSearch::OnMsgChangeAppUrl(WPARAM wParam, LPARAM lParam)
{
	char * sUrl = (char*)wParam;
	if (sUrl==0) return 0;
	if (strlen(sUrl)>0)
	{
		const bool bSearchFocus = lParam==1?true:false;
		theSearchString = "";
		m_bCanSearch = false;
		boost::mutex::scoped_lock lockSearch(m_mutexSearch);
		CString sUrlTemp(sUrl);
		sUrlTemp.MakeLower();
		if (sUrlTemp==_T("about:blank"))
		{
			m_editSearch.SetWindowText(_T(""));
			if (bSearchFocus)
				m_editSearch.SetFocus();
		}else
		{
			USES_CONVERSION;
			const std::string csURL(libEbc::UTF82ACP(libEbc::URLDecode(sUrl,false).c_str()));
			m_editSearch.SetWindowText(csURL.c_str());
			//m_editSearch.SetWindowText(sUrl);
			if (bSearchFocus)
				this->PostMessage(EB_COMMAND_SEARCH_SET_FOCUS_SEL,1,1);
			else
				this->PostMessage(EB_COMMAND_SEARCH_SET_FOCUS_SEL,0,1);
		}
	}
	delete[] sUrl;
	return 0;
}
LRESULT CPanelSearch::OnMsgSearchSetFocusSel(WPARAM wParam, LPARAM lParam)
{
	if (wParam==1)	
		m_editSearch.SetFocus();
	if (lParam==1)
	{
		const int nTextLength = m_editSearch.GetWindowTextLength();
		if (nTextLength>0)
		{
			SetTimer(TIMERID_CALL_SEARCH_SEL_ALL,200,NULL);	// ** �����ʱ����ȫѡ����
			//m_editSearch.SetSel(0,nTextLength);
		}
		//m_editSearch.SetSel(0,-1);	// *�ı�̫�������ǰ��ʱ������ѡ�񵽺���
	}
	return 0;
}
LRESULT CPanelSearch::OnMsgShowRefreshOrStop(WPARAM wParam, LPARAM lParam)
{
	// wParam=1: show refresh
	// wParam=2: show stop
	const bool bShowRefresh = wParam==1?true:false;
	if (bShowRefresh)
	{
		if (!m_btnRefresh.IsWindowVisible())
			m_btnRefresh.ShowWindow(SW_SHOW);
		if (m_btnStop.IsWindowVisible())
			m_btnStop.ShowWindow(SW_HIDE);
	}else
	{
		if (!m_btnStop.IsWindowVisible())
			m_btnStop.ShowWindow(SW_SHOW);
		if (m_btnRefresh.IsWindowVisible())
			m_btnRefresh.ShowWindow(SW_HIDE);
	}
	return 0;
}
void CPanelSearch::OnEditSearch(void)
{
	boost::mutex::scoped_lock lockSearch(m_mutexSearch);
	CString sSearchString;
	m_editSearch.GetWindowText(sSearchString);
	sSearchString.Trim();
	if (sSearchString==theSearchString)
	{
		//HideSearchResult();
		return;
	}
	theSearchString = sSearchString;

	CreatePanelSearchResult();
	if (!sSearchString.IsEmpty())
	{
		m_pPanelSearchResult->DeleteAllResult();

		if (sSearchString.Left(1)==_T("/"))
		{
			// *����Ӧ��
			tstring sAppKey = sSearchString.Mid(1);
			std::transform(sAppKey.begin(), sAppKey.end(), sAppKey.begin(), tolower);
			m_pSubscribeFuncList.clear();
			theEBAppClient.EB_GetSubscribeFuncList((EB_FUNC_LOCATION)0xffffff,m_pSubscribeFuncList);
			for (size_t i=0; i<m_pSubscribeFuncList.size(); i++)
			{
				const EB_SubscribeFuncInfo pFuncInfo = m_pSubscribeFuncList[i];
				tstring sFunctionName(pFuncInfo.m_sFunctionName);
				tstring sDescription(pFuncInfo.m_sDescription);
				std::transform(sFunctionName.begin(), sFunctionName.end(), sFunctionName.begin(), tolower);
				std::transform(sDescription.begin(), sDescription.end(), sDescription.begin(), tolower);

				if (sFunctionName.find(sAppKey)==std::string::npos &&
					sDescription.find(sAppKey)==std::string::npos)
					continue;

				const size_t nGroupResultSize = m_pPanelSearchResult->InsertAppItem(pFuncInfo);
				if (nGroupResultSize>=15) break;
			}
		}

		CString sSql;
		tstring sSearchKey(sSearchString);
		CSqliteCdbc::escape_string_in(sSearchKey);
		sSearchKey = libEbc::ACP2UTF8(sSearchKey.c_str());
		const int nLimit = 25;
		//const int nLimit = GetWorkFrameShowed()?25:20;
		sSql.Format(_T("select url,title,strftime('%%Y-%%m-%%d %%H:%%M',last_time,'localtime') FROM url_record_t WHERE url LIKE '%%%s%%' OR title LIKE '%%%s%%' ORDER BY last_time DESC LIMIT %d"),sSearchKey.c_str(),sSearchKey.c_str(),nLimit);
		int nCookie = 0;
		theApp.m_pBoUsers->select(sSql, nCookie);
		cgcValueInfo::pointer pRecord = theApp.m_pBoUsers->first(nCookie);
		while (pRecord.get()!=NULL)
		{
			tstring sUrl(pRecord->getVector()[0]->getStrValue());
			tstring sTitle(pRecord->getVector()[1]->getStrValue());
			const tstring sLastTime(pRecord->getVector()[2]->getStrValue());
			pRecord = theApp.m_pBoUsers->next(nCookie);
			CSqliteCdbc::escape_string_out(sUrl);
			CSqliteCdbc::escape_string_out(sTitle);
			sUrl = libEbc::UTF82ACP(sUrl.c_str());
			sTitle = libEbc::UTF82ACP(sTitle.c_str());
			m_pPanelSearchResult->InsertUrlItem(sTitle, sUrl, sLastTime);
		}
		theApp.m_pBoUsers->reset(nCookie);

		CString sSearchStringTemp(sSearchString);
		sSearchStringTemp.MakeLower();
		if (sSearchStringTemp!="about:blank" &&
			sSearchStringTemp.Find("http://")<0 &&
			sSearchStringTemp.Find("https://")<0 &&
			sSearchStringTemp.Find("www.")<0)
		{

#ifdef USES_EBCOM_TEST
			//IDispatch* pCallback;
			//((CEBSearchEventsSink*)this)->QueryInterface(IID_IDispatch,(void**)&pCallback);
			theEBClientCore->EB_SearchUserInfo((IDispatch*)(CEBSearchEventsSink*)this, (LPCTSTR)sSearchString, 1);
#else
			theEBAppClient.EB_SearchUserInfo((CEBSearchCallback*)m_pPanelSearchResult, sSearchString, 1);
#endif
		}
		if (!m_pPanelSearchResult->IsEmpty())
		{
			ShowSearchResult();
			SetTimer(TIMERID_SELECT_FIRST_SEARCH,50,NULL);
		}
	}
	if (m_pPanelSearchResult->IsEmpty() || sSearchString.IsEmpty())
	{
		HideSearchResult();
	}
}

void CPanelSearch::HideSearchResult(void)
{
	if (m_pPanelSearchResult!=NULL && m_pPanelSearchResult->IsWindowVisible())
	{
		theSearchString = "";
		m_pPanelSearchResult->DeleteAllResult();
		m_pPanelSearchResult->ShowWindow(SW_HIDE);

		//if (m_pDlgAppFrame!=NULL && GetWorkFrameShowed())//m_pDlgAppFrame->IsWindowVisible()))
		{
			//if (!m_pDlgAppFrame->IsWindowVisible())
			//{
			//	//m_pDlgAppFrame->SetCurrentFocus();
			//	m_pDlgAppFrame->ShowWindow(SW_SHOW);
			//}
			//m_pDlgAppFrame->RefreshAppWnd();
			//if (m_pPanelSearch!=0 && !m_pPanelSearch->IsWindowVisible())
			//	m_pPanelSearch->ShowWindow(SW_SHOW);
			m_editSearch.SetFocus();
			return;
		}
	}
}
void CPanelSearch::ShowSearchResult(void)
{
	CreatePanelSearchResult();
	if (!m_pPanelSearchResult->IsWindowVisible())
	{
		CRect searchRect;
		m_editSearch.GetWindowRect(&searchRect);
		CRect rect;
		this->GetParent()->GetWindowRect(&rect);
		//searchRect.right = rect.right;
		searchRect.top = searchRect.bottom+2;
		searchRect.bottom = rect.bottom-1;
		m_pPanelSearchResult->MoveWindow(&searchRect);
		m_pPanelSearchResult->ShowWindow(SW_SHOW);
		//if (m_pDlgAppFrame!=NULL && GetWorkFrameShowed() && m_pDlgAppFrame->IsWindowVisible())
		//{
		//	m_pDlgAppFrame->ShowWindow(SW_HIDE);
		//}
		//if (m_pPanelSearch!=0&&m_pPanelSearch->IsWindowVisible())
		//	m_pPanelSearch->ShowWindow(SW_HIDE);
		//if (GetCallFrameShowed())
		//{
		//	CFrameWndInfoProxy::ShowHideCurrent(false);
		//}
	}
	//m_pPanelSearchResult
}


void CPanelSearch::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case TIMERID_SELECT_FIRST_SEARCH:
		{
			KillTimer(TIMERID_SELECT_FIRST_SEARCH);
			theApp.SelectFirstSearch(m_pPanelSearchResult->GetTreeCtrl(), m_editSearch, m_bCanSearch);
		}break;
	case TIMERID_CALL_SEARCH_SEL_ALL:
		{
			KillTimer(TIMERID_CALL_SEARCH_SEL_ALL);
			const int nTextLength = m_editSearch.GetWindowTextLength();
			if (nTextLength>0)
			{
				m_editSearch.SetSel(0,nTextLength);
			}
		}break;
	case TIMERID_EDIT_SEARCH:
		{
			KillTimer(TIMERID_EDIT_SEARCH);
			if (m_bCanSearch)
				OnEditSearch();
			else
				HideSearchResult();
			m_editSearch.SetFocus();
		}break;
	default:
		break;
	}

	CEbDialogBase::OnTimer(nIDEvent);
}
void CPanelSearch::OnEnChangeEditSearch()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEbDialogBase::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	//return;	// ??? ��ʱ��֧��������ʾ
	if (!m_bCanSearch) return;
	//KillTimer(TIMERID_EDIT_SEARCH);
	//SetTimer(TIMERID_EDIT_SEARCH,800,NULL);

	CString sSearchString;
	m_editSearch.GetWindowText(sSearchString);
	if (!sSearchString.IsEmpty())
	{
		KillTimer(TIMERID_EDIT_SEARCH);
		SetTimer(TIMERID_EDIT_SEARCH,600,NULL);
	}else
	{
		theSearchString = "";
		HideSearchResult();
	}
}

#define USES_APPFRAME

BOOL CPanelSearch::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == m_editSearch.GetSafeHwnd())
	{
		m_bCanSearch = true;
		if (this->GetFocus()!=&m_editSearch)
		{
			this->PostMessage(EB_COMMAND_SEARCH_SET_FOCUS_SEL,1,1);
		}
	}else if (pMsg->message == WM_LBUTTONUP && pMsg->hwnd == m_editSearch.GetSafeHwnd())
	{
		m_bCanSearch = true;
	}else if (pMsg->message == WM_KEYDOWN && pMsg->hwnd == m_editSearch.GetSafeHwnd())
	{
		boost::mutex::scoped_lock lockSearch(m_mutexSearch);
		if (pMsg->wParam == VK_ESCAPE)
		{
			//if (m_treeSearch.IsWindowVisible() && m_treeSearch.GetCount()>0)
			{
				m_editSearch.SetWindowText(_T(""));
				m_editSearch.SetFocus();
			}
		}else if (pMsg->wParam == VK_DOWN)
		{
			if (m_pPanelSearchResult!=NULL && m_pPanelSearchResult->IsWindowVisible() && !m_pPanelSearchResult->IsEmpty())
			{
				m_pPanelSearchResult->FocusTree();
				return TRUE;
			}
		}else if (pMsg->wParam == VK_RETURN)
		{
			// �س�����Ự
			//if (m_treeSearch.GetCount()>0)
			//{
			//	if (m_treeSearch.GetSelectedItem()==NULL)
			//		CallItem(m_treeSearch.GetFirstVisibleItem());
			//	else
			//		CallItem(m_treeSearch.GetSelectedItem());
			//}else
			{
				CString sSearchString;
				m_editSearch.GetWindowText(sSearchString);
				sSearchString.Trim();
				if (!sSearchString.IsEmpty())
				{
					m_bCanSearch = false;
#ifdef USES_APPFRAME
					CString sSearchStringTemp(sSearchString);
					sSearchStringTemp.MakeLower();
					const bool bIsEmail = sSearchStringTemp.Find(_T("@"))>=0?true:false;
					//const bool bHasPoint = sSearchStringTemp.Find(_T("."))>0?true:false;
					if (m_pPanelSearchResult!=NULL)
					{
						if (sSearchString.Find("(")>0 && sSearchString.Find(")")>0 && m_pPanelSearchResult->CallSelectedItem())
						{
							return TRUE;
						}else if (!bIsEmail && sSearchString.Left(1)=="/" && sSearchString.GetLength()>1 && m_pPanelSearchResult->CallSelectedItem())
						{
							return TRUE;
						}
					}
					if (!bIsEmail && 
						(sSearchStringTemp.Find(_T("."))>0 ||	// * ���ʼ����� . Ĭ�ϴ�������ӣ�www.��
						sSearchStringTemp.Find(_T("/"))>0 ||	// (http:// https://)
						sSearchStringTemp.Find(_T("="))>0 ||	// URL
						sSearchStringTemp==_T("about:blank")))
					//if (sSearchStringTemp.Find(_T("http://"))==0 ||
					//	sSearchStringTemp.Find(_T("https://"))==0 ||
					//	sSearchStringTemp.Find(_T("www."))==0 ||
					//	sSearchStringTemp.Find(_T("/"))>0 ||
					//	sSearchStringTemp.Find(_T("="))>0 ||
					//	sSearchStringTemp==_T("about:blank") ||
					//	(!bIsEmail && (sSearchStringTemp.Find(_T(".com"))>0 || sSearchStringTemp.Find(_T(".cn"))>0 || sSearchStringTemp.Find(_T(".net"))>0))
					//	)
					{
						COpenAppUrlInfo * pOpenAppUrlInfo = new COpenAppUrlInfo(sSearchString,"");
						pOpenAppUrlInfo->m_bSaveBrowseTitle = true;
						theApp.GetMainWnd()->PostMessage(EB_COMMAND_OPEN_APP_URL,(WPARAM)pOpenAppUrlInfo,(LPARAM)0);
						//AddAppUrl(true,(LPCTSTR)sSearchString,NULL);
					}else
#endif
					{

#ifdef USES_EBCOM_TEST
						theEBClientCore->EB_CallAccount((LPCTSTR)sSearchString,0);
#else
						theEBAppClient.EB_CallAccount(sSearchString,0);
#endif
					}
					HideSearchResult();
				}
			}
		}else
		{
			m_bCanSearch = true;
		}
	}

	return CEbDialogBase::PreTranslateMessage(pMsg);
}

void CPanelSearch::CreatePanelSearchResult(void)
{
	if (m_pPanelSearchResult==NULL)
	{
		CWnd * pParent = this;
		//CWnd * pParent = CWnd::FromHandle(::GetDesktopWindow());
		m_pPanelSearchResult = new CPanelSearchResult(pParent);
		m_pPanelSearchResult->Create(CPanelSearchResult::IDD,pParent);
	}
}

void CPanelSearch::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//__super::OnOK();
}

void CPanelSearch::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//__super::OnCancel();
}

void CPanelSearch::OnMove(void)
{
	if (m_pPanelSearchResult!=NULL && m_pPanelSearchResult->GetSafeHwnd()!=NULL)
	{
		CRect searchRect;
		m_editSearch.GetWindowRect(&searchRect);
		CRect rect;
		this->GetParent()->GetWindowRect(&rect);
		//searchRect.right = rect.right;
		searchRect.top = searchRect.bottom+2;
		searchRect.bottom = rect.bottom-1;
		m_pPanelSearchResult->MoveWindow(&searchRect);
	}
}
void CPanelSearch::CheckSearchResultShowHide(void)
{
	if (m_pPanelSearchResult==NULL) return;

	if (this->IsWindowVisible())
	{
		if (!m_pPanelSearchResult->IsWindowVisible() && !m_pPanelSearchResult->IsEmpty())
		{
			m_pPanelSearchResult->ShowWindow(SW_SHOW);
		}
	}else if (m_pPanelSearchResult->IsWindowVisible())
	{
		m_pPanelSearchResult->ShowWindow(SW_HIDE);
	}
}

void CPanelSearch::OnMove(int x, int y)
{
	CEbDialogBase::OnMove(x, y);
	OnMove();
}
