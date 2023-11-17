#ifndef VALUEADDWINDOW_H
#define VALUEADDWINDOW_H

#include <QDialog>
#include <QModelIndex>

class BuddyLineEdit;
class QLabel;
class QComboBox;
class QPushButton;

class ValueRequestOptions;

class ValueAddWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ValueAddWindow(QWidget *parent = nullptr);

    void setToAddIndex(const QModelIndex &toAddIndex);

signals:
    void valueAdded(const QModelIndex &toAddIndex, const ValueRequestOptions &options);

private slots:
    void onAddButtonClicked();

private:
    void setupUi();

private:
    QModelIndex toAddIndex_;

    BuddyLineEdit *nameEdit_ = nullptr;
    BuddyLineEdit *valueAddressEdit_ = nullptr;
    QLabel *intervalBuddyLabel_ = nullptr;
    QComboBox *intervalPicker_ = nullptr;
    QPushButton *addButton_ = nullptr;
};

#endif // VALUEADDWINDOW_H
