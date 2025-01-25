#include <napi.h>
#include "../api/DAO/DatabaseConnection.h"
#include "../api/DAO/deckdao.h"
#include "../api/deck.h"
#include <iostream>

DatabaseConnection dbConn; // Crie uma conexão local
DeckDAO deckDAO(dbConn);

// Converter um objeto Deck para um objeto JavaScript
Napi::Object DeckToJSObject(Napi::Env env, const Deck &deck)
{
    Napi::Object deckObj = Napi::Object::New(env);
    deckObj.Set("id", Napi::Number::New(env, deck.getId()));
    deckObj.Set("title", Napi::String::New(env, deck.getTitle()));
    deckObj.Set("subject", Napi::String::New(env, deck.getSubject()));
    return deckObj;
}

napi_value CreateArray(napi_env env, napi_callback_info info)
{
    napi_value jsArray;
    napi_create_array(env, &jsArray); // Cria um array vazio
    return jsArray;
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
        return DeckToJSObject(env, deck);
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
        for (size_t i = 0; decks[i].getId()!=0; ++i)
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

// Inicializar o módulo
Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("getDeckAll", Napi::Function::New(env, GetDeckAll));
    exports.Set("getDeckById", Napi::Function::New(env, GetDeckById));
    return exports;
}

NODE_API_MODULE(addon, Init)
