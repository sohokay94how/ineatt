#include "ebdialoglogin.h"
#include "ui_ebdialoglogin.h"
#include <QMouseEvent>
#include <QMenu>
#include "ebiconhelper.h"
#include "ebclientapp.h"
#include "ebdialogregister.h"
#include "ebdialogconnectsetting.h"
#include "ebmessagebox.h"

//const int const_listwidget_item_height = 24;

CLoginInfo::CLoginInfo()
    : m_bSafePwd(false)
{

}
CLoginInfo::CLoginInfo(const cgcSmartString &sAccount, const cgcSmartString &sPassword, bool bSafePwd)
    : m_sAccount(sAccount)
    , m_sPassword(sPassword)
    , m_bSafePwd(bSafePwd)
    , m_nLineState(EB_LINE_STATE_UNKNOWN)
    , m_nUserId(0), m_nPhone(0)
//        , m_hItem(NULL)
    , m_item(NULL)
{

}
CLoginInfo::pointer CLoginInfo::create(const mycp::tstring& sAccount, const mycp::tstring& sPassword, bool bSafePwd)
{
    return CLoginInfo::pointer(new CLoginInfo(sAccount, sPassword, bSafePwd));
}


EbDialogLogin::EbDialogLogin(QWidget *parent)
    : EbDialogBase(parent)
    , ui(new Ui::EbDialogLogin)
    , m_menuSetting(NULL)
    , m_labelEntLogo(NULL)
    , m_labelAccountIcon(0)
    , m_isDefaultEntLogo(false)

    , m_inMessageBox(false)
    , m_canSearch(true), m_searchFirst(true)

{
    /// 设置窗口图标
    setWindowIcon(QIcon(QStringLiteral(":/res/mainframe.ico")));

//    QTimer::singleShot( 1, this, SLOT(processDatas()) );
    ui->setupUi(this);

    /// 设置初始大小
    const int const_dialog_login_width = theLocales.getLocalInt("login-dialog.window-size.width", 288);
    const int const_dialog_login_height = theLocales.getLocalInt("login-dialog.window-size.height", 588);
    const QSize const_dialog_login_size(const_dialog_login_width,const_dialog_login_height);
//    const QSize const_dialog_login_size(288,588);
    this->resize(const_dialog_login_size);
    /// 去掉标题栏
    this->setWindowFlags( Qt::Window|Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint);
    /// 设置位置，显示在上面
    this->showTitleBackground(190);

    updateLocaleInfo();
    /// 屏蔽 ESC 按键不退出
    this->setFilterEscapeKey(true);

    /// 产品名称 & 登录LOGO
    updateProductName();
    updateEntLogo(theApp->getAppImgPath() + "/entlogo");    // 企业定制LOGO，空或不存在使用系统默认

//    this->setStyleSheet("QWidget{border-top-left-radius:15px;border-top-right-radius:5px;}");
//    this->setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:5px;}");
    EbIconHelper::Instance()->SetIcon(ui->pushButtonSetting,QChar(0xf0d7),10);
    {
//        ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/new/icons/icons/play.png);}"
//                                      "QPushButton:hover{border-image: url(:/new/icons/icons/play-hover.png);}"
//                                      "QPushButton:pressed{border-image: url(:/new/icons/icons/play-pressed.png);}");

        // **例子
//        QString sButtonStyle = "QPushButton{background-color:black;color: white;   border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
//                               "QPushButton:hover{background-color:white; color: black;}"
//                               "QPushButton:pressed{background-color:rgb(85, 170, 255);border-style: inset; }";

        int x = const_dialog_login_size.width()-this->getSysButtonWidth()-const_sys_button_size.width();
        ui->pushButtonSetting->setGeometry( x,0,const_sys_button_size.width(),const_sys_button_size.height() );
        ui->pushButtonSetting->setObjectName("SysTransButton");

//        QString strTest("Tst");
//        4     QString strSerInfo;
//        5     strSerInfo = QString("%1 %2").arg(strTest).arg(m_baudRateCur);
//        6     hintSerSts->setText(strSerInfo);

        // 圆角样式: border-radius: 2px;
//        QString sButtonStyle = "QPushButton{background-color:rgb(0,0,0,0); color: white; border-radius: 0px;}"
//                               "QPushButton:hover{background-color:rgb(100,162,232,180); color: white;}"
//                               "QPushButton:pressed{background-color:rgb(100,162,232,220); border-style: inset; }";

//        ui->pushButton->setStyleSheet("QPushButton:hover{background-color: rgb(170, 0, 255);}");
//        ui->pushButton->setStyleSheet("background-color: rgb(170, 0, 255);");
//        // 圆角控件
//        ui->pushButton->setStyleSheet ("border:2px groovegray;border-radius:10px;padding:2px 4px;");

//        QPalette pPaletteBg(ui->pushButton->palette());
//        // 普通状态
//        pPaletteBg.setColor(QPalette::Button, QColor(250,162,232));
//        pPaletteBg.setColor(QPalette::ButtonText, QColor(255,0,0));
////        // 激活状态
////        pPaletteBg.setColor(QPalette::Active, QPalette::Button, QColor(0,0,232));
////        pPaletteBg.setColor(QPalette::Active, QPalette::ButtonText, QColor(255,128,0));

////        // 点击状态
////        pPaletteBg.setColor(QPalette::Inactive, QPalette::Button, QColor(0,128,232));
////        pPaletteBg.setColor(QPalette::Inactive, QPalette::ButtonText, QColor(255,128,128));

//        ui->pushButton->setAutoFillBackground(true);
//        ui->pushButton->setPalette(pPaletteBg);


        // 帐号 & 密码，包括小图标和，用户列表控件
        const int const_left_interval = 35;
        const int const_edit_width = const_dialog_login_size.width()-const_left_interval*2;
        const int const_edit_icon_size = const_common_edit_height-4;   // 18
        m_labelAccountIcon = new EbLabel(this);
        m_labelAccountIcon->setGeometry( 84,50,120,120 );
        m_labelAccountIcon->setCursor( QCursor(Qt::PointingHandCursor) );
        EbIconHelper::Instance()->SetIcon(m_labelAccountIcon,QChar(0xf2c0),11);
        m_labelAccountIcon->setObjectName("IconLabel");
        m_labelAccountIcon->resize(const_edit_icon_size,const_edit_icon_size);
//        m_labelAccountIcon->setParent(ui->lineEditAccount);
        m_labelAccountIcon->raise();
        m_labelAccountIcon->setCursor( QCursor(Qt::PointingHandCursor) );
//        m_labelAccountIcon->installEventFilter(this);
        connect( m_labelAccountIcon,SIGNAL(clicked()),this,SLOT(onClickedLabelAccountIcon()) );
        ui->listWidgetLoginRecords->setVisible(false);
        ui->pushButtonDeleteAccount->setVisible(false);
        ui->pushButtonDeleteAccount->setObjectName("DeleteButton");
        EbIconHelper::Instance()->SetIcon(ui->pushButtonDeleteAccount,QChar(0xf00d),10 );
        /// for test data
//        for (int i=0; i<10; i++) {
//            QListWidgetItem * pItem0 = new QListWidgetItem("user1", ui->listWidgetLoginRecords);
//            ui->listWidgetLoginRecords->insertItem( i, pItem0 );
//        }
        EbIconHelper::Instance()->SetIcon(ui->labelPasswordIcon,QChar(0xf084),11);
        ui->labelPasswordIcon->setStyleSheet( "QLabel{background-color:rgb(0,0,0,0); color: rgb(128,128,128); border-radius: 0px;}" );
        ui->labelPasswordIcon->resize(const_edit_icon_size,const_edit_icon_size);
        ui->labelPasswordIcon->setParent(ui->lineEditPassword);
        ui->labelPasswordIcon->raise();
        int y = 218;
        ui->lineEditAccount->setGeometry( const_left_interval, y,const_edit_width, const_common_edit_height );
        m_labelAccountIcon->move( const_dialog_login_size.width()-const_left_interval-const_edit_icon_size-2,y+2 );
        ui->listWidgetLoginRecords->raise();
        ui->listWidgetLoginRecords->setGeometry( const_left_interval,y+const_common_edit_height+1,const_edit_width,96);
        ui->pushButtonDeleteAccount->raise();
        y += (const_common_edit_height + 10);
        ui->lineEditPassword->installEventFilter(this);
        ui->lineEditPassword->setGeometry( const_left_interval, y,const_edit_width, const_common_edit_height );
        ui->labelPasswordIcon->move( const_edit_width-const_edit_icon_size-2,2 );
//        ui->labelPasswordIcon->move( const_dialog_login_size.width()-const_left_interval-const_edit_icon_size-2,y+2 );
        y += (const_common_edit_height + 10);
        // 记住密码 & 开机启动
//        ui->checkBoxSavePwd->setObjectName("CheckBoxSelect");
//        ui->checkBoxAutoRun->setObjectName("CheckBoxSelect");
#ifdef WIN32
        const int const_checkbox_width = 70;
#else
        const int const_checkbox_width = 75;
#endif
        const int const_checkbox_height = 14;
        ui->checkBoxSavePwd->setGeometry( const_left_interval, y,const_checkbox_width, const_checkbox_height );
        ui->checkBoxAutoRun->setGeometry( const_dialog_login_size.width()-const_checkbox_width-const_left_interval, y,
                                          const_checkbox_width, const_checkbox_height);

        // 错误文本
        const int const_error_text_height = 36;
        y += (const_checkbox_height+4);
        ui->labelErrorText->setWordWrap(true);
        ui->labelErrorText->setGeometry( const_left_interval, y,const_dialog_login_size.width()-const_left_interval,const_error_text_height );
        ui->labelErrorText->setAlignment( Qt::AlignLeft|Qt::AlignTop);
        ui->labelErrorText->setStyleSheet("QLabel{background-color:rgb(0,0,0,0); color: rgb(255,0,64);}");
        setErrorText( "",false );
//        setErrorText("错误日志测试<br>错误日志测试第二行");

        // 登录按钮
        y += (const_error_text_height+4);
        ui->pushButtonLogon->setObjectName( "OkButton" );
        ui->pushButtonLogon->setDefault(true);
        ui->pushButtonLogon->setGeometry( const_left_interval, y,const_edit_width, 32 );

        // 下面四按钮
        ui->pushButtonVisitorLogon->setObjectName("BorderButton");
        ui->pushButtonRegister->setObjectName("BorderButton");
        ui->pushButtonForgetPwd->setObjectName("BorderButton");
        ui->pushButtonConnectSetting->setObjectName("BorderButton");
        x = 10;
        y = height()-30;
        const QSize const_button_size2(60, 19);
        const int const_button_interval = const_button_size2.width()+9;
        // 游客登录
        ui->pushButtonVisitorLogon->setGeometry( x,y,const_button_size2.width(),const_button_size2.height() );
        ui->pushButtonVisitorLogon->setVisible(false);
        x += const_button_interval;
        // 我要注册
        ui->pushButtonRegister->setGeometry( x,y,const_button_size2.width(),const_button_size2.height() );
        ui->pushButtonRegister->setVisible(false);
        x += const_button_interval;
        // 忘记密码
        ui->pushButtonForgetPwd->setGeometry( x,y,const_button_size2.width(),const_button_size2.height() );
        ui->pushButtonForgetPwd->setVisible(false);
        x += const_button_interval;
        // 连接设置
        ui->pushButtonConnectSetting->setGeometry( x,y,const_button_size2.width(),const_button_size2.height() );

//        refreshSkin();
    }
    // *** 必须放在 listWidgetLoginRecords->setGeometry 后面；
    QTimer::singleShot( 1, this, SLOT(processDatas()) );
//    QString sWindowText = theLocales.getLocalText("login-dialog.window-text","登录界面");
//    sWindowText.replace( "[PRODUCT_NAME]", theApp->productName() );
////    char sSetWindowText[260];
////    sprintf(sWindowText,"恩布登录界面");
//    this->setWindowTitle(sWindowText);
//    this->setWindowState(Qt::WindowNoState);

//    {
////        ui->pushButtonSetting->setMenu(m_menuSetting);
////        // 去掉弹出菜单下拉三角图标
////        ui->pushButtonSetting->setStyleSheet("QPushButton::menu-indicator{image:None;}");

//    }

    connect( ui->pushButtonSetting,SIGNAL(clicked()),this,SLOT(onClickPushButtonSetting()) );
    connect( ui->pushButtonLogon,SIGNAL(clicked()),this,SLOT(onClickPushButtonLogon()) );

    ui->lineEditAccount->installEventFilter(this);
    connect(ui->lineEditAccount, SIGNAL(textChanged(QString)), this, SLOT(onTextChangedEditAccount(QString)));

    ui->listWidgetLoginRecords->installEventFilter(this);
//    connect(ui->listWidgetLoginRecords, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemClickedLoginRecords(QListWidgetItem*)));
    connect(ui->listWidgetLoginRecords, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClickedLoginRecords(QListWidgetItem*)));
    connect(ui->listWidgetLoginRecords, SIGNAL(itemSelectionChanged()), this, SLOT(onItemSelectionChangedLoginRecords()));
//    connect(ui->listWidgetLoginRecords, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemClickedLoginRecords(QListWidgetItem*)));
    ui->listWidgetLoginRecords->setMouseTracking(true);
    connect(ui->listWidgetLoginRecords, SIGNAL(itemEntered(QListWidgetItem*)), this, SLOT(onItemEnteredLoginRecords(QListWidgetItem*)));
//    connect(ui->listWidgetLoginRecords, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(onCurrentItemChangedLoginRecords(QListWidgetItem*,QListWidgetItem*)));
//    connect(ui->listWidgetLoginRecords, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChangedLoginRecords(int)));
    connect( ui->pushButtonDeleteAccount, SIGNAL(clicked()),this,SLOT(onClickPushButtonDeleteAccount()) );


    connect( ui->pushButtonVisitorLogon,SIGNAL(clicked()),this,SLOT(onClickPushButtonVisitor()) );
    connect( ui->pushButtonRegister,SIGNAL(clicked()),this,SLOT(onClickPushButtonRegister()) );
    connect( ui->pushButtonForgetPwd,SIGNAL(clicked()),this,SLOT(onClickPushButtonForgetPwd()) );
    connect( ui->pushButtonConnectSetting,SIGNAL(clicked()),this,SLOT(onClickPushButtonConnectSetting()) );
}

EbDialogLogin::~EbDialogLogin()
{
    delete ui;
}

void EbDialogLogin::updateLocaleInfo()
{
    /// 显示右上角关闭按钮
    this->showPushButtonSysClose( theLocales.getLocalText("base-dialog.close-button.tooltip","Close") );
    this->showPushButtonSysMin( theLocales.getLocalText("base-dialog.minimize-button.tooltip","Minimize") );

    ui->pushButtonSetting->setToolTip( theLocales.getLocalText("base-dialog.setting-button.tooltip","Setting") );
    ui->lineEditAccount->setToolTip( theLocales.getLocalText("login-dialog.edit-account.tooltip","") );
    ui->lineEditAccount->setPlaceholderText( theLocales.getLocalText("login-dialog.edit-account.bg-text","Account") );
    ui->pushButtonDeleteAccount->setToolTip( theLocales.getLocalText("login-dialog.button-delete-account.tooltip","删除帐号信息") );
    ui->lineEditPassword->setToolTip( theLocales.getLocalText("login-dialog.edit-password.tooltip","") );
    ui->lineEditPassword->setPlaceholderText( theLocales.getLocalText("login-dialog.edit-password.bg-text","Password") );
    ui->checkBoxSavePwd->setText( theLocales.getLocalText("login-dialog.checkbox-savepwd.text","SavePwd") );
    ui->checkBoxAutoRun->setText( theLocales.getLocalText("login-dialog.checkbox-autorun.text","AutoRun") );
    ui->pushButtonLogon->setText( theLocales.getLocalText("login-dialog.button-logon.text","Login") );
    ui->pushButtonLogon->setToolTip( theLocales.getLocalText("login-dialog.button-logon.tooltip","") );
    ui->pushButtonVisitorLogon->setText( theLocales.getLocalText("login-dialog.button-visitor-logon.text","Visitor") );
    ui->pushButtonVisitorLogon->setToolTip( theLocales.getLocalText("login-dialog.button-visitor-logon.tooltip","") );
    ui->pushButtonRegister->setText( theLocales.getLocalText("login-dialog.button-register.text","Resister") );
    ui->pushButtonRegister->setToolTip( theLocales.getLocalText("login-dialog.button-register.tooltip","") );
    ui->pushButtonForgetPwd->setText( theLocales.getLocalText("login-dialog.button-forget-pwd.text","Forget Pwd") );
    ui->pushButtonForgetPwd->setToolTip( theLocales.getLocalText("login-dialog.button-forget-pwd.tooltip","") );
    ui->pushButtonConnectSetting->setText( theLocales.getLocalText("login-dialog.button-connect-setting.text","Connect Setting") );
    ui->pushButtonConnectSetting->setToolTip( theLocales.getLocalText("login-dialog.button-connect-setting.tooltip","") );

}

//void EbDialogLogin::refreshSkin(void)
//{
//    this->showTitleBackground(theApp->getMainColor(), 190);
//}

void EbDialogLogin::updateEntLogo(const QString& fileName)
{
    const bool bFirstUpdate = (m_labelEntLogo==NULL)?true:false;
    if (m_labelEntLogo==NULL) {
        m_labelEntLogo = new EbLabel(this);
        m_labelEntLogo->setGeometry( 84,50,120,120 );
        m_labelEntLogo->setCursor( QCursor(Qt::PointingHandCursor) );
//        m_labelEntLogo->setStyleSheet ("border:2px groove gray;border-radius:10px;padding:2px 4px");  // 不行
//        m_labelEntLogo->setStyleSheet("QLabel{background-color:rgb(0,0,0,0); color: white; border-radius: 2px;}");
        connect( m_labelEntLogo, SIGNAL(clicked()),this,SLOT(onClickedEntLogo()) );
    }
    if (fileName.isEmpty() || !QFile::exists(fileName)) {
        if (!bFirstUpdate && m_isDefaultEntLogo)
        m_isDefaultEntLogo = true;
        m_labelEntLogo->setPixmap( QPixmap(":/res/entlogo").scaled(120,120,Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
    }
    else {
        m_isDefaultEntLogo = false;
        m_labelEntLogo->setPixmap( QPixmap(fileName).scaled(120,120,Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
    }
//    m_labelEntLogo->setPixmap( QPixmap::fromImage(QImage(qApp->applicationDirPath()+"/img/entlogo.png")).scaled(120,120,Qt::IgnoreAspectRatio, Qt::SmoothTransformation) );
    m_labelEntLogo->show();
}

void EbDialogLogin::updateProductName(void)
{
    this->showTitleLogoText( theApp->productName(),const_common_title_font_size );
//    this->showTitleLogoText( tr("恩布互联"),11 );

    QString sWindowText = theLocales.getLocalText("login-dialog.window-text","登录界面");
    sWindowText.replace( "[PRODUCT_NAME]", theApp->productName() );
//    char sSetWindowText[260];
//    sprintf(sWindowText,"恩布登录界面");
    this->setWindowTitle(sWindowText);

}

void EbDialogLogin::setErrorText(const QString& errorText, bool bMessageShowError)
{
    ui->labelErrorText->setText(errorText);
    ui->labelErrorText->setToolTip(errorText);
    ui->labelErrorText->setVisible(errorText.isEmpty()?false:true);
    if ( bMessageShowError && !errorText.isEmpty() ) {
        EbMessageBox::doShow( NULL, "", QChar::Null, errorText, EbMessageBox::IMAGE_WARNING,default_warning_auto_close );
    }
}

void EbDialogLogin::processDatas(void)
{
    // 加载本机登录帐号
    loadLoginData();
    // 创建“setting”菜单数据
    createMenuData();

    ui->pushButtonLogon->setEnabled(false);
    if ( !theApp->setDevAppId(this) ) {
        // ?
    }

}
void EbDialogLogin::setLoginInfo(QListWidgetItem* item, bool bAccountSelect)
{
    const mycp::bigint userId = item->data(Qt::UserRole).toLongLong();
    CLoginInfo::pointer loginInfo;
    if (m_pLoginInfoList.find(userId, loginInfo)) {
        setLoginInfo( loginInfo,bAccountSelect );
     }
}
void EbDialogLogin::setLoginInfo(const CLoginInfo::pointer& loginInfo, bool bAccountSelect)
{
    ui->checkBoxSavePwd->setChecked( loginInfo->m_bSafePwd );
    ui->lineEditAccount->setText( loginInfo->m_sAccount.c_str() );
    if (loginInfo->m_bSafePwd && loginInfo->m_sPassword.size()==32) {
        m_sOAuthKey = loginInfo->m_sPassword;
        ui->lineEditPassword->setText( "********" );
    }
    else {
        ui->lineEditPassword->setText( loginInfo->m_sPassword.c_str() );
        m_sOAuthKey = "";
    }

    if (bAccountSelect) {
        ui->lineEditAccount->setFocus();
        ui->lineEditAccount->selectAll();
    }

}

void EbDialogLogin::loadLoginData(void)
{
    ui->lineEditAccount->setFocus();
    char lpszBuffer[260];
    int nCookie = 0;
    theApp->m_sqliteEbc->select("SELECT user_id,account,account_r,password,safepwd,linestate,phone FROM user_login_record_t ORDER BY recordtime DESC", nCookie);
    cgcValueInfo::pointer pRecord = theApp->m_sqliteEbc->first(nCookie);
    bool bFindFirstData = false;
//    const QSize itemSize(ui->listWidgetLoginRecords->size().width()-5,const_listwidget_item_height);
    while (pRecord.get()!=NULL) {
        const mycp::bigint nUserId = pRecord->getVector()[0]->getBigIntValue();
        const mycp::tstring sAccount( pRecord->getVector()[1]->getStr() );
        const mycp::tstring sRealAccount( pRecord->getVector()[2]->getStr() );
        if (sAccount.empty() || sRealAccount.empty() || m_pLoginInfoList.exist(nUserId)) {
            continue;
        }
        const mycp::tstring sPassword( pRecord->getVector()[3]->getStr() );
        const bool bSafePwd = pRecord->getVector()[4]->getIntValue()==1?true:false;
        const EB_USER_LINE_STATE nLineState = (EB_USER_LINE_STATE)pRecord->getVector()[5]->getIntValue();
        CLoginInfo::pointer pLoginInfo = CLoginInfo::create(sAccount, sPassword, bSafePwd);
        pLoginInfo->m_sRealAccount = sRealAccount;
        pLoginInfo->m_nLineState = nLineState;
        pLoginInfo->m_nUserId = nUserId;
        pLoginInfo->m_nPhone = pRecord->getVector()[5]->getBigIntValue();
        m_pLoginInfoList.insert(pLoginInfo->m_nUserId,pLoginInfo,false);

        sprintf( lpszBuffer, "%s(%lld)", sAccount.c_str(),pLoginInfo->m_nUserId );
        QListWidgetItem * pItem = new QListWidgetItem(lpszBuffer, ui->listWidgetLoginRecords);
        pLoginInfo->m_item = pItem;
//        pItem->setSizeHint(itemSize);
        pItem->setData( Qt::UserRole, QVariant(pLoginInfo->m_nUserId) );
        ui->listWidgetLoginRecords->addItem( pItem );

        if (!bFindFirstData) {
            bFindFirstData = true;
            setLoginInfo( pLoginInfo,true );
        }

        pRecord = theApp->m_sqliteEbc->next(nCookie);
    }
    theApp->m_sqliteEbc->reset(nCookie);

}

void EbDialogLogin::createMenuData(void)
{
    if (m_menuSetting == NULL) {
        m_menuSetting = new QMenu(this);
        const QString selectText = theLocales.getLocalText("color-skin.select-color.text","选择色调");
        QAction * pSelectColorAction = m_menuSetting->addAction( QIcon(QStringLiteral(":/res/color_select.bmp")), selectText );
        pSelectColorAction->setCheckable(true);
        pSelectColorAction->setToolTip( theLocales.getLocalText("color-skin.select-color.tooltip","") );
        pSelectColorAction->setData( QVariant(0) );
        connect( pSelectColorAction, SIGNAL(triggered()), this, SLOT(onClickSelectColor()) );
        m_menuSetting->addSeparator();
        bool bFindMainColorChecked = false;
        const std::vector<EbColorInfo::pointer>& colors = theLocales.colors();
        for (size_t i=0; i<colors.size(); i++) {
            const EbColorInfo::pointer& colorInfo = colors[i];
            QPixmap pixmap(16,16);
            pixmap.fill( colorInfo->color() );
            QAction * pAction = m_menuSetting->addAction( QIcon(pixmap), colorInfo->name() );
            pAction->setCheckable(true);
            pAction->setData( QVariant((int)(i+1)) );
            connect( pAction, SIGNAL(triggered()), this, SLOT(onClickSelectColor()) );
            if (!bFindMainColorChecked && colorInfo->color()==theApp->getMainColor()) {
                bFindMainColorChecked = true;
                pAction->setChecked(true);
            }
        }
//        for (int i=0; i<theColorSkinSize; i++) {
//            const unsigned int nColor = theColorSkinsValue[i];
//            QPixmap pixmap(16,16);
//            pixmap.fill( QColor(GetRValue(nColor), GetGValue(nColor), GetBValue(nColor)) );
//            sprintf(lpszBuffer, "color-skin.color-%d.name", i);
//            const QString colorName = theLocales.getLocalText(lpszBuffer,"color");
//            QAction * pAction = m_menuSetting->addAction( QIcon(pixmap), colorName );
//            //            QAction * pAction = m_menuSetting->addAction( QIcon(pixmap), theColorSkinsString[i].c_str() );
//            pAction->setCheckable(true);
//            pAction->setData( QVariant(i+1) );
//            connect( pAction, SIGNAL(triggered()), this, SLOT(onClickSelectColor()) );
//            if (!bFindMainColorChecked) {
//                const int r = theApp->getMainColor().red();
//                const int g = theApp->getMainColor().green();
//                const int b = theApp->getMainColor().blue();
//                if (RGB(r,g,b)==nColor) {
//                    bFindMainColorChecked = true;
//                    pAction->setChecked(true);
//                }
//            }
//        }
        if (!bFindMainColorChecked) {
            pSelectColorAction->setChecked(true);
        }
    }
}

#ifdef USES_CORE_EVENT
bool EbDialogLogin::event(QEvent *e)
#else
void EbDialogLogin::customEvent(QEvent *e)
#endif
{
    const QEvent::Type eventType = e->type();
    switch ((EB_COMMAND_ID)eventType) {
//    case EB_COMMAND_UPDATE_PRODUCT_NAME:
//        onUpdateProductName(e);
//        break;
//    case EB_COMMAND_UPDATE_ENT_LOGO:
//        onUpdateEntLogo(e);
//        break;
    case EB_WM_APPID_SUCCESS:
        onAppIdSuccess(e);
#ifdef USES_CORE_EVENT
        return true;
#endif
        break;
    case EB_WM_APPID_ERROR:
        onAppIdError(e);
#ifdef USES_CORE_EVENT
        return true;
#endif
        break;
    case EB_WM_LOGON_SUCCESS:
        onLogonSuccess(e);
#ifdef USES_CORE_EVENT
        return true;
#endif
        break;
    case EB_WM_LOGON_TIMEOUT:
//        onLogonTimeout(e);
//        break;
    case EB_WM_LOGON_ERROR:
        onLogonError(e);
#ifdef USES_CORE_EVENT
        return true;
#endif
        break;
    case EB_WM_ONLINE_ANOTHER:
        onOnlineAnother(e);
#ifdef USES_CORE_EVENT
        return true;
#endif
        break;
    default:
        break;
    }
#ifdef USES_CORE_EVENT
    return EbDialogBase::event(e);
#endif
}

void EbDialogLogin::keyPressEvent(QKeyEvent * e)
{
    if (e->key()==Qt::Key_Escape) {
        if (ui->listWidgetLoginRecords->isVisible()) {
            onClickedLabelAccountIcon();
            return;
        }
    }
    EbDialogBase::keyPressEvent(e);
}

bool EbDialogLogin::eventFilter(QObject *obj, QEvent *e)
{
    if (obj==ui->listWidgetLoginRecords) {
//        if (e->type() == QEvent::FocusOut && !ui->pushButtonDeleteAccount->hasFocus()) {
        if (e->type() == QEvent::FocusOut && !ui->pushButtonDeleteAccount->hasFocus() && !ui->lineEditAccount->hasFocus()) {
            ui->listWidgetLoginRecords->setVisible(false);
            ui->pushButtonDeleteAccount->setVisible(false);
//            ui->pushButtonDeleteAccount->setProperty("delete-row",QVariant(-1));
        }
//        else if (e->type() == QEvent::KeyPress) {
//            const QKeyEvent * event = (QKeyEvent*)e;
//            switch (event->key()) {
//            case Qt::Key_Enter:
//            case Qt::Key_Return: {
//                break;
//            }
//            case Qt::Key_Up: {
//                // 实现鼠标向上移动，切换到 lineEditAccount
//                if ( ui->listWidgetLoginRecords->isVisible() && ui->listWidgetLoginRecords->hasFocus() ){
//                    if (ui->listWidgetLoginRecords->count()==0) {
//                        ui->lineEditAccount->setFocus();
//                    }
//                    else {
//                        QList<QListWidgetItem*> items = ui->listWidgetLoginRecords->selectedItems();
//                        if ( items.size()==1 && ui->listWidgetLoginRecords->row(items.at(0))==0 ) {
//                            ui->lineEditAccount->setFocus();
//                        }
//                    }
//                }
//                break;
//            }
//            default:
//                break;
//            }
//        }
    }
    else if (obj == ui->lineEditPassword) {
        if (e->type() == QEvent::KeyPress) {
            const QKeyEvent * event = (QKeyEvent*)e;
            if ( (event->key()>=Qt::Key_0 && event->key()<=Qt::Key_9) ||
                 (event->key()>=Qt::Key_A && event->key()<=Qt::Key_Z) ) {
                /// 手工输入密码，清空 m_sOAuthKey
                m_sOAuthKey.clear();
            }
        }
    }
    else if (obj == ui->lineEditAccount) {
        if (e->type() == QEvent::KeyPress) {
            const QKeyEvent * event = (QKeyEvent*)e;
            switch (event->key()) {
            case Qt::Key_Down: {
                /// 实现鼠标向下移动，切换到 listWidgetLoginRecords
                if (ui->listWidgetLoginRecords->isVisible() && !ui->listWidgetLoginRecords->hasFocus()) {
                    ui->listWidgetLoginRecords->setFocus();
                }
                break;
            }
            case Qt::Key_Tab: {
                /// 实现按TAB，自动隐藏 listWidgetLoginRecords
                if (ui->listWidgetLoginRecords->isVisible()) {
                    onClickedLabelAccountIcon();
                }
                break;
            }
            case Qt::Key_Backspace:
            case Qt::Key_Delete:
                m_searchFirst = false;
                break;
            default:
                m_searchFirst = true;
                break;
            }
        }
        else if (ui->listWidgetLoginRecords->isEnabled() && e->type() == QEvent::MouseButtonPress) {
            onClickedLabelAccountIcon();
            ui->lineEditAccount->setFocus();
            return true;
        }
        return false;
    }
    return EbDialogBase::eventFilter(obj, e);
}

//void EbDialogLogin::onUpdateProductName(QEvent* )
//{
//    updateProductName();
//}

//void EbDialogLogin::onUpdateEntLogo(QEvent* )
//{
//    if (theApp->isLicenseUser())
//        updateEntLogo(theApp->getAppImgPath() + "/entlogo");    // 企业定制LOGO，空或不存在使用系统默认
//    else
//        updateEntLogo("");
//}

void EbDialogLogin::onAppIdSuccess(QEvent *)
{
//    const EB_Event * pEvent = (EB_Event*)e;
    updateProductName();
    if (theApp->isLicenseUser())
        updateEntLogo(theApp->getAppImgPath() + "/entlogo");    // 企业定制LOGO，空或不存在使用系统默认
    else
        updateEntLogo("");
    ui->pushButtonLogon->setEnabled(true);
    ui->pushButtonVisitorLogon->setVisible(theApp->isOpenVisitor()?true:false);
    ui->pushButtonRegister->setVisible(theApp->openRegister()==0?false:true);
    ui->pushButtonForgetPwd->setVisible(theApp->forgetPwdUrl().isEmpty()?false:true);
    theApp->m_ebum.EB_SetMsgReceiver(this);
}
void EbDialogLogin::onAppIdError(QEvent * e)
{
    updateEntLogo("");
    const EB_Event * pEvent = (EB_Event*)e;
    const EB_STATE_CODE stateCode = (EB_STATE_CODE)pEvent->GetEventParameter();
    const QString sStateCode = QString::number( (int)stateCode );
    switch (stateCode) {
    case EB_STATE_NOT_SUPPORT_VERSION_ERROR:
        // 系统不支持当前版本，请更新客户端后重试！
        setErrorText( theLocales.getLocalText("on-appid-response.not-support-version.text","EB_STATE_NOT_SUPPORT_VERSION_ERROR"),true );
        break;
//    case EB_STATE_APPID_KEY_ERROR:
//        break;
    default:
        // 系统APPID验证失败，请退出程序后重新进入！<br>错误代码:[STATE_CODE]
        QString text = theLocales.getLocalText("on-appid-response.other-error.text","APPID Error");
        text.replace( "[STATE_CODE]", sStateCode );
        setErrorText( text,false );
        if (m_inMessageBox) {
            break;
        }
        const QString title = theLocales.getLocalText("on-appid-response.other-error.title","");
        m_inMessageBox = true;
        EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_WARNING,0,true );
        m_inMessageBox = false;
        break;
    }   // switch

}

void EbDialogLogin::onLogonSuccess(QEvent *e)
{
    const EB_AccountInfo * pAccountInfo = (EB_AccountInfo*)e;
    if (!is_visitor_uid(pAccountInfo->GetUserId())) {
        const EB_USER_LINE_STATE m_nOutLineState = EB_LINE_STATE_ONLINE_NEW;
        const std::string sAccount = ui->lineEditAccount->text().toStdString();
        char sSql[512];
        sprintf(sSql, "delete from user_login_record_t where account='%s' OR account_r='%s' OR user_id=%lld",
                pAccountInfo->GetAccount().c_str(), pAccountInfo->GetAccount().c_str(), pAccountInfo->GetUserId());
        int ret = (int)theApp->m_sqliteEbc->execute(sSql);
        if (ui->checkBoxSavePwd->isChecked()) {
            if (theApp->ebServerVersion()==0) {	// ** 兼容旧版本服务端
                const std::string sPassword = ui->lineEditPassword->text().toStdString();
                sprintf(sSql, "insert into user_login_record_t(account,account_r,password,safepwd,linestate,user_id,phone) VALUES('%s','%s','%s',1,%d,%lld,%lld)",
                    sAccount.c_str(),pAccountInfo->GetAccount().c_str(),sPassword.c_str(),(int)m_nOutLineState,pAccountInfo->GetUserId(),pAccountInfo->GetPhone());
            }
            else {
                mycp::tstring sLocalHostOAuthKey;
                entboost::GetLocalHostOAuthKey(sLocalHostOAuthKey);
                sprintf(sSql, "insert into user_login_record_t(account,account_r,password,safepwd,linestate,user_id,phone) VALUES('%s','%s','%s',1,%d,%lld,%lld)",
                        sAccount.c_str(),pAccountInfo->GetAccount().c_str(),sLocalHostOAuthKey.c_str(),m_nOutLineState,pAccountInfo->GetUserId(),pAccountInfo->GetPhone());
            }
        }
        else {
            sprintf(sSql, "insert into user_login_record_t(account,account_r,password,linestate,user_id,phone) VALUES('%s','%s','',%d,%lld,%lld)",
                    sAccount.c_str(),pAccountInfo->GetAccount().c_str(),(int)m_nOutLineState,pAccountInfo->GetUserId(),pAccountInfo->GetPhone());
        }
        ret = (int)theApp->m_sqliteEbc->execute(sSql);
    }
    if (!theApp->onLogonSuccess()) {
        setLogonCtrlEnabled(true);
        ui->lineEditAccount->setFocus();
        ui->lineEditAccount->selectAll();
        return;
    }
    this->accept();
}

//void EbDialogLogin::onLogonTimeout(QEvent *e)
//{
//    onLogonError(e);
//}

void EbDialogLogin::onLogonError(QEvent *e)
{
    const EB_AccountInfo * pAccountInfo = (EB_AccountInfo*)e;
    const EB_STATE_CODE stateCode = (EB_STATE_CODE)pAccountInfo->GetEventParameter();

    setLogonCtrlEnabled(true);
    ui->lineEditAccount->setFocus();
    ui->lineEditAccount->selectAll();

    if (stateCode == EB_STATE_APPID_KEY_ERROR) {
        QString title = theLocales.getLocalText("on-logon-response.appid-key-error.title","");
        if (title.isEmpty())
            title = theApp->productName();
        const QString text = theLocales.getLocalText("on-logon-response.appid-key-error.text","AppId Key Error");
        EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_WARNING,0,QMessageBox::Ok );
        theApp->exitApp(true);
        theApp->initApp();
        theApp->setDevAppId(this);
        //        m_bReload = true;
//        this->OnOK();
//        return 0;
        return;
    }

    QString sErrorText;
    switch (stateCode) {
    case EB_WM_LOGON_TIMEOUT:
        /// 登录超时，请重新登录！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.logon-timeout.text","Logon Timeout");
        break;
    case EB_STATE_UNAUTH_ERROR:
        /// 帐号未激活，请查收邮件，完成注册！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.unauth-error.text","Unauth Error");
        break;
    case EB_STATE_ACCOUNT_FREEZE:
        /// 帐号已经被临时冻结，请联系公司客服！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.account-freeze.text","Account Freeze");
        break;
    case EB_STATE_MAX_RETRY_ERROR:
        /// 错误次数太多，帐号被临时锁住，请稍候再试！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.max-retry-error.text","Max Retry Error");
        break;
    case EB_STATE_NOT_AUTH_ERROR:
        /// 没有权限错误！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.not-auth-error.text","Not Auth Error");
        break;
    case EB_STATE_ACCOUNT_NOT_EXIST:
        /// 帐号不存在，请重新输入！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.account-not-exist.text","Account Not Exist");
        break;
    case EB_STATE_ACC_PWD_ERROR:
        /// 帐号或密码错误，请重新输入！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.acc-pwd-error.text","Account Or Password Error");
        break;
    default:
        /// 登录失败，请重试！\r\n错误代码:%d
        sErrorText = theLocales.getLocalText("on-logon-response.other-error.text","Logon Error");
        break;
    }
    sErrorText.replace( "[STATE_CODE]", QString::number((int)stateCode) );
    setErrorText( sErrorText,true );
    /// 加了也是一样，需要等待错误提示窗口关闭后，才有焦点
//    ui->lineEditAccount->setFocus();
//    ui->lineEditAccount->selectAll();
}

void EbDialogLogin::onOnlineAnother(QEvent *e)
{

}

//#include "dialogframelist.h"
void EbDialogLogin::onClickPushButtonSetting(void)
{
    /// for test
//    DialogFrameList dlg;
//    dlg.exec();
//    return;

    createMenuData();
    // ** set menu checked and uncheck
    int nFindColorIndex = 0;
    const std::vector<EbColorInfo::pointer>& colors = theLocales.colors();
    for (size_t i=0; i<colors.size(); i++) {
        const EbColorInfo::pointer colorInfo = colors[i];
        if (colorInfo->color()==theApp->getMainColor()) {
            nFindColorIndex = (int)(i+1);
            break;
        }
    }
//    const int r = theApp->getMainColor().red();
//    const int g = theApp->getMainColor().green();
//    const int b = theApp->getMainColor().blue();
//    const unsigned int nMainColor = RGB(r,g,b);
//    int nFindColorIndex = 0;
//    for (int i=0; i<theColorSkinSize; i++) {
//        const unsigned int nColor = theColorSkinsValue[i];
//        if (nMainColor==nColor) {
//            nFindColorIndex = i+1;
//            break;
//        }
//    }
    bool bFindColoeChecked = false;
    const QList<QAction*> actionList = m_menuSetting->actions();
    for ( int i=0; i!=actionList.size(); ++i ) {
        QAction* action = actionList.at(i);
        bool bOk = false;
        if (!bFindColoeChecked && action->data().toInt(&bOk)==nFindColorIndex && bOk ) {
            action->setChecked(true);
            bFindColoeChecked = true;
        }
        else {
            action->setChecked(false);
        }
    }

    const QPoint pos(0,ui->pushButtonSetting->geometry().height());
    m_menuSetting->exec(ui->pushButtonSetting->mapToGlobal(pos));
}

void EbDialogLogin::onClickedEntLogo()
{
    if ( theApp->defaultUrl().isEmpty() )
        QDesktopServices::openUrl( QUrl("http://www.entboost.com") );
    else
        QDesktopServices::openUrl( QUrl(theApp->defaultUrl()) );
}

void EbDialogLogin::onClickSelectColor(void)
{
    QAction* pAction = dynamic_cast<QAction*>( sender() );
    pAction->setChecked(true);
    const int nColorIndex = pAction->data().toInt();
    const std::vector<EbColorInfo::pointer>& colors = theLocales.colors();
    if (nColorIndex>=1 && nColorIndex<=(int)colors.size()) {
        theApp->setMainColor( colors[nColorIndex-1]->color(), true );
//    if ( nColorIndex>=1 && nColorIndex<=theColorSkinSize ) {
//        const unsigned int nColor = theColorSkinsValue[nColorIndex-1];
//        theApp->setMainColor( GetRValue(nColor), GetGValue(nColor), GetBValue(nColor), true );
    }
    else {
        QColor c = QColorDialog::getColor( theApp->getMainColor() );
        if ( !c.isValid() ) {
            return;
        }
        theApp->setMainColor( c,true );
    }
//    refreshSkin();
}
void EbDialogLogin::setLogonCtrlEnabled(bool enable)
{
    ui->lineEditAccount->setEnabled(enable);
    m_labelAccountIcon->setEnabled(enable);
    ui->listWidgetLoginRecords->setEnabled(enable);
    if ( !enable ) {
        ui->listWidgetLoginRecords->setVisible(false);
    }
    ui->lineEditPassword->setEnabled(enable);
    ui->checkBoxSavePwd->setEnabled(enable);
    ui->pushButtonLogon->setEnabled(enable);
    ui->pushButtonVisitorLogon->setEnabled(enable);
}

void EbDialogLogin::onClickPushButtonLogon(void)
{
    const QString sAccount = ui->lineEditAccount->text();
    if (sAccount.isEmpty()) {
        ui->lineEditAccount->setFocus();
        /// 帐号不能为空：<br>请重新输入！
        setErrorText( theLocales.getLocalText( "message-show.account-empty-error","Account Empty" ),true );
        return;
    }
    const QString sPassword = ui->lineEditPassword->text();
    if (sPassword.isEmpty()) {
        ui->lineEditPassword->setFocus();
        /// 密码不能为空：<br>请输入密码！
        setErrorText( theLocales.getLocalText( "message-show.password-empty","Password Empty" ),true );
        return;
    }

    setErrorText( "",false );
    setLogonCtrlEnabled(false);
//    bool m_bAutoLogSuccess = false;
    const char * m_sReqCode = "";   // ??
    const EB_USER_LINE_STATE m_nOutLineState = EB_LINE_STATE_ONLINE_NEW;

    int ret = 0;
    if (theApp->ebServerVersion()==0 && sPassword != "********") {
        /// ** 兼容旧版本，("********"))是新版本自动登录
        ret = theApp->m_ebum.EB_LogonByAccount(sAccount.toStdString().c_str(),sPassword.toStdString().c_str(),
                                               m_sReqCode,"",m_nOutLineState);
    }
    else {
        mycp::tstring sLocalHostOAuthKey;
        if (ui->checkBoxSavePwd->isChecked())
            entboost::GetLocalHostOAuthKey(sLocalHostOAuthKey);
        if (!m_sOAuthKey.empty() && m_sOAuthKey==sLocalHostOAuthKey) {
            ret = theApp->m_ebum.EB_LogonByAccount(sAccount.toStdString().c_str(),"",
                                                   m_sReqCode,sLocalHostOAuthKey.c_str(),m_nOutLineState);
        }
        else {
            ret = theApp->m_ebum.EB_LogonByAccount(sAccount.toStdString().c_str(),sPassword.toStdString().c_str(),
                                                   m_sReqCode,sLocalHostOAuthKey.c_str(),m_nOutLineState);
        }
    }
    if (ret<0) {
        setLogonCtrlEnabled(true);
        ui->lineEditAccount->setFocus();
        ui->lineEditAccount->selectAll();
        /// 帐号格式错误，请重新输入！
        setErrorText( theLocales.getLocalText("message-show.account-format-error","Account Format Error"),true );
    }
}

void EbDialogLogin::onTextChangedEditAccount(const QString& sEditAccountText)
{
    if (!m_canSearch) return;
    m_canSearch = false;
    bool bFindAccount = false;
    if (!sEditAccountText.isEmpty()) {
        const std::string sAccount = sEditAccountText.toStdString();
        CLockMap<mycp::bigint, CLoginInfo::pointer>::iterator pIter = m_pLoginInfoList.begin();
        for (; pIter!=m_pLoginInfoList.end(); pIter++) {
            const CLoginInfo::pointer& pLoginInfo = pIter->second;
            if ( (m_searchFirst && pLoginInfo->m_sAccount.find(sAccount)==0) ||
                 (!m_searchFirst && pLoginInfo->m_sAccount==sAccount) ) {
                bFindAccount = true;
                this->setLoginInfo( pLoginInfo,false );
                const int nSelectionStart = (int)sAccount.size();
                const int nSelectionLen = pLoginInfo->m_sAccount.size();    // -nSelectionStart;
                ui->lineEditAccount->setSelection( nSelectionStart,nSelectionLen );
                ui->listWidgetLoginRecords->setCurrentItem(pLoginInfo->m_item);
//                if (m_treeUsers.GetSelectedItem()==pLoginInfo->m_hItem)
//                    SelectItem(pLoginInfo->m_hItem,false);
//                else
//                    m_treeUsers.Select(pLoginInfo->m_hItem,TVGN_CARET);
                break;
            }
        }
    }
    m_canSearch = true;

    if (!bFindAccount) {
        ui->lineEditPassword->setText("");
        ui->checkBoxSavePwd->setChecked(false);
    }

}

void EbDialogLogin::onClickedLabelAccountIcon(void)
{
    if ( ui->listWidgetLoginRecords->isVisible() ) {
        ui->listWidgetLoginRecords->setVisible(false);
        ui->pushButtonDeleteAccount->setVisible(false);
        ui->lineEditAccount->setFocus();
    }
    else {
        ui->listWidgetLoginRecords->setVisible(true);
        ui->listWidgetLoginRecords->setFocus();
        theApp->updateStyleSheet();
    }
}
void EbDialogLogin::onItemClickedLoginRecords(QListWidgetItem* item)
{
    setLoginInfo( item,true );
    ui->listWidgetLoginRecords->setVisible(false);
    ui->pushButtonDeleteAccount->setVisible(false);
}
void EbDialogLogin::onItemSelectionChangedLoginRecords(void)
{
    const QList<QListWidgetItem*> items = ui->listWidgetLoginRecords->selectedItems();
    if (items.count()==1) {
        setLoginInfo( items.at(0),false );
    }
}

void EbDialogLogin::onItemEnteredLoginRecords(QListWidgetItem* item)
{
    /// 滚动条能正常显示
    const QRect rectItem = ui->listWidgetLoginRecords->visualItemRect(item);
    const QPoint pointItem = ui->listWidgetLoginRecords->mapToParent(rectItem.topRight());
    const int y = pointItem.y()+1;  /// 1是 listWidgetLoginRecords 边框
    /// -1(配合下面的 buttonSize+1和y+1)实现删除按钮显示时，保留ITEM边框，
    const int buttonSize = rectItem.height()-2;
    ui->pushButtonDeleteAccount->setGeometry( pointItem.x()-buttonSize+2,y+1,buttonSize,buttonSize );
    ui->pushButtonDeleteAccount->setProperty( "track-row",QVariant(ui->listWidgetLoginRecords->row(item)) );
    ui->pushButtonDeleteAccount->setVisible(true);
}

//void EbDialogLogin::onCurrentItemChangedLoginRecords(QListWidgetItem *current, QListWidgetItem *previous)
//{
//    if (current==NULL) {
//        return;
//    }
//    const mycp::bigint userId = current->data(Qt::UserRole).toLongLong();
//    CLoginInfo::pointer loginInfo;
//    if (m_pLoginInfoList.find(userId, loginInfo)) {
//        const int rowIndex = loginInfo->m_rowIndex;
//        const QRect& rect = ui->listWidgetLoginRecords->geometry();
//        const int y = rect.top()+rowIndex*12;
//        ui->pushButtonDeleteAccount->move( rect.width()-16, y);
//    }
//}

//void EbDialogLogin::onCurrentRowChangedLoginRecords(int currentRow)
//{
//    const int rowIndex = currentRow;
//    const QRect& rect = ui->listWidgetLoginRecords->geometry();
//    const int y = rect.top()+rowIndex*12;
//    ui->pushButtonDeleteAccount->setVisible(true);
//    ui->pushButtonDeleteAccount->move( rect.width()-16, y);
//}

bool DeleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);
    if(!dir.exists())
        return true;

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList) {
        if (fi.isFile()) {
            if (!fi.dir().remove(fi.fileName())) return false;
        }
        else {
            if (!DeleteDirectory(fi.absoluteFilePath())) return false;
        }
    }
    return dir.rmdir(dir.absolutePath());
//    return dir.rmpath(dir.absolutePath());
}

void EbDialogLogin::onClickPushButtonDeleteAccount(void)
{
    const int rowIndex = ui->pushButtonDeleteAccount->property("track-row").toInt();
    QListWidgetItem* item = ui->listWidgetLoginRecords->item(rowIndex);
    if (item==NULL) {
        return;
    }
    const mycp::bigint userId = item->data(Qt::UserRole).toLongLong();
    CLoginInfo::pointer loginInfo;
    if (!m_pLoginInfoList.find(userId, loginInfo)) {
        return;
    }

    setErrorText( "",false );

    const mycp::tstring sRealUserAccount(loginInfo->m_sRealAccount);
    const QString sUserDirectory = theApp->getAppUsersPath() + "/" + QString::fromStdString(sRealUserAccount.string());
    if (QFile::exists(sUserDirectory)) {
        QString title = theLocales.getLocalText("message-box.delete-logon-account.title","删除登录信息");
        if (title.isEmpty())
            title = theApp->productName();
        /// 确定删除本地：<br>[USER_ACCOUNT] 帐号及所有聊天信息吗？
        QString text = theLocales.getLocalText("message-box.delete-logon-account.text","Confirm Delete Local <br>Account and Chat Messages?");
        text.replace( "[USER_ACCOUNT]", sRealUserAccount.string().c_str() );
        if (loginInfo->m_nUserId>0) {
            char lpszUserId[24];
            sprintf(lpszUserId,"%lld",loginInfo->m_nUserId);
            text.replace( "[USER_ID]", lpszUserId );
        }
        const int ret = EbMessageBox::doExec( 0,title, QChar::Null, text, EbMessageBox::IMAGE_QUESTION );
        if (ret!=QDialog::Accepted) {
            if (ui->listWidgetLoginRecords->isVisible()) {
                /// 设置 focus，实现点击 line edit account 能触发focus out 后自动隐藏
                ui->listWidgetLoginRecords->setFocus();
            }
            return;
        }
        if (!DeleteDirectory(sUserDirectory)) {
            /// 删除用户数据失败：<br>请重试！
            setErrorText( theLocales.getLocalText("message-show.delete-logon-account-error","删除用户数据失败：<br>请重试！"),true );
            return;
        }
    }
    if (loginInfo->m_nUserId>0) {
        /// ** 删除对应 chrome 浏览器缓存
        /// C:/Users/pc/AppData/Roaming/ebcd
        const QString sStringTemp = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        const QString sCefCachePath = QString("%1/cef_cache_temp/%2").arg(sStringTemp).arg(loginInfo->m_nUserId);
//        const QString sCefCachePath = QString("%1/entboost/cef_cache_temp/%2").arg(sStringTemp).arg(loginInfo->m_nUserId);
        DeleteDirectory(sCefCachePath);
    }
    if (!sRealUserAccount.empty()) {
        char sSql[260];
        if (loginInfo->m_nUserId>0) {
            sprintf(sSql,"delete from user_login_record_t where account='%s' OR account_r='%s' OR user_id=%lld",
                    loginInfo->m_sAccount.c_str(), sRealUserAccount.c_str(),loginInfo->m_nUserId);
        }
        else {
            sprintf(sSql,"delete from user_login_record_t where account='%s' OR account_r='%s'",
                    loginInfo->m_sAccount.c_str(), sRealUserAccount.c_str());
        }
        theApp->m_sqliteEbc->execute(sSql);
    }
    else if (loginInfo->m_nUserId>0) {
        char sSql[260];
        sprintf(sSql,"delete from user_login_record_t where user_id=%lld", loginInfo->m_nUserId);
        theApp->m_sqliteEbc->execute(sSql);
    }
     ui->pushButtonDeleteAccount->setProperty("track-row",QVariant(-1));
    ui->lineEditAccount->setText("");
    ui->lineEditAccount->setFocus();
    ui->lineEditPassword->setText("");
    ui->checkBoxSavePwd->setChecked(false);
    ui->listWidgetLoginRecords->setCurrentItem(NULL);
    ui->listWidgetLoginRecords->takeItem(rowIndex);
    delete item;
    m_pLoginInfoList.remove(loginInfo->m_nUserId);
    /// ** 优化实现，删除成功后，能正常显示或隐藏 QListWidget
    if (ui->listWidgetLoginRecords->isVisible()) {
        if(ui->listWidgetLoginRecords->count()>0) {
            ui->listWidgetLoginRecords->setFocus();
        }
        else {
            ui->listWidgetLoginRecords->setVisible(false);
            ui->pushButtonDeleteAccount->setVisible(false);
            ui->lineEditAccount->setFocus();
        }
    }
}

void EbDialogLogin::onClickPushButtonVisitor(void)
{
    if (!theApp->isOpenVisitor()) {
        const QString text = theLocales.getLocalText("message-box.not-support-visitor.text","Not Support Visitor");
        const QString title = theLocales.getLocalText("message-box.not-support-visitor.title","");
        EbMessageBox::doShow( NULL, title, QChar::Null, text, EbMessageBox::IMAGE_WARNING,default_warning_auto_close );
        return;
    }
    setLogonCtrlEnabled(false);
//    m_bAutoLogSuccess = false;
    const char * sRegCode = "";
    theApp->m_ebum.EB_LogonByVisitor(sRegCode);
}
void EbDialogLogin::onClickPushButtonRegister(void)
{
    // for test
//    EbMessageBox::doExec( NULL, "", QChar::Null, "测试第一行<br>系统APPID验证失败，请退出程序后重新进入！", EbMessageBox::IMAGE_WARNING,5 );
//    EbMessageBox::doShow( NULL, "", QChar::Null, "测试第一行<br>系统APPID验证失败，请退出程序后重新进入！", EbMessageBox::IMAGE_WARNING,5 );
////    QMessageBox::warning(this, tr("事件类型"), QString::number((int)12), QMessageBox::Yes | QMessageBox::No);
//    return;
    if (!theApp->isAppIdResponseOk()) {
        QString text = theLocales.getLocalText("on-appid-response.other-error.text","APPID Error");
        text.replace( "[STATE_CODE]", "1" );
        const QString title = theLocales.getLocalText("on-appid-response.other-error.title","");
        EbMessageBox::doShow( NULL, title, QChar::Null, text, EbMessageBox::IMAGE_WARNING,default_warning_auto_close );
        return;
    }
    EbDialogRegister pDialogRegister;
    if (pDialogRegister.exec()==QDialog::Accepted && pDialogRegister.registerUserId()>0) {
        char lpszUserId[24];
        sprintf( lpszUserId, "%lld", pDialogRegister.registerUserId() );
        ui->lineEditAccount->setText(lpszUserId);
        ui->lineEditPassword->setFocus();
    }
}

void EbDialogLogin::onClickPushButtonForgetPwd(void)
{
    const QString& sForgetPwdUrl = theApp->forgetPwdUrl();
    if ( !sForgetPwdUrl.isEmpty() ) {
        QDesktopServices::openUrl( QUrl(sForgetPwdUrl) );
    }
}

//#include "dialogmessagetip.h"
//#include "dialogframelist.h"
//#include "dialogmemberinfo.h"
//#include "dialogchangehead.h"
//#include "dialogemotionselect.h"
//#include "dialogmycenter.h"
//#include "dialoggroupinfo.h"  /// 编译有问题

void EbDialogLogin::onClickPushButtonConnectSetting(void)
{
    /// for test
//    DialogGroupInfo dlg;
//    DialogMyCenter dlg;
//    DialogEmotionSelect dlg;
//    DialogChangeHead dlg;
//    DialogMemberInfo dlg;
//    DialogMessageTip dlg;
//    DialogFrameList dlg;
//    dlg.exec();
//    return;

    EbDialogConnectSetting pDialogConnectSetting;
    const int ret = pDialogConnectSetting.exec();
    if ( ret==QDialog::Accepted && pDialogConnectSetting.isServerModified() ) {
        const QString title = theLocales.getLocalText("message-box.change-server.title","修改服务器地址");
        const QString text = theLocales.getLocalText("message-box.change-server.text","需要重新加载验证流程才能生效：<br>确定立即加载吗？");
        const int ret = EbMessageBox::doExec( 0,title, QChar(0xf0ec), text, EbMessageBox::IMAGE_QUESTION );
        if (ret==QDialog::Accepted) {
            theApp->exitApp(true);
            theApp->initApp();
            theApp->setDevAppId(this);
        }
    }

}

