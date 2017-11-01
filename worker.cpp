#include "worker.h"

worker::worker(QObject *parent) : QObject(parent)
{

}

void worker::sendMail(QString server, int port, QString username, QString password, QString recipient, QString subject, QString message)
{
    Smtp* smtp = new Smtp(username, password, server, port);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    message = readMessage(message);
    if (!message.isEmpty()) {
        smtp->sendMail(username, recipient, subject, message);
    } else {
        emit close();
    }
}

void worker::mailSent(QString status)
{
    if (status == "Message sent") {
        printf("{\"SUCCESS\": \"Message sent\"}\n\n");
    } else {
        printf("{\"ERR\": \"%s\"}\n\n", status.toUtf8().data());
    }
    emit close();
    return;
}

QString worker::readMessage(QString path)
{
    QFile file(path);
    if (file.open(QIODevice::ReadWrite)) {
        QString readFile = file.readAll();
        return readFile;
    } else {
        printf("{\"ERR\": \"Cannot open message file\"}\n\n");
        emit close();
    }
    return "";
}
