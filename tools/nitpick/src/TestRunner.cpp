//
//  TestRunner.cpp
//
//  Created by Nissim Hadar on 23 Jan 2019.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#include "TestRunner.h"

#include <QFileDialog>

#include "Nitpick.h"
extern Nitpick* nitpick;

TestRunner::TestRunner(
    QLabel* workingFolderLabel,
    QLabel* statusLabel,
    QCheckBox* usePreviousInstallationCheckBox,
    QCheckBox* runLatest,
    QLineEdit* url,
    QCheckBox* runFullSuite,
    QLineEdit* scriptURL
) {
    _workingFolderLabel = workingFolderLabel;
    _statusLabel = statusLabel;
    _usePreviousInstallationCheckBox = usePreviousInstallationCheckBox;
    _runLatest = runLatest;
    _url = url;
    _runFullSuite = runFullSuite;
    _scriptURL = scriptURL;

    _downloader = new Downloader();
}

void TestRunner::downloadBuildXml() {
    // Download the latest High Fidelity build XML.
    //      Note that this is not needed for PR builds (or whenever `Run Latest` is unchecked)
    //      It is still downloaded, to simplify the flow
    buildXMLDownloaded = false;

    QStringList urls;
    QStringList filenames;

    urls << DEV_BUILD_XML_URL;
    filenames << DEV_BUILD_XML_FILENAME;

    // Delete any existing file
    QFile file(_workingFolder + "/" + DEV_BUILD_XML_FILENAME);
    if (file.exists()) {
        file.remove();
    }
    
    _downloader->downloadFiles(urls, _workingFolder, filenames);
}

QString TestRunner::getInstallerNameFromURL(const QString& url) {
    // An example URL: https://deployment.highfidelity.com/jobs/pr-build/label%3Dwindows/13023/HighFidelity-Beta-Interface-PR14006-be76c43.exe
    // On Mac, replace `exe` with `dmg`
    try {
        QStringList urlParts = url.split("/");
        return urlParts[urlParts.size() - 1];
    }
    catch (QString errorMessage) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), errorMessage);
        exit(-1);
    }
    catch (...) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), "unknown error");
        exit(-1);
    }
}

void TestRunner::appendLog(const QString& message) {
    if (!_logFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__),
            "Could not open the log file");
        exit(-1);
    }

    _logFile.write(message.toStdString().c_str());
    _logFile.write("\n");
    _logFile.close();

    nitpick->appendLogWindow(message);
}

void Worker::setCommandLine(const QString& commandLine) {
    _commandLine = commandLine;
}

int Worker::runCommand() {
    int result = system(_commandLine.toStdString().c_str());
    emit commandComplete();
    return result;
}
