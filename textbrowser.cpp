#include "textbrowser.h"

#define MESSAGE_BOTTOM_MARGIN  40

#define PERSON_ICON_SIZE                                        48
#define MESSAGE_MINIMUM_HEIGHT                          PERSON_ICON_SIZE
#define MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT   68
#define MESSAGE_BOTTOM_MARGIN                          40

#include <QTextFrame>
#include <QTextBlock>
#include <QTextTable>
#include <QTextFormat>

#include <QDebug>

using namespace MessageDef;

TextBrowser::TextBrowser(QWidget* parent)
    :QTextBrowser(parent)
{

}

void TextBrowser::sendMessage(QTextDocument *doc)
{
    qDebug()<<"send message-----------------------";
    MessageDef::Message message;

    message.msgType = MT_Send;

    //解析消息文档，区分文字消息-图片消息(静态和动态图)-语音消息

    //构建文本TextFrame
    QTextFrame::iterator tf_it = doc->rootFrame()->begin();

    QTextBlock textBlock = tf_it.currentBlock();
    QList<MessageDef::Message>  msgList;
    //消息文本
    QString msg_text;
    if(textBlock.isValid()){
        QVector<QTextLayout::FormatRange> formatRanges =  textBlock.textFormats();
        for  (int i=0;i<formatRanges.size();i++) {
            qDebug()<<formatRanges.at(i).start<<formatRanges.at(i).length;
            if(formatRanges.at(i).format.isImageFormat())
            {
                qDebug()<<QStringLiteral("图片");
                message.dataType = DT_Img;
                message.data =  formatRanges.at(i).format.stringProperty(QTextFormat::ImageName);
                msgList.append(message);
                continue;
            }
            else if(formatRanges.at(i).format.isCharFormat())
            {
                msg_text += textBlock.text().mid(formatRanges.at(i).start,formatRanges.at(i).length);
                qDebug()<<QStringLiteral("文本:")+textBlock.text().mid(formatRanges.at(i).start,formatRanges.at(i).length);
            }
        }

        qDebug()<< textBlock.text();
    }

    //发送消息
    if(!msg_text.isEmpty()){
        message.dataType = DT_Text;
        message.data = msg_text;
        msgList.prepend(message);
    }

    for(int i=0;i<msgList.size();i++) {
        addMessage(msgList.at(i));
    }

    //模拟接收到响应消息
    recvMessage();
}


void TextBrowser::recvMessage()
{
    qDebug()<<"recv message-----------------------";

    Message message;
    message.msgType = MessageDef::MT_Reciever;
    message.dataType = MessageDef::DT_Text;
    message.data = QStringLiteral("收到消息");
    addMessage(message);

}

void TextBrowser::mousePressEvent(QMouseEvent *e)
{
    QTextBrowser::mousePressEvent(e);

    //确定当前片段
    QTextTable  *textTable =  textCursor().currentTable();
    if(textTable){
        qDebug()<<"current has table";
        qDebug()<< textTable->cellAt(textCursor()).column();
        //        if( textTable->cellAt(textCursor()).begin().currentBlock().)
    }
    else{
        qDebug()<<"current has  no table";
    }
}


void TextBrowser::addMessage(MessageDef::Message msg)
{
    QTextCursor textCursor =  document()->rootFrame()->lastCursorPosition();
    //添加消息 Frame---------
    QTextFrameFormat msg_all_tff;
    msg_all_tff.setBorder(1);
    msg_all_tff.setBorderBrush(msg.msgType == MT_Send?Qt::green:Qt::blue);
    msg_all_tff.setBottomMargin(MESSAGE_BOTTOM_MARGIN);
    msg_all_tff.setPosition(framePosition(msg.msgType));

    textCursor.insertFrame(msg_all_tff);


    //时间textblock----------
    QTextBlockFormat time_tbf;
    time_tbf.setAlignment(textFormatAlignment(msg.msgType));
    msg.msgType == MT_Send?time_tbf.setRightMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT)
                         :time_tbf.setLeftMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT);

    QTextCharFormat time_tct;
    time_tct.setForeground(QColor("#c6c6c6"));
    textCursor.insertBlock(time_tbf);
    textCursor.insertText(QStringLiteral("5月21日 13:54"));

    //TextTable-----------
    QTextTable *textTable = textCursor.insertTable(1,2,textTableFormat(msg.msgType));

    //消息头像
    QTextCursor msgTabCursor;
    if(msg.msgType == MessageDef::MT_Reciever)
        msgTabCursor = textTable->cellAt(0,0).firstCursorPosition();
    else
        msgTabCursor = textTable->cellAt(0,1).firstCursorPosition();
    QTextImageFormat header_ift;
    header_ift.setName(":/images/header.png");
    header_ift.setWidth(48);
    header_ift.setHeight(48);
    msgTabCursor.insertImage(header_ift);

    //消息内容
        QTextTableCellFormat cellFormat;
        cellFormat.setBackground(QColor("#00ffaa"));
        cellFormat.setForeground(Qt::black);

        cellFormat.setTopPadding(0);
    if(msg.msgType == MessageDef::MT_Reciever){
//        textTable->cellAt(0,1).setFormat(cellFormat);
                msgTabCursor = textTable->cellAt(0,1).firstCursorPosition();
    }
    else{
        msgTabCursor = textTable->cellAt(0,0).firstCursorPosition();

        QTextFrameFormat tft;

        //        textTable->cellAt(0,0).setFormat(cellFormat);
    }
    QTextBlockFormat bft;
    bft.setBackground(QColor("#00ffaa"));
    bft.setForeground(Qt::black);
    bft.setAlignment(Qt::AlignLeft|Qt::AlignTop);
    msgTabCursor.mergeBlockFormat(bft);


    //文本消息
    if(msg.dataType == DT_Text){
        msgTabCursor.insertText(msg.data);
    }
    //图片消息
    else  if(msg.dataType == DT_Img){
        QTextImageFormat ift;
        ift.setName(msg.data);
        ift.setWidth(240);
        ift.setHeight(120);
        msgTabCursor.insertImage(ift);
    };
}

QTextTableFormat TextBrowser::textTableFormat(MessageDef::MessageType msgType) const
{
    QTextTableFormat tableFormat;
    if(msgType == MessageDef::MT_Reciever)
        tableFormat.setColumnWidthConstraints(QVector<QTextLength>()
                                              <<QTextLength(QTextLength::FixedLength,40)
                                              <<QTextLength(QTextLength::FixedLength,100)
                                              );
    else
        tableFormat.setColumnWidthConstraints(QVector<QTextLength>()
                                              <<QTextLength(QTextLength::FixedLength,100)
                                              <<QTextLength(QTextLength::FixedLength,40)
                                              );

    tableFormat.setAlignment(textFormatAlignment(msgType));
    return tableFormat;
}

