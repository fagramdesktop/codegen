/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#pragma once

#include <memory>
#include <QString>
#include "codegen/common/cpp_file.h"
#include "codegen/fa_lang/parsed_file.h"

namespace codegen {
namespace fa_lang {

class Generator {
public:
	Generator(
		const LangEntries &entries,
		const QString &destBasePath,
		const common::ProjectInfo &project);

	bool writeHeader();
	bool writeSource();

private:
	const LangEntries &entries_;
	QString basePath_;
	const common::ProjectInfo &project_;
	std::unique_ptr<common::CppFile> source_;
	std::unique_ptr<common::CppFile> header_;
};

} // namespace fa_lang
} // namespace codegen
