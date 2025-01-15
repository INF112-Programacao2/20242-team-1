import React from 'react';
import PadsList from '../components/PadsList'
import { Container } from 'react-bootstrap';

const PadsPage = () => {
    return (
        <Container fluid="xl">
            <h2>Baralhos</h2>
            <PadsList />
        </Container>
    );
};

export default PadsPage;