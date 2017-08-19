import QtQuick 2.6
import QtQuick.Window 2.2

import org.qter.MyOstuing 1.0

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

        MyOstu {
            id: id_MyOstu
        }
        MouseArea {
            anchors.fill: id_MyRec
            onClicked: id_MyOstu.on_threshold_clicked()
        }
    }
}
