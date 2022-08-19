/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *userEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *closeButton;
    QPushButton *hideButton;
    QPushButton *registButton;
    QPushButton *registButton_2;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(681, 421);
        login->setStyleSheet(QLatin1String("*{\n"
"background:rgb(255, 255, 255);\n"
"font-size:15px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QFrame{\n"
"border:sold 10px rgba(0,0,0);\n"
"background-image: url(:/loginbackground.png);\n"
"}\n"
"QLineEdit{\n"
"color:#8d98a1;\n"
"background-color:#405361;\n"
"font-size:16px;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton{\n"
"background:#ced1d8;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgb(224,0,0);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QCheckBox{\n"
"background:rgba(85,170,255,0);\n"
"color:white;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QLabel{\n"
"background:rgba(85,170,255,0);\n"
"color:white;\n"
"font-style:MingLiU-ExtB;\n"
"font-size:14px;\n"
"}\n"
""));
        frame = new QFrame(login);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 681, 421));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 181, 31));
        userEdit = new QLineEdit(frame);
        userEdit->setObjectName(QStringLiteral("userEdit"));
        userEdit->setGeometry(QRect(110, 150, 461, 61));
        passwordEdit = new QLineEdit(frame);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(110, 220, 461, 61));
        passwordEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(frame);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(120, 300, 441, 51));
        closeButton = new QPushButton(frame);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(652, 0, 31, 28));
        hideButton = new QPushButton(frame);
        hideButton->setObjectName(QStringLiteral("hideButton"));
        hideButton->setGeometry(QRect(622, 0, 31, 28));
        registButton = new QPushButton(frame);
        registButton->setObjectName(QStringLiteral("registButton"));
        registButton->setGeometry(QRect(0, 390, 81, 28));
        registButton->setStyleSheet(QLatin1String("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"background-color: rgb(255, 255, 255,0);\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgb(224,0,0);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}"));
        registButton_2 = new QPushButton(frame);
        registButton_2->setObjectName(QStringLiteral("registButton_2"));
        registButton_2->setGeometry(QRect(600, 390, 81, 28));
        registButton_2->setStyleSheet(QLatin1String("QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"background-color: rgb(255, 255, 255,0);\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgb(224,0,0);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", Q_NULLPTR));
        label->setText(QApplication::translate("login", "WeNoChat", Q_NULLPTR));
        userEdit->setText(QString());
        userEdit->setPlaceholderText(QApplication::translate("login", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        passwordEdit->setPlaceholderText(QApplication::translate("login", "\345\257\206\347\240\201", Q_NULLPTR));
        loginButton->setText(QApplication::translate("login", "\347\231\273\345\275\225", Q_NULLPTR));
        closeButton->setText(QApplication::translate("login", "\303\227", Q_NULLPTR));
        hideButton->setText(QApplication::translate("login", "\342\200\224", Q_NULLPTR));
        registButton->setText(QApplication::translate("login", "\346\263\250\345\206\214\350\264\246\345\217\267", Q_NULLPTR));
        registButton_2->setText(QApplication::translate("login", "\345\277\230\350\256\260\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
