#ifndef WINDOW_H
#define WINDOW_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QFileDialog>

#include <vector>
#include <map>

#include <QLabel>
#include <QVector>

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);

protected:
   // methods and membersss
    void paintEvent(QPaintEvent *event);
    QVector<QPushButton*> plsBtnList;
    QVector<QPushButton*> minBtnList;
    QString lbl;
    QStringList lbl2;
    QStringList data;

public slots:
    // event handlers (in Qt "slots")
    // ...
    void Open();
    void Plus();
    void Minus();
    void Check();
};

#endif
