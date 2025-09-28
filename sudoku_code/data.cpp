#include "data.h"
#include <iostream>

using namespace std;

Data::Data()
{
    QStringList DataString;
    for(int i=0; i<81; i++)
    {
        DataString.append("0");
    }

    data= DataString;
    data1= DataString;
}

Data::Data(QString DataString)
{
    data= DataString.split(",");
    data1= data;
}

void Data::storedata(QString DataString)
{
    data= DataString.split(",");
}

QStringList Data::getdata()
{
    return data;
}

void Data::storedata1(QString DataString)
{
    data1= DataString.split(",");
}

QStringList Data::getdata1()
{
    return data1;
}

