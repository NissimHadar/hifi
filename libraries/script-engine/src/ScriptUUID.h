//
//  ScriptUUID.h
//  libraries/script-engine/src/
//
//  Created by Andrew Meadows on 2014-04-07
//  Copyright (c) 2014 High Fidelity, Inc. All rights reserved.
//
//  Scriptable interface for a UUID helper class object. Used exclusively in the JavaScript API
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_ScriptUUID_h
#define hifi_ScriptUUID_h

#include <QUuid>

#ifndef HIFI_UWP
#include <QtScript/QScriptable>
#endif

/// Scriptable interface for a UUID helper class object. Used exclusively in the JavaScript API
#ifdef HIFI_UWP
class ScriptUUID : public QObject {
#else
class ScriptUUID : public QObject, protected QScriptable {
#endif
    Q_OBJECT

public slots:
    QUuid fromString(const QString& string);
    QString toString(const QUuid& id);
    QUuid generate();
    bool isEqual(const QUuid& idA, const QUuid& idB);
    bool isNull(const QUuid& id);
    void print(const QString& label, const QUuid& id);
};

#endif // hifi_ScriptUUID_h
