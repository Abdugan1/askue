#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DeviceList;
class DeviceAddWindow;
class ValueTable;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();

private:
    DeviceList *deviceList_ = nullptr;
    ValueTable *valueTable_ = nullptr;
    DeviceAddWindow *deviceAddWindow_ = nullptr;
};
#endif // MAINWINDOW_H
