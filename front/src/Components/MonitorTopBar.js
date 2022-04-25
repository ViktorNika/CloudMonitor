import { useState, useEffect } from 'react';
import AppBar from '@mui/material/AppBar';
import Toolbar from '@mui/material/Toolbar';
import IconButton from '@mui/material/IconButton';
import PlayCircleFilledWhiteIcon from '@mui/icons-material/PlayCircleFilledWhite';
import PauseCircleFilledIcon from '@mui/icons-material/PauseCircleFilled';
import StopCircleIcon from '@mui/icons-material/StopCircle';
import { useLoadedMonitor } from '../Monitor';

export default function MonitorTopBar() {
    const { monitor, readyState } = useLoadedMonitor();
    const [calculation, setCalculation] = useState(false);

    useEffect(() => {
        const updateCalculationState = () => {
            setCalculation(monitor.calculation);
        };

        monitor.subscribeOnCalculationChanged(updateCalculationState);
        // return () => {
        //     monitor.unSubscribeOnCalculationChanged(updateCalculationState);
        // }
    }, []);

    function CalculationButtonIcon() {
        if (calculation)
            return <PauseCircleFilledIcon /> 
        else
            return <PlayCircleFilledWhiteIcon />
    }

    return (
        <AppBar position="static" elevation={0}>
            <Toolbar>
                <IconButton
                    size="large"
                    color="inherit"
                    onClick={() => {
                        monitor.calculation = !monitor.calculation;
                    }}
                >
                    <CalculationButtonIcon/>
                </IconButton>
                <IconButton
                    size="large"
                    color="inherit"
                    onClick={() => {
                        monitor.calculation = false;
                    }}
                >
                    <StopCircleIcon/>
                </IconButton>
            </Toolbar>
        </AppBar>
    )
}
