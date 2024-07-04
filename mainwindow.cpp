#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Txt_SystemData->setReadOnly(true);

    QSettings settings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\BIOS", QSettings::NativeFormat);
    QString Str = QString("BIOS Data :");
    Str.append(QString("\r\nBase Manufacturer : %1").arg(settings.value("BaseBoardManufacturer", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nBase Product : %1").arg(settings.value("BaseBoardProduct", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nBIOS Vendor : %1").arg(settings.value("BIOSVendor", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nBIOS Release Date : %1").arg(settings.value("BIOSReleaseDate", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nSystem Manufacturer : %1").arg(settings.value("SystemManufacturer", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nProduct Name : %1").arg(settings.value("SystemProductName", "0").toString().toLocal8Bit().constData()));
    Str.append(QString("\r\nSystem SKU : %1").arg(settings.value("SystemSKU", "0").toString().toLocal8Bit().constData()));
    //QMessageBox::about(this,QString("System ID"),Str);
    ui->Txt_SystemData->append(Str);

    Str = QString("");
    Str.append(QString("\r\nCPU Architecture : %1").arg(QSysInfo::currentCpuArchitecture().toLocal8Bit().constData()));
    Str.append(QString("\r\nProduct Type : %1").arg(QSysInfo::prettyProductName().toLocal8Bit().constData()));
    Str.append(QString("\r\nKernel Type : %1").arg(QSysInfo::kernelType().toLocal8Bit().constData()));
    Str.append(QString("\r\nKernel Version : %1").arg(QSysInfo::kernelVersion().toLocal8Bit().constData()));
    Str.append(QString("\r\nMachine Host Name : %1").arg(QSysInfo::machineHostName().toLocal8Bit().constData()));
    Str.append(QString("\r\nMachine Unique ID : %1").arg(QString::fromLocal8Bit(QSysInfo::machineUniqueId())));
    ui->Txt_SystemData->append(Str);

    Str = QString("");
    QProcess process_system;
    if(QSysInfo::kernelType() == "winnt")
    {
        QString cpuname = "wmic cpu get name";
        process_system.start(cpuname);
        process_system.waitForFinished();
        Str.append(QString("\r\nCPU : %1").arg(QString::fromLocal8Bit(process_system.readAllStandardOutput().toUpper())));

        QString gpuname = "wmic PATH Win32_videocontroller get VideoProcessor ";
        process_system.start(gpuname);
        process_system.waitForFinished();
        Str.append(QString("\r\nGPU : %1").arg(QString::fromLocal8Bit(process_system.readAllStandardOutput())));

        QString gpuRam = "wmic PATH Win32_VideoController get AdapterRAM";
        process_system.start(gpuRam);
        process_system.waitForFinished();
        Str.append(QString("\r\nGPU RAM : %1").arg(QString::fromLocal8Bit(process_system.readAllStandardOutput())));
    }
    else if(QSysInfo::kernelType() == "linux")
    {
        QString linuxcpuname = "cat /proc/cpuinfo | grep 'model name' | uniq";
        process_system.start(linuxcpuname);
        process_system.waitForFinished();
        Str.append(QString("Linux CPU Info : %1").arg(QString::fromLocal8Bit(process_system.readAllStandardOutput())));
    }
    //QMessageBox::about(this,QString("System ID"),Str);
    ui->Txt_SystemData->append(Str);
}

MainWindow::~MainWindow()
{
    delete ui;
}

