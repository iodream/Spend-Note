#pragma once
#include <QtGlobal>
#include <QLoggingCategory>

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
