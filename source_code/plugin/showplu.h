#ifndef SHOWPLU_H_INCLUDED
#define SHOWPLU_H_INCLUDED
#include "../po/plugin.h"
#include "crashword.h"
#include "../po/figureset.h"
class ShowPlu:public PO::Plugin<PO::Render,CrashWord>
{
    PO::Info<PO::VertexInfo,PO::ColorInfo> Wall,Wall2;
public:
    ShowPlu(PluAdapter L)
    {
        CrashWord& CW(L);
        PO::VerTool::SetLineLoop(Wall,CW.SX,CW.SY,CW.SX,CW.EY);
        PO::VerTool::AddLineLoop(Wall,CW.EX,CW.EY);
        PO::VerTool::AddLineLoop(Wall,CW.EX,CW.SY);
        PO::ColTool::Paint(Wall,Wall,1.0,1.0,0.2,1.0);
        PO::VerTool::SetLineLoop(Wall2,CW.SX2,CW.SY2,CW.SX2,CW.EY2);
        PO::VerTool::AddLineLoop(Wall2,CW.EX2,CW.EY2);
        PO::VerTool::AddLineLoop(Wall2,CW.EX2,CW.SY2);
        PO::ColTool::Paint(Wall2,1.0,0.5,0.2,1.0);
    }
    void Layer2D(PluAdapter& L)
    {
        CrashWord& CW(L);
        PO::Draw_Color DC(L,Wall,Wall);
        PO::Draw_Vertex DV(L,Wall);
        for(auto& Li:CW.CrashPool)
            Li.Draw(L);
        for(auto& Li:CW.CrashHead)
            Li.Draw(L);
        for(auto& Li:CW.CrashWall)
            Li.Draw(L);
        if(CW.Exit)
            ExitPlugin();
        /*for(auto Li=CW.CrashPool.begin();Li!=CW.CrashPool.end();)
        {
            Li->Draw(L);
            float X=0,Y=0;
            if(!CW.CrashWithWall2(Li->Location,Li->W,Li->H,X,Y)){
               Li->Move(GetIntervalTime(L));
                ++Li;
            }else {CW.CrashPool.erase(Li++);}
        }
        for(auto Li=CW.CrashHead.begin();Li!=CW.CrashHead.end();++Li)
        {
            Li->Draw(L);
            //Normal<2> S=Li->Speed*(GetIntervalTime(L)/1000.0);
            CW.CrashWithWall2(Li->Location,Li->W,Li->H,Li->Speed(0),Li->Speed(1));
            Li->Move(GetIntervalTime(L));
        }*/
    }
};

#endif // SHOWPLU_H_INCLUDED
