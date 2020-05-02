/****************************************************************************
** Meta object code from reading C++ file 'FileSender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FileSender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileSender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FilesSender_t {
    QByteArrayData data[19];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FilesSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FilesSender_t qt_meta_stringdata_FilesSender = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FilesSender"
QT_MOC_LITERAL(1, 12, 11), // "rpt_process"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 2), // "id"
QT_MOC_LITERAL(4, 28, 3), // "msg"
QT_MOC_LITERAL(5, 32, 12), // "BeginSending"
QT_MOC_LITERAL(6, 45, 8), // "basepath"
QT_MOC_LITERAL(7, 54, 8), // "filename"
QT_MOC_LITERAL(8, 63, 9), // "IPaddress"
QT_MOC_LITERAL(9, 73, 11), // "StopSending"
QT_MOC_LITERAL(10, 85, 11), // "setcompress"
QT_MOC_LITERAL(11, 97, 1), // "a"
QT_MOC_LITERAL(12, 99, 10), // "setencrypt"
QT_MOC_LITERAL(13, 110, 16), // "process_compress"
QT_MOC_LITERAL(14, 127, 13), // "process_begin"
QT_MOC_LITERAL(15, 141, 15), // "process_process"
QT_MOC_LITERAL(16, 157, 5), // "value"
QT_MOC_LITERAL(17, 163, 16), // "process_complete"
QT_MOC_LITERAL(18, 180, 7) // "success"

    },
    "FilesSender\0rpt_process\0\0id\0msg\0"
    "BeginSending\0basepath\0filename\0IPaddress\0"
    "StopSending\0setcompress\0a\0setencrypt\0"
    "process_compress\0process_begin\0"
    "process_process\0value\0process_complete\0"
    "success"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FilesSender[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   64,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    1,   72,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,
      13,    1,   78,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,
      15,    2,   84,    2, 0x0a /* Public */,
      17,    3,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::QString,    6,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort, QMetaType::Int,    3,   16,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool, QMetaType::QString,    3,   18,    4,

       0        // eod
};

void FilesSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FilesSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rpt_process((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->BeginSending((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->StopSending(); break;
        case 3: _t->setcompress((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setencrypt((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->process_compress((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        case 6: _t->process_begin((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        case 7: _t->process_process((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->process_complete((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FilesSender::*)(unsigned short , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FilesSender::rpt_process)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FilesSender::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_FilesSender.data,
    qt_meta_data_FilesSender,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FilesSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FilesSender::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FilesSender.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FilesSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void FilesSender::rpt_process(unsigned short _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SingleFileSender_t {
    QByteArrayData data[10];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SingleFileSender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SingleFileSender_t qt_meta_stringdata_SingleFileSender = {
    {
QT_MOC_LITERAL(0, 0, 16), // "SingleFileSender"
QT_MOC_LITERAL(1, 17, 11), // "compressing"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 2), // "id"
QT_MOC_LITERAL(4, 33, 5), // "begin"
QT_MOC_LITERAL(5, 39, 7), // "process"
QT_MOC_LITERAL(6, 47, 5), // "value"
QT_MOC_LITERAL(7, 53, 8), // "complete"
QT_MOC_LITERAL(8, 62, 7), // "success"
QT_MOC_LITERAL(9, 70, 3) // "msg"

    },
    "SingleFileSender\0compressing\0\0id\0begin\0"
    "process\0value\0complete\0success\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SingleFileSender[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    2,   40,    2, 0x06 /* Public */,
       7,    3,   45,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::UShort, QMetaType::Int,    3,    6,
    QMetaType::Void, QMetaType::UShort, QMetaType::Bool, QMetaType::QString,    3,    8,    9,

       0        // eod
};

void SingleFileSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SingleFileSender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->compressing((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->begin((*reinterpret_cast< unsigned short(*)>(_a[1]))); break;
        case 2: _t->process((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->complete((*reinterpret_cast< unsigned short(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SingleFileSender::*)(unsigned  );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleFileSender::compressing)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SingleFileSender::*)(unsigned short );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleFileSender::begin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SingleFileSender::*)(unsigned short , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleFileSender::process)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SingleFileSender::*)(unsigned short , bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SingleFileSender::complete)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SingleFileSender::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SingleFileSender.data,
    qt_meta_data_SingleFileSender,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SingleFileSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SingleFileSender::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SingleFileSender.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int SingleFileSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SingleFileSender::compressing(unsigned  _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SingleFileSender::begin(unsigned short _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SingleFileSender::process(unsigned short _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SingleFileSender::complete(unsigned short _t1, bool _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
