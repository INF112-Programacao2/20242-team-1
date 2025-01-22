#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "sqlite3.h"

#include  <vector>
#include <string>

class Deck{
private:
    int id;
    std::string title;
    std::string subject;
    int levelCollection_id;

public:
    void create(std::string title, std::string subject, int levelCollection_id);
    void delet(int id);
    void update(std::string title, std::string subject, int levelCollection_id, int id);
    
    
    std::vector<Card>* get_cards(int id);
    std::vector<Card>* get_cardsReview(int id);


};

#endif
