import React from "react";
import * as FlexLayout from "flexlayout-react";
import { createTheme, ThemeProvider } from '@mui/material/styles';
import Box from '@mui/material/Box';
import MonitorTopBar from "./MonitorTopBar";
import GoalPlot from "./GoalPlot";
import MinMaxTable from "./MinMaxTable";
import ModelView from "./ModelView";

const theme = createTheme({
    palette: {
        primary: {
            main: "#005a8c"
        },
        secondary: {
            main: "#fddc69"
        }
    },
});

const Placeholdah = () => {
    return <div className="placeholdah">Lorem ipsum dolor sit amet</div>;
};

var json = {
    global: {},
    borders: [
        {
            type: "border",
            location: "left",
            children: [
                {
                    type: "tab",
                    enableClose: false,
                    name: "Menu",
                    component: "placeholdah"
                }
            ]
        }
    ],
    layout: {
        type: "row",
        weight: 100,
        children: [
            {
                type: "tabset",
                weight: 50,
                selected: 0,
                children: [
                    {
                        type: "tab",
                        name: "Min Max Table",
                        component: "minMaxTable"
                    }
                ]
            },
            {
                type: "tabset",
                weight: 50,
                selected: 0,
                children: [
                    {
                        type: "tab",
                        name: "Goal Plot",
                        component: "goalPlot"
                    }
                ]
            },
            {
                type: "tabset",
                weight: 50,
                selected: 0,
                children: [
                    {
                        type: "tab",
                        name: "Model View",
                        component: "modelView"
                    }
                ]
            }
        ]
    }
};

export default class ApplicationFrame extends React.Component {
    constructor(props) {
        super(props);
        this.state = { model: FlexLayout.Model.fromJson(json) };
    }

    factory = (node) => {
        var component = node.getComponent();

        switch (component) {
            case "placeholdah":
                return <Placeholdah />;
            case "minMaxTable":
                return <MinMaxTable />;
            case "goalPlot":
                return <GoalPlot />;
            case "modelView":
                return <ModelView />;
        }
    }

    render() {
        return (
            <ThemeProvider theme={theme}>
                <Box
                    sx={{
                        display: 'flex',
                        flexDirection: 'column',
                        height: '100vh',
                        overflow: 'hidden'
                    }}>
                    <MonitorTopBar />
                    <Box
                        sx={{
                            display: 'flex',
                            flex: 1,
                            flexDirection: 'row',
                            height: 0,
                            position: 'relative'
                        }}>
                        <FlexLayout.Layout model={this.state.model} factory={this.factory} />
                    </Box>
                </Box>
            </ThemeProvider >
        )
    }
}
