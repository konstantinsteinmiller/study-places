#include "heatmap.h"

HeatMap::HeatMap()
{

}

void HeatMap::reset()
{
    data.clear();
    data.shrink_to_fit();
}

QString HeatMap::getStr()
{
    return "{}";
}

void HeatMap::addData(QString jsonStr)
{
    QJsonDocument doc=QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject obj=doc.object();
    Data d;
    d.latitude=obj["latitude"].toDouble();
    d.longitude=obj["longitude"].toDouble();
    d.total=obj["total"].toInt();
    std::cout<<"got package: latitude="<<d.latitude<<" longtitude="<<d.longitude<<" total="<<d.total<<std::endl;
    data.push_back(d);
}
