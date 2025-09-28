#include "data.h"

Data::Data()
{
    dataString= "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
}

Data::Data(QString DataString)
{
    dataString= DataString;
}

void Data::storedataString(QString DataString)
{
    dataString= DataString;
}

QString Data::getdataString()
{
    return dataString;
}
