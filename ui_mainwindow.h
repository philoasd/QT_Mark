/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ExtendQGraphicsView.h"
#include "QxtSpanSlider.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFile;
    QAction *actionSaveFile;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionOpenMarkInterface;
    QAction *actionOpenCameraInterface;
    QAction *actionSelect;
    QAction *actionDrawLine;
    QAction *actionDrawRectangle;
    QAction *actionDrawRoundedCornerRectangle;
    QAction *actionDrawTriangle;
    QAction *actionDrawCircle;
    QAction *actionDrawEllipse;
    QAction *actionDrawPolygon;
    QAction *actionGrabOnce;
    QAction *actionGrabContinue;
    QAction *actionGrabStop;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView_Mark;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_3;
    ExtendQGraphicsView *graphicsView_Camera;
    QStackedWidget *stackedWidget_Parameters;
    QWidget *page_3;
    QLabel *label_2;
    QWidget *page_4;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_AutoThreshold;
    QCheckBox *checkBox_ManualThreshold;
    QHBoxLayout *horizontalLayout_7;
    QSpinBox *spinBox_LeftThreshold;
    QxtSpanSlider *horizontalSlider_Threshold;
    QSpinBox *spinBox_RightThreshold;
    QWidget *tab_2;
    QWidget *tab_3;
    QGroupBox *groupBox_CameraInfo;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_3;
    QComboBox *comboBox_CameraInfo;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_AutoExposure;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_Exposure;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_FrameRate;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_ConnectedCamera;
    QPushButton *pushButton_DisConnectedCamera;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_LoadImage;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *lineEdit_ImageFilePath;
    QPushButton *pushButton_LoadImage;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar_Tool;
    QToolBar *toolBar_Shapes;
    QToolBar *toolBar_Camera;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1080);
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("ico/open_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon);
        actionSaveFile = new QAction(MainWindow);
        actionSaveFile->setObjectName(QString::fromUtf8("actionSaveFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("ico/save_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveFile->setIcon(icon1);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("ico/undo_back_left_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon2);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("ico/redo_forward_right_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon3);
        actionOpenMarkInterface = new QAction(MainWindow);
        actionOpenMarkInterface->setObjectName(QString::fromUtf8("actionOpenMarkInterface"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("ico/laser_wip_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenMarkInterface->setIcon(icon4);
        actionOpenCameraInterface = new QAction(MainWindow);
        actionOpenCameraInterface->setObjectName(QString::fromUtf8("actionOpenCameraInterface"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("ico/camera_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenCameraInterface->setIcon(icon5);
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("ico/_selection_tool_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect->setIcon(icon6);
        actionDrawLine = new QAction(MainWindow);
        actionDrawLine->setObjectName(QString::fromUtf8("actionDrawLine"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("ico/line_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawLine->setIcon(icon7);
        actionDrawRectangle = new QAction(MainWindow);
        actionDrawRectangle->setObjectName(QString::fromUtf8("actionDrawRectangle"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("ico/rectangle_shape_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawRectangle->setIcon(icon8);
        actionDrawRoundedCornerRectangle = new QAction(MainWindow);
        actionDrawRoundedCornerRectangle->setObjectName(QString::fromUtf8("actionDrawRoundedCornerRectangle"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("ico/rectangleCircle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawRoundedCornerRectangle->setIcon(icon9);
        actionDrawTriangle = new QAction(MainWindow);
        actionDrawTriangle->setObjectName(QString::fromUtf8("actionDrawTriangle"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("ico/shape_triangle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawTriangle->setIcon(icon10);
        actionDrawCircle = new QAction(MainWindow);
        actionDrawCircle->setObjectName(QString::fromUtf8("actionDrawCircle"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("ico/circle_oval_shape_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawCircle->setIcon(icon11);
        actionDrawEllipse = new QAction(MainWindow);
        actionDrawEllipse->setObjectName(QString::fromUtf8("actionDrawEllipse"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("ico/ellipse_adobe illustrator tool_circle_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawEllipse->setIcon(icon12);
        actionDrawPolygon = new QAction(MainWindow);
        actionDrawPolygon->setObjectName(QString::fromUtf8("actionDrawPolygon"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("ico/linearray_lines_shape_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDrawPolygon->setIcon(icon13);
        actionGrabOnce = new QAction(MainWindow);
        actionGrabOnce->setObjectName(QString::fromUtf8("actionGrabOnce"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("ico/grabOnce_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrabOnce->setIcon(icon14);
        actionGrabContinue = new QAction(MainWindow);
        actionGrabContinue->setObjectName(QString::fromUtf8("actionGrabContinue"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("ico/grabContinue_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrabContinue->setIcon(icon15);
        actionGrabStop = new QAction(MainWindow);
        actionGrabStop->setObjectName(QString::fromUtf8("actionGrabStop"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("ico/grabStop_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGrabStop->setIcon(icon16);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        page->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        graphicsView_Mark = new QGraphicsView(page);
        graphicsView_Mark->setObjectName(QString::fromUtf8("graphicsView_Mark"));

        horizontalLayout_2->addWidget(graphicsView_Mark);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_3 = new QHBoxLayout(page_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        graphicsView_Camera = new ExtendQGraphicsView(page_2);
        graphicsView_Camera->setObjectName(QString::fromUtf8("graphicsView_Camera"));

        horizontalLayout_3->addWidget(graphicsView_Camera);

        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        stackedWidget_Parameters = new QStackedWidget(centralwidget);
        stackedWidget_Parameters->setObjectName(QString::fromUtf8("stackedWidget_Parameters"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_2 = new QLabel(page_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 29, 16));
        stackedWidget_Parameters->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        tabWidget = new QTabWidget(page_4);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(40, 490, 401, 281));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::East);
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        groupBox = new QGroupBox(tab_1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 321, 121));
        horizontalLayout_8 = new QHBoxLayout(groupBox);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_AutoThreshold = new QCheckBox(groupBox);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(checkBox_AutoThreshold);
        checkBox_AutoThreshold->setObjectName(QString::fromUtf8("checkBox_AutoThreshold"));

        horizontalLayout_6->addWidget(checkBox_AutoThreshold);

        checkBox_ManualThreshold = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_ManualThreshold);
        checkBox_ManualThreshold->setObjectName(QString::fromUtf8("checkBox_ManualThreshold"));
        checkBox_ManualThreshold->setChecked(true);

        horizontalLayout_6->addWidget(checkBox_ManualThreshold);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        spinBox_LeftThreshold = new QSpinBox(groupBox);
        spinBox_LeftThreshold->setObjectName(QString::fromUtf8("spinBox_LeftThreshold"));
        spinBox_LeftThreshold->setAlignment(Qt::AlignCenter);
        spinBox_LeftThreshold->setMaximum(254);

        horizontalLayout_7->addWidget(spinBox_LeftThreshold);

        horizontalSlider_Threshold = new QxtSpanSlider(groupBox);
        horizontalSlider_Threshold->setObjectName(QString::fromUtf8("horizontalSlider_Threshold"));
        horizontalSlider_Threshold->setMaximum(255);
        horizontalSlider_Threshold->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_Threshold);

        spinBox_RightThreshold = new QSpinBox(groupBox);
        spinBox_RightThreshold->setObjectName(QString::fromUtf8("spinBox_RightThreshold"));
        spinBox_RightThreshold->setAlignment(Qt::AlignCenter);
        spinBox_RightThreshold->setMinimum(1);
        spinBox_RightThreshold->setMaximum(255);

        horizontalLayout_7->addWidget(spinBox_RightThreshold);

        horizontalLayout_7->setStretch(0, 2);
        horizontalLayout_7->setStretch(1, 6);
        horizontalLayout_7->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        groupBox_CameraInfo = new QGroupBox(page_4);
        groupBox_CameraInfo->setObjectName(QString::fromUtf8("groupBox_CameraInfo"));
        groupBox_CameraInfo->setGeometry(QRect(100, 60, 351, 111));
        horizontalLayout_9 = new QHBoxLayout(groupBox_CameraInfo);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        comboBox_CameraInfo = new QComboBox(groupBox_CameraInfo);
        comboBox_CameraInfo->setObjectName(QString::fromUtf8("comboBox_CameraInfo"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_CameraInfo->sizePolicy().hasHeightForWidth());
        comboBox_CameraInfo->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(comboBox_CameraInfo);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        checkBox_AutoExposure = new QCheckBox(groupBox_CameraInfo);
        checkBox_AutoExposure->setObjectName(QString::fromUtf8("checkBox_AutoExposure"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_AutoExposure->sizePolicy().hasHeightForWidth());
        checkBox_AutoExposure->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(checkBox_AutoExposure);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label = new QLabel(groupBox_CameraInfo);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(label);

        doubleSpinBox_Exposure = new QDoubleSpinBox(groupBox_CameraInfo);
        doubleSpinBox_Exposure->setObjectName(QString::fromUtf8("doubleSpinBox_Exposure"));
        doubleSpinBox_Exposure->setAlignment(Qt::AlignCenter);
        doubleSpinBox_Exposure->setDecimals(1);
        doubleSpinBox_Exposure->setMaximum(99999999.000000000000000);
        doubleSpinBox_Exposure->setSingleStep(1.000000000000000);

        horizontalLayout_5->addWidget(doubleSpinBox_Exposure);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_CameraInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_FrameRate = new QLineEdit(groupBox_CameraInfo);
        lineEdit_FrameRate->setObjectName(QString::fromUtf8("lineEdit_FrameRate"));
        sizePolicy2.setHeightForWidth(lineEdit_FrameRate->sizePolicy().hasHeightForWidth());
        lineEdit_FrameRate->setSizePolicy(sizePolicy2);
        lineEdit_FrameRate->setAlignment(Qt::AlignCenter);
        lineEdit_FrameRate->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_FrameRate);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_9->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_ConnectedCamera = new QPushButton(groupBox_CameraInfo);
        pushButton_ConnectedCamera->setObjectName(QString::fromUtf8("pushButton_ConnectedCamera"));

        verticalLayout_2->addWidget(pushButton_ConnectedCamera);

        pushButton_DisConnectedCamera = new QPushButton(groupBox_CameraInfo);
        pushButton_DisConnectedCamera->setObjectName(QString::fromUtf8("pushButton_DisConnectedCamera"));

        verticalLayout_2->addWidget(pushButton_DisConnectedCamera);


        horizontalLayout_9->addLayout(verticalLayout_2);

        groupBox_3 = new QGroupBox(page_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(170, 830, 171, 91));
        groupBox_LoadImage = new QGroupBox(page_4);
        groupBox_LoadImage->setObjectName(QString::fromUtf8("groupBox_LoadImage"));
        groupBox_LoadImage->setGeometry(QRect(100, 180, 351, 58));
        horizontalLayout_11 = new QHBoxLayout(groupBox_LoadImage);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        lineEdit_ImageFilePath = new QLineEdit(groupBox_LoadImage);
        lineEdit_ImageFilePath->setObjectName(QString::fromUtf8("lineEdit_ImageFilePath"));
        lineEdit_ImageFilePath->setReadOnly(true);

        horizontalLayout_10->addWidget(lineEdit_ImageFilePath);

        pushButton_LoadImage = new QPushButton(groupBox_LoadImage);
        pushButton_LoadImage->setObjectName(QString::fromUtf8("pushButton_LoadImage"));

        horizontalLayout_10->addWidget(pushButton_LoadImage);


        horizontalLayout_11->addLayout(horizontalLayout_10);

        stackedWidget_Parameters->addWidget(page_4);

        horizontalLayout->addWidget(stackedWidget_Parameters);

        horizontalLayout->setStretch(0, 7);
        horizontalLayout->setStretch(1, 3);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar_Tool = new QToolBar(MainWindow);
        toolBar_Tool->setObjectName(QString::fromUtf8("toolBar_Tool"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_Tool);
        toolBar_Shapes = new QToolBar(MainWindow);
        toolBar_Shapes->setObjectName(QString::fromUtf8("toolBar_Shapes"));
        MainWindow->addToolBar(Qt::BottomToolBarArea, toolBar_Shapes);
        toolBar_Camera = new QToolBar(MainWindow);
        toolBar_Camera->setObjectName(QString::fromUtf8("toolBar_Camera"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_Camera);

        toolBar_Tool->addAction(actionOpenFile);
        toolBar_Tool->addAction(actionSaveFile);
        toolBar_Tool->addSeparator();
        toolBar_Tool->addAction(actionUndo);
        toolBar_Tool->addAction(actionRedo);
        toolBar_Tool->addSeparator();
        toolBar_Tool->addAction(actionOpenMarkInterface);
        toolBar_Tool->addAction(actionOpenCameraInterface);
        toolBar_Shapes->addAction(actionSelect);
        toolBar_Shapes->addAction(actionDrawLine);
        toolBar_Shapes->addAction(actionDrawRectangle);
        toolBar_Shapes->addAction(actionDrawRoundedCornerRectangle);
        toolBar_Shapes->addAction(actionDrawTriangle);
        toolBar_Shapes->addAction(actionDrawCircle);
        toolBar_Shapes->addAction(actionDrawEllipse);
        toolBar_Shapes->addAction(actionDrawPolygon);
        toolBar_Camera->addAction(actionGrabOnce);
        toolBar_Camera->addAction(actionGrabContinue);
        toolBar_Camera->addAction(actionGrabStop);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);
        stackedWidget_Parameters->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpenFile->setText(QApplication::translate("MainWindow", "OpenFile", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenFile->setToolTip(QApplication::translate("MainWindow", "open file from the disk", nullptr));
#endif // QT_NO_TOOLTIP
        actionSaveFile->setText(QApplication::translate("MainWindow", "SaveFile", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSaveFile->setToolTip(QApplication::translate("MainWindow", "save file to disk", nullptr));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionUndo->setToolTip(QApplication::translate("MainWindow", "return last action", nullptr));
#endif // QT_NO_TOOLTIP
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", nullptr));
#ifndef QT_NO_TOOLTIP
        actionRedo->setToolTip(QApplication::translate("MainWindow", "forward next action", nullptr));
#endif // QT_NO_TOOLTIP
        actionOpenMarkInterface->setText(QApplication::translate("MainWindow", "OpenMarkInterface", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenMarkInterface->setToolTip(QApplication::translate("MainWindow", "open the laser marking interface", nullptr));
#endif // QT_NO_TOOLTIP
        actionOpenCameraInterface->setText(QApplication::translate("MainWindow", "OpenCameraInterface", nullptr));
#ifndef QT_NO_TOOLTIP
        actionOpenCameraInterface->setToolTip(QApplication::translate("MainWindow", "open the vision interface", nullptr));
#endif // QT_NO_TOOLTIP
        actionSelect->setText(QApplication::translate("MainWindow", "Select", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSelect->setToolTip(QApplication::translate("MainWindow", "select a shape(no draw)", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawLine->setText(QApplication::translate("MainWindow", "DrawLine", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawLine->setToolTip(QApplication::translate("MainWindow", "draw a line", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawRectangle->setText(QApplication::translate("MainWindow", "DrawRectangle", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawRectangle->setToolTip(QApplication::translate("MainWindow", "draw a rectangle", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawRoundedCornerRectangle->setText(QApplication::translate("MainWindow", "DrawRoundedCornerRectangle", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawRoundedCornerRectangle->setToolTip(QApplication::translate("MainWindow", "Draw a RoundedCornerRectangle", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawTriangle->setText(QApplication::translate("MainWindow", "DrawTriangle", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawTriangle->setToolTip(QApplication::translate("MainWindow", "Draw a Triangle", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawCircle->setText(QApplication::translate("MainWindow", "DrawCircle", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawCircle->setToolTip(QApplication::translate("MainWindow", "Draw a Circle", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawEllipse->setText(QApplication::translate("MainWindow", "DrawEllipse", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawEllipse->setToolTip(QApplication::translate("MainWindow", "Draw a Ellipse", nullptr));
#endif // QT_NO_TOOLTIP
        actionDrawPolygon->setText(QApplication::translate("MainWindow", "DrawPolygon", nullptr));
#ifndef QT_NO_TOOLTIP
        actionDrawPolygon->setToolTip(QApplication::translate("MainWindow", "Draw a Polygon", nullptr));
#endif // QT_NO_TOOLTIP
        actionGrabOnce->setText(QApplication::translate("MainWindow", "GrabOnce", nullptr));
#ifndef QT_NO_TOOLTIP
        actionGrabOnce->setToolTip(QApplication::translate("MainWindow", "Grab Once", nullptr));
#endif // QT_NO_TOOLTIP
        actionGrabContinue->setText(QApplication::translate("MainWindow", "GrabContinue", nullptr));
#ifndef QT_NO_TOOLTIP
        actionGrabContinue->setToolTip(QApplication::translate("MainWindow", "Grab Continue", nullptr));
#endif // QT_NO_TOOLTIP
        actionGrabStop->setText(QApplication::translate("MainWindow", "GrabStop", nullptr));
#ifndef QT_NO_TOOLTIP
        actionGrabStop->setToolTip(QApplication::translate("MainWindow", "Grab Stop", nullptr));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("MainWindow", "mark1", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Threshold", nullptr));
        checkBox_AutoThreshold->setText(QApplication::translate("MainWindow", "Auto", nullptr));
        checkBox_ManualThreshold->setText(QApplication::translate("MainWindow", "Manual", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Image Process", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Calibration", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Egde Finder", nullptr));
        groupBox_CameraInfo->setTitle(QApplication::translate("MainWindow", "Camera Info", nullptr));
        checkBox_AutoExposure->setText(QApplication::translate("MainWindow", "AutoExposure", nullptr));
        label->setText(QApplication::translate("MainWindow", "Exposure:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Frame Rate:", nullptr));
        pushButton_ConnectedCamera->setText(QApplication::translate("MainWindow", "Connected", nullptr));
        pushButton_DisConnectedCamera->setText(QApplication::translate("MainWindow", "DisConnected", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Motion", nullptr));
        groupBox_LoadImage->setTitle(QApplication::translate("MainWindow", "Load Image", nullptr));
        pushButton_LoadImage->setText(QApplication::translate("MainWindow", "load Image", nullptr));
        toolBar_Tool->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_Shapes->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
        toolBar_Camera->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
