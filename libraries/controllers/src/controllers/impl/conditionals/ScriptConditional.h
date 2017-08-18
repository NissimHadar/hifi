//
//  Created by Bradley Austin Davis 2015/10/20
//  Copyright 2015 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#pragma once
#ifndef hifi_Controllers_ScriptConditional_h
#define hifi_Controllers_ScriptConditional_h

#include <QtCore/QObject>

#ifndef HIFI_UWP
#include <QtScript/QScriptValue>
#endif

#include "../Conditional.h"

namespace controller {

class ScriptConditional : public QObject, public Conditional {
    Q_OBJECT;
public:
#ifdef HIFI_UWP
    ScriptConditional() {}
#else
    ScriptConditional(const QScriptValue& callable) : _callable(callable) { }
#endif
    virtual bool satisfied() override;
protected:
    Q_INVOKABLE void updateValue();
private:
#ifndef HIFI_UWP
    QScriptValue _callable;
#endif

    bool _lastValue { false };
};

}
#endif
