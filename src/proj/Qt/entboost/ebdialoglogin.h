#ifndef EBDIALOGLOGIN_H
#define EBDIALOGLOGIN_H

#include "ebclientapp.h"
#include <QMouseEvent>
#include <QMenu>
#include <ebdialogbase.h>
#include <QListWidgetItem>
#include <eblabel.h>

namespace Ui {
class EbDialogLogin;
}

class CLoginInfo
{
public:
    typedef boost::shared_ptr<CLoginInfo> pointer;
    CLoginInfo(void);
    CLoginInfo(const mycp::tstring &account, const mycp::tstring &password, bool bSafePwd);
    static CLoginInfo::pointer create(const mycp::tstring &account, const mycp::tstring &password, bool safePwd);

    mycp::tstring m_sAccount;
    mycp::tstring m_sRealAccount;
    mycp::tstring m_sPassword;
    bool m_bSafePwd;
    EB_USER_LINE_STATE m_nLineState;
    mycp::bigint m_nUserId;
    mycp::bigint m_nPhone;
//    HTREEITEM m_hItem;
    QListWidgetItem* m_item;
};

class EbDialogLogin : public EbDialogBase
{
    Q_OBJECT
public:
    explicit EbDialogLogin(QWidget *parent = 0);
    ~EbDialogLogin(void);

    void updateLocaleInfo(void);
//    void refreshSkin(void);
    void updateEntLogo(const QString &fileName);
    void updateProductName(void);
    void setErrorText(const QString &errorText, bool messageShowError);
    bool isDefaultEntLogo(void) const {return m_isDefaultEntLogo;}
public slots:
    void onClickedPushButtonSetting(void);
    void onClickedEntLogo(void);
    void setLogonCtrlEnabled(bool);
    void onClickPushButtonLogon(void);
#ifdef WIN32
    void onClickedCheckBoxAutoRun(void);
#endif

    void onClickSelectColor(void);

    void onTextChangedEditAccount(const QString &text);
    void onClickedLabelAccountIcon(void);
    void onItemClickedLoginRecords(QListWidgetItem *item);
    void onItemSelectionChangedLoginRecords(void);
    void onItemEnteredLoginRecords(QListWidgetItem *item);
//    void onCurrentItemChangedLoginRecords(QListWidgetItem *current, QListWidgetItem *previous);
//    void onCurrentRowChangedLoginRecords(int currentRow);

    void onClickPushButtonDeleteAccount(void);
    void onClickPushButtonVisitor(void);
    void onClickPushButtonRegister(void);
    void onClickPushButtonForgetPwd(void);
    void onClickPushButtonConnectSetting(void);

    void processDatas(void);
protected:
    void setLoginInfo(QListWidgetItem* item, bool bAccountSelect);
    void setLoginInfo(const CLoginInfo::pointer& pLoginInfo, bool bAccountSelect);
    void loadLoginData(void);
    void createMenuData(void);
//    void timerEvent( QTimerEvent *e);

#ifdef USES_CORE_EVENT
    virtual bool event(QEvent *e);
#else
    virtual void customEvent(QEvent *e);
#endif
    void keyPressEvent(QKeyEvent *);
    virtual bool eventFilter(QObject *obj, QEvent *e);
private:
//    void onUpdateProductName(QEvent* e);
//    void onUpdateEntLogo(QEvent* e);
    void onAppIdSuccess(QEvent *e); /// from ebclientapp
    void onAppIdError(QEvent *e);   /// from ebclientapp
    void onLogonSuccess(QEvent *e);
//    void onLogonTimeout(QEvent *e);
    void onLogonError(QEvent *e);
    void onOnlineAnother(QEvent *e);
private:
    Ui::EbDialogLogin *ui;
    QMenu* m_menuSetting;
    EbLabel * m_labelEntLogo;
    EbLabel * m_labelAccountIcon;
    bool m_isDefaultEntLogo;
    bool m_inMessageBox;
    bool m_canSearch;
    bool m_searchFirst; /// true=查找开头 false=完全匹配
    CLockMap<mycp::bigint, CLoginInfo::pointer> m_pLoginInfoList;
    mycp::tstring m_sOAuthKey;
};

#endif // EBDIALOGLOGIN_H
