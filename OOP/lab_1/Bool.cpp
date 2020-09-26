#include "Bool.h"

Bool &Bool::operator=(bool val) {
    _value = val;
    return *this;
}

Bool::operator bool() const { return _value; }

Bool::Bool(bool val) {
    _value = val;
}

Bool::Bool() :_value{false}{}
