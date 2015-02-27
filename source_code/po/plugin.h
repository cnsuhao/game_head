#ifndef PLUGIN_H
#define PLUGIN_H
#include "elementfigure.h"
#include "templatemetaprogramming/typeselect.h"
#include "templatemetaprogramming/adapter.h"
#include "render.h"
namespace PO
{
    class POContext;

    class PluginBase
    {
        bool Exit;
        PluginBase():Exit(false){}
        template<typename ...AP> friend class Plugin;
    public:
        bool IsExit()const {return Exit;}
        void ExitPlugin(){Exit=true;}
        virtual ~PluginBase(){}
        void GetMouseLocation(Render& L,Vertex<2>& Mouse,const std::shared_ptr<Event>& E){L.GetMouseLocation(Mouse(0),Mouse(1),E);}
        void CloseRender(Render& L){L.ExitRender();}
        void GetScreen2D(Render& L,float& X,float& Y){X=L.GetScreen2DX();Y=L.GetScreen2DY();}
        void SetScreen2D(Render& L,float X,float Y){ L.Set2DView(X,Y);    }
        long GetSpendTime(Render& L){return L.GetSpendTime();}
        long GetIntervalTime(Render& L){return L.GetIntervalTime();}
        void ResetWindowSize(Render& L,int X,int Y){L.ResetWindowSize(X,Y);}
        void GetWindowSize(Render& L,int& X,int& Y){X=L.GetWindowW();Y=L.GetWindowH();}
        void ExitRender(Render& L){L.ExitRender();}
    };

    template<typename ...AP>
    struct Plugin:public PluginBase
    {
        typedef Adapter<POContext,AP...> PluAdapter;
        Plugin(){}
        virtual void Respond(const EventBox& ,PluAdapter& L){}
        virtual void Layer2D(PluAdapter& L){}
        virtual void Layer3D(PluAdapter& L){}
    };

    template<typename This>
    struct VirtualCreater
    {
        virtual std::shared_ptr<This> VirtualPluginCreater(Adapter<POContext,Render>&,This* )=0;
    };

    template<typename This,typename ...AP>
    struct PluginCreaterPlu:public VirtualCreater<This>,public PluginCreaterPlu<AP...>{};
    template<typename This>
    struct PluginCreaterPlu<This>:public VirtualCreater<This>{};

    template<typename ...AL>
    struct PluginCreater:public PluginCreaterPlu<AL...>
    {
        template<typename Type> std::shared_ptr<Type> CreatePlugin(Adapter<POContext,Render> R)
        {
            VirtualCreater<Type>& Th(*this);
            return Th.VirtualPluginCreater(R,(Type*)(nullptr));
        }
        typedef PluginCreater creater_type;
    };
}
#endif // PLUGIN_HPP
