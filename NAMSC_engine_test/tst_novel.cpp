#include <QtTest>

// add necessary includes here

class Novel : public QObject
{
    Q_OBJECT

public:
    Novel();
    ~Novel();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

Novel::Novel()
{

}

Novel::~Novel()
{

}

void Novel::initTestCase()
{

}

void Novel::cleanupTestCase()
{

}

void Novel::test_case1()
{

}

QTEST_APPLESS_MAIN(Novel)

#include "tst_novel.moc"
