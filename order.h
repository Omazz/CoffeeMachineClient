#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Order
{
public:
    Order();
    Order(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded, QString syrup);
    void setOrder(QString drink, bool sugarIsNeeded, bool milkIsNeeded, bool cinnamonIsNeeded, QString syrup);
    QString getMessage(void);
private:
    QString boolToString(bool flag);
    QString drink;
    bool sugarIsNeeded;
    bool milkIsNeeded;
    bool cinnamonIsNeeded;
    QString syrup;
};

#endif // ORDER_H
