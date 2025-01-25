import * as React from 'react';
import { useNavigate } from "react-router-dom";
import { Table, Button } from 'react-bootstrap';
import { ReactComponent as PlayIcon } from '../assets/icons/play.svg';


const DecksListPlay = (props) => {
  const navigate = useNavigate();

  return (
    <Table variant='light' className=''>
      <thead>
        <tr>
          <th>Baralho</th>
          <th>Jogar</th>
        </tr>
      </thead>
      <tbody>
        {props.decks.map((row, idx) => (
          <tr key={idx}>
            <td>{row.title}</td>
            <td><Button size='lg' variant='light' onClick={() => navigate(`/pad/${row.id}`)}><PlayIcon /></Button></td>
          </tr>
        ))}
      </tbody>
    </Table>
  );
};

export default DecksListPlay;
