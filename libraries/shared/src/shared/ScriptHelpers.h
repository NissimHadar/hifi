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

#ifndef HIFI_UWP
// Use the Qt Script classes
#include <QScriptable>
#include <QScriptClass>
#include <QScriptContextInfo>
#include <QScriptEngine>
#include <QScriptValue>
#include <QScriptValueIterator>
#include <QScriptValueList>
#include <QtScript/QScriptContext>
#include <QtScript/QScriptEngine>
#include <QtScriptTools/QtScriptTools>

#else
// Use a set of stubs
#include <QString>
#include <QVariant>
#include <QThread>
#include <QMenu>

typedef double qsreal;

class QScriptEngine;
class QScriptValue;
class QScriptProgram;
class QScriptString;
class QScriptClass;

typedef QList<QScriptValue> QScriptValueList;

class QScriptValue {
public:
    QScriptValue() {}
    QScriptValue(const float) {}
    QScriptValue(QString) {}
    QScriptValue(const QScriptValue&) {}
    QScriptValue(bool) {}
    QScriptValue(int) {}
    QScriptValue(unsigned int) {}
    QScriptValue(qsreal) {}
    QScriptValue(int, QScriptValue) {}

    QScriptValue(QScriptEngine* engine) { _enginePtr = engine;  }
    QScriptValue(QScriptEngine* engine, const QStringList& names, bool useNames) { _enginePtr = engine; }

    QScriptValue operator=(const QScriptValue&) { return this; }

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

    void setProperty(const QString &name, const QScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}
    void setProperty(quint32 arrayIndex, const QScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}
    void setProperty(const QScriptString &name, const QScriptValue &value, const PropertyFlags &flags = KeepExistingFlags) {}

    QScriptValue property(const QString&) const { return *this; }
    QScriptValue property(const int& i) const { return *this; }
    QScriptValue property(const QScriptString&) const { return *this; }

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
    bool equals(const QScriptValue &other) const { return true; }
    bool strictlyEquals(const QScriptValue & other) const { return true; }

    enum SpecialValue {
        NullValue,
        UndefinedValue
    };

    QScriptValue call(const QScriptValue & thisObject = QScriptValue(), const QScriptValueList & args = QScriptValueList()) { return QScriptValue(); }
    QScriptEngine* engine() const { return _enginePtr; }

    QScriptValue QScriptValue::data() const { return QScriptValue(); }
    void QScriptValue::setData(const QScriptValue & data) {}

    QScriptValue QScriptValue::construct(const QScriptValueList & args = QScriptValueList()) { return QScriptValue(); }

    void QScriptValue::setPrototype(const QScriptValue & prototype) {}
    QScriptValue QScriptValue::prototype() const { return QScriptValue(); }

private:
    QScriptEngine* _enginePtr;
};

class QScriptSyntaxCheckResult {
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

class QScriptContext {
public:
    QScriptContext() { parent = nullptr;  }

    QScriptValue argument(int) const { return QScriptValue(); }
    QScriptValue callee() { return QScriptValue(); }
    int argumentCount() const { return 0; }

    QScriptValue thisObject() const { return QScriptValue(); }
    QScriptValue throwError(const QString &text) { return QScriptValue(); }

    QStringList backtrace() const { return QStringList(); }
    QScriptContext* parentContext() const { return parent; }

    bool QScriptContext::isCalledAsConstructor() const { return false; }
    void setThisObject(const QScriptValue & thisObject) {}

    QScriptValue throwValue(const QScriptValue & value) { return QScriptValue(); }

    void pushScope(const QScriptValue &object) {}

private:
    QScriptContext* parent;
};

class QScriptContextInfo {
public:
    QScriptContextInfo(const QScriptContext *context) {}

    QString fileName() const { return QString(); }

    int QScriptContextInfo::lineNumber() const { return 1;  }
};

class QScriptString {
public:
    QString QScriptString::toString() const { return QString();  }

    bool operator==(const QScriptString & other) const { return true; }

    quint32 toArrayIndex(bool * ok = 0) const { return 0; }
};

class QScriptEngine : public QObject {
Q_OBJECT
public:
    QScriptEngine() {}
    QScriptEngine(QObject*) {}

    QScriptValue newObject() { return QScriptValue(); }
    QScriptValue newObject(QScriptClass * scriptClass, const QScriptValue & data = QScriptValue()) { return QScriptValue(); }
    QScriptValue newArray(uint length = 0) { return QScriptValue(); }

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

    QScriptValue QScriptEngine::newQObject(QObject* object, ValueOwnership ownership = QtOwnership, const int& options = 0) { return QScriptValue(); }

    void setDefaultPrototype(int, const QScriptValue&) {}

 
    QScriptValue newVariant(QVariant) { return QScriptValue(); }
    QScriptValue newVariant(int) { return QScriptValue(); }
    QScriptValue undefinedValue() { return QScriptValue(); }

    QThread* thread() { return QThread::currentThread();  }

    static QScriptSyntaxCheckResult QScriptEngine::checkSyntax(const QString&) { return QScriptSyntaxCheckResult(); }

    bool hasUncaughtException() const { return false; }
    QStringList uncaughtExceptionBacktrace() const { return QStringList(); }
    QScriptValue uncaughtException() const { return QScriptValue(); }
    int uncaughtExceptionLineNumber() const { return 0; }
    void clearExceptions() {}

    QScriptValue evaluate(const QString & program, const QString & fileName = QString(), int lineNumber = 1) { return QScriptValue(); }
    QScriptValue evaluate(const QScriptProgram & program) { return QScriptValue(); }
    QScriptValue globalObject() const { return QScriptValue(); }

    template<typename T>
    QScriptValue toScriptValue(const T&) { return QScriptValue(); }

    QScriptContext* currentContext() const { QScriptContext* c = new QScriptContext();  return c; }

    typedef QScriptValue(*FunctionSignature)(QScriptContext *, QScriptEngine *);

    QScriptValue create(int, const void*) { return QScriptValue(); }

    void collectGarbage() {}
    void setProcessEventsInterval(int interval) {}

    bool isEvaluating() const { return false; }
    void abortEvaluation(const QScriptValue &result = QScriptValue()) {}

    QScriptValue newFunction(FunctionSignature signature, int length = 0) { return QScriptValue(); }
    QScriptValue newFunction(FunctionSignature fun, const QScriptValue & prototype, int length = 0) { return QScriptValue(); }

    void reportAdditionalMemoryCost(int size) {}

    QScriptValue QScriptEngine::nullValue() { return QScriptValue();  }

    QScriptString toStringHandle(const QString & str) { return QScriptString(); }

    void setGlobalObject(const QScriptValue & object) {}

    QScriptContext *pushContext() { return &sc; }

    void popContext() {}

    void signalHandlerException(const QScriptValue &exception) {}

private:
    QScriptContext sc;
};

class QScriptable {
public:
    QScriptValue thisObject() const { return QScriptValue(); }

    QScriptEngine* engine() const { return nullptr; }
};

class QScriptValueIterator {
public:
    QScriptValueIterator(const QScriptValue&) {}

    QScriptValue value() { return QScriptValue();  }

    bool hasNext() { return false; }
    bool isString() { return false; }
    bool isNumber() { return false; }

    void next() {}

    const char *name() const { return ""; }

    QScriptValue::PropertyFlags QScriptValueIterator::flags() const { return QScriptValue::ReadOnly; }
};

class QScriptProgram {
public:
    QScriptProgram() {}
    QScriptProgram::QScriptProgram(const QString & sourceCode, const QString fileName = QString(), int firstLineNumber = 1) {}

    QString sourceCode() const { return QString(); }
    QString fileName() const { return QString(); }

    bool QScriptProgram::isNull() const { return false; }
};

class QScriptEngineDebugger : public QObject
{
Q_OBJECT
public:
    QScriptEngineDebugger(QObject *parent = Q_NULLPTR) {}
    void attachTo(QScriptEngine *engine) {}
    QMenu *createStandardMenu(QWidget *parent = Q_NULLPTR) { return &menu; }

private:
    QMenu menu;
};

class QScriptClass {
public:
    QScriptClass(QScriptEngine *engine) { _enginePtr = engine;  }

    enum QueryFlag {
        HandlesReadAccess = 0x01,
        HandlesWriteAccess = 0x02
    };
    Q_DECLARE_FLAGS(QueryFlags, QueryFlag)

    virtual QueryFlags queryProperty(const QScriptValue &object, const QScriptString &name, QueryFlags flags, uint *id) { return HandlesReadAccess; }
    
    virtual QScriptValue property(const QScriptValue& object, const QScriptString& name, uint id) { return QScriptValue(); }
    virtual void setProperty(QScriptValue &object, const QScriptString &name, uint id, const QScriptValue &value) {}
    virtual QScriptValue::PropertyFlags propertyFlags(const QScriptValue& object, const QScriptString& name, uint id) { return QScriptValue::ReadOnly; }

    virtual QString name() const { return QString(); }
    virtual QScriptValue prototype() const { return QScriptValue(); }

    QScriptEngine* engine() const { return _enginePtr; }

private:
    QScriptEngine* _enginePtr;
};

typedef QList<QScriptValue> QScriptValueList;

template<typename T>
int qScriptRegisterMetaType(
    QScriptEngine* engine,
    QScriptValue(*toScriptValue)(QScriptEngine *, const T &t),
    void(*fromScriptValue)(const QScriptValue &, T &t),
    const QScriptValue &prototype = QScriptValue()
) {
    return 0;
}

template<typename T>
T qscriptvalue_cast(const QScriptValue &value)
{
    return T();
}

template<typename T>
int qScriptRegisterSequenceMetaType(
    QScriptEngine *engine,
    const QScriptValue &prototype = QScriptValue()
)
{
    return 0;
}

inline QScriptValue qScriptValueFromValue_helper(QScriptEngine *engine, int type, const void *ptr)
{
    if (!engine)
        return QScriptValue();

    return engine->create(type, ptr);
}

template <typename T>
inline QScriptValue qScriptValueFromValue(QScriptEngine *engine, const T &t)
{
    return qScriptValueFromValue_helper(engine, qMetaTypeId<T>(), &t);
}

template <class Container>
QScriptValue qScriptValueFromSequence(QScriptEngine *eng, const Container &cont)
{
    QScriptValue a = eng->newArray();
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