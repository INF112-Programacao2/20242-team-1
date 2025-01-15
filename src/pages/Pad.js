import React, { useEffect, useState } from 'react';
import { Container } from 'react-bootstrap';
import { useParams } from "react-router-dom";

import Card from 'react-bootstrap/Card';
import Button from 'react-bootstrap/Button';
import ButtonGroup from 'react-bootstrap/ButtonGroup';

let cards = [{ id: 1, front: "Frente 1", back: "Verso 1", pad_id: 1, level_time_id: 1, last_review: new Date() },
{ id: 2, front: "Frente 2", back: "Verso 2", pad_id: 2, level_time_id: 2, last_review: new Date() },
{ id: 3, front: "Frente 3", back: "Verso 3", pad_id: 3, level_time_id: 3, last_review: new Date() }
]
const Pad = () => {
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
        <Container>
            {finish ?
                <h5>Não há mais revisões !</h5>
                : <> <Card
                    bg="LIGHT"
                    key="Light"
                    text="Light"
                    style={{ width: '18rem' }}
                    className="mb-2">
                    <Card.Body>
                        <Card.Title>
                            <h5>
                                {card.front ?? ""}
                            </h5>
                        </Card.Title>
                        {visibleBack && <Card.Text>
                            <h6>{card.back ?? ""}</h6>
                        </Card.Text>}
                    </Card.Body>
                </Card>
                    {visibleBack ? <ButtonGroup aria-label="Basic button group">
                        <Button variant="secondary" onClick={() => nextCard(cards)}> Next</Button>
                    </ButtonGroup> : <ButtonGroup variant="contained" aria-label="Basic button group">
                        {levelTime.map((level) => {
                            return <Button variant="secondary" key={level.id} onClick={() => setVsibleBackFinish(true)}>{level.title}</Button>
                        })}
                    </ButtonGroup>}
                </>
            }

        </Container>
    );
};

export default Pad;