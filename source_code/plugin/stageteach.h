#ifndef STAGETEACH_H_INCLUDED
#define STAGETEACH_H_INCLUDED
#include "../po/plugin.h"
#include "../po/modual/image/popicture.h"
#include "../po/modual/text/potext.h"
#include "../po/modual/image/elfpicture.h"
#include "crashword.h"
class ShowPlu;
class BAKA9;
class StageTeach;
class Welcome;
struct ElfPic_3X4:public PO::ElfPicture
{
    int SX,SY;
    int Traget=1;
    int Direct=0;
    long WaitTime=0;
    void GetIntervalTime(long T);
    void GetDirection(int);
    void LoadElf(PO::ImageManager& IM,const std::string& L,float Size){PO::ElfPicture::LoadElf(IM,L,3,4,Size);}
};

struct Screen1:public PO::Plugin<PO::FontManager,PO::Render,CrashWord>,public PO::PluginCreater<Welcome>
{
    PO::Info<PO::VertexInfo,PO::ColorInfo> Screen;
    PO::StaticText ST[2];
    bool Finish=false;
    int Step=0;
    long WaitTime=0;
    Screen1(PluAdapter L)
    {
        PO::VerTool::SetRect(Screen,-2.0,1.0,4.0,0.0,0.0,-2.0);
        PO::ColTool::Paint(Screen,0.0,0.0,0.0,1.0);
        ST[0].CreateStaticText(L,"~您已经死了~");
        ST[1].CreateStaticText(L,"按任意键返回主界面");
        PO::TexTool::TexRotEqu(ST[0],ST[0],0.0,0.2,0.1);
        PO::TexTool::TexRotEqu(ST[1],ST[1],0.0,0.0,0.1);
        PO::ColTool::Paint(ST[0],1.0,0.3,0.2,1.0);
        PO::ColTool::Paint(ST[1],1.0,0.3,0.2,1.0);
        //ST[0].DrawText(L);
        //ST[1].DrawText(L);
    }
    void Respond(const PO::EventBox& EB,PluAdapter& L)
    {
        WaitTime+=GetIntervalTime(L);
        if(Step==2)
            for(auto& Lo:EB.GetKeyBox())
            {
                if(Lo->IsKeyButtonUp())
                {
                    CrashWord& CW(L);
                    CW.Exit=true;
                    CreatePlugin<Welcome>(L);
                    ExitPlugin();
                    return ;
                }
            }
    }
    void Layer2D(PluAdapter& L)
    {
        if(Step==0)
        {
            if(WaitTime<1000)
                PO::ColTool::Cover(Screen,WaitTime/1250.0);
            else{
                PO::ColTool::Cover(Screen,0.8);
                Step+=1;
                WaitTime=0;
            }
            PO::Draw_Color DC(L,Screen,Screen);
            PO::Draw_Vertex DV(L,Screen);
        }else if(Step==1)
        {
            if(WaitTime<2000)
            {
                PO::ColTool::Cover(ST[0],WaitTime/2000.0);
                PO::ColTool::Cover(ST[1],WaitTime/2000.0);
            }else{
                PO::ColTool::Cover(ST[0],1.0);
                PO::ColTool::Cover(ST[1],1.0);
                Step+=1;
                WaitTime=0;
            }
            PO::Draw_Color DC(L,Screen,Screen);
            PO::Draw_Vertex DV(L,Screen);
            ST[0].DrawText(L);
            ST[1].DrawText(L);
        }else if(Step==2)
        {
            PO::Draw_Color DC(L,Screen,Screen);
            PO::Draw_Vertex DV(L,Screen);
            ST[0].DrawText(L);
            ST[1].DrawText(L);
        }
    }
};


struct StageTeach:public PO::Plugin<PO::ImageManager,PO::FontManager,PO::Render,CrashWord>,
                    public PO::PluginCreater<ShowPlu,BAKA9,Screen1>
{
    PO::StaticText ST[10];
    ElfPic_3X4 EF[2];
    long WaitTime=0;
    unsigned int Step=0;
    Vertex<2> PlaLoc;
    PO::Info<PO::VertexInfo,PO::ColorInfo> Screen;
    PO::Info<PO::VertexInfo,PO::ColorInfo> TargetLine;
    float TargetAngle;
    int Live=5;
    bool HoldHand=true;
    bool Unbeatable=false;
    bool Button[6];
    StageTeach(PluAdapter L );
    void Layer2D(PluAdapter& L);
    void Respond(const PO::EventBox& EB,PluAdapter& O);
    unsigned int PreScriptionWindow(PluAdapter& L,unsigned int& MaxStep);
};


#endif // STAGETEACH_H_INCLUDED
