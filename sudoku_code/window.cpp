#include "window.h"

#include <QPainter>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>

#include <map>
#include <vector>

#include <QFile>
#include <QVector>

using namespace std;


// Main window class
Window::Window(QWidget *parent) : QWidget(parent)
{
   // set form size
   setFixedSize(700,600);
   setWindowTitle("Sudoku");

   // create widgets....
   for(int i=0; i<81; i++)
   {
       data.append("0");
   }
   for(int i=0; i<81; i++)
   {
       lbl2.append(" ");
   }
   //open button
   auto *openBtn = new QPushButton("Open", this);
   openBtn->setGeometry(615, 185, 75, 30);

   connect(openBtn, &QPushButton::clicked, this, &Window::Open);

   //plus&minus buttons
   int l=0;

   for(int k=0; k<9; k++)
   {
       for(int j=0; j<9; j++)
       {
           if(data[l]=="0")
           {
           auto *plsBtn= new QPushButton("^", this);
           auto *minBtn= new QPushButton("v", this);
           plsBtnList.append(plsBtn);
           minBtnList.append(minBtn);

           plsBtnList[l]->setGeometry(44 + j*66.6, 16.65 + k*66.6, 20, 20);
           minBtnList[l]->setGeometry(44 + j*66.6, 35.65 + k*66.6, 20, 20);

           plsBtnList[l]->setProperty("order", l);
           minBtnList[l]->setProperty("order", l);

           connect(plsBtnList[l], &QPushButton::clicked, this, &Window::Plus);
           connect(minBtnList[l], &QPushButton::clicked, this, &Window::Minus);
           l++;
           }
       }
   }
    //check button
   auto *checkBtn = new QPushButton("Check", this);
   checkBtn->setGeometry(615, 250, 75, 30);

   connect(checkBtn, &QPushButton::clicked, this, &Window::Check);
}

void Window::Plus() {
    QPushButton *plsBtn = qobject_cast<QPushButton*>(sender());
    int ord= plsBtn->property("order").toInt();

    int val= data[ord].toInt();
    if(val!=9){val++;}

    data[ord]= QString::number(val);
    update();
}

void Window::Minus() {
    QPushButton *plsBtn = qobject_cast<QPushButton*>(sender());
    int ord= plsBtn->property("order").toInt();

    int val= data[ord].toInt();
    if(val!=0){val--;}

    data[ord]= QString::number(val);
    update();
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

    //leftmost line and topmost line
    painter.setPen(pen2);
    QPoint p3(0, 0), p4(0,600);
    painter.drawLine(p3, p4);
    QPoint p5(0, 0), p6(600, 0);
    painter.drawLine(p5, p6);

    //QStringList DataList= data1.getdata();
    int i=0;
    for(int k=0; k<9; k++)
    {
        for(int j=0; j<9; j++)
        {
            if(k==0){
                if((j==2)|(j==5)|(j==9)) { painter.setPen(pen2);}
                else {painter.setPen(pen);}
                QPoint p1(66.6+j*66.6, 0), p2(66.6+j*66.6,600);
                painter.drawLine(p1, p2);
            }
            painter.setPen(pen2);
            painter.drawText(24 + j*66.6, 44 + k*66.6, data[i]);
            painter.drawText(10 + j*66.6, 44 + k*66.6, lbl2[i]);
            i++;
        }
        if((k==2)|(k==5)|(k==9)) { painter.setPen(pen2);}
        else {painter.setPen(pen);}
        QPoint p1(0, 66.6+k*66.6 ), p2(600,66.6+k*66.6);
        painter.drawLine(p1, p2);
    }

    //rightmost line and bottommost line
    painter.setPen(pen2);
    QPoint p7(600, 0), p8(600, 600);
    painter.drawLine(p7, p8);
    QPoint p9(0, 600), p10(600, 600);
    painter.drawLine(p9, p10);

    //font.setPixelSize(20);
    painter.setFont(QFont("times",12));
     if(lbl=="Incorrect"){painter.drawText(615, 325, lbl);}
     else if(lbl=="You won!"){painter.drawText(615, 325, lbl);}
}

void Window:: Open(){
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open File"), "C:/Users/theov/OneDrive/Documents/EEE2023-2024/Semester2/Advanced Programming/lab work/P7/P7proj", tr("Text Files (*.txt)"));

    QFile file(fileName);

    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);

    QString DataString;

    DataString= in.readAll();

    QStringList DataList= DataString.split(",");

    data= DataList;

    //disconnect signals with initial nonzero value and reconnects them with zero value
    int i=0;
    for(int k=0; k<9; k++)
    {
        for(int j=0; j<9; j++)
        {
            if(data[i]!="0")
            {
                disconnect(plsBtnList[i], &QPushButton::clicked, this, &Window::Plus);
                disconnect(minBtnList[i], &QPushButton::clicked, this, &Window::Minus);
                lbl2[i]="*";
            }
            else
            {
                if((disconnect(plsBtnList[i], &QPushButton::clicked, this, &Window::Plus)&&
                        disconnect(minBtnList[i], &QPushButton::clicked, this, &Window::Minus))== true)
                {
                connect(plsBtnList[i], &QPushButton::clicked, this, &Window::Plus);
                connect(minBtnList[i], &QPushButton::clicked, this, &Window::Minus);
                }
                lbl2[i]=" ";
            }
            i++;
        }
    }
    lbl=" ";
    file.close();
}

void Window:: Check(){

    //check for horizontal sum
    int sum=0;
    int i=0;
    int sg0=0, sg1=0, sg2=0;
    for(int k=0; k<9; k++)
    {
        for(int j=0; j<9; j++)
        {
            sum += data[i].toInt();
            i++;
        }
        if(sum!=45) { lbl= "Incorrect";sg0=1;
            update();}
        else{ sum=0; }
    }
  // qDebug()<<sg0;
    // check for vertical sum
    sum=0;
    for(int j=0; j<9; j++)
    {
        for(int k=0; k<9; k++)
        {
            sum += data[j+(9*k)].toInt();
        }
        if(sum!=45) { lbl= "Incorrect";sg1=1;
            update(); }
        else{ sum=0; }
    }

   // qDebug()<<sg1;
    //check for each 9 cell groups sum
    sum=0;
    for(int l=0; l<2; l++)
    {
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<3; j++)
            {
                for(int k=0; k<3; k++)
                {
                    sum += data[k+(9*j)+(3*i)+(27*l)].toInt();
                }
            }
            //qDebug()<<sum;
            if(sum!=45) { lbl= "Incorrect";sg2=1;
                update(); }
            else{ sum=0; }
         }
    }

    qDebug()<<sg2;
    if(((sg0!=1)&&(sg1!=1)&&(sg2!=1))==true){lbl= "You won!";}
}
