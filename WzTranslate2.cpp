#include "WzTranslate2.h"

#include <QDebug>
#include <QFile>

WzTranslate2::WzTranslate2()
{
    qDebug()<<"WzTranslate2: WzTranslate()";

    library = NULL;
    isLoaded = false;
    fileName = "";
    currentLanguage = "";
}

WzTranslate2::WzTranslate2(const QString &fileName)
{
    qDebug()<<"WzTranslate2: WzTranslate(const QString &fileName)";

    library = NULL;
    isLoaded = false;

    this->fileName = fileName;
}

WzTranslate2::~WzTranslate2()
{
    qDebug()<<"WzTranslate2: ~WzTranslate()";

    release();
}

void WzTranslate2::setFileName(const QString &fileName)
{
    qDebug()<<"WzTranslate2: setFileName(const QString &fileName)";

    this->fileName = fileName;
}

void WzTranslate2::setCurrentLanguage(const QString &language)
{
    qDebug()<<"WzTranslate2: setCurrentLanguage(const QString &language)";

    this->currentLanguage = language;
}

bool WzTranslate2::load()
{
    qDebug()<<"WzTranslate2: load(const char* encode)";

    if(fileName.isEmpty())
    {
        qDebug()<<"WzTranslate2: 加载失败，文件名不能为空";
        return false;
    }
    QFile file(fileName);
    if(file.exists())
    {
        if(!file.open(QIODevice::ReadWrite))//如果文件存在但不可写
        {
            qDebug()<< "WzTranslate2: 加载失败，文件不可写";
            file.close();
            return false;
        }
        file.close();
    }
    else
    {
        qDebug()<< "WzTranslate2: 加载失败，文件不存在";
        return false;
    }

    //创建库对象
    library = new WzIni();
    if(library == NULL)
    {
        qDebug()<<"WzTranslate2: 加载失败，library对象创建失败";
        return false;
    }
    if(library->loadFile(this->fileName.toStdString()))
    {
        qDebug()<< "WzTranslate2: 加载成功，文件路径为: "<<this->fileName;

        isLoaded = true;
        return true;
    }
    else
    {
        qDebug()<< "WzTranslate2: 加载失败，请传入绝对路径";
        return false;
    }
}

bool WzTranslate2::updatelibrary(const QString &key, const QString &value)
{
    qDebug()<<"WzTranslate2: updatelibrary(const QString &key, const QString &value)";
    if(!isLoaded)
    {
        qDebug()<<"WzTranslate2: 更新语言库失败，库未成功加载";
        return false;
    }
    if(currentLanguage.isEmpty())
    {
        qDebug()<<"WzTranslate2: 更新语言库失败，当前语言为空，请调用setCurrentLanguage函数设置当前语言";
        return false;
    }

    library->setValue(currentLanguage.toStdString(),key.toStdString(),value.toStdString());
    return true;
}

QString WzTranslate2::tr(const QString &key)
{
    qDebug()<<"WzTranslate2: tr(const QString &key)";

    if(!isLoaded)
    {
        qDebug()<<"WzTranslate2: 翻译失败，库未成功加载";
        return "translate failed";
    }
    if(currentLanguage.isEmpty())
    {
        qDebug()<<"WzTranslate2: 翻译失败，当前语言为空，请调用setCurrentLanguage函数设置当前语言";
        return "translate failed";
    }

    if(library->hasKey(currentLanguage.toStdString(),key.toStdString()))
    {
        return QString::fromStdString(library->getValueString(currentLanguage.toStdString(),key.toStdString()));
    }
    else
    {
        return key;
    }
}

void WzTranslate2::close()
{
    qDebug()<<"WzTranslate2: close()";
    release();
}

void WzTranslate2::test()
{
    qDebug()<<"WzTranslate2: test()";
    library->print();
}

void WzTranslate2::release()
{
    if(library != NULL)
    {
        delete library;
        library = NULL;
    }
    fileName = "";
    currentLanguage = "";
    isLoaded = false;
}
