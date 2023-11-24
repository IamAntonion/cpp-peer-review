#include <iostream>
#include <deque>
 
static const int USER_ID_MAXIMUM = 1e+5 + 1;    // номера пользователей не превосходят 10⁵
static const int PAGE_NUMBER_MAXIMUM = 1000; // номера страниц не превосходят 1000
 
class Book {
public:
    
    Book() : users_id_(PAGE_NUMBER_MAXIMUM, 0),
             pages_for_user_id_(USER_ID_MAXIMUM, 0) {}
    
    void Read(int user_id, int pages);  // READ user page  
    double Cheer(int user_id);             // CHEER user
    
private:
    std::deque<int> users_id_;             // список id пользователей
    std::deque<int> pages_for_user_id_;    // список на каких страницах остановились пользователи
    
    int number_of_authorized_people = 0;
};
 
void Book::Read(int user_id, 
                int pages) {
 
    int pages_before = 0;
 
    if (pages_for_user_id_[user_id]) {
        pages_before = pages_for_user_id_[user_id];
        
    } else {
        ++number_of_authorized_people;
    }
 
    pages_for_user_id_[user_id] = pages;
 
    for (int i = pages_before; i < pages; ++i) {
        users_id_[i] += 1;
        
    }
}
 
double Book::Cheer(int user_id) {
    if (pages_for_user_id_[user_id] <= 0) {
        return 0.0;
    }
    if (number_of_authorized_people - 1 <= 0) {
        return 1.0;
    }
    int pages = pages_for_user_id_[user_id];
    if (number_of_authorized_people == users_id_[pages - 1]) {
        return 0.0;   
    }
    return (number_of_authorized_people - users_id_[pages - 1]) / (number_of_authorized_people * 1.0 - 1.0);
}
 
void Parse(std::istream& input, 
           std::ostream& output, 
           Book& book) {
    
    std::string str;
    getline(input, str);
    
    int requests_amount = std::stoi(str);
 
    for (int i = 0; i < requests_amount; ++i) {
        
        std::string request_type;
        getline(input, request_type, ' ');
        
        if (request_type == "READ") {
            std::string user_id;
            getline(input, user_id, ' ');
            
            std::string pages;
            getline(input, pages);
            
            book.Read(std::stoi(user_id), 
                      std::stoi(pages));
        } else if (request_type == "CHEER") {
            std::string user_id;
            getline(input, user_id);
            
            output << book.Cheer(std::stoi(user_id)) << std::endl;
        }
    }
}

int main() {
    Book book;
    Parse(std::cin, 
          std::cout, 
          book);
}