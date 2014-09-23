/****************************************************************************
** Meta object code from reading C++ file 'mediaWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../medienverwaltung/mediaWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mediaWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MediaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      29,   12,   12,   12, 0x0a,
      49,   43,   12,   12, 0x0a,
      86,   79,   74,   12, 0x0a,
     112,   12,   74,   12, 0x2a,
     127,   12,   12,   12, 0x0a,
     139,   79,   74,   12, 0x0a,
     165,   12,   74,   12, 0x2a,
     180,   12,   12,   12, 0x0a,
     199,  192,   12,   12, 0x0a,
     222,   12,   74,   12, 0x0a,
     233,   12,   74,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MediaWidget[] = {
    "MediaWidget\0\0updateActions()\0insertChild()\0"
    "index\0insertChild(QModelIndex)\0bool\0"
    "parent\0insertColumn(QModelIndex)\0"
    "insertColumn()\0insertRow()\0"
    "removeColumn(QModelIndex)\0removeColumn()\0"
    "removeRow()\0column\0resizeColumnWidth(int)\0"
    "loadFile()\0saveFile()\0"
};

void MediaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MediaWidget *_t = static_cast<MediaWidget *>(_o);
        switch (_id) {
        case 0: _t->updateActions(); break;
        case 1: _t->insertChild(); break;
        case 2: _t->insertChild((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: { bool _r = _t->insertColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->insertColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->insertRow(); break;
        case 6: { bool _r = _t->removeColumn((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->removeColumn();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: _t->removeRow(); break;
        case 9: _t->resizeColumnWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: { bool _r = _t->loadFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->saveFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MediaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MediaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MediaWidget,
      qt_meta_data_MediaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MediaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MediaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MediaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MediaWidget))
        return static_cast<void*>(const_cast< MediaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MediaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
