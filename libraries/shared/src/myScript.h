#ifndef hifi_MyScript_h
#define hifi_MyScript_h

#include <QString>
#include <QVariant>
#include <QThread>

typedef double qsreal;

class QScriptEngine;
class QScriptValue;
class QScriptProgram;
class QScriptString;

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

    QScriptValue(QScriptEngine* engine) { _enginePtr = engine;  }
    QScriptValue(QScriptEngine* engine, const QStringList& names, bool useNames) { _enginePtr = engine; }

    QScriptValue operator=(const QScriptValue&) { return this; }

    void setProperty(const QString&, const QScriptValue&) {}
    void setProperty(const QString&, const QString&) {}
    void setProperty(const QScriptString&, quint32) {}
    void setProperty(int i, const QScriptValue&) {}
    void setProperty(const char*, const char*) {}

    QScriptValue property(const QString&) const { return *this; }
    QScriptValue property(const int& i) const { return *this; }

    QVariant toVariant() const { return QVariant(); }
    int toInteger() const { return 0; }
    int toBool() const { return true; }
    int toNumber() const { return 0; }
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

    enum SpecialValue {
        NullValue,
        UndefinedValue
    };

    QScriptValue call(const QScriptValue & thisObject = QScriptValue(), const QScriptValueList & args = QScriptValueList()) { return QScriptValue(); }
    QScriptEngine* engine() const { return _enginePtr; }

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
    QScriptValue argument(int) const { return QScriptValue(); }
    QScriptValue callee() { return QScriptValue(); }
    int argumentCount() const { return 0; }

    QScriptValue thisObject() const { return QScriptValue(); }
};

class QScriptEngine : public QObject {
Q_OBJECT
public:
    QScriptEngine() {}
    QScriptEngine(QObject*) {}

    QScriptValue newObject() { return QScriptValue(); }
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

    QScriptValue evaluate(const QScriptProgram&) { return QScriptValue(); }
    QScriptValue evaluate(const QByteArray&) { return QScriptValue(); }
    QScriptValue globalObject() const { return QScriptValue(); }

    template<typename T>
    QScriptValue toScriptValue(const T&) { return QScriptValue(); }

    QScriptContext* currentContext() const { QScriptContext* c = new QScriptContext();  return c; }

    typedef QScriptValue(*FunctionSignature)(QScriptContext *, QScriptEngine *);
};

class QScriptable {
public:
    QScriptValue thisObject() const { return QScriptValue(); }
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
};

class QScriptProgram {
public:
    QScriptProgram() {}
    QScriptProgram::QScriptProgram(const QString & sourceCode, const QString fileName = QString(), int firstLineNumber = 1) {}

    QString sourceCode() const { return QString(); }
    QString fileName() const { return QString(); }
};

class QScriptString {

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
#endif