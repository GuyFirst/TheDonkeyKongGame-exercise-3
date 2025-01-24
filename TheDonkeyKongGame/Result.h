#pragma once

#include <list>
#include <string>
class Results {
public:
	enum ResultValue { DIED, REACH_PAULIN, NO_RESULT}; // Maybe we need a WIN event
private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
public:
	void loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}
	std::pair<size_t, ResultValue> popResult() {
		if (results.empty())
			return { 0, Results::NO_RESULT };
		auto result = results.front();
		results.pop_front();
		return result;
	}

	bool isFinishedBy(size_t iteration) const {
		return results.empty() || results.back().first <= iteration;
	}

};
