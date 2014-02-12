import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1


ApplicationWindow {
    id:    mainWindow
    title: "Linux Community Software Installer (LCSI)"
    visible: true
    width: 800
    height: 600

    menuBar: MenuBar {
        Menu {
            title: "&File"

            MenuItem {
                id: exitButton
                text: "E&xit"
                shortcut: "Alt+F4"
                onTriggered: { mainWindow.close(); }
            }
        }
    }

    GridLayout {
        id: myGridLayout
        anchors.rightMargin: 8
        anchors.bottomMargin: 8
        anchors.leftMargin: 8
        anchors.topMargin: 8
        anchors.fill: parent
        rows: 7
        columns: 7

        columnSpacing: 10
        rowSpacing: 10

        Label {
            Layout.row:         0
            Layout.column:      0
            Layout.rowSpan:     1
            Layout.columnSpan:  1
            text: "Categories"
            Layout.fillWidth: true
        }

        ComboBox {
            id: categories
            model: catModel
            Layout.row:         0
            Layout.column:      1
            Layout.rowSpan:     1
            Layout.columnSpan:  2
            Layout.fillWidth: true
        }

        Label {
            Layout.row:         0
            Layout.column:      4
            Layout.rowSpan:     1
            Layout.columnSpan:  1
            text: "Search"
            Layout.fillWidth: true
        }

        TextField {
            id: search
            Layout.row:         0
            Layout.column:      5
            Layout.rowSpan:     1
            Layout.columnSpan:  2
            Layout.fillWidth: true
        }

        TableView {
            id: projects
            Layout.row:         1
            Layout.column:      0
            Layout.rowSpan:     6
            Layout.columnSpan:  7
            Layout.fillHeight: true
            Layout.fillWidth: true

            TableViewColumn { role: "program"; title: "Program" }
            TableViewColumn { role: "category"; title: "Category" }
            TableViewColumn { role: "description"; title: "Description" }
            TableViewColumn { role: "developer"; title: "Developer" }
            TableViewColumn { role: "website"; title: "Website" }
            TableViewColumn { role: "email"; title: "E-Mail" }
            model: myModel

            Component.onCompleted: {
                console.log("TableView loaded.");
                console.log("# Projects: " + projects.rowCount);
            }
        }
    }
}
