#ifndef POCONTEXT_H_INCLUDED
#define POCONTEXT_H_INCLUDED
#include <ostream>
#include "modual/pomodual.h"
#include "render_packet.h"
#include "templatemetaprogramming/adapter.h"
namespace PO
{
    struct POContextIniter
    {
        POContextIniter(){Graphic::Init();}
        ~POContextIniter(){Graphic::Quit();}
    };

    class POContext:public POContextIniter
    {
        template<typename T>        friend int Loop(const T&);
        template<typename Tem>      friend int Loop(std::ostream& OS,const Tem&);
        std::map<int,std::shared_ptr<Render> > RenderMap;
        long SpendTime;
        POContext() {SpendTime=Graphic::GetTick();}
    public:

        template<typename ...Type,typename ...Pa>
            auto CreateRender( const std::shared_ptr<GraphicInfo>& GI, const std::shared_ptr< TypePair< TypeInfo<Type...>,std::tuple<Pa...>   >>& T  ) ->  Adapter<Render_Packet< Render_Modual<Type...> >,Render,Type...,POContext>;
        auto CreateRender( const std::shared_ptr<GraphicInfo>& GI ) -> Adapter<Render_Packet< Render_Modual<EmptyModual> >,Render,EmptyModual,POContext>
        {
            auto Iu=CreateModual<EmptyModual>();
            return CreateRender(GI,Iu);
        }
        void DeliverEvent( const std::shared_ptr<Event>& Tem );
        int ContextLoop();
    };
    template<typename ...Type,typename ...Pa>
    auto POContext::CreateRender( const std::shared_ptr<GraphicInfo>& GI,   const std::shared_ptr< TypePair< TypeInfo<Type...>,std::tuple<Pa...>   >>& T    ) -> Adapter<Render_Packet< Render_Modual<Type...> >,Render,Type...,POContext>
    {
        std::shared_ptr<Render_Packet<Render_Modual<Type...> >  > Tem(new Render_Packet< Render_Modual<Type...> >( *GI,T->Data ));
        std::shared_ptr<Render> List(Tem);
        int i=List->GetWindowIndex();
        RenderMap[i]=List;
        Adapter<Render_Packet< Render_Modual<Type...> >,Render,Type...> TR(*Tem);
        return TR.Connect(*this);
    }
}


#endif // POCONTEXT_HPP_INCLUDED
