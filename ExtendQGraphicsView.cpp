#include "ExtendQGraphicsView.h"

ExtendQGraphicsView::ExtendQGraphicsView(QWidget* parent)
	: QGraphicsView(parent)
{
	isFitWindow = false;

	scene = new QGraphicsScene(parent);
	this->setScene(scene);
}

ExtendQGraphicsView::~ExtendQGraphicsView()
{
	delete scene;
}

void ExtendQGraphicsView::ShowImage(const QPixmap& pic)
{
	pixmap = pic;
	FitWindow();
}

void ExtendQGraphicsView::FitWindow()
{
	isFitWindow = true;

	auto width = this->width();
	auto height = this->height();

	if (!pixmap.isNull() && isFitWindow) {
		scene->clear();
		
		// 计算缩放比例
		double scale = 1.0;

		double scaleX = static_cast<double>(width) / (pixmap.width() + 10);// 不+1会有滚动条
		double scaleY = static_cast<double>(height) / (pixmap.height() + 10);// 不+1会有滚动条
		if (scaleX > scaleY)
		{
			scale = scaleY;
		}
		else
		{
			scale = scaleX;
		}

		QPixmap scalePixmap = pixmap.copy();
		// 缩放
		scalePixmap = scalePixmap.scaled(scalePixmap.width() * scale, scalePixmap.height() * scale, Qt::KeepAspectRatio);
	/*	QGraphicsItem* item = (QGraphicsItem*)scene->addPixmap(scalePixmap);
		scene->addItem(item);*/
		scene->addPixmap(scalePixmap);
		//this->show();
		isFitWindow = false;
	}

	this->update();
	//// 手动触发 resizeEvent 以确保图像按比例显示
	//QResizeEvent fakeEvent(size(), size());
	//resizeEvent(&fakeEvent);
}

void ExtendQGraphicsView::addText(const QString& text)
{
	// 创建一个 QGraphicsTextItem
	QGraphicsTextItem* textItem = new QGraphicsTextItem(text);

	// 设置文字的位置，这里设置为视图的中心
	textItem->setPos(viewport()->rect().center() - textItem->boundingRect().center());

	// 将文字添加到场景中
	scene->addItem(textItem);
}

void ExtendQGraphicsView::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);
}
