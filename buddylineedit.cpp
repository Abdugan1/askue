#include "buddylineedit.h"

#include <QLineEdit>
#include <QLabel>
#include <QBoxLayout>

BuddyLineEdit::BuddyLineEdit(const QString &buddyLabelText,
                             const QString &placeholder,
                             QWidget *parent)
    : QWidget(parent)
    , lineEdit_(new QLineEdit())
    , label_(new QLabel(buddyLabelText))
{
    setPlaceholderText(placeholder);
    label_->setBuddy(lineEdit_);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(label_);
    layout->addWidget(lineEdit_);

    setLayout(layout);
}

void BuddyLineEdit::setText(const QString &text)
{
    lineEdit_->setText(text);
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
