#include "Result.h"
#include <fstream>


Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file.close();
}

size_t Results::getNextEvent() const {
	if (!results.empty) {
		return results.front();
	}
	else return 0; 
	// we use the fact that on iteration zero we cannot hit a bomb
	// to indicate that there isn't any result left with a hit bomb event
}
