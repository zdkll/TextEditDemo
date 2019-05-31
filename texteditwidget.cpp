#include "texteditwidget.h"
#include "ui_texteditwidget.h"

#include <QSplitter>

#include <QSplashScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QBoxLayout>

#include <QTextDocument>
#include <QTextCursor>

#include <QTextFrameFormat>
#include <QTextBlockFormat>
#include <QTextCharFormat>
#include <QTextTableFormat>
#include <QTextImageFormat>
#include <QTextTableCellFormat>

#include <QTextFrame>
#include <QTextFragment>
#include <QTextBlock>
#include <QTextTable>
#include <QTextList>
#include <QTextTableCell>
#include <QTextLine>

#include <QTextDocumentWriter>

#include <QDebug>

TextEditWidget::TextEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextEditWidget)
{
    ui->setupUi(this);

    initWidget();

    QTextCursor textCursor = textEdit->textCursor();
    QTextFrame *rootFrame=   textEdit->document()->rootFrame();

    //插入文本块
    QTextBlockFormat bft;
    bft.setAlignment(Qt::AlignLeft);
    bft.setTopMargin(10);
    bft.setBackground(Qt::green);
    bft.setForeground(Qt::red);

    QTextCharFormat cft;
    cft.setForeground(Qt::red);
    //textCursor.insertBlock(bft,cft);
    textCursor.setBlockFormat(bft);
    textCursor.setBlockCharFormat(cft);
    textCursor.insertText(QStringLiteral("Block 文字"));

    //插入图片
    QTextImageFormat imageFormat;
    imageFormat.setName("C:/Users/Administrator/Desktop/pics/dingding.png");
    imageFormat.setWidth(200);
    imageFormat.setProperty(1,QString("C:/Users/Administrator/Desktop/pics/dingding.png"));
    // ui->textEdit->textCursor().insertImage(imageFormat);
    textCursor.insertImage(imageFormat);
    qDebug()<<textCursor.blockNumber();

    textCursor.insertText(QStringLiteral(" 这是颜色字段"));

    textCursor.insertBlock();
    textCursor.insertText("block 1");

    QTextDocumentWriter writer("D:/files/test1.html");
    writer.write(textEdit->document());
}

TextEditWidget::~TextEditWidget()
{
    delete ui;
}

void TextEditWidget::textColorChanged(const QColor &color)
{
    QTextCharFormat fmt;
    fmt.setForeground(color);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEditWidget::textBold(bool bold)
{

}

void TextEditWidget::textUnderline(bool underline)
{

}

void TextEditWidget::textItalic(bool italic)
{

}

void TextEditWidget::textFamily(const QString &f)
{

}

void TextEditWidget::textSize(const QString &p)
{

}

void TextEditWidget::sendMessage()
{
    textBrowser->sendMessage(textEdit->document());
    textEdit->document()->clear();
}

void TextEditWidget::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);

}

void TextEditWidget::initWidget()
{
    QSplitter *splitter = new QSplitter(Qt::Vertical,this);
    textBrowser = new TextBrowser(this);
    splitter->addWidget(textBrowser);

    textEdit = new TextEdit(this);
    splitter->addWidget(textEdit);

    splitter->setStretchFactor(0,1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(splitter);

    sendButton = new QPushButton(QStringLiteral("发送"),this);
    mainLayout->addWidget(sendButton,0,Qt::AlignRight|Qt::AlignVCenter);

    const QRect rect = QApplication::desktop()->availableGeometry();

    this->resize(rect.width()/2,rect.height()*2/3);

    this->move((rect.width()-this->width())/2,(rect.height()-this->height())/2);

    connect(sendButton,SIGNAL(clicked(bool)),this,SLOT(sendMessage()));
}
