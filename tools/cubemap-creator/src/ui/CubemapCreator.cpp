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

    ui.checkBoxInteractiveMode->setChecked(true);

    ui.progressBar->setVisible(false);
}

void CubemapCreator::on_evaluateTestsButton_clicked() {
    test.evaluateTests(ui.checkBoxInteractiveMode->isChecked(), ui.progressBar);
}

void CubemapCreator::on_evaluateTestsRecursivelyButton_clicked() {
    test.evaluateTestsRecursively(ui.checkBoxInteractiveMode->isChecked(), ui.progressBar);
}

void CubemapCreator::on_createRecursiveScriptButton_clicked() {
    test.createRecursiveScript();
}

void CubemapCreator::on_createTestButton_clicked() {
    test.createTest();
}

void CubemapCreator::on_deleteOldSnapshotsButton_clicked() {
    test.deleteOldSnapshots();
}

void CubemapCreator::on_closeButton_clicked() {
    exit(0);
}