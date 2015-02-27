#ifndef IMAGE_H
#define IMAGE_H
#include <map>
#include <string>
#include <SDL2/SDL_image.h>
#include "../../texture.h"
#include "../../error/poerror.h"
#include "../../render.h"
namespace PO
{
    class ImageManager
    {
        class ImageData
        {
            std::shared_ptr<GraphicTexture> Data;
            void ForceDelete(){decltype(Data) Tem;Data=Tem;}
            friend class ImageManager;
        public:
            operator const GraphicTexture& (){return *Data;}
            const std::shared_ptr<GraphicTexture> GetGraphic() const {return Data;}
            ImageData(const std::shared_ptr<GraphicPreTexture>& SH):Data( new GraphicTexture(*SH)){}
            ImageData(const GraphicPreTexture& GTD):Data(new GraphicTexture(GTD)){}
        };

        std::map<std::string,std::weak_ptr<ImageData> > ImageDataMap;
        static unsigned int InitCount;
    public:
        typedef std::shared_ptr<ImageData> ImageIndex;
        ImageIndex CreateImage(const std::string& U ) throw(PictureUnavailable);
        void PreWindowChange();
        void PosWindowChange(const GraphicInfo& ,const GraphicInfo& );

        ImageManager() {if(InitCount==0)IMG_Init(~0);++InitCount;}
        ~ImageManager();
        void ClearRemain();
    };

    typedef ImageManager ImageModual;
}
#endif // TEXTUREMANAGER_H
