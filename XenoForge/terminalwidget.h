#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QProcess>

class TerminalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void executeCommand(const QString &command);
    void clear();

signals:


private slots:


protected:


private:
    QPlainTextEdit *consoleOutput;
    QLineEdit *commandInput;
    QProcess *currentProcess;
};

#endif // TERMINALWIDGET_H
