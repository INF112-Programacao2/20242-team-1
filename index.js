const express = require('express');
const fs = require('fs');
const path = require('path');
const addon = require('./build/Release/addon.node');
//const deck = require('./build/Release/deck.node');
//const myclass = require('./build/Release/myclass.node'); // Módulo C++ compilado
const fileUpload = require('express-fileupload');

const app = express();
const port = 3000;

// Middleware para permitir upload de arquivos
app.use(fileUpload());

// Servir arquivos estáticos (como HTML, CSS, JS)
app.use(express.static(path.join(__dirname, 'dist')));

// Rota principal
app.get('*', (req, res, next) => {
  // Verifica se a rota começa com '/api'
  if (req.path.startsWith('/api')) {
    return next(); // Deixe a requisição continuar para os handlers da API
  }

  // Redireciona todas as outras rotas para o 'index.html'
  res.sendFile(path.join(__dirname, 'dist', 'index.html'));
});
// Pega todos os baralhos 
app.get('/api/decks', (req, res) => {
  try {
    const decks = addon.getDeckAll();
    res.json(decks);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
// Pega todos um baralho por id 
app.get('/api/deck/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const deck = addon.getDeckById(id);
    const cards = addon.getCardAll(id);
    res.json({...deck, cards});
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
app.delete('/api/deck/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const data = addon.deleteDeck(id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Criar novo Deck
app.post('/api/deck', (req, res) => {
  const { title,subject } = req.body
  try {
    const data = addon.createUpdateDeck(title,subject);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Atualiza o Deck
app.put('/api/deck/:id', (req, res) => {
  const id = Number(req.params.id);
  const { title, subject } = req.body
  try {
    const data = addon.createUpdateDeck(title, subject, id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
// Pega todos os cards por id 
app.get('/api/card/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const cards = addon.getCardById(id);
    res.json(cards);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
app.delete('/api/card/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const data = addon.deleteDeck(id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Criar novo Deck
app.post('/api/card', (req, res) => {
  const {front, back,deckId } = req.body
  try {
    const data = addon.createCard(front, back, Number(deckId));
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Atualiza o Deck
app.put('/api/card/lastreview/:id', (req, res) => {
  const id = Number(req.params.id);
  const { front, back, deckId, mes, dia, hora, min } = req.body
  try {
    const data = addon.createUpdateDeck(id, front, back, deckId, mes, dia, hora, min);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Atualiza o Card
app.put('/api/card/:id', (req, res) => {
  const id = Number(req.params.id);
  const { front, back} = req.body
  try {
    const data = addon.updateCard(id,front,back);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});


// Rota para upload de arquivos
app.post('/api/upload', (req, res) => {
  const { file } = req.files;
  const diretorio = './src/assets/uploads';
  // Se nenhum arquivo foi enviado
  if (!file) return res.sendStatus(400);
  if (!fs.existsSync(diretorio)) {
    fs.mkdirSync(diretorio);
  }
  // Move a imagem para o diretório de uploads
  file.mv(path.join(__dirname, diretorio, file.name), (err) => {
    if (err) {
      console.error('Erro ao mover o arquivo:', err);
      return res.sendStatus(500);
    }

    res.sendStatus(200);
  });
});


// Inicia o servidor
app.listen(port, () => {
  console.log(`API running on http://localhost:${port}`);
});
