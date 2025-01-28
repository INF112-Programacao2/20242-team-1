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
app.use('/assets/uploads', express.static(path.join(__dirname, 'assets/uploads')));

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
// Pega todos os baralhos e a quantidade de revisões
app.get('/api/decks/reviews', (req, res) => {
  try {
    const decks = addon.getContReviews();
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
    res.json({ ...deck, cards });
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});

// Pega um baralho e as revisões por id 
app.get('/api/card/reviews/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const cards = addon.getCardReviews(id);
    res.json(cards);
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
  const { title, subject } = req.body
  try {
    const data = addon.createUpdateDeck(title, subject);
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

// Pega todos os cards por id 
app.get('/api/audio/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const cards = addon.getCardAudioById(id);
    res.json(cards);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
app.delete('/api/card/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const data = addon.deleteCard(id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
app.delete('/api/audio/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const data = addon.deleteCardAudio(id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
app.delete('/api/image/:id', (req, res) => {
  const id = Number(req.params.id);
  try {
    const data = addon.deleteCardImage(id);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});
//Criar novo Deck
app.post('/api/card', (req, res) => {
  const { front, back, deckId } = req.body
  try {
    const data = addon.createCard(front, back, Number(deckId));
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});


app.put('/api/card/lastreview/:id', (req, res) => {
  const id = Number(req.params.id);
  const { type, day, month, year, hour, minute, second } = req.body
  try {
    let data;
    if (type === '0') {
      data = addon.updateCardLastReview(id, Number(day), Number(month), Number(year), Number(hour), Number(minute), Number(second));
    } else if (type === '1') {
      data = addon.updateCardAudioLastReview(id, Number(day), Number(month), Number(year), Number(hour), Number(minute), Number(second));
    } else {
      data = addon.updateCardImageLastReview(id, Number(day), Number(month), Number(year), Number(hour), Number(minute), Number(second));

    }
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});
//Atualiza o Card
app.put('/api/card/:id', (req, res) => {
  const id = Number(req.params.id);
  const { front, back } = req.body
  try {
    const data = addon.createCard(id, front, back);
    res.json(data);
  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }

});

app.post('/api/image', (req, res) => {
  const { image } = req.files;
  const diretorio = './dist/dist/assets/uploads/';
  const { front, deckId } = req.body
  const id = addon.createImage(front, "", "image", Number(deckId));

  try {
    if (!image) return res.sendStatus(400);
    if (!fs.existsSync(diretorio)) {
      fs.mkdirSync(diretorio);
    }
    // Move a imagem para o diretório de uploads
    image.mv(path.join(__dirname, diretorio, `${id}image.png`), (err) => {
      if (err) {
        console.error('Erro ao mover o arquivo:', err);
        return res.sendStatus(500);
      }
      return res.sendStatus(200);
    });

  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});

app.put('/api/image/:id', (req, res) => {
  const id = Number(req.params.id);
  const diretorio = './dist/dist/assets/uploads/';
  const { front, deckId } = req.body

  try {
    const result = addon.updateCardImage(id, front, id + "image")
    const { audio } = req.files;
    if (audio) {
      if (!fs.existsSync(diretorio)) {
        fs.mkdirSync(diretorio);
      }
      fs.unlink(path.join(__dirname, diretorio, `${id}image.png`), (err) => {
        if (err) {
          console.error(`Error removing file: ${err}`);
          return;
        }
        // Move a imagem para o diretório de uploads
        audio.mv(path.join(__dirname, diretorio, `${id}image.png`), (err) => {
          if (err) {
            console.error('Erro ao mover o arquivo:', err);
            return res.sendStatus(500);
          }
          return res.sendStatus(200);
        });
        console.log(`File ${filePath} has been successfully removed.`);
      });
    }
    return res.sendStatus(200);

  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});

app.post('/api/audio', (req, res) => {
  const { audio } = req.files;
  const diretorio = './dist/dist/assets/uploads/';
  const { front, deckId } = req.body
  const id = addon.createAudio(front, "", "sound", Number(deckId));

  try {
    
    if (!audio) return res.sendStatus(400);
    if (!fs.existsSync(diretorio)) {
      fs.mkdirSync(diretorio);
    }
    // Move a imagem para o diretório de uploads
    audio.mv(path.join(__dirname, diretorio, `${id}sound.webm`), (err) => {
      if (err) {
        console.error('Erro ao mover o arquivo:', err);
        return res.sendStatus(500);
      }
      const result = addon.updateCardAudio(id, front, id + "sound")
      return res.sendStatus(200);
    });

  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});

app.put('/api/audio/:id', (req, res) => {
  const id = Number(req.params.id);
  const diretorio = './dist/dist/assets/uploads/';
  const { front, deckId } = req.body

  try {
    const result = addon.updateCardAudio(id, front, id + "sound")
    const { audio } = req.files;
    if (audio) {
      if (!fs.existsSync(diretorio)) {
        fs.mkdirSync(diretorio);
      }
      fs.unlink(path.join(__dirname, diretorio, `${id}sound.webm`), (err) => {
        if (err) {
          console.error(`Error removing file: ${err}`);
          return;
        }
        // Move a imagem para o diretório de uploads
        audio.mv(path.join(__dirname, diretorio, `${id}sound.webm`), (err) => {
          if (err) {
            console.error('Erro ao mover o arquivo:', err);
            return res.sendStatus(500);
          }
          return res.sendStatus(200);
        });
        console.log(`File ${filePath} has been successfully removed.`);
      });
    }
    return res.sendStatus(200);

  } catch (error) {
    console.error('Erro ao criar conexão:', error.message);
  }
});

// Rota para upload de arquivos
app.post('/api/upload', (req, res) => {
  const { file } = req.files;
  const diretorio = './dist/dist/assets/uploads/';
  // Se nenhum arquivo foi enviado
  /*if (!file) return res.sendStatus(400);
  if (!fs.existsSync(diretorio)) {
    fs.mkdirSync(diretorio);
  }*/
  console.log(__dirname)
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
