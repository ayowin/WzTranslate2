#ifndef WZTRANSLATE2_H
#define WZTRANSLATE2_H

#include <QObject>
#include <QString>
#include "WzIni.h"

class WzTranslate2 : public QObject
{
    Q_OBJECT
public:
    WzTranslate2();
    WzTranslate2(const QString &fileName);
    ~WzTranslate2();

    //设置文件名，即：语言库的文件名，搭配无参构造函数使用
    Q_INVOKABLE void setFileName(const QString &fileName);
    //设置当前语言
    Q_INVOKABLE void setCurrentLanguage(const QString &language);
    //加载语言库
    Q_INVOKABLE bool load();
    //更新语言库，deprecated（不推荐使用），如果没有必要插入，则不需要调用这个函数
    Q_INVOKABLE bool updatelibrary(const QString &key,const QString &value);
    //翻译函数，tr为translate缩写，减少使用过程中的代码复杂度
    //成功返回实际值，失败返回key值
    Q_INVOKABLE QString tr(const QString &key);
    //关闭并释放内存
    Q_INVOKABLE void close();
    //测试当前语言库的所有输出
    Q_INVOKABLE void test();

private:
    //释放内存
    void release();

private:
    QString fileName;
    QString currentLanguage;
    bool isLoaded;

    WzIni *library;
};

#endif // WZTRANSLATE2_H
