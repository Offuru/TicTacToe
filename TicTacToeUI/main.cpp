#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QMetaType>
#include <optional>

Q_DECLARE_METATYPE(std::optional<tictactoe::Symbol>)


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
