import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

GridLayout {
    id: root
    columns: 2
    property date birthDay: new Date()

    DayOfWeekRow {
        locale: grid.locale

        Layout.column: 1
        Layout.fillWidth: true
    }

    WeekNumberColumn {
        month: grid.month
        year: grid.year
        locale: grid.locale

        Layout.fillHeight: true
    }

    MonthGrid {
        id: grid
        month: Calendar.December
        year: 2015
        locale: Qt.locale("en_US")
        delegate: Button {
            text: model.day
            onClicked: {
                root.birthDay = model.date;
            }
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
