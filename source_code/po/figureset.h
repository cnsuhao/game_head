#ifndef FIGURESET_H_INCLUDED
#define FIGURESET_H_INCLUDED
#include <vector>
#include "render.h"
#include "templatemetaprogramming/adapter.h"
namespace PO
{
    struct VertexInfo
    {
        GLenum DrawType=GL_POINTS;
        std::vector<unsigned int> DrawOrder;
        unsigned int Dimensional=2;
        std::vector<float> Vertex;
        unsigned int MaxOrder=0;
        bool Avalible() const {return Vertex.size()/Dimensional>=MaxOrder;}
        VertexInfo& Pick ( const VertexInfo&);
    };

    class Draw_Vertex
    {
        bool& Ready;
        void* operator new(size_t Z) =delete;
    public:
        Draw_Vertex(Render&,const VertexInfo& );
        ~Draw_Vertex();
    };

    struct ColorInfo
    {
        unsigned int Dimensional=3;
        std::vector<float> Color;
        bool operator == ( const VertexInfo& DI) const {return Color.size()/Dimensional==DI.Vertex.size()/DI.Dimensional;}
    };

    class Draw_Color
    {
        bool& Ready;
        void* operator new(size_t Z) =delete;
    public:
        Draw_Color(Render&,const VertexInfo& VI,const ColorInfo& GI);
        ~Draw_Color();
    };

    struct NormalInfo
    {
        std::vector<float> Normal;
        bool operator ==( const VertexInfo& DI ) const {return Normal.size()/3==DI.Vertex.size()/DI.Dimensional;}
    };

    class Draw_Normal
    {
        bool& Ready;
        void* operator new(size_t Z) =delete;
    public:
        Draw_Normal(Render& , const VertexInfo& , const NormalInfo&);
        ~Draw_Normal();
    };

    struct TexCoorInfo
    {
        float RateW=0.0,RateH=0.0;
        std::vector<float> TexCoor;
        bool operator ==( const VertexInfo& DI) const {return TexCoor.size()/2==DI.Vertex.size()/DI.Dimensional;}
        TexCoorInfo& operator= (const TexCoorInfo& TC);
        void SetRate(float W,float H){RateW=W;RateH=H;}
    };

    class Draw_TexCoor
    {
        bool& Ready;
        void* operator new(size_t Z) =delete;
    public:
        Draw_TexCoor(Render&,const VertexInfo&,const TexCoorInfo&);
        ~Draw_TexCoor();
    };



    /*template<typename AP>
    class FormatPlu:public AP
    {
    public:
        template<typename I>
            Format(I& U):AP(U){}
    };

    template<typename ...AP>
    class Format:public FormatPlu<AP>...
    {
    public:
        template<typename I>
            Forma
    };*/

    namespace VerTool
    {
        void SetRect(VertexInfo&,float SX,float SY,float WX,float WY,float HX,float HY);
        void SetLine(VertexInfo&,float SX,float SY,float EX,float EY);
        void AddLine(VertexInfo&,float SX,float SY,float EX,float EY);
        void SetLineLoop(VertexInfo&,float SX,float SY,float EX,float EY);
        void AddLineLoop(VertexInfo&,float X,float Y);

        void Translation(VertexInfo& VI,float X,float Y,float Z);
    }
    namespace ColTool
    {
        void Paint(VertexInfo&,ColorInfo&,float R=1.0,float G=1.0,float B=1.0);
        inline void Paint(Adapter<VertexInfo,ColorInfo> L,float R=1.0,float G=1.0,float B=1.0){Paint(L,L,R,G,B);}
        void Paint(VertexInfo&,ColorInfo&,float R,float G,float B,float A);
        inline void Paint(Adapter<VertexInfo,ColorInfo> L,float R,float G,float B,float A){Paint(L,L,R,G,B,A);}
        void Cover(ColorInfo&,float A);
    }
    namespace NorTool
    {
        void EqualNormal(VertexInfo&,ColorInfo&,float X,float Y,float Z);
    }
    namespace TexTool
    {
        inline void PaseInfo(TexCoorInfo& TC,const GraphicTexture& GT){TC.SetRate(GT.GetRateW(),GT.GetRateH());}
        void VerRotEqu2D(VertexInfo& VI,TexCoorInfo& TI,const GraphicTexture& GT,float Rotate,float SX=0.0,float SY=1.0);
        inline void VerRotEqu2D(Adapter<VertexInfo,TexCoorInfo> TI,const GraphicTexture& GT,float Rotate,float SX=0.0,float SY=1.0){VerRotEqu2D(TI,TI,GT,Rotate,SX,SY);}
        void TexRotEqu(VertexInfo& VI,TexCoorInfo& TI,const GraphicTexture& GT,float SX,float SY,float Size=1.0);
        inline void TexRotEqu(Adapter<VertexInfo,TexCoorInfo> TI,const GraphicTexture& GT,float SX,float SY,float Size=1.0){TexRotEqu(TI,TI,GT,SX,SY,Size);}
    }
    namespace ForTool
    {
        inline void InfoEqual(VertexInfo& VI,VertexInfo& VI2){VI2=VI;}
        inline void InfoEqual(TexCoorInfo& TI,TexCoorInfo& TI2){}
        inline void InfoEqual(ColorInfo& CI,ColorInfo& CI2){CI2=CI;}
        inline void InfoEqual(NormalInfo& NI,NormalInfo& NI2){NI2=NI;}
        template<typename This,typename ...AP>
            void EqualTo( Adapter<This,AP...> So,Adapter<This,AP...> Fo )
            {
                Adapter<AP...> TC1(So);
                InfoEqual( static_cast<This&>(So),static_cast<This&>(Fo) );
                EqualTo(TC1,Fo);
            }
        template<typename This>
            void EqualTo( Adapter<This> So,Adapter<This> Fo )
            {
                InfoEqual( static_cast<This&>(So),static_cast<This&>(Fo) );
            }
    }

    template<typename This,typename ...AP>
    class InfoPlu:public This,public InfoPlu<AP...>
    {
    };

    template<typename This>
    class InfoPlu<This>:public This
    {

    };

    template<typename ...AP>
    class Info:public InfoPlu<AP...>
    {
    public:
        template<typename This,typename ...TO>
        void SingleEqual( Info<TO...>& IF)
        {
            This& I=IF;
            This& F=*this;
            IF=*this;
        }
        template<typename ...AO>
        void EqualTo(  Info<AO...>& L)
        {
            Adapter<AO...> T1(*this);
            Adapter<AO...> T2(L);
            ForTool::EqualTo(T1,T2);
        }
        void Draw(Render& L)
        {
            InfoPlu<AP...>::Draw(L);
        }
    };






    /*struct FigurePattern
    {
        std::vector<float> VectorCenter;
        std::vector<float> Vector;
        unsigned int VectorSize=0;

        std::vector<float> Normal;

        std::vector<float> Color;

        GLenum DrawType=GL_POINTS;
        std::vector<unsigned int> DrawOrder;
        unsigned int MaxDraw=0;
        void clear()
        {
            VectorCenter.clear();
            Vector.clear();
            VectorSize=0;
            DrawType=GL_POINTS;
            Normal.clear();
            Color.clear();
            DrawOrder.clear();
            MaxDraw=0;
        }
    };

    namespace Pattern
    {
        namespace Fig{
            void DrawFigurePattern( const FigurePattern& GP );
            void AddLine(FigurePattern& GP,const Vertex<2>& Start,const Vertex<2>& End, const Color<4>&);
            void AddRectance2D( FigurePattern& GP ,const Vertex<2>& PC, const Normal<2>& T, const Normal<2>& D,const Color<4>& C);
            void Transltae(FigurePattern& GP,const Normal<2>& PL);
            void Reset(FigurePattern& PL,const Vertex<2>& L);
            void Reset(FigurePattern& PL,const Color<4>& C);
        }
    }*/
}
#endif // GLPATTERN_HPP_INCLUDED
