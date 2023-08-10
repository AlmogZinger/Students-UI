import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    property var students: query.data.students

    height: 700
    title: "Qt Example"
    visible: true
    width: 500

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: 10
        clip: true
        model: root.students

        delegate: Rectangle {
            id: currentStudent

            required property var model
            property var student: currentStudent.model.data

            color: "red"
            height: 200
            width: ListView.view.width

            RowLayout {
                anchors.fill: parent
                spacing: 15

                Rectangle {
                    color: "grey"
                    implicitHeight: 100
                    implicitWidth: 100

                    Text {
                        text: ` ${student.name}`
                    }
                }
                ListView {
                    id: innerList

                    implicitHeight: 100
                    implicitWidth: 100
                    model: currentStudent.student.test

                    delegate: Item {
                        id: insideDelegate

                        required property var model
                        property var test: model.data

                        height: 50
                        width: 100

                        Text {
                            anchors.centerIn: parent
                            text: `${test.subject} ${test.grade}`
                            width: parent.width * 0.4
                        }
                    }
                }
            }
        }
    }
}

// RowLayout {
//      height: 700
//      width: 500
//      RowLayout {
//          Button {
//              text: "Append"
//              onClicked: listView.model.append(appendBtn.text)
//          }
//          Button {
//              text: "Remove last"
//              onClicked: listView.model.removeLast()
//          }
//          Button {
//              text: "Clear"
//              onClicked: listView.model.clear()
//          }
//      }
//  }
