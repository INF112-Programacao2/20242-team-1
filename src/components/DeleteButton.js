import * as React from 'react';
import { useState } from 'react';
import { useNavigate } from "react-router-dom";
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import { ReactComponent as TrashIcon } from '../assets/icons/trash.svg';

function DeleteButton({ url }) {
    const navigate = useNavigate();
    const [show, setShow] = useState(false);

    const handleClose = () => setShow(false);
    const handleShow = () => setShow(true);

    const handleContinue = async () => {
        if(url){
            try {
                const response = await fetch(`http://localhost:3000/api/${url}`, {
                  method: 'DELETE',
                });
                const result = await response.json();
                if(result){
                    window.location.reload(); 
                }
              } catch (error) {
                console.error('Erro ao buscar os dados:', error);
              }
          }
        setShow(false)
    };
    return (
        <>
            <Button size='lg' variant='light' onClick={handleShow}><TrashIcon /></Button>

            <Modal show={show} onHide={handleClose}>
                <Modal.Header closeButton>
                    <Modal.Title>Atenção</Modal.Title>
                </Modal.Header>
                <Modal.Body>Tem certeza de que quer continuar a exclusão?</Modal.Body>
                <Modal.Footer>
                    <Button variant="secondary" onClick={handleClose}>
                        Não
                    </Button>
                    <Button variant="primary" onClick={handleContinue}>
                        Continuar
                    </Button>
                </Modal.Footer>
            </Modal>
        </>
    );
}

export default DeleteButton;