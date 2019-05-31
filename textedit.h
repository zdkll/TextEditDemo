#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class TextEdit : public QTextEdit
{
public:
    TextEdit(QWidget *parent = Q_NULLPTR);

protected:
    //双击某些块，比如图片
    void mouseDoubleClickEvent(QMouseEvent *e);

};

#endif // TEXTEDIT_H
