import React, { useEffect, useState } from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import { useParams } from "react-router-dom";

import Card from '@mui/material/Card';
import CardContent from '@mui/material/CardContent';
import Button from '@mui/material/Button';
import ButtonGroup from '@mui/material/ButtonGroup';
import NavigateNextIcon from '@mui/icons-material/NavigateNext';

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
        <Container maxWidth="xm" sx={{
            height: "90%",
            display: 'flex',
            alignItems: 'center',
            flexDirection: 'column',
            gap: '2vh',
            padding: '2vh'
        }}>
            {finish ?
                <Typography variant="h5" component="div">
                    Não há mais revisões !
                </Typography> : <> <Card sx={{ minWidth: '70vw', minHeight: '70vh' }}>
                    <CardContent>
                        <Typography variant="h5" component="div">
                            {card.front ?? ""}
                        </Typography>
                    </CardContent>
                    {visibleBack && <CardContent>
                        <Typography variant="h6" component="div">
                            {card.back ?? ""}
                        </Typography>
                    </CardContent>}
                </Card>
                    {visibleBack ? <ButtonGroup variant="contained" aria-label="Basic button group">
                        <Button onClick={() => nextCard(cards)}> <NavigateNextIcon></NavigateNextIcon></Button>
                    </ButtonGroup> : <ButtonGroup variant="contained" aria-label="Basic button group">
                        {levelTime.map((level) => {
                            return <Button key={level.id} onClick={() => setVsibleBackFinish(true)}>{level.title}</Button>
                        })}
                    </ButtonGroup>}
                </>
            }

        </Container>
    );
};

export default Pad;