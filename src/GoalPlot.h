#pragma once

#include <set>
#include <emscripten/val.h>

class GoalPlot
{
public:
	GoalPlot();

	const emscripten::val& plot() const;
	void subscribeOnPlotChanged(const emscripten::val& callback);
	void unSubscribeOnPlotChanged(const emscripten::val& callback);
	void onSolverStep();
private:
	void notifyAboutPlotChanged();
	static double randValue();

	emscripten::val m_plot = emscripten::val::array();
	std::set<emscripten::val> m_onPlotChangeSubscribers;
	int m_solverStep = 0;
};
