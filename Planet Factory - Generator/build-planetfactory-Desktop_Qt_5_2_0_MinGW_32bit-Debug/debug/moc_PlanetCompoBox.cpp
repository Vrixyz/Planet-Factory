/****************************************************************************
** Meta object code from reading C++ file 'PlanetCompoBox.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interface_2/PlanetCompoBox.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlanetCompoBox.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlanetCompoBox_t {
    QByteArrayData data[14];
    char stringdata[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PlanetCompoBox_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PlanetCompoBox_t qt_meta_stringdata_PlanetCompoBox = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 18),
QT_MOC_LITERAL(2, 34, 0),
QT_MOC_LITERAL(3, 35, 20),
QT_MOC_LITERAL(4, 56, 20),
QT_MOC_LITERAL(5, 77, 18),
QT_MOC_LITERAL(6, 96, 17),
QT_MOC_LITERAL(7, 114, 17),
QT_MOC_LITERAL(8, 132, 22),
QT_MOC_LITERAL(9, 155, 22),
QT_MOC_LITERAL(10, 178, 13),
QT_MOC_LITERAL(11, 192, 13),
QT_MOC_LITERAL(12, 206, 13),
QT_MOC_LITERAL(13, 220, 13)
    },
    "PlanetCompoBox\0changePercentCompo\0\0"
    "componentPlaSelected\0componentSysSelected\0"
    "windowSysEditCompo\0windowSysAddCompo\0"
    "windowPlaAddCompo\0windowSysCloseAndClean\0"
    "windowPlaCloseAndClean\0addCompoToSys\0"
    "delCompoToSys\0addCompoToPla\0delCompoToPla\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlanetCompoBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x0a,
       3,    0,   77,    2, 0x0a,
       4,    0,   78,    2, 0x0a,
       5,    0,   79,    2, 0x0a,
       6,    0,   80,    2, 0x0a,
       7,    0,   81,    2, 0x0a,
       8,    0,   82,    2, 0x0a,
       9,    0,   83,    2, 0x0a,
      10,    0,   84,    2, 0x0a,
      11,    0,   85,    2, 0x0a,
      12,    0,   86,    2, 0x0a,
      13,    1,   87,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void PlanetCompoBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlanetCompoBox *_t = static_cast<PlanetCompoBox *>(_o);
        switch (_id) {
        case 0: _t->changePercentCompo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->componentPlaSelected(); break;
        case 2: _t->componentSysSelected(); break;
        case 3: _t->windowSysEditCompo(); break;
        case 4: _t->windowSysAddCompo(); break;
        case 5: _t->windowPlaAddCompo(); break;
        case 6: _t->windowSysCloseAndClean(); break;
        case 7: _t->windowPlaCloseAndClean(); break;
        case 8: _t->addCompoToSys(); break;
        case 9: _t->delCompoToSys(); break;
        case 10: _t->addCompoToPla(); break;
        case 11: _t->delCompoToPla((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PlanetCompoBox::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_PlanetCompoBox.data,
      qt_meta_data_PlanetCompoBox,  qt_static_metacall, 0, 0}
};


const QMetaObject *PlanetCompoBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlanetCompoBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlanetCompoBox.stringdata))
        return static_cast<void*>(const_cast< PlanetCompoBox*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int PlanetCompoBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
