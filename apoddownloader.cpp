#include "apoddownloader.h"
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDebug>

APODDownloader::APODDownloader()
{
    downloadDate = QDate::currentDate().toString(QString("yyyy-MM-dd"));

    connect(&textDownloader, SIGNAL (fileDownloadCompleted()),this, SLOT (onTextDownloadComplete()));
    connect(&textDownloader, SIGNAL (fileDownloadError()),this, SLOT (onTextDownloadError()));

    loadTextAndImage();
}

APODDownloader::~APODDownloader()
{

}

QString APODDownloader::copyright()
{
    return _copyright;
}

void APODDownloader::setCopyright(const QString &c)
{
    if (c != _copyright) {
        _copyright = c;
        emit copyrightChanged();
    }
}

QString APODDownloader::picturedate()
{
    return _picturedate;
}

void APODDownloader::setPicturedate(const QString &p)
{
    if (p != _picturedate) {
        _picturedate = p;
        emit picturedateChanged();
    }
}

QString APODDownloader::explanation()
{
    return _explanation;
}

void APODDownloader::setExplanation(const QString &e)
{
    if (e != _explanation) {
        _explanation = e;
        emit explanationChanged();
    }
}

QString APODDownloader::title()
{
    return _title;
}

void APODDownloader::setTitle(const QString &t)
{
    if (t != _title) {
        _title = t;
        emit titleChanged();
    }
}

QString APODDownloader::serviceversion()
{
    return _serviceversion;
}

void APODDownloader::setServiceversion(const QString &s)
{
    if (s != _serviceversion) {
        _serviceversion = s;
        emit serviceversionChanged();
    }
}

QString APODDownloader::mediatype()
{
    return _mediatype;
}

void APODDownloader::setMediatype(const QString &m)
{
    if (m != _mediatype) {
        _mediatype = m;
        emit mediatypeChanged();
    }
}

QString APODDownloader::url()
{
    return _url;
}

void APODDownloader::setUrl(const QString &u)
{
    if (u != _url) {
        _url = u;
        emit urlChanged();
    }
}

QString APODDownloader::hdurl()
{
    return _hdurl;
}

void APODDownloader::setHdurl(const QString &h)
{
    if (h != _hdurl) {
        _hdurl = h;
        emit hdurlChanged();
    }
}

bool APODDownloader::error()
{
    return _error;
}

void APODDownloader::setError(const bool b)
{
    if (b != _error) {
        _error = b;
        emit errorChanged();
    }
}

void APODDownloader::downloadPicture(QString theDate)
{
    if(theDate.length() > 0)
        downloadDate = theDate;

    loadTextAndImage();
}

void APODDownloader::downloadPrevious()
{
    QString newDate;
    changeDate(newDate, -1);

    if(newDate != downloadDate) {
        downloadDate = newDate;
        loadTextAndImage();
    }
}

void APODDownloader::downloadNext()
{
    QString newDate;
    changeDate(newDate, 1);

    if(newDate != downloadDate) {
        downloadDate = newDate;
        loadTextAndImage();
    }
}

void APODDownloader::downloadToday()
{
    QDate todaysDate(QDate::currentDate());

    if(todaysDate.toString(QString("yyyy-MM-dd")) != downloadDate) {
        downloadDate = todaysDate.toString(QString("yyyy-MM-dd"));
        loadTextAndImage();
    }
}

void APODDownloader::changeDate(QString &newDate, int daysToAdd)
{
    QDate firstDate(1995, 1, 1);

    QDate todaysDate(QDate::currentDate());

    QString sY = downloadDate.left(4);
    int year = sY.toInt();

    QString sM = downloadDate.mid(5, 2);
    int month = sM.toInt();

    QString sD = downloadDate.right(2);
    int day = sD.toInt();

    QDate prev(year, month, day);
    prev = prev.addDays(daysToAdd);

    if(prev < firstDate)
        newDate = firstDate.toString(QString("yyyy-MM-dd"));
    else if(prev > todaysDate)
        newDate = todaysDate.toString(QString("yyyy-MM-dd"));
    else
        newDate = prev.toString(QString("yyyy-MM-dd"));
}

void APODDownloader::loadTextAndImage()
{
    _error = false;
    textUrl = "https://api.nasa.gov/planetary/apod?api_key=0000000000000000000000000000000000000000&date=";
    textUrl += downloadDate;
    qDebug() << "Retrieving apod url: " << textUrl << "\n";
    textDownloader.setUrl(textUrl);
    textDownloader.doDownload();
}

void APODDownloader::onTextDownloadComplete()
{
    QJsonObject jsonObj;
    QByteArray ba = textDownloader.getReplyData();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(ba.data());
    jsonObj = jsonResponse.object();

    imageUrl = jsonObj["url"].toString();

    setCopyright(jsonObj["copyright"].toString());
    setPicturedate(jsonObj["date"].toString());
    setExplanation(jsonObj["explanation"].toString());
    setTitle(jsonObj["title"].toString());
    setServiceversion(jsonObj["service_version"].toString());
    setUrl(jsonObj["url"].toString());
    setHdurl(jsonObj["hdurl"].toString());

    QString mediaType = jsonObj["media_type"].toString();
    if(mediaType == QString("image")){
        setUrl(imageUrl);
    }
    else{
        setUrl(QString(":/youtube.png"));
    }
    setMediatype(mediaType);
}

void APODDownloader::onTextDownloadError()
{
    setError(true);
}
