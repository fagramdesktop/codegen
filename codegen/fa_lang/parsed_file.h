/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#pragma once

#include <QString>
#include <QVector>

namespace codegen {
namespace fa_lang {

struct LangEntry {
	QString key;
	QString value;
};

using LangEntries = QVector<LangEntry>;

LangEntries parseJsonFile(const QString &path);

} // namespace fa_lang
} // namespace codegen
