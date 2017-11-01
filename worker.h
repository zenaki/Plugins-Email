#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QFile>

#include "smtp.h"

class worker : public QObject
{
    Q_OBJECT

public:
    explicit worker(QObject *parent = 0);

    void sendMail(QString server, int port, QString username, QString password, QString recipient, QString subject, QString message);
    QString readMessage(QString path);

signals:
    void close();

private slots:
    void mailSent(QString status);
};

#endif // WORKER_H
