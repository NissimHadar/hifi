//
//  BuildXMLParser.cpp
//
//  Created by Nissim Hadar on 12 Apr 2019.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#include "BuildXMLParser.h"

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>

BuildInformation BuildXMLParser::getLatestBuild(QString platformOfInterest, QString filename) {
    BuildInformation buildInformation;

    try {
        QDomDocument domDocument;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly) || !domDocument.setContent(&file)) {
            throw QString("Could not open " + filename);
        }

        QDomElement projectsElement = domDocument.documentElement();
        // Verify first element is "projects"
        if (projectsElement.tagName() != "projects") {
            throw("File seems to be in wrong format");
        }

        QDomElement projectElement = projectsElement.firstChildElement();
        if (projectElement.tagName() != "project") {
            throw("File seems to be in wrong format");
        }

        if (projectElement.attribute("name") != "interface") {
            throw("File is not from 'interface' build");
        }

        // Now loop over the platforms, looking for ours
        bool platformFound{ false };
        QDomElement platformElement = projectElement.firstChildElement();
        while (!platformElement.isNull()) {
            if (platformElement.attribute("name") == platformOfInterest) {
                platformFound = true;
                break;
            }
            platformElement = platformElement.nextSiblingElement();
        }

        if (!platformFound) {
            throw("File seems to be in wrong format - platform " + platformOfInterest + " not found");
        }

        QDomElement buildElement = platformElement.firstChildElement();
        if (buildElement.tagName() != "build") {
            throw("File seems to be in wrong format");
        }

        // First sibling should be version
        buildElement = buildElement.firstChildElement();
        if (buildElement.tagName() != "version") {
            throw("File seems to be in wrong format");
        }

        // Add the version number to the end of the filename
        buildInformation.version = buildElement.text();

        // First sibling should be stable_version
        buildElement = buildElement.nextSiblingElement();
        if (buildElement.tagName() != "stable_version") {
            throw("File seems to be in wrong format");
        }

        // Next sibling should be url
        buildElement = buildElement.nextSiblingElement();
        if (buildElement.tagName() != "url") {
            throw("File seems to be in wrong format");
        }
        buildInformation.url = buildElement.text();
    } catch (QString errorMessage) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), errorMessage);
        exit(-1);
    } catch (...) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), "unknown error");
        exit(-1);
    }

    return buildInformation;
}

std::vector<BuildInformation> BuildXMLParser::getBuilds(QString platformOfInterest, QString filename) {
    std::vector<BuildInformation> buildInformationVector;

    try {
        QDomDocument domDocument;
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly) || !domDocument.setContent(&file)) {
            throw QString("Could not open " + filename);
        }

        QDomElement projectsElement = domDocument.documentElement();
        // Verify first element is "projects"
        if (projectsElement.tagName() != "projects") {
            throw("File seems to be in wrong format");
        }

        QDomElement projectElement = projectsElement.firstChildElement();
        if (projectElement.tagName() != "project") {
            throw("File seems to be in wrong format");
        }

        if (projectElement.attribute("name") != "interface") {
            throw("File is not from 'interface' build");
        }

        // Now loop over the platforms, looking for ours
        bool platformFound{ false };
        QDomElement platformElement = projectElement.firstChildElement();
        while (!platformElement.isNull()) {
            if (platformElement.attribute("name") == platformOfInterest) {
                platformFound = true;
                break;
            }
            platformElement = platformElement.nextSiblingElement();
        }

        if (!platformFound) {
            throw("File seems to be in wrong format - platform " + platformOfInterest + " not found");
        }

        // Now build vector
        QDomElement buildElement = platformElement.firstChildElement();
        while (!buildElement.isNull()) {
            BuildInformation buildInformation;
            if (buildElement.tagName() != "build") {
                throw("File seems to be in wrong format");
            }

            // First sibling should be version
            buildElement = buildElement.firstChildElement();
            if (buildElement.tagName() != "version") {
                throw("File seems to be in wrong format");
            }

            buildInformation.version = buildElement.text();

            // Next sibling should be stable_version
            buildElement = buildElement.nextSiblingElement();
            if (buildElement.tagName() != "stable_version") {
                throw("File seems to be in wrong format");
            }
            buildInformation.stable_version = buildElement.text();

            // Next sibling should be url
            buildElement = buildElement.nextSiblingElement();
            if (buildElement.tagName() != "url") {
                throw("File seems to be in wrong format");
            }
            buildInformation.url = buildElement.text();

            // Push on vector
            buildInformationVector.push_back(buildInformation);

            // Get next element
            buildElement = buildElement.parentNode().nextSiblingElement();
        }
    } catch (QString errorMessage) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), errorMessage);
        exit(-1);
    } catch (...) {
        QMessageBox::critical(0, "Internal error: " + QString(__FILE__) + ":" + QString::number(__LINE__), "unknown error");
        exit(-1);
    }

    return buildInformationVector;
}
