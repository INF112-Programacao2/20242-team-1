import React from "react";
import { Link } from "react-router-dom";

import Container from 'react-bootstrap/Container';
import { Nav,Navbar } from "react-bootstrap";


function NavbarCostum() {
    return (
        <Navbar bg="light" data-bs-theme="light" style={{width:'100vw'}}>
            <Container >
                <Navbar.Brand href="/">Home</Navbar.Brand>
                <Nav.Link href="/pad">Baralhos</Nav.Link>
                <Nav.Link href="/settings">Configurações</Nav.Link>
                <Nav.Link href="/">Estatísticas</Nav.Link>
            </Container>
        </Navbar>
    );
}

export default NavbarCostum;