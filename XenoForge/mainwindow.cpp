#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    tabWidget(nullptr),
    dockLeft(nullptr),
    dockDown(nullptr)
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

    QAction *toggleTheme = new QAction("&Toggle Theme", this);

    //connect(menuEdition, );

    menuHelp = menuBar()->addMenu("&Help");
    QAction *actionUpdate = new QAction("&Search Update", this);
        menuHelp->addAction(actionUpdate);
        connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals/releases"));});
    QAction *actionRepoGithub = new QAction("&Github Repo", this);
        menuHelp->addAction(actionRepoGithub);
        connect(actionRepoGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals"));});
    QAction *actionDiscord = new QAction("&Discord Server", this);
        menuHelp->addAction(actionDiscord);
        connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/27Wz4QB"));});
    QAction *actionQt = new QAction("About &Qt", this);
        menuHelp->addAction(actionQt);
        connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
    QAction *actionXenoForge = new QAction("About &XenoForge", this);
        menuHelp->addAction(actionXenoForge);
        connect(actionXenoForge, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/Geo6453/Xenoblade-3-modding-tools-for-casuals/main/README.md"));});

    // Add tabs on a QDockWidget
    dockLeft = new QDockWidget("Lateral Pannel", this);
    dockLeft->setWidget(tabWidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockLeft);
    dockLeft->setMinimumWidth(250);
    dockLeft->setMaximumWidth(450);
    dockLeft->setFeatures(dockLeft->features() & QDockWidget::NoDockWidgetFeatures);

    // Create the widget who contain the grid on CentralWidget
    QWidget *gridCentral = new QWidget(centralWidget());
    QGridLayout *layoutCentral = new QGridLayout(gridCentral);
    QCheckBox *checkbox = new QCheckBox("show &CMD", gridCentral);
        layoutCentral->addWidget(checkbox);
    QPushButton *launch = new QPushButton("Launch Xenotools", gridCentral);
        layoutCentral->addWidget(launch);

    // Create the QDockWidget Down
    dockDown = new QDockWidget("Status pannel", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockDown);
    dockDown->setMinimumWidth(250);
    dockDown->setMaximumWidth(450);
    dockDown->setFeatures(dockDown->features() & QDockWidget::NoDockWidgetFeatures);

    // Create the widget who contain the grid on DockDown
    QWidget *gridDown = new QWidget();
    QGridLayout *layoutDown = new QGridLayout(gridDown);
    dockDown->setWidget(gridDown);

    layoutDown->addWidget(new QPushButton("One", gridDown), 0, 0);
    layoutDown->addWidget(new QPushButton("Two", gridDown), 0, 1);
    layoutDown->addWidget(new QPushButton("Three", gridDown), 1, 0, 1, 2);  // RowSpan
    layoutDown->addWidget(new QPushButton("Four", gridDown), 2, 0);
    layoutDown->addWidget(new QPushButton("Five", gridDown), 2, 1);

    dockDown->setWidget(gridDown);
    addDockWidget(Qt::BottomDockWidgetArea, dockDown);


    // QProcess;
}

MainWindow::~MainWindow(){}
