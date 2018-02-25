#ifndef TCOORDINATES_H
#define TCOORDINATES_H

#include <algorithm>

/*!
    Класс для хранения адресов элементов в матрице.
    num_dimensions - размерность матрицы
*/
template<size_t num_dimensions>
class TCoordinates
{
    public:

        TCoordinates():_indexes() {}
        ~TCoordinates() {}
        /*!
            Оператор сравнения для хранения в map
        */
        bool operator < (const TCoordinates<num_dimensions>& other) const{
            return _indexes<other._indexes;
        }
        /*!
            Задание индекса номеру измерения.
            idx     -   номер измерения
            value   -   значение индекса
        */
        void set(size_t idx, size_t value){
            if(num_dimensions>idx)
                _indexes[idx] = value;
            else throw std::logic_error("Index overflow in Coordinates!");
        }

        /*!
            Обеспечение доступа к накопленным индексам.
            Результат напрямую передаётся в контейнер для запроса значения.
        */
        auto get(){return _indexes;}

        /*!
            Форматированный вывод координат в поток
        */
        friend std::ostream& operator<< (std::ostream& os, TCoordinates<num_dimensions> const& idx){
            for(auto val: idx._indexes){
                std::cout << "["<<val <<"]";
            }
            return os;
        };
    protected:

    private:
        //  Хранимые значения измерений для доступа к элементу
        std::array<size_t, num_dimensions>  _indexes;
};

#endif // TCOORDINATES_H
