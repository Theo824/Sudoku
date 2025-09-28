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
    void storedataString(QString DataString);
    QString getdataString();

private:
    QString dataString;
};

#endif // DATA_H
