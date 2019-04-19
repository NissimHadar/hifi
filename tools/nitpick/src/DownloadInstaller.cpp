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

DownloadInstaller::DownloadInstaller(
    QLabel* workingFolderLabel, 
    QComboBox* platformComboBox,
    QComboBox* stableComboBox,
    QComboBox* developmentComboBox,
    QComboBox* prComboBox
) {
    _workingFolderLabel = workingFolderLabel;

    _platformComboBox = platformComboBox;
    _stableComboBox = stableComboBox;
    _developmentComboBox = developmentComboBox;
    _prComboBox = prComboBox;

    _downloader = new Downloader();
}

void DownloadInstaller::setWorkingFolder() {
    PathUtils::setWorkingFolder(_workingFolderLabel, _workingFolder);
}

void DownloadInstaller::loadStableBuilds() {
    downloadBuildXml();
    _stableBuildInformation = _buildXMLParser.getBuilds("windows", _workingFolder + "/" + BUILD_XML_FILENAME);

    QStringList releases;
    for (int i = 0; i < _stableBuildInformation.size(); ++i) {
        releases << _stableBuildInformation[i].stable_version + " [" + _stableBuildInformation[i].version + "]";
    }

    _stableComboBox->clear();
    _stableComboBox->insertItems(0, releases);
    _stableComboBox->setEnabled(true);
}

void DownloadInstaller::downloadStableBuild() {
    QStringList urls;
    QStringList filenames;

    BuildInformation buildInformation = _stableBuildInformation[_stableComboBox->currentIndex()];
    urls << buildInformation.url;
    filenames << buildInformation.filename;

    // Delete any existing file
    QFile file(_workingFolder + "/" + buildInformation.filename);
    if (file.exists()) {
        file.remove();
    }

    _downloader->downloadFiles(urls, _workingFolder, filenames);
}

void DownloadInstaller::loadDevelopmentBuilds() {
    downloadDevBuildXml();
    _developmentBuildInformation = _buildXMLParser.getBuilds("windows", _workingFolder + "/" + DEV_BUILD_XML_FILENAME);

    QStringList builds;
    for (int i = 0; i < _developmentBuildInformation.size(); ++i) {
        builds << _developmentBuildInformation[i].version;
    }

    _developmentComboBox->clear();
    _developmentComboBox->insertItems(0, builds);
    _developmentComboBox->setEnabled(true);
}

void DownloadInstaller::downloadDevelopmentBuild() {
    QStringList urls;
    QStringList filenames;

    BuildInformation buildInformation = _developmentBuildInformation[_stableComboBox->currentIndex()];
    urls << buildInformation.url;
    filenames << buildInformation.filename;

    // Delete any existing file
    QFile file(_workingFolder + "/" + buildInformation.filename);
    if (file.exists()) {
        file.remove();
    }

    _downloader->downloadFiles(urls, _workingFolder, filenames);
}

void DownloadInstaller::loadPRBuilds() {
}

void DownloadInstaller::downloadPRBuild() {
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
