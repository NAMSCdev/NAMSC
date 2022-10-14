#include "Global.h"

QMap<const type_info&, const QString> allowedTypes = 
{
    { typeid(int), "int" },
    { typeid(double), "double" },
    { typeid(bool), "bool" },
    { typeid(QString), "QString" }
};