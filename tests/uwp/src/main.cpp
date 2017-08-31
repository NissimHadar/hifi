//
//  Created by Bradley Austin Davis on 2017/06/06
//  Copyright 2013-2017 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <mutex>

#include <QtGui/QGuiApplication>
#include <QtGui/QWindow>


class UwpTestApp : public QGuiApplication {
    Q_OBJECT
public:
    UwpTestApp(int argc, char* argv[]);
    ~UwpTestApp();


private:
    void finish(int exitCode);
};


UwpTestApp::UwpTestApp(int argc, char* argv[]) :
    QGuiApplication(argc, argv)
{
    auto window = new QWindow();
    window->show();
}

UwpTestApp::~UwpTestApp() {
}

void UwpTestApp::finish(int exitCode) {
    QCoreApplication::exit(exitCode);
}

int main(int argc, char * argv[]) {
    QCoreApplication::setApplicationName("UwpTest");
    QCoreApplication::setOrganizationName("High Fidelity");
    QCoreApplication::setOrganizationDomain("highfidelity.com");
    QCoreApplication::setApplicationVersion("1.0");
    UwpTestApp app(argc, argv);
    return app.exec();
}

#include "main.moc"
