#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "mainform.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainForm gui{};
    gui.show();
    gui.resize(600, 400);

    return QApplication::exec();
}
