#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextDocument>
#include <QTextBrowser>
#include <QTextFormat>

#include "publicdef.h"

class TextBrowser : public QTextBrowser
{
public:
    TextBrowser(QWidget* parent = Q_NULLPTR);

    //整个文档发送，内部接收后读取自动拆分块显示
    void  sendMessage(QTextDocument *doc);
    //接收到消息
    void  recvMessage();

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    //添加消息
    void addMessage(MessageDef::Message msg);

    inline QTextFrameFormat::Position framePosition (MessageDef::MessageType msgType)const;
    inline Qt::Alignment textFormatAlignment(MessageDef::MessageType msgType) const;

    QTextTableFormat textTableFormat(MessageDef::MessageType msgType)const;

};

inline QTextFrameFormat::Position TextBrowser::framePosition(MessageDef::MessageType msgType)const{
    return msgType == MessageDef::MT_Send?QTextFrameFormat::FloatRight:QTextFrameFormat::FloatLeft;
}
inline Qt::Alignment TextBrowser::textFormatAlignment(MessageDef::MessageType msgType) const{
    return msgType== MessageDef::MT_Send?Qt::AlignRight:Qt::AlignLeft;
}

#endif // TEXTBROWSER_H
