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

function App() {
    return (
        <BrowserRouter>
            <NavbarCostum />
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/pad" element={<DecksPage />} />
                <Route path="/pad/:id" element={<CardsReview />} />
                <Route path="/settings" element={<Settings />} />
                <Route path="/edit/pad/:id" element={<DeckEdit />} />
                <Route path="/card/:id?" element={<CardEdit/>} />
            </Routes>
        </BrowserRouter>
    );
}

export default App;
