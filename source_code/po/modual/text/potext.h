#ifndef POTEXT_HPP
#define POTEXT_HPP
#include <sstream>
#include <deque>
#include "pofont.h"
#include "../../texture.h"
namespace PO
{

    class StaticText:public VertexInfo,public ColorInfo,public TexCoorInfo
    {
        std::shared_ptr<StaticTextData> Data;
    public:
        operator const GraphicTexture& () const {return *Data->GetGraphic();}
        const std::shared_ptr<StaticTextData>& GetData() const {return Data;}
        int GetWidth() const {return Data->GetWidth();}
        StaticText(){}
        void DrawText(Render& R)
        {
            Draw_Color DC(R,*this,*this);
            Draw_TexCoor DT(R,*this,*this);
            Draw_Texture DT2(R,*this);
            Draw_Vertex DV ( R,*this);
        }
        void CreateStaticText(FontManager& FM,const std::string& L){Data=FM.CreateStaticText(L);}
        void Free(){decltype(Data) Empty;Data=Empty;}
    };



    /*struct DynamicTextFigure
    {
        TextureFigure TP;
        int RenderedWidth;
        void clear(){RenderedWidth=0;TP.clear();}
    };

    class DynamicText:public DynamicTextData<std::deque>
    {
        DynamicTextFigure DTP;
    public:
        template<typename ...ALL>
            void DrawDynamic( void (*)(DynamicTextFigure& ST,std::shared_ptr<SingleCharStruct>& Tem,ALL... ),ALL... );
    };

    class NumberText
    {
        DynamicText DT;
        static std::wstringstream WSS;
    public:
        template<typename Type>
            void Connect( FontManager& FM,const Type& T )
            {
                WSS.str();
                WSS.clear();
                WSS<<T;
                std::wstring Tem;
                WSS>>Tem;
                FM.CreateDynamicText(Tem,DT);
            }
        template<typename ...ALL>
        void DrawNumber( void (* FP)(DynamicTextFigure& ST,std::shared_ptr<SingleCharStruct>& Tem,ALL... ),ALL... al)
        {
            DT.DrawDynamic( FP,al...  );
        }
    };

    template<typename ...ALL>
        void DynamicText::DrawDynamic(void (*FP)(DynamicTextFigure&,std::shared_ptr<SingleCharStruct>& Tem,ALL... ),ALL... al)
        {
            int RecordWidth=0;
            glEnable(GL_TEXTURE_2D);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glEnableClientState(GL_VERTEX_ARRAY);
            bool ColorEnable=false;
            bool NormalEnable=false;
            for(auto &SCD :*this)
            {
                DTP.RenderedWidth=RecordWidth;
                if(SCD) { RecordWidth++;continue;  }
                //auto Ui=SCD.lock();
                (*FP)(DTP,SCD,al...);
                if(!DTP.TP.GLP.DrawOrder.empty())
                {
                    if(!DTP.TP.GLP.Color.empty())
                    {
                        if(!ColorEnable)
                        {
                            glEnableClientState(GL_COLOR_ARRAY);
                            ColorEnable=true;
                        }
                        glColorPointer(4,GL_FLOAT,0,&DTP.TP.GLP.Color[0]);
                    }else if(ColorEnable)
                    {
                        glDisableClientState(GL_COLOR_ARRAY);
                        ColorEnable=false;
                    }

                    if(!DTP.TP.GLP.Normal.empty())
                    {
                        if(!NormalEnable)
                        {
                            glEnableClientState(GL_NORMAL_ARRAY);
                            NormalEnable=true;
                        }
                        glNormalPointer(GL_FLOAT,0,&DTP.TP.GLP.Normal[0]);
                    }else if(NormalEnable)
                    {
                        glDisableClientState(GL_NORMAL_ARRAY);
                        NormalEnable=false;
                    }
                    glVertexPointer(DTP.TP.GLP.VectorSize,GL_FLOAT,0,&DTP.TP.GLP.Vector[0]);
                    glTexCoordPointer(2,GL_FLOAT,0,&DTP.TP.TextureCoor[0]);
                    glBindTexture(GL_TEXTURE_2D,SCD->GetGraphic()->GetPoint());
                    glDrawElements(DTP.TP.GLP.DrawType,DTP.TP.GLP.DrawOrder.size(),GL_UNSIGNED_INT,&DTP.TP.GLP.DrawOrder[0]);
                }
                RecordWidth+=SCD->GetWidth();
            }
            if(NormalEnable) glDisableClientState(GL_NORMAL_ARRAY);
            if(ColorEnable)  glDisableClientState(GL_COLOR_ARRAY);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisable(GL_TEXTURE_2D);
        }

        //void SetRectangle2D(StaticText& ST,float Size,const Vertex<2>& Sh=Ver(0.0,0.0),const Color<4>& Co=Col(1.0,1.0,1.0,1.0)){SetEqualRectangle(ST,ST,Size,Sh,Co);}
        //void Translation( StaticText& ST,float Size,const Vertex<2>& Sh ){ Translation(ST.STP.GTP,Sh); }
        namespace Pattern{
            namespace Fon{
                void Rectangle2D(DynamicTextFigure& ST,std::shared_ptr<SingleCharStruct>& Tem,float Size,Vertex<2> Sh,Color<4> Co);
                void SetRectangle2D(StaticText& ST,float Size,const Vertex<2>& Sh=Ver(0.0,0.0),const Color<4>& Co=Col(1.0,1.0,1.0,1.0));
                inline void Translate(StaticText& ST,const Normal<2>& L){ Pattern::Tex::Translate(ST.STP,L);}
                inline void Reset(StaticText& ST,const Vertex<2>& P){  Pattern::Tex::Reset(ST.STP,P);}
                inline void Reset(StaticText& ST,const Color<4>& P){  Pattern::Tex::Reset(ST.STP,P);}
            }
        }
    /*struct DynamicStruct:public TexturePattern
    {
        unsigned int Count=0;
        const Font::DynamicTextData* DTD;
        float GetRateW(){return DTD->GetRateW();}
        float GetRateH(){return DTD->GetRateH();}
        unsigned int GetWidth(){return DTD->GetWidth();}
        unsigned int GetPoint(){return DTD->GetPoint();}
    };

    class TextDynamic
    {
    protected:
        Font::DynamicText<std::deque> PA;
    public:
        void Clear(){PA.clear();}
        bool CreateText(const std::string& P){Clear();return Font::Manager::CreateDynamicText(P,PA);}
        bool InsertText(const std::string& P){return Font::Manager::CreateDynamicText(P,PA);}
        operator bool(){return !PA.empty();}
        unsigned int Width();
        unsigned int PopFront(unsigned int S=1);
        unsigned int PopBack(unsigned int S=1);
        template<typename Type,typename ...TP>
            void Display(const Type& L,const TP&... TO) const
            {
                DynamicStruct Tem;
                glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                glEnableClientState(GL_COLOR_ARRAY);
                glEnableClientState(GL_NORMAL_ARRAY);
                glEnable(GL_TEXTURE_2D);
                for( auto Pl:PA)
                {
                    if( Font::Manager::GetDynamicData(Pl,Tem.DTD))
                    {
                        L(Tem,TO...);
                        if(Tem.Legal())
                        {
                            glVertexPointer(Tem.LS,GL_FLOAT,0,&Tem.Loc[0]);
                            glTexCoordPointer(2,GL_FLOAT,0,&Tem.Tex[0]);
                            glColorPointer(Tem.CS,GL_FLOAT,0,&Tem.Col[0]);
                            glNormalPointer(GL_FLOAT,0,&Tem.Nor[0]);
                            glBindTexture(GL_TEXTURE_2D,Tem.GetPoint());
                            glDrawElements(GL_TRIANGLES,Tem.Dra.size(),GL_UNSIGNED_INT,&Tem.Dra[0]);
                            Tem.Count+=(Tem.DTD)->GetWidth();
                        }else Tem.Count+=1;
                    }else{
                        Tem.Count+=1;
                    }
                }
                glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                glDisableClientState(GL_COLOR_ARRAY);
                glDisableClientState(GL_NORMAL_ARRAY);
                glDisable(GL_TEXTURE_2D);
            }
    };

    unsigned int TextDynamic::PopFront(unsigned int S)
    {
        unsigned int Size=PA.size();
        if(Size<=S)
        {
            PA.clear();
            return Size;
        }else{
            for(int i=0;i<S;++i)
                PA.pop_front();
            return S;
        }
    }

    unsigned int TextDynamic::PopBack(unsigned int S)
    {
        unsigned int Size=PA.size();
        if(Size<=S)
        {
            PA.clear();
            return Size;
        }else{
            for(int i=0;i<S;++i)
                PA.pop_back();
            return S;
        }
    };

    class TextNumber
    {
        static std::stringstream StaticStream;
        TextDynamic TD;
        std::string Number;
    public:
        template<typename ST,typename T,typename ...TP>
            void Display(const ST& Ty,const T& L,const TP&... TO)
            {
                StaticStream.clear();
                StaticStream<<Ty;
                StaticStream>>Number;
                TD.CreateText(Number);
                TD.Display(L,TO...);
            }
    };
    std::stringstream TextNumber::StaticStream;

    unsigned int TextDynamic::Width()
    {
        unsigned int CW=0;
        unsigned int Point;
        const Font::DynamicTextData* DTD;
        for(auto Po=PA.begin();Po!=PA.end();++Po)
            if(Font::Manager::GetDynamicData(*Po,DTD))
                CW+=DTD->GetWidth();
        return CW;
    }


    auto DynTexSqu_P2SC4=std::bind(
                                    [] (DynamicStruct& DS , const Point<2>& S , float Size ,const Color<4>& C)
                                  {
                                        if(DS.Count==0)
                                        {
                                            DS.LPS=2;
                                            DS.LS=2;
                                            DS.CS=4;
                                            DS.Dra={0,1,2,2,0,3};
                                            DS.Col ={     C(0),C(1),C(2),C(3),
                                                                C(0),C(1),C(2),C(3),
                                                                C(0),C(1),C(2),C(3),
                                                                C(0),C(1),C(2),C(3)};

                                            DS.Nor={     0.0,0.0,-1.0,
                                                             0.0,0.0,-1.0,
                                                              0.0,0.0,-1.0,
                                                               0.0,0.0,-1.0};
                                        }
                                        DS.Tex={0.0,0.0,
                                                    DS.GetRateW(),0.0,
                                                    DS.GetRateW(),DS.GetRateH(),
                                                    0.0,DS.GetRateH() };
                                        float TemSize=DS.Count*0.25*Size;
                                        float EachSize=DS.GetWidth()*0.5;
                                        float SX=S(0)+DS.Count*0.25*Size;
                                        float EaX=DS.GetWidth()*0.25*Size;
                                        DS.Loc={   SX,S(1),
                                                        SX+EaX,S(1),
                                                        SX+EaX,S(1)-2*EaX,
                                                        SX,S(1)-2*EaX};
                                  }
                                  ,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);*/
}
#endif // POTTF_H
