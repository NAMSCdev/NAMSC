#include "ExampleEngine.h"

#include <QFile>
#include <QMessageBox>

#include "pvnlib/Novel/Event/EventDialogue.h"
#include "pvnlib/Novel/Event/EventChoice.h"

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

ExampleEngine::ExampleEngine(QWidget *parent)
    : QMainWindow(parent)
{
    qInstallMessageHandler(errorMessageHandler);
    ui.setupUi(this);
    Novel        &novel        = Novel::getInstance();
    AssetManager &assetManager = AssetManager::getInstance();
    novel.loadNovel(0, true);

//#ifdef DEBUG
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
    Character felicjaCharacter(QString("Felicja"),        QString("felicja"),  false, QPoint(280, 0),   QSizeF(1.0, 1.0), 0.0);

    scenery1.setBackgroundAssetImage("testBackground");
    scenery1.addDisplayedCharacter(wikingCharacter);

    EventDialogue* event1 = static_cast<EventDialogue*>(scene1->addEvent(new EventDialogue(scene1)).get());
    event1->addSentence(Sentence(event1, Translation(Translate{ { "En", "Witaj!"} }), "Nieznajomy"));
    event1->addSentence(Sentence(event1, Translation(Translate { { "En", "Jestem Edggar. W pobliżu grasuje niebezpieczny stwór. "} }), "Nieznajomy", "", "", ""));
    event1->addSentence(Sentence(event1, Translation(Translate { { "En", "Uważaj na siebie!"} }), "Edggar"));
    
    event1->scenery = scenery1;

    EventDialogue* event2 = static_cast<EventDialogue*>(scene1->addEvent(new EventDialogue(scene1)).get());
    event2->addSentence(Sentence(event2, Translation(Translate { { "En", "Żegnam!"} }), "Edggar"));

    scenery1.clearDisplayedCharacters();
    wikingCharacter.bMirrored = true;
    scenery1.addDisplayedCharacter(wikingCharacter);
    event2->scenery = scenery1;

    EventDialogue* event3 = static_cast<EventDialogue*>(scene1->addEvent(new EventDialogue(scene1)).get());
    event3->addSentence(Sentence(event2, Translation(Translate{ { "En", "Podziwiasz otoczenie. Lorem ipsum, komu by się chciało pisać opisy przyrody... Masz czas, w końcu żaden potwór nie jest Tobie straszny!"} }), ""));

    scenery1.clearDisplayedCharacters();
    event3->scenery = scenery1;

    EventJump* eventJump1 = static_cast<EventJump*>(scene1->addEvent(new EventJump(scene1, "", "Monster Encounter")).get());

    scenery2 = scenery1;

    EventDialogue* event4 = static_cast<EventDialogue*>(scene2->addEvent(new EventDialogue(scene2)).get());
    event4->addSentence(Sentence(event4, Translation(Translate{ { "En", "..."} }), ""));

    scenery2.clearDisplayedCharacters();
    scenery2.addDisplayedCharacter(falmeCharacter);
    event4->scenery = scenery2;

    EventDialogue* event5 = static_cast<EventDialogue*>(scene2->addEvent(new EventDialogue(scene2)).get());
    event5->addSentence(Sentence(event5, Translation(Translate{ { "En", "No chyba, że ten!"} }), ""));
    event5->addSentence(Sentence(event5, Translation(Translate{ { "En", "J...j...j..."} }), "Straszna istotna", "", "", "", 1.0, 6));
    event5->addSentence(Sentence(event5, Translation(Translate{ { "En", "J-JEŚĆ!"} }), "Straszna istotna", "", "", "", 1.0, 3));

    scenery2.clearDisplayedCharacters();
    falmeCharacter.pos   = QPointF(80.0, 0.0);
    falmeCharacter.scale = QSizeF(2.5, 2.5);
    scenery2.addDisplayedCharacter(falmeCharacter);
    event5->scenery = scenery2;

    EventChoice* event6 = static_cast<EventChoice*>(scene2->addEvent(new EventChoice(scene2)).get());
    event6->setMenuText(Translate{ { "En", "Co zamierasz dać tej strasznej istocie?"} });
    event6->addChoice(std::move(Choice(event6, Translation(Translate{ { "En", "Garść ziaren słonecznika"} }), "Win")));
    event6->addChoice(std::move(Choice(event6, Translation(Translate{ { "En", "Dwa kilo mięsa wołowego zapakowanego szczelnie w pojemniku próżniowym, ale nieco po terminie, bo ciężko pamiętać, że takie rzeczy nosi się w kieszeni"} }), "Lose")));
    event6->addChoice(std::move(Choice(event6, Translation(Translate{ { "En", "W twarz"} }), "Lose")));

    scenery2.clearDisplayedCharacters();
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

    //scene1->removeEvent(event1->label);
    //scene1->removeEvent(event2->label);
    //scene1->removeEvent(event3->label);
    //scene1->removeEvent(eventJump1->label);

    //scene2->removeEvent(event4->label);
    //scene2->removeEvent(event5->label);
    //scene2->removeEvent(event6->label);

    //scene3->removeEvent(event7->label);
    //scene3->removeEvent(event8->label);
    //scene3->removeEvent(event9->label);
    //scene4->removeEvent(event10->label);
    //scene4->removeEvent(eventJump2->label);
    //scene5->removeEvent(event11->label);

//#endif
    ui.gameLayout->addWidget(novel.createSceneWidget());
    novel.run();
}

ExampleEngine::~ExampleEngine()
{
    /// In case we want to Novel to delete it instead of the Layout
    /// Novel::getInstance().getSceneWidget()->setParent(nullptr);
    /// delete Novel::getInstance().getSceneWidget();
}