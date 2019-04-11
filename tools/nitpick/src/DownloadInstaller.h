//
//  DownloadInstaller.h
//
//  Created by Nissim Hadar on 1 Sept 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_downloadInstaller_h
#define hifi_downloadInstaller_h

#include <QLabel>
#include <QObject>

class DownloadInstaller : public QObject {
    Q_OBJECT
public:
    DownloadInstaller(
        QLabel* workingFolderLabel
    );

    void DownloadInstaller::setWorkingFolderAndEnableControls();

private:
    QLabel* _workingFolderLabel;
};

#endif