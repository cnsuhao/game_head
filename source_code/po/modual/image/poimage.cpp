#include "poimage.h"
namespace PO
{
    unsigned int ImageManager::InitCount=0;

    void ImageManager::ClearRemain()
    {
        for(auto Po=ImageDataMap.begin();Po!=ImageDataMap.end();++Po)
        {
            if(Po->second.expired())
                ImageDataMap.erase(Po++);
            else Po++;
        }
    }

    ImageManager::~ImageManager()
    {
        for(auto& Po:ImageDataMap)
            if(!Po.second.expired())
                (Po.second.lock())->ForceDelete();
    }

    ImageManager::ImageIndex ImageManager::CreateImage(const std::string& U) throw( PictureUnavailable )
    {
        auto Find=ImageDataMap.find(U);
        if(Find!=ImageDataMap.end()&&!Find->second.expired())
        {
            return Find->second.lock();
        }else{
            GraphicPreTexture GTD(IMG_Load(U.c_str()));
            std::shared_ptr<ImageData> Tem(new ImageData(GTD));
            std::weak_ptr<ImageData> CC(Tem);
            ImageDataMap[U]=CC;
            return Tem;
        }
    }

    void ImageManager::PreWindowChange()
    {
        for(auto L=ImageDataMap.begin();L!=ImageDataMap.end();)
        {
            if(L->second.expired())
                ImageDataMap.erase(L++);
            else{
                std::shared_ptr<ImageData> Tm=L->second.lock();
                Tm->ForceDelete();
                ++L;
            }
        }
    }
    void ImageManager::PosWindowChange(const GraphicInfo& ,const GraphicInfo& )
    {
        for(auto L=ImageDataMap.begin();L!=ImageDataMap.end();++L)
        {
            auto P=L->second.lock();
            GraphicPreTexture Tem(IMG_Load(L->first.c_str()));
            std::shared_ptr<GraphicTexture> GT(  new GraphicTexture(Tem));
            P->Data=GT;
        }
    }
}
