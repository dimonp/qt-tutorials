import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Dialog {
    id: thisDialog
    title: qsTr("New user")
    width: 600
    height: 200

    property alias name: nameField.text
    property alias email: emailField.text

    onOpened: {
        nameField.text = ""
        emailField.text = ""
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 5
        columns: 2

        Label { text: qsTr("Name:") }
        TextField {
            id: nameField
            Layout.fillWidth: true
            placeholderText: "Enter username"

            validator: RegularExpressionValidator {
                regularExpression: /.+/ // Matches one or more characters
            }
        }

        Label { text: qsTr("Email:") }
        TextField {
            id: emailField
            Layout.fillWidth: true
        }

        Row {
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                text: qsTr("OK")
                onClicked: {
                    if (thisDialog.validateForm()) {
                        thisDialog.accept() // Closes the dialog and emits accepted()
                    } else {
                        nameField.forceActiveFocus()
                    }
                }
            }

            Button {
                text: qsTr("Cancel")
                onClicked: {
                    thisDialog.reject() // Closes the dialog and emits rejected()
                }
            }
        }
    }

    function validateForm() {
        return nameField.acceptableInput
    }
}
