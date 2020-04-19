#include "folderhandle.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QDate>

const int g_folderLoaded = 33;
const int g_fileNameLoaed = 66;
const int g_writeFileFinished = 100;

FolderHandle::FolderHandle()
{

}

FolderHandle::~FolderHandle()
{

}

void FolderHandle::setFilterType(const QString &filterType)
{
    m_filterType = filterType;
}

QFileInfoList FolderHandle:: getAllFolderListPath(QString path)
{
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

    emit sig_progressValue(true,g_folderLoaded);

    return fileInfoList;
}

QStringList FolderHandle::getFileNameByFileInfoList(QString selectedPath,QFileInfoList allFileInfoList)
{
    QStringList fileNameList;
    foreach (QFileInfo folder, allFileInfoList)
    {
        QDir dir(folder.absoluteFilePath());
        dir.setFilter(QDir::Files|QDir::NoDotAndDotDot);

//        QString filterType =;
        dir.setNameFilters(QStringList( "*."+m_filterType));

        QFileInfoList mp4InfoList = dir.entryInfoList();
        if(mp4InfoList.length() != 0)
        {
            if(folder.filePath() != selectedPath)
                fileNameList.append(folder.filePath().remove(selectedPath+"/"));

            foreach (QFileInfo mp4Info, mp4InfoList)
            {
                //获取MP4文件名
                fileNameList.append(mp4Info.fileName().remove("."+m_filterType));
            }

            //分隔
            fileNameList.append("");
        }
    }

    emit sig_progressValue(true,g_fileNameLoaed);
    return fileNameList;
}

bool FolderHandle::writeFileIntoTxt(QString selectedPath, QStringList nameList)
{
    QString path = QString("%1/list_%2.txt")
            .arg(selectedPath)
            .arg(QDate::currentDate().toString("yyyy_MM_dd"));
    qDebug()<<path;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    foreach(QString name,nameList)
    {
        QByteArray  strBytes=(name+"\n").toUtf8();
        file.write(strBytes,strBytes.length());  //写入文件
    }
    file.close();

    return true;
}

void FolderHandle::slot_makeListFile(QString selectedPath)
{
    QFileInfoList allFileInfoList = getAllFolderListPath(selectedPath);
    //加入当前选中的文件夹
    allFileInfoList.append(QFileInfo(selectedPath));

    emit sig_progressValue(
                //写入文件
                writeFileIntoTxt(
                    selectedPath,
                    getFileNameByFileInfoList(selectedPath,allFileInfoList)
                    ),
                g_writeFileFinished);
}
