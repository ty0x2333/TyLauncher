#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char **argv, int flags= ApplicationFlags);

protected slots:
    void updateTheme();
};

#endif // APPLICATION_H
