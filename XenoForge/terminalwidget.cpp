#include "terminalwidget.h"
#include <QScrollBar>
#include <QVBoxLayout>

TerminalWidget::TerminalWidget(QWidget *parent)
    : QWidget(parent),
    consoleOutput(new QPlainTextEdit(this)),
    commandInput(new QLineEdit(this)),
    currentProcess(new QProcess(this))
{
    // Configuration de l'interface
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // Configuration de la console
    consoleOutput->setReadOnly(true);
    consoleOutput->setWordWrapMode(QTextOption::NoWrap);
    consoleOutput->setStyleSheet("QPlainTextEdit {"
                                 "background: black;"
                                 "color: #00FF00;"
                                 "font-family: Consolas;"
                                 "padding: 5px;"
                                 "border: none;"
                                 "}");

    // Configuration du champ de commande
    commandInput->setPlaceholderText("Entrez une commande...");
    commandInput->setStyleSheet("QLineEdit {"
                                "background: #222;"
                                "color: white;"
                                "padding: 5px;"
                                "border: 1px solid #444;"
                                "}");

    // Assemblage
    layout->addWidget(consoleOutput);
    layout->addWidget(commandInput);

    // Connexions
    connect(commandInput, &QLineEdit::returnPressed, this, &TerminalWidget::onCommandEntered);
    connect(currentProcess, &QProcess::readyReadStandardOutput, this, &TerminalWidget::processReadyRead);
    connect(currentProcess, &QProcess::readyReadStandardError, this, &TerminalWidget::processReadyRead);
    connect(currentProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, &TerminalWidget::processFinished);

    commandInput->installEventFilter(this);

    // Message de bienvenue
    consoleOutput->appendPlainText("Terminal - Prêt");
    consoleOutput->appendPlainText("Entrez 'help' pour l'aide\n----------------------------------------\n");
}

TerminalWidget::~TerminalWidget()
{
    if (currentProcess->state() == QProcess::Running) {
        currentProcess->terminate();
        currentProcess->waitForFinished();
    }
}

void TerminalWidget::executeCommand(const QString &command)
{
    if (command.isEmpty()) return;

    consoleOutput->appendPlainText("$ " + command);

    if (command == "clear") {
        consoleOutput->clear();
        return;
    }

    if (command == "help") {
        consoleOutput->appendPlainText(
            "\nCommandes disponibles:\n"
            "  clear       - Efface la console\n"
            "  help        - Affiche cette aide\n"
            "  exit        - Quitte l'application\n"
            "\nCommandes système:\n"
            "  Toutes les autres commandes sont exécutées dans le shell système\n");
        return;
    }

    currentProcess->setWorkingDirectory(QDir::currentPath());
    currentProcess->start("cmd.exe", QStringList() << "/C" << command);

    if (!currentProcess->waitForStarted(1000)) {
        consoleOutput->appendPlainText("Erreur: impossible d'exécuter la commande");
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

    if (!command.isEmpty()) {
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
                         "\n[Processus terminé anormalement]" :
                         QString("\n[Processus terminé - Code: %1]").arg(exitCode);
    consoleOutput->appendPlainText(status + "\n----------------------------------------\n");
}

bool TerminalWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == commandInput && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Up || keyEvent->key() == Qt::Key_Down) {
            // Gestion de l'historique
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}
