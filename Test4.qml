import QtQuick 2.0

Rectangle {
    id: mainRect
    property var myJson: contextJson
    property var statusConnect: contextStatusText

    width: 250
    height: 500

    JSONListModel  {
        id: dataModel
        json: myJson
//        source: "text.json"

        // All books in the store object
        query: "$[*]"
    }

    Rectangle {
        id: statusIndicator
        width: parent.width
        height: 20
        color: "white"
        Text {
            id: statusIndicatorText
            anchors.centerIn: parent
            renderType: Text.NativeRendering
            text: statusConnect
        }
    }
    Rectangle {
        id: titleNameLat
        width: parent.width
        height: 20
        anchors.top: statusIndicator.bottom

        Rectangle {
            id: titleName
            width: 105
            height: parent.height
            Text {
                anchors.centerIn: parent
                text: "Name"
            }
        }
        Rectangle {
            id: titleLat
            width: 105
            height: parent.height
            anchors.left: titleName.right
            Text {
                anchors.centerIn: parent
                text: "Latitude"
            }
        }
    }

    Column {
        anchors.margins: 10
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: titleNameLat.bottom
        spacing: 0

        ListView {
            id: view

            width: parent.width
            height: parent.height - parent.spacing - statusIndicator.height
            spacing: 10
            model: dataModel.model
            clip: true

            delegate: Rectangle {
                width: view.width
                height: 100
//                anchors.margins: 20
                Rectangle {
                    id: leftRect
                    width: 100
                    height: 100
                    color: "#8fbc8f"
                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: model.name
                    }
                }
                Rectangle {
                    anchors.left: leftRect.right
                    id: midRect
                    width: 10
                    height: parent.height
                    color: "white"
                }
                Rectangle {
                    id: rightRect
                    anchors.left: midRect.right
                    width: 100
                    height: 100
                    color: "#8fbc8f"
                    radius: width*0.5
                    Text {
                        anchors.centerIn: parent
                        renderType: Text.NativeRendering
                        text: model.address.geo.lat
                    }
                    Component.onCompleted: {
                        if(model.address.geo.lat < 0){
                            leftRect.color =  "#ff6347"
                            rightRect.color = "#ff6347"
                        }
                    }
                }
                Component.onCompleted: {
//                    console.log(dataModel.count)
//                    console.log(mainRect.myJson)
                }
            }
        }
    }
}
