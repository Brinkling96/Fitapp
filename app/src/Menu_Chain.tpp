template <typename T>
Menu_Chain<T>::Menu_Chain(){
    this->next_Chain = new Null_Chain_Link<T>();
}

template <typename T>
Menu_Chain<T>::Menu_Chain(Menu_Chain<T>* next_Chain): next_Chain{next_Chain} {};

template <typename T>
Menu_Chain<T>::~Menu_Chain(){
    delete next_Chain;
}

template <typename T>
Null_Chain_Link<T>::Null_Chain_Link() : Menu_Chain<T>(nullptr) {};

template <typename T>
Null_Chain_Link<T>::~Null_Chain_Link(){};

template <typename T>
void Null_Chain_Link<T>::setNext(Menu_Chain<T>* next_Chain){
    throw Menu_Chain_Exception("Null Chain link does not allow next chain sets.");
}

template <typename T>
T Null_Chain_Link<T>::select(std::string select){
    throw Menu_Chain_Exception("Null Chain, cannot execute select");
}

template <typename T>
std::string Null_Chain_Link<T>::toString_Chain(){
    return std::string("");
}

template <typename T>
String_Option_Chain_Link<T>::String_Option_Chain_Link(std::string prompt,std::string option, T result)
: prompt{prompt}, option{option}, result{result} {};

template <typename T>
String_Option_Chain_Link<T>::String_Option_Chain_Link(
    Menu_Chain<T>* next_Chain, std::string prompt, std::string option, T result
) 
: Menu_Chain<T>(next_Chain), prompt{prompt}, option{option}, result{result} {};

template <typename T>
String_Option_Chain_Link<T>::~String_Option_Chain_Link(){
    delete this->next_Chain;
}

template <typename T>
void String_Option_Chain_Link<T>::setNext(Menu_Chain<T>* next_Chain){
    this->next_Chain= next_Chain;
}

template <typename T>
void String_Option_Chain_Link<T>::setResult(T result){
    this->result = result;
}

template <typename T>
T String_Option_Chain_Link<T>::select(std::string select){
    if(option.compare(select) == 0){
        return result;
    }
    else {
        return this->next_Chain->select(select);
    }
}

template <typename T>
std::string String_Option_Chain_Link<T>::toString_Chain(){
    return prompt + this->next_Chain->toString_Chain();
}

