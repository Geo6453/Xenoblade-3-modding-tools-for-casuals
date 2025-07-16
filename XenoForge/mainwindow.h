#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDesktopServices>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QDockWidget>
#include "terminalwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *menuFiles;
    QMenu *menuHelp;

    QDockWidget *dockDown;
    TerminalWidget *terminalWidget;
};
#endif // MAINWINDOW_H
