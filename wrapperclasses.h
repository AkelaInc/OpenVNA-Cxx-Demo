#ifndef WRAPPERCLASSES_H
#define WRAPPERCLASSES_H

//#include "../../../vnadll/akela_vna_dll.h"
#include <QObject>

/*
 * Because I can't pass custom types through signals/slots
 * without registering them with Qt, here I define a macro
 * to generate wrapper classes that conform with Qt's needs.
 * All of my types are either enums or trivial structs with
 * pointers that can be shallow-copied (i.e. the compiler
 * will generate the struct-copying code for me).
*/

#define WRAPPER_CLASS(name) \
class Qt##name \
{ \
public: \
    name val; \
    int time; \
    Qt##name() {} \
    Qt##name(const Qt##name& other) { this->val = other.val; this->time = other.time; } \
    ~Qt##name() {} \
    Qt##name(name newval) { this->val = newval; this->time = 0; } \
}; \
Q_DECLARE_METATYPE(Qt##name)


WRAPPER_CLASS(ErrCode)
WRAPPER_CLASS(CalibrationStep)
WRAPPER_CLASS(TaskHandle)
WRAPPER_CLASS(ComplexData)

WRAPPER_CLASS(progress_callback)
typedef void* voidptr;
WRAPPER_CLASS(voidptr)

#endif // WRAPPERCLASSES_H
