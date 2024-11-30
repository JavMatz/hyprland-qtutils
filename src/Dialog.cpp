#include "Dialog.hpp"
#include <print>

CDialog::CDialog(QObject* parent) : QObject(parent) {
    ;
}

void CDialog::onButtonPress(QString buttonName) {
    std::print("{}\n", buttonName.trimmed().toStdString());
    exit(0);
}
