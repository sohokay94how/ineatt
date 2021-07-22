#include "ebcontextmenu.h"
#include "ebclientapp.h"
#include "eblistwidgetitem.h"
#include "ebtreewidgetitem.h"
#include "ebmessagebox.h"
#include <dialogmainframe.h>
#include <ebdialogcontactinfo.h>

EbContextMenu::EbContextMenu(Type type,QWidget * parent)
    : QObject(parent)
    , m_type(type)
    , m_adminSeparatorAction(0)
    , m_memberSeparatorAction(0)
    , m_memberForbidSpeechAction(0)
{
    m_menu = new QMenu(parent);
    QString text;
    QString tooltip;
    QAction * action = 0;
    int actionData = 0;
    switch (m_type) {
    case MyGroup: {
        /// 新建个人群组
        text = theLocales.getLocalText("context-menu.new-group.text","New Group");
        text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)EB_GROUP_TYPE_GROUP)->name().c_str() );
        action = m_menu->addAction( text );
        tooltip = theLocales.getLocalText("context-menu.new-group.tooltip","");
        tooltip.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)EB_GROUP_TYPE_GROUP)->name().c_str() );
        action->setToolTip( tooltip );
        actionData = EB_COMMAND_NEW_DEPARTMENT3;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionNewGroup()) );
        m_actionList.insert( actionData,action );
        /// ---------------------------
        m_menu->addSeparator();
        /// 修改我的名片
        action = m_menu->addAction( theLocales.getLocalText("context-menu.edit-my-member.text","Edit My Member") );
        action->setToolTip( theLocales.getLocalText("context-menu.edit-my-member.tooltip","") );
        actionData = EB_COMMAND_DEPARTMENT_EDIT_MY_EMP;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionEditMember()) );
        m_actionList.insert( actionData,action );
        break;
    }
    case MyContact: {
        /// 添加联系人
        action = m_menu->addAction( QIcon(":/img/menuadduser.png"),theLocales.getLocalText("context-menu.add-contact.text","Add Contact") );
        action->setToolTip( theLocales.getLocalText("context-menu.add-contact.tooltip","") );
        actionData = EB_COMMAND_NEW_CONTACT;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionAddContact()) );
        m_actionList.insert( actionData,action );
        /// ---------------------------
        m_menu->addSeparator();
        /// 查看联系人资料
        action = m_menu->addAction( theLocales.getLocalText("context-menu.edit-contact.text","Edit Contact") );
        action->setToolTip( theLocales.getLocalText("context-menu.edit-contact.tooltip","") );
        actionData = EB_COMMAND_EDIT_CONTACT;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionEditContact()) );
        m_actionList.insert( actionData,action );
        /// 删除联系人资料
        action = m_menu->addAction( theLocales.getLocalText("context-menu.delete-contact.text","Delete Contact") );
        action->setToolTip( theLocales.getLocalText("context-menu.delete-contact.tooltip","") );
        actionData = EB_COMMAND_DELETE_CONTACT;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionDeleteContact()) );
        m_actionList.insert( actionData,action );
        /// 添加分组
        action = m_menu->addAction( theLocales.getLocalText("context-menu.add-contact-group.text","Add Contact Group") );
        action->setToolTip( theLocales.getLocalText("context-menu.add-contact-group.tooltip","") );
        actionData = EB_COMMAND_NEW_GROUP;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionAddContactGroup()) );
        m_actionList.insert( actionData,action );
//        /// 修改分组 (双击支持直接修改，不需要鼠标右键操作)
//        action = m_menu->addAction( theLocales.getLocalText("context-menu.rename-contact-group.text","Rename Contact Group") );
//        action->setToolTip( theLocales.getLocalText("context-menu.rename-contact-group.tooltip","") );
//        actionData = EB_COMMAND_RENAME_GROUP;
//        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionRenameContactGroup()) );
//        m_actionList.insert( actionData,action );
        /// 删除该组
        action = m_menu->addAction( theLocales.getLocalText("context-menu.delete-contact-group.text","Delete Contact Group") );
        action->setToolTip( theLocales.getLocalText("context-menu.delete-contact-group.tooltip","") );
        actionData = EB_COMMAND_DELETE_GROUP;
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionDeleteContactGroup()) );
        m_actionList.insert( actionData,action );
        break;
    }
    default:
        break;
    }

    /// 打开会话
    action = m_menu->addAction( theLocales.getLocalText("context-menu.open-chat.text","Open Chat") );
    action->setIcon( QIcon( QPixmap(":/img/menucall.png") ));
    action->setToolTip( theLocales.getLocalText("context-menu.open-chat.tooltip","") );
    actionData = EB_COMMAND_CALL_USER;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionCallUser()) );
    m_actionList.insert( actionData,action );
    /// 聊天记录
    action = m_menu->addAction( theLocales.getLocalText("context-menu.chat-record.text","Chat Record") );
    action->setIcon( QIcon( QPixmap(":/img/menumsg.png") ));
    action->setToolTip( theLocales.getLocalText("context-menu.chat-record.tooltip","") );
    actionData = EB_MSG_VIEW_MSG_RECORD;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionViewMsgRecord()) );
    m_actionList.insert( actionData,action );
    /// 群共享
    action = m_menu->addAction( theLocales.getLocalText("context-menu.group-share.text","Group Share") );
    action->setToolTip( theLocales.getLocalText("context-menu.group-share.tooltip","") );
    actionData = EB_COMMAND_VIEW_GROUP_SHARE;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionViewGroupShare()) );
    m_actionList.insert( actionData,action );
    /// ---------------------------
    m_adminSeparatorAction = m_menu->addSeparator();
    /// 加为管理员
    action = m_menu->addAction( theLocales.getLocalText("context-menu.member-add-admin.text","Add Admin") );
    action->setToolTip( theLocales.getLocalText("context-menu.member-add-admin.tooltip","") );
    actionData = EB_COMMAND_MEMBER_ADD_ADMIN;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddAdminLevel()) );
    m_actionList.insert( actionData,action );
    /// 取消管理员资格
    action = m_menu->addAction( theLocales.getLocalText("context-menu.member-del-admin.text","Del Admin") );
    action->setToolTip( theLocales.getLocalText("context-menu.member-del-admin.tooltip","") );
    actionData = EB_COMMAND_MEMBER_DEL_ADMIN;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberDelAdminLevel()) );
    m_actionList.insert( actionData,action );
    /// 群禁言
    action = m_menu->addAction( theLocales.getLocalText("context-menu.group-add-forbid-speech.text","Group Forbid Speech") );
    action->setIcon( QIcon( QPixmap(":/img/imgstateforbid.png") ));
    action->setToolTip( theLocales.getLocalText("context-menu.group-add-forbid-speech.tooltip","") );
    actionData = EB_COMMAND_MEMBER_ADD_GROUP_FORBID_SPEECH;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionGroupAddForbidSpeech()) );
    m_actionList.insert( actionData,action );
    /// 解除群禁言
    action = m_menu->addAction( theLocales.getLocalText("context-menu.group-del-forbid-speech.text","Group Delete Forbid Speech") );
    action->setToolTip( theLocales.getLocalText("context-menu.group-del-forbid-speech.tooltip","") );
    actionData = EB_COMMAND_MEMBER_DEL_GROUP_FORBID_SPEECH;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionGroupDelForbidSpeech()) );
    m_actionList.insert( actionData,action );
    /// 修改群资料
    text = theLocales.getLocalText("context-menu.edit-group.text","Edit Group");
    text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)EB_GROUP_TYPE_GROUP)->name().c_str() );
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.edit-group.tooltip","") );
    actionData = EB_COMMAND_EDIT_DEPARTMENT;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionEditGroup()) );
    m_actionList.insert( actionData,action );
    /// 解散该群
    text = theLocales.getLocalText("context-menu.delete-group.text","Delete Group");
    text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)EB_GROUP_TYPE_GROUP)->name().c_str() );
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.delete-group.tooltip","") );
    actionData = EB_COMMAND_DELETE_DEPARTMENT;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionDeleteGroup()) );
    m_actionList.insert( actionData,action );
    /// 退出该群
    text = theLocales.getLocalText("context-menu.exit-group.text","Exit Group");
    text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)EB_GROUP_TYPE_GROUP)->name().c_str() );
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.delete-group.tooltip","") );
    actionData = EB_COMMAND_EXIT_DEPARTMENT;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionExitGroup()) );
    m_actionList.insert( actionData,action );
    ///
    /// ---------------------------
    m_memberSeparatorAction = m_menu->addSeparator();
    /// 修改成员名片
    text = theLocales.getLocalText("context-menu.edit-user-member.text","Edit User Member");
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.edid-user-member.tooltip","") );
    actionData = EB_COMMAND_DEPARTMENT_EDIT_USER_EMP;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionEditMember()) );
    m_actionList.insert( actionData,action );
    /// 修改成员名片
    text = theLocales.getLocalText("context-menu.del-member.text","Delete Member");
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.del-member.tooltip","") );
    actionData = EB_COMMAND_DEPARTMENT_DEL_EMP;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionDeleteMember()) );
    m_actionList.insert( actionData,action );
    /// 解除禁言
    text = theLocales.getLocalText("context-menu.member-del-forbid-speech.text","Member Delete Forbid Speech");
    action = m_menu->addAction( text );
    action->setToolTip( theLocales.getLocalText("context-menu.member-del-forbid-speech.tooltip","") );
    actionData = EB_COMMAND_MEMBER_DEL_FORBID_SPEECH;
    this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberDelForbidSpeech()) );
    m_actionList.insert( actionData,action );
    /// 禁言->
    {
        QMenu * memberForbidSpeechMenu = new QMenu(m_menu);
        m_memberForbidSpeechAction = m_menu->addMenu(memberForbidSpeechMenu);
        m_memberForbidSpeechAction->setIcon( QIcon( QPixmap(":/img/imgstateforbid.png") ));
        m_memberForbidSpeechAction->setText( theLocales.getLocalText("context-menu.member-forbid-speech.text","Forbid Speech") );
        /// 10分钟
        action = memberForbidSpeechMenu->addAction( theLocales.getLocalText("context-menu.member-forbid-speech.10","10 Minutes") );
        action->setData( QVariant((int)10) );
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddForbidSpeech()) );
        /// 1小时=10分钟
        action = memberForbidSpeechMenu->addAction( theLocales.getLocalText("context-menu.member-forbid-speech.60","1 Hour") );
        action->setData( QVariant((int)60) );
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddForbidSpeech()) );
        /// 12小时=720分钟
        action = memberForbidSpeechMenu->addAction( theLocales.getLocalText("context-menu.member-forbid-speech.720","12 Hours") );
        action->setData( QVariant((int)720) );
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddForbidSpeech()) );
        /// 1天=1440分钟
        action = memberForbidSpeechMenu->addAction( theLocales.getLocalText("context-menu.member-forbid-speech.1440","1 Day") );
        action->setData( QVariant((int)1440) );
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddForbidSpeech()) );
        /// 永久=0分钟
        action = memberForbidSpeechMenu->addAction( theLocales.getLocalText("context-menu.member-forbid-speech.0","Forever") );
        action->setData( QVariant((int)0) );
        this->connect( action,SIGNAL(triggered()),this,SLOT(onTriggeredActionMemberAddForbidSpeech()) );
    }

    hideAllMenuAction();
}

EbContextMenu::~EbContextMenu()
{
    m_actionList.clear();
}

QAction * EbContextMenu::exec(const QPoint &pos)
{
    return m_menu->exec(pos);
}

void EbContextMenu::hideAllMenuAction()
{
//    if (m_adminSeparatorAction!=0) {
//        m_adminSeparatorAction->setVisible(false);
//    }
//    if (m_memberSeparatorAction!=0) {
//        m_memberSeparatorAction->setVisible(false);
//    }
    if (m_memberForbidSpeechAction!=0) {
        m_memberForbidSpeechAction->setVisible(false);
    }
    CLockMap<int,QAction*>::iterator iter =  m_actionList.begin();
    for (; iter!=m_actionList.end(); iter++) {
        QAction * action = iter->second;
        if ( action->isSeparator() ) continue;
        action->setVisible(false);
    }
}

bool EbContextMenu::updateMenuItem(const EbWidgetItemInfo::pointer &itemInfo)
{
    hideAllMenuAction();
    m_itemInfo = itemInfo;

    /// ?? 群组云盘功能
    EB_FUNC_LOCATION nFuncLocation = EB_FUNC_LOCATION_UNKNOWN;
    ////    theApp.ClearSubscribeSelectInfo();
    if (m_type==MyGroup) {
        this->setMenuActionVisible( EB_COMMAND_NEW_DEPARTMENT3,true );
    }
    else if (m_type==MyContact) {
        /// 添加联系人 & 添加分组
        this->setMenuActionVisible( EB_COMMAND_NEW_CONTACT,true );
        this->setMenuActionVisible( EB_COMMAND_NEW_GROUP,true );
    }
    if (/*item==0 || */m_itemInfo.get()==0) {
        ///
    }
    else if (m_itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_CONTACT) {
//        nFuncLocation = EB_FUNC_LOCATION_RIGHT_CLICK_MENU_USER;
//        theApp.m_nSelectUserId = pTreeItemInfo->m_nUserId;
//        theApp.m_sSelectAccount = pTreeItemInfo->m_sAccount;

        this->setMenuActionVisible( EB_COMMAND_NEW_CONTACT,true );
//        /// 判断聊天记录
//        CString sSql;
//        sSql.Format(_T("select msg_type FROM msg_record_t WHERE dep_code=0 AND (from_uid=%lld OR to_uid=%lld) LIMIT 1"),
//            pTreeItemInfo->m_nUserId,pTreeItemInfo->m_nUserId);
//        if (theApp.m_pBoUsers->select(sSql)>0)
//        {
//            m_menu2.InsertODMenu(-1,_T("聊天记录"),MF_BYPOSITION,EB_MSG_VIEW_MSG_RECORD,IDB_BITMAP_MENU_MSG);
//            //m_menu2.AppendMenu(MF_BYCOMMAND,EB_MSG_VIEW_MSG_RECORD,_T("聊天记录"));
//            //m_menu2.AppendMenu(MF_BYCOMMAND,EB_COMMAND_DELETE_MSG_RECORD,_T("清空聊天记录"));
//            m_menu2.AppendMenu(MF_SEPARATOR);
//        }
        this->setMenuActionVisible( EB_COMMAND_EDIT_CONTACT,true );
//        if (m_pGroupItemInfo.size()>1)
//        {
//            //
//            pPopupMenuMoveto.CreatePopupMenu();
//            BoostReadLock rdlock(m_pGroupItemInfo.mutex());
//            CLockMap<mycp::bigint,CTreeItemInfo::pointer>::iterator pIter = m_pGroupItemInfo.begin();
//            int nIndex = 0;
//            for (; pIter!=m_pGroupItemInfo.end();  pIter++)
//            {
//                const CTreeItemInfo::pointer& pGroupItemInfo = pIter->second;
//                if (pGroupItemInfo->m_sId==const_default_group_ugid || pGroupItemInfo->m_sId==pTreeItemInfo->m_sParentId)
//                    continue;
//                pPopupMenuMoveto.AppendMenu(MF_BYCOMMAND,EB_COMMAND_MY_UGINFO+nIndex,pGroupItemInfo->m_sName.c_str());
//                nIndex++;
//            }
//            m_menu2.AppendMenu(MF_POPUP|MF_BYPOSITION,(UINT)pPopupMenuMoveto.m_hMenu,_T("移动至"));
//        }
        this->setMenuActionVisible( EB_COMMAND_DELETE_CONTACT,true );
        this->setMenuActionVisible( EB_COMMAND_NEW_GROUP,true );
    }
    else if (m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_GROUP && m_type==MyContact) {
        /// 联系人分组
        this->setMenuActionVisible( EB_COMMAND_NEW_CONTACT,true );
        this->setMenuActionVisible( EB_COMMAND_NEW_GROUP,true );
        if (const_default_group_ugid!=m_itemInfo->m_sId)
        {
            this->setMenuActionVisible( EB_COMMAND_RENAME_GROUP,true );
            this->setMenuActionVisible( EB_COMMAND_DELETE_GROUP,true );
        }
    }
    else if (m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_MEMBER) {
        /// member
        nFuncLocation = EB_FUNC_LOCATION_RIGHT_CLICK_MENU_USER;
        //        theApp.m_nSelectUserId = pTreeItemInfo->m_nUserId;
        if (m_itemInfo->m_nUserId == theApp->logonUserId()) {
            /// 选择自己，修改我的名片
            this->setMenuActionVisible( EB_COMMAND_DEPARTMENT_EDIT_MY_EMP,true );
        }
        else {
            /// 选择别人
            this->setMenuActionVisible( EB_COMMAND_CALL_USER,true );
            /// 判断聊天记录
            char sSql[256];
            sprintf(sSql,"select msg_type FROM msg_record_t WHERE dep_code=0 AND (from_uid=%lld OR to_uid=%lld) LIMIT 1",
                    m_itemInfo->m_nUserId,m_itemInfo->m_nUserId);
            if (theApp->m_sqliteUser->select(sSql)>0) {
                this->setMenuActionVisible( EB_MSG_VIEW_MSG_RECORD,true );
            }
        }
        /// 我是群主，选择对象不是群主
        if (theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode) && !theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId)) {
            //            m_adminSeparatorAction->setVisible(true);
            if (theApp->m_ebum.EB_IsGroupAdminLevel(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId))
                this->setMenuActionVisible( EB_COMMAND_MEMBER_DEL_ADMIN,true );
            else
                this->setMenuActionVisible( EB_COMMAND_MEMBER_ADD_ADMIN,true );
        }

//        EbWidgetItemInfo::pointer groupitemInfo;
//        if (m_itemInfo->m_hItem!=0) {
//            const EbTreeWidgetItem * itemParent = (EbTreeWidgetItem*)m_itemInfo->m_hItem->parent();
//            groupitemInfo = itemParent->m_itemInfo;
//        }
//        else if (m_itemInfo->m_listItem!=0) {
////            const EbListWidgetItem * itemParent = (EbListWidgetItem*)itemInfo->m_listItem->parent();
////            pDem_itemInfo = itemParent->m_itemInfo;
//        }
//        const EbTreeWidgetItem * itemParent = (EbTreeWidgetItem*)item->parent();
//        if (itemParent==0) {
//            return false;
//        }
//        const EbWidgetItemInfo::pointer pDem_itemInfo = itemParent->m_itemInfo;
        if ( (theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode) && !theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId)) ||
             (theApp->m_ebum.EB_IsGroupAdminLevel(m_itemInfo->m_sGroupCode) && !theApp->m_ebum.EB_IsGroupAdminLevel(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId)) ) {
            /// 选择用户不是群管理员
            //            m_memberSeparatorAction->setVisible(true);
            this->setMenuActionVisible( EB_COMMAND_DEPARTMENT_EDIT_USER_EMP,true );
            this->setMenuActionVisible( EB_COMMAND_DEPARTMENT_DEL_EMP,true );

            int nForbidMinutes = 0;
            if (theApp->m_ebum.EB_IsMemberForbidSpeech(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId,nForbidMinutes)) {
                this->setMenuActionVisible( EB_COMMAND_MEMBER_DEL_FORBID_SPEECH,true );
            }
            else {
                m_memberForbidSpeechAction->setVisible(true);
            }
        }
        else {
            /// 我不是群管理员，普通成员
            //m_menu2.AppendMenu(nPosIndex++,MF_BYCOMMAND,EB_COMMAND_EXIT_DEPARTMENT,_T("退出该群"));
        }
    }
    else if (m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_GROUP && m_type==MyGroup) {
        /// group
        //eb::bigint nGroupCreateUserId = 0;
        //if (!theApp->m_ebum.EB_GetGroupCreator(pTreeItemInfo->m_sGroupCode,nGroupCreateUserId)) return;
        EB_GROUP_TYPE nGroupType = EB_GROUP_TYPE_DEPARTMENT;
        if (!theApp->m_ebum.EB_GetGroupType(m_itemInfo->m_sGroupCode,nGroupType)) {
            return false;
        }
        nFuncLocation = EB_FUNC_LOCATION_RIGHT_CLICK_MENU_GROUP;
        //        theApp.m_nSelectGroupId = pTreeItemInfo->m_sGroupCode;
        //        m_menu2.AppendMenu(MF_SEPARATOR);
        this->setMenuActionVisible( EB_COMMAND_CALL_USER,true );

        char sSql[256];
        sprintf(sSql,"select msg_type FROM msg_record_t WHERE dep_code=%lld LIMIT 1",m_itemInfo->m_sGroupCode);
        if (theApp->m_sqliteUser->select(sSql)>0) {
            this->setMenuActionVisible( EB_MSG_VIEW_MSG_RECORD,true );
        }
        if ( !theApp->isDisableGroupShareCloud() ) {
            this->setMenuActionVisible( EB_COMMAND_VIEW_GROUP_SHARE,true );
        }
        if (theApp->m_ebum.EB_IsGroupAdminLevel(m_itemInfo->m_sGroupCode)) {
            if (theApp->m_ebum.EB_IsGroupForbidSpeech(m_itemInfo->m_sGroupCode))
                this->setMenuActionVisible( EB_COMMAND_MEMBER_DEL_GROUP_FORBID_SPEECH,true );
            else
                this->setMenuActionVisible( EB_COMMAND_MEMBER_ADD_GROUP_FORBID_SPEECH,true );
            /// 我是群管理员
            QAction * action = this->setMenuActionVisible( EB_COMMAND_EDIT_DEPARTMENT,true );
            if (action!=0) {
                QString text = theLocales.getLocalText("context-menu.edit-group.text","Edit Group");
                text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)nGroupType)->name().c_str() );
                action->setText(text);
            }
            if (theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode) &&
                    nGroupType != EB_GROUP_TYPE_DEPARTMENT &&	/// 公司部门
                    nGroupType != EB_GROUP_TYPE_PROJECT)			/// 公司项目组
            {
                action = this->setMenuActionVisible( EB_COMMAND_DELETE_DEPARTMENT,true );
                if (action!=0) {
                    QString text = theLocales.getLocalText("context-menu.delete-group.text","Delete Group");
                    text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)nGroupType)->name().c_str() );
                    action->setText(text);
                }
            }
        }
        if ( !theApp->m_ebum.EB_IsGroupCreator(m_itemInfo->m_sGroupCode) &&
             nGroupType != EB_GROUP_TYPE_DEPARTMENT &&	/// 公司部门
             nGroupType != EB_GROUP_TYPE_PROJECT ) {			/// 公司项目组
            QAction * action = this->setMenuActionVisible( EB_COMMAND_EXIT_DEPARTMENT,true );
            if (action!=0) {
                QString text = theLocales.getLocalText("context-menu.exit-group.text","Delete Group");
                text.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)nGroupType)->name().c_str() );
                action->setText(text);
            }
        }
    }
    return true;
}

void EbContextMenu::onCallItem(const EbWidgetItemInfo::pointer &itemInfo)
{
    if (itemInfo.get()==0) return;
    if (itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_CONTACT) {
        if (itemInfo->m_nUserId>0)
            theApp->m_ebum.EB_CallUserId(itemInfo->m_nUserId,0);
        else
            theApp->m_ebum.EB_CallAccount(itemInfo->m_sAccount.c_str(),0);
    }
    else if (itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_MEMBER) {
        theApp->m_pAutoCallFromUserIdList.remove(itemInfo->m_nUserId);
        theApp->m_ebum.EB_CallMember(itemInfo->m_sMemberCode,0);
    }
    else if (itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_GROUP) {
        theApp->m_pAutoCallGroupIdList.remove(itemInfo->m_sGroupCode);
        theApp->m_ebum.EB_CallGroup(itemInfo->m_sGroupCode);
    }
}

void EbContextMenu::onEditItem(const EbWidgetItemInfo::pointer &itemInfo)
{
    if (itemInfo.get()==0) {
        return;
    }
    if (itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_CONTACT) {
        theApp->editContactInfo(itemInfo->m_sId);
    }
    else if (itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_MEMBER) {
        EB_MemberInfo memberInfo;
        if (theApp->m_ebum.EB_GetMemberInfoByUserId(&memberInfo,itemInfo->m_sGroupCode,itemInfo->m_nUserId)) {
            theApp->editMemberInfo(&memberInfo);
        }
    }
}

void EbContextMenu::onTriggeredActionAddContact()
{
    if (theApp->isAuthContact()) {
        /// 添加好友需要验证
        if (theApp->findAppSugId()==0) {
            /// 暂时未开放添加好友验证功能：\r\n请联系管理员！
            EbMessageBox::doShow( NULL, "", QChar::Null,
                                  theLocales.getLocalText( "message-show.not-support-auth-contact","Not supprt auth contact" ),
                                  EbMessageBox::IMAGE_WARNING,default_warning_auto_close );
        }
        else {
            /// 找群找人
            EB_SubscribeFuncInfo funcInfo;
            if (theApp->m_ebum.EB_GetSubscribeFuncInfo(theApp->findAppSugId(),&funcInfo)) {
                theApp->mainWnd()->openSubscribeFuncWindow(funcInfo);
            }
        }
    }
    else {
        /// 添加普通联系人
        eb::bigint ugId = 0;
        if ( m_itemInfo.get()!=0 ) {
            if (m_itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_GROUP) {
                ugId = m_itemInfo->m_sId;
            }
            else if (m_itemInfo->m_nItemType == EbWidgetItemInfo::ITEM_TYPE_CONTACT) {
                ugId = m_itemInfo->m_sParentId;
            }
            if (ugId==const_default_group_ugid) {
                ugId = 0;
            }
        }
        EbDialogContactInfo dlgContactInfo;
        dlgContactInfo.m_contactInfo.m_nUGId = ugId;
        if ( dlgContactInfo.exec()==QDialog::Accepted ) {
            theApp->m_ebum.EB_EditContact(&dlgContactInfo.m_contactInfo);
        }
    }
}

void EbContextMenu::onTriggeredActionEditContact()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_CONTACT) return;
    theApp->editContactInfo(m_itemInfo->m_sId);
}

void EbContextMenu::onTriggeredActionDeleteContact()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_CONTACT) return;
    QString title;
    QString text;
    if (theApp->isAuthContact() && m_itemInfo->m_nUserId>0) {
        /// 确定删除联系人：\r\n%s(%s) 同时从对方联系人列表中消失吗？
        title = theLocales.getLocalText("message-box.delete-auth-contact.title","Delete Contact");
        text = theLocales.getLocalText("message-box.delete-auth-contact.text","Confirm delete contact?");
    }
    else {
        /// 确定删除联系人：\r\n%s(%s) 吗？
        title = theLocales.getLocalText("message-box.delete-contact.title","Delete Contact");
        text = theLocales.getLocalText("message-box.delete-contact.text","Confirm delete contact?");
    }
    if (title.isEmpty()) {
        title = theApp->productName();
    }
    text.replace( "[USER_NAME]", m_itemInfo->m_sName.c_str() );
    text.replace( "[USER_ACCOUNT]", m_itemInfo->m_sAccount.c_str() );
    if (EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION )==QDialog::Accepted) {
        if (theApp->isAuthContact())
            theApp->m_ebum.EB_DeleteContact(m_itemInfo->m_sId,true);
        else
            theApp->m_ebum.EB_DeleteContact(m_itemInfo->m_sId,false);
    }
}

void EbContextMenu::onTriggeredActionAddContactGroup()
{
    if (m_type==MyContact) {
//        theApp->m_ebum.EB_EditUGInfo(0,"Unname Group")
        emit addContactGroup();
    }

}

void EbContextMenu::onTriggeredActionRenameContactGroup()
{

}

void EbContextMenu::onTriggeredActionDeleteContactGroup()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_GROUP) return;

    QString title = theLocales.getLocalText("message-box.delete-contact-group.title","Delete Group");
    if (title.isEmpty()) {
        title = theApp->productName();
    }
    /// 确定删除：\r\n%s 分组吗？
    /// 确定删除：\r\n%s 并将该分组所有联系人移到默认分组吗？
    QString text = m_itemInfo->m_dwItemData==0?
                theLocales.getLocalText("message-box.delete-contact-empty-group.text","Confirm Delete Group?"):
                theLocales.getLocalText("message-box.delete-contact-group.text","Confirm Delete Group?");
    text.replace( "[GROUP_NAME]", m_itemInfo->m_sName.c_str() );
    const int ret = EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION );
    if (ret==QDialog::Accepted) {
        theApp->m_ebum.EB_DeleteUGInfo(m_itemInfo->m_sId);
    }
}

void EbContextMenu::onTriggeredActionNewGroup()
{
    if (m_type==MyGroup) {
        theApp->newGroupInfo(EB_GROUP_TYPE_GROUP);
    }
}

void EbContextMenu::onTriggeredActionEditGroup()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_sGroupCode==0) return;
    theApp->editGroupInfo(m_itemInfo->m_sGroupCode);
}

void EbContextMenu::onTriggeredActionDeleteGroup()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_GROUP) return;

    EB_GroupInfo pGroupInfo;
    if (!theApp->m_ebum.EB_GetGroupInfo(m_itemInfo->m_sGroupCode,&pGroupInfo)) {
        return;
    }
    if ( pGroupInfo.m_nCreateUserId != theApp->logonUserId() ) {
        /// 不是部门创建者，不能删除
        return;
    }
    else if (pGroupInfo.m_nGroupType == EB_GROUP_TYPE_DEPARTMENT			/// 企业部门
        && theApp->m_ebum.EB_GetGroupMemberSize(m_itemInfo->m_sGroupCode,1)>0) {		/// 不为空，不能删除
        return;
    }
//    if (this->m_pViewContactInfo && m_pViewContactInfo->IsWindowVisible()) {
//        m_pViewContactInfo->HideReset();
//    }

    QString title = theLocales.getLocalText("message-box.delete-group.title","Delete Group");
    if (title.isEmpty())
        title = theApp->productName();
    else {
        title.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)pGroupInfo.m_nGroupType)->name().c_str() );
    }
    /// 确定解散：\r\n%s 吗？
    QString text = theLocales.getLocalText("message-box.delete-group.text","Confirm Delete Group?");
    text.replace( "[GROUP_NAME]", pGroupInfo.m_sGroupName.c_str() );
    text.replace( "[GROUP_ID]", QString::number(pGroupInfo.m_sGroupCode) );
    const int ret = EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION );
    if (ret==QDialog::Accepted) {
        theApp->m_ebum.EB_DeleteGroup(m_itemInfo->m_sGroupCode);
    }
}

void EbContextMenu::onTriggeredActionExitGroup()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_GROUP) return;

    EB_GroupInfo pGroupInfo;
    if (!theApp->m_ebum.EB_GetGroupInfo(m_itemInfo->m_sGroupCode,&pGroupInfo)) {
        return;
    }
    else if ( pGroupInfo.m_nCreateUserId == theApp->logonUserId() ) {
        /// 部门创建者，不能退出
        return;
    }
    QString title = theLocales.getLocalText("message-box.exit-group.title","Exit Group");
    if (title.isEmpty())
        title = theApp->productName();
    else {
        title.replace( "[GROUP_TYPE_NAME]", theLocales.getGroupTypeName((int)pGroupInfo.m_nGroupType)->name().c_str() );
    }
    /// 确定退出：\r\n%s 吗？
    QString text = theLocales.getLocalText("message-box.exit-group.text","Confirm Exit Group?");
    text.replace( "[GROUP_NAME]", pGroupInfo.m_sGroupName.c_str() );
    text.replace( "[GROUP_ID]", QString::number(pGroupInfo.m_sGroupCode) );
    const int ret = EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION );
    if (ret==QDialog::Accepted) {
        theApp->m_ebum.EB_ExitGroup(m_itemInfo->m_sGroupCode);
    }
}

void EbContextMenu::onTriggeredActionGroupAddForbidSpeech()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_GROUP) return;
    /// 群组禁言
    theApp->m_ebum.EB_SetGroupForbidSpeech(m_itemInfo->m_sGroupCode,true);

}

void EbContextMenu::onTriggeredActionGroupDelForbidSpeech()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_GROUP) return;
    /// 解除群组禁言
    theApp->m_ebum.EB_SetGroupForbidSpeech(m_itemInfo->m_sGroupCode,false);
}

void EbContextMenu::onTriggeredActionEditMember()
{
    onEditItem( m_itemInfo );
}

void EbContextMenu::onTriggeredActionDeleteMember()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_MEMBER) return;

    EB_GroupInfo pGroupInfo;
    if (!theApp->m_ebum.EB_GetGroupInfo(m_itemInfo->m_sGroupCode,&pGroupInfo))
        return;
    if (m_itemInfo->m_nUserId == pGroupInfo.m_nCreateUserId)
    {
        /// 不能移除管理者自己
        return;
    //}else if (pGroupInfo.m_nCreateUserId!=theApp.GetLogonUserId())
    //{
    //	CDlgMessageBox::EbDoModal(this,"移除成员：","没有操作权限！",CDlgMessageBox::IMAGE_WARNING);
    //	return;
    }

    QString title = theLocales.getLocalText("message-box.delete-member.title","移除成员");
    if (title.isEmpty())
        title = theApp->productName();
    /// 确定移除：\r\n%s(%s) 吗？
    QString text = theLocales.getLocalText("message-box.delete-member.text","Confirm Delete Member?");
    text.replace( "[USER_ACCOUNT]", m_itemInfo->m_sAccount.string().c_str() );
    char lpszUserId[24];
    sprintf(lpszUserId,"%lld", m_itemInfo->m_nUserId);
    text.replace( "[USER_ID]", lpszUserId );
    const int ret = EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION );
    if (ret==QDialog::Accepted) {
        theApp->m_ebum.EB_DeleteMember(m_itemInfo->m_sMemberCode);
    }
}

void EbContextMenu::onTriggeredActionMemberAddAdminLevel()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_MEMBER) return;
    theApp->m_ebum.EB_AddGroupAdminLevel(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId);
}

void EbContextMenu::onTriggeredActionMemberDelAdminLevel()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_MEMBER) return;
    theApp->m_ebum.EB_DelGroupAdminLevel(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId);

}

void EbContextMenu::onTriggeredActionMemberAddForbidSpeech()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_MEMBER) return;
    const QAction * action = (QAction*)sender();
    const int forbidMinutes = action->data().toInt();
    theApp->m_ebum.EB_SetMemberForbidSpeech(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId, true, forbidMinutes);

}

void EbContextMenu::onTriggeredActionMemberDelForbidSpeech()
{
    if (m_itemInfo.get()==0 || m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_MEMBER) return;
    theApp->m_ebum.EB_SetMemberForbidSpeech(m_itemInfo->m_sGroupCode,m_itemInfo->m_nUserId, false);
}

void EbContextMenu::onTriggeredActionCallUser()
{
    onCallItem( m_itemInfo );
}

void EbContextMenu::onTriggeredActionViewMsgRecord()
{

}

void EbContextMenu::onTriggeredActionViewGroupShare()
{

}

QAction *EbContextMenu::setMenuActionVisible(int commandId, bool visible)
{
    QAction * action = 0;
    if (m_actionList.find(commandId,action)) {
        action->setVisible(visible);
        return action;
    }
    return 0;
}

