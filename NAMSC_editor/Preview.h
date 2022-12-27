#pragma once

#include <qgraphicsproxywidget.h>
#include <QGraphicsView>
#include <qitemselectionmodel.h>
#include <qmimetype.h>
#include <QMediaPlayer>
#include <QLabel>
#include <QVBoxLayout>

class Preview  : public QGraphicsView
{
	Q_OBJECT

private:
	QList<QMimeType> supportedImageFormats;
	QList<QMimeType> supportedAudioFormats;
	QMediaPlayer player;
	QImage image;
	QLabel label;
	QGraphicsProxyWidget* labelProxy;
public:
	Preview(QWidget *parent);
	~Preview();

	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
public Q_SLOTS:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	bool isSupportedImageFormat(QMimeType mime);
	bool isSupportedAudioFormat(QMimeType mime);
	void playAudio(QString name);
	void previewImage(QUrl url);
	void previewAudio(QUrl url);
protected:
	void resizeEvent(QResizeEvent* event) override;
};
