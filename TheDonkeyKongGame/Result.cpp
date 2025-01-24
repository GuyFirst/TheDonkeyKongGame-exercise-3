#include "Result.h"
#include <fstream>


void Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		this->addResult(iteration, static_cast<ResultValue>(result));
	}
	results_file.close();
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file.close();
}




