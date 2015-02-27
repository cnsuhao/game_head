#ifndef PORENDER_PACKET_H
#define PORENDER_PACKET_H
#include "render.h"
#include "plugin_packet.h"
#include "templatemetaprogramming/typeselect.h"
#include "templatemetaprogramming/renderfunctioncheck.h"
#include "templatemetaprogramming/functiondetect.h"
namespace PO
{

    MEMBER_FUNCTION_DETECTOR(POS,PosRender,void,(L),typename Render::ModualAdapter& L);
    MEMBER_FUNCTION_DETECTOR(PRE,PreRender,void,(L),typename Render::ModualAdapter& L);
    MEMBER_FUNCTION_DETECTOR(PRE,PreWindowChange,void,() );
    MEMBER_FUNCTION_DETECTOR(POS,PosWindowChange,void,(GI,GI2),const PO::GraphicInfo& GI,const PO::GraphicInfo& GI2 );
    MEMBER_FUNCTION_DETECTOR(CRE,PluCreate,void,() );
    MEMBER_FUNCTION_DETECTOR(CLO,PluClose,void,() );

    template<typename ...Expand> struct Render_Modual:public UnbalanceTreeInheritance<Expand...>
    {
        template<typename T>    Render_Modual( T t ): UnbalanceTreeInheritance<Expand...>(t){}
        typedef Adapter<Expand...,Render> ModAdapter;
        typedef Adapter<Expand...,Render,POContext> RenAdapter;
        UnbalanceTreeInheritance<Expand...>& GetMaxLevel() {return *this;}
        template<typename T,typename ...AP> void PreRenderDetail(UnbalanceTreeInheritance<T,AP...>& L,Render::ModualAdapter& MA){MEMBER_FUNCTION_PROCESS(PRE,PreRender,T,L,MA);PreRenderDetail( L.GetUpper(),MA );}
        template<typename T> void PreRenderDetail( UnbalanceTreeInheritance<T>& L,Render::ModualAdapter& MA ){MEMBER_FUNCTION_PROCESS(PRE,PreRender,T,L,MA);}

        template<typename T,typename ...AP> void PosRenderDetail(UnbalanceTreeInheritance<T,AP...>& L,Render::ModualAdapter& MA){MEMBER_FUNCTION_PROCESS(POS,PosRender,T,L,MA);PosRenderDetail( L.GetUpper(),MA );}
        template<typename T> void PosRenderDetail( UnbalanceTreeInheritance<T>& L,Render::ModualAdapter& MA ){MEMBER_FUNCTION_PROCESS(POS,PosRender,T,L,MA);}

        template<typename T,typename ...AP> void CreatePluDetail(UnbalanceTreeInheritance<T,AP...>& L){ MEMBER_FUNCTION_PROCESS(CRE,PluCreate,T,L);CreatePluDetail( L.GetUpper()); }
        template<typename T> void CreatePluDetail( UnbalanceTreeInheritance<T>& L){MEMBER_FUNCTION_PROCESS(CRE,PluCreate,T,L);}

        template<typename T,typename ...AP> void ClosePluDetail(UnbalanceTreeInheritance<T,AP...>& L){MEMBER_FUNCTION_PROCESS(CLO,PluClose,T,L);ClosePluDetail( L.GetUpper());}
        template<typename T> void ClosePluDetail( UnbalanceTreeInheritance<T>& L){MEMBER_FUNCTION_PROCESS(CLO,PluClose,T,L);}

        template<typename T,typename ...AP> void PreWinDetail(UnbalanceTreeInheritance<T,AP...>& L){ MEMBER_FUNCTION_PROCESS(PRE,PreWindowChange,T,L);PreWinDetail( L.GetUpper()); }
        template<typename T> void PreWinDetail( UnbalanceTreeInheritance<T>& L){MEMBER_FUNCTION_PROCESS(PRE,PreWindowChange,T,L);}
        template<typename T,typename ...AP> void PosWinDetail(UnbalanceTreeInheritance<T,AP...>& L,const PO::GraphicInfo& GI,const PO::GraphicInfo& GI2){ MEMBER_FUNCTION_PROCESS(POS,PosWindowChange,T,L,GI,GI2);PosWinDetail( L.GetUpper(),GI,GI2); }
        template<typename T> void PosWinDetail( UnbalanceTreeInheritance<T>& L,const PO::GraphicInfo& GI,const PO::GraphicInfo& GI2){MEMBER_FUNCTION_PROCESS(POS,PosWindowChange,T,L,GI,GI2);}
    };



    template<typename Expand>
        class Render_Packet:public Render,public Expand
        {

        public:
            friend class POContext;

            const GraphicInfo& GetGraphicInfo()const {return *this;}

            std::list<std::shared_ptr<Plugin_Ptr<Expand> > > PluginList;

            void PreRender(typename Render::ModualAdapter i)    {this->PreRenderDetail(Expand::GetMaxLevel(),i);}
            void PosRender(typename Render::ModualAdapter i)    {this->PosRenderDetail(Expand::GetMaxLevel(),i);}
            void PluCreate(){this->CreatePluDetail( Expand::GetMaxLevel() );}
            void PluClose(){this->ClosePluDetail( Expand::GetMaxLevel() );}
            void PreWinChange(){this->PreWinDetail(Expand::GetMaxLevel());}
            void PosWinChange(const PO::GraphicInfo& GI,const PO::GraphicInfo& GI2){this->PosWinDetail(Expand::GetMaxLevel(),GI,GI2);}

            void RenderLoop(POContext& );
            void DeliverEvent(typename Expand::RenAdapter&);
            void Render2D(typename Expand::RenAdapter&);
            void Render3D(typename Expand::RenAdapter&);

            template<typename UnknowType>   Render_Packet( GraphicInfo& GI,UnknowType& UT  ):Render(GI),Expand(UT){}

            template<typename Type,typename E> friend class Plugin_Packet;

            template<typename Type>
                std::shared_ptr<Type> PointCreate(POContext& L, Type* )
                {
                    typename Expand::ModAdapter CC(*this);
                    auto P=CC.Connect(L);
                    typename Type::PluAdapter TC(P);
                    std::shared_ptr<Plugin_Packet<Type,Expand>>
                        Tem( new Plugin_Packet<Type,Expand>( TC ) );
                    std::shared_ptr<Plugin_Ptr<Expand>> Pc(Tem);
                    PluginList.push_back(Pc);
                    PluCreate();
                    return Tem;
                }

            template<typename T> friend class Render_Creater;
        public:

            template< typename Type,typename ...AP>
                std::shared_ptr<Type> CreatePlugin(AP... p)
                {
                    SetCurrent();
                      std::shared_ptr<Plugin_Packet<Type,Expand>>
                        Tem( new Plugin_Packet<Type,Expand>(p...) );
                      std::shared_ptr<Plugin_Ptr<Expand>> Pc(Tem);
                    PluginList.push_back(Pc);
                    PluCreate();
                    return Tem;
                }
        };

    template<typename Expand>
        void Render_Packet<Expand>::RenderLoop(POContext& P)
        {
            SetCurrent();
            typename Expand::ModAdapter AdaT(*this);
            auto Ada=AdaT.Connect(P);
            PreRender(Ada);
            DeliverEvent(Ada);
            CleanScreen();
            SetParallel();
            Render2D(Ada);
            SetPerspective();
            Render3D(Ada);
            FinishLoop();
            PosRender(Ada);
            SwapScreen();
        }

    template<typename Expand>
        void Render_Packet<Expand>::Render2D(typename Expand::RenAdapter& P)
        {
            for(auto L=PluginList.begin();L!=PluginList.end();)
            {
                if((*L)->IsPluginExit())
                {
                    PluginList.erase(L++);
                    PluClose();
                    continue;
                }else
                    (*L)->Layer2D(P);
                ++L;
            }
        }

    template<typename Expand>
        void Render_Packet<Expand>::Render3D(typename Expand::RenAdapter& P)
        {
            for(auto L=PluginList.begin();L!=PluginList.end();)
            {
                if((*L)->IsPluginExit())
                {
                    PluginList.erase(L++);
                    PluClose();
                    continue;
                }else
                    (*L)->Layer3D(P);
                ++L;
            }
        }

    template<typename Expand>
        void Render_Packet<Expand>::DeliverEvent(typename Expand::RenAdapter& P)
        {
            for(auto L=PluginList.begin();L!=PluginList.end();)
            {
                if((*L)->IsPluginExit())
                {
                    PluginList.erase(L++);
                    PluClose();
                    continue;
                }else (*L)->Respond(GetBox(),P);
                ++L;
            }
        }
    template<typename T>
        struct Render_Creater
        {
            template<typename Expand,typename ...AP>
            static auto Create( Render_Packet<Expand>& RP,AP... p ) -> std::shared_ptr<Plugin_Ptr<Expand>>
            {
                RP.SetCurrent();
                std::shared_ptr<Plugin_Packet<T,Expand>> Tem( new Plugin_Packet<T,Expand>(p...) );
                std::shared_ptr<Plugin_Ptr<Expand>> Pc(Tem);
                RP.PluginList.push_back(Pc);
                RP.PluCreate();
                return Tem;
            }
        };

    template<typename T,typename Ren,typename ...Other,typename ...AP>
        auto CreatePlugin(  Adapter<Ren,Other...>& L,AP... ap) ->
            decltype( Render_Creater<T>::Create( static_cast<Ren&>(L),ap...))
            {return Render_Creater<T>::Create( static_cast<Ren&>(L),ap...);}

}
#endif // PORENDER_HPP
