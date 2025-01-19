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

const PadsList = () => {
  const navigate = useNavigate();
  const [cardDelete, setCardDelete] = useState({});
  const [open, setOpen] = useState(false);

  const deleteCard = (i) => {
    if (i == -1) {
      setCardDelete({});
    } else {
      setCardDelete(rows[i]);
    }
  }
  // Estado para armazenar o número de cliques
  //const [clickCount, setClickCount] = useState('');

  // Função para lidar com o clique no botão
  /* const navigateClick = async () => {
     try {
       const response = await fetch(`http://localhost:3000/api/greet/sabrina`);
       const data = await response.json();
       console.log(data)
       setClickCount(data.message);
     } catch (error) {
       console.error('Error fetching data:', error);
     }
   };*/

  return (
    <Table variant='light' className=''>
      <thead>
        <tr>
          <th>Baralho</th>
          <th>Assunto</th>
          <th>Jogar</th>
          <th>Editar</th>
          <th>Deletar</th>
        </tr>
      </thead>
      <tbody>
        {rows.map((row, idx) => (
          <tr key={idx}>
            <td>{row.title}</td>
            <td>{row.subject}</td>
            <td><Button size='lg' variant='light' onClick={() => navigate(`/pad/${row.id}`)}><PlayIcon /></Button></td>
            <td><Button size='lg' variant='light'onClick={() => navigate(`/edit/pad/${row.id}`)}><EditIcon /></Button></td>
            <td><Button size='lg' variant='light'><TrashIcon /></Button></td>
          </tr>
        ))}
      </tbody>
    </Table>
  );
};

export default PadsList;
