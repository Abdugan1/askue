#ifndef BUDDYLINEEDIT_H
#define BUDDYLINEEDIT_H

#include <QWidget>

class QLineEdit;
class QLabel;
class QValidator;

class BuddyLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit BuddyLineEdit(const QString &lineEditText,
                           const QString &buddyLabelText,
                           QWidget *parent = nullptr);

    void setPlaceholderText(const QString &placeholder);

    void setValidator(const QValidator *validator);

    void clear();

    QString text() const;

private:
    QLineEdit *lineEdit_ = nullptr;
    QLabel *label_ = nullptr;
};

#endif // BUDDYLINEEDIT_H
