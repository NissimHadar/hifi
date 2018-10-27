//
//  CubemapCreator.cpp
//  zone/ambientLightInheritence
//
//  Created by Nissim Hadar on 2 Nov 2017.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#include "CubemapCreator.h"

CubemapCreator::CubemapCreator(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);

    ui.progressBar->setVisible(false);
}

void CubemapCreator::on_whiteButton_clicked() {
    creator.createWhiteCube();
}

void CubemapCreator::on_yellowButton_clicked() {
    creator.createYellowCube();
}

void CubemapCreator::on_create6ColorsButton_clicked() {
    creator.create6ColorCube();
}

void CubemapCreator::on_createSphericalGridButton_clicked() {
    creator.createSphericalGridCube();
}

void CubemapCreator::on_createStarMapButton_clicked() {
    creator.createStarMap(ui.progressBar);
}

void CubemapCreator::on_closeButton_clicked() {
    exit(0);
}