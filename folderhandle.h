#ifndef FOLDERHANDLE_H
#define FOLDERHANDLE_H
#include <QFileInfoList>
#include <QObject>

class FolderHandle:public QObject
{
    Q_OBJECT
public:
    explicit FolderHandle();
    ~FolderHandle();

    void setFilterType(const QString &filterType);

signals:
    void sig_progressValue(bool isSucced, const int value);

public slots:
    void slot_makeListFile(QString selectedPath);

private:
    //获取所有的文件夹地址
    QFileInfoList getAllFolderListPath(QString path);

    //获取所有的MP4文件名称
     QStringList getFileNameByFileInfoList(QString selectedPath,QFileInfoList allFileInfoList);

     //写入文件
     bool writeFileIntoTxt(QString selectedPath,QStringList nameList);

     QString m_filterType = "mp4";
};

#endif // FOLDERHANDLE_H
