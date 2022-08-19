/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *indowLabel;
    QToolBox *toolBox;
    QWidget *page_3;
    QWidget *page;
    QWidget *page_2;
    QFrame *windowFrame;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *chatName;
    QFrame *line;
    QFrame *line_2;
    QFrame *frame;
    QFrame *frame_2;
    QTextEdit *textEdit;
    QPushButton *pushButton_3;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1050, 649);
        indowLabel = new QLabel(MainWindow);
        indowLabel->setObjectName(QStringLiteral("indowLabel"));
        indowLabel->setGeometry(QRect(0, 0, 211, 61));
        indowLabel->setMouseTracking(true);
        indowLabel->setStyleSheet(QStringLiteral("background-color: rgb(250, 250, 250);"));
        toolBox = new QToolBox(MainWindow);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(0, 60, 211, 591));
        toolBox->setStyleSheet(QStringLiteral("background-color: rgb(226, 226, 226);"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        toolBox->addItem(page_3, QString::fromUtf8("\350\277\231\351\207\214\346\230\276\347\244\272\345\245\275\345\217\213\345\210\206\347\273\204"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 211, 501));
        toolBox->addItem(page, QString::fromUtf8("\351\231\244\344\272\206toolbox\346\262\241\346\203\263\345\210\260\347\211\271\345\210\253\345\245\275\347\232\204"));
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setGeometry(QRect(0, 0, 211, 501));
        toolBox->addItem(page_2, QString::fromUtf8("\345\244\252\344\270\221\344\272\206\346\234\200\345\245\275\346\215\242\344\270\200\344\270\213"));
        windowFrame = new QFrame(MainWindow);
        windowFrame->setObjectName(QStringLiteral("windowFrame"));
        windowFrame->setGeometry(QRect(990, 0, 61, 31));
        windowFrame->setFrameShape(QFrame::StyledPanel);
        windowFrame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(windowFrame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 31, 31));
        pushButton_2 = new QPushButton(windowFrame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 0, 31, 31));
        chatName = new QLabel(MainWindow);
        chatName->setObjectName(QStringLiteral("chatName"));
        chatName->setGeometry(QRect(210, 0, 841, 61));
        chatName->setStyleSheet(QStringLiteral("background-color: rgb(245, 245, 245);"));
        line = new QFrame(MainWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 50, 1051, 16));
        line->setLineWidth(2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(MainWindow);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(203, 0, 21, 651));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        frame = new QFrame(MainWindow);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(210, 60, 841, 591));
        frame->setStyleSheet(QStringLiteral("background-color: rgb(250, 250, 250);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 450, 841, 141));
        frame_2->setStyleSheet(QStringLiteral("background-color: rgb(242, 242, 242);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        textEdit = new QTextEdit(frame_2);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 0, 821, 91));
        textEdit->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        textEdit->setFrameShape(QFrame::NoFrame);
        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 90, 121, 41));
        pushButton_3->setStyleSheet(QLatin1String("QPushButton{\n"
"background:#ced1d8;\n"
"border-style:outset;\n"
"border-radius:10px;\n"
"font-style:MingLiU-ExtB;\n"
"}\n"
"QPushButton:pressed{\n"
"background-color:rgb(50,224,40);\n"
"border-style:inset;\n"
"font-style:MingLiU-ExtB;\n"
"}"));
        frame->raise();
        chatName->raise();
        indowLabel->raise();
        toolBox->raise();
        windowFrame->raise();
        line->raise();
        line_2->raise();

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", Q_NULLPTR));
        indowLabel->setText(QApplication::translate("MainWindow", "  WeNoChat", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("MainWindow", "\350\277\231\351\207\214\346\230\276\347\244\272\345\245\275\345\217\213\345\210\206\347\273\204", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "\351\231\244\344\272\206toolbox\346\262\241\346\203\263\345\210\260\347\211\271\345\210\253\345\245\275\347\232\204", Q_NULLPTR));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "\345\244\252\344\270\221\344\272\206\346\234\200\345\245\275\346\215\242\344\270\200\344\270\213", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\342\200\224", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\303\227", Q_NULLPTR));
        chatName->setText(QApplication::translate("MainWindow", "  \350\277\231\351\207\214\346\230\276\347\244\272\345\257\271\346\226\271\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\231\351\207\214\346\234\211\344\270\200\344\270\252\350\276\223\345\205\245\346\241\206</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
