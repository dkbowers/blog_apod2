#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class DownloadFile : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFile(QObject *parent = 0);

    void setUrl(QString sUrl) { urlString = sUrl; }

    void doDownload();

    QByteArray& getReplyData() { return replyData; }

signals:
    void fileDownloadCompleted();
    void fileDownloadError();

public slots:
    void replyFinished (QNetworkReply *reply);

private:
   QNetworkAccessManager *manager;
   QString urlString;
   QByteArray replyData;

};

#endif // DOWNLOADFILE_H
