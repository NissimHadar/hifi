//
//  ArrayBufferViewClass.h
//
//
//  Created by Clement on 7/8/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef hifi_ArrayBufferViewClass_h
#define hifi_ArrayBufferViewClass_h

#ifndef HIFI_UWP
#include <QScriptClass>
#endif
#include <QtCore/QObject>

#ifndef HIFI_UWP
#include <QtScript/QScriptClass>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptString>
#include <QtScript/QScriptValue>
#endif

#include "ScriptEngine.h"

static const QString BUFFER_PROPERTY_NAME = "buffer";
static const QString BYTE_OFFSET_PROPERTY_NAME = "byteOffset";
static const QString BYTE_LENGTH_PROPERTY_NAME = "byteLength";

#ifdef HIFI_UWP
class ArrayBufferViewClass : public QObject {
#else
class ArrayBufferViewClass : public QObject, public QScriptClass {
#endif
    Q_OBJECT
public:
#ifdef HIFI_UWP
    ArrayBufferViewClass();
#else
    ArrayBufferViewClass(ScriptEngine* scriptEngine);

    ScriptEngine* getScriptEngine() { return _scriptEngine; }

    virtual QueryFlags queryProperty(const QScriptValue& object,
                                     const QScriptString& name,
                                     QueryFlags flags, uint* id) override;
    virtual QScriptValue property(const QScriptValue& object,
                                  const QScriptString& name, uint id) override;
    virtual QScriptValue::PropertyFlags propertyFlags(const QScriptValue& object,
                                                      const QScriptString& name, uint id) override;
#endif
protected:
    // JS Object attributes
    QScriptString _bufferName;
    QScriptString _byteOffsetName;
    QScriptString _byteLengthName;

#ifndef HIFI_UWP
    ScriptEngine* _scriptEngine;
#endif
};

#endif // hifi_ArrayBufferViewClass_h
