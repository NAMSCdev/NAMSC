#include "NAMSC_engine.h"

#include <QMessageBox>
#include <QFile>

#include "Novel/Event/EventDialogue.h"
#include "Novel/Event/EventChoice.h"

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

    Scenery scenery(&scene);
    scenery.setBackgroundAssetImage("testBackground");
    scenery.addDisplayedCharacter(wikingCharacter);

    EventDialogue* event = new EventDialogue(&scene);
    event->scenery = scenery;
    event->addSentence(std::move(Sentence(event, Translation(Translate{ { "En", "Witaj!"} }), "Nieznajomy")));
    event->addSentence(std::move(Sentence(event, Translation(Translate { { "En", "Jestem Edggar. W pobliżu grasuje niebezpieczny stwór. "} }), "Nieznajomy")));
    event->addSentence(std::move(Sentence(event, Translation(Translate { { "En", "Uważaj na siebie!"} }), "Edggar")));

    scenery.clearDisplayedCharacters();
    wikingCharacter.bMirrored = true;
    scenery.addDisplayedCharacter(wikingCharacter);
    EventDialogue* event2 = new EventDialogue(&scene);
    event2->addSentence(std::move(Sentence(event2, Translation(Translate { { "En", "Żegnam!"} }), "Edggar")));
    event2->scenery = scenery;

    EventDialogue* event3 = new EventDialogue(&scene);
    event3->addSentence(std::move(Sentence(event2, Translation(Translate{ { "En", "Podziwiasz otoczenie. Lorem ipsum, komu by się chciało pisać opisy przyrody... Masz czas, w końcu żaden potwór nie jest Tobie straszny!"} }), "")));

    scenery.clearDisplayedCharacters();
    event3->scenery = scenery;

    EventDialogue* event4 = new EventDialogue(&scene);
    event4->addSentence(std::move(Sentence(event4, Translation(Translate{ { "En", "..."} }), "")));

    scenery.clearDisplayedCharacters();
    scenery.addDisplayedCharacter(falmeCharacter);
    event4->scenery = scenery;

    EventDialogue* event5 = new EventDialogue(&scene);
    event5->addSentence(std::move(Sentence(event5, Translation(Translate{ { "En", "No chyba, że ten!"} }), "")));
    event5->addSentence(std::move(Sentence(event5, Translation(Translate{ { "En", "J...j...j..."} }), "Straszna istotna")));
    event5->addSentence(std::move(Sentence(event5, Translation(Translate{ { "En", "J-JEŚĆ!"} }), "Straszna istotna")));
    scenery.clearDisplayedCharacters();
    falmeCharacter.pos   = QPointF(80, 0);
    falmeCharacter.scale = QSizeF(2.5, 2.5);
    scenery.addDisplayedCharacter(falmeCharacter);
    event5->scenery = scenery;

    EventChoice* event6 = new EventChoice(&scene);
    //event6->choices.emplace_back(event6, Translation(Translate{ { "En", "Sięgasz do kieszeni. "} }), "");
    //event6->sentences.emplace_back(event6, Translation(Translate{ { "En", "J...j...j..."} }), "Straszna istotna");
    //event6->sentences.emplace_back(event6, Translation(Translate{ { "En", "J-JEŚĆ!"} }), "Straszna istotna");
    scenery.clearDisplayedCharacters();
    falmeCharacter.rotationDegree = 20.0;
    scenery.addDisplayedCharacter(falmeCharacter);
    event6->scenery = scenery;

    //scene.addEvent(std::move(event));
    //scene.addEvent(std::move(event2));
    //scene.addEvent(std::move(event3));
    //scene.addEvent(std::move(event4));
    scene.addEvent(std::move(event5));
    scene.addEvent(std::move(event6));
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