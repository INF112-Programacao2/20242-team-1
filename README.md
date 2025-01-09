# **Nome em Aberto**  🔎 📖
Uma aplicação simples e intuitiva para estudo e memorização baseada no conceito de repetição espaçada, inspirada no Anki.Você pode criar, editar, organizar e revisar seus cartões de forma eficiente, acompanhando seu progresso em uma interface  funcional.

---

## **Principais Funcionalidades**

### 📋 **Gerenciamento de Cartões**
- **Criar cartões:** Adicione novos cartões facilmente, com suporte para frente e verso.  
- **Editar cartões:** Atualize o conteúdo de qualquer cartão existente.  
- **Excluir cartões:** Remova cartões desnecessários com apenas um clique.  

### 📊 **Estatísticas ( Ainda não decidida Implementação)**
  - Acompanhe seu desempenho com métricas como:
  - Total de cartões revisados.
  - Taxa de acertos.
  - Gráficos que mostram o progresso diário, semanal e mensal.
    
  - **Sugestões de  Frameworks para essa Aba**
  - Qt Charts: Biblioteca para criar gráficos interativos em C++.
  - Matplotlib (C++ bindings): Para criar gráficos de alta qualidade.
  - Plotly (C++ bindings): Para gráficos interativos e visualizações avançadas.

### 🖼️ **Interface Simples e Intuitiva**
- **Design minimalista**
- **Modo de estudo:** Interface limpa .
- **Aba de estatísticas:** Visualização dos dados sobre seu desempenho (Semanal).
 - **Sugestões de  Frameworks para essa Aba (Total em Aberto)** 
- Qt: Framework para criar interfaces gráficas em C++.
- wxWidgets: Outra opção para interfaces gráficas multiplataforma.

---



### 🧩 **Diagrama Inicial de Classes**
O sistema foi projetado para ser modular e escalável. Aqui está uma visão geral das classes principais:

```plaintext
+-----------------+       +-------------------+       +--------------------+       +----------------------+
|    Subject      |       |       Pad         |       |       Card         |       |     LevelTime         |
+-----------------+       +-------------------+       +--------------------+       +----------------------+
| - id: int       |       | - id: int         |       | - id: int          |       | - id: int            |
| - title: string |       | - title: string   |       | - front: string    |       | - time: Date         |
| - pads_id: Pad[]|       | - cards_id: Card[]|       | - back: string     |       | - obs: string        |
|                 |       | - subject_id: int |       | - pad_id: int      |       | - title: string      |
| + get_title()   |       |                   |       | - level_time_id: int|      |                      |
| + get_pads()    |       | + get_title()     |       | - last_review: Date|       | + get_time()         |
| + set_title()   |       | + get_cards()     |       | + nextReview()     |       | + get_details()      |
| + set_pads()    |       | + set_cards()     |       |                    |       |                      |
| - delete(id)    |       | - delete(id)      |       |                    |       |                      |
+-----------------+       +-------------------+       +--------------------+       +----------------------+
        |                      ^           |                   ^       |                               ^
        |                      |           |                   |       |                               |
        ' ----- Contém --------'           ' ----- Possui ---- '       ' ----- Está Classifcado em: ---'

# **Instalação** 
 1. Instalar Nodejs;
 2. Instalar o gerenciador de pacotes yarn;
 3. Entre no projeto e rode : `yarn` para instalar as dependências;
 
# **Executar** 
 1. Faça o build com `yarn build`
 2. Execute com `yarn start`
                  
                               
                                                    
                                                              
