const express = require('express');
const fs = require('fs');
const path = require('path');
const myclass = require('./build/Release/myclass.node'); // Módulo C++ compilado
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

// Rota para API de saudação
app.get('/api/greet/:name', (req, res) => {
  const name = req.params.name;
  const greeting = myclass.greet(name); // Chama a função C++
  res.json({ message: greeting });
});

// Rota para upload de arquivos
app.post('/api/upload', (req, res) => {
  const { image } = req.files;
  const diretorio = './src/assets/uploads';
  // Se nenhum arquivo foi enviado
  if (!image) return res.sendStatus(400);
  if (!fs.existsSync(diretorio)) {
    fs.mkdirSync(diretorio);
  }
  // Move a imagem para o diretório de uploads
  image.mv(path.join(__dirname, diretorio, image.name), (err) => {
    if (err) {
      console.error('Erro ao mover o arquivo:', err);
      return res.sendStatus(500);
    }

    res.sendStatus(200);
  });
});

// Rota para obter informações de um card
app.get('/api/card/:id', (req, res) => {
  const id = req.params.id;
  console.log(`get card ${id}`);
  // Chamar função C++ ou lógica
  res.json({ id: id, front: `front card ${id}`, back: `back card ${id}` });
});

// Inicia o servidor
app.listen(port, () => {
  console.log(`API running on http://localhost:${port}`);
});
