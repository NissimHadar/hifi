//
//  WindowScriptingInterface.cpp
//  interface/src/scripting
//
//  Created by Ryan Huffman on 4/29/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_WindowScriptingInterface_h
#define hifi_WindowScriptingInterface_h

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtQuick/QQuickItem>

#ifndef HIFI_UWP
#include <QtScript/QScriptValue>
#endif

#include <QtWidgets/QMessageBox>

#include <DependencyManager.h>

class CustomPromptResult {
public:
    QVariant value;
};

#ifndef HIFI_UWP
Q_DECLARE_METATYPE(CustomPromptResult);

QScriptValue CustomPromptResultToScriptValue(QScriptEngine* engine, const CustomPromptResult& result);
void CustomPromptResultFromScriptValue(const QScriptValue& object, CustomPromptResult& result);
#endif

class WindowScriptingInterface : public QObject, public Dependency {
    Q_OBJECT
    Q_PROPERTY(int innerWidth READ getInnerWidth)
    Q_PROPERTY(int innerHeight READ getInnerHeight)
    Q_PROPERTY(int x READ getX)
    Q_PROPERTY(int y READ getY)
public:
    WindowScriptingInterface();
    ~WindowScriptingInterface();
    int getInnerWidth();
    int getInnerHeight();
    int getX();
    int getY();

public slots:
#ifndef HIFI_UWP
    QScriptValue hasFocus();
#endif

    void setFocus();
    void raiseMainWindow();
    void alert(const QString& message = "");

#ifndef HIFI_UWP
    QScriptValue confirm(const QString& message = "");
    QScriptValue prompt(const QString& message = "", const QString& defaultText = "");
#endif

    CustomPromptResult customPrompt(const QVariant& config);

#ifndef HIFI_UWP
    QScriptValue browseDir(const QString& title = "", const QString& directory = "");
    QScriptValue browse(const QString& title = "", const QString& directory = "",  const QString& nameFilter = "");
    QScriptValue save(const QString& title = "", const QString& directory = "",  const QString& nameFilter = "");
    QScriptValue browseAssets(const QString& title = "", const QString& directory = "", const QString& nameFilter = "");
#endif

    void showAssetServer(const QString& upload = "");
    QString checkVersion();
    void copyToClipboard(const QString& text);
    void takeSnapshot(bool notify = true, bool includeAnimated = false, float aspectRatio = 0.0f);
    void takeSecondaryCameraSnapshot();
    void makeConnection(bool success, const QString& userNameOrError);
    void displayAnnouncement(const QString& message);
    void shareSnapshot(const QString& path, const QUrl& href = QUrl(""));
    bool isPhysicsEnabled();
    bool setDisplayTexture(const QString& name);

    int openMessageBox(QString title, QString text, int buttons, int defaultButton);
    void updateMessageBox(int id, QString title, QString text, int buttons, int defaultButton);
    void closeMessageBox(int id);

private slots:
    void onMessageBoxSelected(int button);

signals:
    void domainChanged(const QString& domainHostname);
    void svoImportRequested(const QString& url);
    void domainConnectionRefused(const QString& reasonMessage, int reasonCode, const QString& extraInfo);
    void stillSnapshotTaken(const QString& pathStillSnapshot, bool notify);
    void snapshotShared(bool isError, const QString& reply);
    void processingGifStarted(const QString& pathStillSnapshot);
    void processingGifCompleted(const QString& pathAnimatedSnapshot);

    void connectionAdded(const QString& connectionName);
    void connectionError(const QString& errorString);
    void announcement(const QString& message);

    void messageBoxClosed(int id, int button);

    // triggered when window size or position changes
    void geometryChanged(QRect geometry);

private:
    QString getPreviousBrowseLocation() const;
    void setPreviousBrowseLocation(const QString& location);

    QString getPreviousBrowseAssetLocation() const;
    void setPreviousBrowseAssetLocation(const QString& location);

    void ensureReticleVisible() const;

    int createMessageBox(QString title, QString text, int buttons, int defaultButton);
    QHash<int, QQuickItem*> _messageBoxes;
    int _lastMessageBoxID{ -1 };
};

#endif // hifi_WindowScriptingInterface_h
