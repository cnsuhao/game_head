#ifndef TYPEPAIR_H_INCLUDED
#define TYPEPAIR_H_INCLUDED
#include <tuple>
#include <memory>
template<typename ...Type>
    struct TypeInfo{};

template<typename TI,typename Ik>
    struct TypePair
    {
        Ik Data;
        TypePair(const Ik& I ):Data(I){}
        const Ik& GetData()const {return Data;}
    };

template<unsigned int K>
struct EmptyTupleCreater
{
    static auto Create() -> decltype(
                                     std::tuple_cat(
                                                    std::tuple<std::tuple<> >() ,
                                                    EmptyTupleCreater<K-1>::Create()
                                                    )
                                     )
    {
        std::tuple<std::tuple<>> Tem;
        return std::tuple_cat( Tem , EmptyTupleCreater<K-1>::Create());
    }
};

template<>
struct EmptyTupleCreater<1>
{
    static std::tuple<std::tuple<>> Create()
    {
        std::tuple<std::tuple<>> Tem;
        return Tem;
    }
};

template<typename ...T1,typename ...T2,typename ...I1,typename ...I2>
auto ConnectTypePair(   const std::shared_ptr<TypePair<TypeInfo<T1...>,std::tuple<I1...>>>& TP1,
                        const std::shared_ptr<TypePair<TypeInfo<T2...>,std::tuple<I2...>>>& TP2)
    -> std::shared_ptr<TypePair<TypeInfo<T1...,T2...> ,decltype( std::tuple_cat(TP1->Data,TP2->Data)   )   > >
    {
        std::shared_ptr<TypePair<TypeInfo<T1...,T2...> ,decltype( std::tuple_cat(TP1->Data,TP2->Data)   )   > >
        TemPtr(new TypePair<TypeInfo<T1...,T2...> ,decltype( std::tuple_cat(TP1->Data,TP2->Data )   )   > ( std::tuple_cat(TP1->Data,TP2->Data) ));
        return TemPtr;
    }

template<typename Name,typename ...Para>
    auto CreateTypePair( Para... Pa ) -> std::shared_ptr<TypePair<TypeInfo<Name>,std::tuple<std::tuple<Para...>>>>
    {
        std::shared_ptr<TypePair<TypeInfo<Name> ,std::tuple<std::tuple<Para...>> > > TemPtr(new TypePair<TypeInfo<Name>,std::tuple<std::tuple<Para...>>>((std::make_tuple(std::make_tuple(Pa...)))));
        return TemPtr;
    }

template<typename Type,typename ...Name>
    auto CreateTypePair(void) ->
    std::shared_ptr<TypePair<TypeInfo<Type,Name...>,decltype(EmptyTupleCreater<sizeof...(Name)+1>::Create())>>
    {
            std::shared_ptr<TypePair<TypeInfo<Type,Name...>,decltype(EmptyTupleCreater<sizeof...(Name)+1>::Create())>>
                Tem(new TypePair<TypeInfo<Type,Name...>,decltype(EmptyTupleCreater<sizeof...(Name)+1>::Create())> (EmptyTupleCreater<sizeof...(Name)+1>::Create()));
        return Tem;
    }

#endif // TYPEPAIR_HPP_INCLUDED
