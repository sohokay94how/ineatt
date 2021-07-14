#ifndef EBWIDGETWORKVIEW_H
#define EBWIDGETWORKVIEW_H

#include "ebclientapp.h"
#include <QWidget>
#include <QLabel>
#include <QWebEngineView>
#include <QWebEngineHistory>
//#include <ebwebengineurlrequestinterceptor.h>
#include <boost/shared_ptr.hpp>

class EbWebEngineView;
class EbFrameFindText;

class EbWidgetWorkView : public QWidget
{
    Q_OBJECT
public:
    typedef boost::shared_ptr<EbWidgetWorkView> pointer;
    explicit EbWidgetWorkView(bool saveUrl,const QUrl& url, const QString &postData, QWidget *parent = 0);
    virtual ~EbWidgetWorkView(void);
    static EbWidgetWorkView::pointer create(bool saveUrl,const QUrl& url, const QString &postData, QWidget *parent = 0);

    enum LOAD_STATE {
        LOAD_UNKNOWN
        , LOAD_STARTED
        , LOAD_FINISHED
    };

    EB_SubscribeFuncInfo m_funcInfo;

    void load(const QUrl & url, const QString & postData);
    void back(void);
    void forward(void);
    bool canGoBack() const;
    bool canGoForward() const;
    void refreshOrStop(void);
    void saveUrlHistory(void);
    bool isLoading(void) const;
    bool isLoadFinished(void) const;

    void setFocusInput(void);
    void setSaveUrl(bool v);
    bool saveUrl(void) const {return m_saveUrl;}
signals:
    void titleChanged(const EbWidgetWorkView * view, const QString& title);
    void urlChanged(const EbWidgetWorkView * view, const QUrl&);
    void iconChanged(const EbWidgetWorkView * view, const QIcon&);
    void loadStateChange(const EbWidgetWorkView * view, bool loadFinished, bool canGoBack, bool canGoForward);
    void openLinkInNewTab(const EbWidgetWorkView * view, const QUrl &linkUrl);
    void windowCloseRequested(const EbWidgetWorkView * view);

public slots:
    void onFindAction(const QString &selectedText);
    void onLoadStarted();
//    void onLoadProgress(int progress);
    void onLoadFinished(bool);
    void onTitleChanged(const QString& title);
//    void onSelectionChanged();
    void onUrlChanged(const QUrl&);
//    void onIconUrlChanged(const QUrl&);
    void onIconChanged(const QIcon&);
    void onLinkHovered(const QString &url);
//    void onRenderProcessTerminated(QWebEnginePage::RenderProcessTerminationStatus terminationStatus,
//                             int exitCode);

    void onWindowCloseRequested(void);
    void onOpenLink(const EbWebEngineView * view, QWebEnginePage::WebWindowType type, const QUrl &linkUrl);
    /// find text
    void onFindText(bool back,const QString & text);
    void onExitFindText(void);

    /// 可以 callback
//    void handleFindTextResult(bool found);

protected:
    virtual bool eventFilter(QObject *obj, QEvent *ev);
    virtual void keyPressEvent(QKeyEvent * e);
    virtual void resizeEvent(QResizeEvent * event);
    virtual void timerEvent(QTimerEvent * e);
    void showZoomFactor(void);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *event);
#endif

private:
    bool m_saveUrl;
    bool m_savedUrl;
    QUrl m_url;
    QString m_postData;
    EbWebEngineView * m_webEngineView;
    qreal m_zoomFactor;
    int m_timerIdCheckZoom;
    LOAD_STATE m_loadState;
    QLabel * m_labelStatus;
    int m_timerIdHideStatus;
    EbFrameFindText * m_frameFindText;
//    EbWebEngineUrlRequestInterceptor * m_webEngineUrlRequestInterceptor;
};

#endif // EBWIDGETWORKVIEW_H
