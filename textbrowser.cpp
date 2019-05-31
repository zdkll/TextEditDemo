#include "textbrowser.h"

#include <QTextFrame>
#include <QTextBlock>
#include <QTextTable>
#include <QTextFormat>

#include <QDebug>

TextBrowser::TextBrowser(QWidget* parent)
    :QTextBrowser(parent)
{
    //从rootFrame 开始遍历
    textFrame = this->document()->rootFrame();
}

void TextBrowser::sendMessage(QTextDocument *doc)
{
    qDebug()<<"send message-----------------------";

    //一条消息Message_Frame-----------------------------
    QTextFrameFormat msg_all_tff;
    msg_all_tff.setBorder(1);
    msg_all_tff.setBottomMargin(20);
    msg_all_tff.setPosition(QTextFrameFormat::FloatRight);
    textFrame =  textFrame->lastCursorPosition().insertFrame(msg_all_tff);

    //时间textblock
    QTextBlockFormat time_tbf;
    time_tbf.setAlignment(Qt::AlignRight);
    time_tbf.setRightMargin(80);
    this->textCursor().insertBlock(time_tbf);
    QTextCharFormat time_tct;
    time_tct.setForeground(QColor("#c6c6c6"));
    this->textCursor().insertText(QStringLiteral("5月21日 13:54"),time_tct);


    //插入表格
    QTextTableFormat tableFormat;
    tableFormat.setColumnWidthConstraints(QVector<QTextLength>()
                                          <<QTextLength(QTextLength::FixedLength,100)
                                          <<QTextLength(QTextLength::FixedLength,40));
    tableFormat.setBorderBrush(Qt::red);
    tableFormat.setPosition(QTextFrameFormat::FloatRight);
    QTextTable *textTable = this->textCursor().insertTable(1,2,tableFormat);
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
    QTextCursor textCursor =  document()->rootFrame()->lastCursorPosition();

    //一条消息Message_Frame-----------------------------
    //tabCursor1.movePosition(QTextCursor::EndOfBlock);
    QTextFrameFormat msg_all_tff;
    msg_all_tff.setBottomMargin(20);
    msg_all_tff.setBorder(1);
    QTextLength textLength(QTextLength::VariableLength,240);
    msg_all_tff.setWidth(textLength);
    msg_all_tff.setBorderBrush(Qt::red);
    msg_all_tff.setPosition(QTextFrameFormat::FloatLeft);
    textCursor.insertFrame(msg_all_tff);

    //时间textblock
    QTextBlockFormat time_tbf;
    time_tbf.setAlignment(Qt::AlignLeft);
    time_tbf.setLeftMargin(80);
    textCursor.insertBlock(time_tbf);
    QTextCharFormat time_tct;
    time_tct.setForeground(QColor("#c6c6c6"));
    textCursor.insertText(QStringLiteral("5月21日 13:54"),time_tct);

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


