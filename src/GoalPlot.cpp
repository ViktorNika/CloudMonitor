#include "GoalPlot.h"
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(jsGoalPlot) {
	emscripten::class_<GoalPlot>("GoalPlot")
		.constructor<>()
		.smart_ptr<std::shared_ptr<GoalPlot>>("GoalPlot")
		.function("subscribeOnPlotChanged", &GoalPlot::subscribeOnPlotChanged)
		.function("unSubscribeOnPlotChanged", &GoalPlot::unSubscribeOnPlotChanged)
		.property("plot", &GoalPlot::plot)
		;
}

GoalPlot::GoalPlot()
{
}

const emscripten::val& GoalPlot::plot() const
{
	return m_plot;
}

void GoalPlot::subscribeOnPlotChanged(const emscripten::val& callback)
{
	m_onPlotChangeSubscribers.insert(callback);
}

void GoalPlot::unSubscribeOnPlotChanged(const emscripten::val& callback)
{
	m_onPlotChangeSubscribers.erase(callback);
}

void GoalPlot::onSolverStep()
{
	m_solverStep++;

	emscripten::val point = emscripten::val::object();
	point.set("x", (double)m_solverStep);
	point.set("y", randValue());
	m_plot.call<void>("push", point);

	notifyAboutPlotChanged();
}

void GoalPlot::notifyAboutPlotChanged()
{
	for (const emscripten::val& callback : m_onPlotChangeSubscribers)
		callback();
}

double GoalPlot::randValue()
{
	return static_cast<double>(rand()) / RAND_MAX;
}
