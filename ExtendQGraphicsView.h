#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QResizeEvent>

class ExtendQGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	ExtendQGraphicsView(QWidget* parent);
	~ExtendQGraphicsView();

	// 适应窗口
	void FitWindow();
	// 清空
	//void Clear();

	void addText(const QString& text);

public slots:
	// 显示图像
	void ShowImage(const QPixmap& pic);

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QGraphicsScene* scene;
	QPixmap pixmap;
	bool isFitWindow;
};
