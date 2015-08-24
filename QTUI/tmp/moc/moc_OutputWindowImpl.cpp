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
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_OutputWindowImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_OutputWindowImpl_t qt_meta_stringdata_OutputWindowImpl = {
    {
QT_MOC_LITERAL(0, 0, 16), // "OutputWindowImpl"
QT_MOC_LITERAL(1, 17, 10), // "UpdateText"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12) // "categoryName"

    },
    "OutputWindowImpl\0UpdateText\0\0categoryName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_OutputWindowImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void OutputWindowImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OutputWindowImpl *_t = static_cast<OutputWindowImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
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
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
