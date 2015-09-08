/****************************************************************************
** Meta object code from reading C++ file 'OutputWindowImpl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../OutputWindowImpl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OutputWindowImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_OutputWindowImpl_t {
    QByteArrayData data[10];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OutputWindowImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OutputWindowImpl_t qt_meta_stringdata_OutputWindowImpl = {
    {
QT_MOC_LITERAL(0, 0, 16), // "OutputWindowImpl"
QT_MOC_LITERAL(1, 17, 17), // "AddCategorySignal"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "categoryName"
QT_MOC_LITERAL(4, 49, 13), // "RefreshSignal"
QT_MOC_LITERAL(5, 63, 4), // "text"
QT_MOC_LITERAL(6, 68, 18), // "AddCategoryHandler"
QT_MOC_LITERAL(7, 87, 14), // "RefreshHandler"
QT_MOC_LITERAL(8, 102, 20), // "ComboCategoryChanged"
QT_MOC_LITERAL(9, 123, 3) // "cat"

    },
    "OutputWindowImpl\0AddCategorySignal\0\0"
    "categoryName\0RefreshSignal\0text\0"
    "AddCategoryHandler\0RefreshHandler\0"
    "ComboCategoryChanged\0cat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OutputWindowImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    2,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   47,    2, 0x0a /* Public */,
       7,    2,   50,    2, 0x0a /* Public */,
       8,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void OutputWindowImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OutputWindowImpl *_t = static_cast<OutputWindowImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddCategorySignal((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->RefreshSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->AddCategoryHandler((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->RefreshHandler((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->ComboCategoryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (OutputWindowImpl::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutputWindowImpl::AddCategorySignal)) {
                *result = 0;
            }
        }
        {
            typedef void (OutputWindowImpl::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&OutputWindowImpl::RefreshSignal)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject OutputWindowImpl::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_OutputWindowImpl.data,
      qt_meta_data_OutputWindowImpl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *OutputWindowImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OutputWindowImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_OutputWindowImpl.stringdata0))
        return static_cast<void*>(const_cast< OutputWindowImpl*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int OutputWindowImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void OutputWindowImpl::AddCategorySignal(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OutputWindowImpl::RefreshSignal(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
