 #include "terminalwidget.h"
#include <QScrollBar>
#include <QVBoxLayout>

TerminalWidget::TerminalWidget(QWidget *parent)
    : QWidget(parent),
    consoleOutput(new QPlainTextEdit(this)),
    commandInput(new QLineEdit(this)),
    currentProcess(new QProcess(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    consoleOutput->setReadOnly(true);
    consoleOutput->setWordWrapMode(QTextOption::NoWrap);
    consoleOutput->setStyleSheet("QPlainTextEdit {"
                                 "background: black;"
                                 "color: #00FF00;"
                                 "font-family: Consolas;"
                                 "padding: 5px;"
                                 "border: none;"
                                 "}");

    commandInput->setPlaceholderText("Enter a command...");
    commandInput->setStyleSheet("QLineEdit {"
                                "background: #222;"
                                "color: white;"
                                "padding: 5px;"
                                "border: 1px solid #444;"
                                "}");

    layout->addWidget(consoleOutput);
    layout->addWidget(commandInput);

    connect(commandInput, &QLineEdit::returnPressed, this, &TerminalWidget::onCommandEntered);
    connect(currentProcess, &QProcess::readyReadStandardOutput, this, &TerminalWidget::processReadyRead);
    connect(currentProcess, &QProcess::readyReadStandardError, this, &TerminalWidget::processReadyRead);
    connect(currentProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &TerminalWidget::processFinished);

    commandInput->installEventFilter(this);
    consoleOutput->appendPlainText("Terminal - Ready");
    consoleOutput->appendPlainText("Enter 'help' to display some commands\n----------------------------------------\n");
}

TerminalWidget::~TerminalWidget()
{
    if (currentProcess->state() == QProcess::Running)
    {
        currentProcess->terminate();
        currentProcess->waitForFinished();
    }
}

void TerminalWidget::executeCommand(const QString &command)
{
    if (command.isEmpty()) return;

    consoleOutput->appendPlainText("$ " + command);

    if (command == "clear") {consoleOutput->clear(); return;}

    if (command == "help")
    {
        consoleOutput->appendPlainText(
            "\nAvailables commands:\n"
            "  clear       - Clear the console\n"
            "  help        - Display some commands\n"
            "  exit        - Close the software\n"
            "\nSystem Commands:\n"
            "  All other commands are executed on the system shell\n");
        return;
    }

    currentProcess->setWorkingDirectory(QDir::currentPath());
    currentProcess->start("cmd.exe", QStringList() << "/C" << command);

    if (!currentProcess->waitForStarted(1000))
    {
        consoleOutput->appendPlainText("Error: This command cannot be executed");
    }
}

void TerminalWidget::clear()
{
    consoleOutput->clear();
}

void TerminalWidget::onCommandEntered()
{
    QString command = commandInput->text().trimmed();
    commandInput->clear();

    if (!command.isEmpty())
    {
        executeCommand(command);
        emit commandExecuted(command);
    }
}

void TerminalWidget::processReadyRead()
{
    consoleOutput->appendPlainText(QString::fromLocal8Bit(currentProcess->readAllStandardOutput()).trimmed());
    consoleOutput->appendPlainText(QString::fromLocal8Bit(currentProcess->readAllStandardError()).trimmed());
    consoleOutput->verticalScrollBar()->setValue(consoleOutput->verticalScrollBar()->maximum());
}

void TerminalWidget::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString status = exitStatus == QProcess::CrashExit ?
                         "\n[The process did not complete normally]" :
                         QString("\n[Process end]").arg(exitCode);
    consoleOutput->appendPlainText(status + "\n----------------------------------------\n");
}

bool TerminalWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == commandInput && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down) {return true;}
    }
    return QWidget::eventFilter(obj, event);
}
