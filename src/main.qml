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

        anchors.margins: 10
        anchors.top: root.top
        clip: true
        height: 500
        model: root.students
        width: parent.width

        delegate: Rectangle {
            id: currentStudent

            required property var model
            property Student__students student: currentStudent.model.data

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
                        property Test__studentstest test: model.data

                        height: 50
                        width: 100

                        Text {
                            anchors.centerIn: parent
                            text: `${insideDelegate.test.grade} ${insideDelegate.test.grade}`
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
            Popup {
                id: popup

                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
                focus: true
                height: 100
                modal: true
                width: 300
                x: 0
                y: 30

                ColumnLayout {
                    TextField {
                        id: nameText
                        text: "enter the name of the student"
                        width: text.implicitWidth
                    }
                    TextField {
                        id: birthText

                        text: "enter the birthday of the student like \n 03-06-1998"
                    }
                    Button {
                        text: "Append!"
                        onClicked: mutation.AddingStudent(nameText.text, birthText.text)
                    }
                }
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
}
