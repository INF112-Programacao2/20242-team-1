import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import NavbarCostum from "../components/NavbarCostum";
import Home from "./Home";
import PadsPage from "./PadsPage";
import Pad from "./Pad";
import Settings from "./Settings";
import PadEdit from "./PadEdit";
import 'bootstrap/dist/css/bootstrap.min.css';
import './style.css';

function App() {
    return (
        <BrowserRouter>
            <NavbarCostum />
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/pad" element={<PadsPage />} />
                <Route path="/pad/:id" element={<Pad />} />
                <Route path="/settings" element={<Settings />} />
                <Route path="/edit/pad/:id" element={<PadEdit />} />
            </Routes>
        </BrowserRouter>
    );
}

export default App;
