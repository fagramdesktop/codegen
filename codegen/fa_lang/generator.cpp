/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#include "codegen/fa_lang/generator.h"

#include <QtCore/QDir>

namespace codegen {
namespace fa_lang {

Generator::Generator(
	const LangEntries &entries,
	const QString &destBasePath,
	const common::ProjectInfo &project)
: entries_(entries)
, basePath_(destBasePath)
, project_(project) {
}

bool Generator::writeHeader() {
	header_ = std::make_unique<common::CppFile>(
		basePath_ + ".h",
		project_);

	header_->includeFromLibrary("rpl/producer.h")
		.includeFromLibrary("QString")
		.newline()
		.include("fa/lang/fa_lang.h")
		.newline();

	header_->pushNamespace("fatr");

	header_->stream() << "\
\n\
struct now_t {\n\
};\n\
\n\
inline constexpr now_t now{};\n\
\n\
struct phrase {\n\
\tconst char *key;\n\
\n\
\t[[nodiscard]] inline QString operator()(now_t) const {\n\
\t\treturn FAlang::Translate(QString::fromLatin1(key));\n\
\t}\n\
\t[[nodiscard]] inline rpl::producer<QString> operator()() const {\n\
\t\treturn FAlang::RplTranslate(QString::fromLatin1(key));\n\
\t}\n\
};\n\
\n";

	for (const auto &entry : entries_) {
		header_->stream()
			<< "inline constexpr phrase "
			<< entry.key
			<< "{ \""
			<< entry.key
			<< "\" };\n";
	}

	header_->newline();
	header_->popNamespace();

	return header_->finalize();
}

bool Generator::writeSource() {
	source_ = std::make_unique<common::CppFile>(
		basePath_ + ".cpp",
		project_);
	source_->newline();
	return source_->finalize();
}

} // namespace fa_lang
} // namespace codegen
