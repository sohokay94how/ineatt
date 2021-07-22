#include "ebwidgetmycontact.h"
#include<ebtreewidgetitem.h>
#include<iconhelper.h>

//const CEBString const_default_group_name = "默认分组";

EbWidgetMyContact::EbWidgetMyContact(QWidget *parent) : QWidget(parent)
  , m_contextMenu(0)
  , m_timeNewGroup(0)
  , m_inGroupEdit(false)
{
    m_treeWidgetMyContact = new QTreeWidget(this);
    m_treeWidgetMyContact->setFrameStyle(QFrame::NoFrame); /// 去掉边框
    m_treeWidgetMyContact->setHeaderHidden(true);
    m_treeWidgetMyContact->setIconSize(const_tree_icon_size);
    m_treeWidgetMyContact->setExpandsOnDoubleClick(false);
    m_treeWidgetMyContact->setMouseTracking(false);
    m_treeWidgetMyContact->setFrameShape(QFrame::NoFrame);
    m_treeWidgetMyContact->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_treeWidgetMyContact->setAllColumnsShowFocus(false);
    m_treeWidgetMyContact->setWordWrap(true);
    m_treeWidgetMyContact->setColumnCount(1);
    connect( m_treeWidgetMyContact,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onItemClicked(QTreeWidgetItem*,int)) );
    m_treeWidgetMyContact->setMouseTracking(true);
    connect( m_treeWidgetMyContact,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(onItemEntered(QTreeWidgetItem*,int)) );
    connect( m_treeWidgetMyContact,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)) );
    connect( m_treeWidgetMyContact,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(onItemChanged(QTreeWidgetItem*,int)) );

    /// “打开会话”按钮
    m_pushButtonCall = new QPushButton(this);
    m_pushButtonCall->setParent( m_treeWidgetMyContact );
    m_pushButtonCall->setVisible(false);
    m_pushButtonCall->setObjectName("CallButton");
    connect( m_pushButtonCall, SIGNAL(clicked()),this,SLOT(onClickedPushButtonCall()) );
    IconHelper::Instance()->SetIcon(m_pushButtonCall,QChar(0xf27a),12 );
    /// “修改我的名片”
    m_pushButtonEdit = new QPushButton(this);
    m_pushButtonEdit->setParent( m_treeWidgetMyContact );
    m_pushButtonEdit->setVisible(false);
    m_pushButtonEdit->setObjectName("CallButton");
    connect( m_pushButtonEdit, SIGNAL(clicked()),this,SLOT(onClickedPushButtonEdit()) );
    IconHelper::Instance()->SetIcon(m_pushButtonEdit,QChar(0xf2c3),12 );

    const std::string const_default_group_name = theLocales.getLocalStdString("name-text.default-group-name","Default Group");
    const EB_UGInfo ugInfo(const_default_group_ugid,const_default_group_name);
    onUGInfo(&ugInfo);
//    QString sGroupText;
//    if (theApp->isAuthContact())
//        sGroupText.Format(_T("%s [0]"),const_default_group_name.c_str());
//    else
//        sGroupText.Format(_T("%s (0)"),const_default_group_name.c_str());
//    HTREEITEM pGroupTreeItem = m_treeContacts.InsertItem(sGroupText);
//    EbWidgetItemInfo::pointer pContactInfo = EbWidgetItemInfo::create(EbWidgetItemInfo::ITEM_TYPE_GROUP,pGroupTreeItem);
//    pContactInfo->m_nSubType = -1;
//    pContactInfo->m_sId = const_default_group_ugid;
//    pContactInfo->m_sName = const_default_group_name;
//    m_treeContacts.SetItemData(pGroupTreeItem,(DWORD)pContactInfo.get());
//    m_pGroupItemInfo.insert(const_default_group_ugid, pContactInfo);

    updateLocaleInfo();
}

EbWidgetMyContact::~EbWidgetMyContact()
{
    m_pGroupItemInfo.clear();
    m_pContactItemInfo.clear();

}

void EbWidgetMyContact::updateLocaleInfo()
{
    m_pushButtonCall->setToolTip( theLocales.getLocalText("main-frame.button-call.tooltip","open chat") );
    m_pushButtonEdit->setToolTip( theLocales.getLocalText("main-frame.button-edit.tooltip","edit member info") );

}

void EbWidgetMyContact::timerCheckState()
{
    if ( this->isVisible() &&
         (m_pushButtonCall->isVisible() || m_pushButtonEdit->isVisible()) ) {
        /// 实现定期自动判断当前鼠标位置，并刷新 call 按钮
        const QRect& rect = m_treeWidgetMyContact->geometry();
        const QPoint pointMouseToDialog = this->mapFromGlobal(this->cursor().pos());
        if (!rect.contains(pointMouseToDialog)) {
            m_pushButtonCall->setVisible(false);
            m_pushButtonEdit->setVisible(false);
        }
    }
}

const EbWidgetItemInfo::pointer EbWidgetMyContact::onUGInfo(const EB_UGInfo *ugInfo)
{
//    if (ugInfo==0 || ugInfo->m_nUGId==0) {
//        return;
//    }
    bool bSortItems = false;
    EbWidgetItemInfo::pointer groupItemInfo;
    if (!m_pGroupItemInfo.find(ugInfo->m_nUGId,groupItemInfo)) {
        bSortItems = true;
        QString groupText;
        if ( theApp->isAuthContact() )
            groupText = QString("%1 [0]").arg(ugInfo->m_sGroupName.c_str());
        else
            groupText = QString("%1 (0)").arg(ugInfo->m_sGroupName.c_str());
        EbTreeWidgetItem * groupWidgetItem = new EbTreeWidgetItem(m_treeWidgetMyContact, QStringList(groupText));
        if (ugInfo->m_nUGId!=const_default_group_ugid) {
            groupWidgetItem->setFlags( groupWidgetItem->flags()|Qt::ItemIsEditable );
        }
        groupItemInfo = EbWidgetItemInfo::create(EbWidgetItemInfo::ITEM_TYPE_GROUP,groupWidgetItem);
        groupItemInfo->m_nSubType = -1;
        groupItemInfo->m_sId = ugInfo->m_nUGId;
        groupItemInfo->m_sName = ugInfo->m_sGroupName;
        groupWidgetItem->m_itemInfo = groupItemInfo;
        if (ugInfo->m_nUGId==const_default_group_ugid) {
            /// 默认分组，排在前面
            groupItemInfo->m_nIndex = 1;
        }
        m_treeWidgetMyContact->addTopLevelItem(groupWidgetItem);
        m_pGroupItemInfo.insert(ugInfo->m_nUGId,groupItemInfo);
        if (m_timeNewGroup>0 && time(0)-m_timeNewGroup<3) {
            m_timeNewGroup = 0;
            m_inGroupEdit = true;
            m_treeWidgetMyContact->editItem(groupWidgetItem);
            m_treeWidgetMyContact->setCurrentItem(groupWidgetItem);
        }
    }
    else {
        if (groupItemInfo->m_sName != ugInfo->m_sGroupName) {
            bSortItems = true;
        }
        groupItemInfo->m_sName = ugInfo->m_sGroupName;
        QString groupText;
        if ( theApp->isAuthContact() ) {
            int nContactSize = 0;
            int nOnlineSize = 0;
            theApp->m_ebum.EB_GetUGContactSize(groupItemInfo->m_sId,nContactSize,nOnlineSize);
            groupText = QString("%1 (%2/%3)").arg(ugInfo->m_sGroupName.c_str()).arg(nOnlineSize).arg(nContactSize);
        }
        else {
            groupText = QString("%1 (%2)").arg(ugInfo->m_sGroupName.c_str()).arg((int)groupItemInfo->m_dwItemData);
        }
        const bool oldInGroupEdit = m_inGroupEdit;
        m_inGroupEdit = false;
        groupItemInfo->m_hItem->setText(0,groupText);
        m_inGroupEdit = oldInGroupEdit;
    }

    if (bSortItems) {
        m_treeWidgetMyContact->sortItems( 0,Qt::AscendingOrder );
    }
    return groupItemInfo;
}

void EbWidgetMyContact::onUGDelete(const EB_UGInfo *ugInfo)
{
    EbWidgetItemInfo::pointer groupItemInfo;
    if (!m_pGroupItemInfo.find(ugInfo->m_nUGId,groupItemInfo,true)) {
        return;
    }

    {
        EbWidgetItemInfo::pointer defaultGroupItemInfo;
//        QString sContactText;
        /// 先处理该分组下面，并移到默认分组去；
        AUTO_RLOCK(m_pContactItemInfo);
        CLockMap<eb::bigint,EbWidgetItemInfo::pointer>::const_iterator pIter;
        for (pIter=m_pContactItemInfo.begin(); pIter!=m_pContactItemInfo.end(); pIter++) {
            const EbWidgetItemInfo::pointer& pContactItemInfo = pIter->second;
            if (pContactItemInfo->m_sParentId == groupItemInfo->m_sId) {

                if (defaultGroupItemInfo.get()==0) {
                    if (!m_pGroupItemInfo.find(const_default_group_ugid,defaultGroupItemInfo)) {
                        continue;
                    }
                }
                pContactItemInfo->m_sParentId = defaultGroupItemInfo->m_sId;
                defaultGroupItemInfo->m_dwItemData++;

                /// 移到默认分组去；
//                sContactText.Format(_T("%s"), pContactItemInfo->m_sName.c_str());
//                pContactItemInfo->m_hItem = m_treeContacts.InsertItem(sContactText,pDefaultGroupItemInfo->m_hItem);
//                m_treeContacts.SetItemData(pContactItemInfo->m_hItem,(DWORD)pContactItemInfo.get());
            }
        }
        if (defaultGroupItemInfo.get()!=0) {
            /// 有移到默认分组，重新设置一次数量；
            QString groupText;
            if (theApp->isAuthContact()) {
                int nContactSize = 0;
                int nOnlineSize = 0;
                theApp->m_ebum.EB_GetUGContactSize(0,nContactSize,nOnlineSize);
                groupText = QString("%1 [%2/%3]").arg(defaultGroupItemInfo->m_sName.c_str()).arg(nOnlineSize).arg(nContactSize);
            }
            else {
                groupText = QString("%1 (%2)").arg(defaultGroupItemInfo->m_sName.c_str()).arg((int)defaultGroupItemInfo->m_dwItemData);
            }
//            const QString groupText = QString("%1 (%2)").arg(defaultGroupItemInfo->m_sName.c_str()).arg((int)defaultGroupItemInfo->m_dwItemData);
            defaultGroupItemInfo->m_hItem->setText(0,groupText);
        }
    }

    deleteGroupItem(groupItemInfo->m_hItem);
}

void EbWidgetMyContact::onContactInfo(const EB_ContactInfo *contactInfo)
{
    if (contactInfo==0 || contactInfo->m_nContactId==0) {
        return;
    }
    const eb::bigint nUGId = contactInfo->m_nUGId==0?const_default_group_ugid:contactInfo->m_nUGId;
    QString groupText;
    EbWidgetItemInfo::pointer pGroupItemInfo;
    if (!m_pGroupItemInfo.find(nUGId,pGroupItemInfo)) {
        const EB_UGInfo ugInfo(nUGId,contactInfo->m_sGroupName);
        pGroupItemInfo = onUGInfo(&ugInfo);
    }
    const QString sContactText = contactInfo->m_sName.c_str();
    EbWidgetItemInfo::pointer pContactItemInfo;
    bool bChangeGroupCount = false;
    bool bChangeLineState = false;
    if (!m_pContactItemInfo.find(contactInfo->m_nContactId, pContactItemInfo)) {
        pGroupItemInfo->m_dwItemData++;
        bChangeGroupCount = true;

        EbTreeWidgetItem * contactWidgetItem = new EbTreeWidgetItem(pGroupItemInfo->m_hItem, QStringList(sContactText));
        pContactItemInfo = EbWidgetItemInfo::create(EbWidgetItemInfo::ITEM_TYPE_CONTACT,contactWidgetItem);
        contactWidgetItem->m_itemInfo = pContactItemInfo;
        pGroupItemInfo->m_hItem->addChild(contactWidgetItem);
        m_pContactItemInfo.insert(contactInfo->m_nContactId,pContactItemInfo);
    }
    else if (pContactItemInfo->m_sParentId != contactInfo->m_nUGId) {
        /// change group
        EbTreeWidgetItem * parentWidgetItem = (EbTreeWidgetItem*)pContactItemInfo->m_hItem->parent();
        const EbWidgetItemInfo::pointer pOldGroupItemInfo = parentWidgetItem==0?EbWidgetItemInfoNull:parentWidgetItem->m_itemInfo;
        if (pOldGroupItemInfo.get()!=0 && pOldGroupItemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_GROUP) {
            if (pOldGroupItemInfo->m_dwItemData>1 || pOldGroupItemInfo->m_sGroupCode==0) {
                /// empty是默认分组
                pOldGroupItemInfo->m_dwItemData--;
                if (theApp->isAuthContact()) {
                    int nContactSize = 0;
                    int nOnlineSize = 0;
                    theApp->m_ebum.EB_GetUGContactSize(pOldGroupItemInfo->m_sId,nContactSize,nOnlineSize);
                    groupText = QString("%1 [%2/%3]").arg(pOldGroupItemInfo->m_sName.c_str()).arg(nOnlineSize).arg(nContactSize);
                }
                else {
                    groupText = QString("%1 (%2)").arg(pOldGroupItemInfo->m_sName.c_str()).arg((int)pOldGroupItemInfo->m_dwItemData);
                }
                pOldGroupItemInfo->m_hItem->setText(0,groupText);
            }
            else {
//            else// if (pOldGroupItemInfo->m_dwItemData<=0 && !pOldGroupItemInfo->m_sGroupCode.empty()) {
                /// 无用分组，删除
                deleteGroupItem(pOldGroupItemInfo->m_hItem);
                m_pGroupItemInfo.remove(pOldGroupItemInfo->m_sId);
            }
            pOldGroupItemInfo->m_hItem->removeChild( pContactItemInfo->m_hItem );
        }
        m_pContactItemInfo.remove(contactInfo->m_nContactId);

        pGroupItemInfo->m_dwItemData++;
        bChangeGroupCount = true;

        EbTreeWidgetItem * contactWidgetItem = new EbTreeWidgetItem(pGroupItemInfo->m_hItem, QStringList(sContactText));
        pContactItemInfo = EbWidgetItemInfo::create(EbWidgetItemInfo::ITEM_TYPE_CONTACT,contactWidgetItem);
        contactWidgetItem->m_itemInfo = pContactItemInfo;
        pGroupItemInfo->m_hItem->addChild(contactWidgetItem);
        m_pContactItemInfo.insert(contactInfo->m_nContactId,pContactItemInfo);
    }
    else {
        if (theApp->isAuthContact()) {
            if ((pContactItemInfo->m_dwItemData <= EB_LINE_STATE_OFFLINE && contactInfo->m_nLineState>=EB_LINE_STATE_BUSY) ||	/// 下线
                (pContactItemInfo->m_dwItemData >= EB_LINE_STATE_BUSY && contactInfo->m_nLineState<=EB_LINE_STATE_OFFLINE)) {	/// 上线
                bChangeLineState = true;
            }
        }
        pContactItemInfo->m_hItem->setText(0, sContactText);
    }
    pContactItemInfo->updateContactInfo(contactInfo);

    if (bChangeGroupCount || bChangeLineState) {
        if (theApp->isAuthContact()) {
            int nContactSize = 0;
            int nOnlineSize = 0;
            theApp->m_ebum.EB_GetUGContactSize(pGroupItemInfo->m_sId,nContactSize,nOnlineSize);
            groupText = QString("%1 [%2/%3]").arg(pGroupItemInfo->m_sName.c_str()).arg(nOnlineSize).arg(nContactSize);
        }
        else {
            groupText = QString("%1 (%2)").arg(pGroupItemInfo->m_sName.c_str()).arg((int)pGroupItemInfo->m_dwItemData);
        }
        pGroupItemInfo->m_hItem->setText(0, groupText);
    }
    if (pGroupItemInfo->m_dwItemData>1) {
        pGroupItemInfo->m_hItem->sortChildren( 0,Qt::AscendingOrder );
    }
}

void EbWidgetMyContact::onContactDelete(const EB_ContactInfo *contactInfo)
{
    EbWidgetItemInfo::pointer contactItemInfo;
    if (m_pContactItemInfo.find(contactInfo->m_nContactId, contactItemInfo, true)) {
        EbTreeWidgetItem * parentWidgetItem = (EbTreeWidgetItem*)contactItemInfo->m_hItem->parent();
        const EbWidgetItemInfo::pointer pGroupItemInfo = parentWidgetItem==0?EbWidgetItemInfoNull:parentWidgetItem->m_itemInfo;
        if (pGroupItemInfo.get()!=0) {
            if (pGroupItemInfo->m_dwItemData>0)
                pGroupItemInfo->m_dwItemData--;
            //const eb::bigint nUGId = pGroupItemInfo->m_sId;
            //if (pGroupItemInfo->m_dwItemData == 0 && nUGId != const_default_group_ugid)
            //{
            //	// delete group item
            //	m_pGroupItemInfo.remove(nUGId);
            //	m_treeContacts.DeleteItem(hGroupItem);
            //}else
            {
                QString sGroupText;
                if (theApp->isAuthContact()) {
                    int nContactSize = 0;
                    int nOnlineSize = 0;
                    theApp->m_ebum.EB_GetUGContactSize(pGroupItemInfo->m_sId,nContactSize,nOnlineSize);
                    sGroupText = QString("%1 [%2/%3]").arg(pGroupItemInfo->m_sName.c_str()).arg(nOnlineSize).arg(nContactSize);
                }
                else {
                    sGroupText = QString("%1 (%2)").arg(pGroupItemInfo->m_sName.c_str()).arg((int)pGroupItemInfo->m_dwItemData);
                }
                pGroupItemInfo->m_hItem->setText(0,sGroupText);
            }
//            m_treeContacts.Expand(hGroupItem, TVE_EXPAND);
            parentWidgetItem->removeChild(contactItemInfo->m_hItem);
        }
//        m_treeContacts.DeleteItem(pContactItemInfo->m_hItem);
    }
}

void EbWidgetMyContact::onContactHeadChange(const EB_ContactInfo *contactInfo)
{

}

void EbWidgetMyContact::onItemDoubleClicked(QTreeWidgetItem *item, int /*column*/)
{
    const EbTreeWidgetItem* ebitem = (EbTreeWidgetItem*)item;
    if (ebitem->m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_GROUP) {
        m_inGroupEdit = true;
    }
    else if (ebitem->m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_CONTACT) {
        createMenuData();
        m_contextMenu->onCallItem(ebitem->m_itemInfo);
    }
}

void EbWidgetMyContact::onItemClicked(QTreeWidgetItem *item, int /*column*/)
{
    m_inGroupEdit = false;
    const EbTreeWidgetItem* itemEb = (EbTreeWidgetItem*)item;
    const EbWidgetItemInfo::ITEM_TYPE itemType = itemEb->m_itemInfo->m_nItemType;
    if (itemType==EbWidgetItemInfo::ITEM_TYPE_GROUP) {
        if (item->isExpanded()) {
            m_treeWidgetMyContact->collapseItem(item);
        }
        else {
            m_treeWidgetMyContact->expandItem(item);
        }
    }
}
void EbWidgetMyContact::onItemEntered(QTreeWidgetItem *item, int /*column*/)
{
    if (!m_treeWidgetMyContact->hasFocus()) {
        m_treeWidgetMyContact->setFocus();
    }
    /// 滚动条能正常显示
    const QRect rectItem = m_treeWidgetMyContact->visualItemRect(item);
    const QPoint pointItem = m_treeWidgetMyContact->mapToParent(rectItem.topRight());
    const int y = pointItem.y();
    /// -2（配合下面的 y+1）实现删除按钮显示时，保留ITEM边框，
    const int buttonSize = rectItem.height()-2;
    const EbTreeWidgetItem* itemEb = (EbTreeWidgetItem*)item;
    if ( itemEb->m_itemInfo->m_nItemType!=EbWidgetItemInfo::ITEM_TYPE_CONTACT ) {
        m_pushButtonEdit->setVisible(false);
        m_pushButtonCall->setVisible(false);
        return;
    }
    m_pushButtonEdit->setGeometry( pointItem.x()-buttonSize,y+1,buttonSize,buttonSize );
    m_pushButtonEdit->setProperty("track-item",QVariant((quint64)item));
    m_pushButtonEdit->setVisible(true);
    m_pushButtonCall->setGeometry( pointItem.x()-buttonSize*2,y+1,buttonSize,buttonSize );
    m_pushButtonCall->setProperty("track-item",QVariant((quint64)item));
    m_pushButtonCall->setVisible(true);
}

void EbWidgetMyContact::onItemChanged(QTreeWidgetItem *item, int column)
{
    const EbTreeWidgetItem* ebitem = (EbTreeWidgetItem*)item;
    if ( m_inGroupEdit && ebitem->m_itemInfo->m_nItemType==EbWidgetItemInfo::ITEM_TYPE_GROUP ) {
        m_inGroupEdit = false;
        std::string newGroupName = item->text(column).toStdString();
        if (newGroupName.empty()) {
            newGroupName = theLocales.getLocalStdString("name-text.unname-group","Unname Group");
        }
        else {
            std::string::size_type find = newGroupName.rfind(" (");
            if (find==std::string::npos)
                find = newGroupName.rfind(" [");
            if (find!=std::string::npos) {
                /// 去掉后面 " (%1/%2)" 字符 或
                /// 去掉后面 " [%1]" 字符
                newGroupName = newGroupName.substr(0,find);
            }

        }
        theApp->m_ebum.EB_EditUGInfo( ebitem->m_itemInfo->m_sId,newGroupName.c_str() );
    }
}

void EbWidgetMyContact::onClickedPushButtonCall()
{
    const EbTreeWidgetItem * item = (EbTreeWidgetItem*)m_pushButtonCall->property("track-item").toULongLong();
    if (item!=0) {
        createMenuData();
        m_contextMenu->onCallItem(item->m_itemInfo);
    }
    m_pushButtonCall->hide();
    m_pushButtonCall->setProperty("track-item",QVariant((quint64)0));
    m_treeWidgetMyContact->setFocus();
}

void EbWidgetMyContact::onClickedPushButtonEdit()
{
    const EbTreeWidgetItem* item = (EbTreeWidgetItem*)m_pushButtonEdit->property("track-item").toULongLong();
    if (item==0) {
        return;
    }
    m_pushButtonEdit->hide();
    m_pushButtonEdit->setProperty("track-item",QVariant((quint64)0));
    m_treeWidgetMyContact->setFocus();
    createMenuData();
    m_contextMenu->onEditItem(item->m_itemInfo);
}

void EbWidgetMyContact::onAddContactGroup()
{
    m_timeNewGroup = time(0);
    const std::string text = theLocales.getLocalStdString("name-text.unname-group","Unname Group");
    theApp->m_ebum.EB_EditUGInfo(0, text.c_str());

//    QTreeWidget * treeWidget = m_itemInfo->m_hItem->treeWidget();
//    //        treeWidget->setEditTriggers(QTreeWidget::AllEditTriggers);
//    EbTreeWidgetItem * groupWidgetItem = new EbTreeWidgetItem(treeWidget, QStringList("unname group"));
//    groupWidgetItem->m_itemInfo = EbWidgetItemInfo::create(EbWidgetItemInfo::ITEM_TYPE_GROUP,groupWidgetItem);
//    groupWidgetItem->setFlags( groupWidgetItem->flags()|Qt::ItemIsEditable );
//    treeWidget->addTopLevelItem(groupWidgetItem);
//    treeWidget->setCurrentItem(groupWidgetItem);
//    treeWidget->editItem(groupWidgetItem);
}

void EbWidgetMyContact::resizeEvent(QResizeEvent *e)
{
    m_treeWidgetMyContact->setGeometry( 0,0,width(),height() );
    QWidget::resizeEvent(e);
}

void EbWidgetMyContact::createMenuData()
{
    if (m_contextMenu==0) {
        m_contextMenu = new EbContextMenu( EbContextMenu::MyContact, this );
        connect( (const QObject*)m_contextMenu,SIGNAL(addContactGroup()),this,SLOT(onAddContactGroup()) );
    }
}

void EbWidgetMyContact::contextMenuEvent(QContextMenuEvent *e)
{
    createMenuData();
    const EbTreeWidgetItem* item = (EbTreeWidgetItem*)m_treeWidgetMyContact->itemAt(e->pos());
    const EbWidgetItemInfo::pointer itemInfo = item==0?EbWidgetItemInfoNull:item->m_itemInfo;
    if (!m_contextMenu->updateMenuItem(itemInfo)) {
        return;
    }
    m_contextMenu->exec( e->globalPos() );
}

void EbWidgetMyContact::deleteGroupItem(QTreeWidgetItem *groupItem)
{
    QTreeWidgetItem * item = m_treeWidgetMyContact->takeTopLevelItem( m_treeWidgetMyContact->indexOfTopLevelItem(groupItem) );
    if (item!=0) {
        delete item;
    }

}

