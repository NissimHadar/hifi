//
//  DownloadInstaller.cpp
//
//  Created by Nissim Hadar on 11 Apr 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "DownloadInstaller.h"
#include "PathUtils.h"

#include <QFile>

DownloadInstaller::DownloadInstaller(QLabel* workingFolderLabel, QComboBox* platformCombo) {
    _workingFolderLabel = workingFolderLabel;
    _platformCombo = platformCombo;

    _downloader = new Downloader();
}

void DownloadInstaller::setWorkingFolder() {
    PathUtils::setWorkingFolder(_workingFolderLabel, _workingFolder);
}

void DownloadInstaller::loadReleases() {
    downloadBuildXml();
    _buildInformation = _buildXMLParser.getBuilds("windows", _workingFolder + "/" + BUILD_XML_FILENAME);
}
 
void DownloadInstaller::loadBuilds() {
    downloadDevBuildXml();
    _buildInformation = _buildXMLParser.getBuilds("windows", _workingFolder + "/" + DEV_BUILD_XML_FILENAME);
}

void DownloadInstaller::loadPRs() {
}

void DownloadInstaller::downloadBuildXml() {
    QStringList urls;
    QStringList filenames;

    urls << BUILD_XML_URL;
    filenames << BUILD_XML_FILENAME;

    // Delete any existing file
    QFile file(_workingFolder + "/" + BUILD_XML_FILENAME);
    if (file.exists()) {
        file.remove();
    }

    _downloader->downloadFiles(urls, _workingFolder, filenames);
}

void DownloadInstaller::downloadDevBuildXml() {
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
