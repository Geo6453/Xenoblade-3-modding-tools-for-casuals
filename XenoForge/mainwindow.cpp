#include "mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    menuFiles(nullptr),
    menuEdition(nullptr),
    menuDisplay(nullptr),
    menuHelp(nullptr),
    toggleTheme(nullptr),
    dockLeft(nullptr),
    dockDown(new QDockWidget("Terminal", this)),
    terminalWidget(new TerminalWidget(this)),
    tabWidget(nullptr)
{
    this->window()->setGeometry(0, 0, 1000, 600);
    setCentralWidget(new QWidget);
    this->centralWidget();

    menuFiles = menuBar()->addMenu("&Files");
    QMenu *recentFiles = menuFiles->addMenu("&Recent files");
        recentFiles->addAction("PlaceHolder 1");
        recentFiles->addAction("PlaceHolder 2");
        recentFiles->addAction("PlaceHolder 3");
    //QAction *actionSave = new QAction("&Save", this);
    QAction *actionQuit = new QAction("&Quit", this);
        menuFiles->addAction(actionQuit);
        connect(actionQuit, &QAction::triggered, qApp, &QApplication::quit);

    //menuEdition = menuBar()->addMenu("&Edition", this);

    menuHelp = menuBar()->addMenu("&Help");
    QAction *actionUpdate = new QAction("&Search Update", this);
        menuHelp->addAction(actionUpdate);
        connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge/releases"));});
    QAction *actionRepoGithub = new QAction("&Github Repo", this);
        menuHelp->addAction(actionRepoGithub);
        connect(actionRepoGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge"));});
    QAction *actionDiscord = new QAction("&Discord Server", this);
        menuHelp->addAction(actionDiscord);
        connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/27Wz4QB"));});
    QAction *actionQt = new QAction("About &Qt", this);
        menuHelp->addAction(actionQt);
        connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
    QAction *actionXenoForge = new QAction("About &XenoForge", this);
        menuHelp->addAction(actionXenoForge);
        connect(actionXenoForge, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/XenoForge/main/README.md"));});

    QAction *toggleTheme = new QAction("&Toggle Theme", this);
        menuBar()->addAction(toggleTheme);

    // Add tabs on a QDockWidget
    dockLeft = new QDockWidget("Lateral Pannel", this);
    dockLeft->setWidget(tabWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockLeft);
    dockLeft->setMinimumWidth(250);
    dockLeft->setMaximumWidth(450);
    dockLeft->setFeatures(dockLeft->features() & QDockWidget::NoDockWidgetFeatures);

    // Create the widget that contain the grid on CentralWidget
    QWidget *gridCentral = new QWidget(centralWidget());
    QGridLayout *layoutCentral = new QGridLayout(gridCentral);

    QCheckBox *checkbox = new QCheckBox("show &CMD", gridCentral);
    layoutCentral->addWidget(checkbox, 0, 0);

    QPushButton *launch = new QPushButton("Launch Xenotools", gridCentral);
    layoutCentral->addWidget(launch, 1, 0);

    dockDown->setWidget(terminalWidget);
    addDockWidget(Qt::BottomDockWidgetArea, dockDown);
    dockDown->setFeatures(dockDown->features() & ~QDockWidget::DockWidgetFloatable & ~QDockWidget::DockWidgetClosable);
}

MainWindow::~MainWindow(){}
