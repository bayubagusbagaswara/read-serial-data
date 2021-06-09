#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include <QApplication>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QMessageBox>
#include <QFile>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
QApplication a(argc, argv);
QSerialPortInfo info("COM6");
    // Check info of the port
            qDebug() << "Name        : " << info.portName();
            qDebug() << "Manufacturer: " << info.manufacturer();
            qDebug() << "Busy: " << info.isBusy() << endl;

// Initialize Serial
QSerialPort serial;
serial.setPortName("COM6");
serial.open(QIODevice::ReadWrite);
serial.setBaudRate(QSerialPort::Baud9600);
serial.setDataBits(QSerialPort::Data8);
serial.setParity(QSerialPort::NoParity);
serial.setStopBits(QSerialPort::OneStop);
serial.setFlowControl(QSerialPort::NoFlowControl);

QFile file("C:\\Users\\Keenan\\Documents\\serialTest\\arduinoData.txt");//open file

if(!file.exists())
 {
    qDebug()<<"File Doesn't Exist";
 }
if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
 {
     QMessageBox::information(0, "error", file.errorString());
 };

QTextStream stream(&file);


while (serial.isOpen())
 {
  serial.waitForReadyRead(-1);
  QString data;
  data = serial.readAll();
  qDebug() << "Data has been found: " << data <<endl;
  stream << data << endl;
 }

file.close();
qDebug() << "Done" << endl;
return a.exec();
}
