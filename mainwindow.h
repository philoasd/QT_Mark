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

#if USEOPENCV
#include <OpenCVLibrary.h>
#endif

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

	void on_pushButton_ImageRotation_clicked();

	void on_pushButton_RunImageEnhancement_clicked();

	void on_comboBox_ImageEnhancementMethods_currentIndexChanged(int index);

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
	/// <summary>
	/// 保存配置
	/// </summary>
	/// <param name="valueName">配置名</param>
	/// <param name="value">配置值</param>
	/// <param name="groupName">配置组（如果没有，则为默认）</param>
	void SaveConfig(QString valueName, QVariant value, QString groupName = "");
	/// <summary>
	/// 加载配置
	/// </summary>
	/// <param name="valueName">配置名</param>
	/// <param name="groupName">>配置组（如果没有，则为默认）</param>
	/// <returns></returns>
	QVariant LoadConfig(QString valueName, QString groupName = "");

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

#pragma region 图像变量
	enum ImageProcessStep
	{
		none = 0, // 无操作
		loadImage, // 加载图像
		threshold, // 阈值分割
		morphological, // 形态学操作
		rotate, // 旋转
		enhancement, // 增强
		denoising // 去噪
	}m_ImageProcessStep; // 图像处理步骤

	cv::Mat m_ImageProcessResult[6]; // 图像处理结果：0-原图，1-阈值分割，2-形态学操作，3-旋转，4-增强，5-去噪
#pragma endregion

	bool isAutoExposure = false; // 是否自动曝光
	QTimer* timer_Exposure; // 定时器，用于获取自动曝光时的曝光时间和帧率

	QString EXEPath; // 程序所在路径

#if USEOPENCV
	OpenCVLibrary* m_ImageProcess; // 图像处理对象
#endif
};
#endif // MAINWINDOW_H
