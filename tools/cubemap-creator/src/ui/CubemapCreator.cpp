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
}

void CubemapCreator::on_createButton_clicked() {
    creator.create6ColorCube();
}

void CubemapCreator::on_closeButton_clicked() {
    exit(0);
}