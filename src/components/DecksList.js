import * as React from 'react';
import { useState } from 'react';
import { useNavigate } from "react-router-dom";
import { Table, Button } from 'react-bootstrap';
import { ReactComponent as TrashIcon } from '../assets/icons/trash.svg';
import { ReactComponent as EditIcon } from '../assets/icons/edit.svg';
import { ReactComponent as PlayIcon } from '../assets/icons/play.svg';
//Exemplo de dados que vamos receber do backend
const rows = [
  { title: 'title', subject: 'subject', id: 1 },
  { title: 'title', subject: 'subject', id: 2 },
  { title: 'title', subject: 'subject', id: 3 },
  { title: 'title', subject: 'subject', id: 4 },
  { title: 'title', subject: 'subject', id: 5 },
];

const DecksList = (props) => {
  const navigate = useNavigate();
  const [cardDelete, setCardDelete] = useState({});
  const [open, setOpen] = useState(false);
  const deleteCard = (i) => {
  
  }

  return (
    <Table variant='light' className=''>
      <thead>
        <tr>
          <th>Baralho</th>
          <th>Assunto</th>
          <th>Editar</th>
          <th>Deletar</th>
        </tr>
      </thead>
      <tbody>
        {props.decks.map((row, idx) => (
          <tr key={idx}>
            <td>{row.title}</td>
            <td>{row.subject}</td>
            <td><Button size='lg' variant='light'onClick={() => navigate(`/edit/pad/${row.id}`)}><EditIcon /></Button></td>
            <td><Button size='lg' variant='light'><TrashIcon /></Button></td>
          </tr>
        ))}
      </tbody>
    </Table>
  );
};

export default DecksList;
