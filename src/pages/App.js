import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import NavbarCostum from "../components/NavbarCostum";
import Home from "./Home";
import DecksPage from "./DecksPage";
import CardsReview from "./CardsReview";
import Settings from "./Settings";
import DeckEdit from "./DeckEdit";
import 'bootstrap/dist/css/bootstrap.min.css';
import '../style/main.scss'
import CardEdit from "./CardEdit";
import CardNew from "./CardNew";
import CardAudioNew from "./CardAudioNew";
import CardImageNew from "./CardImageNew";
import CarAudiodEdit from "./CardAudioEdit";
import CardTODO from "./CardTODO";
function App() {
    return (
        <BrowserRouter>
            <NavbarCostum />
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/deck" element={<DecksPage />} />
                <Route path="/deck/:id" element={<CardsReview />} />
                <Route path="/settings" element={<Settings />} />
                <Route path="/edit/deck/:id?" element={<DeckEdit />} />
                <Route path="/card/edit/:id" element={<CardEdit/>} />
                <Route path="/card/new/:id" element={<CardNew/>} />
                <Route path="/audio/new/:id" element={<CardAudioNew/>} />
                <Route path="/image/edit/:id" element={<CardTODO/>} />
                <Route path="/audio/edit/:id" element={<CardTODO/>} />
                <Route path="/image/new/:id" element={<CardImageNew/>} />
            </Routes>
        </BrowserRouter>
    );
}

export default App;
