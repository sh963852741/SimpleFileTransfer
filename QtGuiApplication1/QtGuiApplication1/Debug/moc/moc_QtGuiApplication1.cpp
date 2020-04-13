/****************************************************************************
** Meta object code from reading C++ file 'QtGuiApplication1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QtGuiApplication1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtGuiApplication1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtGuiApplication1_t {
    QByteArrayData data[17];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtGuiApplication1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtGuiApplication1_t qt_meta_stringdata_QtGuiApplication1 = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QtGuiApplication1"
QT_MOC_LITERAL(1, 18, 12), // "BeginSending"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 8), // "basepath"
QT_MOC_LITERAL(4, 41, 8), // "filename"
QT_MOC_LITERAL(5, 50, 16), // "updateRecvFloder"
QT_MOC_LITERAL(6, 67, 6), // "floder"
QT_MOC_LITERAL(7, 74, 13), // "StopReceiving"
QT_MOC_LITERAL(8, 88, 12), // "showFileList"
QT_MOC_LITERAL(9, 101, 14), // "ShowSendingMsg"
QT_MOC_LITERAL(10, 116, 2), // "id"
QT_MOC_LITERAL(11, 119, 3), // "msg"
QT_MOC_LITERAL(12, 123, 14), // "ShowRecvingMsg"
QT_MOC_LITERAL(13, 138, 8), // "filePath"
QT_MOC_LITERAL(14, 147, 9), // "SendFiles"
QT_MOC_LITERAL(15, 157, 18), // "ShowRecvingMsgById"
QT_MOC_LITERAL(16, 176, 16) // "selectRecvFloder"

    },
    "QtGuiApplication1\0BeginSending\0\0"
    "basepath\0filename\0updateRecvFloder\0"
    "floder\0StopReceiving\0showFileList\0"
    "ShowSendingMsg\0id\0msg\0ShowRecvingMsg\0"
    "filePath\0SendFiles\0ShowRecvingMsgById\0"
    "selectRecvFloder"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtGuiApplication1[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   67,    2, 0x0a /* Public */,
       8,    0,   68,    2, 0x0a /* Public */,
       9,    2,   69,    2, 0x0a /* Public */,
      12,    1,   74,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,
      15,    2,   78,    2, 0x0a /* Public */,
      16,    0,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::QString,   10,   11,
    QMetaType::Void,

       0        // eod
};

void QtGuiApplication1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtGuiApplication1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BeginSending((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 1: _t->updateRecvFloder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->StopReceiving(); break;
        case 3: _t->showFileList(); break;
        case 4: _t->ShowSendingMsg((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->ShowRecvingMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->SendFiles(); break;
        case 7: _t->ShowRecvingMsgById((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->selectRecvFloder(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtGuiApplication1::*)(QString , QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtGuiApplication1::BeginSending)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtGuiApplication1::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtGuiApplication1::updateRecvFloder)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtGuiApplication1::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_QtGuiApplication1.data,
    qt_meta_data_QtGuiApplication1,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtGuiApplication1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtGuiApplication1::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtGuiApplication1.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int QtGuiApplication1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QtGuiApplication1::BeginSending(QString _t1, QStringList _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtGuiApplication1::updateRecvFloder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
