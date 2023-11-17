#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DeviceView;
class ValueView;

class DeviceAddWindow;
class ValueAddWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();

private:
    DeviceView *deviceList_ = nullptr;
    ValueView *valueTable_ = nullptr;
};
#endif // MAINWINDOW_H
