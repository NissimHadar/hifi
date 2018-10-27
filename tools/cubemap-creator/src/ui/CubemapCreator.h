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
#include "../Creator.h"

class CubemapCreator : public QMainWindow {
    Q_OBJECT

public:
    CubemapCreator(QWidget *parent = Q_NULLPTR);

private slots:
    void on_closeButton_clicked();
    void on_whiteButton_clicked();
    void on_yellowButton_clicked();
    void on_create6ColorsButton_clicked();
    void on_createSphericalGridButton_clicked();
    void on_createStarMapButton_clicked();

private:
    Ui::CubemapCreatorClass ui;

    Creator creator;
};

#endif // hifi_CubemapCreator_h