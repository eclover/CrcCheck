#include "widget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include <QDebug>


Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowIcon(QIcon(":/icon.ico"));
    inputCrc16 = new QLineEdit;
    resultCrc16 = new QLineEdit;
    inputCrcGB = new QTextEdit;
    resultCrcGB = new QLineEdit;
    inputFloat = new QLineEdit;
    resultFloat = new QLineEdit;
    inputConvert = new QLineEdit;
    resultConvert = new QLineEdit;
    input16 = new QLineEdit;
    result16 = new QLineEdit;
    inputCrcGB->setMaximumHeight(150);

    btn10To2 = new QPushButton(tr("10进制转2进制"));
    btn10To8 = new QPushButton(tr("10进制转8进制"));
    btn10To16 = new QPushButton(tr("10进制转16进制"));
    btn2To10 = new QPushButton(tr("2进制转10进制"));
    btn8To10 = new QPushButton(tr("8进制转10进制"));
    btn16To10 = new QPushButton(tr("16进制转10进制"));
    btnAsciiTo10 = new QPushButton(tr("Ascii转10进制"));
    btnAsciiTo16 = new QPushButton(tr("Ascii转16进制"));
    btn16ToAscii = new QPushButton(tr("16进制转Ascii"));
    btnFloatTo16 = new QPushButton(tr("浮点数据转16进制"));
    btn16ToFloat = new QPushButton(tr("16进制转浮点数"));
    btnCrc16 = new QPushButton(tr("Crc16校验结果"));
    btnCrcGB = new QPushButton(tr("国标校验结果"));

    QGridLayout *mainLayout = new QGridLayout;
    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(tr("Crc16校验："),inputCrc16);
    layout1->addRow(tr("Crc16结果："),resultCrc16);
    mainLayout->addLayout(layout1,0,0,2,4);
    mainLayout->addWidget(btnCrc16,0,4);


    QFormLayout *layout2 = new QFormLayout;
    layout2->addRow(tr("国标数据包："),inputCrcGB);
    layout2->addRow(tr("国标校验码："),resultCrcGB);
    mainLayout->addLayout(layout2,2,0,2,4);
    mainLayout->addWidget(btnCrcGB,2,4);

    mainLayout->addWidget(btnFloatTo16,4,0);
    mainLayout->addWidget(btn16ToFloat,4,1);
    mainLayout->addWidget(btn10To2,4,2);
    mainLayout->addWidget(btn10To8,4,3);
    mainLayout->addWidget(btn10To16,5,0);
    mainLayout->addWidget(btn2To10,5,1);
    mainLayout->addWidget(btn8To10,5,2);
    mainLayout->addWidget(btn16To10,5,3);
    mainLayout->addWidget(btnAsciiTo10,6,0);
    mainLayout->addWidget(btnAsciiTo16,6,1);
    mainLayout->addWidget(btn16ToAscii,6,2);

    QFormLayout *layout3 = new QFormLayout;
    layout3->addRow(tr("转换字符："),inputConvert);
    layout3->addRow(tr("转换结果："),resultConvert);

    mainLayout->addLayout(layout3,7,0,2,4);
    setWindowTitle(tr("转换小工具"));
    setFixedSize(600,400);
    setLayout(mainLayout);

    connect(btnCrc16,&QPushButton::clicked,this,&Widget::btnCrc16Clicked);
    connect(btnCrcGB,&QPushButton::clicked,this,&Widget::btnCrcGBClicked);
    connect(btnFloatTo16,&QPushButton::clicked,this,&Widget::btnFloatTo16Clicked);
    connect(btn10To2,&QPushButton::clicked,this,&Widget::btn10To2Clicked);
    connect(btn10To8,&QPushButton::clicked,this,&Widget::btn10To8Clickd);
    connect(btn10To16,&QPushButton::clicked,this,&Widget::btn10To16Clicked);
    connect(btn2To10,&QPushButton::clicked,this,&Widget::btn2To10Clicked);
    connect(btn8To10,&QPushButton::clicked,this,&Widget::btn8To10Clicked);
    connect(btn16To10,&QPushButton::clicked,this,&Widget::btn16To10Clicked);
    connect(btnAsciiTo10,&QPushButton::clicked,this,&Widget::btnAsciiTo10Clicked);
    connect(btnAsciiTo16,&QPushButton::clicked,this,&Widget::btnAsciiTo16Clicked);
    connect(btn16ToFloat,&QPushButton::clicked,this,&Widget::btn16ToFloatClicked);
    connect(btn16ToAscii,&QPushButton::clicked,this,&Widget::btn16ToAsciiClicked);
}

void Widget::btnCrc16Clicked()
{
    QString strData = inputCrc16->text();
    QByteArray byteData = QByteArray::fromHex(strData.toLatin1().data());//按16进制接收文本

    int length = byteData.size();
    int nCRC = crc16LH((uchar*)byteData.data(),length);
    int hi = (nCRC & 0xFF00)>>8;
    int lo = nCRC & 0xFF;

    resultCrc16->setText(tr("%1%2").arg(hi,2,16,QLatin1Char('0')).toUpper()
                         .arg( lo,2,16,QLatin1Char('0')).toUpper());//自动补0


}

void Widget::btnCrcGBClicked()
{
    QString strData = inputCrcGB->toPlainText();

    QByteArray byteData = strData.toLatin1();
    int nCRC = crcChangTian(&byteData,strData.count());
    int hi = (nCRC & 0xFF00)>>8;
    int lo = nCRC & 0xFF;

     resultCrcGB->setText(tr("%1%2").arg(hi,2,16,QLatin1Char('0')).toUpper()
                          .arg( lo,2,16,QLatin1Char('0')).toUpper());//自动补0
}

//浮点数转16进制
void Widget::btnFloatTo16Clicked()
{
    float value = inputConvert->text().toFloat();
    long val = *(long*)&value;
    QString strData = QString::number(val,16).toUpper();
    resultConvert->setText(strData);

}

void Widget::btn10To2Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    strData = QString::number(strData.toInt(),2);
    resultConvert->setText(strData);

}

void Widget::btn10To8Clickd()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    strData = QString::number(strData.toInt(),8);
    resultConvert->setText(strData);
}

void Widget::btn10To16Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    strData = QString::number(strData.toInt(),16);
    resultConvert->setText(strData);
}

void Widget::btn2To10Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    bool ok;
    int hex = strData.toInt(&ok,2);
    if(ok){
        strData = QString::number(hex);
        resultConvert->setText(strData);
    }
    else{
        QMessageBox::warning(this,tr("提示"),tr("输入有误，转换失败,请重新输入"),QMessageBox::Yes);
    }

}

void Widget::btn8To10Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    bool ok;
    int data = strData.toInt(&ok,8);
    if(ok){
        strData = QString::number(data);
        resultConvert->setText(strData);
    }
    else{
        QMessageBox::warning(this,tr("提示"),tr("输入有误，转换失败,请重新输入"),QMessageBox::Yes);
    }
}

void Widget::btn16To10Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    bool ok;
    int hex = strData.toInt(&ok,16);
    if(ok){
        strData = QString::number(hex);
        resultConvert->setText(strData);
    }
    else{
        QMessageBox::warning(this,tr("提示"),tr("输入有误，转换失败,请重新输入"),QMessageBox::Yes);

    }

}

void Widget::btnAsciiTo10Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    QString data;
    for(int i=0;i<strData.length();i++){
        QString str = strData.at(i);
        QByteArray byte = str.toLatin1().toHex();
        str = QString(byte).toUpper();
        int dec = str.toInt(0,16);
        str = QString::number(dec);
        data.append(str);
        data.append(" ");
    }
    resultConvert->setText(data);
}

//Ascii 码转16进制
void Widget::btnAsciiTo16Clicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString strData =list.join("");
    QString data;
    for(int i=0;i<strData.length();i++){
        QString str = strData.at(i);
        QByteArray byte = str.toLatin1();
        data.append(byte.toHex());
        data.append(" ");
    }
    resultConvert->setText(data);
}
//16进制转浮点数
void Widget::btn16ToFloatClicked()
{
    QStringList list = inputConvert->text().split(" ");
    QString data =list.join("");
    int hex = data.toInt(0,16);
    float value = *(float*)&hex;

    data = QString::number(value,10,6);
    resultConvert->setText(data);
}

void Widget::btn16ToAsciiClicked()
{
    QString strData = inputConvert->text();
    int hex = strData.toInt(0,16);

    char ch = hex;

    QString str_ascii = QString(ch);
    resultConvert->setText(str_ascii);
}

//Modbus校验
int Widget::crc16LH(uchar *pBuf, int len)
{
    int nCRC = 0xFFFF;
    uchar hi,lo;
    for(int pos = 0;pos < len;pos++){
        nCRC ^= (int)pBuf[pos];
        for(int bitidex = 0;bitidex < 8;bitidex++){
            if(nCRC & 1){
                nCRC >>= 1;
                nCRC ^= 0xA001;
            }
            else{
                nCRC >>= 1;
            }
        }
    }
    hi = (nCRC%256);
    lo = nCRC/256;
    nCRC = hi << 8|lo;
    return nCRC;
}

//国标校验
int Widget::crcChangTian(QByteArray *pBuf, int len)
{
    uint crc_reg = 0xFFFF,check;

    uchar *chData = new uchar[len];
    chData = (uchar *)pBuf->data();
    int ruler = 0xA001;

    for(int i=0;i<len;i++){
        crc_reg = (crc_reg >> 8)^chData[i];
        for(int j=0;j<8;j++){
            check = crc_reg & 0x0001;
            crc_reg >>= 1;
            if(check == 0x0001){
                crc_reg ^= ruler;
            }
        }
    }
    return crc_reg;
}


