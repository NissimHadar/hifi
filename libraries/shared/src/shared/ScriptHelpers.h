//
//  ScriptHelpers.h
//  libraries/shared/src
//
//  Created by Nissim Hadar on 8/23/2014.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//
#ifndef hifi_ScriptHelpers_h
#define hifi_ScriptHelpers_h

#include <QtGlobal>

#include <QtCore/QObject>
// Use a set of stubs
#include <QString>
#include <QVariant>
#include <QThread>
#include <QMenu>

class StubScriptEngine;
class StubScriptValue;
class StubScriptProgram;
class StubScriptString;
class StubScriptClass;
class StubScriptContext;
class StubScriptValueIterator;
using StubScriptValueList = QList<StubScriptValue>;
class StubScriptSyntaxCheckResult;
class StubScriptContextInfo;

#if defined(Q_OS_WINRT)
typedef double qsreal;
using QScriptEngine = StubScriptEngine;
using QScriptValue = StubScriptValue;
using QScriptContext = StubScriptContext;
using QScriptProgram = StubScriptProgram;
using QScriptValueList = StubScriptValueList;
using QScriptValueIterator = StubScriptValueIterator;
using QScriptSyntaxCheckResult = StubScriptSyntaxCheckResult;
using QScriptContextInfo = StubScriptContextInfo;


#else
// Use the Qt Script classes
#include <QtScript/QScriptable>
#include <QtScript/QScriptClass>
#include <QtScript/QScriptContextInfo>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>
#include <QtScript/QScriptValueList>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScriptTools/QtScriptTools>
#endif


class StubScriptValue {
public:
    StubScriptValue() {}
    StubScriptValue(const float) {}
    StubScriptValue(QString) {}
    StubScriptValue(const StubScriptValue&) {}
    StubScriptValue(bool) {}
    StubScriptValue(int) {}
    StubScriptValue(unsigned int) {}
    StubScriptValue(qsreal) {}
    StubScriptValue(int, StubScriptValue) {}

    StubScriptValue(StubScriptEngine* engine) { _enginePtr = engine;  }
    StubScriptValue(StubScriptEngine* engine, const QStringList& names, bool useNames) { _enginePtr = engine; }

    StubScriptValue operator=(const StubScriptValue&) { return this; }

    enum PropertyFlag {
        ReadOnly = 0x00000001,
        Undeletable = 0x00000002,
        SkipInEnumeration = 0x00000004,

        PropertyGetter = 0x00000008,
        PropertySetter = 0x00000010,

        QObjectMember = 0x00000020,

        KeepExistingFlags = 0x00000800,

        UserRange = 0xff000000            // Users may use these as they see fit.
    };
    Q_DECLARE_FLAGS(PropertyFlags, PropertyFlag)

    void setProperty(const QString &name, const StubScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}
    void setProperty(quint32 arrayIndex, const StubScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}
    void setProperty(const StubScriptString &name, const StubScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}

    StubScriptValue property(const QString&) const { return *this; }
    StubScriptValue property(const int& i) const { return *this; }
    StubScriptValue property(const StubScriptString&) const { return *this; }

    QVariant toVariant() const { return QVariant(); }
    int toInteger() const { return 0; }
    int toBool() const { return true; }
    qsreal toNumber() const { return 0; }
    QString toString() const { return ""; }
    unsigned int toUInt32() const { return 0; }
    int toInt32() const { return 0; }
    int toUInt16() const { return 0; }
    QObject* toQObject() const { QObject* o = new QObject(); return o; }

    bool isArray() const { return false; }
    bool isNumber() const { return true; }
    bool isValid() const { return true; }
    bool isString() const { return false; }
    bool isNull() const { return false; }
    bool isObject() const { return false; }
    bool isFunction() const { return false; }
    bool isBool() { return true; }
    bool isUndefined() { return true; }
    bool isError() const { return true; }
    bool equals(const StubScriptValue &other) const { return true; }
    bool strictlyEquals(const StubScriptValue & other) const { return true; }

    enum SpecialValue {
        NullValue,
        UndefinedValue
    };

    StubScriptValue call(const StubScriptValue & thisObject = StubScriptValue(), const StubScriptValueList & args = StubScriptValueList()) { return StubScriptValue(); }
    StubScriptEngine* engine() const { return _enginePtr; }

    StubScriptValue data() const { return StubScriptValue(); }
    void setData(const StubScriptValue & data) {}

    StubScriptValue construct(const StubScriptValueList & args = StubScriptValueList()) { return StubScriptValue(); }

    void setPrototype(const StubScriptValue & prototype) {}
    StubScriptValue prototype() const { return StubScriptValue(); }

private:
    StubScriptEngine* _enginePtr;
};

class StubScriptSyntaxCheckResult {
public:

    enum State {
        Error,
        Intermediate,
        Valid
    };
    State state() const { return Valid; }

    QString errorMessage() const { return QString(); }
    int errorLineNumber() const { return 1; }
    int errorColumnNumber() const { return 1; }
};

class StubScriptContext {
public:
    StubScriptContext() { parent = nullptr;  }

    StubScriptValue argument(int) const { return StubScriptValue(); }
    StubScriptValue callee() { return StubScriptValue(); }
    int argumentCount() const { return 0; }

    StubScriptValue thisObject() const { return StubScriptValue(); }
    StubScriptValue throwError(const QString &text) { return StubScriptValue(); }

    QStringList backtrace() const { return QStringList(); }
    StubScriptContext* parentContext() const { return parent; }

    bool StubScriptContext::isCalledAsConstructor() const { return false; }
    void setThisObject(const StubScriptValue & thisObject) {}

    StubScriptValue throwValue(const StubScriptValue & value) { return StubScriptValue(); }

    void pushScope(const StubScriptValue &object) {}

private:
    StubScriptContext* parent;
};

class StubScriptContextInfo {
public:
    StubScriptContextInfo(const StubScriptContext *context) {}

    QString fileName() const { return QString(); }

    int StubScriptContextInfo::lineNumber() const { return 1;  }
};

class StubScriptString {
public:
    QString StubScriptString::toString() const { return QString();  }

    bool operator==(const StubScriptString & other) const { return true; }

    quint32 toArrayIndex(bool * ok = 0) const { return 0; }
};

class StubScriptEngine : public QObject {
Q_OBJECT
public:
    StubScriptEngine(QObject* parent = nullptr);

    StubScriptValue newObject() { return StubScriptValue(); }
    StubScriptValue newObject(StubScriptClass * scriptClass, const StubScriptValue & data = StubScriptValue()) { return StubScriptValue(); }
    StubScriptValue newArray(uint length = 0) { return StubScriptValue(); }

    enum ValueOwnership {
        QtOwnership,
        ScriptOwnership,
        AutoOwnership
    };

    enum QObjectWrapOption {
        ExcludeChildObjects = 0x0001,
        ExcludeSuperClassMethods = 0x0002,
        ExcludeSuperClassProperties = 0x0004,
        ExcludeSuperClassContents = 0x0006,
        SkipMethodsInEnumeration = 0x0008,
        ExcludeDeleteLater = 0x0010,
        ExcludeSlots = 0x0020,

        AutoCreateDynamicProperties = 0x0100,
        PreferExistingWrapperObject = 0x0200
    };
    Q_DECLARE_FLAGS(QObjectWrapOptions, QObjectWrapOption)

    enum PropertyFlag {
        ReadOnly            = 0x00000001,
        Undeletable         = 0x00000002,
        SkipInEnumeration   = 0x00000004,

        PropertyGetter      = 0x00000008,
        PropertySetter      = 0x00000010,

        QObjectMember       = 0x00000020,

        KeepExistingFlags   = 0x00000800,

        UserRange           = 0xff000000            // Users may use these as they see fit.
    };
    Q_DECLARE_FLAGS(PropertyFlags, PropertyFlag)

    StubScriptValue newQObject(QObject* object, ValueOwnership ownership = QtOwnership, const int& options = 0) { return StubScriptValue(); }

    void setDefaultPrototype(int, const StubScriptValue&) {}

 
    StubScriptValue newVariant(QVariant) { return StubScriptValue(); }
    StubScriptValue newVariant(int) { return StubScriptValue(); }
    StubScriptValue undefinedValue() { return StubScriptValue(); }

    QThread* thread() { return QThread::currentThread();  }

    static StubScriptSyntaxCheckResult checkSyntax(const QString&) { return StubScriptSyntaxCheckResult(); }

    bool hasUncaughtException() const { return false; }
    QStringList uncaughtExceptionBacktrace() const { return QStringList(); }
    StubScriptValue uncaughtException() const { return StubScriptValue(); }
    int uncaughtExceptionLineNumber() const { return 0; }
    void clearExceptions() {}

    StubScriptValue evaluate(const QString & program, const QString & fileName = QString(), int lineNumber = 1) { return StubScriptValue(); }
    StubScriptValue evaluate(const StubScriptProgram & program) { return StubScriptValue(); }
    StubScriptValue globalObject() const { return StubScriptValue(); }

    template<typename T>
    StubScriptValue toScriptValue(const T&) { return StubScriptValue(); }

    StubScriptContext* currentContext() const { StubScriptContext* c = new StubScriptContext();  return c; }

    typedef StubScriptValue(*FunctionSignature)(StubScriptContext *, StubScriptEngine *);

    StubScriptValue create(int, const void*) { return StubScriptValue(); }

    void collectGarbage() {}
    void setProcessEventsInterval(int interval) {}

    bool isEvaluating() const { return false; }
    void abortEvaluation(const StubScriptValue &result = StubScriptValue()) {}

    StubScriptValue newFunction(FunctionSignature signature, int length = 0) { return StubScriptValue(); }
    StubScriptValue newFunction(FunctionSignature fun, const StubScriptValue & prototype, int length = 0) { return StubScriptValue(); }

    void reportAdditionalMemoryCost(int size) {}

    StubScriptValue nullValue() { return StubScriptValue();  }

    StubScriptString toStringHandle(const QString & str) { return StubScriptString(); }

    void setGlobalObject(const StubScriptValue & object) {}

    StubScriptContext *pushContext() { return &sc; }

    void popContext() {}

signals:
    void signalHandlerException(const StubScriptValue &exception);

private:
    StubScriptContext sc;
};

class StubScriptable {
public:
    StubScriptValue thisObject() const { return StubScriptValue(); }

    StubScriptEngine* engine() const { return nullptr; }
};

class StubScriptValueIterator {
public:
    StubScriptValueIterator(const StubScriptValue&) {}

    StubScriptValue value() { return StubScriptValue();  }

    bool hasNext() { return false; }
    bool isString() { return false; }
    bool isNumber() { return false; }

    void next() {}

    const char *name() const { return ""; }

    StubScriptValue::PropertyFlags StubScriptValueIterator::flags() const { return StubScriptValue::ReadOnly; }
};

class StubScriptProgram {
public:
    StubScriptProgram() {}
    StubScriptProgram::StubScriptProgram(const QString & sourceCode, const QString fileName = QString(), int firstLineNumber = 1) {}

    QString sourceCode() const { return QString(); }
    QString fileName() const { return QString(); }

    bool StubScriptProgram::isNull() const { return false; }
};

class StubScriptEngineDebugger : public QObject
{
Q_OBJECT
public:
    StubScriptEngineDebugger(QObject *parent = Q_NULLPTR) {}
    void attachTo(StubScriptEngine *engine) {}
    QMenu *createStandardMenu(QWidget *parent = Q_NULLPTR) { return &menu; }

private:
    QMenu menu;
};

class StubScriptClass {
public:
    StubScriptClass(StubScriptEngine *engine) { _enginePtr = engine;  }

    enum QueryFlag {
        HandlesReadAccess = 0x01,
        HandlesWriteAccess = 0x02
    };
    Q_DECLARE_FLAGS(QueryFlags, QueryFlag)

    virtual QueryFlags queryProperty(const StubScriptValue &object, const StubScriptString &name, QueryFlags flags, uint *id) { return HandlesReadAccess; }
    
    virtual StubScriptValue property(const StubScriptValue& object, const StubScriptString& name, uint id) { return StubScriptValue(); }
    virtual void setProperty(StubScriptValue &object, const StubScriptString &name, uint id, const StubScriptValue &value) {}
    virtual StubScriptValue::PropertyFlags propertyFlags(const StubScriptValue& object, const StubScriptString& name, uint id) { return StubScriptValue::ReadOnly; }

    virtual QString name() const { return QString(); }
    virtual StubScriptValue prototype() const { return StubScriptValue(); }

    StubScriptEngine* engine() const { return _enginePtr; }

private:
    StubScriptEngine* _enginePtr;
};


#ifdef Q_OS_WINRT
template<typename T>
int qScriptRegisterMetaType(
    StubScriptEngine* engine,
    StubScriptValue(*toScriptValue)(StubScriptEngine *, const T &t),
    void(*fromScriptValue)(const StubScriptValue &, T &t),
    const StubScriptValue &prototype = StubScriptValue()
) {
    return 0;
}


template<typename T>
T qscriptvalue_cast(const StubScriptValue &value) {
    return T();
}


inline StubScriptValue qScriptValueFromValue_helper(StubScriptEngine *engine, int type, const void *ptr) {
    if (!engine)
        return StubScriptValue();

    return engine->create(type, ptr);
}

template<typename T>
int qScriptRegisterSequenceMetaType(
    StubScriptEngine *engine,
    const StubScriptValue &prototype = StubScriptValue()
) {
    return 0;
}

template <typename T>
inline StubScriptValue qScriptValueFromValue(StubScriptEngine *engine, const T &t) {
    return StubScriptValueFromValue_helper(engine, qMetaTypeId<T>(), &t);
}

template <class Container>
StubScriptValue qScriptValueFromSequence(QScriptEngine *eng, const Container &cont) {
    StubScriptValue a = eng->newArray();
    typename Container::const_iterator begin = cont.begin();
    typename Container::const_iterator end = cont.end();
    typename Container::const_iterator it;
    quint32 i;
    for (it = begin, i = 0; it != end; ++it, ++i)
        a.setProperty(i, eng->toScriptValue(*it));
    return a;
}
#endif


#endif // hifi_ScriptHelpers_h
