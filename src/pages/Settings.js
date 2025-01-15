import React from 'react';
import { Container } from 'react-bootstrap';
import LevelsTimeList from '../components/LevelsTimeList';


const Settings = () => {
    return (
        <Container fluid="xl" responsive="xl">
            <h2>Configurações</h2>
            <LevelsTimeList />
        </Container>
    );
};

export default Settings;