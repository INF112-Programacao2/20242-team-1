// myclass.cpp
#include <napi.h>
#include "../api/myclass.cpp"
// Funções para integrar com Node.js
Napi::String GreetWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    // Obtém o nome do argumento
    std::string name = info[0].As<Napi::String>();

    // Cria uma instância de MyClass e retorna a saudação
    MyClass myClass(name);
    return Napi::String::New(env, myClass.greet());
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "greet"), Napi::Function::New(env, GreetWrapped));
    return exports;
}

NODE_API_MODULE(myclass, Init);
