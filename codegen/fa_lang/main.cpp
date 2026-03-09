/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#include <QtCore/QCoreApplication>

#include "codegen/fa_lang/options.h"
#include "codegen/fa_lang/parsed_file.h"
#include "codegen/fa_lang/generator.h"
#include "codegen/common/cpp_file.h"
#include "codegen/common/logging.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

int main(int argc, char *argv[]) {
	QCoreApplication app(argc, argv);

	const auto options = codegen::fa_lang::parseOptions();
	if (options.inputPath.isEmpty()) {
		return -1;
	}

	const auto entries = codegen::fa_lang::parseJsonFile(options.inputPath);
	if (entries.isEmpty()) {
		return -1;
	}

	QDir dir(options.outputPath);
	if (!dir.mkpath(".")) {
		codegen::common::logError(821, "Command Line")
			<< "can not open path for writing: "
			<< dir.absolutePath().toStdString();
		return -1;
	}

	const auto srcFile = QFileInfo(options.inputPath);
	const auto dstFilePath = dir.absolutePath() + "/fa_lang_auto";

	const auto project = codegen::common::ProjectInfo{
		"codegen_fa_lang",
		srcFile.fileName(),
		false,
	};

	auto generator = codegen::fa_lang::Generator(
		entries,
		dstFilePath,
		project);

	if (!generator.writeHeader()
		|| !generator.writeSource()
		|| !codegen::common::TouchTimestamp(dstFilePath)) {
		return -1;
	}

	return 0;
}
