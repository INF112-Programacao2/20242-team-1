import * as React from 'react';
import { useState } from 'react';
import { useNavigate } from "react-router-dom";
import { ReactComponent as TrashIcon } from '../assets/icons/trash.svg';


import Table from 'react-bootstrap/Table';

//Exemplo de dados que vamos receber do backend
const rows = [
  { name: 'name', id: 1 },
  { name: 'name', id: 2 },
  { name: 'name', id: 3 },
  { name: 'name', id: 4 },
  { name: 'name', id: 5 },
];

const LevelsTimeList = () => {
  const navigate = useNavigate();

  return (
      <Table hover responsive="lg">
        <thead>
          <tr>
            <th>Nível</th>
            <th>Editar</th>
            <th>Deletar</th>
          </tr>
        </thead>
        <tbody>
          {rows.map((row, idx) => (
            <tr key={`row-${row.id}`}>
              <td component="th" scope="row">
                {row.name}
              </td>
              <td>Edit<i className="bi bi-pen"></i></td>
              <td><TrashIcon/></td>
            </tr>
          ))}
        </tbody>
      </Table>
  );
};

export default LevelsTimeList;
