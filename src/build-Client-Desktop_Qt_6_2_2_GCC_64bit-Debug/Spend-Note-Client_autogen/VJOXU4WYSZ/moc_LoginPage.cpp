/****************************************************************************
** Meta object code from reading C++ file 'LoginPage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Client/View/LoginPage/LoginPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginPage_t {
    const uint offsetsAndSize[22];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_LoginPage_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_LoginPage_t qt_meta_stringdata_LoginPage = {
    {
QT_MOC_LITERAL(0, 9), // "LoginPage"
QT_MOC_LITERAL(10, 10), // "GotoSignup"
QT_MOC_LITERAL(21, 0), // ""
QT_MOC_LITERAL(22, 5), // "Login"
QT_MOC_LITERAL(28, 38), // "LoginModel::JSONFormatter::Cr..."
QT_MOC_LITERAL(67, 11), // "credentials"
QT_MOC_LITERAL(79, 26), // "OnLoginSubmitButtonClicked"
QT_MOC_LITERAL(106, 21), // "OnSignupButtonClicked"
QT_MOC_LITERAL(128, 21), // "OnPasswordTextChanged"
QT_MOC_LITERAL(150, 4), // "arg1"
QT_MOC_LITERAL(155, 18) // "OnLoginTextChanged"

    },
    "LoginPage\0GotoSignup\0\0Login\0"
    "LoginModel::JSONFormatter::Credentials\0"
    "credentials\0OnLoginSubmitButtonClicked\0"
    "OnSignupButtonClicked\0OnPasswordTextChanged\0"
    "arg1\0OnLoginTextChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,
       3,    1,   51,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   54,    2, 0x08,    4 /* Private */,
       7,    0,   55,    2, 0x08,    5 /* Private */,
       8,    1,   56,    2, 0x08,    6 /* Private */,
      10,    1,   59,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void LoginPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->GotoSignup(); break;
        case 1: _t->Login((*reinterpret_cast< LoginModel::JSONFormatter::Credentials(*)>(_a[1]))); break;
        case 2: _t->OnLoginSubmitButtonClicked(); break;
        case 3: _t->OnSignupButtonClicked(); break;
        case 4: _t->OnPasswordTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->OnLoginTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginPage::GotoSignup)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginPage::*)(LoginModel::JSONFormatter::Credentials );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginPage::Login)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LoginPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LoginPage.offsetsAndSize,
    qt_meta_data_LoginPage,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LoginPage_t
, QtPrivate::TypeAndForceComplete<LoginPage, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<LoginModel::JSONFormatter::Credentials, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>


>,
    nullptr
} };


const QMetaObject *LoginPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LoginPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void LoginPage::GotoSignup()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginPage::Login(LoginModel::JSONFormatter::Credentials _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
