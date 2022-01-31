/****************************************************************************
** Meta object code from reading C++ file 'MainPage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Client/View/MainPage/MainPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainPage_t {
    const uint offsetsAndSize[18];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainPage_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainPage_t qt_meta_stringdata_MainPage = {
    {
QT_MOC_LITERAL(0, 8), // "MainPage"
QT_MOC_LITERAL(9, 13), // "ChangeSubPage"
QT_MOC_LITERAL(23, 0), // ""
QT_MOC_LITERAL(24, 12), // "MainSubPages"
QT_MOC_LITERAL(37, 4), // "page"
QT_MOC_LITERAL(42, 6), // "Logout"
QT_MOC_LITERAL(49, 18), // "OnGoToListsClicked"
QT_MOC_LITERAL(68, 15), // "OnLogoutClicked"
QT_MOC_LITERAL(84, 9) // "OnAddList"

    },
    "MainPage\0ChangeSubPage\0\0MainSubPages\0"
    "page\0Logout\0OnGoToListsClicked\0"
    "OnLogoutClicked\0OnAddList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    0,   47,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   48,    2, 0x0a,    4 /* Public */,
       7,    0,   49,    2, 0x0a,    5 /* Public */,
       8,    0,   50,    2, 0x0a,    6 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ChangeSubPage((*reinterpret_cast< MainSubPages(*)>(_a[1]))); break;
        case 1: _t->Logout(); break;
        case 2: _t->OnGoToListsClicked(); break;
        case 3: _t->OnLogoutClicked(); break;
        case 4: _t->OnAddList(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainPage::*)(MainSubPages );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainPage::ChangeSubPage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainPage::Logout)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MainPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MainPage.offsetsAndSize,
    qt_meta_data_MainPage,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainPage_t
, QtPrivate::TypeAndForceComplete<MainPage, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<MainSubPages, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MainPage::ChangeSubPage(MainSubPages _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainPage::Logout()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
