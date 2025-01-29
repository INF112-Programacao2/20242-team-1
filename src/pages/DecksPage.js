'use client';

import React, { useEffect, useState } from 'react';
import DecksList from '../components/DecksList';
import { Container } from 'react-bootstrap';

const DecksPage = () => {
    const [data, setData] = useState([]);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch('http://localhost:3000/api/decks');
                const result = await response.json();
                setData(result);
            } catch (error) {
                console.error('Erro ao buscar os dados:', error);
            } finally {
                setLoading(false);
            }
        };

        fetchData(); // Chama a função dentro do useEffect
    }, []);
    if (loading) {
        return (
            <Container fluid="xl">
                <h2>Carregando...</h2>
            </Container>
        );
    }



    return (
        <Container fluid="xl">
            <h2>Baralhos</h2>
            {loading??  <h2>Carregando...</h2>}
            <DecksList decks={data} />
        </Container>
    );
};

export default DecksPage;
