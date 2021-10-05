#include "log.h"

Log::Log()
{
    qDebug() << QSqlDatabase::drivers();
}
