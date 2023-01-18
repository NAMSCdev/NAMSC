#include "NAMSC_engine.h"

#include <QMessageBox>
#include <QFile>

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
    assetManager.addAssetImageSceneryObject("flamigno", 0, 0, "C:\\Users\\Murloc\\Downloads\\potwor.png");

    Scene scene(QString("start"), QString(""));

    Character wikingCharacter(QString("Nieznajomy"), QString("kotImage"), false, QPoint(600, 40), QSizeF(1.0, 1.0), 0.0);
    Character falmeCharacter(QString("Straszna istota!"), QString("flamigno"), false, QPoint(500, 680), QSizeF(1.0, 1.0), 0.0);

    Scenery scenery;
    scenery.setBackgroundAssetImage("testBackground");
    scenery.addDisplayedCharacter(wikingCharacter);
    //scenery.addDisplayedCharacter(falmeCharacter);

    EventDialogue* event = new EventDialogue(&scene);
    event->scenery = scenery;
    event->sentences.emplace_back(event, Translation(Translate{ { "En", "Witaj!"} }), "Nieznajomy");
    event->sentences.emplace_back(event, Translation(Translate { { "En", "Jestem Edggar. W pobliży grasuje niebezpieczny potwór. "} }), "Nieznajomy");
    event->sentences.emplace_back(event, Translation(Translate { { "En", "Zostałeś ostrzeżony!"} }), "Edggar");
    scene.addEvent(event);

    scenery.clearDisplayedCharacters();
    wikingCharacter.bMirrored = true;
    scenery.addDisplayedCharacter(wikingCharacter);
    EventDialogue* event2 = new EventDialogue(&scene);
    event2->sentences.emplace_back(event2, Translation(Translate { { "En", "Żegnam!"} }), "Edggar");
    //event->sentences.emplace_back(event, Translation({ {QString("En"), QString("I salute the pigeons!")} }), "Wiser whoever");
    event2->scenery = scenery;
    scene.addEvent(event2);

    EventDialogue* event3 = new EventDialogue(&scene);
    event3->sentences.emplace_back(event2, Translation(Translate{ { "En", "Podziwiasz otoczenie. Lorem ipsum, komu by się chciało pisać opisy przyrody... Masz na to czas, w końcu żaden potwór nie jest Tobie straszny!"} }), "");

    scenery.clearDisplayedCharacters();
    event3->scenery = scenery;
    scene.addEvent(event3);

    EventDialogue* event4 = new EventDialogue(&scene);
    event4->sentences.emplace_back(event4, Translation(Translate{ { "En", "..."} }), "");

    scenery.clearDisplayedCharacters();
    scenery.addDisplayedCharacter(falmeCharacter);
    event4->scenery = scenery;
    scene.addEvent(event4);

    EventDialogue* event5 = new EventDialogue(&scene);
    event5->sentences.emplace_back(event5, Translation(Translate{ { "En", "No chyba, że ten!"} }), "");
    event5->sentences.emplace_back(event5, Translation(Translate{ { "En", "J...j...j..."} }), "Straszna istotna");
    event5->sentences.emplace_back(event5, Translation(Translate{ { "En", "J-JEŚĆ!"} }), "Straszna istotna");

    scenery.clearDisplayedCharacters();
    falmeCharacter.pos   = QPointF(80, 0);
    falmeCharacter.scale = QSizeF(1.6, 1.6);
    scenery.addDisplayedCharacter(falmeCharacter);
    event5->scenery = scenery;
    scene.addEvent(event5);

    novel.addScene(std::move(scene));

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