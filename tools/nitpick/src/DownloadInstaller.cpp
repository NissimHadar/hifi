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

DownloadInstaller::DownloadInstaller(
    QLabel* workingFolderLabel
) {
    _workingFolderLabel = workingFolderLabel;

    _downloader = new Downloader();
}

void DownloadInstaller::setWorkingFolder() {
    PathUtils::setWorkingFolder(_workingFolderLabel, _workingFolder);
}

void DownloadInstaller::loadReleases() {
    downloadBuildXml();
}
 
void DownloadInstaller::loadBuilds() {
    downloadDevBuildXml();
}

void DownloadInstaller::loadPRs() {
}

void DownloadInstaller::downloadBuildXml() {
    QStringList urls;
    QStringList filenames;

    urls << BUILD_XML_URL;
    filenames << BUILD_XML_FILENAME;

    _downloader->downloadFiles(urls, _workingFolder, filenames);
}

void DownloadInstaller::downloadDevBuildXml() {
    QStringList urls;
    QStringList filenames;

    urls << DEV_BUILD_XML_URL;
    filenames << DEV_BUILD_XML_FILENAME;

    _downloader->downloadFiles(urls, _workingFolder, filenames);
}
