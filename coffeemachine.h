#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H
#include <QUdpSocket>
#include "order.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CoffeeMachine; }
QT_END_NAMESPACE

class CoffeeMachine : public QMainWindow
{
    Q_OBJECT

public:
    CoffeeMachine(QWidget *parent = nullptr);
    ~CoffeeMachine();
public slots:
    void readDatagram();
private slots:
    void on_pushButtonBuy_clicked();
    void on_pushButtonCheckCost_clicked();
signals:
    void tryToBuy();
private:
    void writeDatagram(QString data);
    QString getChoiceDrink();
    QString getChoiceSyrup();
    Ui::CoffeeMachine *ui;
    Order currentOrder;
    QUdpSocket* socket;

    const static QString BUY_COMMAND_HEADER;
    const static QString CHECK_COMMAND_HEADER;
    const static QString BUY_SUCCESS_COMMAND;
    const static QString BUY_FAILURE_COMMAND;
    const static quint16 TO_LISTEN_PORT = 8080; // порт на котором мы будем слушать чужие сообщения
    const static QHostAddress::SpecialAddress TO_LISTEN_IP = QHostAddress::LocalHost; // айпи на котором мы будем слушать чужие сообщения
    const static quint16 TO_SEND_PORT = 8090; // порт на который мы будем отправлять наши сообщения
    const static QHostAddress::SpecialAddress TO_SEND_IP = QHostAddress::LocalHost; // айпи на которое мы будем отправлять наши сообщения
};
#endif // COFFEEMACHINE_H
