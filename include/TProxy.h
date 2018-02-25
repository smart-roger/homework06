#ifndef TPROXY_H
#define TPROXY_H

#include <vector>
#include "TCoordinates.h"

/*!
    Прокси объект для обращения к матрице.
    Он перехватывает все обращения к элементу матрицы (индексирование, присваивание, получение значения).

    TContainer      -   контейнер, для которого используется прокси
*/

template<typename TContainer>
class TProxy
{
    public:
        //  Размерность контейнера (и прокси)
        static const size_t CONTAINER_DIMENSION =   TContainer::dimensions;

        //  Тип хранимого элемента
        using value_type = typename TContainer::value_type;

        //  Запрет создавать объект по умолчанию - необходима ссылка на контейнер и первый индекс
        TProxy() = delete;

        //  Конструктор копирования
        TProxy(const TProxy& other):_container(other._container),
                                    _dimension(other._dimension),
                                    _indexes(other._indexes)

        {
        };

        //  Основной конструктор для прокси
        TProxy(TContainer& container, const size_t first_index):
            _container(container),
            _dimension(0),
            _indexes()
        {
            _indexes.set(0,first_index);
        };

        /*!  Оператор индексирования.
            Прокси накапливает внутри себя все обращения к индексам.
        */
        TProxy& operator[] (const size_t idx){
            ++_dimension;
            //  Проверка корректности измерений (накопленных индексов)
            if(CONTAINER_DIMENSION<=_dimension)
                throw std::logic_error("Wrong indexes in TProxy::operator[]!");
            _indexes.set(_dimension, idx);
            return *this;
        }

        /*! Оператор присваивания элемента.
            Вызов присваивания перехватывается.
            Контейнеру направляется присваиваемое значение и накопленные индексы
        */
        TProxy& operator= (value_type val){
            //  Проверка корректности измерений (накопленных индексов)
            if(CONTAINER_DIMENSION-1!=_dimension)
                throw std::logic_error("Wrong indexes in TProxy::operator=!");
            _container.set(_indexes, val);
            return *this;
        };

        /*!
            Получение значения элемента по индексу.
            Накопленные индексы передаются контейнеру и возвращается значение.
        */
        operator value_type(){
            //  Проверка корректности измерений (накопленных индексов)
            if(CONTAINER_DIMENSION-1!=_dimension)
                throw std::logic_error("Wrong indexes in TProxy::operator T!");
            return _container.get(_indexes);
        }

        ~TProxy(){};

    private:
        //  Проксируемый контейнер
        TContainer&                         _container;
        //  Количество, накопленных индексов
        size_t                              _dimension;
        //  Накопленные индексы
        TCoordinates<CONTAINER_DIMENSION>   _indexes;
};

#endif // TPROXY_H
