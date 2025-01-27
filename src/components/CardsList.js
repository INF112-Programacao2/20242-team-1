import * as React from 'react';
import { useState } from 'react';
import { useNavigate } from "react-router-dom";
import { Table, Button } from 'react-bootstrap';
import DeleteButton from './DeleteButton';
import { ReactComponent as EditIcon } from '../assets/icons/edit.svg';

const CardsList = (props) => {
    const navigate = useNavigate();
    return (
        <Table variant='light' className=''>
            <thead>
                <tr>
                    <th>Card</th>
                    <th>Editar</th>
                    <th>Deletar</th>
                </tr>
            </thead>
            <tbody>
                {props.cards.map((card, idx) => (
                    <tr key={idx}>
                        <td>{card.front}</td>
                        <td><Button size='lg' variant='light' onClick={() => navigate(`/card/edit/${card.id}`)}><EditIcon /></Button></td>
                        <td><DeleteButton  url={`card/${card.id}`}/></td>
                    </tr>
                ))}
                <tr><td colSpan={3}><Button size='sm' variant='secondary' onClick={() => navigate(`/card/new/${props.id}`)}> + Novo</Button></td></tr>
            </tbody>
        </Table>
    );
};

export default CardsList;
