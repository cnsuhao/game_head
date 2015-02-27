#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include "error/poerror.h"
#include "figureset.h"
//This model store any data that may used about the Texture.
//And any model about texture should include this head file.
namespace PO
{

    /*namespace Pattern{
        namespace Tex{
            void DrawTexture( const TextureFigure& TP,const GraphicTexture& GL);
            void SetEqualRectangle( TextureFigure& TP,const GraphicTexture& GL,float Size,const Vertex<2>& Shift=Ver(0.0,0.0),const Color<4>& Co=Col(1.0,1.0,1.0,1.0));
            inline void Translate( TextureFigure& TP,const Normal<2>& L){Pattern::Fig::Transltae(TP.GLP,L);}
            inline void Reset(TextureFigure& TP,const Vertex<2>& L ){Pattern::Fig::Reset(TP.GLP,L);}
            inline void Reset(TextureFigure& TP,const Color<4>& L ){Pattern::Fig::Reset(TP.GLP,L);}
        }
    }*/



    /*class Texture
    {
        //the define in GL system.
        unsigned int GLPoint;

        //the Real Texture Size.
        unsigned int TextureW;
        unsigned int TextureH;

        //the Space use in GL system.
        unsigned int MemoryW;
        unsigned int MemoryH;

        //Well, as we all know, gl can not store any picture witch 2^n*2^n, so any picture loaded should be changes to2^n*2^n,
        //and changes to normal when displaying.
        static bool CreateTexture(SDL_Surface*,unsigned int& P,unsigned int& W,unsigned int& H,unsigned int & MemoryW,unsigned int & MemoryH);
        static bool CreateTexture(SDL_Surface* K,Texture& P){P.FreeTexture();return CreateTexture(K,P.GLPoint,P.TextureW,P.TextureH,P.MemoryW,P.MemoryH);}
        Texture(const Texture& K)=delete;
    protected:
        void FreeTexture();
        Texture(SDL_Surface* SS)
        {
            if(SS==nullptr)
                throw
        }
        ~Texture(){FreeTexture}
    public:
        void DrawTexture(const float* TxP,const float* LoP,int LSize,const unsigned int* Or,unsigned int M) const ;
        void DrawTexture(const float* TxP,const float* LoP,int LSize,const float* CoP,int CSize,const unsigned int* Or,unsigned int M) const ;
        void DrawTexture(const float* TxP,const float* LoP,int LSize,const float* CoP,int CSize,const float* NoP,const unsigned int* Or,unsigned int M) const ;
        void DrawTexture( const TextureFigure& ) const;

        unsigned int GetPoint() const {return GLPoint;}
        unsigned int GetTextureW() const {return TextureW;}
        unsigned int GetTextureH() const {return TextureH;}
        unsigned int GetMemoryW()const  {return MemoryW;}
        unsigned int GetMemoryH()const  {return MemoryH;}
        float GetRateWH() const {return static_cast<float>(TextureW)/TextureH;}
        float GetRateW()const  {return static_cast<float>(TextureW)/MemoryW;}
        float GetRateH()const  {return static_cast<float>(TextureH)/MemoryH;}
        bool IsAvalible() const {return glIsTexture(GLPoint)==GL_TRUE;}
        static unsigned int Find2Power(unsigned int );
        static std::string TellSurfaceFormat(unsigned int);
    };*/
}
#endif // POGIDATA_H
