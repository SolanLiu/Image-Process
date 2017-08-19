import QtQuick 2.7
import QtQuick.Window 2.2

import org.qter.MyWatershedsing 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        id: id_MyRec

        width: 360
        height: 360
        color: "gray"
        anchors.centerIn: parent

        MyWatersheds {
            id: id_MyWatersheds
        }
        MouseArea {
            anchors.fill: id_MyRec
            onClicked: id_MyWatersheds.on_segmentationW_clicked()
        }
    }
}
