import React, { useEffect, useState } from 'react';
import { useParams } from "react-router-dom";
import { Container } from 'react-bootstrap';
const PadEdit = () => {
    const { id } = useParams();
    return (
        <Container>
            <h2>Configurações do Baralho {id}</h2>
        </Container>
    );
}
export default PadEdit;