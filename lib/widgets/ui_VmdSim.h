/********************************************************************************
** Form generated from reading ui file 'vmdsim.ui'
**
** Created: Sun Sep 2 20:47:08 2007
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VMDSIM_H
#define UI_VMDSIM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

class Ui_vmdsim
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pausa;
    QPushButton *arranca;
    QPushButton *descartar;
    QPushButton *detiene;
    QPushButton *vmdbutton;
    QPushButton *namd2;

    void setupUi(QWidget *vmdsim)
    {
    vmdsim->setObjectName(QString::fromUtf8("vmdsim"));
    vmdsim->setWindowModality(Qt::ApplicationModal);
    vmdsim->setSizeIncrement(QSize(10, 10));
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(255, 255, 255, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    QBrush brush2(QColor(255, 255, 255, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Light, brush2);
    QBrush brush3(QColor(255, 255, 255, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
    QBrush brush4(QColor(127, 127, 127, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
    QBrush brush5(QColor(170, 170, 170, 255));
    brush5.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
    QBrush brush6(QColor(0, 0, 0, 255));
    brush6.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Text, brush6);
    QBrush brush7(QColor(255, 255, 255, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::BrightText, brush7);
    QBrush brush8(QColor(0, 0, 0, 255));
    brush8.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush8);
    QBrush brush9(QColor(255, 255, 255, 255));
    brush9.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush9);
    QBrush brush10(QColor(255, 255, 255, 255));
    brush10.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush10);
    QBrush brush11(QColor(0, 0, 0, 255));
    brush11.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Shadow, brush11);
    QBrush brush12(QColor(255, 255, 255, 255));
    brush12.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush12);
    QBrush brush13(QColor(0, 0, 0, 255));
    brush13.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush13);
    QBrush brush14(QColor(255, 255, 255, 255));
    brush14.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush14);
    QBrush brush15(QColor(255, 255, 255, 255));
    brush15.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Light, brush15);
    QBrush brush16(QColor(255, 255, 255, 255));
    brush16.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush16);
    QBrush brush17(QColor(127, 127, 127, 255));
    brush17.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Dark, brush17);
    QBrush brush18(QColor(170, 170, 170, 255));
    brush18.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Mid, brush18);
    QBrush brush19(QColor(0, 0, 0, 255));
    brush19.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush19);
    QBrush brush20(QColor(255, 255, 255, 255));
    brush20.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush20);
    QBrush brush21(QColor(0, 0, 0, 255));
    brush21.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush21);
    QBrush brush22(QColor(255, 255, 255, 255));
    brush22.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush22);
    QBrush brush23(QColor(255, 255, 255, 255));
    brush23.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush23);
    QBrush brush24(QColor(0, 0, 0, 255));
    brush24.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush24);
    QBrush brush25(QColor(255, 255, 255, 255));
    brush25.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush25);
    QBrush brush26(QColor(127, 127, 127, 255));
    brush26.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush26);
    QBrush brush27(QColor(255, 255, 255, 255));
    brush27.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush27);
    QBrush brush28(QColor(255, 255, 255, 255));
    brush28.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Light, brush28);
    QBrush brush29(QColor(255, 255, 255, 255));
    brush29.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush29);
    QBrush brush30(QColor(127, 127, 127, 255));
    brush30.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Dark, brush30);
    QBrush brush31(QColor(170, 170, 170, 255));
    brush31.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush31);
    QBrush brush32(QColor(127, 127, 127, 255));
    brush32.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush32);
    QBrush brush33(QColor(255, 255, 255, 255));
    brush33.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush33);
    QBrush brush34(QColor(127, 127, 127, 255));
    brush34.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush34);
    QBrush brush35(QColor(255, 255, 255, 255));
    brush35.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush35);
    QBrush brush36(QColor(255, 255, 255, 255));
    brush36.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush36);
    QBrush brush37(QColor(0, 0, 0, 255));
    brush37.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush37);
    QBrush brush38(QColor(255, 255, 255, 255));
    brush38.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush38);
    vmdsim->setPalette(palette);
    layoutWidget = new QWidget(vmdsim);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(30, 70, 271, 72));
    gridLayout = new QGridLayout(layoutWidget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    pausa = new QPushButton(layoutWidget);
    pausa->setObjectName(QString::fromUtf8("pausa"));
    pausa->setIcon(QIcon(QString::fromUtf8(":/icons/default/icons/control_pause_blue.png")));

    gridLayout->addWidget(pausa, 0, 2, 1, 1);

    arranca = new QPushButton(layoutWidget);
    arranca->setObjectName(QString::fromUtf8("arranca"));
    arranca->setIcon(QIcon(QString::fromUtf8(":/icons/default/icons/control_play_blue.png")));

    gridLayout->addWidget(arranca, 0, 0, 1, 2);

    descartar = new QPushButton(layoutWidget);
    descartar->setObjectName(QString::fromUtf8("descartar"));
    descartar->setIcon(QIcon(QString::fromUtf8(":/icons/default/icons/cancel.png")));

    gridLayout->addWidget(descartar, 1, 2, 1, 1);

    detiene = new QPushButton(layoutWidget);
    detiene->setObjectName(QString::fromUtf8("detiene"));
    detiene->setIcon(QIcon(QString::fromUtf8(":/icons/default/icons/control_stop_blue.png")));

    gridLayout->addWidget(detiene, 1, 0, 1, 1);

    vmdbutton = new QPushButton(vmdsim);
    vmdbutton->setObjectName(QString::fromUtf8("vmdbutton"));
    vmdbutton->setGeometry(QRect(30, 20, 80, 27));
    vmdbutton->setContextMenuPolicy(Qt::NoContextMenu);
    namd2 = new QPushButton(vmdsim);
    namd2->setObjectName(QString::fromUtf8("namd2"));
    namd2->setGeometry(QRect(170, 20, 80, 27));

    retranslateUi(vmdsim);

    QSize size(335, 155);
    size = size.expandedTo(vmdsim->minimumSizeHint());
    vmdsim->resize(size);


    QMetaObject::connectSlotsByName(vmdsim);
    } // setupUi

    void retranslateUi(QWidget *vmdsim)
    {
    vmdsim->setWindowTitle(QApplication::translate("vmdsim", "Form", 0, QApplication::UnicodeUTF8));
    vmdsim->setToolTip(QApplication::translate("vmdsim", "Simulador de molecuals", 0, QApplication::UnicodeUTF8));
    pausa->setToolTip(QApplication::translate("vmdsim", "Pausa la simulacion", 0, QApplication::UnicodeUTF8));
    pausa->setText(QApplication::translate("vmdsim", " Pausa", 0, QApplication::UnicodeUTF8));
    arranca->setToolTip(QApplication::translate("vmdsim", "Arranca la simulacion", 0, QApplication::UnicodeUTF8));
    arranca->setText(QApplication::translate("vmdsim", " Arranca", 0, QApplication::UnicodeUTF8));
    descartar->setToolTip(QApplication::translate("vmdsim", "Detiene la simulacion, pero regresa la visualizacion al edo inicial", 0, QApplication::UnicodeUTF8));
    descartar->setText(QApplication::translate("vmdsim", " Descartar", 0, QApplication::UnicodeUTF8));
    detiene->setToolTip(QApplication::translate("vmdsim", "Detiene la simulacion y lo deja en el ultimo estado de la misma", 0, QApplication::UnicodeUTF8));
    detiene->setText(QApplication::translate("vmdsim", "Detiene", 0, QApplication::UnicodeUTF8));
    vmdbutton->setText(QApplication::translate("vmdsim", "VMD", 0, QApplication::UnicodeUTF8));
    namd2->setText(QApplication::translate("vmdsim", "NAMD2", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(vmdsim);
    } // retranslateUi

};

namespace Ui {
    class vmdsim: public Ui_vmdsim {};
} // namespace Ui

#endif // UI_VMDSIM_H
