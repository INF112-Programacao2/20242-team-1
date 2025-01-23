#include <napi.h>
#include "../api/DAO/DatabaseConnection.h"
#include "../api/DAO/deckdao.h"
#include "../api/deck.h"
#include <iostream>

// Converter um objeto Deck para um objeto JavaScript
Napi::Object DeckToJSObject(Napi::Env env, const Deck& deck) {
    Napi::Object deckObj = Napi::Object::New(env);
    deckObj.Set("id", Napi::Number::New(env, deck.getId()));
    deckObj.Set("title", Napi::String::New(env, deck.getTitle()));
    deckObj.Set("subject", Napi::String::New(env, deck.getSubject()));
    return deckObj;
}

// Função para criar uma conexão
Napi::Value CreateConnection(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    try {
        DatabaseConnection connection;
        // Retorne um objeto JavaScript indicando que a conexão foi criada
        Napi::Object obj = Napi::Object::New(env);
        //obj.Set("status", "connected");
        return obj;
    } catch (const std::exception& e) {
        Napi::TypeError::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Função para obter um Deck por ID
Napi::Value GetDeckById(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsNumber()) {
        Napi::TypeError::New(env, "Esperado um ID numérico para o deck").ThrowAsJavaScriptException();
        return env.Null();
    }

    int deckId = info[0].As<Napi::Number>();

    try {
        DatabaseConnection dbConn; // Crie uma conexão local
        DeckDAO deckDAO(dbConn);
        Deck deck = deckDAO.getDeckById(deckId);
        return DeckToJSObject(env, deck);
    } catch (const std::exception& e) {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

// Inicializar o módulo
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("createConnection", Napi::Function::New(env, CreateConnection));
    exports.Set("getDeckById", Napi::Function::New(env, GetDeckById));
    return exports;
}

NODE_API_MODULE(addon, Init)
