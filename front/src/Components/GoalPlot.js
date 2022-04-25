import React, { useState, useEffect } from "react";
import Chart from "react-apexcharts";
import { Component } from 'react';
import { VictoryChart, VictoryLine, VictoryTheme } from 'victory';
import { useLoadedMonitor } from '../Monitor';

export default function GoalPlot(props) {
	const [data, updateData] = useState([{
		x: 0,
		y: 0
	}]);
	const { monitor, readyState } = useLoadedMonitor();

	useEffect(() => {
		const updatePlot = () => {
			updateData(monitor.goalPlot.plot);
		};

		monitor.goalPlot.subscribeOnPlotChanged(updatePlot);
		updateData();
		// return () => {
		//     monitor.goalPlot.unSubscribeOnPlotChanged(updatePlot);
		// }
	}, [data]);

	const series = [
		{
			name: "Goal",
			data: data
		}
	];
	const options = {
		chart: {
			type: "line",
		},
		xaxis: {
			type: 'numeric',
			min: 0,
			max: 100,
			title: {
				text: 'Iterations'
			},
			labels: {
				formatter: function (val) {
					return val.toFixed(0);
				}
			}
		},
		yaxis: {
			min: 0,
			max: 1,
			tickAmount: 6,
			labels: {
				formatter: function (val) {
					return val.toFixed(2);
				}
			}
		},
		dataLabels: {
			enabled: false
		},
		toolbar: {
			show: false
		},
		zoom: {
			enabled: false
		}
	};

	return (
		<Chart options={options} series={series} type="line" height="500" />
	);
}
