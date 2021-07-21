#include "ebwidgetchatright.h"
#include <dialogmainframe.h>

const int const_top_button_width = 85;
EbWidgetChatRight::EbWidgetChatRight(const EbcCallInfo::pointer& pCallInfo,QWidget *parent)
    : DialogWorkFrame(false,false,parent)
    , m_callInfo(pCallInfo)
//    , m_workFrame(0)
{
    assert(m_callInfo.get()!=0);

//    m_workFrame = new DialogWorkFrame(this);
//    m_workFrame->setModal(false);

//    this->addUrl(false,"www.entboost.com");

    if (m_callInfo->groupId()==0) {
        ///
        EbWorkItem::pointer workItem = EbWorkItem::create(EbWorkItem::WORK_ITEM_USER_INFO);
        workItem->setCallInfo( m_callInfo );
        workItem->setTopButtonWidth( const_top_button_width );
        DialogWorkFrame::addWorkItem(false,workItem,0);
    }
    else {
        ///
        EbWorkItem::pointer workItem = EbWorkItem::create(EbWorkItem::WORK_ITEM_USER_LIST);
        workItem->setCallInfo( m_callInfo );
        workItem->setTopButtonWidth( const_top_button_width );
        DialogWorkFrame::addWorkItem(false,workItem,0);
    }
}

EbWidgetChatRight::~EbWidgetChatRight()
{
    exitChat(false);
}

void EbWidgetChatRight::exitChat(bool bHangup)
{
//    if (m_pPanVideos!=NULL)
//    {
//        m_pPanVideos->ExitChat(bHangup);
//    }
    EbWidgetFileTranList * tranFile = widgetTranFile();
    if ( tranFile!=0 ) {
        tranFile->onExitChat(bHangup);
    }
//    if (m_pPanRemoteDesktop!=NULL)
//        m_pPanRemoteDesktop->ExitChat(bHangup);
}

void EbWidgetChatRight::onUserExit(eb::bigint nUserId, bool bExitDep)
{
    EbWidgetUserList * widgetUserList = DialogWorkFrame::widgetUserList();
    if ( widgetUserList!=0 ) {
        widgetUserList->onExitUser( nUserId, bExitDep );
    }
}

void EbWidgetChatRight::setCallInfo(const EbcCallInfo::pointer &pCallInfo)
{
    m_callInfo = pCallInfo;
    assert(m_callInfo.get()!=0);
}

void EbWidgetChatRight::onMsgReceipt(const CCrRichInfo *pCrMsgInfo, int nAckType)
{
//    if (m_pMsgRecord!=NULL)
//		m_pMsgRecord->OnMsgReceipt(pCrMsgInfo, nAckType);

}

void EbWidgetChatRight::onSendingFile(const CCrFileInfo *fileInfo)
{
    EbWidgetFileTranList * tranFile = this->openTranFile();
    tranFile->onSendingFile(fileInfo);
    if (tranFile->isEmpty()) {
        DialogWorkFrame::closeItem( indexOf(EbWorkItem::WORK_ITEM_TRAN_FILE) );
    }
}

void EbWidgetChatRight::onReceivingFile(const CCrFileInfo *fileInfo)
{
    EbWidgetFileTranList * tranFile = this->openTranFile();
    tranFile->onReceivingFile(fileInfo);
}

void EbWidgetChatRight::onReceivedFile(const CCrFileInfo *fileInfo)
{
    deleteTranFile(fileInfo->m_nMsgId);
}

void EbWidgetChatRight::onFilePercent(const CChatRoomFilePercent *pChatRoomFilePercent)
{
    EbWidgetFileTranList * tranFile = widgetTranFile();
    if ( tranFile!=0 ) {
        tranFile->onFilePercent(pChatRoomFilePercent);
    }
}

void EbWidgetChatRight::deleteTranFile(eb::bigint msgId)
{
    EbWidgetFileTranList * tranFile = widgetTranFile();
    if (tranFile!=0) {
        tranFile->deleteTranFile(msgId);
        if (tranFile->isEmpty()) {
            DialogWorkFrame::closeItem( indexOf(EbWorkItem::WORK_ITEM_TRAN_FILE) );
        }
    }
}

void EbWidgetChatRight::onMemberInfo(const EB_MemberInfo *memberInfo, bool bSort)
{
    EbWidgetUserList * userList = widgetUserList();
    if (userList!=0) {
        userList->onMemberInfo(memberInfo,bSort);
    }
}

void EbWidgetChatRight::getProcessing(bool &/*pVideoProcessing*/, bool &pFileProcessing, bool &/*pDesktopProcessing*/) const
{
//    if (m_pPanVideos!=NULL)
//    {
//        pVideoProcessing = m_pPanVideos->GetVideoCount()>0;
//    }else
//    {
//        pVideoProcessing = false;
//    }
    const EbWidgetFileTranList * tranFile = widgetTranFile();
    pFileProcessing = (tranFile!=0 && !tranFile->isEmpty())?true:false;
//    if (m_pPanRemoteDesktop!=NULL)
//        pDesktopProcessing = m_pPanRemoteDesktop->GetInDesktop();
//    else
    //        pDesktopProcessing = false;
}

void EbWidgetChatRight::showMsgRecord()
{
    EbWidgetChatRecord * chatRecord = widgetChatRecord();
    if (chatRecord==0) {
        EbWorkItem::pointer workItem = EbWorkItem::create(EbWorkItem::WORK_ITEM_CHAT_RECORD);
        workItem->setCallInfo( m_callInfo );
        workItem->setTopButtonWidth( const_top_button_width );
        DialogWorkFrame::addWorkItem(false,workItem);
    }
    else {
        DialogWorkFrame::closeItem( indexOf(EbWorkItem::WORK_ITEM_CHAT_RECORD) );
    }

}

void EbWidgetChatRight::triggeredApps(int index)
{
    if ( index>=0 && index<(int)theApp->m_pSubscribeFuncList.size() ) {
        const EB_SubscribeFuncInfo funcInfo = theApp->m_pSubscribeFuncList[index];
        const eb::bigint m_nSelectCallId = m_callInfo->callId();
        const eb::bigint m_nSelectUserId = 0;
        const tstring m_sSelectAccount;
        const eb::bigint m_nSelectGroupId = m_callInfo->groupId();
        if (funcInfo.m_nFunctionMode == EB_FUNC_MODE_WINDOW ||	/// 窗口模式；
            funcInfo.m_nFunctionMode == EB_FUNC_MODE_MAINFRAME) {
            const CEBString funcUrl = theApp->m_ebum.EB_GetSubscribeFuncUrl(funcInfo.m_nSubscribeId,
                                                                             m_nSelectCallId,m_nSelectUserId,m_sSelectAccount,m_nSelectGroupId);
            if (!funcUrl.empty()) {
                /// 250,250,25=fafafa
                char fullFuncUrl[260];
                sprintf( fullFuncUrl, "%s&color=fafafa",funcUrl.c_str());
                addUrl( false,fullFuncUrl,"", funcInfo );
            }
        }
        else {
            theApp->m_nSelectCallId = m_nSelectCallId;
            theApp->mainWnd()->openSubscribeFuncWindow(funcInfo);
        }
    }

}

void EbWidgetChatRight::resizeEvent(QResizeEvent *e)
{
    const int nwidth = width();

    DialogWorkFrame::resizeEvent(e);
}

EbWidgetFileTranList * EbWidgetChatRight::openTranFile()
{
    EbWidgetFileTranList * tranFile = widgetTranFile();
    if (tranFile==0) {
        EbWorkItem::pointer workItem = EbWorkItem::create(EbWorkItem::WORK_ITEM_TRAN_FILE);
        workItem->setCallInfo( m_callInfo );
        workItem->setTopButtonWidth( const_top_button_width );
        DialogWorkFrame::addWorkItem(false,workItem);
        tranFile = workItem->widgetTranFile();
    }
    return tranFile;
}

//void EbWidgetChatRight::updateGroupUsers()
//{
//    if ( m_callInfo->isGroupCall() ) {
//        int memberSize = 0;
//        int onlineSize = 0;
//        theApp->m_ebum.EB_GetGroupMemberSize(m_callInfo->groupId(),1,memberSize,onlineSize);
//        //const int nMemberSize = theEBAppClient.EB_GetGroupMemberSize(m_pCallInfo.m_sGroupCode,1);
//        //const int nOnlineSize = theEBAppClient.EB_GetGroupOnlineSize(m_pCallInfo.m_sGroupCode,1);
//        /// 群成员(%d/%d)
//        /// 群成员(%d)
//        QString text;
//        if (onlineSize>=0)
//            text = QString("%1(%2/%3)").arg(theLocales.getLocalText("user-list.title","User List")).arg(onlineSize).arg(memberSize);
//        else
//            text = QString("%1(%2)").arg(theLocales.getLocalText("user-list.title","User List")).arg(memberSize);
//        setItemText(EbWorkItem::WORK_ITEM_USER_LIST,text);
//    }
//}
