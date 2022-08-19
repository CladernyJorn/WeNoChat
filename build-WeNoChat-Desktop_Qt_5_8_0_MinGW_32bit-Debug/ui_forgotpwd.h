/********************************************************************************
** Form generated from reading UI file 'forgotpwd.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPWD_H
#define UI_FORGOTPWD_H

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

class Ui_ForgotPwd
{
public:
    QFrame *frame;
    QLabel *label;
    QLineEdit *userEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *closeButton;
    QPushButton *hideButton;
    QLabel *label_2;
    QLineEdit *passwordEdit_2;
    QLineEdit *phoneNumberEdit;
    QLineEdit *questionEdit;
    QLineEdit *answerEdit;

    void setupUi(QWidget *ForgotPwd)
    {
        if (ForgotPwd->objectName().isEmpty())
            ForgotPwd->setObjectName(QStringLiteral("ForgotPwd"));
        ForgotPwd->resize(731, 731);
        ForgotPwd->setStyleSheet(QLatin1String("*{\n"
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
        frame = new QFrame(ForgotPwd);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 0, 731, 731));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 181, 31));
        userEdit = new QLineEdit(frame);
        userEdit->setObjectName(QStringLiteral("userEdit"));
        userEdit->setGeometry(QRect(110, 160, 511, 61));
        passwordEdit = new QLineEdit(frame);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(110, 460, 511, 61));
        passwordEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(frame);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(160, 650, 411, 51));
        closeButton = new QPushButton(frame);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(700, 0, 31, 28));
        hideButton = new QPushButton(frame);
        hideButton->setObjectName(QStringLiteral("hideButton"));
        hideButton->setGeometry(QRect(670, 0, 31, 28));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 70, 231, 71));
        label_2->setStyleSheet(QString::fromUtf8("font: 28pt \"\347\255\211\347\272\277\";"));
        passwordEdit_2 = new QLineEdit(frame);
        passwordEdit_2->setObjectName(QStringLiteral("passwordEdit_2"));
        passwordEdit_2->setGeometry(QRect(110, 530, 511, 61));
        passwordEdit_2->setEchoMode(QLineEdit::Password);
        phoneNumberEdit = new QLineEdit(frame);
        phoneNumberEdit->setObjectName(QStringLiteral("phoneNumberEdit"));
        phoneNumberEdit->setGeometry(QRect(110, 230, 511, 61));
        questionEdit = new QLineEdit(frame);
        questionEdit->setObjectName(QStringLiteral("questionEdit"));
        questionEdit->setGeometry(QRect(110, 300, 511, 61));
        answerEdit = new QLineEdit(frame);
        answerEdit->setObjectName(QStringLiteral("answerEdit"));
        answerEdit->setGeometry(QRect(110, 370, 511, 61));

        retranslateUi(ForgotPwd);

        QMetaObject::connectSlotsByName(ForgotPwd);
    } // setupUi

    void retranslateUi(QWidget *ForgotPwd)
    {
        ForgotPwd->setWindowTitle(QApplication::translate("ForgotPwd", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ForgotPwd", "WeNoChat", Q_NULLPTR));
        userEdit->setText(QString());
        userEdit->setPlaceholderText(QApplication::translate("ForgotPwd", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        passwordEdit->setPlaceholderText(QApplication::translate("ForgotPwd", "\346\226\260\345\257\206\347\240\201", Q_NULLPTR));
        loginButton->setText(QApplication::translate("ForgotPwd", "\346\211\276\345\233\236\345\257\206\347\240\201", Q_NULLPTR));
        closeButton->setText(QApplication::translate("ForgotPwd", "\303\227", Q_NULLPTR));
        hideButton->setText(QApplication::translate("ForgotPwd", "\342\200\224", Q_NULLPTR));
        label_2->setText(QApplication::translate("ForgotPwd", "\346\211\276\345\233\236\345\257\206\347\240\201", Q_NULLPTR));
        passwordEdit_2->setPlaceholderText(QApplication::translate("ForgotPwd", "\351\207\215\345\244\215\346\226\260\345\257\206\347\240\201", Q_NULLPTR));
        phoneNumberEdit->setText(QApplication::translate("ForgotPwd", "\346\211\213\346\234\272\345\217\267", Q_NULLPTR));
        phoneNumberEdit->setPlaceholderText(QApplication::translate("ForgotPwd", "\345\257\206\347\240\201", Q_NULLPTR));
        questionEdit->setText(QApplication::translate("ForgotPwd", "\345\257\206\344\277\235\351\227\256\351\242\230", Q_NULLPTR));
        questionEdit->setPlaceholderText(QApplication::translate("ForgotPwd", "\345\257\206\347\240\201", Q_NULLPTR));
        answerEdit->setText(QApplication::translate("ForgotPwd", "\345\257\206\344\277\235\351\227\256\351\242\230\345\233\236\347\255\224", Q_NULLPTR));
        answerEdit->setPlaceholderText(QApplication::translate("ForgotPwd", "\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ForgotPwd: public Ui_ForgotPwd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPWD_H
