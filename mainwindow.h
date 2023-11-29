#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtimer.h>
#include <qlabel.h>
#include <qdatetime.h>

#include "GlobalDef.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QMutex>
#include <QTextStream>

#include "ImageConvert.h"

#include <BaslerCamera.h>
#include <OpenCVLibrary.h>

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

	void on_pushButton_LoadImage_clicked();

	void on_spinBox_LeftThreshold_valueChanged(int arg1);

	void on_spinBox_RightThreshold_valueChanged(int arg1);

    void on_pushButton_MorphologicalOperations_clicked();

    void on_comboBox_KernelShape_currentIndexChanged(int index);

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
	// 阈值分割
	void ThresholdImage(bool autoFlag);

public:
	// 记录日志
	static void Logging(QtMsgType type, const QMessageLogContext& context, const QString& str);

signals:
	void ShowImageSignal(const QPixmap& img);

private:
	Ui::MainWindow* ui;
	QTimer* timer; // 定时器，用于在状态栏显示系统时间
	BaslerCamera* m_Camera; // 相机对象
	ImageEventHandler* m_ImageEventHandler; // 图像事件处理器
	ImageEventHandler::ImageCallback m_ImageCallback; // 图像回调函数

	QImage m_ptrGrabResult; // 图像缓冲区,用于存储图像
	cv::Mat m_cvImage; // opencv图像缓冲区,用于存储经过opencv处理后的图像，便于多个处理方法对于同一个图像的处理

	bool isAutoExposure = false; // 是否自动曝光
	QTimer* timer_Exposure; // 定时器，用于获取自动曝光时的曝光时间和帧率

	QString EXEPath; // 程序所在路径

	bool hasPicture = false; // 是否有图片
#if USEOPENCV
	OpenCVLibrary* m_ImageProcess; // 图像处理对象
#endif
};
#endif // MAINWINDOW_H
