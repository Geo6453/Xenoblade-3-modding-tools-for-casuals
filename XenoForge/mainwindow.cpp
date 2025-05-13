#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    tabWidget(nullptr),
    dockLeft(nullptr)
{
    this->window()->setGeometry(0, 0, 1000, 600);

    setCentralWidget(new QWidget);

    menuFiles = menuBar()->addMenu("&Files");
        QMenu *recentFiles = menuFiles->addMenu("&Recent files");
            recentFiles->addAction("PlaceHolder 1");
            recentFiles->addAction("PlaceHolder 2");
            recentFiles->addAction("PlaceHolder 3");
        //QAction *actionSave = new QAction("&Save", this);
        QAction *actionQuit = new QAction("&Quit", this);
        menuFiles->addAction(actionQuit);
        connect(actionQuit, &QAction::triggered, qApp, &QApplication::quit);

    menuEdition = menuBar()->addMenu("&Edition");

    menuHelp = menuBar()->addMenu("&Help");
    QAction *actionUpdate = new QAction("&Search Update", this);
        menuHelp->addAction(actionUpdate);
        connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals/releases"));});
    QAction *actionRepoGithub = new QAction("&Github Repo", this);
        menuHelp->addAction(actionRepoGithub);
        connect(actionRepoGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals"));});
    QAction *actionDiscord = new QAction("&Discord server", this);
        menuHelp->addAction(actionDiscord);
        connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/27Wz4QB"));});
    QAction *actionQt = new QAction("&About Qt", this);
        menuHelp->addAction(actionQt);
        connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
    QAction *actionXenoForge = new QAction("&About XenoForge", this);
        menuHelp->addAction(actionXenoForge);
        connect(actionXenoForge, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals/main/README.md"));});

    // Add tabs on a QDockWidget
    dockLeft = new QDockWidget("Lateral Pannel", this);
    dockLeft->setWidget(tabWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockLeft);
    dockLeft->setMinimumWidth(250);
    dockLeft->setMaximumWidth(450);
    dockLeft->setFeatures(dockLeft->features() & QDockWidget::NoDockWidgetFeatures);

    // Create the QDockWidget Down
    dockDown = new QDockWidget("Status pannel", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockDown);
    dockDown->setMinimumWidth(250);
    dockDown->setMaximumWidth(450);
    dockDown->setFeatures(dockDown->features() & QDockWidget::NoDockWidgetFeatures);

    // Create the widget who contain the grid
    QWidget *grid = new QWidget();
    dockDown->setWidget(grid);

    // Create test buttons
    QPushButton *button1 = new QPushButton("One", grid);
    QPushButton *button2 = new QPushButton("Two", grid);
    QPushButton *button3 = new QPushButton("Three", grid);
    QPushButton *button4 = new QPushButton("Four", grid);
    QPushButton *button5 = new QPushButton("Five", grid);

    // Create layout as a grid
    QGridLayout *layout = new QGridLayout(grid);
    layout->addWidget(button1, 0, 0);
    layout->addWidget(button2, 0, 1);
    layout->addWidget(button3, 1, 0, 1, 2);
    layout->addWidget(button4, 2, 0);
    layout->addWidget(button5, 2, 1);
}

MainWindow::~MainWindow()
{
}
