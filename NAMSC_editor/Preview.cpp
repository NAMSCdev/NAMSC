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

	supportedImageFormats.append(db.mimeTypeForName("image/png"));
	supportedImageFormats.append(db.mimeTypeForName("image/bmp"));
	supportedImageFormats.append(db.mimeTypeForName("image/jpeg"));


	supportedAudioFormats.append(db.mimeTypeForName("audio/mpeg"));
	supportedAudioFormats.append(db.mimeTypeForName("audio/MPA"));
	supportedAudioFormats.append(db.mimeTypeForName("audio/mpa-robust"));

	supportedAudioFormats.append(db.mimeTypeForName("audio/x-wav"));
	supportedAudioFormats.append(db.mimeTypeForName("audio/wav"));
	supportedAudioFormats.append(db.mimeTypeForName("audio/wave"));
	supportedAudioFormats.append(db.mimeTypeForName("audio/vnd.wave"));

	supportedAudioFormats.append(db.mimeTypeForName("audio/flac"));


	setScene(new QGraphicsScene(this->parent()));

	label.setScaledContents(true);
	label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	label.setAlignment(Qt::AlignCenter);
	labelProxy = scene()->addWidget(&label);
	scene()->sceneRect().center();


	player.setLoops(QMediaPlayer::Loops::Once);
	player.setAudioOutput(new QAudioOutput(this));
}

Preview::~Preview()
{}

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

void Preview::selectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	const QFileSystemModel* model = (QFileSystemModel*)selected.indexes()[0].model();
	QModelIndexList::Type index = selected.indexes()[0];
	qDebug() << "Selected " << model->fileName(index);
	qDebug() << index;
	QMimeData* mime = model->mimeData(selected.indexes());
	qDebug() << "Selection mime " << mime->formats();
	if (mime->hasUrls())
	{
		QMimeDatabase db;
		QUrl fileUrl = mime->urls().at(0);
		QMimeType fileMime = db.mimeTypeForUrl(fileUrl);
		qDebug() << "Url mime " << fileMime;
		qDebug() << "Url mime " << fileMime.name();
		qDebug() << "isSupportedImageFormat " << isSupportedImageFormat(fileMime);
		if (isSupportedImageFormat(fileMime))
		{
			this->previewImage(fileUrl);
		}
		qDebug() << "isSupportedAudioFormat " << isSupportedAudioFormat(fileMime) << "\n";
		if (isSupportedAudioFormat(fileMime))
		{
			this->previewAudio(fileUrl);
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
	image.load(url.toLocalFile());
	resizeEvent(new QResizeEvent(this->size(), this->size()));
	show();
}

void Preview::resizeEvent(QResizeEvent* event)
{

	QGraphicsView::resizeEvent(event);

	scene()->setSceneRect(this->rect());

	float windowRatio = (float) scene()->height() / (float) scene()->width();
	float imageRatio = (float) image.height() / (float) image.width();
	if (imageRatio > windowRatio)
	{
		label.resize(this->height()/imageRatio, this->height());
	} else
	{
		label.resize(this->width(), this->width()*imageRatio);
	}
	label.setPixmap(QPixmap::fromImage(image));
	QPoint center = scene()->sceneRect().center().toPoint();
	labelProxy->setPos(
		center.x() - label.width() / 2,
		center.y() - label.height() / 2
	);
}

void Preview::previewAudio(QUrl url)
{
	this->player.setSource(url);
	player.play();
}


QAudioSink* sink;

QWaveDecoder* decoder;
QByteArray wholeData;
QAudioDecoder* audioDecoder;
QBuffer* buffer;
QAudioFormat format;

void Preview::playAudio(QString name)
{
	QFile* file = new QFile(name);
	file->open(QIODevice::ReadOnly);
	QByteArray array = file->readAll();
	QBuffer buffer(&array);
	QAudioDevice info = QMediaDevices::defaultAudioOutput();

	format =info.preferredFormat();
	
	audioDecoder = new QAudioDecoder(this);
	audioDecoder->setAudioFormat(format);
	audioDecoder->setSourceDevice(&buffer);
	buffer.open(QIODeviceBase::ReadOnly);
	audioDecoder->setSource(QUrl(name));
	sink = new QAudioSink(format);
	wholeData.clear();

	connect(audioDecoder, &QAudioDecoder::bufferReady, this, [&]
	{
		QAudioBuffer rawAudio = audioDecoder->read();
		char* data = rawAudio.data<char>();
		wholeData.append(QByteArray::fromRawData(data, rawAudio.byteCount()));
	});
	connect(audioDecoder, &QAudioDecoder::isDecodingChanged, this, [&](bool isDecoding)
		{
			sink = new QAudioSink(format);
			if (isDecoding)
			{
				qDebug() << "Still decoding";
				return;
			}
			qDebug() << "Finished decoding";
			
			qDebug() << sink->state();
			sink->stop();
			try
			{
				QBuffer* buffer = new QBuffer(&wholeData);
				buffer->open(QIODeviceBase::ReadOnly);
				sink->start(buffer);
			}
			catch (...)
			{
				try
				{
					qDebug() << sink->error();
				}
				catch (...)
				{
					std::cout << "git gut";
				}
			}
		});
	audioDecoder->start();
}