#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtimer.h>
#include <qlabel.h>
#include <qdatetime.h>

#include "GlobalDef.h"
#include <QMessageBox>

#include <BaslerCamera.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void on_actionOpenCameraInterface_triggered();

	void on_actionOpenMarkInterface_triggered();

	void on_checkBox_AutoThreshold_clicked();

	void on_checkBox_ManualThreshold_clicked();

	void on_actionGrabOnce_triggered();

	void on_actionGrabContinue_triggered();

	void on_actionGrabStop_triggered();

	void on_pushButton_ConnectedCamera_clicked();

	void on_pushButton_DisConnectedCamera_clicked();

    void on_doubleSpinBox_Exposure_valueChanged(double arg1);

    void on_checkBox_AutoExposure_stateChanged(int arg1);

private:
	// 初始化UI
	void InitUI();
	// 初始化一些槽连接
	void InitConnect();
	// 状态栏操作
	void InitStatusBar();
	// 初始化相机
	void InitCamera();
	// 显示图像
	void ShowImage(const CGrabResultPtr& ptrGrabResult);
	// 图像转换
	QImage ConvertBalserToQImage(const CGrabResultPtr& ptrGrabResult);

signals:
	void ShowImageSignal(const QPixmap& img);

private:
	Ui::MainWindow* ui;
	QTimer* timer; // 定时器，用于在状态栏显示系统时间
	BaslerCamera* m_Camera; // 相机对象
	ImageEventHandler* m_ImageEventHandler; // 图像事件处理器
	ImageEventHandler::ImageCallback m_ImageCallback; // 图像回调函数

	bool isAutoExposure = false; // 是否自动曝光
	QTimer* timer_Exposure; // 定时器，用于获取自动曝光时的曝光时间和帧率
};
#endif // MAINWINDOW_H
