import React from 'react';
import Container from '@mui/material/Container';
import Listar from '../components/Listar'
import Typography from '@mui/material/Typography';


const PadsPage = () => {
    return (
        <Container maxWidth="xm" sx={{
            gap: "10px",
            justifyContent: "center",
            alignItems: "center",
        }}>
            <Typography variant="h2" align="center" color='#0009' gutterBottom>
                Baralhos
            </Typography>
            <Listar />
        </Container>
    );
};

export default PadsPage;