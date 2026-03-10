/*
This file is part of FAgram Desktop,
the unofficial desktop client based on Telegram Desktop.

For license and copyright information please follow this link:
https://github.com/fagramdesktop/fadesktop/blob/dev/LEGAL
*/

#include "codegen/fa_lang/options.h"

#include <QtCore/QCoreApplication>
#include "codegen/common/logging.h"

namespace codegen {
namespace fa_lang {
namespace {

constexpr int kErrorOutputPathExpected = 902;
constexpr int kErrorInputPathExpected = 903;

} // namespace

using common::logError;

Options parseOptions() {
	auto result = Options();
	const auto args = QCoreApplication::instance()->arguments();
	for (int i = 1, count = args.size(); i < count; ++i) {
		const auto &arg = args.at(i);

		if (arg == "-o") {
			if (++i == count) {
				logError(kErrorOutputPathExpected, "Command Line")
					<< "output path expected after -o";
				return Options();
			} else {
				result.outputPath = args.at(i);
			}
		} else if (arg.startsWith("-o")) {
			result.outputPath = arg.mid(2);
		} else {
			if (result.inputPath.isEmpty()) {
				result.inputPath = arg;
			} else {
				logError(kErrorInputPathExpected, "Command Line")
					<< "only one input path expected";
				return Options();
			}
		}
	}
	if (result.inputPath.isEmpty()) {
		logError(kErrorInputPathExpected, "Command Line")
			<< "input path expected";
		return Options();
	}
	return result;
}

} // namespace fa_lang
} // namespace codegen
