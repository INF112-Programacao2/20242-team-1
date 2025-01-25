'use client';

import React, { useEffect, useState } from 'react';
import { Container } from 'react-bootstrap';
import DecksListPlay from '../components/DecksListPlay';
const Home = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch('http://localhost:3000/api/decks', {
          headers: {
            'Cache-Control': 'no-store',
          }
        });
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

  if (!data || data.length === 0) {
    return (
      <Container fluid="xl">
        <h2>Nenhum baralho encontrado.</h2>
      </Container>
    );
  }
  return (
    <Container fluid="xl">
      <h2>Baralhos</h2>
      <DecksListPlay decks={data} />
    </Container>
  );
};

export default Home;
