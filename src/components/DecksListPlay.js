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
          <th>Revisões</th>
          <th>Jogar</th>
        </tr>
      </thead>
      <tbody>
        {props.decks.map((row, idx) => (
          <tr key={idx}>
            <td>{row.title}</td>
            <td>{row.reviews}</td>
            <td>{row.reviews == 0 ? <Button size='lg' variant='light' disabled><PlayIcon /></Button> : <Button size='lg' variant='light' onClick={() => navigate(`/deck/${row.id}`)} ><PlayIcon /></Button>}</td>
          </tr>
        ))}
      </tbody>
    </Table>
  );
};

export default DecksListPlay;
