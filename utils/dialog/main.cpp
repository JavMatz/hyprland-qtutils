#include "Dialog.hpp"
#include <hyprutils/string/VarList.hpp>
#include <print>
#include <qapplication.h>
#include <QCommandLineParser>
#include <qqmlapplicationengine.h>
#include <qquickstyle.h>
#include <qtenvironmentvariables.h>
#include <QQmlContext>

using namespace Hyprutils::String;

int main(int argc, char* argv[]) {
    // disable logs to not trash the stdout
    qputenv("QT_LOGGING_RULES", QByteArray("*.debug=false;qml=false"));

    QString appTitle;
    auto dialog = new CDialog();

    QApplication app(argc, argv);
    app.setApplicationVersion("0.1.0");

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE"))
        QQuickStyle::setStyle("Basic");

    QCommandLineParser parser;
    parser.setApplicationDescription("Dialog");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption appTitleOption(QStringList() << "a" << "app-title", "Set the app title (for window rules of your WM)", "app-title");
    parser.addOption(appTitleOption);

    QCommandLineOption titleOption(QStringList() << "t" << "title", "Set the dialog's title", "title");
    parser.addOption(titleOption);

    QCommandLineOption textOption(QStringList() << "T" << "text", "Set the dialog's text", "text");
    parser.addOption(textOption);

    QCommandLineOption buttonsOptions(QStringList() << "b" << "buttons", "Set the dialog's buttons", "buttons");
    parser.addOption(buttonsOptions);

    parser.process(app);

    const QString argTitle = parser.value(titleOption);
    dialog->title = argTitle;

    const QString argAppTitle = parser.value(appTitleOption);
    appTitle = argAppTitle;

    const QString argText = parser.value(textOption);
    dialog->text = argText;

    const QString argButtons = parser.value(buttonsOptions);
    if (!argButtons.isEmpty())
    {
        for(auto& b : argButtons.split(u';')){
        dialog->buttons.emplace_back(b);
        }
    }

    app.setApplicationName(appTitle.isEmpty() ? dialog->title : appTitle);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dialog", dialog);
    engine.load("qrc:/qt/qml/org/hyprland/dialog/main.qml");

    return app.exec();
}
