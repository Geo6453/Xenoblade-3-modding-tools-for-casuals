#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include "qconsole.h"
#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QProcess>
#include <QDir>

class TerminalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void executeCommand(const QString &command);
    void clear();

signals:
    void commandExecuted(const QString &command);

private slots:
    void onCommandEntered();
    void processReadyRead();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    QPlainTextEdit *consoleOutput;
    QLineEdit *commandInput;
    QProcess *currentProcess;
};

#endif // TERMINALWIDGET_H
