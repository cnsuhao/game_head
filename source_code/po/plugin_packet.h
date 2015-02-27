#ifndef PLUGIN_PACKET_H_INCLUDED
#define PLUGIN_PACKET_H_INCLUDED
#include "plugin.h"
namespace PO
{
    template<typename Expand> class Render_Packet;

    template<typename Expand>
    struct Plugin_Ptr
    {
        virtual bool IsPluginExit() const =0;
        virtual void Layer3D(typename Render_Packet<Expand>::RenAdapter& R)=0;
        virtual void Layer2D(typename Render_Packet<Expand>::RenAdapter& R)=0;
        virtual void Respond(const EventBox& EB,typename Render_Packet<Expand>::RenAdapter& R)=0;
    };

    template<typename Pre,typename Expand,typename This,typename ...AP>
    struct RealCreater:public RealCreater<Pre,Expand,AP...>
    {
        std::shared_ptr<This> VirtualPluginCreater(Adapter<POContext,Render>& L,This* );
        template<typename ...AO>
        RealCreater(const AO&... a):RealCreater<Pre,Expand,AP...>(a...){}
    };

    template<typename Pre,typename Expand,typename This>
    struct RealCreater<Pre,Expand,This>:public Pre
    {
        std::shared_ptr<This> VirtualPluginCreater(Adapter<POContext,Render>& L,This* );
        template<typename ...AP>
        RealCreater(const AP&... a):Pre(a...){}
    };

    template<typename Pre,typename Expand,typename ...AP>
        RealCreater<Pre,Expand,AP...> TranslateType(  PluginCreater<AP...>*   );
    template<typename Pre,typename Expand>
        Pre TranslateType(...);

    template<typename Type,typename Expand>
    struct Plugin_Packet
        :public std::enable_if<std::is_base_of< PluginBase ,Type >::value,decltype(TranslateType<Type,Expand>( (Type*)(nullptr)  ))>::type,public Plugin_Ptr<Expand>
    {
        typedef decltype(TranslateType<Type,Expand>( (Type*)(nullptr)  )) RealType;
        bool IsPluginExit() const {return Type::IsExit();}
        void Respond(const EventBox& EB, typename Render_Packet<Expand>::RenAdapter& L )
        {
            typename Type::PluAdapter Tem(L);
            Type::Respond(EB,Tem);
        }
        void Layer2D(typename Render_Packet<Expand>::RenAdapter& L)
        {
            typename Type::PluAdapter Tem(L);
            Type::Layer2D(Tem);
        }
        void Layer3D(typename Render_Packet<Expand>::RenAdapter& L)
        {
            typename Type::PluAdapter Tem(L);
            Type::Layer3D(Tem);
        }
        typename Type::PluAdapter Translate( typename Render_Packet<Expand>::RenAdapter& L ) { typename Type::PluAdapter T(L);return T;  }
        template<typename T> T& Translate(T& L){return L;}
        template<typename ...AD>
        Plugin_Packet( AD&... ap ):RealType(Translate(ap)...){}
    };


    template<typename Pre,typename Expand,typename This,typename ...AP> auto RealCreater<Pre,Expand,This,AP...>::VirtualPluginCreater(Adapter<POContext,Render>& DD,This* )->std::shared_ptr<This>
    {
        Render& L=static_cast<Render&>(DD);
        Render_Packet<Expand>* Ex=dynamic_cast<Render_Packet<Expand>*>(&L);
        return Ex->PointCreate( DD,(This*)(nullptr) );
    };
    template<typename Pre,typename Expand,typename This> auto RealCreater<Pre,Expand,This>::VirtualPluginCreater(Adapter<POContext,Render>& DD,This* )->std::shared_ptr<This>
    {
        Render& L=static_cast<Render&>(DD);
        Render_Packet<Expand>* Ex=dynamic_cast<Render_Packet<Expand>*>(&L);
        return Ex->PointCreate( DD, (This*)(nullptr) );
    };
}

#endif // PLUGIN_PACKET_H_INCLUDED
