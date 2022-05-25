#pragma once

#include <string>
#include <fstream>

namespace lucy {
	namespace Util {
		std::string ReadFile(const std::string& filename) {
			std::string line, text = "";
			std::fstream file(filename);

			if (!file.is_open()) return text;

			while (std::getline(file, line)) text += (line + '\n');

			file.close();

			return text;
		}

		bool WriteFile(const std::string& filename, const std::string& source) {
			return WriteFile(filename, source.c_str());
		}

		bool WriteFile(const std::string& filename, const char* source) {
			std::ofstream fout(filename.c_str());

			if (!fout.is_open()) return false;

			fout << source;
			fout.close();

			return true;
		}
	}
}