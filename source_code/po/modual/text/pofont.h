#ifndef FONTMANAGER_H
#define FONTMANAGER_H
#include <map>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../../graphic/graphic.h"
#include "../../language.h"
#include "../pomodual.h"
#include "../../render.h"
namespace PO
{
    class FontData
    {
        TTF_Font* Data;
        operator TTF_Font* () {return Data;}
        friend class FontManager;
    public:
        FontData(TTF_Font* TTF) throw ( ResourceUnavailable ) :Data(TTF){ if(TTF==nullptr) throw ResourceUnavailable("Font");}
        ~FontData() {TTF_CloseFont(Data);}
    };

    typedef std::shared_ptr<FontData> Font;
    class SingleCharStruct
    {
        std::shared_ptr<GraphicTexture> Data;
        int Width;
        friend class FontManager;
        void ForceDelete(){ decltype(Data) Empty;Data=Empty;  }
    public:
        int GetWidth() const {return Width;}
        const std::shared_ptr<GraphicTexture>& GetGraphic() const {return Data;}
        SingleCharStruct(const std::shared_ptr<GraphicTexture>& L,int W):Data(L),Width(W){}
        SingleCharStruct(const GraphicPreTexture& L,int W):Data(new GraphicTexture(L)),Width(W){}
        void Change(const std::shared_ptr<GraphicTexture>& L,int W){Data=L;Width=W;}
        void Change(const std::shared_ptr<SingleCharStruct>& L){Data=L->Data;Width=L->Width;}
    };

    template<template<typename StoreType,typename ...Other> class Tank>
        class DynamicTextData:public Tank<std::shared_ptr<SingleCharStruct> >
        {
            unsigned int WidthOfString;
            friend class FontManager;
        public:
            unsigned int GetWidth() const { return WidthOfString;  }
            DynamicTextData():WidthOfString(0){}
            DynamicTextData(const DynamicTextData& )=delete;
            void clear(){Tank<std::shared_ptr<SingleCharStruct>>::clear();WidthOfString=0;}
        };

    class StaticTextData
    {
        std::shared_ptr<GraphicTexture> ID;
        int Width=0;
        Font UsedFont;
        friend class FontManager;
        void ForceDelete(){ decltype(ID) Empty;ID=Empty;  }
    public:
        const std::shared_ptr<GraphicTexture>& GetGraphic() const {return ID;}
        operator bool ( ) const { return static_cast<bool>(ID);}
        int GetWidth(){return Width;}
        StaticTextData(const std::shared_ptr<GraphicPreTexture>& Tem,int W,Font& F):StaticTextData(*Tem,W,F){}
        StaticTextData(const GraphicPreTexture& Tem,int W,const Font& F):ID(new GraphicTexture(Tem)),Width(W),UsedFont(F){}
    };

    class FontIninter
    {
        static unsigned int InitCount;
    public:
        FontIninter()
        {
            if(InitCount==0)
                TTF_Init();
            ++InitCount;
        }
        ~FontIninter()
        {
            --InitCount;
            if(InitCount==0)
                TTF_Quit();
        }
    };

    class FontManager:public FontIninter
    {
        std::map<wchar_t,std::shared_ptr<SingleCharStruct>> DynamicData;
        std::map<std::wstring,std::weak_ptr<StaticTextData>> StaticData;
        Font DefaultFont;
        static int InitCount;
        static SDL_Color Col;
    public:
        Font CreateFont(const std::string& Ade,int Size)throw ( FontUnavailable );
        void CreateDefaultFont( const std::string& Ade,int Size )throw ( FontUnavailable );

        template<template<typename Type,typename ...O>class  Tank >
            void CreateDynamicText(const std::string& U,DynamicTextData<Tank>& T)throw(  TextUnavailable  ){ CreateDynamicText(DefaultTurnToUnicode(U),T);}
        template<template<typename Type,typename ...O>class  Tank >
            void CreateDynamicText(const std::wstring& U,DynamicTextData<Tank>& T)throw(  TextUnavailable  ){ T.clear();AddDynamicText(U,T); }

        template<template<typename Type,typename ...O>class  Tank >
            void AddDynamicText(const std::string& U,DynamicTextData<Tank>& T)throw(  TextUnavailable  ){ CreateDynamicText(DefaultTurnToUnicode(U),T);}
        template<template<typename Type,typename ...O>class  Tank >
            void AddDynamicText(const std::wstring& U,DynamicTextData<Tank>& T)throw(  TextUnavailable  );

        std::shared_ptr<StaticTextData> CreateStaticText(const std::string& L)throw(  TextUnavailable,ResourceUnavailable  ){return CreateStaticText(L,DefaultFont);}
        std::shared_ptr<StaticTextData> CreateStaticText(const std::wstring& L)throw(  TextUnavailable,ResourceUnavailable  ){return CreateStaticText(L,DefaultFont);}
        std::shared_ptr<StaticTextData> CreateStaticText(const std::string& L,const Font& FI)throw(  TextUnavailable,ResourceUnavailable  ){return CreateStaticText(DefaultTurnToUnicode(L),FI);}
        std::shared_ptr<StaticTextData> CreateStaticText(const std::wstring& L,const Font& FI)throw(  TextUnavailable ,ResourceUnavailable );
        FontManager();
        FontManager(const std::string& L,int Size)throw ( FontUnavailable );
        ~FontManager();
        void PreWindowChange();
        void PosWindowChange(const GraphicInfo&,const GraphicInfo&);
    };


    template<template<typename Ts,typename ...TP> class S>
        void FontManager::AddDynamicText(const std::wstring& U, DynamicTextData<S>& T) throw(  TextUnavailable  )
        {
            for(auto& I:U)
            {
                auto Find=DynamicData.find(I);
                if(Find!=DynamicData.end())
                {
                    shared_ptr<SingleCharStruct> Tem(Find->second);
                    T.push_back(Tem);
                }else{
                    std::wstring Tf;
                    Tf+=I;
                    GraphicPreTexture GPT(TTF_RenderUNICODE_Blended(*DefaultFont,(Uint16*)(Tf.c_str()),FontManager::Col));
                    std::shared_ptr<SingleCharStruct> Tem(new SingleCharStruct(GPT,CountWidth(I)));
                    DynamicData.insert(std::make_pair(I,Tem));
                    T.WidthOfString+=Tem->Width;
                    T.push_back(Tem);
                }
            }
        }

    struct FontModual:public FontManager
    {
        FontModual(const std::string& L,int Size):FontManager(L,Size){}
        FontModual(){}
    };

    typedef std::shared_ptr<FontData> Font;
}
#endif // FONTMANAGER_H_INCLUDED
