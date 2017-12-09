#ifndef HEATMAP_H
#define HEATMAP_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>
#include <iostream>

struct Data{
    double latitude;
    double longitude;
    int total;
};

class HeatMap
{
public:
    HeatMap();
    void reset();
    QString getStr();
    void addData(QString jsonStr);
    std::vector<Data> data;
};

#endif // HEATMAP_H
