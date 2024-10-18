#ifndef TESTAPP_H
#define TESTAPP_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class TestApp;
}

class TestApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestApp(QWidget *parent = nullptr);
    ~TestApp() override;

private:
    QScopedPointer<Ui::TestApp> m_ui;
};

#endif // TESTAPP_H
