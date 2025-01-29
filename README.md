# **Nome em Aberto**  🔎 📖
Uma aplicação simples e intuitiva para estudo e memorização baseada no conceito de repetição espaçada, inspirada no Anki.Você pode criar, editar, organizar e revisar seus cartões de forma eficiente, acompanhando seu progresso em uma interface  funcional.

---

## **Principais Funcionalidades**

### 📋 **Gerenciamento de Cartões**

-  **Criar cartões:** Adicione novos cartões facilmente, com suporte para frente e verso.

-  **Editar cartões:** Atualize o conteúdo de qualquer cartão existente.

-  **Excluir cartões:** Remova cartões desnecessários com apenas um clique.

  

### 📊 **Estatísticas ( Ainda não decidida Implementação)**

- Acompanhe seu desempenho com métricas como:

- Total de cartões revisados.

- Taxa de acertos.

- Gráficos que mostram o progresso diário, semanal e mensal.

-  **Sugestões de Frameworks para essa Aba**

- Qt Charts: Biblioteca para criar gráficos interativos em C++.

- Matplotlib (C++ bindings): Para criar gráficos de alta qualidade.

- Plotly (C++ bindings): Para gráficos interativos e visualizações avançadas.

  

### 🖼️ **Interface Simples e Intuitiva**

-  **Design minimalista**

-  **Modo de estudo:** Interface limpa .

-  **Aba de estatísticas:** Visualização dos dados sobre seu desempenho (Semanal).

-  **Sugestões de Frameworks para essa Aba (Total em Aberto)**

- Qt: Framework para criar interfaces gráficas em C++.

- wxWidgets: Outra opção para interfaces gráficas multiplataforma.

  

### **Requesitos**

1. Nodejs >=20.0.0;

2. Yarn >=1.22.10;

  

### **Instalação**

1. Instalar Nodejs e NPM;
´sudo apt update ´ -> Atualizar indice de pacotes 
´curl -fsSL https://deb.nodesource.com/setup_current.x | sudo -E bash -´
´sudo apt install -y nodejs´

2. Instalar o gerenciador de pacotes yarn;
´npm install -g yarn´

4. Instalar SQLITE;
     ´sudo apt update´
    ´sudo apt install sqlite3´


5. Entre no projeto e rode : `yarn` para instalar as dependências;

### **Executar**

1. Faça o build com `yarn build`

2. Execute com `yarn start`

3. Para executar sem interromper utilize `yarn dev`

4. Acesse '`http://localhost:3000`

### **Estrutura de Pastas**
|Pasta|Função  |
|--|--|
| api| Contém todo o c++ da aplicação (arquivos .h e .cpp)  |
| dist| Abriga os pontos de inicialização do html  |
| integration| Integrações de c++ para javascript |
| api| Contém todo o c++ da aplicação (arquivos .h e .cpp)  |
|  src| Arquivos do react (Frontend)  |
| node_modules| Bibliotecas do nodejs que são instaladas localmente |
| build| Build para execução do gerado localmente localmente |
---

### 🧩 **Diagrama de Classes**

![Diagrama de Classes](https://lucid.app/publicSegments/view/954ba3af-6cea-465c-b535-966b3841d53d/image.png)                                 
