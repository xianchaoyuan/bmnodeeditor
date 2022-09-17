#include "properties.h"

void Properties::put(QString const &name, QVariant const &v)
{
    _values.insert(name, v);
}


