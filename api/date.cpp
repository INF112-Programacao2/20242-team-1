#include "date.h"
#include <iostream>

/*
* @brief Método responsável por inicializar um objeto do tipo Date com a data atual
* @param void
* @return void
*/
Date::Date(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    this->day = ltm->tm_mday;
    this->month = 1 + ltm->tm_mon;
    this->year = 1900 + ltm->tm_year;
    this->hour = ltm->tm_hour;
    this->minute = ltm->tm_min;
    this->second = ltm->tm_sec;
}

/*
* @brief Método responsável por inicializar um objeto do tipo Date com a data atual
* @param int O número inteiro referente ao dia
* @param int O número inteiro referente ao mês
* @param int O número inteiro referente ao ano
* @param int O número inteiro referente à hora
* @param int O número inteiro referente ao minuto
* @param int O número inteiro referente ao segundo
* @return void
*/
Date::Date(int day, int month, int year, int hour, int minute, int second){
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

/*
* @brief Método responsável por inicializar um objeto do tipo Date utilizando outro objeto do tipo Date (cópia)
* @param Date O objeto do tipo Date que será copiado
* @return void
*/
Date::Date(const Date &date){
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
    this->hour = date.hour;
    this->minute = date.minute;
    this->second = date.second;
}

/*
* @brief Método responsável por retornar o dia armazenado no objeto
* @param void
* @return O número inteiro referente ao dia
*/
int Date::getDay() const{
    return this->day;
}

/*
* @brief Método responsável por retornar o mês armazenado no objeto
* @param void
* @return O número inteiro referente ao mês
*/
int Date::getMonth() const{
    return this->month;
}

/*
* @brief Método responsável por retornar o ano armazenado no objeto
* @param void
* @return O número inteiro referente ao ano
*/
int Date::getYear() const{
    return this->year;
}

/*
* @brief Método responsável por retornar a hora armazenada no objeto
* @param void
* @return O número inteiro referente à hora
*/
int Date::getHour() const{
    return this->hour;
}

/*
* @brief Método responsável por retornar o minuto armazenado no objeto
* @param void
* @return O número inteiro referente ao minuto
*/
int Date::getMinute() const{
    return this->minute;
}
/*
* @brief Método responsável por retornar o segundo armazenado no objeto
* @param void
* @return O número inteiro referente ao segundo
*/
int Date::getSecond() const{
    return this->second;
}

std::string Date::getDateBystring() const {
        std::ostringstream ss;
        ss << std::setfill('0') << std::setw(4) << year << "-" 
           << std::setw(2) << month << "-" 
           << std::setw(2) << day << " " 
           << std::setw(2) << hour << ":" 
           << std::setw(2) << minute << ":" 
           << std::setw(2) << second;

        return ss.str();
}

/*
* @brief Método responsável por alterar o dia armazenado no objeto
* @param int O número inteiro referente ao dia
* @return void
*/
void Date::setDay(int day){
    this->day = day;
}

/*
* @brief Método responsável por alterar o mês armazenado no objeto
* @param int O número inteiro referente ao mês
* @return void
*/
void Date::setMonth(int month){
    this->month = month;
}

/*
* @brief Método responsável por alterar o ano armazenado no objeto
* @param int O número inteiro referente ao ano
* @return void
*/
void Date::setYear(int year){
    this->year = year;
}

/*
* @brief Método responsável por alterar a hora armazenada no objeto
* @param int O número inteiro referente à hora
* @return void
*/
void Date::setHour(int hour){
    this->hour = hour;
}

/*
* @brief Método responsável por alterar o minuto armazenado no objeto
* @param int O número inteiro referente ao minuto
* @return void
*/
void Date::setMinute(int minute){
    this->minute = minute;
}

/*
* @brief Método responsável por alterar o segundo armazenado no objeto
* @param int O número inteiro referente ao segundo
* @return void
*/
void Date::setSecond(int second){
    this->second = second;
}

void Date::setDateBystring(const std::string& dateStr) {
        std::istringstream ss(dateStr);
        char dash1, dash2, space, colon1, colon2;

        // Espera o formato: "YYYY-MM-DD HH:MM:SS"
        if (!((ss >> year >> dash1 >> month >> dash2 >> day >> space >> hour >> colon1 >> minute >> colon2 >> second) ||
            dash1 != '-' || dash2 != '-' || space != ' ' || colon1 != ':' || colon2 != ':')) {
                std::string a = dateStr;
                a += "oi";
            throw std::runtime_error("Formato de data e hora inválido: " + dateStr);
        }
}

/*
* @brief Método responsável por atualizar a data armazenada no objeto
* @param int O número inteiro referente ao dia
* @param int O número inteiro referente ao mês
* @param int O número inteiro referente ao ano
* @param int O número inteiro referente à hora
* @param int O número inteiro referente ao minuto
* @param int O número inteiro referente ao segundo
* @return void
*/
void Date::updateDate(int day, int month, int year, int hour, int minute, int second){
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

/*
* @brief Método responsável por atualizar a data armazenada no objeto
* @param Date O objeto do tipo Date que será copiado
* @return void
*/
void Date::updateDate(const Date &date){
    this->day = date.day;
    this->month = date.month;
    this->year = date.year;
    this->hour = date.hour;
    this->minute = date.minute;
    this->second = date.second;
}

/*
* @brief Método responsável por atualizar a data armazenada no objeto com a data atual
* @param void
* @return void
*/
void Date::updateDate(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    this->day = ltm->tm_mday;
    this->month = 1 + ltm->tm_mon;
    this->year = 1900 + ltm->tm_year;
    this->hour = ltm->tm_hour;
    this->minute = ltm->tm_min;
    this->second = ltm->tm_sec;
}

/*
* @brief Método responsável por imprimir a data armazenada no objeto
* @param void
* @return void
*/
void Date::printDate() const{
    std::cout << this->day << "/" << this->month << "/" << this->year << " " << this->hour << ":" << this->minute << ":" << this->second << std::endl;
}