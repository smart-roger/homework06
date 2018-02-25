#ifndef TMATRIX_H
#define TMATRIX_H

#include <algorithm>
#include <map>
#include <iostream>
#include "TCoordinates.h"
#include "TProxy.h"

/*!
    Шаблонный класс для реализации матрицы
    T               -   тип хранимых значений
    _default_value_ -   значение типа Т, возвращаемое по умолчанию
    num_dimensions  -   количество измерений в матрице (по умолчанию 2)
*/
template<typename T, T _default_value_, size_t num_dimensions=2>
class TMatrix
{
    public:
        //  Количество измерений в матрице
        static const size_t dimensions = num_dimensions;
        //  Тип хранимых значений
        using value_type = T;
        //  Тип используемый для предоставления прокси-объекта к элементам
        using typeProxy = TProxy<TMatrix<T,_default_value_, num_dimensions>>;

        //  Тип контейнера для хранения занятых ячеек
        using containerCells = typename std::map<TCoordinates<num_dimensions>, T>;
        //  Итератор по занятым ячейкам
        using containerConstIterator = typename containerCells::const_iterator;

        TMatrix():_matrix_(){};
        ~TMatrix(){};

        //  Для упрощения запретил копирование и присваивание
        TMatrix(const TMatrix&) = delete;
        TMatrix& operator= (const TMatrix&) const= delete;

        //  Обработка запроса к матрице по индексу.
        //  Так обрабатывается только первый запрос. Остальные перенаправляются прокси-объекту.
        typeProxy  operator [](const size_t index){
            return typeProxy(*this, index);
        }

        //  Получение значения элемента по индексу
        T get (TCoordinates<num_dimensions> address) const{
            if(0==_matrix_.count(address))
                return _default_value_;
            else
                return _matrix_.at(address);
        }
        //  Задание значения элементу по индексу
        void set(TCoordinates<num_dimensions> address, T value){
            //address add(getAddress(idxs));
            if (_default_value_ == value)
                //  Если задаётся значение по умолчанию - элемент удаляется.
               _matrix_.erase(address);
            else   _matrix_[address] = value;
        }

        //  Определение числа занятых ячеек
        size_t size () const{return _matrix_.size();};

        /*!  Итератор для перемещения по занятым ячейкам
            Фактически просто обёртка вокруг итератора контейнера с ячейками.
        */
        class const_iterator{

            private:
                //  Итератор внутреннего контейнера
                containerConstIterator   _iter;

            public:
                //  Конструктор по умолчанию быть не должно - необходимо передавать ссылку на итератор
                const_iterator()=delete;

                //  Конструкторы для итератора
                const_iterator(containerConstIterator&& cellIterator):_iter(cellIterator){};
                const_iterator(const_iterator& other):_iter(other._iter){};
                const_iterator(const_iterator&& other):_iter(other._iter){};

                //  Оператор для перемещения по занятым ячейкам
                const_iterator& operator++(){
                    ++_iter;
                    return *this;
                };
                /*bool operator==(const const_iterator& other) const{
                    return _iter==other._iter;
                }*/

                bool operator!=(const const_iterator& other) const{
                    std::cout << std::boolalpha << "!=" << (_iter!=other._iter) << std::endl;
                    return _iter!=other._iter;
                }
                //reference operator*(){return *_iter;};

                //  Форматированный вывод данных в поток
                friend std::ostream& operator<< (std::ostream& os, const_iterator const& citer){
                    os << citer._iter->first;
                    os << citer._iter->second;
                    return os;
                };
        };
        //  Получение итератора на начало
        const_iterator cbegin() const {return _matrix_.cbegin();}
        //  Получение итератора на конец
        const_iterator cend() const{return _matrix_.cend();}

    private:
        //  Словарь для хранения значений. Первый параметр - индекс, второй - конкретное значение.
        containerCells _matrix_;
};


#endif // TMATRIX_H
