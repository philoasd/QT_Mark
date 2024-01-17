#pragma execution_character_set("utf-8")

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	EXEPath = QCoreApplication::applicationDirPath(); // 获取当前程序的路径
	qInstallMessageHandler(Logging); // 安装日志记录函数

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

	m_ImageProcessStep = ImageProcessStep::none; // 设置图像处理步骤为无

	ui->horizontalSlider_Threshold->setLowerValue(0); // 设置滑动条的左边值
	ui->horizontalSlider_Threshold->setUpperValue(255); // 设置滑动条的右边值

	InitStatusBar(); // 初始化状态栏

	ui->checkBox_AutoExposure->setEnabled(false); // 设置自动曝光为不可用
	m_ImageProcessResult.resize(6); // 设置图像处理结果的大小
	ui->doubleSpinBox_GammaValue->setVisible(false); // 隐藏gamma值

	qDebug("app start!!!");
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
		QImage img = ImageConvert::ConvertBalserToQImage(ptrGrabResult); // 将Basler图像原始数据转换为QImage
		m_ImageProcessResult[0] = img; // 将QImage赋值给图像缓冲区
		emit ShowImageSignal(QPixmap::fromImage(img)); // 发送显示图像信号
		m_ImageProcessStep = ImageProcessStep::loadImage; // 设置图像处理步骤为加载图像
	}
}

void MainWindow::ThresholdImage(bool autoFlag)
{
	if (m_ImageProcessStep != ImageProcessStep::none) {
		int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤

		if (autoFlag) {
			m_ImageProcessResult[1] = ImageConvert::ConverMatToQImage(m_ImageProcess->AutoThreshold(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[0]))); // 自动阈值分割
		}
		else {
			m_ImageProcessResult[1] = ImageConvert::ConverMatToQImage(m_ImageProcess->Threshold(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[0]), ui->spinBox_LeftThreshold->value(), ui->spinBox_RightThreshold->value())); // 手动阈值分割
		}

		if ((ui->spinBox_LeftThreshold->value() == 0) && (ui->spinBox_RightThreshold->value() == 255) && !autoFlag) {
			// 如果左阈值为0，右阈值为255，则显示原图
			ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[0]));
		}
		else {
			// 显示阈值图像
			ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[1]));
		}

		m_ImageProcessStep = ImageProcessStep::threshold; // 设置图像处理步骤为阈值分割
	}
}

void MainWindow::SaveConfig(QString valueName, QVariant value, QString groupName)
{
	QSettings settings(EXEPath + "./Config.ini", QSettings::IniFormat); // 创建配置文件对象

	if (groupName != "") {
		settings.beginGroup(groupName); // 开始组
	}
	settings.setValue(valueName, value); // 保存值
	if (groupName != "") {
		settings.endGroup(); // 结束组
	}
}

QVariant MainWindow::LoadConfig(QString valueName, QString groupName)
{
	QSettings settings(EXEPath + "./Config.ini", QSettings::IniFormat); // 创建配置文件对象
	if (groupName != "") {
		settings.beginGroup(groupName); // 开始组
	}
	QVariant value = settings.value(valueName).toString(); // 获取上次打开的路径
	if (groupName != "") {
		settings.endGroup(); // 结束组
	}
	return value;
}

void MainWindow::Logging(QtMsgType type, const QMessageLogContext& context, const QString& str)
{
	static QMutex mutex;
	mutex.lock(); // 上锁

	QString text;
	switch (type) {
	case QtDebugMsg: {
		text = QString("(Debug): ");
		break;
	}
	case QtWarningMsg: {
		text = QString("(Warning): ");
		break;
	}
	case QtCriticalMsg: {
		text = QString("(Critical): ");
		break;
	}
	case QtFatalMsg: {
		text = QString("(Fatal): ");
		break;
	}
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line); // 输出信息的文件名和行数
	// 输出当前的日期和时间
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString fileName = QCoreApplication::applicationDirPath() + "/Log/" + QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
	QString current_date = QString("%1").arg(current_date_time);

	QString message = QString("%1 %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(str); // 最终要输出的信息

	QFile file(fileName); // 创建日志文件对象
	QDir dir;
	// 如果日志文件夹不存在，则创建
	if (!dir.exists(QFileInfo(fileName).path())) {
		dir.mkpath(QFileInfo(fileName).path()); // 创建日志文件夹
	}
	file.open(QIODevice::WriteOnly | QIODevice::Append); // 以只写的方式打开日志文件

	QTextStream text_stream(&file); // 创建文本流对象
	text_stream << message << "\r\n"; // 将信息写入文本流
	file.flush(); // 将信息刷新到文件中
	file.close(); // 关闭文件

	mutex.unlock(); // 解锁
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

#if USECAMERA
	ui->groupBox_CameraInfo->setEnabled(true); // 显示相机信息组合框
	InitCamera();
#else
	ui->groupBox_CameraInfo->setEnabled(false); // 隐藏相机信息组合框
#endif

#if USEOPENCV
	m_ImageProcess = new OpenCVLibrary(); // 创建OpenCV图像处理对象
#elif

#endif
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

	ThresholdImage(true); // 自动阈值分割
}


void MainWindow::on_checkBox_ManualThreshold_clicked()
{
	ui->spinBox_LeftThreshold->setReadOnly(false); // 设置左阈值为可读写
	ui->spinBox_RightThreshold->setReadOnly(false); // 设置右阈值为可读写
	ui->horizontalSlider_Threshold->setEnabled(true); // 设置滑动条为可用

	ThresholdImage(false); // 手动阈值分割
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
	QString LastOpenImagePath = LoadConfig("LastOpenImagePath").toString(); // 获取上次打开的路径
	imgPath = QFileDialog::getOpenFileName(this, tr("Load Image"), LastOpenImagePath, tr("Image Files(*.bmp *.png *.jpg);;All(*.*)"));
	if (imgPath != "")
	{
		ui->lineEdit_ImageFilePath->setText(imgPath);
		QImage img(imgPath);
		m_ImageProcessResult[0] = img; // 将QImage赋值给图像缓冲区
		m_ImageProcessStep = ImageProcessStep::loadImage; // 设置图像处理步骤为加载图像
		ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[0]));
		SaveConfig("LastOpenImagePath", imgPath); // 保存上次打开的路径
		ui->checkBox_ManualThreshold->setChecked(true);
	}
	else
	{
		return;
	}
}


void MainWindow::on_spinBox_LeftThreshold_valueChanged(int arg1)
{
	ThresholdImage(false); // 手动阈值分割
}


void MainWindow::on_spinBox_RightThreshold_valueChanged(int arg1)
{
	ThresholdImage(false); // 手动阈值分割
}


void MainWindow::on_pushButton_MorphologicalOperations_clicked()
{
	//if (m_ImageProcessResult[1].isNull()) // 如果阈值图像为空
	//{
	//	QMessageBox::critical(this, "Error", "need to threshold the image!!!"); // 弹出警告对话框
	//	return;
	//}
	int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤

	switch (ui->comboBox_MorphologicalOperations->currentIndex())
	{
	case 0: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Dilate(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 膨胀
		break;
	}
	case 1: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Erode(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 腐蚀
		break;
	}
	case 2: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Open(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 开运算
		break;
	}
	case 3: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Close(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 闭运算
		break;
	}
	case 4: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Gradient(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 形态学梯度
		break;
	}
	case 5: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->TopHat(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 顶帽
		break;
	}
	case 6: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->BlackHat(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 黑帽
		break;
	}
	case 7: {
		m_ImageProcessResult[2] = ImageConvert::ConverMatToQImage(m_ImageProcess->Hitmiss(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value())); // 骨架
		break;
	}
	default: { // 默认显示原图
		m_ImageProcessResult[2] = m_ImageProcessResult[currentStep - 1];
		break;
	}
	}

	// 显示形态学图像
	m_ImageProcessStep = ImageProcessStep::morphological; // 设置图像处理步骤为形态学
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[2]));
}


void MainWindow::on_comboBox_KernelShape_currentIndexChanged(int index)
{
	switch (index)
	{
	case 0: {
		m_ImageProcess->morphShape = cv::MORPH_RECT; // 矩形
		break;
	}
	case 1: {
		m_ImageProcess->morphShape = cv::MORPH_CROSS; // 十字形
		break;
	}
	case 2: {
		m_ImageProcess->morphShape = cv::MORPH_ELLIPSE; // 椭圆形
		break;
	}
	}
}


void MainWindow::on_pushButton_ImageRotation_clicked()
{
	int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤
	if (currentStep < 1) // 如果当前图像处理步骤小于1(没有图像)，则返回
	{
		QMessageBox::critical(this, "Error", "need to load image!!!"); // 弹出错误对话框
		return;
	}

	m_ImageProcessResult[3] = ImageConvert::ConverMatToQImage(m_ImageProcess->Rotate(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->doubleSpinBox_AngleRotation->value())); // 旋转图像
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[3])); // 显示旋转后的图像

	m_ImageProcessStep = ImageProcessStep::rotate; // 设置图像处理步骤为旋转
}


void MainWindow::on_pushButton_RunImageEnhancement_clicked()
{
	int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤
	if (currentStep < 1) // 如果当前图像处理步骤小于1(没有图像)，则返回
	{
		QMessageBox::critical(this, "Error", "need to load image!!!"); // 弹出错误对话框
		return;
	}

	cv::Mat enhancedImage;

	switch (ui->comboBox_ImageEnhancementMethods->currentIndex())
	{
	case 0: {
		enhancedImage = m_ImageProcess->EqualizeHist(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1])); // 直方图均衡化
		break;
	}
	case 1: {
		enhancedImage = m_ImageProcess->CLAHE(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1])); // 自适应直方图均衡化
		break;
	}
	case 2: {
		enhancedImage = m_ImageProcess->Laplace(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1])); // 拉普拉斯变换
		break;
	}
	case 3: {
		enhancedImage = m_ImageProcess->Log(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1])); // 对数变换
		break;
	}
	case 4: {
		enhancedImage = m_ImageProcess->Gamma(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->doubleSpinBox_GammaValue->value()); // 对比度拉伸
		break;
	}
	case 5: {
		enhancedImage = m_ImageProcess->Sobel(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1])); // Sobel变换
		break;
	}
	default: {
		enhancedImage = ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]); // 默认显示原图
		break;
	}
	}

	m_ImageProcessResult[4] = ImageConvert::ConverMatToQImage(enhancedImage); // 获取增强后的图像
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[4])); // 显示增强后的图像

	m_ImageProcessStep = ImageProcessStep::enhancement; // 设置图像处理步骤为增强
}


void MainWindow::on_comboBox_ImageEnhancementMethods_currentIndexChanged(int index)
{
	if (index == 4)
	{
		ui->doubleSpinBox_GammaValue->setVisible(true);
	}
	else
	{
		ui->doubleSpinBox_GammaValue->setVisible(false);
	}
}


void MainWindow::on_pushButton_RunImageDenoising_clicked()
{
	int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤
	if (currentStep < 1) // 如果当前图像处理步骤小于1(没有图像)，则返回
	{
		QMessageBox::critical(this, "Error", "need to load image!!!"); // 弹出错误对话框
		return;
	}

	cv::Mat denoisedImage;
	switch (ui->comboBox_ImageDenoisingMethods->currentIndex())
	{
	case 0: {
		denoisedImage = m_ImageProcess->Blur(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 均值滤波
		break;
	}
	case 1: {
		denoisedImage = m_ImageProcess->BoxFilter(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 方框滤波
		break;
	}
	case 2: {
		denoisedImage = m_ImageProcess->MedianBlur(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 中值滤波
		break;
	}
	case 3: {
		denoisedImage = m_ImageProcess->GaussianBlur(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 高斯滤波
		break;
	}
	case 4: {
		denoisedImage = m_ImageProcess->BilateralFilter(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 双边滤波
		break;
	}
	case 5: {
		denoisedImage = m_ImageProcess->NLMeanFilter(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), ui->spinBox_KernelSize->value()); // 非局部均值滤波
		break;
	}
	default: {
		denoisedImage = ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]); // 默认显示原图
		break;
	}
	}

	m_ImageProcessResult[5] = ImageConvert::ConverMatToQImage(denoisedImage); // 获取降噪后的图像
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[5])); // 显示降噪后的图像

	m_ImageProcessStep = ImageProcessStep::denoising; // 设置图像处理步骤为降噪
}


void MainWindow::on_pushButton_LoadTemplateFile_clicked()
{
	QString templateFilePath;
	QString lastOpenTemplateFilePath = LoadConfig("LastOpenImagePath").toString(); // 获取上次打开的路径
	templateFilePath = QFileDialog::getOpenFileName(this, tr("Load Image"), lastOpenTemplateFilePath, tr("Image Files(*.bmp *.png *.jpg);;All(*.*)"));
	if (templateFilePath != "")
	{
		ui->lineEdit_TemplateFilePath->setText(templateFilePath);
		QImage templateImage(templateFilePath);

		//ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(m_ImageProcessResult[0]));
		SaveConfig("lastOpenTemplateFilePath", lastOpenTemplateFilePath); // 保存上次打开的路径

		auto matchResult = m_ImageProcess->MatchTemplate(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[0]), ImageConvert::ConvertQImageToMat(templateImage));
		ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(ImageConvert::ConverMatToQImage(matchResult)));
	}
	else
	{
		return;
	}
}


void MainWindow::on_pushButton_HoughCircleDetect_clicked()
{
	auto radius = ui->spinBox_HoughCircleRadius->value();
	int currentStep = static_cast<int>(m_ImageProcessStep); // 获取当前图像处理步骤
	auto result = m_ImageProcess->HoughCircleDetect(ImageConvert::ConvertQImageToMat(m_ImageProcessResult[currentStep - 1]), radius);
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(ImageConvert::ConverMatToQImage(result)));
}


void MainWindow::on_pushButton_Test_clicked()
{
	auto image = m_ImageProcessResult[0];
	auto cvMat = ImageConvert::ConvertQImageToMat(image);
	if (cvMat.empty()) {
		int i = 0;
	}
	auto open_image = m_ImageProcess->Open(cvMat, 15);

	auto close_image = m_ImageProcess->Close(open_image, 7);

	auto threshold_image = m_ImageProcess->Threshold(close_image, 120, 255);

	auto filter_image = m_ImageProcess->Laplace(threshold_image);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(filter_image, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	cv::Mat img_contours;
	cv::cvtColor(cvMat, img_contours, cv::COLOR_GRAY2BGR);
	cv::drawContours(img_contours, contours, -1, cv::Scalar(0, 255, 0), 1); // 画出所有轮廓

	float targetArea = 3.14 * 1400 * 1400;
	std::vector<std::vector<cv::Point>> reslutContours;
	// 计算轮廓的面积
	for (size_t i = 0; i < contours.size(); i++) {
		// 计算轮廓的面积和周长
		double area = cv::contourArea(contours[i]);
		double perimeter = cv::arcLength(contours[i], true);
		// 计算圆形度
		double circularity = (4 * 3.1415926 * area) / (perimeter * perimeter);

		if (!(targetArea * 0.25 <= area && area <= targetArea * 1.44)) {
			continue;
		}

		reslutContours.push_back(contours[i]);
	}
	cv::Mat result = cv::Mat::zeros(cvMat.size(), CV_8UC3);
	cv::drawContours(result, reslutContours, -1, cv::Scalar(0, 0, 255), 2);

	cv::Mat origin = ImageConvert::ConvertQImageToMat(m_ImageProcessResult[0]);
	if (reslutContours.empty()) {
		QMessageBox::critical(this, "Error", "No circle found!!!"); // 弹出错误对话框
		return;
	}
	for (auto contour : reslutContours) {
		cv::RotatedRect ellipse = cv::fitEllipse(contour);
		if (origin.channels() == 1)
			cv::cvtColor(origin, origin, cv::COLOR_GRAY2BGR);
		cv::Scalar color(rand() % 256, rand() % 256, rand() % 256);
		cv::ellipse(origin, ellipse, color, 2);
	}
	ui->graphicsView_Camera->ShowImage(QPixmap::fromImage(ImageConvert::ConverMatToQImage(origin)));
	// 显示找到多少个圆
	QMessageBox::information(this, "Information", "Found " + QString::number(reslutContours.size()) + " circles");
}

