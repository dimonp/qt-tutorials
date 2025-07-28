import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    title: "Addressbook"
    visible: true

    width: 800
    height: 600
    x: (Screen.width - this.width) / 2
    y: (Screen.height - this.height) / 2

    SystemPalette { id: activePalette; colorGroup: SystemPalette.Active }

    Adddialog {
        id: addDialog
        modal: true

        x: (parent.width - this.width) / 2
        y: (parent.height - this.height) / 2

        onAccepted: {
            dataModel.append({ name: addDialog.name, email: addDialog.email })
        }

        onRejected: console.log("Cancel clicked")
    }

    ListModel {
        id: dataModel
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 9
        rowSpacing: 6
        columnSpacing: 6
        rows: 3
        columns: 2

        Rectangle {
            id: listViewContainer
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row: 0
            Layout.column: 0

            color: "transparent"
            border {
                color: "black"
                width: 1
            }

            ScrollView {
                anchors.fill: parent
                anchors.margins: 5

                ListView {
                    id: listView
                    clip: true
                    focus: true

                    model: dataModel

                    delegate: Text {
                        width: parent.width
                        text: name

                        color: ListView.isCurrentItem ? activePalette.highlightedText : activePalette.text // Text color based on highlight

                        MouseArea {
                            anchors.fill: parent
                            onClicked: listView.currentIndex = index
                        }
                    }

                    highlight: Rectangle {
                        color: activePalette.highlight
                    }

                    onCurrentItemChanged: {
                        console.log("index changed see this " + this.currentIndex)

                        console.log(this.currentIndex);
                        let selectedItem = model.get(this.currentIndex)
                        if (selectedItem) {
                            nameLabel.text = "Name: " + selectedItem.name
                            emailLabel.text = "Email: " + selectedItem.email
                            view.addressListCurrentItemChanged()
                        }
                    }

                    function deleteSelected() {
                        if (this.currentIndex >= 0)
                            model.remove(this.currentIndex)
                    }
                }
            }
        }

        Label {
            id: nameLabel
            text: qsTr("Name")
            Layout.row: 1
            Layout.column: 0
        }

        Label {
            id: emailLabel
            text: qsTr("Email")
            Layout.row: 2
            Layout.column: 0
        }

        Column {
            id: column
            spacing: 5
            Layout.alignment: Qt.AlignTop
            Layout.row: 0
            Layout.column: 1
            Layout.rowSpan: 3

            Button {
                id: addButton
                text: qsTr("Add")
                onClicked: {
                    view.addButtonClicked()
                    addDialog.open()
                }
            }

            Button {
                id: deleteButton
                text: qsTr("Delete")
                onClicked: {
                    view.deleteButtonClicked()
                    listView.deleteSelected()
                }
            }
        }
    }
}
