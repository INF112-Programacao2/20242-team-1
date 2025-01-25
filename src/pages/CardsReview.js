import React, { useEffect, useState } from 'react';
import { Container, Row } from 'react-bootstrap';
import { useParams } from "react-router-dom";

import Card from 'react-bootstrap/Card';
import Button from 'react-bootstrap/Button';
import ButtonGroup from 'react-bootstrap/ButtonGroup';
import { ReactComponent as SmileIcon } from '../assets/icons/smile.svg';
let cards = [{ id: 1, front: "Frente 1", back: "Verso 1", pad_id: 1, level_time_id: 1, last_review: new Date() },
{ id: 2, front: "Frente 2", back: "Verso 2", pad_id: 2, level_time_id: 2, last_review: new Date() },
{ id: 3, front: "Frente 3", back: "Verso 3", pad_id: 3, level_time_id: 3, last_review: new Date() }
]
const CardsReview = () => {
    const [card, setCard] = useState({ id: null, front: "", back: "", pad_id: 1, level_time_id: 1, last_review: new Date() })
    const [finish, setFinish] = useState(false)
    const [visibleBack, setVsibleBackFinish] = useState(false)
    const { id } = useParams();

    const levelCollection = {
        id: 1,
        name: "Level Fácil"
    }
    const levelTime = [{
        id: 1,
        time: new Date(),
        ob: "Obs",
        title: "Fácil"
    },
    {
        id: 2,
        time: new Date(),
        ob: "Obs",
        title: "Médio"
    },
    {
        id: 3,
        time: new Date(),
        ob: "Obs",
        title: "Difícil"
    }]


    const nextCard = (cards) => {
        if (cards.length == 0) {
            setFinish(true);
        } else {
            setCard(cards.shift());
            setVsibleBackFinish(false);
        }
    };

    if (card.id == null) {
        setCard(cards.shift());
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
                                {card.front ?? ""}
                            </h4>
                        </Card.Title>
                        {visibleBack && <Card.Text>{card.back ?? ""}
                        </Card.Text>}
                    </Card.Body>
                </Card>
                    {visibleBack ? <ButtonGroup aria-label="Basic button group" className='bottom'>
                        <Button variant="secondary" onClick={() => nextCard(cards)}> Next</Button>
                    </ButtonGroup> : <ButtonGroup variant="contained" aria-label="Basic button group">
                        {levelTime.map((level) => {
                            return <Button className='bottom' variant="secondary" key={level.id} onClick={() => setVsibleBackFinish(true)}>{level.title}</Button>
                        })}
                    </ButtonGroup>}
                </>
            }

        </Container>
    );
};

export default CardsReview;