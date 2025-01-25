import React from "react";

import Container from 'react-bootstrap/Container';
import { Nav,Navbar } from "react-bootstrap";
import { ReactComponent as GearIcon } from '../assets/icons/gear.svg';
import { ReactComponent as CardIcon } from '../assets/icons/card.svg';
import { ReactComponent as StatsIcon } from '../assets/icons/stats.svg';

function NavbarCostum() {
    return (
        <Navbar bg="light" data-bs-theme="light" style={{width:'100vw'}}>
            <Container >
                <Navbar.Brand href="/">Home</Navbar.Brand>
                <Nav.Link href="/deck">Baralhos <CardIcon/></Nav.Link>
                <Nav.Link href="/settings">Configurações <GearIcon/></Nav.Link>
            </Container>
        </Navbar>
    );
}

export default NavbarCostum;