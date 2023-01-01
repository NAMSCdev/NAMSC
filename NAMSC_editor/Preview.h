#pragma once

#include <qgraphicsproxywidget.h>
#include <QGraphicsView>
#include <qitemselectionmodel.h>
#include <qmimetype.h>
#include <QMediaPlayer>
#include <QLabel>
#include <qpushbutton.h>
#include <qslider.h>
#include <QVBoxLayout>

class Preview  : public QGraphicsView
{
	Q_OBJECT

private:
	QList<QMimeType> supportedImageFormats;
	QList<QMimeType> supportedAudioFormats;
	QMediaPlayer player;
	QImage image;
	QLabel* imagePreview;
	QGraphicsProxyWidget* imagePreviewPoxy;
	QSlider* mediaSlider;
	QFrame* audioFrame;
	QVBoxLayout* vbox;
	QLabel* progress;
	QLabel* audioTitle;
	QPushButton* mediaButton;
	QHBoxLayout* hbox;
	QFrame* mediaInnerFrame;
	QSpacerItem* horizontalSpacer;
	void resizeEvent(QResizeEvent* event) override;
	std::string durationFrom(qint64 duration);
public:
	Preview(QWidget *parent);
	~Preview();

	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void setSupportedAudioFormats(QList<QMimeType> supportedAudioFormats);
	void setSupportedImageFormats(QList<QMimeType> supportedImageFormats);

public Q_SLOTS:
	void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	bool isSupportedImageFormat(QMimeType mime);
	bool isSupportedAudioFormat(QMimeType mime);
	void playAudio(QString name);
	void previewImage(QUrl url);
	void previewAudio(QUrl url);
	void mediaButtonPressed();
	void playerStateChanged(QMediaPlayer::PlaybackState newState);
	void durationChanged(qint64 duration);
};
