import { Component } from 'react';
import ApplicationFrame from './Components/ApplicationFrame';
import '@fontsource/roboto/300.css';
import '@fontsource/roboto/400.css';
import '@fontsource/roboto/500.css';
import '@fontsource/roboto/700.css';
import { useMonitor, MONITOR_READY_STATE } from './Monitor';

const App = () => {
  const [MonitorProvider, monitorObject] = useMonitor();

  return (
    <MonitorProvider value={monitorObject}>
      <div id="App">
        {monitorObject.readyState === MONITOR_READY_STATE.READY && <ApplicationFrame />}
      </div>
    </MonitorProvider>
  );
};

export default App;
