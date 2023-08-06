import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import App

ApplicationWindow {
    id: root

    property StudentModel studentModel: StudentModel {
    }

    height: 700
    title: "Qt Example"
    visible: true
    width: 500

    footer: RowLayout {
        TextField {
            id: appendBtn

            text: "enter a garde"
        }
        Button {
            text: "Append"

            onClicked: listView.model.append(appendBtn.text)
        }
        Button {
            text: "Remove last"

            onClicked: listView.model.removeLast()
        }
        Button {
            text: "Clear"

            onClicked: listView.model.clear()
        }
    }

    Loader {
        anchors.fill: parent
        sourceComponent: timer.running ? undefined : students_list

        Timer {
            id: timer

            interval: 1000
            running: true
        }
    }
    Component {
        id: students_list

        ListView {
            id: listView

            anchors.fill: parent
            anchors.margins: 10
            clip: true
            model: root.studentModel

            delegate: Rectangle {
                id: currentStudent

                required property var model

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
                            text: ` ${currentStudent.model.name}`
                        }
                    }
                    ListView {
                        id: innerList

                        implicitHeight: 100
                        implicitWidth: 100
                        model: currentStudent.model.tests

                        delegate: Item {
                            id: insideDelegate

                            required property var model

                            height: 50
                            width: 100

                            Text {
                                anchors.centerIn: parent
                                text: `${insideDelegate.model.subject} ${insideDelegate.model.grade}`
                                width: parent.width * 0.4
                            }
                        }
                    }
                }
            }
        }
    }
}