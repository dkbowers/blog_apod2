import QtQuick 2.6
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0
import com.davidkbowers.demo 1.0

ApplicationWindow {
    id: window
    width: 375
    height: 647
    visible: true
    title: "APOD Demo"

    APODDownloader {
        id: apod

        onUrlChanged: { myPicture.source = apod.url; }
        onPicturedateChanged: { mydate.text = apod.picturedate; }
        onExplanationChanged: { explanationText.text = apod.explanation; }
        onTitleChanged: { mytitle.text = apod.title; }
        onErrorChanged: {
            mytitle.text = "Uknown server error.";
            myPicture.source = "error.png"
        }
    }

    header: ToolBar {
        id: topnavbar
        RowLayout {
            anchors.fill: parent
            Label {
                id: labelAppTitle
                text: "Astronomy Picture Of The Day"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Control {
        id: contentcontrol
        anchors.fill: parent

        Text {
            id: mytitle
            x: titleArea.x
            y: titleArea.y
            width: titleArea.width
            height: titleArea.height
            text: "Saturn and Mars visit Milky Way Star Clouds"

        }

        Text {
            id: mydate
            x: dateArea.x
            y: dateArea.y
            width: dateArea.width
            height: dateArea.height
            text: "2016-05-11"

        }

        Image {
            id: myPicture
            x: pictureArea.x
            y: pictureArea.y
            width: pictureArea.width
            height: pictureArea.height
            fillMode: Image.PreserveAspectFit
            source: "http://apod.nasa.gov/apod/image/1605/OphiuchusPlanets_Fairbairn_960.jpg"
        }

        Flickable {
            id: flickArea
            x: explanationArea.x
            y: explanationArea.y
            width: explanationArea.width
            height: explanationArea.height
            contentWidth: explanationText.width; contentHeight: explanationText.height
            flickableDirection: Flickable.VerticalFlick
            clip: true

             TextEdit{
                  id: explanationText
                   wrapMode: TextEdit.Wrap
                   width:explanationArea.width
                   readOnly:true
                   text:  "Planets, stars, nebulas and a galaxy -- this impressive image has them all. Closest to home are the two planets Mars (right) and Saturn (center), visible as the two bright orange spots in the upper half of the featured image. On the central right are the colorful Rho Ophiuchus star clouds featuring the bright orange star Antares lined up below Mars.  These interstellar clouds contain both red emission nebulas and blue reflection nebulas.  At the top right of the image is the Blue Horsehead reflection nebula. On the lower left are many dark absorption nebulas that extend from the central band of our Milky Way Galaxy. The featured deep composite was composed of multiple deep exposures taken last month from Brazil.  Although you need a telescope to see the nebulosities, Saturn and Mars will remain visible to the unaided eye this month toward the east, just after sunset.    Follow APOD on: Facebook,  Google Plus,  Instagram, or Twitter"
            }
        }
    }

    Popup {
        id: dateDialog
        property string myDate: ""
        modal: true
        focus: true
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: dateColumn.height
        closePolicy: Popup.OnEscape | Popup.OnPressOutside

        Column {
            id: dateColumn
            spacing: 20

            Label {
                text: "Select A Date"
                font.bold: true
            }

            RowLayout {
                spacing: 10

                Tumbler {
                    id: tumblerMonth
                    model: ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]
                    visibleItemCount: 5
                }

                Tumbler {
                    id: tumblerDay
                    model: ["01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12","13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"]
                    visibleItemCount: 5
                }

                Tumbler {
                    id: tumblerYear
                    model: ["1995", "1996", "1997", "1998", "1999", "2000", "2001", "2002", "2003", "2004", "2005", "2006","2007", "2008", "2009", "2010", "2011", "2012", "2013", "2014", "2015", "2016"]
                    visibleItemCount: 5
                }
            }

            Button {
                id: doneButton
                text: "Done"
                onClicked: {
                    var sYear = tumblerYear.model[tumblerYear.currentIndex];

                    var sMonth = ""
                    if(tumblerMonth.currentIndex == 0)
                        sMonth = "01";
                    else if(tumblerMonth.currentIndex == 1)
                        sMonth = "02";
                    else if(tumblerMonth.currentIndex == 2)
                        sMonth = "03";
                    else if(tumblerMonth.currentIndex == 3)
                        sMonth = "04";
                    else if(tumblerMonth.currentIndex == 4)
                        sMonth = "05";
                    else if(tumblerMonth.currentIndex == 5)
                        sMonth = "06";
                    else if(tumblerMonth.currentIndex == 6)
                        sMonth = "07";
                    else if(tumblerMonth.currentIndex == 7)
                        sMonth = "08";
                    else if(tumblerMonth.currentIndex == 8)
                        sMonth = "09";
                    else if(tumblerMonth.currentIndex == 9)
                        sMonth = "10";
                    else if(tumblerMonth.currentIndex == 10)
                        sMonth = "11";
                    else if(tumblerMonth.currentIndex == 11)
                        sMonth = "12";

                    var sDay = tumblerDay.model[tumblerDay.currentIndex];

                    dateDialog.myDate = sYear + "-" + sMonth + "-" + sDay;
                    apod.downloadPicture(dateDialog.myDate)
                    dateDialog.myDate = ""
                    dateDialog.close()
                }
                Layout.preferredWidth: 0
                Layout.fillWidth: true
            }
        }
    }

    footer: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/tbcalendar.png"
                }
                onClicked: {
                    dateDialog.open()
                }
            }

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/tbtoday.png"
                }
                onClicked: { apod.downloadToday(); }
            }

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/tbleft.png"
                }
                onClicked: apod.downloadPrevious()
            }

            ToolButton {
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/tbright.png"
                }
                onClicked: apod.downloadNext()
            }

        }
    }


}
