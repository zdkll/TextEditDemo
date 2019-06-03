#ifndef PUBLICDEF_H
#define PUBLICDEF_H

#include <QTextFormat>

#define  IMAGE_NAME  QTextFormat::Property::UserProperty +1

#include <QString>

namespace  MessageDef{
//消息类型 - 发送还是接收
enum  MessageType{
    MT_Send,
    MT_Reciever
};
//消息数据类型
enum DataType
{
    DT_Text,
    DT_Img,
    DT_Voice
};


struct Message
{
    MessageType msgType;//相对于本地来说是发送还是接收
    long long  fromId; //发送用户Id
    long long  toId;//接收用户
    DataType dataType;//消息数据类型
    QString   dataId;//数据缓存Id

    //数据
    QString   data;
    QTextCharFormat format;//分段样式显示文本时候用，现在文本无样式（使用同一样式），故暂时用不上
};


//消息数据缓存
struct DataCache
{

};
}


#endif // PUBLICDEF_H
