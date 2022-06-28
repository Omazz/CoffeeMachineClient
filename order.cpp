#include "order.h"

Order::Order() {

}

Order::Order(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  QString syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}

void Order::setOrder(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded,  QString syrup)
{
    this->drink = drink;
    this->sugarIsNeeded = sugarIsNeeded;
    this->milkIsNeeded = milkIsNeeded;
    this->cinnamonIsNeeded = cinnamonIsNeeded;
    this->syrup = syrup;
}


QString Order::getMessage()
{
    return this->drink +";" + boolToString(this->sugarIsNeeded) + ";" + boolToString(this->milkIsNeeded) + ";" + boolToString(this->cinnamonIsNeeded) + ";" + this->syrup;
}

QString Order:: boolToString(bool flag)
{
    return flag ? "1" : "0";
}
