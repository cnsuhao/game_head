#include "texture.h"
namespace PO
{
    void Pattern::Tex::DrawTexture( const TextureFigure& TP ,const GraphicTexture& GL)
    {
        if(!TP.TextureCoor.empty())
        {
            Texture2DEnvir TD(GL.GetPoint());
            //glEnable(GL_TEXTURE_2D);
            //glBindTexture(GL_TEXTURE_2D,GL->GetPoint());
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glTexCoordPointer(2,GL_FLOAT,0,&TP.TextureCoor[0]);
            Fig::DrawFigurePattern(TP.GLP);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            //glDisable(GL_TEXTURE_2D);
        }
    }


    void Pattern::Tex::SetEqualRectangle( TextureFigure& TP,const GraphicTexture& GL,float Size,const Vertex<2>& Shift,const Color<4>& Co)
    {
        if(GL.IsAvalible())
        {
            TP.clear();
            Fig::AddRectance2D(
                          TP.GLP,
                          Ver(GL.GetRateWH()/-2.0*Size+Shift(0),Size/2.0+Shift(1)),
                          Nor(GL.GetRateWH()*Size,0.0),
                          Nor(0.0,-1.0*Size),
                          Co);
            TP.TextureCoor.resize( 2*4 );

            TP.TextureCoor[0]=0.0;
            TP.TextureCoor[1]=0.0;

            TP.TextureCoor[2]=GL.GetRateW();
            TP.TextureCoor[3]=0.0;

            TP.TextureCoor[4]=GL.GetRateW();
            TP.TextureCoor[5]=GL.GetRateH();

            TP.TextureCoor[6]=0.0;
            TP.TextureCoor[7]=GL.GetRateH();
        }
    }

    /*std::string Texture::TellSurfaceFormat(unsigned int Fag)
    {
        switch(Fag)
        {
        case SDL_PIXELFORMAT_UNKNOWN:
            return "SDL_PIXELFORMAT_UNKNOWN";
        case SDL_PIXELFORMAT_INDEX1LSB:
            return "SDL_PIXELFORMAT_INDEX1LSB";
        case SDL_PIXELFORMAT_INDEX1MSB:
            return "SDL_PIXELFORMAT_INDEX1MSB";
        case SDL_PIXELFORMAT_INDEX4LSB:
            return "SDL_PIXELFORMAT_INDEX4LSB";
        case SDL_PIXELFORMAT_INDEX4MSB:
            return "SDL_PIXELFORMAT_INDEX4MSB";
        case SDL_PIXELFORMAT_INDEX8:
            return "SDL_PIXELFORMAT_INDEX8";
        case SDL_PIXELFORMAT_RGB332:
            return "SDL_PIXELFORMAT_RGB332";
        case SDL_PIXELFORMAT_RGB444:
            return "SDL_PIXELFORMAT_RGB444";
        case SDL_PIXELFORMAT_RGB555:
            return "SDL_PIXELFORMAT_RGB555";
        case SDL_PIXELFORMAT_BGR555:
            return "SDL_PIXELFORMAT_BGR555";
        case SDL_PIXELFORMAT_ARGB4444:
            return "SDL_PIXELFORMAT_ARGB4444";
        case SDL_PIXELFORMAT_RGBA4444:
            return "SDL_PIXELFORMAT_RGBA4444";
        case SDL_PIXELFORMAT_ABGR4444:
            return "SDL_PIXELFORMAT_ABGR4444";
        case SDL_PIXELFORMAT_BGRA4444:
            return "SDL_PIXELFORMAT_BGRA4444";
        case SDL_PIXELFORMAT_ARGB1555:
            return "SDL_PIXELFORMAT_ARGB1555";
        case SDL_PIXELFORMAT_RGBA5551:
            return "SDL_PIXELFORMAT_RGBA5551";
        case SDL_PIXELFORMAT_ABGR1555:
            return "SDL_PIXELFORMAT_ABGR1555";
        case SDL_PIXELFORMAT_BGRA5551:
            return "SDL_PIXELFORMAT_BGRA5551";
        case SDL_PIXELFORMAT_RGB565:
            return "SDL_PIXELFORMAT_RGB565";
        case SDL_PIXELFORMAT_BGR565:
            return "SDL_PIXELFORMAT_BGR565";
        case SDL_PIXELFORMAT_RGB24:
            return "SDL_PIXELFORMAT_RGB24";
        case SDL_PIXELFORMAT_BGR24:
            return "SDL_PIXELFORMAT_BGR24";
        case SDL_PIXELFORMAT_RGB888:
            return "SDL_PIXELFORMAT_RGB888";
        case SDL_PIXELFORMAT_RGBX8888:
            return "SDL_PIXELFORMAT_RGBX8888";
        case SDL_PIXELFORMAT_BGR888:
            return "SDL_PIXELFORMAT_BGR888";
        case SDL_PIXELFORMAT_BGRX8888:
            return "SDL_PIXELFORMAT_BGRX8888";
        case SDL_PIXELFORMAT_ARGB8888:
            return "SDL_PIXELFORMAT_ARGB8888";
        case SDL_PIXELFORMAT_RGBA8888:
            return "SDL_PIXELFORMAT_RGBA8888";
        case SDL_PIXELFORMAT_ABGR8888:
            return "SDL_PIXELFORMAT_ABGR8888";
        case SDL_PIXELFORMAT_BGRA8888:
            return "SDL_PIXELFORMAT_BGRA8888";
        case SDL_PIXELFORMAT_ARGB2101010:
            return "SDL_PIXELFORMAT_ARGB2101010";
        case SDL_PIXELFORMAT_YV12:
            return "SDL_PIXELFORMAT_YV12";
        case SDL_PIXELFORMAT_IYUV:
            return "SDL_PIXELFORMAT_IYUV";
        case SDL_PIXELFORMAT_YUY2:
            return "SDL_PIXELFORMAT_YUY2";
        case SDL_PIXELFORMAT_UYVY:
            return "SDL_PIXELFORMAT_UYVY";
        case SDL_PIXELFORMAT_YVYU:
            return "SDL_PIXELFORMAT_YVYU";
        }
        std::string Empty;
        return Empty;
    }*/
}
