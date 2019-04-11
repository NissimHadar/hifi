//
//  DownloadInstaller.cpp
//
//  Created by Nissim Hadar on 1 Sept 2018.
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
}

void DownloadInstaller::setWorkingFolderAndEnableControls() {
    PathUtils::setWorkingFolder(_workingFolderLabel, _workingFolder);
}
