#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("UDRMS");
    app.setOrganizationName("ENSIA");
    MainWindow win;
    win.show();
    return app.exec();
}
