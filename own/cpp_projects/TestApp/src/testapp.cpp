#include "testapp.h"
#include "ui_testapp.h"

TestApp::TestApp(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::TestApp)
{
    m_ui->setupUi(this);
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
    QAction *newAct = new QAction(tr("&New"), this);
    fileMenu->addAction(newAct);
}

TestApp::~TestApp() = default;
