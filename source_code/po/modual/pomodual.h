#ifndef POMODUAL_H_INCLUDED
#define POMODUAL_H_INCLUDED
#include <list>
#include <memory>
#include <tuple>
#include "../templatemetaprogramming/inheritance.h"

namespace PO
{
    class EmptyModual{};
    template< typename Type ,typename ...AP>
        inline auto CreateGenerialModual( AP... ap) -> decltype(CreateTypePair<Type>(ap...)){Type::PreConstruct(ap...);return CreateTypePair<Type>( ap... );}
    template< typename Type ,typename ...AP>
        inline auto CreateModual( AP... ap) -> decltype(CreateTypePair<Type>(ap...)){return CreateTypePair<Type>( ap... );}
    template< typename ...Type>
        inline auto CreateModual() -> decltype(CreateTypePair<Type...>()){return CreateTypePair<Type...>();}
    template<typename ...T1,typename ...T2,typename ...I1,typename ...I2>
        inline auto IncludeModual(   const std::shared_ptr<TypePair<TypeInfo<T1...>,std::tuple<I1...>>>& TP1,
                        const std::shared_ptr<TypePair<TypeInfo<T2...>,std::tuple<I2...>>>& TP2)
    -> decltype(ConnectTypePair(TP1,TP2))
    {
        return ConnectTypePair(TP1,TP2);
    }

    template<typename ...ALLModual>
        struct ModualType
        {
            typedef UnbalanceTreeInheritance<ALLModual...> type;
        };

    template<typename ...All,typename Type>
        UnbalanceTreeInheritance<All...>
            AbstractModualType( const TypePair< TypeInfo<All...>,Type >& L  ){}
    template< typename Mod, template<typename Type> class Plu>
        UnbalanceTreeInheritance<Mod>
            AbstractModualType( std::shared_ptr<Plu<UnbalanceTreeInheritance<Mod> >>& L ){}
}


#endif // POMODUAL_HPP_INCLUDED
