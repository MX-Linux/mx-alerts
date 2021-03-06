#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCommandLineParser>
#include <QMenu>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QTimer>

#include <version.h>

// struct for outputing both the exit code and the strings when running a command
struct Output {
    int exit_code;
    QString str;
};

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(const QCommandLineParser &arg_parser);
    Output getCmdOut(const QString &cmd);

private slots:
    bool checkUpdates();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();
    void setIcon(QString icon_name);
    void showAbout();

private:
    bool autoStartup;
    bool downloadFile(QUrl url);
    bool showLastAlert(bool clicked = false);
    bool verifySignature();

    void displayFile(QString fileName, bool clicked = false);
    void createActions();
    void createMenu();
    void csleep(int msec);
    void loadSettings();
    void toggleDisabled();
    void setEnabled(bool enabled);
    void showMessage(QString title, QString body);
    void writeFile(QString extension = "");

    QString getDateInfo();
    QString getSigInfo();

    QString release;
    QString server;
    QString tmpFolder = "/var/tmp/mx-alerts/";
    QSettings userSettings;

    QAction *aboutAction;
    QAction *toggleDisableAction;
    QAction *hideAction;
    QAction *lastAlertAction;
    QAction *lastNewsAction;
    QAction *quitAction;

    QSystemTrayIcon *alertIcon;
    QMenu *alertMenu;

    QNetworkAccessManager manager;
    QNetworkReply *reply;

    QTimer timer;
};

#endif

