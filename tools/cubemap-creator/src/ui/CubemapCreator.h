//
//  CubemapCreator.h
//
//  Created by Nissim Hadar on 18 Jan 2018.
//  Copyright 2013 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#ifndef hifi_CubemapCreator_h
#define hifi_CubemapCreator_h

#include <QtWidgets/QMainWindow>
#include "ui_CubemapCreator.h"
#include "../Test.h"

class CubemapCreator : public QMainWindow {
    Q_OBJECT

public:
    CubemapCreator(QWidget *parent = Q_NULLPTR);

private slots:
    void on_evaluateTestsButton_clicked();
    void on_evaluateTestsRecursivelyButton_clicked();
    void on_createRecursiveScriptButton_clicked();
    void on_createTestButton_clicked();
    void on_deleteOldSnapshotsButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::CubemapCreatorClass ui;

    Test test;
};

#endif // hifi_CubemapCreator_h