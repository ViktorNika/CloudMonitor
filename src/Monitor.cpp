#include "Monitor.h"
#include <emscripten/bind.h>
#include "MinMaxTable.h"
#include "GoalPlot.h"
#include "ModelView.h"

EMSCRIPTEN_BINDINGS(jsMonitor) {
	emscripten::class_<Monitor>("Monitor")
		.constructor<>()
		.function("subscribeOnCalculationChanged", &Monitor::subscribeOnCalculationChanged)
		.function("unSubscribeOnCalculationChanged", &Monitor::unSubscribeOnCalculationChanged)
		.function("timerTick", &Monitor::timerTick)
		.property("calculation", &Monitor::calculation, &Monitor::setCalculation)
		.property("minMaxTable", &Monitor::minMaxTable)
		.property("goalPlot", &Monitor::goalPlot)
		.property("modelView", &Monitor::modelView)
		;
}


Monitor::Monitor()
{
	m_minMaxTable = std::make_shared<MinMaxTable>();
	m_goalPlot = std::make_shared<GoalPlot>();
	m_modelView = std::make_shared<ModelView>();
}

void Monitor::setCalculation(bool calculation)
{
	if (m_calculation == calculation)
		return;

	m_calculation = calculation;
	for (const emscripten::val& callback : m_onCalculationChangedSubscribers)
		callback();
}

bool Monitor::calculation() const
{
	return m_calculation;
}

void Monitor::subscribeOnCalculationChanged(const emscripten::val& callback)
{
	m_onCalculationChangedSubscribers.insert(callback);
}

void Monitor::unSubscribeOnCalculationChanged(const emscripten::val& callback)
{
	m_onCalculationChangedSubscribers.erase(callback);
}

std::shared_ptr<MinMaxTable> Monitor::minMaxTable() const
{
	return m_minMaxTable;
}

std::shared_ptr<GoalPlot> Monitor::goalPlot() const
{
	return m_goalPlot;
}

std::shared_ptr<ModelView> Monitor::modelView() const
{
	return m_modelView;
}

void Monitor::timerTick()
{
	if (!m_calculation)
		return;

	if (m_minMaxTable)
		m_minMaxTable->onSolverStep();
	if (m_goalPlot)
		m_goalPlot->onSolverStep();
	if (m_modelView)
		m_modelView->render();
}
