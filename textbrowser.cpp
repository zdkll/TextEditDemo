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

    //一条消息Message_Frame-----------------------------
    QTextFrame *textFrame = addMessageFrame(MT_Send);
    QTextCursor textCursor = textFrame->firstCursorPosition();

    //时间
    insertMessageTime(textFrame,MT_Send);

    //插入表格
    QTextTableFormat tableFormat;
    tableFormat.setColumnWidthConstraints(QVector<QTextLength>()
                                          <<QTextLength(QTextLength::FixedLength,100)
                                          <<QTextLength(QTextLength::FixedLength,40));
    tableFormat.setBorderBrush(Qt::red);
    tableFormat.setPosition(QTextFrameFormat::FloatRight);
    QTextTable *textTable = textCursor.insertTable(1,2,tableFormat);
    QTextCursor tabCursor1 = textTable->cellAt(0,0).firstCursorPosition();

    QTextCharFormat tab_cft;
    tab_cft.setBackground(Qt::blue);
    tab_cft.setForeground(Qt::red);

    tabCursor1.insertText(QStringLiteral("收到的信息"),tab_cft);
    tabCursor1.movePosition(QTextCursor::NextCell);

    QTextImageFormat header_ift;
    header_ift.setName("C:/Users/Administrator/Desktop/pics/person.png");
    header_ift.setWidth(48);
    header_ift.setHeight(48);
    tabCursor1.insertImage(header_ift);

    //    //构建文本TextFrame
    //    for (; !(tf_it.atEnd()); ++tf_it) {
    //        QTextBlock textBlock = tf_it.currentBlock();

    //        if(textBlock.isValid()){
    //            QVector<QTextLayout::FormatRange> formatRanges =  textBlock.textFormats();
    //            for  (int i=0;i<formatRanges.size();i++) {
    //                qDebug()<<formatRanges.at(i).start<<formatRanges.at(i).length;
    //            }

    //            qDebug()<< textBlock.text();

    //        }

    //    }


    //模拟接收到响应消息
    recvMessage();
}


void TextBrowser::recvMessage()
{
    qDebug()<<"recv message-----------------------";

    //一条消息Message_Frame-----------------------------
    QTextFrame *textFrame = addMessageFrame(MT_Reciever);
    QTextCursor textCursor = textFrame->firstCursorPosition();

    //时间
    insertMessageTime(textFrame,MT_Reciever);

    //插入表格
    QTextTableFormat tableFormat;
    tableFormat.setColumnWidthConstraints(QVector<QTextLength>()
                                          <<QTextLength(QTextLength::FixedLength,40)
                                          <<QTextLength(QTextLength::FixedLength,100)
                                          );
    tableFormat.setBorderBrush(Qt::red);
    tableFormat.setPosition(QTextFrameFormat::FloatLeft);
    QTextTable *textTable = textCursor.insertTable(1,2,tableFormat);
    QTextCursor tabCursor1 = textTable->cellAt(0,0).firstCursorPosition();

    QTextImageFormat header_ift;
    header_ift.setName("C:/Users/Administrator/Desktop/pics/person.png");
    header_ift.setWidth(48);
    header_ift.setHeight(48);
    tabCursor1.insertImage(header_ift);
    tabCursor1.movePosition(QTextCursor::NextCell);

    QTextCharFormat tab_cft;
    tab_cft.setBackground(Qt::blue);
    tab_cft.setForeground(Qt::red);
    tabCursor1.insertText(QStringLiteral("收到的信息"),tab_cft);

}


QTextFrame *TextBrowser::addMessageFrame(TextBrowser::MessageType msgType)
{
    QTextCursor textCursor =  document()->rootFrame()->lastCursorPosition();

    QTextFrameFormat msg_all_tff;
    msg_all_tff.setBorder(1);
    msg_all_tff.setBorderBrush(msgType == MT_Send?Qt::green:Qt::blue);
    msg_all_tff.setBottomMargin(MESSAGE_BOTTOM_MARGIN);
    msg_all_tff.setPosition(msgType == MT_Send?QTextFrameFormat::FloatRight:QTextFrameFormat::FloatLeft);

    return textCursor.insertFrame(msg_all_tff);
}

void TextBrowser::insertMessageTime(QTextFrame *textFrame,MessageType msgType)
{
    QTextCursor textCursor = textFrame->lastCursorPosition();
    //时间textblock
    QTextBlockFormat time_tbf;
    time_tbf.setAlignment(msgType == MT_Send?Qt::AlignRight:Qt::AlignLeft);
    msgType == MT_Send?time_tbf.setRightMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT)
                     :time_tbf.setLeftMargin(MESSAGE_TEXT_MARGIN_LEFT_OR_RIGHT);

    QTextCharFormat time_tct;
    time_tct.setForeground(QColor("#c6c6c6"));
    textCursor.insertBlock(time_tbf);
    textCursor.insertText(QStringLiteral("5月21日 13:54"));
}


