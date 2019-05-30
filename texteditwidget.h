#ifndef TEXTEDITWIDGET_H
#define TEXTEDITWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTextBrowser>
#include <QPushButton>

#include <textbrowser.h>
#include <textedit.h>

namespace Ui {
class TextEditWidget;
}

class TextEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextEditWidget(QWidget *parent = 0);
    ~TextEditWidget();

    void textColorChanged(const QColor& color);
    void textBold(bool bold);
    void textUnderline(bool underline);
    void textItalic(bool italic);
    void textFamily(const QString &f);
    void textSize(const QString &p);

private slots:
    void sendMessage();

private:
    Ui::TextEditWidget *ui;

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void initWidget();

    TextEdit  *textEdit;
    TextBrowser *textBrowser;
    QPushButton   *sendButton;
};

#endif // TEXTEDITWIDGET_H
