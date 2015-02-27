#ifndef WELCOME_H_INCLUDED
#define WELCOME_H_INCLUDED
#include "../po/plugin.h"
#include "../po/pocontext.h"
#include "../po/modual/image/popicture.h"
#include "../po/modual/text/potext.h"
#include "../po/posensitive.h"
#include "../po/figureset.h"
class StageTeach;
class Welcome:public PO::Plugin<PO::Render,PO::ImageManager,PO::FontManager>,public PO::PluginCreater<StageTeach>
{
    PO::Picture P[4];
    //PO::NumberText NT;
    PO::StaticText ST[4];
    unsigned int Step=0;
    PO::Info<PO::VertexInfo,PO::ColorInfo> Screen;
    unsigned int Button[2];
    PO::MouseSensitive MS;
    Vertex<2> MouseL;
    PO::VertexInfo PI;
    bool ShowAdvice=false;
    bool Translation=false;
    bool Exit=false;
    long WaitTime=0;
    bool Showzima=false;
public:
    void Respond(const PO::EventBox& EB,PluAdapter& L);
    Welcome(PluAdapter RP);
    void Layer2D(PluAdapter& RE);
};

#endif // WELCOME_HPP_INCLUDED
