#ifndef DATA_H
#define DATA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <vector>
#include <map>

#include <QString>

using namespace std;

class Data
{
public:
    Data();
    Data(QString DataString);

    void storedata(QString DataString);
    QStringList getdata();

    void storedata1(QString DataString);
    QStringList getdata1();

private:
    QStringList data;
    QStringList data1;
};

#endif // DATA_H
