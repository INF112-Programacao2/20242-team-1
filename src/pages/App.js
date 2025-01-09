import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Navbar from "../components/Navbar";
import Home from "./Home";
import PadsPage from "./PadsPage";
import Pad from "./Pad";
function App() {
    return (
        <BrowserRouter>
            <Navbar />
            <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/pad" element={<PadsPage />} />
                <Route path="pad/:id" element={<Pad />} />
            </Routes>
        </BrowserRouter>
    );
}

export default App;
