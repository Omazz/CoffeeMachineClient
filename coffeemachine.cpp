#include "coffeemachine.h"
#include "ui_coffeemachine.h"

#include <QMessageBox>

const QString CoffeeMachine:: BUY_COMMAND_HEADER = (QString) "BUY";
const QString CoffeeMachine:: CHECK_COMMAND_HEADER = (QString) "CHECK";
const QString CoffeeMachine:: BUY_SUCCESS_COMMAND = (QString) "SUCCESS";
const QString CoffeeMachine:: BUY_FAILURE_COMMAND = (QString) "FAILURE";

CoffeeMachine::CoffeeMachine(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CoffeeMachine)
    , currentOrder()
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(TO_LISTEN_IP, TO_LISTEN_PORT);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readDatagram()));
}

CoffeeMachine::~CoffeeMachine()
{
    delete ui;
}


void CoffeeMachine::on_pushButtonBuy_clicked()
{
    QString drink = getChoiceDrink();
    bool sugarIsNeeded = ui->checkBoxSugar->isChecked();
    bool milkIsNeeded = ui->checkBoxMilk->isChecked();
    bool cinnamonIsNeeded = ui->checkBoxCinnamon->isChecked();
    QString syrup = getChoiceSyrup();
    if(drink != nullptr && syrup != nullptr) {
        currentOrder.setOrder(drink, sugarIsNeeded, milkIsNeeded, cinnamonIsNeeded, syrup);
        writeDatagram(BUY_COMMAND_HEADER + ";" + currentOrder.getMessage());
    }
}

QString CoffeeMachine:: getChoiceDrink()
{
    if(ui->radioButtonAmericano->isChecked()) {
        return "Americano";
    } else if(ui->radioButtonCapuccino->isChecked()) {
        return "Capuccino";
    } else if(ui->radioButtonLatte->isChecked()) {
        return "Latte";
    } else if(ui->radioButtonEspresso->isChecked()) {
        return "Espresso";
    } else if(ui->radioButtonDoubleEspresso->isChecked()) {
        return "Double espresso";
    } else if(ui->radioButtonCacao->isChecked()) {
        return "Cacao";
    } else if(ui->radioButtonHotChocolate->isChecked()) {
        return "Hot chocolate";
    } else if(ui->radioButtonFlatwhite->isChecked()) {
        return "Flatwhite";
    }
    return nullptr;
}

QString CoffeeMachine:: getChoiceSyrup()
{
    if(ui->radioButtonStrawnerry->isChecked()) {
        return "Strawberry";
    } else if(ui->radioButtonCaramel->isChecked()) {
        return "Caramel";
    } else if(ui->radioButtonBanana->isChecked()) {
        return "Banana";
    } else if(ui->radioButtonGrape->isChecked()) {
        return "Grape";
    } else if(ui->radioButtonVanila->isChecked()) {
        return "Vanila";
    } else if(ui->radioButtonTangerine->isChecked()) {
        return "Tangerine";
    } else if(ui->radioButtonWithoutSyrup->isChecked()) {
        return "Without syrup";
    }

    return nullptr;
}

void CoffeeMachine::on_pushButtonCheckCost_clicked()
{
    QString drink = getChoiceDrink();
    bool sugarIsNeeded = ui->checkBoxSugar->isChecked();
    bool milkIsNeeded = ui->checkBoxMilk->isChecked();
    bool cinnamonIsNeeded = ui->checkBoxCinnamon->isChecked();
    QString syrup = getChoiceSyrup();
    if(drink != nullptr && syrup != nullptr) {
        currentOrder.setOrder(drink, sugarIsNeeded, milkIsNeeded, cinnamonIsNeeded, syrup);
        writeDatagram(CHECK_COMMAND_HEADER + ";" + currentOrder.getMessage());
    }
}

void CoffeeMachine:: writeDatagram(QString data)
{
    socket->writeDatagram(data.toUtf8(), TO_SEND_IP, TO_SEND_PORT);
}

void CoffeeMachine:: readDatagram()
{
    QHostAddress sender;
    quint16 senderPort;
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString data = datagram.data();
        qDebug() << data;
        QStringList stringList = data.split(";");
        if(stringList.at(0) == BUY_COMMAND_HEADER) {
            if(stringList.at(1) == "SUCCESS") {
                QMessageBox::information(this, "Result of request", "Order is accepted");
            } else if(stringList.at(1) == "FAILURE") {

                QMessageBox::information(this, "Result of request", "Order is denied");
            }
        } else if(stringList.at(0) == CHECK_COMMAND_HEADER) {
            QString result = "Total cost is " + stringList.at(1);
            QMessageBox::information(this, "Result of request", result);
        }

    }
}

