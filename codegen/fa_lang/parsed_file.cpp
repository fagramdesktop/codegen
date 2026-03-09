/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#include "codegen/fa_lang/parsed_file.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include "codegen/common/logging.h"

namespace codegen {
namespace fa_lang {
namespace {

constexpr int kErrorCantOpenFile = 851;
constexpr int kErrorBadJson = 852;

} // namespace

LangEntries parseJsonFile(const QString &path) {
	auto file = QFile(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		common::logError(kErrorCantOpenFile, path)
			<< "can not open input file";
		return {};
	}

	auto error = QJsonParseError();
	const auto doc = QJsonDocument::fromJson(file.readAll(), &error);
	file.close();

	if (error.error != QJsonParseError::NoError || !doc.isObject()) {
		common::logError(kErrorBadJson, path)
			<< "bad JSON: " << error.errorString().toStdString();
		return {};
	}

	const auto obj = doc.object();
	auto result = LangEntries();
	result.reserve(obj.size());
	for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
		if (it.value().isString()) {
			result.push_back({ it.key(), it.value().toString() });
		}
	}

	std::sort(result.begin(), result.end(), [](const LangEntry &a, const LangEntry &b) {
		return a.key < b.key;
	});

	return result;
}

} // namespace fa_lang
} // namespace codegen
