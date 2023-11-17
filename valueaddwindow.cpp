#include "valueaddwindow.h"
#include "buddylineedit.h"
#include "valuerequestoptions.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>

const QList<QString> intervals{
    QObject::tr("1 second"),
    QObject::tr("15 seconds"),
    QObject::tr("1 minute"),
    QObject::tr("15 minutes"),
};

ValueAddWindow::ValueAddWindow(QWidget *parent)
    : QDialog(parent)
{
    setupUi();

    connect(addButton_, &QPushButton::clicked, this, &ValueAddWindow::onAddButtonClicked);
}

void ValueAddWindow::setToAddIndex(const QModelIndex &toAddIndex)
{
    toAddIndex_ = toAddIndex;
}

void ValueAddWindow::setupUi()
{
    nameEdit_ = new BuddyLineEdit(tr("Value &name"), tr("Example Power"));
    nameEdit_->setText("Power");

    valueAddressEdit_ = new BuddyLineEdit(tr("Value &address"), tr("Example 13312"));
    valueAddressEdit_->setText("5");

    intervalPicker_ = new QComboBox;
    intervalPicker_->addItems(intervals);

    intervalBuddyLabel_ = new QLabel(tr("Request &interval"));
    intervalBuddyLabel_->setBuddy(intervalPicker_);

    auto intervalLayout = new QVBoxLayout;
    intervalLayout->addWidget(intervalBuddyLabel_);
    intervalLayout->addWidget(intervalPicker_);

    addButton_ = new QPushButton(tr("A&dd value"));

    auto editLayout = new QHBoxLayout;
    editLayout->addWidget(nameEdit_);
    editLayout->addWidget(valueAddressEdit_);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(editLayout);
    mainLayout->addLayout(intervalLayout);
    mainLayout->addWidget(addButton_, 0, Qt::AlignVCenter | Qt::AlignRight);


    setLayout(mainLayout);
}

void ValueAddWindow::onAddButtonClicked()
{
    ValueRequestOptions options;
    options.setName(nameEdit_->text());
    options.setAddress(valueAddressEdit_->text().toInt());

    emit valueAdded(toAddIndex_, options);

    close();
}
