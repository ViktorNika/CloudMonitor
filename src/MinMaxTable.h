#pragma once

#include <set>
#include <emscripten/val.h>

class MinMaxTable
{
public:
	MinMaxTable();

	const emscripten::val& table() const;
	void subscribeOnTableChanged(const emscripten::val& callback);
	void unSubscribeOnTableChanged(const emscripten::val& callback);
	void onSolverStep();
private:
	void generateData(bool init = false);
	void notifyAboutTableChanged();
	static double randValue();

	emscripten::val m_table = emscripten::val::array();
	std::set<emscripten::val> m_onTableChangeSubscribers;
};
