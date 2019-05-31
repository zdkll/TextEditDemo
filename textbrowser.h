#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextDocument>
#include <QTextBrowser>

class TextBrowser : public QTextBrowser
{
public:
    //消息类型
    enum  MessageType{
        MT_Send,
        MT_Reciever
    };

    TextBrowser(QWidget* parent = Q_NULLPTR);

    //整个文档发送，内部接收后读取自动拆分块显示
    void  sendMessage(QTextDocument *doc);
    //接收到消息
    void  recvMessage();

private:
    //添加消息
    QTextFrame *addMessageFrame(MessageType msgType);

    //设置时间
    void insertMessageTime(QTextFrame *textFrame,MessageType msgType);


};

#endif // TEXTBROWSER_H
