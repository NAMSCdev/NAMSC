#include "NAMSC_engine.h"

#include <QMessageBox>

#include "Novel/Event/EventDialogue.h"

void errorMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString category;
    switch (type)
    {
    case QtDebugMsg:
        category = "Debug";
        break;
    default:
    case QtInfoMsg:
        category = "Info";
        break;
    case QtWarningMsg:
        category = "Warning";
        break;
    case QtCriticalMsg:
        category = "Critical";
        break;
    case QtFatalMsg:
        category = "Fatal";
        break;
    }

    QString message = '[' + category + "] [" + context.function + " {" + context.file + ':' + std::to_string(context.line).c_str() + "}]" + msg;
    switch (type) 
    {
    case QtDebugMsg:
    #ifdef DEBUG
        QMessageBox::information(nullptr, category, message);
    #endif
        break;

    default:
    case QtInfoMsg:
    case QtWarningMsg:
        QMessageBox::warning(nullptr, category, message);
        break;

    case QtCriticalMsg:
    case QtFatalMsg:
        QMessageBox::critical(nullptr, category, message);
        throw NovelLib::NovelException(msg);
        break;
    }
}

NAMSC_engine::NAMSC_engine(QWidget *parent)
    : QMainWindow(parent)
{
    qInstallMessageHandler(errorMessageHandler);
    ui.setupUi(this);
    Novel        &novel        = Novel::getInstance();
    AssetManager &assetManager = AssetManager::getInstance();
    novel.loadNovel(0, true);
#ifdef DEBUG
    assetManager.addAssetImageSceneryBackground("testBackground", 0, 0, "C:\\Users\\Murloc\\Downloads\\pies.png");
    assetManager.addAssetImageSceneryObject("kotImage", 0, 0, "C:\\Users\\Murloc\\Downloads\\kot.png");

    Scene scene(QString("start"), QString(""));

    Character testCharacter(QString("kot1"), QString("kotImage"), false, QPoint(0, 0), QSizeF(1.0, 1.0), 20.0);

    Scenery scenery;
    scenery.setBackgroundAssetImage("testBackground");
    scenery.setDisplayedCharacter("kot1", testCharacter);
    testCharacter.bMirrored      = true;
    testCharacter.rotationDegree = 0.0;
    testCharacter.name           = "kot2";
    testCharacter.pos            = QPoint(600, 100);
    scenery.setDisplayedCharacter("kot2", testCharacter);

    Event* event = new EventDialogue(&scene);
    event->scenery = scenery;
    scene.addEvent(event);
    novel.addScene("start", std::move(scene));

#endif
    ui.gameLayout->addWidget(novel.createSceneWidget());
    novel.run();
}

NAMSC_engine::~NAMSC_engine()
{
    /// In case we want to Novel to delete it instead of the Layout
    /// Novel::getInstance().getSceneWidget()->setParent(nullptr);
    /// delete Novel::getInstance().getSceneWidget();
}