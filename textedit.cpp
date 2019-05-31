#include "textedit.h"

#include <QTextBlock>
#include <QTextFragment>
#include <QTextCursor>
#include <QDebug>

TextEdit::TextEdit(QWidget *parent)
    :QTextEdit(parent)
{

}

void TextEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
    QTextEdit::mouseDoubleClickEvent(e);

    QTextCursor cursor = textCursor();

    QTextBlock textBlock = cursor.block();

    qDebug()<<cursor.positionInBlock()
           <<cursor.position()
          <<textBlock.position();

    QTextImageFormat imageFormat =  cursor.charFormat().toImageFormat();
    if(imageFormat.isValid()){
        cursor.clearSelection();
        qDebug()<<"Image url:"<< imageFormat.stringProperty(1);
    }
    return;
    //查找图片
    QTextBlock::iterator it;
    for (it = textBlock.begin(); !(it.atEnd()); ++it) {
        QTextFragment currentFragment = it.fragment();
        qDebug()<< currentFragment.position()
                <<currentFragment.text().isSimpleText()
               <<currentFragment.contains(10)
              <<currentFragment.length();
        if (currentFragment.isValid()){

            QTextImageFormat imageFormat = currentFragment.charFormat().toImageFormat();
            if(imageFormat.isValid()){
                qDebug()<<"Image url:"<< imageFormat.stringProperty(1);
            }
        }
    }

}
