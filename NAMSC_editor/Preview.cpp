#include "Preview.h"

#include <iostream>
#include <QMimeType>
#include <QMediaPlayer>
#include <QtMultimediaWidgets/QtMultimediaWidgets>
#include "NAMSC_editor.h"


Preview::Preview(QWidget *parent)
	: QGraphicsView(parent)
{
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);

	this->setAcceptDrops(true);

	QMimeDatabase db;
	setScene(new QGraphicsScene(this));
	imagePreview = new QLabel();
	imagePreview->setScaledContents(true);
	imagePreview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	imagePreview->setAlignment(Qt::AlignCenter);
	imagePreviewProxy = scene()->addWidget(imagePreview);

	audioFrame = new QFrame(this);
	scene()->addWidget(audioFrame);

	progress = new QLabel(QString("0:00/0:00"));
	progress->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
	progress->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	connect(&player, &QMediaPlayer::positionChanged, this, &Preview::durationChanged);
	connect(&player, &QMediaPlayer::durationChanged, this, &Preview::durationChanged);
	audioTitle = new QLabel(QString("Title"));
	audioTitle->setAlignment(Qt::AlignCenter);
	mediaSlider = new QSlider();
	mediaSlider->setMinimum(0);
	mediaSlider->setOrientation(Qt::Horizontal);
	mediaSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	mediaButton = new QPushButton(QString("Pause"));
	connect(mediaButton, &QPushButton::pressed, this, &Preview::mediaButtonPressed);
	connect(&player, &QMediaPlayer::playbackStateChanged, this, &Preview::playerStateChanged);
	mediaSlider->setTracking(false);
	connect(mediaSlider, &QSlider::sliderMoved, &player, &QMediaPlayer::setPosition);
	mediaInnerFrame = new QFrame();
	mediaInnerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
	horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
	hbox = new QHBoxLayout(mediaInnerFrame);
	hbox->addWidget(mediaButton);
	hbox->addItem(horizontalSpacer);
	hbox->addWidget(progress);
	vbox = new QVBoxLayout(audioFrame);
	vbox->setSpacing(0);
	vbox->addWidget(audioTitle);
	vbox->addWidget(mediaInnerFrame);
	vbox->addWidget(mediaSlider);
	audioFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	player.setLoops(QMediaPlayer::Loops::Once);
	player.setAudioOutput(new QAudioOutput(this));

	audioFrame->hide();
	imagePreviewProxy->hide();
}

Preview::~Preview()
{
	delete imagePreview;
	delete audioFrame;
}

void Preview::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void Preview::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasUrls()) {
		qDebug() << "Dropped file " + event->mimeData()->urls().takeAt(0).toLocalFile();
	}
}

void Preview::setSupportedAudioFormats(QList<QMimeType> audioFormats)
{
	supportedAudioFormats.clear();
	supportedAudioFormats.append(audioFormats);
}

void Preview::setSupportedImageFormats(QList<QMimeType> imageFormats)
{
	supportedImageFormats.clear();
	supportedImageFormats.append(imageFormats);
}

void Preview::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	if (selected.indexes().isEmpty())
	{
		player.stop();
		audioFrame->hide();
		imagePreviewProxy->hide();
		return;
	}
	const QAbstractItemModel* model = selected.indexes()[0].model();
	QModelIndexList::Type index = selected.indexes()[0];
	qDebug() << index;
	QMimeData* mime = model->mimeData(selected.indexes());
	qDebug() << "Selection mime " << mime->formats();
	if (mime->hasUrls())
	{
		QMimeDatabase db;
		QUrl fileUrl = mime->urls().at(0);
		QMimeType fileMime = db.mimeTypeForUrl(fileUrl);
		qDebug() << "File: " << fileUrl.fileName();
		qDebug() << "Url mime " << fileMime;
		qDebug() << "Url mime " << fileMime.name();
		qDebug() << "isSupportedImageFormat " << isSupportedImageFormat(fileMime);
		qDebug() << "isSupportedAudioFormat " << isSupportedAudioFormat(fileMime) << "\n";
		if (isSupportedImageFormat(fileMime))
		{
			this->previewImage(fileUrl);
		} else if (isSupportedAudioFormat(fileMime))
		{
			this->previewAudio(fileUrl);
		} else
		{
			player.stop();
			audioFrame->hide();
			imagePreviewProxy->hide();
		}
	}
}

bool Preview::isSupportedImageFormat(QMimeType mime)
{
	if(mime.name().contains("image"))
	{
		return supportedImageFormats.contains(mime);
	}
	return false;
}

bool Preview::isSupportedAudioFormat(QMimeType mime)
{
	if (mime.name().contains("audio"))
	{
		return supportedAudioFormats.contains(mime);
	}
	return false;
}

void Preview::previewImage(QUrl url)
{
	player.stop();
	audioFrame->hide();
	imagePreviewProxy->show();
	image.load(url.toLocalFile());
	resizeEvent(new QResizeEvent(this->size(), this->size()));
	show();
}

void Preview::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);

	scene()->setSceneRect(this->rect());
	audioFrame->resize(this->size());

	float windowRatio = (float)scene()->height() / (float)scene()->width();
	float imageRatio = (float)image.height() / (float)image.width();
	if (imageRatio > windowRatio)
	{
		imagePreview->resize(this->height() / imageRatio, this->height());
	}
	else
	{
		imagePreview->resize(this->width(), this->width() * imageRatio);
	}
	imagePreview->setPixmap(QPixmap::fromImage(image));
	QPoint center = scene()->sceneRect().center().toPoint();
	imagePreviewProxy->setPos(
		center.x() - imagePreview->width() / 2,
		center.y() - imagePreview->height() / 2
	);
}

std::string Preview::durationFrom(qint64 duration)
{
	return std::format("{:02}", duration / 60000) + ":" + 
		std::format("{:02}", duration / 1000 % 60)+ "." + 
		std::format("{:01}", duration % 1000 / 100);
}

void Preview::previewAudio(QUrl url)
{
	player.setSource(url);
	player.play();
	audioFrame->show();
	imagePreviewProxy->hide();
	mediaSlider->setMaximum(player.duration());
	audioTitle->setText(url.fileName());
}


void Preview::playerStateChanged(QMediaPlayer::PlaybackState newState)
{
	if (newState == QMediaPlayer::PausedState || newState == QMediaPlayer::StoppedState)
	{
		mediaButton->setText("Play");
	}
	else
	{
		mediaButton->setText("Pause");
	}
}

void Preview::durationChanged(qint64 duration)
{
	std::string string = durationFrom(player.position()) + "/" + durationFrom(player.duration());
	progress->setText(QString(string.data()));
	mediaSlider->setRange(0, player.duration());
	mediaSlider->setSliderPosition(player.position());
}

void Preview::mediaButtonPressed()
{
	if(player.playbackState() == QMediaPlayer::PausedState || player.playbackState() == QMediaPlayer::StoppedState)
	{
		player.play();
	} else
	{
		player.pause();
	}
}