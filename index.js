// index.js
const express = require('express');
const path = require('path');
const myclass = require('./build/Release/myclass.node'); // Módulo C++ compilado

const app = express();
const port = 3000;
// Servir arquivos estáticos (como HTML, CSS, JS)
app.use(express.static(path.join(__dirname, 'dist')));

// Rota principal
app.get(['/','/pad'], (req, res) => {
  res.sendFile(path.join(__dirname, 'dist', 'index.html'));
});

app.get('/api/greet/:name', (req, res) => {
    const name = req.params.name;
    const greeting = myclass.greet(name); // Chama a função C++
    res.json({ message: greeting });
});

app.listen(port, () => {
    console.log(`API running on http://localhost:${port}`);
});
