#include "terminalwidget.h"
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

    consoleOutput->appendPlainText("Terminal - Ready");
    consoleOutput->appendPlainText("Enter 'help' to display some commands\n----------------------------------------\n");
}

TerminalWidget::~TerminalWidget() {}

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

    currentProcess->setWorkingDirectory("C:\\");
    currentProcess->start("cmd.exe", QStringList() << "/A /H:ON /K" << command);
}

void TerminalWidget::clear()
{
    consoleOutput->clear();
}
