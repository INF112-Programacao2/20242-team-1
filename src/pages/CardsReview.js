import React, { useEffect, useState } from 'react';
import { Container, Row } from 'react-bootstrap';
import { useParams } from "react-router-dom";

import Card from 'react-bootstrap/Card';
import Button from 'react-bootstrap/Button';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import { ReactComponent as SmileIcon } from '../assets/icons/smile.svg';

const CardsReview = () => {
    const [cards, setCards] = useState([{ id: null, front: "", back: "", pad_id: 1, level_time_id: 1, lastReview: new Date() }])
    const [n, setN] = useState(0);
    const [data, setData] = useState([]);
    const [loading, setLoading] = useState(true);
    const [finish, setFinish] = useState(true);
    const [visibleBack, setVsibleBackFinish] = useState(false)
    const { id } = useParams();

    const levelTime = [
        {
            id: 1,
            time: (60 * 1000), // 1 minuto
            title: "De novo"
        }, {
            id: 2,
            time: (10 * 60 * 1000), // 10 minutos
            title: "Difícil"
        },
        {
            id: 3,
            time: (24 * 60 * 60 * 1000), // 1 dia
            title: "Bom"
        },
        {
            id: 4,
            time: (7 * 24 * 60 * 60 * 1000), // 1 semana
            title: "Fácil"
        }]


    const nextCard = () => {
        const valor = n + 1;
        if (cards.length == valor) {
            setFinish(true);
        } else {
            setN(valor);
            setVsibleBackFinish(false);
        }
    };

    const updateLastRevision = async (i) => {
        const futureDate = new Date();
        futureDate.setTime(futureDate.getTime() + levelTime[i].time);

        const day = futureDate.getDate();
        const month = futureDate.getUTCMonth() + 1;
        const year = futureDate.getFullYear();
        const hour = futureDate.getHours();
        const minute = futureDate.getMinutes();
        const second = futureDate.getSeconds();
        const formData = new FormData();
        const type = cards[n].back !== undefined ? '0' : cards[n].audio !== undefined ? '1' : '2';
        formData.append('type', type);
        formData.append('day', day);
        formData.append('month', month);
        formData.append('year', year);
        formData.append('hour', hour);
        formData.append('minute', minute);
        formData.append('second', second);
        setVsibleBackFinish(true)
        try {
            const response = await fetch(`http://localhost:3000/api/card/lastreview/${cards[n].id}`, {
                method: 'PUT',
                body: formData,
            });
            if (!response.ok) {
                throw new Error('Failed to upload image');
            } else {

            }

        } catch (error) {
            console.error('Error uploading image:', error);
        }

    }

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await fetch(`http://localhost:3000/api/card/reviews/${id}`, {
                    headers: {
                        'Cache-Control': 'no-store',
                    }
                });
                const data = await response.json();
                setCards(data)
            } catch (error) {
                console.error('Erro ao buscar os dados:', error);
            } finally {
                setLoading(false);
                setFinish(false);
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

    return (
        <Container className='cardPageContaier' variant='light'>
            {finish ?
                <div className='align-self-center py-4'>
                    <h4>Não há mais revisões ! <SmileIcon /></h4>
                </div>
                : <> <Card
                    bg="LIGHT"
                    key="Light"
                    text="Light">
                    <Card.Body>
                        <Card.Title>
                            <h4>
                                {cards[n].front ?? ""}
                            </h4>

                        </Card.Title>
                        {visibleBack && (
                            cards[n]?.back !== undefined ? (
                                <Card.Text>{cards[n]?.back}</Card.Text>
                            ) : cards[n]?.audio !== undefined ? (
                                <audio controls>
                                    <source src={`http://localhost:3000/dist/assets/uploads/${cards[n].id}sound.webm`} type="audio/webm" />
                                    Seu navegador não suporta o elemento de áudio.
                                </audio>
                            ) : (
                                <Card.Img variant="top" src={`http://localhost:3000/dist/assets/uploads/${cards[n].id}image.png`} />
                            )
                        )}

                    </Card.Body>
                </Card>
                    {visibleBack ? <ButtonGroup aria-label="Basic button group" className='bottom'>
                        <Button variant="secondary" onClick={() => nextCard()}> Next</Button>
                    </ButtonGroup> : <ButtonGroup variant="contained" aria-label="Basic button group">
                        {levelTime.map((level, idx) => {
                            return <Button className='bottom' variant="secondary" key={level.id} onClick={() => updateLastRevision(idx)}>{level.title}</Button>
                        })}
                    </ButtonGroup>}
                </>
            }

        </Container>
    );
};

export default CardsReview;