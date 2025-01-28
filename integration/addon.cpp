#include <napi.h>
#include "../api/DAO/DatabaseConnection.h"
#include "../api/DAO/deckdao.h"
#include "../api/DAO/carddao.h"
#include "../api/DAO/cardAudioDAO.h"
#include "../api/DAO/cardImageDAO.h"
#include "../api/DAO/audioDAO.h"
#include "../api/DAO/imageDAO.h"
#include "../api/deck.h"
#include "../api/date.h"
#include "../api/card.h"
#include "../api/media.h"
#include "../api/audio.h"
#include "../api/image.h"
#include "../api/cardaudio.h"
#include "../api/cardimage.h"
#include <iostream>

DatabaseConnection dbConn; // Crie uma conexão local

DeckDAO deckDAO(dbConn);
CardDAO cardDAO(dbConn);
CardAudioDAO cardAudioDAO(dbConn);
CardImageDAO cardImageDAO(dbConn);
// Converter um objeto Deck para um objeto JavaScript
Napi::Object DeckToJSObject(Napi::Env env, const Deck &deck)
{
    Napi::Object deckObj = Napi::Object::New(env);
    deckObj.Set("id", Napi::Number::New(env, deck.getId()));
    deckObj.Set("title", Napi::String::New(env, deck.getTitle()));
    deckObj.Set("subject", Napi::String::New(env, deck.getSubject()));
    return deckObj;
}

Napi::Object CardToJSObject(Napi::Env env, const Card &card)
{
    Napi::Object cardObj = Napi::Object::New(env);
    cardObj.Set("id", Napi::Number::New(env, card.getId()));
    cardObj.Set("front", Napi::String::New(env, card.getFront()));
    cardObj.Set("back", Napi::String::New(env, card.getBack()));
    cardObj.Set("deckId", Napi::Number::New(env, card.getDeckId()));
    cardObj.Set("lastReview", Napi::String::New(env, card.getLastReview().getDateBystring()));
    return cardObj;
}

Napi::Object CardAudioToJSObject(Napi::Env env, CardAudio &cardAudio)
{
    
    Napi::Object cardObj = Napi::Object::New(env);
    cardObj.Set("id", Napi::Number::New(env, cardAudio.getId()));
    cardObj.Set("front", Napi::String::New(env, cardAudio.getFront()));
    cardObj.Set("audio", Napi::String::New(env,cardAudio.getId()+"sound"));
    cardObj.Set("deckId", Napi::Number::New(env, cardAudio.getDeckId()));
    cardObj.Set("lastReview", Napi::String::New(env, cardAudio.getLastReview().getDateBystring()));
    return cardObj;
}
Napi::Object CardImageToJSObject(Napi::Env env, CardImage &cardImage)
{
    
    Napi::Object cardObj = Napi::Object::New(env);
    cardObj.Set("id", Napi::Number::New(env, cardImage.getId()));
    cardObj.Set("front", Napi::String::New(env, cardImage.getFront()));
    cardObj.Set("image", Napi::String::New(env, cardImage.getImage().getPath()+cardImage.getImage().getName()));
    cardObj.Set("deckId", Napi::Number::New(env, cardImage.getDeckId()));
    cardObj.Set("lastReview", Napi::String::New(env, cardImage.getLastReview().getDateBystring()));
    return cardObj;
}


// Função para obter um Deck por ID
Napi::Value GetDeckById(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int deckId = info[0].As<Napi::Number>();

    try
    {
        Deck deck = deckDAO.getDeckById(deckId);
        std::vector<CardAudio> audios = cardAudioDAO.getCardsAudioByDeckId(deckId);
        std::vector<CardImage> images = cardImageDAO.getCardsImageByDeckId(deckId);
        Napi::Array imagesArray = Napi::Array::New(env);
        Napi::Array audiosArray = Napi::Array::New(env);

        Napi::Object deckAll = DeckToJSObject(env, deck);
        // Preencher o array com objetos Deck convertidos
        for (size_t i = 0; i < audios.size(); ++i)
        {
            Napi::Object cardObject = CardAudioToJSObject(env, audios[i]);
            audiosArray[i] = cardObject; // Adiciona o objeto no array
        }
        for (size_t i = 0; i < images.size(); ++i)
        {
            Napi::Object cardObject = CardImageToJSObject(env, images[i]);
            imagesArray[i] = cardObject; // Adiciona o objeto no array
        }
        deckAll.Set("images", imagesArray);
        deckAll.Set("audios", audiosArray);
        return deckAll;
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value DeleteDeck(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int deckId = info[0].As<Napi::Number>();

    try
    {
        bool deck = deckDAO.deleteDeck(deckId);
        return Napi::Boolean::New(env, deck);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
// Função para obter todos os Decks
Napi::Value GetContReviews(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    try
    {
        // Criar o array JavaScript
        std::array<Deck, 50UL> decks = deckDAO.getAllDecks();

        Napi::Array decksArray = Napi::Array::New(env);

        // Preencher o array com objetos Deck convertidos
        for (size_t i = 0; decks[i].getId() != 0; ++i)
        {
            Napi::Object deckObject = DeckToJSObject(env, decks[i]);
            decksArray[i] = deckObject; // Adiciona o objeto no array
            int quantity = cardDAO.countCards(decks[i].getId()) + cardImageDAO.countCardsImageByDeck(decks[i].getId())+ cardAudioDAO.countCardsAudioByDeck(decks[i].getId()) ;
            deckObject.Set("reviews", Napi::Number::New(env, quantity));
        }
        return decksArray;
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter todos os Decks
Napi::Value GetCardReviews(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();
    try
    {
        Date date;
        // Criar o array JavaScript
        std::vector<Card> cards = cardDAO.getCardsByDate(id);
        std::vector<CardImage> images = cardImageDAO.getCardsByDate(id);
        std::vector<CardAudio> audios = cardAudioDAO.getCardsAudioByDate(date,id);

        Napi::Array cardsArray = Napi::Array::New(env);

        // Preencher o array com objetos Deck convertidos
        for (size_t i = 0; i < cards.size(); ++i)
        {
            Napi::Object cardObject = CardToJSObject(env, cards[i]);
            cardsArray[i] = cardObject; // Adiciona o objeto no array
        }
        for (size_t i = 0; i < images.size(); ++i)
        {
            Napi::Object cardObject = CardImageToJSObject(env, images[i]);
            cardsArray[cardsArray.Length()+ i] = cardObject; // Adiciona o objeto no array
        }
        for (size_t i = 0; i < audios.size(); ++i)
        {
            Napi::Object cardObject = CardAudioToJSObject(env, audios[i]);
            cardsArray[cardsArray.Length()+ i] = cardObject; // Adiciona o objeto no array
        }
        return cardsArray;
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter todos os Decks
Napi::Value GetDeckAll(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    try
    {
        // Criar o array JavaScript
        std::array<Deck, 50UL> decks = deckDAO.getAllDecks();

        Napi::Array decksArray = Napi::Array::New(env);

        // Preencher o array com objetos Deck convertidos
        for (size_t i = 0; decks[i].getId() != 0; ++i)
        {
            Napi::Object deckObject = DeckToJSObject(env, decks[i]);
            decksArray[i] = deckObject; // Adiciona o objeto no array
        }
        return decksArray;
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value CreateUpdateDeck(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsString() || !info[1].IsString())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string title = info[0].As<Napi::String>();
    std::string subject = info[1].As<Napi::String>();
    try
    {
        Deck newDeck(title, subject);

        if (info.Length() > 2)
        {
            int deckId = info[2].As<Napi::Number>();
            newDeck.setId(deckId);
            bool deck = deckDAO.updateDeck(newDeck);
            return Napi::Boolean::New(env, deck);
        }
        else
        {
            bool deck = deckDAO.createDeck(newDeck);
            return Napi::Boolean::New(env, deck);
        }
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter um Deck por ID
Napi::Value GetCardById(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();

    try
    {
        Card card = cardDAO.getCardById(id);
        return CardToJSObject(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter um Deck por ID
Napi::Value GetCardAudioById(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();

    try
    {
        CardAudio card = cardAudioDAO.getCardAudioById(id);
        return CardAudioToJSObject(env,card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value DeleteCard(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();

    try
    {
        bool card = cardDAO.deleteCard(id);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter todos os Decks
Napi::Value GetCardAll(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();
    try
    {
        // Criar o array JavaScript
        std::vector<Card> cards = cardDAO.getCardsByDeckIdSortedByDate(id);

        Napi::Array cardsArray = Napi::Array::New(env);

        // Preencher o array com objetos Deck convertidos
        for (size_t i = 0; i < cards.size(); ++i)
        {
            Napi::Object cardObject = CardToJSObject(env, cards[i]);
            cardsArray[i] = cardObject; // Adiciona o objeto no array
        }
        return cardsArray;
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value CreateCard(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 3 || !info[0].IsString() || !info[1].IsString() || !info[2].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradad para Card").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string front = info[0].As<Napi::String>();
    std::string back = info[1].As<Napi::String>();
    int deckId = info[2].As<Napi::Number>();

    try
    {

        Card newCard(front, back, deckId);

        bool card = cardDAO.createCard(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value CreateAudio(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 4 || !info[0].IsString() || !info[1].IsString() || !info[2].IsString() ||!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradas para Card").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string front = info[0].As<Napi::String>();
    std::string path = info[1].As<Napi::String>();
    std::string name = info[2].As<Napi::String>();
    int deckId = info[3].As<Napi::Number>();

    try
    {
        Audio newAudio;
        newAudio.setName(name);
        newAudio.setPath(path);
        CardAudio newCardAudio;
        newCardAudio.setAudio(newAudio);
        newCardAudio.setDeckId(deckId);
        newCardAudio.setFront(front);
        int card = cardAudioDAO.createCardAudio(newCardAudio);
        return Napi::Number::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value CreateImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 4 || !info[0].IsString() || !info[1].IsString() || !info[2].IsString() ||!info[3].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradas para Card").ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string front = info[0].As<Napi::String>();
    std::string path = info[1].As<Napi::String>();
    std::string name = info[2].As<Napi::String>();
    int deckId = info[3].As<Napi::Number>();

    try
    {
        Image newImage;
        newImage.setName(name);
        newImage.setPath(path);
        CardImage newCArdImage;
        newCArdImage.setImage(newImage);
        newCArdImage.setDeckId(deckId);
        newCArdImage.setFront(front);
        int card = cardImageDAO.createCardImage(newCArdImage);
        return Napi::Number::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value UpdateCardLastReview(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 7 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber() || !info[4].IsNumber() || !info[5].IsNumber() || !info[6].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradas para atualizar lastReview em Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    int day = info[1].As<Napi::Number>();
    int month = info[2].As<Napi::Number>();
    int year = info[3].As<Napi::Number>();
    int hour = info[4].As<Napi::Number>();
    int minute = info[5].As<Napi::Number>();
    int second = info[6].As<Napi::Number>();

    try
    {
        Card newCard = cardDAO.getCardById(id);
        Date nova(day, month, year, hour, minute, second);
        newCard.setLastReview(nova);
        bool card = cardDAO.updateCard(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value UpdateCard(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 3 || !info[0].IsNumber() || !info[1].IsString() || !info[2].IsString())
    {
        Napi::TypeError::New(env, "Esperadas Entradad para Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    std::string front = info[1].As<Napi::String>();
    std::string back = info[2].As<Napi::String>();

    try
    {
        Card newCard = cardDAO.getCardById(id);
        newCard.setFront(front);
        newCard.setBack(back);
        bool card = cardDAO.updateCard(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value UpdateCardAudio(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 3 || !info[0].IsNumber() || !info[1].IsString() || !info[2].IsString())
    {
        Napi::TypeError::New(env, "Esperadas Entradad para Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    std::string front = info[1].As<Napi::String>();
    std::string name = info[2].As<Napi::String>();

    try
    {
        CardAudio newCard = cardAudioDAO.getCardAudioById(id);
        newCard.setFront(front);
        newCard.getAudio().setName(name);
        bool card = cardAudioDAO.updateCardAudio(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value UpdateCardImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 3 || !info[0].IsNumber() || !info[1].IsString() || !info[2].IsString())
    {
        Napi::TypeError::New(env, "Esperadas Entradad para Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    std::string front = info[1].As<Napi::String>();
    std::string name = info[2].As<Napi::String>();

    try
    {
        CardImage newCard = cardImageDAO.getCardImageById(id);
        newCard.setFront(front);
        newCard.getImage().setName(name);
        bool card = cardImageDAO.updateCardImage(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value DeleteCardAudio(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();

    try
    {
        bool card = cardAudioDAO.deleteCardAudio(id);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value DeleteCardImage(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int id = info[0].As<Napi::Number>();

    try
    {
        bool card = cardImageDAO.deleteCardImage(id);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value UpdateCardImageLastReview(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 7 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber() || !info[4].IsNumber() || !info[5].IsNumber() || !info[6].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradas para atualizar lastReview em Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    int day = info[1].As<Napi::Number>();
    int month = info[2].As<Napi::Number>();
    int year = info[3].As<Napi::Number>();
    int hour = info[4].As<Napi::Number>();
    int minute = info[5].As<Napi::Number>();
    int second = info[6].As<Napi::Number>();

    try
    {
        CardImage newCard= cardImageDAO.getCardImageById(id);
        Date nova(day, month, year, hour, minute, second);
        newCard.setLastReview(nova);
        bool card = cardImageDAO.updateCardImage(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
Napi::Value UpdateCardAudioLastReview(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 7 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber() || !info[4].IsNumber() || !info[5].IsNumber() || !info[6].IsNumber())
    {
        Napi::TypeError::New(env, "Esperadas Entradas para atualizar lastReview em Card").ThrowAsJavaScriptException();
        return env.Null();
    }
    // void updateDate(int day, int month, int year, int hour, int minute, int second);
    int id = info[0].As<Napi::Number>();
    int day = info[1].As<Napi::Number>();
    int month = info[2].As<Napi::Number>();
    int year = info[3].As<Napi::Number>();
    int hour = info[4].As<Napi::Number>();
    int minute = info[5].As<Napi::Number>();
    int second = info[6].As<Napi::Number>();

    try
    {
        CardAudio newCard = cardAudioDAO.getCardAudioById(id);
        Date nova(day, month, year, hour, minute, second);
        newCard.setLastReview(nova);
        bool card = cardAudioDAO.updateCardAudio(newCard);
        return Napi::Boolean::New(env, card);
    }
    catch (const std::exception &e)
    {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}
// Inicializar o módulo
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getDeckAll", Napi::Function::New(env, GetDeckAll));
    exports.Set("getContReviews", Napi::Function::New(env, GetContReviews));
    exports.Set("getCardReviews", Napi::Function::New(env, GetCardReviews));
    exports.Set("getDeckById", Napi::Function::New(env, GetDeckById));
    exports.Set("deleteDeck", Napi::Function::New(env, DeleteDeck));
    exports.Set("createUpdateDeck", Napi::Function::New(env, CreateUpdateDeck));
    exports.Set("getCardAll", Napi::Function::New(env, GetCardAll));
    exports.Set("getCardById", Napi::Function::New(env, GetCardById));
    exports.Set("getCardAudioById", Napi::Function::New(env, GetCardAudioById));
    exports.Set("deleteCard", Napi::Function::New(env, DeleteCard));
    exports.Set("createAudio", Napi::Function::New(env, CreateAudio));
    exports.Set("createCard", Napi::Function::New(env, CreateCard));
    exports.Set("updateCardLastReview", Napi::Function::New(env, UpdateCardLastReview));
    exports.Set("updateCard", Napi::Function::New(env, UpdateCard));
    exports.Set("updateCardAudio", Napi::Function::New(env, UpdateCardAudio));
    exports.Set("deleteCardImage", Napi::Function::New(env, DeleteCardImage));
    exports.Set("deleteCardAudio", Napi::Function::New(env, DeleteCardAudio));
    exports.Set("updateCardAudioLastReview", Napi::Function::New(env, UpdateCardAudioLastReview));
    exports.Set("updateCardImageLastReview", Napi::Function::New(env, UpdateCardImageLastReview));
    exports.Set("createImage", Napi::Function::New(env, CreateImage));
    exports.Set("updateCardImage", Napi::Function::New(env, UpdateCardImage));

    return exports;
}

NODE_API_MODULE(addon, Init)
