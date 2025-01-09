import React from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import { useParams } from "react-router-dom";


const Pad = () => {
    const { id } = useParams();
    console.log(id)
    return (
        <Container maxWidth="xm" sx={{
            gap: "10px",
            justifyContent: "center",
            alignItems: "center",
        }}>
            <Typography variant="h2" align="center" color='#0009' gutterBottom>
                Baralhos
            </Typography>
        </Container>
    );
};

export default Pad;