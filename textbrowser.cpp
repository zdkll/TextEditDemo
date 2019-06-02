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

TextBrowser::TextBrowser(QWidget* parent)
    :QTextBrowser(parent)
{

}

void TextBrowser::sendMessage(QTextDocument *doc)
{
    qDebug()<<"send message-----------------------";

    //解析消息文档，区分文字消息-图片消息(静态和动态图)-语音消息

    //构建文本TextFrame
  QTextFrame::iterator tf_it = doc->rootFrame()->begin();
    for (; !(tf_it.atEnd()); ++tf_it) {
        QTextBlock textBlock = tf_it.currentBlock();

        if(textBlock.isValid()){
            QVector<QTextLayout::FormatRange> formatRanges =  textBlock.textFormats();
            for  (int i=0;i<formatRanges.size();i++) {
                qDebug()<<formatRanges.at(i).start<<formatRanges.at(i).length;
            }

            qDebug()<< textBlock.text();

        }

    }

    addMessage(MT_Send);


    //模拟接收到响应消息
    recvMessage();
}


void TextBrowser::recvMessage()
{
    qDebug()<<"recv message-----------------------";
    addMessage(MT_Reciever);

}


void TextBrowser::addMessage(TextBrowser::MessageType msgType)
{
    QTextCursor textCursor =  document()->rootFrame()->lastCursorPosition();
    //添加消息 Frame---------
    QTextFrameFormat msg_all_tff;
    msg_all_tff.setBorder(1);
    msg_all_tff.setBorderBrush(msgType == MT_Send?Qt::green:Qt::blue);
    msg_all_tff.setBottomMargin(MESSAGE_BOTTOM_MARGIN);
    msg_all_tff.setPosition(framePosition(msgType));

    textCursor.insertFrame(msg_all_tff);


    //时间textblock----------
    QTextBlockFormat time_tbf;
    time_tbf.setAlignment(textFormatAlignment(msgType));
    msgType == MT_Send?time_tbf.setRightMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT)
                     :time_tbf.setLeftMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT);

    QTextCharFormat time_tct;
    time_tct.setForeground(QColor("#c6c6c6"));
    textCursor.insertBlock(time_tbf);
    textCursor.insertText(QStringLiteral("5月21日 13:54"));

    //TextTable-----------
    QTextTable *textTable = textCursor.insertTable(1,2,textTableFormat(msgType));
    QTextCursor msgTabCursor;
    if(msgType == MT_Reciever)
        msgTabCursor = textTable->cellAt(0,0).firstCursorPosition();
    else
        msgTabCursor = textTable->cellAt(0,1).firstCursorPosition();

    QTextImageFormat header_ift;
    header_ift.setName(":/images/header.png");
    header_ift.setWidth(48);
    header_ift.setHeight(48);
    msgTabCursor.insertImage(header_ift);

    if(msgType == MT_Reciever)
        msgTabCursor = textTable->cellAt(0,1).firstCursorPosition();
    else
        msgTabCursor = textTable->cellAt(0,0).firstCursorPosition();
    QTextCharFormat tab_cft;
    tab_cft.setBackground(Qt::blue);
    tab_cft.setForeground(Qt::red);
    msgTabCursor.insertText(QStringLiteral("收到的信息"),tab_cft);

}

QTextTableFormat TextBrowser::textTableFormat(MessageType msgType) const
{
    QTextTableFormat tableFormat;
    if(msgType == MT_Reciever)
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

