#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMediaPlayer>
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

QFileInfoList MainWindow:: getAllFolderListPath(QString path)
{
    qDebug()<<"path"<<path;
    QDir dir(path);
    dir.setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList = dir.entryInfoList();

    if(fileInfoList.length() !=0 )
    {
        //遍历文件夹内的所有文件夹
        foreach (QFileInfo folder, fileInfoList)
        {
            QFileInfoList subFileInfoList =  getAllFolderListPath(folder.absoluteFilePath());
            if(subFileInfoList.length() !=0)
            {
                fileInfoList.append(subFileInfoList);
            }
        }
    }

    return fileInfoList;
}

QStringList MainWindow::getAllFileName(QString preName,QFileInfoList allFileInfoList)
{
    QStringList fileNameList;
    foreach (QFileInfo folder, allFileInfoList)
    {
        QDir dir(folder.absoluteFilePath());
        dir.setFilter(QDir::Files|QDir::NoDotAndDotDot);
        dir.setNameFilters(QStringList("*.mp4"));

        QFileInfoList mp4InfoList = dir.entryInfoList();
        if(mp4InfoList.length() != 0)
        {
            fileNameList.append(folder.filePath().remove(preName+"/"));
            foreach (QFileInfo mp4Info, mp4InfoList)
            {
                fileNameList.append(mp4Info.fileName().remove(".mp4"));
            }
            fileNameList.append("");
        }
    }
    return fileNameList;
}

bool MainWindow::writeFileIntoTxt(QString savePath, QStringList nameList)
{
    QFile file(savePath+"/list.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    foreach(QString name,nameList)
    {
        QByteArray  strBytes=(name+"\n").toUtf8();
        //QByteArray  strBytes=str.toLocal8Bit();
        file.write(strBytes,strBytes.length());  //写入文件
    }
    file.close();

    return true;
}


void MainWindow::on_pushButton_clicked()
{
    QString preName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    QFileInfoList allFileInfoList =  getAllFolderListPath(preName);
    allFileInfoList.append(QFileInfo(preName));

    writeFileIntoTxt(preName,getAllFileName(preName,allFileInfoList));
}
