/****************************************************************************
** Meta object code from reading C++ file 'Controller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Client/Controller/Controller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Controller_t {
    const uint offsetsAndSize[28];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Controller_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Controller_t qt_meta_stringdata_Controller = {
    {
QT_MOC_LITERAL(0, 10), // "Controller"
QT_MOC_LITERAL(11, 15), // "OnGotoLoginPage"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 7), // "OnLogin"
QT_MOC_LITERAL(36, 38), // "LoginModel::JSONFormatter::Cr..."
QT_MOC_LITERAL(75, 11), // "credentials"
QT_MOC_LITERAL(87, 8), // "OnLogout"
QT_MOC_LITERAL(96, 19), // "OnChangeMainSubPage"
QT_MOC_LITERAL(116, 12), // "MainSubPages"
QT_MOC_LITERAL(129, 4), // "page"
QT_MOC_LITERAL(134, 16), // "OnGotoSignupPage"
QT_MOC_LITERAL(151, 8), // "OnSignup"
QT_MOC_LITERAL(160, 11), // "SignupInDTO"
QT_MOC_LITERAL(172, 6) // "in_dto"

    },
    "Controller\0OnGotoLoginPage\0\0OnLogin\0"
    "LoginModel::JSONFormatter::Credentials\0"
    "credentials\0OnLogout\0OnChangeMainSubPage\0"
    "MainSubPages\0page\0OnGotoSignupPage\0"
    "OnSignup\0SignupInDTO\0in_dto"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Controller[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    1,   51,    2, 0x0a,    2 /* Public */,
       6,    0,   54,    2, 0x0a,    4 /* Public */,
       7,    1,   55,    2, 0x0a,    5 /* Public */,
      10,    0,   58,    2, 0x0a,    7 /* Public */,
      11,    1,   59,    2, 0x0a,    8 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Controller *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->OnGotoLoginPage(); break;
        case 1: _t->OnLogin((*reinterpret_cast< LoginModel::JSONFormatter::Credentials(*)>(_a[1]))); break;
        case 2: _t->OnLogout(); break;
        case 3: _t->OnChangeMainSubPage((*reinterpret_cast< MainSubPages(*)>(_a[1]))); break;
        case 4: _t->OnGotoSignupPage(); break;
        case 5: _t->OnSignup((*reinterpret_cast< const SignupInDTO(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Controller.offsetsAndSize,
    qt_meta_data_Controller,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Controller_t
, QtPrivate::TypeAndForceComplete<Controller, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<LoginModel::JSONFormatter::Credentials, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<MainSubPages, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const SignupInDTO &, std::false_type>


>,
    nullptr
} };


const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Controller.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
