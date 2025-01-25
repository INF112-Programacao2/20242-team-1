import React, { useEffect, useState } from 'react';
import { useParams } from "react-router-dom";
import { Container } from 'react-bootstrap';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import CardsList from '../components/CardsList';

const DeckEdit = () => {
    const { id } = useParams();
    // consulta o backend
    //Exemplo de dados que vamos receber do backend
    const cards = [
        { front: 'front', id: 1 },
        { front: 'front', id: 2 },
        { front: 'front', id: 3 },
        { front: 'front', id: 4 },
        { front: 'front', id: 5 },
    ];

    // Card find all: pegar somente o front e o id
    return (
        <Container>
            <h2>Edição</h2>
            <Form>
                <Form.Group className="mb-3" controlId="formBasiTitle">
                    <Form.Label>Título</Form.Label>
                    <Form.Control type="Text" placeholder="Adicione o nome do baralho" />
                </Form.Group>

                <Form.Group className="mb-3" controlId="formBasicSubject">
                    <Form.Label>Assunto</Form.Label>
                    <Form.Control type="text" placeholder="Adicione o assunto" />
                </Form.Group>
                <Form.Group className="mb-3">
                    <CardsList cards={cards} />
                </Form.Group>

                <Button variant="secondary" type="submit" size="lg">
                    Submit
                </Button>
            </Form>
        </Container>

    );
}
export default DeckEdit;