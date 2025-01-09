import * as React from 'react';
import { useNavigate } from "react-router-dom";

import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import IconButton from '@mui/material/IconButton';
import DeleteIcon from '@mui/icons-material/Delete';
import EditIcon from '@mui/icons-material/Edit';
import PlayArrowIcon from '@mui/icons-material/PlayArrow';

//Exemplo de dados que vamos receber do backend
const rows = [
  { title: 'title', subject: 'subject', id: 1 },
  { title: 'title', subject: 'subject', id: 2 },
  { title: 'title', subject: 'subject', id: 3 },
  { title: 'title', subject: 'subject', id: 4 },
  { title: 'title', subject: 'subject', id: 5 },
];

const Listar = () => {
  const navigate = useNavigate();

  const handleClick = ( id) => {
    navigate(`/pad/${id}`);
  };
  // Estado para armazenar o número de cliques
  //const [clickCount, setClickCount] = useState('');

  // Função para lidar com o clique no botão
 /* const handleClick = async () => {
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
    <TableContainer component={Paper}>
      <Table sx={{ minWidth: 650 }} aria-label="simple table">
        <TableHead>
          <TableRow>
            <TableCell>Baralho</TableCell>
            <TableCell align="right">Assunto</TableCell>
            <TableCell align="right">Jogar</TableCell>
            <TableCell align="right">Editar</TableCell>
            <TableCell align="right">Deletar</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {rows.map((row) => (
            <TableRow
              key={row.id}
              sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
            >
              <TableCell component="th" scope="row">
                {row.title}
              </TableCell>
              <TableCell align="right">{row.subject}</TableCell>
              <TableCell align="right"><IconButton aria-label="Jogar" size="small" onClick={()=>handleClick(row.id)}>
                <PlayArrowIcon fontSize="small" />
              </IconButton></TableCell>
              <TableCell align="right"><IconButton aria-label="Editar" size="small">
                <EditIcon fontSize="small" />
              </IconButton></TableCell>
              <TableCell align="right"><IconButton aria-label="Deletar" size="small">
                <DeleteIcon fontSize="small" />
              </IconButton></TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  );
};

export default Listar;
