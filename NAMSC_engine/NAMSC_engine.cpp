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
    assetManager.addAssetImageSceneryBackground("testBackground",    0, 0, "C:\\Users\\Murloc\\Downloads\\pies.png");
    assetManager.addAssetImageSceneryBackground("testBackground2",   0, 0, "C:\\Users\\Murloc\\Downloads\\pies.jpg");
    assetManager.addAssetImageSceneryBackground("testBackgroundRed", 0, 0, "C:\\Users\\Murloc\\Downloads\\piesRed.png");
    assetManager.addAssetImageSceneryObject("kotImage",              0, 0, "C:\\Users\\Murloc\\Downloads\\kot.png");
    assetManager.addAssetImageSceneryObject("flamigno",              0, 0, "C:\\Users\\Murloc\\Downloads\\potwor.png");
    assetManager.addAssetImageSceneryObject("flamignoAngry",         0, 0, "C:\\Users\\Murloc\\Downloads\\potworNegative.png");
    assetManager.addAssetImageSceneryObject("felicja",               0, 0, "C:\\Users\\Murloc\\Downloads\\felicja.png");

    Scene*  scene1 = novel.addScene(Scene("start", ""));
    Scenery scenery1(scene1);
    Scene*  scene2 = novel.addScene(Scene("Monster Encounter", ""));
    Scenery scenery2(scene2);
    Scene*  scene3 = novel.addScene(Scene("Lose", ""));
    Scenery scenery3(scene3);
    Scene*  scene4 = novel.addScene(Scene("Win", ""));
    Scenery scenery4(scene4);
    Scene*  scene5 = novel.addScene(Scene("Credits", ""));
    Scenery scenery5(scene5);

    Character wikingCharacter(QString("Nieznajomy"),      QString("kotImage"), false, QPoint(600, 40),  QSizeF(1.0, 1.0), 0.0);
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
    scenery2.addDisplayedCharacter(falmeCharacter);
    event6->scenery = scenery2;

    scenery3 = scenery2;

    EventDialogue* event7 = static_cast<EventDialogue*>(scene3->addEvent(new EventDialogue(scene3)).get());
    event7->addSentence(Sentence(event7, Translation(Translate{ { "En", "Gęba potwora przybiera grymas niezadowolenia... Stwór zaczyna powoli zmierzać w Twoim kierunku!"} }), "", "", "", "", 1.5));

    scenery3.clearDisplayedCharacters();
    falmeCharacter.rotationDegree = 0.0;
    falmeCharacter.scale = QSizeF(2.7, 2.7);
    scenery3.addDisplayedCharacter(falmeCharacter);
    event7->scenery = scenery3;

    EventDialogue* event8 = static_cast<EventDialogue*>(scene3->addEvent(new EventDialogue(scene3)).get());
    event8->addSentence(Sentence(event8, Translation(Translate{ { "En", "Bo przekroczeniu Twojego dystansu indywidualnego, potwór bierze głęboki wdech..."} }), ""));
    event8->addSentence(Sentence(event8, Translation(Translate{ { "En", "ZAPACH..."} }), "Straszna istotna", "", "", "", 1.0, 6));
    event8->addSentence(Sentence(event8, Translation(Translate{ { "En", "...SMACZNY!"} }), "Straszna istotna", "", "", "", 1.0, 3));

    scenery3.clearDisplayedCharacters();
    scenery3.setBackgroundAssetImage("testBackgroundRed");
    falmeCharacter.pos = QPointF(445.0, -495.0);
    falmeCharacter.scale = QSizeF(3.5, 3.5);
    falmeCharacter.rotationDegree = -23.3;
    scenery3.addDisplayedCharacter(falmeCharacter);
    event8->scenery = scenery3;

    EventDialogue* event9 = static_cast<EventDialogue*>(scene3->addEvent(new EventDialogue(scene3)).get());
    event9->addSentence(Sentence(event9, Translation(Translate{ { "En", "Kończysz marnie."} }), ""));
  
    scenery3.clearDisplayedCharacters();
    scenery3.setBackgroundAssetImage("testBackground2");
    falmeCharacter.setAssetImage("flamignoAngry");
    scenery3.addDisplayedCharacter(falmeCharacter);
    event9->scenery = scenery3;

    scenery4 = scenery2;

    EventDialogue* event10 = static_cast<EventDialogue*>(scene4->addEvent(new EventDialogue(scene4)).get());
    event10->addSentence(Sentence(event10, Translation(Translate{ { "En", "Dziękuję. Ziarna są naprawdę smaczne. "} }), "???"));
    event10->addSentence(Sentence(event10, Translation(Translate{ { "En", "Jestem Felicja. Gdybyś potrzebował kiedyś desantu powietrznego, to moi poddani zareagują, gdy zadzwonisz pod numer +84 91 241 22 15, będąc w zasięgu sieci 5G."} }), "Felicja"));
    event10->addSentence(Sentence(event10, Translation(Translate{ { "En", "Nie będę już więcej przeszkadzać, dziękuję za smaczne ziarna."} }), "Felicja"));

    scenery4.clearDisplayedCharacters();
    scenery4.addDisplayedCharacter(felicjaCharacter);
    event10->scenery = scenery4;
    
    scenery5 = scenery4;
    EventJump*     eventJump2 = static_cast<EventJump*>(scene4->addEvent(new EventJump(scene4, "", "Credits")).get());
    EventDialogue* event11    = static_cast<EventDialogue*>(scene5->addEvent(new EventDialogue(scene5)).get());
    event11->addSentence(Sentence(event11, Translation(Translate{ { "En", "The End."} }), ""));
    scenery5.clearDisplayedCharacters();
    event11->scenery = scenery5;

    scene1->removeEvent(event1->label);
    scene1->removeEvent(event2->label);
    scene1->removeEvent(event3->label);
    //scene1->removeEvent(eventJump1->label);

    scene2->removeEvent(event4->label);
    scene2->removeEvent(event5->label);
    //scene2->removeEvent(event6->label);

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