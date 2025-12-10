#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>

class databasemanager : public QObject
{
    Q_OBJECT

public:
    explicit databasemanager(QObject *parent = nullptr);
    ~databasemanager();

    bool conectar();
    void desconectar();
    bool estaConectado() const;

private:
    class Impl;
    Impl *d;
};

#endif // DATABASEMANAGER_H
