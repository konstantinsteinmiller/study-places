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
    QString heatMapStr="{\"map\":[";
    if(data.size()>0)
    {
        unsigned int i=0;
        for(i;i<data.size()-1;i++)
        {
            heatMapStr+="[{\"latitude\":"+QString::number(data.at(i).latitude)+",\"longitude\":"+
                        QString::number(data.at(0).longitude)+",\"total\":"+QString::number(data.at(i).total)+"}],";
        }
        heatMapStr+="[{\"latitude\":"+QString::number(data.at(i).latitude)+",\"longitude\":"+
                    QString::number(data.at(i).longitude)+",\"total\":"+QString::number(data.at(i).total)+"}]]}";
        return heatMapStr;
    }
    else
    {
        heatMapStr+="]}";
    }
    return heatMapStr;
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
