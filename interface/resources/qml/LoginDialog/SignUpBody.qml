//
//  SignUpBody.qml
//
//  Created by Stephen Birarda on 7 Dec 2016
//  Copyright 2016 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

import Hifi 1.0
import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4 as OriginalStyles

import controlsUit 1.0 as HifiControlsUit
import stylesUit 1.0 as HifiStylesUit
import TabletScriptingInterface 1.0

Item {
    z: -2
    id: signUpBody
    clip: true
    height: root.height
    width: root.width
    property int textFieldHeight: 31
    property string fontFamily: "Raleway"
    property int fontSize: 15
    property int textFieldFontSize: 18
    property bool fontBold: true

    property bool keyboardEnabled: false
    property bool keyboardRaised: false
    property bool punctuationMode: false

    onKeyboardRaisedChanged: d.resize();

    property string errorString: errorString
    property bool linkSteam: linkSteam

    QtObject {
        id: d
        readonly property int minWidth: 480
        readonly property int minWidthButton: !root.isTablet ? 256 : 174
        property int maxWidth: root.isTablet ? 1280 : root.width
        readonly property int minHeight: 120
        readonly property int minHeightButton: 36
        property int maxHeight: root.isTablet ? 720 : root.height

        function resize() {
            maxWidth = root.isTablet ? 1280 : root.width;
            maxHeight = root.isTablet ? 720 : root.height;
            var targetWidth = Math.max(titleWidth, mainContainer.width);
            var targetHeight =  hifi.dimensions.contentSpacing.y + mainContainer.height +
                    4 * hifi.dimensions.contentSpacing.y;

            var newWidth = Math.max(d.minWidth, Math.min(d.maxWidth, targetWidth));
            if (!isNaN(newWidth)) {
                parent.width = root.width = newWidth;
            }

            parent.height = root.height = Math.max(d.minHeight, Math.min(d.maxHeight, targetHeight)) + hifi.dimensions.contentSpacing.y;
        }
    }

    function signup() {
        loginDialog.signup(emailField.text, usernameField.text, passwordField.text);
    }

    function init() {
        // going to/from sign in/up dialog.
        loginDialog.isLogIn = false;
        emailField.placeholderText = "Email";
        emailField.text = "";
        emailField.anchors.top = usernameField.bottom;
        emailField.anchors.topMargin = 1.5 * hifi.dimensions.contentSpacing.y;
        passwordField.text = "";
        usernameField.focus = true;
        loginContainer.visible = true;
    }

    Item {
        id: mainContainer
        width: root.width
        height: root.height
        onHeightChanged: d.resize(); onWidthChanged: d.resize();

        Item {
            id: loginContainer
            width: usernameField.width
            height: parent.height
            anchors {
                top: parent.top
                topMargin: root.bannerHeight + 0.25 * parent.height
                left: parent.left
                leftMargin: (parent.width - usernameField.width) / 2
            }
            visible: true

            Item {
                id: errorContainer
                width: parent.width
                height: loginErrorMessageTextMetrics.height
                anchors {
                    bottom: usernameField.top;
                    bottomMargin: hifi.dimensions.contentSpacing.y;
                    left: usernameField.left;
                }
                TextMetrics {
                    id: loginErrorMessageTextMetrics
                    font: loginErrorMessage.font
                    text: loginErrorMessage.text
                }
                Text {
                    id: loginErrorMessage;
                    width: root.bannerWidth
                    color: "red";
                    font.family: signUpBody.fontFamily
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: ""
                    visible: false
                }
            }

            HifiControlsUit.TextField {
                id: usernameField
                width: root.bannerWidth
                height: signUpBody.textFieldHeight
                placeholderText: "Username"
                font.pixelSize: signUpBody.textFieldFontSize
                styleRenderType: Text.QtRendering
                anchors {
                    top: parent.top
                    topMargin: loginErrorMessage.height
                }
                focus: true
                Keys.onPressed: {
                    if (!usernameField.visible) {
                        return;
                    }
                    switch (event.key) {
                        case Qt.Key_Tab:
                            event.accepted = true;
                            if (event.modifiers === Qt.ShiftModifier) {
                                passwordField.focus = true;
                            } else {
                                emailField.focus = true;
                            }
                            break;
                        case Qt.Key_Backtab:
                            event.accepted = true;
                            passwordField.focus = true;
                            break;
                        case Qt.Key_Enter:
                        case Qt.Key_Return:
                            event.accepted = true;
                            if (keepMeLoggedInCheckbox.checked) {
                                Settings.setValue("keepMeLoggedIn/savedUsername", usernameField.text);
                            }
                            signUpBody.signup();
                            break;
                    }
                }
                onFocusChanged: {
                    root.text = "";
                    if (focus) {
                        root.isPassword = false;
                    }
                }
            }

            HifiControlsUit.TextField {
                id: emailField
                width: root.bannerWidth
                height: signUpBody.textFieldHeight
                anchors {
                    top: parent.top
                }
                placeholderText: "Username or Email"
                font.pixelSize: signUpBody.textFieldFontSize
                styleRenderType: Text.QtRendering
                activeFocusOnPress: true
                Keys.onPressed: {
                    switch (event.key) {
                        case Qt.Key_Tab:
                            event.accepted = true;
                            if (event.modifiers === Qt.ShiftModifier) {
                                if (usernameField.visible) {
                                    usernameField.focus = true;
                                    break;
                                }
                            }
                            passwordField.focus = true;
                            break;
                        case Qt.Key_Backtab:
                            event.accepted = true;
                            usernameField.focus = true;
                            break;
                        case Qt.Key_Enter:
                        case Qt.Key_Return:
                            event.accepted = true;
                            if (keepMeLoggedInCheckbox.checked) {
                                Settings.setValue("keepMeLoggedIn/savedUsername", usernameField.text);
                            }
                            signUpBody.signup();
                            break;
                    }
                }
                onFocusChanged: {
                    root.text = "";
                    if (focus) {
                        root.isPassword = false;
                    }
                }
            }
            HifiControlsUit.TextField {
                id: passwordField
                width: root.bannerWidth
                height: signUpBody.textFieldHeight
                placeholderText: "Password"
                font.pixelSize: signUpBody.textFieldFontSize
                styleRenderType: Text.QtRendering
                activeFocusOnPress: true
                echoMode: passwordFieldMouseArea.showPassword ? TextInput.Normal : TextInput.Password
                anchors {
                    top: emailField.bottom
                    topMargin: 1.5 * hifi.dimensions.contentSpacing.y
                }

                onFocusChanged: {
                    root.text = "";
                    root.isPassword = focus;
                }

                Item {
                    id: showPasswordContainer
                    z: 10
                    // width + image's rightMargin
                    width: showPasswordImage.width + 8
                    height: parent.height
                    anchors {
                        right: parent.right
                    }

                    Image {
                        id: showPasswordImage
                        width: passwordField.height * 16 / 23
                        height: passwordField.height * 16 / 23
                        anchors {
                            right: parent.right
                            rightMargin: 8
                            top: parent.top
                            topMargin: passwordFieldMouseArea.showPassword ? 6 : 8
                            bottom: parent.bottom
                            bottomMargin: passwordFieldMouseArea.showPassword ? 5 : 8
                        }
                        source: passwordFieldMouseArea.showPassword ?  "../../images/eyeClosed.svg" : "../../images/eyeOpen.svg"
                        MouseArea {
                            id: passwordFieldMouseArea
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            property bool showPassword: false
                            onClicked: {
                                showPassword = !showPassword;
                            }
                        }
                    }
                }
                Keys.onPressed: {
                    switch (event.key) {
                        case Qt.Key_Tab:
                            event.accepted = true;
                            if (event.modifiers === Qt.ShiftModifier) {
                                emailField.focus = true;
                            } else if (usernameField.visible) {
                                usernameField.focus = true;
                            } else {
                                emailField.focus = true;
                            }
                            break;
                        case Qt.Key_Backtab:
                            event.accepted = true;
                            emailField.focus = true;
                            break;
                    case Qt.Key_Enter:
                    case Qt.Key_Return:
                        event.accepted = true;
                        if (keepMeLoggedInCheckbox.checked) {
                            Settings.setValue("keepMeLoggedIn/savedUsername", usernameField.text);
                        }
                        signUpBody.signup();
                        break;
                    }
                }
            }
            HifiControlsUit.CheckBox {
                id: keepMeLoggedInCheckbox
                checked: Settings.getValue("keepMeLoggedIn", false);
                text: qsTr("Keep Me Logged In");
                boxSize: 18;
                labelFontFamily: signUpBody.fontFamily
                labelFontSize: 18;
                color: hifi.colors.white;
                anchors {
                    top: passwordField.bottom;
                    topMargin: hifi.dimensions.contentSpacing.y;
                    left: passwordField.left;
                }
                onCheckedChanged: {
                    Settings.setValue("keepMeLoggedIn", checked);
                }
                Component.onDestruction: {
                    Settings.setValue("keepMeLoggedIn", checked);
                    if (checked) {
                        Settings.setValue("keepMeLoggedIn/savedUsername", emailField.text);
                    }
                }
            }

            TextMetrics {
                id: cancelButtonTextMetrics
                font: loginErrorMessage.font
                text: cancelButton.text
            }
            HifiControlsUit.Button {
                id: cancelButton
                width: (emailField.width - hifi.dimensions.contentSpacing.x) / 2
                height: d.minHeightButton
                anchors {
                    top: keepMeLoggedInCheckbox.bottom
                    topMargin: hifi.dimensions.contentSpacing.y
                    left: parent.left
                }
                color: hifi.buttons.noneBorderlessWhite
                text: qsTr("CANCEL")
                fontFamily: signUpBody.fontFamily
                fontSize: signUpBody.fontSize
                fontBold: signUpBody.fontBold
                onClicked: {
                    bodyLoader.setSource("LinkAccountBody.qml", { "loginDialog": loginDialog, "root": root, "bodyLoader": bodyLoader, "linkSteam": signUpBody.linkSteam });
                }
            }
            HifiControlsUit.Button {
                id: signUpButton
                width: (emailField.width - hifi.dimensions.contentSpacing.x) / 2
                height: d.minHeightButton
                color: hifi.buttons.blue
                text: qsTr("Sign Up")
                fontFamily: signUpBody.fontFamily
                fontSize: signUpBody.fontSize
                fontBold: signUpBody.fontBold
                anchors {
                    top: cancelButton.top
                    right: passwordField.right
                }

                onClicked: {
                    signUpBody.signup();
                }
            }
        }
    }

    MouseArea {
        z: -2
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onClicked: {
            if (!usernameField.focus && !emailField.focus && !passwordField.focus) {
                usernameField.focus = true;
            }
        }
    }

    Component.onCompleted: {
        //but rise Tablet's one instead for Tablet interface
        root.keyboardEnabled = HMD.active;
        root.keyboardRaised = Qt.binding( function() { return keyboardRaised; })
        root.text = "";
        d.resize();
        init();
    }

    Keys.onPressed: {
        if (!visible) {
            return;
        }

        switch (event.key) {
            case Qt.Key_Enter:
            case Qt.Key_Return:
                event.accepted = true;
                Settings.setValue("keepMeLoggedIn/savedUsername", usernameField.text);
                signUpBody.login();
                break;
        }
    }
    Connections {
        target: loginDialog
        onHandleSignupCompleted: {
            console.log("Sign Up Completed");

            loginDialog.login(usernameField.text, passwordField.text);
            bodyLoader.setSource("LoggingInBody.qml", { "loginDialog": loginDialog, "root": root, "bodyLoader": bodyLoader, "withSteam": false, "linkSteam": false });
        }
        onHandleSignupFailed: {
            console.log("Sign Up Failed")

            var errorStringEdited = errorString.replace(/[\n\r]+/g, ' ');
            loginErrorMessage.visible = (errorStringEdited !== "");
            if (errorStringEdited !== "") {
                loginErrorMessage.text = errorStringEdited;
                loginErrorMessageTextMetrics.text = errorStringEdited;
                if (loginErrorMessageTextMetrics.width > 350 && root.isTablet) {
                    loginErrorMessage.wrapMode = Text.WordWrap;
                    loginErrorMessage.verticalAlignment = Text.AlignLeft;
                    loginErrorMessage.horizontalAlignment = Text.AlignLeft;
                    errorContainer.height = 2 * loginErrorMessageTextMetrics.height;
                }
                errorContainer.anchors.bottom = usernameField.top;
                errorContainer.anchors.left = usernameField.left;
            }
        }
    }
}
