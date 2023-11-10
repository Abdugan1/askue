#include "buddylineedit.h"

#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>

BuddyLineEdit::BuddyLineEdit(const QString &lineEditText,
                             const QString &buddyLabelText,
                             QWidget *parent)
    : QWidget(parent)
    , lineEdit_(new QLineEdit(lineEditText))
    , label_(new QLabel(buddyLabelText))
{
    label_->setBuddy(lineEdit_);

    auto layout = new QVBoxLayout;
    layout->addWidget(label_);
    layout->addWidget(lineEdit_);

    setLayout(layout);
}

void BuddyLineEdit::setPlaceholderText(const QString &placeholder)
{
    lineEdit_->setPlaceholderText(placeholder);
}

void BuddyLineEdit::setValidator(const QValidator *validator)
{
    lineEdit_->setValidator(validator);
}

void BuddyLineEdit::clear()
{
    lineEdit_->clear();
}

QString BuddyLineEdit::text() const
{
    return lineEdit_->text();
}
