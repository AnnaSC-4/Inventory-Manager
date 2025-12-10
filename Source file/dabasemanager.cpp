#include "databasemanager.h"
#include <QDebug>

// Implementación privada (PIMPL)
class databasemanager::Impl
{
public:
    bool conectado = false;
};

databasemanager::databasemanager(QObject *parent)
    : QObject(parent)
    , d(new Impl)
{
}

databasemanager::~databasemanager()
{
    delete d;
}

bool databasemanager::conectar()
{
    d->conectado = true;
    qDebug() << "Base de datos conectada (simulada)";
    return true;
}

void databasemanager::desconectar()
{
    d->conectado = false;
    qDebug() << "Base de datos desconectada";
}

bool databasemanager::estaConectado() const
{
    return d->conectado;
}
