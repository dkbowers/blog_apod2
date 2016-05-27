#ifndef APODDOWNLOADER_H
#define APODDOWNLOADER_H

#include <QObject>
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDate>
#include "downloadfile.h"

class APODDownloader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString copyright READ copyright WRITE setCopyright NOTIFY copyrightChanged)
    Q_PROPERTY(QString picturedate READ picturedate WRITE setPicturedate NOTIFY picturedateChanged)
    Q_PROPERTY(QString explanation READ explanation WRITE setExplanation NOTIFY explanationChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString serviceversion READ serviceversion WRITE setServiceversion NOTIFY serviceversionChanged)
    Q_PROPERTY(QString mediatype READ mediatype WRITE setMediatype NOTIFY mediatypeChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString hdurl READ hdurl WRITE setHdurl NOTIFY hdurlChanged)
    Q_PROPERTY(bool error READ error WRITE setError NOTIFY errorChanged)

public:
    APODDownloader();
    ~APODDownloader();

    void startRequest(QUrl url);

    QString copyright();
    void setCopyright(const QString &c);

    QString picturedate();
    void setPicturedate(const QString &p);

    QString explanation();
    void setExplanation(const QString &e);

    QString title();
    void setTitle(const QString &t);

    QString serviceversion();
    void setServiceversion(const QString &s);

    QString mediatype();
    void setMediatype(const QString &m);

    QString url();
    void setUrl(const QString &u);

    QString hdurl();
    void setHdurl(const QString &h);

    bool error();
    void setError(const bool b);

    Q_INVOKABLE void downloadPicture(QString theDate = "");
    Q_INVOKABLE void downloadPrevious();
    Q_INVOKABLE void downloadNext();
    Q_INVOKABLE void downloadToday();

private:
    void loadTextAndImage();
    void loadTextFields(const QJsonObject& obj);
    void changeDate(QString &newDate, int daysToAdd);

public slots:

private slots:
    void onTextDownloadComplete();
    void onTextDownloadError();

signals:
    void copyrightChanged();
    void picturedateChanged();
    void explanationChanged();
    void titleChanged();
    void serviceversionChanged();
    void mediatypeChanged();
    void urlChanged();
    void hdurlChanged();
    void errorChanged();
    void pictureDownloaded(bool success);

private:
    QString _copyright;
    QString _picturedate;
    QString _explanation;
    QString _title;
    QString _serviceversion;
    QString _mediatype;
    QString _url;
    QString _hdurl;
    bool _error;

    QString downloadDate;
    QString textUrl;
    QString imageUrl;
    DownloadFile textDownloader;
};

#endif // APODDOWNLOADER_H
