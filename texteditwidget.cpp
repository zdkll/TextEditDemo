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

    textCursor.insertText(QStringLiteral("这是颜色字段"));

    textColorChanged(Qt::red);

    textCursor.insertText(QStringLiteral("这是颜色字段"));

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
    textBrowser->textCursor().insertText(textEdit->document()->toPlainText());
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
