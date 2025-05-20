#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QDesktopServices>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private:
    QMenu *menuFiles;
    QMenu *menuEdition;
    QMenu *menuDisplay;
    QMenu *menuHelp;
    QMenu *toggleTheme;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    QTabWidget *tabWidget; // Tabs of DockLeft
    QDockWidget *dockLeft; // Lateral Pannel
    QDockWidget *dockDown; // Status Pannel
};
#endif // MAINWINDOW_H
