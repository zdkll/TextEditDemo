#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextDocument>
#include <QTextBrowser>
#include <QTextFormat>

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
    void addMessage(MessageType msgType);

    inline QTextFrameFormat::Position framePosition (MessageType msgType)const;
    inline Qt::Alignment textFormatAlignment(MessageType msgType) const;

    QTextTableFormat textTableFormat(MessageType msgType)const;

};

inline QTextFrameFormat::Position TextBrowser::framePosition(TextBrowser::MessageType msgType)const{
    return msgType == TextBrowser::MT_Send?QTextFrameFormat::FloatRight:QTextFrameFormat::FloatLeft;
}
inline Qt::Alignment TextBrowser::textFormatAlignment(TextBrowser::MessageType msgType) const{
    return msgType== TextBrowser::MT_Send?Qt::AlignRight:Qt::AlignLeft;
}

#endif // TEXTBROWSER_H
