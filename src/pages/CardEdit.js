'use client';
import React, { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { Container } from 'react-bootstrap';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import { Accordion } from 'react-bootstrap';
import {ReactComponent as TextIcon} from '../assets/icons/card-text.svg';
import {ReactComponent as ImgIcon} from '../assets/icons/img.svg';
import {ReactComponent as MicIcon} from '../assets/icons/mic.svg';
const CardEdit = () => {
    const { id } = useParams();
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState(null); // Para armazenar os dados da API
    const [cardType, setCardType]= useState(0);
    const [file, setFile] = useState(null); // Para armazenar o arquivo selecionado
    const [text, setText] = useState(null);
    const [audio, setAudio] = useState(null);
 
    const handleFileChange = (e) => {
        setFile(e.target.files[0]); // Armazena o arquivo selecionado no estado
      };
    
      const handleSubmit = async (e) => {
        e.preventDefault();

        if (file) {
          const formData = new FormData();
          console.log(file)
          formData.append('image', file);
    
          try {
            const response = await fetch('http://localhost:3000/api/upload', {
              method: 'POST',
              body: formData,
            });
            console.log(response)
            if (!response.ok) {
              throw new Error('Failed to upload file');
            }
    
            console.log('File uploaded successfully:');
          } catch (error) {
            console.error('Error uploading file:', error);
          }
        } else {
          console.log('No file selected for upload');
        }
      };
    
    useEffect(() => {
        async function fetchData() {
            if (id) {
                try {
                    const response = await fetch(`http://localhost:3000/api/card/${id}`);
                    const result = await response.json();
                    setData(result); // Armazena os dados na variável de estado
                } catch (error) {
                    console.error('Error fetching data:', error);
                } finally {
                    setLoading(false);
                }
            } else {
                setLoading(false);
            }
        }

        fetchData();
    }, [id]);

    if (loading) {
        return (
            <Container fluid="xl" responsive="xl">
                <h2>Loading...</h2>
            </Container>
        );
    }

    if (!data && id) {
        return (
            <Container fluid="xl" responsive="xl">
                <h2>No data found</h2>
            </Container>
        );
    }

    return (
        <Container fluid="xl" responsive="xl">
            <h2>Edição</h2>
            <Form onSubmit={handleSubmit}>
                <Form.Group className="mb-3" controlId="formBasiTitle">
                    <Form.Label>Frente</Form.Label>
                    <Form.Control type="Text" placeholder="Adicione o nome do baralho" />
                </Form.Group>

                <Form.Group className="mb-3" controlId="formBasicSubject">
                    
                </Form.Group>
                <Form.Group className="mb-3">
                    <Accordion defaultActiveKey={cardType}>
                        <Accordion.Item eventKey="0" onClick={()=>setCardType(0)}>
                            <Accordion.Header>Texto <TextIcon/></Accordion.Header>
                            <Accordion.Body>
                            <Form.Label>Assunto</Form.Label>
                            <Form.Control type="text" placeholder="Adicione o assunto" />
                            </Accordion.Body>
                        </Accordion.Item>
                        <Accordion.Item eventKey="1" onClick={()=>setCardType(1)}>
                            <Accordion.Header>Imagem <ImgIcon/></Accordion.Header>
                            <Accordion.Body>
                                <Form.Label>Default file input example</Form.Label>
                                <Form.Control type="file" onChange={handleFileChange}/>
                            </Accordion.Body>
                        </Accordion.Item>
                        <Accordion.Item eventKey="2" onClick={()=>setCardType(2)}>
                            <Accordion.Header>Audio <MicIcon/></Accordion.Header>
                            <Accordion.Body>
                                <Form.Label>Default file input example</Form.Label>
                                <Form.Control type="file" />
                            </Accordion.Body>
                        </Accordion.Item>
                    </Accordion>
                </Form.Group>

                <Button variant="secondary" type="submit" size="lg" onSubmit={handleSubmit}>
                    Submit
                </Button>
            </Form>
        </Container>
    );
};

export default CardEdit;
