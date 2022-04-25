import { createContext, useState, useContext, useEffect } from 'react';

export const MonitorContext = createContext();
export const MONITOR_READY_STATE = {
    ERROR: -2,
    NOT_READY: 0,
    READY: 1,
};

var loadWASMModuleCalled = false; //TODO

export const useMonitor = () => {
    const [monitorObject, setMonitorObject] = useState({ monitor: null, readyState: MONITOR_READY_STATE.NOT_READY });

    useEffect(() => {
        if (loadWASMModuleCalled)
            return;

        window.loadWASMModule()
            .then((module) => {
                console.log('wasm monitor loaded');
                const monitor = new module.Monitor();
                setMonitorObject({ monitor, readyState: MONITOR_READY_STATE.READY });
                setInterval(function () {
                    monitor.timerTick();
                }, 500);

            }).catch(error => {
                console.log('wasm monitor error' + error);
                setMonitorObject({ monitor: null, readyState: MONITOR_READY_STATE.ERROR });
            });
        loadWASMModuleCalled = true;
    }, []);

    return [MonitorContext.Provider, monitorObject];
};

export const useLoadedMonitor = () => {
    const { monitor, readyState } = useContext(MonitorContext);

    return { monitor, readyState };
};