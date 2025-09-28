#include "window.h"
#include "data.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>

#include <map>
#include <vector>

#include <QFile>

Data data1;

Window::Window(QWidget *parent) : QWidget(parent)
{
   // set form size
   setFixedSize(1000,1000);
   setWindowTitle("Sudoku bla....");

   QFile file("C:/Users/theov/OneDrive/Documents/EEE2023-2024/Semester2/Advanced Programming/lab work/P6/P6proj/game.txt");

   file.open(QIODevice::ReadOnly | QIODevice::Text);

   QTextStream in(&file);

   QString DataString;

   DataString= in.readAll();

   data1.storedataString(DataString);

   file.close();
}


void Window::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen, pen2;
    QFont font;
    font.setPixelSize(30);
    pen.setWidth(1);
    pen2.setWidth(4);
    painter.setPen(pen);
    painter.setFont(font);
    QPoint p1(10,20), p2(80,60);
    painter.drawLine(p1, p2);
    painter.setPen(pen2);
    QPoint p3(80, 20), p4(80,900);
    painter.drawLine(p3, p4);
    QPoint p5(20, 60), p6(900, 60);
    painter.drawLine(p5, p6);

    QString DataString= data1.getdataString();
    QStringList DataList= DataString.split(" ");
    for(int i=0; i<81; i++)
    {
        for(int j=0; j<9; j++)
        {
            if((j==2)|(j==5)|(j==9)) { painter.setPen(pen2);}
            else {painter.setPen(pen);}
            QPoint p1(150+j*90, 20), p2(150+j*90,900);
            painter.drawLine(p1, p2);
            for(int k=0; k<9; k++)
            {
                painter.setPen(pen2);
                painter.drawText(100 + j*90,100 + k*80, DataList[i]);
            }
        }
    }
    for(int k=0; k<9; k++)
    {
        if((k==2)|(k==5)|(k==9)) { painter.setPen(pen2);}
        else {painter.setPen(pen);}
        QPoint p1(20, 130+k*80 ), p2(900,130+k*80);
        painter.drawLine(p1, p2);
    }
    painter.setPen(pen2);
    QPoint p7(870, 20), p8(870, 820);
    painter.drawLine(p7, p8);
    QPoint p9(20, 770), p10(900, 770 );
    painter.drawLine(p9, p10);
}

void Window::mouseReleaseEvent(QMouseEvent * event) 
{
    // get click position
    qDebug() << "Mouse x " << event->x() << " Mouse y " << event->y();
}
