#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextDocument>
#include <QTextBrowser>

class TextBrowser : public QTextBrowser
{
public:
    TextBrowser(QWidget* parent = Q_NULLPTR);

    //整个文档发送，内部接收后读取自动拆分块显示
    void  sendMessage(QTextDocument *doc);

    //接收到消息
    void  recvMessage();

private:
    QTextFrame *textFrame;
};

#endif // TEXTBROWSER_H
