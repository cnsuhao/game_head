#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "../po/plugin.h"
#include "crashword.h"
#include "../po/figureset.h"
#include "../po/modual/image/elfpicture.h"
struct ElfPic_4X4:public PO::ElfPicture
{
    int SX,SY;
    int Direct=0;
    long WaitTime=0;
    void GetIntervalTime(long T)
    {
        WaitTime+=T;
        if(WaitTime>200)
        {
            if(Direct!=0)
            {
                SX+=1;
                if(SX==4) SX=0;
                PO::ElfTool::SetState(*this,SX,SY-1);
            }
            WaitTime=0;
        }
    }
    void GetDirection(int K)
    {
        Direct=K;
        if(Direct!=0)
            SY=K;
        SX=1;
        PO::ElfTool::SetState(*this,SX,SY-1);
    }
    void LoadElf(PO::ImageManager& IM,const std::string& L,float Size){PO::ElfPicture::LoadElf(IM,L,4,4,Size);}
};
struct YouWin:public PO::Plugin<PO::Render,CrashWord,PO::FontManager>,public PO::PluginCreater<Welcome>
{
    PO::Info<PO::VertexInfo,PO::ColorInfo> Screen;
    PO::StaticText ST[2];
    bool Finish=false;
    int Step=0;
    long WaitTime=0;
    YouWin(PluAdapter L)
    {
        PO::VerTool::SetRect(Screen,-2.0,1.0,4.0,0.0,0.0,-2.0);
        PO::ColTool::Paint(Screen,0.0,0.0,0.0,1.0);
        ST[0].CreateStaticText(L,"~您赢了~");
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

struct BAKA9:public PO::Plugin<PO::ImageManager,CrashWord,PO::Render>,public PO::PluginCreater<YouWin>
{
    ElfPic_4X4 EP;
    int Step=0;
    int Step_=0;
    long WaitTime=20000;
    bool Unbeat=false;
    Vertex<2> Loc9;
    Normal<2> Speed;
public:
    BAKA9(PluAdapter L):Loc9(1.2,0.0),Speed(0.0,-1.0)
    {
        EP.LoadElf(L,"image/baka9.jpg",0.3);
        PO::VerTool::Translation(EP,Loc9(0),Loc9(1),0.0);
        EP.GetDirection(1);
    }
    void Layer2D(PluAdapter& L)
    {
        CrashWord& CW(L);
        if(CW.Active)
        {
            EP.GetIntervalTime(GetIntervalTime(L));
            WaitTime+=GetIntervalTime(L);
        }
        if(CW.Exit)
        {
            ExitPlugin();
            return;
        }

        switch(Step)
        {
        case 0:
            if(WaitTime>1000)
            {
                CrashPlu CP;
                CP.H=0.1;CP.W=0.1;CP.Location.Set(1.2,0.0);
                for(int i=0;i<7;++i)
                {
                    CP.Speed=Nor( cos((120+i*(20))/180.0*3.14),sin((120+i*20)/180.0*3.14) );
                    CW.CrashPool.push_back(CP);
                }
                /*CP.Location.Set(1.0,0.0);
                for(int i=0;i<6;++i)
                {
                    CP.Speed=Nor( cos((120+i*(24))/180.0*3.14),sin((120+i*24)/180.0*3.14) );
                    CW.CrashPool.push_back(CP);
                }*/
                WaitTime=0;
            }
            break;
        case 1:
            switch(Step_)
            {
            case 0:
                if(!Unbeat)
                {
                    Step_+=1;
                    WaitTime=2000;
                }
                break;
            case 1:
                if(WaitTime>1500)
                {
                    CrashPlu CP;
                    CP.H=0.1;
                    CP.W=0.1;
                    CP.Location=Loc9;
                    for(int i=0; i<7; ++i)
                    {
                        CP.Speed=Nor( cos((120+i*(20))/180.0*3.14),sin((120+i*20)/180.0*3.14) );
                        CW.CrashPool.push_back(CP);
                    }
                    WaitTime=0;
                }
                if(CW.Active)
                {
                    CW.CrashWithWall2(Loc9,0.2,0.2,Speed(0),Speed(1),GetIntervalTime(L));
                    Normal<2> Tem=Speed*(GetIntervalTime(L)/1000.0);
                    PO::VerTool::Translation(EP,Tem(0),Tem(1),0.0);
                    Loc9+=Tem;
                }
                break;
            }
            break;
        case 2:
            switch(Step_)
            {
            case 0:
                if(!Unbeat)
                {
                    Step_+=1;
                    WaitTime=2000;
                }
                break;
            case 1:
                if(WaitTime>1000)
                {
                    CrashPlu CP;
                    CP.H=0.1;
                    CP.W=0.1;
                    CP.Location=Loc9;
                    for(int i=0; i<7; ++i)
                    {
                        CP.Speed=Nor( cos((120+i*(20))/180.0*3.14),sin((120+i*20)/180.0*3.14) );
                        CW.CrashPool.push_back(CP);
                    }
                    CP.Location=Loc9+Nor(-0.2,0.0);
                    for(int i=0; i<6; ++i)
                    {
                        CP.Speed=Nor( cos((120+i*(24))/180.0*3.14),sin((120+i*24)/180.0*3.14) );
                        CW.CrashPool.push_back(CP);
                    }
                    WaitTime=0;
                }
                if(CW.Active)
                {
                    CW.CrashWithWall2(Loc9,0.15,0.15,Speed(0),Speed(1),GetIntervalTime(L));
                    Normal<2> Tem=Speed*(GetIntervalTime(L)/1000.0);
                    PO::VerTool::Translation(EP,Tem(0),Tem(1),0.0);
                    Loc9+=Tem;
                }
                break;
            }
            break;
            case 3:
                switch(Step_)
                {
                case 0:
                    if(!Unbeat)
                    {
                        Step_+=1;
                        WaitTime=2000;
                    }
                    break;
                case 1:{
                    CW.CrashWall.clear();
                    CrashPlu CP;
                    CP.Location.Set(0.8,0.7);
                    CP.R=0.3;CP.G=1.0;CP.B=0.3;CP.A=1.0;
                    CP.W=0.1;CP.H=0.3;
                    CW.CrashWall.push_back(CP);
                    CP.Location.Set(0.8,0.0);
                    CW.CrashWall.push_back(CP);
                    CP.Location.Set(0.8,-0.7);
                    CW.CrashWall.push_back(CP);
                    Step_+=1;
                    break;
                }
                case 2:
                    if(WaitTime>1000)
                    {
                        CrashPlu CP;
                        CP.H=0.1;
                        CP.W=0.1;
                        CP.Location=Loc9;
                        for(int i=0; i<7; ++i)
                        {
                            CP.Speed=Nor( cos((120+i*(20))/180.0*3.14),sin((120+i*20)/180.0*3.14) );
                            CW.CrashPool.push_back(CP);
                        }
                        CP.Location=Loc9+Nor(-0.2,0.0);
                        for(int i=0; i<6; ++i)
                        {
                            CP.Speed=Nor( cos((120+i*(24))/180.0*3.14),sin((120+i*24)/180.0*3.14) );
                            CW.CrashPool.push_back(CP);
                        }
                        WaitTime=0;
                    }
                    if(CW.Active)
                    {
                        CW.CrashWithWall2(Loc9,0.15,0.15,Speed(0),Speed(1),GetIntervalTime(L));
                        Normal<2> Tem=Speed*(GetIntervalTime(L)/1000.0);
                        PO::VerTool::Translation(EP,Tem(0),Tem(1),0.0);
                        Loc9+=Tem;
                    }
                    break;
                }
                break;
            case 4:
                CW.Active=false;
                CreatePlugin<YouWin>(L);
                Step++;
                break;
        }
        if(!Unbeat||(Unbeat&&WaitTime%200<99))
            EP.DrawElf(L);
        if(CW.CrashWithHead(Loc9,EP.GetRateWH()*0.2,0.2)&&!Unbeat)
        {
            Step+=1;
            Step_=0;
            Unbeat=true;
            WaitTime=0;
        }
        if(Unbeat)
            if(WaitTime>4000)
            {
                Unbeat=false;
                WaitTime=0;
            }
    }
};


#endif // PLAYER_H_INCLUDED
