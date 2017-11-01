#include <QCoreApplication>
#include <QTimer>

#include "worker.h"

#define VERSION "0.1 beta"

QStringList processArgs(int argc, char **argv)
{
    bool err = false;
    QStringList result;
    if (argc < 2) {
        printf(" -h  / --help\t\t\t\t: Print this help info\n\n"
               " -mf / --message-file MESSAGE_FILE\t: Message(file) for Recipient\n\n"
               " -pr / --port SERVER_PORT\t\t: Server Port for Email\n\n"
               " -pw / --password EMAIL_PASSSWORD\t: Password for Sender\n\n"
               " -re / --recipient EMAIL_ADDRESS\t: Recipient Email Address\n\n"
               " -sd / --sender EMAIL_ADDRESS\t\t: Sender Email Address\n\n"
               " -su / --subject SUBJECT\t\t: Subject for Message\n\n"
               " -sv / --server SERVER_ADDRESS\t\t: SMTP Server Address for Email\n\n"
               " -t  / --timeout TIMEOUT(ms)\t\t: Timeout for end process (default 5000ms)\n\n"
               " -v  / --version\t\t\t\t: Print version of plugins\n\n"
               " ex  : -sv smtp.gmail.com -pr 465 -sd email@gmail.com -pw password -re recipient@gmail.com -su test_email -mf /home/user/message.txt -t 10000\n\n"
              );
        err = false;
    } else if (argc == 2) {
        QString arg1(argv[1]);
        if (arg1 == QLatin1String("-h") ||
            arg1 == QLatin1String("--help")) {
            printf(" -h  / --help\t\t\t\t: Print this help info\n\n"
                   " -mf / --message-file MESSAGE_FILE\t: Message(file) for Recipient\n\n"
                   " -pr / --port SERVER_PORT\t\t: Server Port for Email\n\n"
                   " -pw / --password EMAIL_PASSSWORD\t: Password for Sender\n\n"
                   " -re / --recipient EMAIL_ADDRESS\t: Recipient Email Address\n\n"
                   " -sd / --sender EMAIL_ADDRESS\t\t: Sender Email Address\n\n"
                   " -su / --subject SUBJECT\t\t: Subject for Message\n\n"
                   " -sv / --server SERVER_ADDRESS\t\t: SMTP Server Address for Email\n\n"
                   " -t  / --timeout TIMEOUT(ms)\t\t: Timeout for end process (default 5000ms)\n\n"
                   " -v  / --version\t\t\t\t: Print version of plugins\n\n"
                   " ex  : -sv smtp.gmail.com -pr 465 -sd email@gmail.com -pw password -re recipient@gmail.com -su test_email -mf /home/user/message.txt -t 10000\n\n"
                  );
            err = false;
        } else if (arg1 == QLatin1String("-v") ||
                 arg1 == QLatin1String("--version")) {
            printf(" Email Plugin Version: %s \nPT. DaunBiru Engiinering\nwww.daunbiru.com\n\n", VERSION);
            err = false;
        }
    } else  if (argc > 2) {
        QString server = "",
                port = "",
                sender = "",
                password = "",
                recipient = "",
                subject = "",
                message_file = "";
        for (int i = 1; i < argc; i++) {
            QString arg1(argv[i]);
            if (arg1 == QLatin1String("-mf") ||
                arg1 == QLatin1String("--message-file")) {
                message_file = argv[i+1];
//                qDebug() << "Message File : " << message_file;
            } else if (arg1 == QLatin1String("-pr") ||
                       arg1 == QLatin1String("--port")) {
                port = argv[i+1];
//                qDebug() << "Port         : " << port;
            } else if (arg1 == QLatin1String("-pw") ||
                       arg1 == QLatin1String("--password")) {
                password = argv[i+1];
//                qDebug() << "Password     : " << password;
            } else if (arg1 == QLatin1String("-re") ||
                       arg1 == QLatin1String("--recipient")) {
                recipient = argv[i+1];
//                qDebug() << "Recipient    : " << recipient;
            } else if (arg1 == QLatin1String("-sd") ||
                       arg1 == QLatin1String("--sender")) {
                sender = argv[i+1];
//                qDebug() << "Sender       : " << sender;
            } else if (arg1 == QLatin1String("-su") ||
                       arg1 == QLatin1String("--subject")) {
                subject = argv[i+1];
                subject = subject.replace("_", " ");
//                qDebug() << "Subject      : " << subject;
            } else if (arg1 == QLatin1String("-sv") ||
                       arg1 == QLatin1String("--server")) {
                server = argv[i+1];
//                qDebug() << "Server       : " << server;
            } /*else if (arg1 == QLatin1String("-t") ||
                       arg1 == QLatin1String("--timeout")) {
                timeout = atoi(argv[i+1]);
            }*/
        }
        if (!server.isEmpty() && !port.isEmpty() && !sender.isEmpty() && !password.isEmpty() && !recipient.isEmpty()) {
            result.append(server);
            result.append(port);
            result.append(sender);
            result.append(password);
            result.append(recipient);
            result.append(subject);
            result.append(message_file);
        } else {
            err = true;
        }
    }
    if (err) {
        printf("{\"ERR\": \"Wrong Plugin Commands\"}\n\n");
    }

    return result;
}

int timeOut(int argc, char **argv) {
    int tOut = 0;

    if (argc > 2) {
        for (int i = 1; i < argc; i++) {
            QString arg1(argv[i]);
            if (arg1 == QLatin1String("-t") || arg1 == QLatin1String("--timeout")) {
                tOut = atoi(argv[i+1]);
            }
        }
    }

    return tOut;
}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    worker w;
    a.connect(&w, SIGNAL(close()), &a, SLOT(quit()));
    QStringList parameter = processArgs(argc, argv);
    if (parameter.length() > 0) {
        w.sendMail(parameter.at(0),
                   parameter.at(1).toInt(),
                   parameter.at(2),
                   parameter.at(3),
                   parameter.at(4),
                   parameter.at(5),
                   parameter.at(6));
        QTimer::singleShot(timeOut(argc, argv), &a, SLOT(quit()));
        return a.exec();
    } else {
        return 0;
    }
}
