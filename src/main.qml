import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root

    height: 700
    title: "Qt Example"
    visible: true
    width: 500

    ListView {
        id: listView

        anchors.margins: 10
        anchors.top: root.top
        clip: true
        height: 500
        model: ApplicationSingleton.studentsQuery.data?.students
        width: parent.width

        delegate: Rectangle {
            id: currentStudent

            required property var model
            property var student: model.data

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
                        text: ` ${currentStudent.student.name}`
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
                            text: `${insideDelegate.test.subject} ${insideDelegate.test.grade}`
                            width: parent.width * 0.4
                        }
                    }
                }
            }
        }
    }
    RowLayout {
        anchors.top: listView.bottom
        height: 50
        width: 500

        RowLayout {
            Button {
                text: "Append Student"

                onClicked: popup.open()
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
    }
    Popup {
        id: popup

        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        z: 123123
        focus: true
        height: 300
        modal: true
        width: 400
        anchors.centerIn: parent
        contentItem: ColumnLayout {
            TextField {
                id: nameText
                text: "enter the name of the student"
            }
            Calender {
                id: calendar
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
            Button {
                text: "Append!"
                onClicked: ApplicationSingleton.add_student(nameText.text, calendar.birthDay)
            }
            Text {
                property var add_mutation: ApplicationSingleton.addStudentMutation
                text: add_mutation.completed ? `${add_mutation.data.addStudent.name} is added to the system` : add_mutation.operationInFlight ? "Sending..." : ""
            }
        }
    }
}
