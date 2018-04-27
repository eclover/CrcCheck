#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTextEdit;

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);

signals:

public slots:
    void btnCrc16Clicked();
    void btnCrcGBClicked();
    void btnFloatTo16Clicked();//浮点数转16进制
    void btn10To2Clicked();
    void btn10To8Clickd();
    void btn10To16Clicked();
    void btn2To10Clicked();
    void btn8To10Clicked();
    void btn16To10Clicked();
    void btnAsciiTo10Clicked();
    void btnAsciiTo16Clicked();
    void btn16ToFloatClicked();
    void btn16ToAsciiClicked();

private:
    QLineEdit *inputCrc16;
    QLineEdit *resultCrc16;
    QTextEdit *inputCrcGB;//国标校验输入
    QLineEdit *resultCrcGB;
    QLineEdit *inputFloat;//输入浮点数
    QLineEdit *resultFloat;//浮点数转换结果
    QLineEdit *input16;//输入16进制
    QLineEdit *result16;//16进制转换浮点数
    QLineEdit *inputConvert;//进制转换输入
    QLineEdit *resultConvert;//进制转换结果

    QPushButton *btn10To2;
    QPushButton *btn10To8;
    QPushButton *btn10To16;
    QPushButton *btn2To10;
    QPushButton *btn8To10;
    QPushButton *btn16To10;
    QPushButton *btnAsciiTo10;
    QPushButton *btnAsciiTo16;
    QPushButton *btn16ToAscii;

    QPushButton *btnCrc16;
    QPushButton *btnCrcGB;
    QPushButton *btnFloatTo16;//浮点数转16进制
    QPushButton *btn16ToFloat;//16进制转浮点数

public:
    int crc16LH(uchar *pBuf,int len);
    int crcChangTian(QByteArray *pBuf,int len);

};

#endif // WIDGET_H
