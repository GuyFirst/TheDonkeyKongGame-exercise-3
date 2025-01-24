#include "Steps.h"
#include "gameConfig.h"
#include <fstream>
#include <iostream>


void Steps::loadSteps(const std::string& filename) {
	
	std::ifstream steps_file(filename);
	if (!steps_file.is_open())
		std::cout << " oh no";
	steps_file >> this->randomSeed;
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		this->addStep(iteration, step);
	}
	steps_file.close();

}

void Steps::saveSteps(const std::string& filename) const {
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}


void Steps::printSteps() const {
	gotoxy(0, 0);
	if (steps.empty()) {
		std::cout << "No steps available." << std::endl;
		return;
	}

	for (const auto& step : steps) {
		std::cout << "Itr: " << step.first << ",Step: " << step.second << "  ";
	}
}