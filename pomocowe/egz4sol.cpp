namespace OOP{ // tworzymy namespace bo potem wyciągamy z niego ten szablon
    template<typename T>
    struct Array{
        using value_type = T;
        Array(int size){}
        
        Array& insert(char x){
            _vec.push_back(static_cast<int>(x));
            return *this;
        }

        Array& operator%(char x){
            return insert(x);
        }

        T& operator[](int index){
            return _vec.at(index);
        }
        int operator ~(){
            return _vec.size();
        }

        private:
            std::vector<T> _vec;
    };
}