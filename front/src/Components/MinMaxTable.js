import * as React from 'react';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import { useState, useEffect } from 'react';
import { useLoadedMonitor } from '../Monitor';

export default function MinMaxTable() {
  const { monitor, readyState } = useLoadedMonitor();
  const [rows, setRows] = useState([]);

  useEffect(() => {
    const updateRows = () => {
      setRows(monitor.minMaxTable.table);
    };

    updateRows();
    monitor.minMaxTable.subscribeOnTableChanged(updateRows);
    // return () => {
    //     monitor.minMaxTable.unSubscribeOnTableChanged(updateRows);
    // }
  }, []);

  return (
    <TableContainer component={Paper}>
      <Table aria-label="simple table">
        <TableHead>
          <TableRow>
            <TableCell>Parameter</TableCell>
            <TableCell>Min</TableCell>
            <TableCell>Max</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {rows.map((row) => (
            <TableRow
              key={row.name}
              sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
            >
              <TableCell component="th" scope="row">
                {row.name}
              </TableCell>
              <TableCell>{Number(row.min).toFixed(2)}</TableCell>
              <TableCell>{Number(row.max).toFixed(2)}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  );
}
