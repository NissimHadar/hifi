//
//  BuildXMLParser.h
//
//  Created by Nissim Hadar on 12 Apr 2019.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_BuildXMLParser_h
#define hifi_BuildXMLParser_h

#include <vector>

#include <QString>

class BuildInformation {
public:
    QString version;
    QString stable_version;
    QString url;
    QString filename;
};

class BuildXMLParser {
public:
    BuildInformation getLatestBuild(QString platformOfInterest, QString filename);
    std::vector<BuildInformation> getBuilds(QString platformOfInterest, QString filename);
    QString convertURLToFilename(const QString& url);
};

#endif
