#include "MinMaxTable.h"
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(jsMinMaxTable) {
	emscripten::class_<MinMaxTable>("MinMaxTable")
		.constructor<>()
		.smart_ptr<std::shared_ptr<MinMaxTable>>("MinMaxTable")
		.function("subscribeOnTableChanged", &MinMaxTable::subscribeOnTableChanged)
		.function("unSubscribeOnTableChanged", &MinMaxTable::unSubscribeOnTableChanged)
		.property("table", &MinMaxTable::table)
		;
}

MinMaxTable::MinMaxTable()
{
	generateData(true);
}

const emscripten::val& MinMaxTable::table() const
{
	return m_table;
}

void MinMaxTable::subscribeOnTableChanged(const emscripten::val& callback)
{
	m_onTableChangeSubscribers.insert(callback);
}

void MinMaxTable::unSubscribeOnTableChanged(const emscripten::val& callback)
{
	m_onTableChangeSubscribers.erase(callback);
}

void MinMaxTable::onSolverStep()
{
	generateData();
}

void MinMaxTable::generateData(bool init)
{
	static std::vector<std::string> names = {
		"Pressure",
		"Temperature",
		"Force",
		"Flow",
		"Density",
		"Mass"
	};

	m_table = emscripten::val::array();

	for (const std::string& name : names) 
	{
		emscripten::val row = emscripten::val::object();
		row.set("name", name);

		double min = 0.0;
		double max = 0.0;

		if (!init)
		{
			min = randValue();
			max = min + randValue();
		}

		row.set("min", min);
		row.set("max", max);

		m_table.call<void>("push", row);
	}

	notifyAboutTableChanged();
}

void MinMaxTable::notifyAboutTableChanged()
{
	for (const emscripten::val& callback : m_onTableChangeSubscribers)
		callback();
}

double MinMaxTable::randValue()
{
	return static_cast<double>(rand()) / RAND_MAX * 100;
}
