#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	EXEPath = QCoreApplication::applicationDirPath(); // 获取当前程序的路径

	InitConnect();
	InitUI();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::InitUI()
{
	ui->actionOpenMarkInterface->setVisible(false); // 隐藏打开激光界面的按钮
	ui->toolBar_Camera->setVisible(false); // 隐藏相机工具栏
	ui->stackedWidget->setCurrentIndex(0); // 切换到激光界面
	ui->stackedWidget_Parameters->setCurrentIndex(0); // 切换到激光参数界面

	ui->horizontalSlider_Threshold->setLowerValue(0); // 设置滑动条的左边值
	ui->horizontalSlider_Threshold->setUpperValue(255); // 设置滑动条的右边值

	InitStatusBar(); // 初始化状态栏

	ui->checkBox_AutoExposure->setEnabled(false); // 设置自动曝光为不可用
}

void MainWindow::InitConnect()
{
	// 连接左阈值的值改变信号与滑动条的左边值改变槽函数
	connect(ui->spinBox_LeftThreshold, QOverload<int>::of(&QSpinBox::valueChanged), ui->horizontalSlider_Threshold, &QxtSpanSlider::setLowerValue);
	// 连接滑动条的左边值改变信号与左阈值的值改变槽函数
	connect(ui->horizontalSlider_Threshold, &QxtSpanSlider::lowerValueChanged, ui->spinBox_LeftThreshold, &QSpinBox::setValue);
	// 连接右阈值的值改变信号与滑动条的右边值改变槽函数
	connect(ui->spinBox_RightThreshold, QOverload<int>::of(&QSpinBox::valueChanged), ui->horizontalSlider_Threshold, &QxtSpanSlider::setUpperValue);
	// 连接滑动条的右边值改变信号与右阈值的值改变槽函数
	connect(ui->horizontalSlider_Threshold, &QxtSpanSlider::upperValueChanged, ui->spinBox_RightThreshold, &QSpinBox::setValue);

	connect(this, &MainWindow::ShowImageSignal, ui->graphicsView_Camera, &ExtendQGraphicsView::ShowImage); // 连接显示图像信号与显示图像槽函数
	connect(ui->pushButton_ConnectedCamera, &QPushButton::clicked, this, [&]() {
		ui->doubleSpinBox_Exposure->setValue(m_Camera->GetExposureTime()); // 获取曝光时间
		});
}

void MainWindow::InitStatusBar()
{
	timer = new QTimer(this); // 创建定时器
	// 添加右对齐的Label到状态栏
	QLabel* rightAlignedLabel = new QLabel(this);
	rightAlignedLabel->setAlignment(Qt::AlignRight); // 设置右对齐
	statusBar()->addPermanentWidget(rightAlignedLabel); // 添加到状态栏
	// 修改字体大小和颜色
	ui->statusbar->findChild<QLabel*>()->setStyleSheet("font-size: 20px; color: rgb(0, 0, 0)");
	connect(timer, &QTimer::timeout, this, [&]()
		{
			// 设置状态栏的时间
			ui->statusbar->findChild<QLabel*>()->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
		});
	timer->start(1000); // 启动定时器
}

void MainWindow::InitCamera()
{
	m_Camera = new BaslerCamera(); // 创建相机对象
	auto cameraDevices = m_Camera->GetCameraDevices(); // 获取相机设备
	if (cameraDevices.empty()) { // 如果相机设备为空
		QMessageBox::warning(this, "Warning", "No camera device found!"); // 弹出警告对话框
		return;
	}
	else {
		// 添加相机设备到下拉框
		for (auto& cameraDevice : cameraDevices) {
			ui->comboBox_CameraInfo->addItem(cameraDevice.c_str());
		}
	}
}

void MainWindow::ShowImage(const CGrabResultPtr& ptrGrabResult)
{
	if (ptrGrabResult->GrabSucceeded()) {
		QImage img = ConvertBalserToQImage(ptrGrabResult); // 将Basler图像原始数据转换为QImage
		m_ptrGrabResult = img.copy(); // 将QImage赋值给图像缓冲区
		emit ShowImageSignal(QPixmap::fromImage(img)); // 发送显示图像信号
	}
}

QImage MainWindow::ConvertBalserToQImage(const CGrabResultPtr& ptrGrabResult)
{
	return QImage((uchar*)ptrGrabResult->GetBuffer(), ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), QImage::Format_Grayscale8);
}


void MainWindow::on_actionOpenCameraInterface_triggered()
{
	ui->toolBar_Camera->setVisible(true); // 显示相机工具栏
	ui->actionOpenMarkInterface->setVisible(true); // 显示打开激光界面的按钮
	ui->actionOpenCameraInterface->setVisible(false); // 隐藏打开相机界面的按钮
	ui->stackedWidget->setCurrentIndex(1); // 切换到相机界面
	ui->toolBar_Shapes->setVisible(false); // 隐藏形状工具栏
	ui->actionGrabOnce->setEnabled(false); // 设置抓取一次按钮为不可用
	ui->actionGrabContinue->setEnabled(false); // 设置连续抓取按钮为不可用
	ui->actionGrabStop->setEnabled(false); // 设置停止抓取按钮为不可用
	ui->stackedWidget_Parameters->setCurrentIndex(1); // 切换到相机参数界面
	ui->pushButton_DisConnectedCamera->setEnabled(false); // 设置断开相机按钮为不可用

	if (USECAMERA) {
		ui->groupBox_CameraInfo->setVisible(true); // 显示相机信息组合框
		InitCamera();
	}
	else {
		ui->groupBox_CameraInfo->setVisible(false); // 隐藏相机信息组合框
	}
}


void MainWindow::on_actionOpenMarkInterface_triggered()
{
	ui->toolBar_Camera->setVisible(false); // 隐藏相机工具栏
	ui->actionOpenMarkInterface->setVisible(false); // 隐藏打开激光界面的按钮
	ui->actionOpenCameraInterface->setVisible(true); // 显示打开相机界面的按钮
	ui->stackedWidget->setCurrentIndex(0); // 切换到激光界面
	ui->toolBar_Shapes->setVisible(true); // 显示形状工具栏
	ui->stackedWidget_Parameters->setCurrentIndex(0); // 切换到激光参数界面
}


void MainWindow::on_checkBox_AutoThreshold_clicked()
{
	ui->spinBox_LeftThreshold->setReadOnly(true); // 设置左阈值为只读
	ui->spinBox_RightThreshold->setReadOnly(true); // 设置右阈值为只读
	ui->horizontalSlider_Threshold->setEnabled(false); // 设置滑动条为不可用
}


void MainWindow::on_checkBox_ManualThreshold_clicked()
{
	ui->spinBox_LeftThreshold->setReadOnly(false); // 设置左阈值为可读写
	ui->spinBox_RightThreshold->setReadOnly(false); // 设置右阈值为可读写
	ui->horizontalSlider_Threshold->setEnabled(true); // 设置滑动条为可用
}


void MainWindow::on_actionGrabOnce_triggered()
{
	m_Camera->StartCapture(0); // 抓取一次
}


void MainWindow::on_actionGrabContinue_triggered()
{
	m_Camera->StartCapture(1); // 连续抓取

	ui->actionGrabOnce->setEnabled(false); // 设置抓取一次按钮为不可用
	ui->actionGrabContinue->setEnabled(false); // 设置连续抓取按钮为不可用
	ui->actionGrabStop->setEnabled(true); // 设置停止抓取按钮为可用
}


void MainWindow::on_actionGrabStop_triggered()
{
	m_Camera->StopCapture(); // 停止抓取

	ui->actionGrabOnce->setEnabled(true); // 设置抓取一次按钮为可用
	ui->actionGrabContinue->setEnabled(true); // 设置连续抓取按钮为可用
	ui->actionGrabStop->setEnabled(false); // 设置停止抓取按钮为不可用
}


void MainWindow::on_pushButton_ConnectedCamera_clicked()
{
	if (!(m_Camera->ConnectedCamera(ui->comboBox_CameraInfo->currentIndex()))) // 连接相机
	{
		return;
	}
	m_ImageCallback = [&](const CGrabResultPtr& ptrGrabResult)
		{
			ShowImage(ptrGrabResult);
		};
	m_ImageEventHandler = new ImageEventHandler(m_ImageCallback);
	m_Camera->RegisterImageEvent(m_ImageEventHandler); // 注册图像事件处理器

	ui->actionGrabOnce->setEnabled(true); // 设置抓取一次按钮为可用
	ui->actionGrabContinue->setEnabled(true); // 设置连续抓取按钮为可用
	ui->pushButton_ConnectedCamera->setEnabled(false); // 设置连接相机按钮为不可用
	ui->pushButton_DisConnectedCamera->setEnabled(true); // 设置断开相机按钮为可用
	ui->checkBox_AutoExposure->setEnabled(true); // 设置自动曝光为可用
}


void MainWindow::on_pushButton_DisConnectedCamera_clicked()
{
	if (!(m_Camera->DisConnectedCamera())) // 断开相机失败
	{
		return;
	}
	if (m_ImageEventHandler != nullptr)
	{
		m_Camera->DeregisterImageEvent(m_ImageEventHandler); // 注销图像事件处理器
		m_ImageEventHandler = nullptr;
		delete m_ImageEventHandler;
	}

	isAutoExposure = false;
	ui->actionGrabStop->trigger(); // 触发停止抓取按钮
	ui->actionGrabOnce->setEnabled(false); // 设置抓取一次按钮为不可用
	ui->actionGrabContinue->setEnabled(false); // 设置连续抓取按钮为不可用
	ui->pushButton_ConnectedCamera->setEnabled(true); // 设置连接相机按钮为可用
	ui->pushButton_DisConnectedCamera->setEnabled(false); // 设置断开相机按钮为不可用
	ui->checkBox_AutoExposure->setEnabled(false); // 设置自动曝光为不可用
}


void MainWindow::on_doubleSpinBox_Exposure_valueChanged(double arg1)
{
	if (arg1 < 100) { return; }
	if (!isAutoExposure) {
		m_Camera->SetExposureTime(arg1); // 设置曝光时间
	}

	ui->lineEdit_FrameRate->setText(QString::number(m_Camera->GetFrameRate(), 'f', 1) + " FPS"); // 获取帧率
}


void MainWindow::on_checkBox_AutoExposure_stateChanged(int arg1)
{
	isAutoExposure = arg1; // 获取自动曝光的状态
	ui->doubleSpinBox_Exposure->setReadOnly(arg1); // 设置曝光时间为只读/可读写
	m_Camera->SetAutoExposure(arg1); // 设置自动曝光

	if (isAutoExposure) {
		timer_Exposure = new QTimer(this); // 创建定时器
		connect(timer_Exposure, &QTimer::timeout, this, [&]() {
			ui->doubleSpinBox_Exposure->setValue(m_Camera->GetExposureTime()); // 获取曝光时间
			ui->lineEdit_FrameRate->setText(QString::number(m_Camera->GetFrameRate(), 'f', 1) + " FPS"); // 获取帧率
			});
		timer_Exposure->start(1000); // 启动定时器
	}
	else {
		timer_Exposure->stop(); // 停止定时器
		delete timer_Exposure; // 删除定时器
	}
}


void MainWindow::on_pushButton_LoadImage_clicked()
{
	QString imgPath;
	QSettings settings(EXEPath + "./Config.ini", QSettings::IniFormat); // 创建配置文件对象
	QString lastPath = settings.value("LastPath").toString(); // 获取上次打开的路径
	imgPath = QFileDialog::getOpenFileName(this, tr("Load Image"), lastPath, tr("Image Files(*.bmp *.png *.jpg);;All(*.*)"));
	if (imgPath != "")
	{
		ui->lineEdit_ImageFilePath->setText(imgPath);
		QImage img(imgPath);
		m_ptrGrabResult = img.copy(); // 将QImage赋值给图像缓冲区
		ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(img));
		settings.setValue("LastPath", imgPath); // 保存上次打开的路径
	}
	else
	{
		return;
	}
}

