#ifndef EBDIALOGFILEMANAGER_H
#define EBDIALOGFILEMANAGER_H

#include <ebclientapp.h>
#include <EbDialogBase.h>
#include <ebwidgetfiletranlist.h>
#include <ebwidgetiteminfo.h>

namespace Ui {
class EbDialogFileManager;
}

class EbDialogFileManager : public EbDialogBase
{
    Q_OBJECT

public:
    explicit EbDialogFileManager(QWidget *parent = 0);
    ~EbDialogFileManager();

    void updateLocaleInfo(void);
    void timerCheckState(void);
    void onSendingFile(const CCrFileInfo * fileInfo);
    void onReceivingFile(const CCrFileInfo * fileInfo);
    void onReceivedFile(const CCrFileInfo * fileInfo);
    void onFilePercent(const CChatRoomFilePercent * filePercent);
    void deleteTranFile(eb::bigint msgId);
    bool isEmpty(void) const;

public slots:
    void updateWidgetInfo(bool traningFile);
    void onClickedButtonTraningFile(void);
    void onClickedButtonTranedFile(void);
    void onClickedButtonRefresh(void);
    void onRefreshTranedFile(void);
    void onTextChangedSearch(const QString &);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemEntered(QListWidgetItem *item);

protected:
    virtual void resizeEvent(QResizeEvent *);

private:
    Ui::EbDialogFileManager *ui;
    EbWidgetFileTranList * m_tranFiles;
    CLockMap<eb::bigint,EbWidgetItemInfo::pointer> m_pItemItemInfo;	/// msgid->

};

#endif // EBDIALOGFILEMANAGER_H
