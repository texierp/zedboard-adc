#include <QCoreApplication>
#include <QDebug>
#include <QFile>



QByteArray readValueFromFile(QString filePath)
{
    QByteArray data;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        data = file.readAll();
        data.remove(data.length() - 1, 1);
        file.close();
    }

    return data;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QByteArray rawTemp = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp0_raw");
    QByteArray scaleTemp = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp0_scale");
    QByteArray offsetTemp = readValueFromFile("/sys/bus/iio/devices/iio\:device0/in_temp0_offset");

    quint32 rawOffset = rawTemp.toInt() - offsetTemp.toInt();

    float temp = rawOffset / scaleTemp.toFloat();

    qDebug() << temp <<"deg";

    return 0;
}

