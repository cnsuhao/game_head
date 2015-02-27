#ifndef INHERITANCE_H_INCLUDE
#define INHERITANCE_H_INCLUDE
#include <tuple>
#include <memory>
#include "tupleinitclass.h"
#include "typepair.h"
template<typename ThisClass,typename ...OtherClass>
class UnbalanceTreeInheritance:public TupleInitClass<ThisClass>,public UnbalanceTreeInheritance<OtherClass...>
{
    public:
    template<unsigned int L,unsigned int N,typename ...A1>
        UnbalanceTreeInheritance( const IndexSquence<L,N>& IS, std::tuple<A1...>& T ):TupleInitClass<ThisClass>(std::get<IndexSquence<L,N>::Value>(T)),UnbalanceTreeInheritance<OtherClass...>(IS.Next(),T){}

    template<typename ...A1>
        UnbalanceTreeInheritance( std::tuple<A1...>& T ):UnbalanceTreeInheritance( GetIndex< std::tuple_size<std::tuple<A1...>>::value >(),T ){}
    UnbalanceTreeInheritance<OtherClass...>& GetUpper(){ return *this;}
    typedef ThisClass type;
};

template<typename ThisClass>
class UnbalanceTreeInheritance<ThisClass>:public TupleInitClass<ThisClass>
{
    public:
    template<unsigned int L,unsigned int N,typename ...A1>
        UnbalanceTreeInheritance( const IndexSquence<L,N>& IS, std::tuple<A1...>& T ):TupleInitClass<ThisClass>(std::get<IndexSquence<L,N>::Value>(T)){}
public:
    template<typename ...A1>
        UnbalanceTreeInheritance( std::tuple<A1...>& T ):UnbalanceTreeInheritance( GetIndex< std::tuple_size<std::tuple<A1...>>::value >(),T ){}
    typedef ThisClass type;
};
template<typename This> struct UnbalanceTreeInheritanceType{};
template<typename This,typename ...Other>
    struct UnbalanceTreeInheritanceType<UnbalanceTreeInheritance<This,Other...>>
    {
        typedef This type;
    };

#endif // INHERITANCE_HPP_INCLUDE
