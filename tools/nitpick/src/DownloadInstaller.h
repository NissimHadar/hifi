//
//  DownloadInstaller.h
//
//  Created by Nissim Hadar on 11 Apr 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_downloadInstaller_h
#define hifi_downloadInstaller_h

#include "BuildXMLParser.h"
#include "Downloader.h"

#include <QComboBox>
#include <QLabel>
#include <QObject>

class DownloadInstaller : public QObject {
    Q_OBJECT
public:
    DownloadInstaller(
        QLabel* workingFolderLabel, 
        QComboBox* platformComboBox,
        QComboBox* stableComboBox, 
        QComboBox* developmentComboBox,
        QComboBox* prComboBox
    );

    void setWorkingFolder();
    
    void loadStableBuilds();
    void downloadStableBuild();

    void loadDevelopmentBuilds();
    void downloadDevelopmentBuild();

    void loadPRBuilds();
    void downloadPRBuild();
    
    void downloadBuildXml();
    void downloadDevBuildXml();

private:
    QLabel* _workingFolderLabel;
    QComboBox* _platformComboBox;
    QComboBox* _stableComboBox;
    QComboBox* _developmentComboBox;
    QComboBox* _prComboBox;

    QString _workingFolder;

    Downloader* _downloader;
    BuildXMLParser _buildXMLParser;

    std::vector<BuildInformation> _stableBuildInformation;
    std::vector<BuildInformation> _developmentBuildInformation;
    std::vector<BuildInformation> _prBuildInformation;
};

#endif