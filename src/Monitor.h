#pragma once

#include <set>
#include <emscripten/val.h>

class MinMaxTable;
class GoalPlot;
class ModelView;

class Monitor
{
public:
	Monitor();

	void setCalculation(bool calculation);
	bool calculation() const;
	void subscribeOnCalculationChanged(const emscripten::val& callback);
	void unSubscribeOnCalculationChanged(const emscripten::val& callback);
	std::shared_ptr<MinMaxTable> minMaxTable() const;
	std::shared_ptr<GoalPlot> goalPlot() const;
	std::shared_ptr<ModelView> modelView() const;
	void timerTick();
private:
	bool m_calculation = false;
	std::set<emscripten::val> m_onCalculationChangedSubscribers;

	std::shared_ptr<MinMaxTable> m_minMaxTable;
	std::shared_ptr<GoalPlot> m_goalPlot;
	std::shared_ptr<ModelView> m_modelView;
};
