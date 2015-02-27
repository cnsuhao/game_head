#include "stageteach.h"
using namespace std;
using namespace PO;
std::string Title[]={
                    "(..按回车键跳过开场说明..)",
                    "赤头蛮在妖精之湖上遇到了BAKA9",
                    "BAKA9似乎有点不对劲，二话不说，对着赤头蛮放起了弹幕",
                    "赤头蛮也不甘示弱，但她想使用弹幕的时候，",
                    "却发现她的弹幕被别人封印了。",
                    "“YO~，看来是异变了~”",
                    "赤头蛮扔出了头，“来战吧！”",
                    "这其实就是个打砖块+躲弹幕的游戏。。。",
                    "wasd行走，空格扔头",
                    "躲避白色方块，扔出红色方块攻击BAKA9",
                    "当人物闪烁时，表示受到攻击，此时会无敌一段时间",
                    "~游戏愉快~"};
const int TitileCount=11;
void ElfPic_3X4::GetIntervalTime(long T)
{
    WaitTime+=T;
    if(WaitTime>200)
    {
        if(Direct!=0)
        {
            SX+=Traget;
            if(SX==2) Traget=-1;
            else if(SX==0) Traget=1;
            ElfTool::SetState(*this,SX,SY-1);
        }
        WaitTime=0;
    }
}
void ElfPic_3X4::GetDirection(int K)
{
    Direct=K;
    if(Direct!=0)
        SY=K;
    SX=1;
    ElfTool::SetState(*this,SX,SY-1);
}
StageTeach::StageTeach(PluAdapter L)
{
    CrashWord& CW(L);
    CW.Reset();
    for(int i=0;i<4;++i)
        Button[i]=false;
    //Step=3*TitileCount;
    float SX,SY;
    GetScreen2D(L,SX,SY);
    CW.SetWall(-SX+0.01,SX-0.8,-SY+0.01,SY-0.01);
    CW.SetWall2(-SX,SX,-SY,SY);
    //CW.SX=-SX+0.01;CW.EX=SX-0.4;CW.SY=-SY+0.01;CW.EY=SY-0.01;
}
void StageTeach::Layer2D(PluAdapter& L)
{
    CrashWord& CW(L);
    if(true)
    {
        if(Step>=0&&Step<3*TitileCount)
        {
            int D=Step%3;
            switch(D)
            {
            case 0:
                ST[0].CreateStaticText(L,Title[Step/3]);
                TexTool::TexRotEqu(ST[0],ST[0],ST[0],0.0,0.2,0.1);
                ColTool::Paint(ST[0],ST[0],1.0,1.0,1.0,0.0);
                WaitTime=0;
                Step+=1;
                ST[0].DrawText(L);
                break;
            case 1:
                if(WaitTime<500)
                    ColTool::Cover(ST[0],WaitTime/500.0);
                else
                {
                    ColTool::Cover(ST[0],1.0);
                    WaitTime=0;
                    Step+=1;
                }
                ST[0].DrawText(L);
                break;
            case 2:
                if(WaitTime>3000)
                {
                    WaitTime=0;
                    Step+=1;
                }
                ST[0].DrawText(L);
                break;
            case 3:
                if(WaitTime<500)
                    ColTool::Cover(ST[0],1.0-WaitTime/500.0);
                else
                {
                    ColTool::Cover(ST[0],0.0);
                    WaitTime=0;
                    Step+=1;
                }
                ST[0].DrawText(L);
            }
        }
        else if(Step==3*TitileCount)
        {
            EF[0].LoadElf(L,"image/sekibanki.png",0.15);
            EF[0].DrawElf(L);
            VerTool::SetLine(TargetLine,0.0,0.0,0.0,0.0);
            ColTool::Paint(TargetLine,1.0,0.0,0.0,1.0);
            CreatePlugin<BAKA9>(L);
            CreatePlugin<ShowPlu>(L);
            Step+=1;
        }
        else if(Step==3*TitileCount+1)
        {
            EF[0].GetIntervalTime(GetIntervalTime(L));
            if(!Unbeatable||(  Unbeatable&&(WaitTime%200<99)   ))
                EF[0].DrawElf(L);
            if(HoldHand)
            {
                float A=sin(TargetAngle);
                PO::VerTool::SetLine(TargetLine,PlaLoc(0),PlaLoc(1),PlaLoc(0)+(A<0?-A:A)*0.2,PlaLoc(1)+(cos(TargetAngle))*0.2);
                PO::Draw_Color DC(L,TargetLine,TargetLine);
                Draw_Vertex DV(L,TargetLine);
            }
        }
    }
}
void StageTeach::Respond(const EventBox& EB,PluAdapter& L)
{
    CrashWord& CW(L);
    WaitTime+=GetIntervalTime(L);
    if(Step>=3*TitileCount+1&&CW.Active)
    {
        int& Dir=EF[0].Direct;
        for(auto& L:EB.GetKeyBox())
        {
            if(L->IsKey('w')) Button[3]=L->IsKeyButtonDown();
            else if(L->IsKey('d')) Button[2]=L->IsKeyButtonDown();
            else if(L->IsKey('a')) Button[1]=L->IsKeyButtonDown();
            else if(L->IsKey('s')) Button[0]=L->IsKeyButtonDown();
            else if(L->IsKey('r')) Button[4]=L->IsKeyButtonDown();
            else if(L->IsKey('f')) Button[5]=L->IsKeyButtonDown();
            else if(L->IsKeySpace())
            {
                if(L->IsKeyButtonUp())
                    if(HoldHand)
                    {
                        CrashPlu CP;
                        float A=sin(TargetAngle);
                        CP.Location=PlaLoc+Nor( A>0?(A*0.2):(-A*0.2),cos(TargetAngle)*0.2  );
                        CP.Speed=Nor( A>0?A:-A,cos(TargetAngle) );
                        CP.R=0.8;CP.G=0.1;CP.B=0.2,CP.A=1.0;
                        CP.W=0.1;CP.H=0.1;
                        CW.CrashHead.push_back(CP);
                        HoldHand=false;
                    }
            }
            if(L->IsKeyButtonUp()&&Step==3*TitileCount+5)
            {
                ExitPlugin();
                return ;
            }
        }
        if(Dir!=0&&(!Button[Dir-1]))
        {
            for(int i=0;i<4;++i)
                if(Button[i])
                {
                    EF[0].GetDirection(i+1);
                    break;
                }else if(i==3)
                    EF[0].GetDirection(0);
        }else if(Dir==0)
        {
            for(int i=0;i<4;++i)
                if(Button[i])
                {
                    EF[0].GetDirection(i+1);
                    break;
                }
        }else if(Dir!=0)
        {
            Normal<2> N;
            switch(Dir)
            {
            case 1:
                N=Nor(0.0,-1.0*GetIntervalTime(L)/1000.0);
                break;
            case 2:
                N=Nor(-1.0*GetIntervalTime(L)/1000.0,0.0);
                break;
            case 3:
                N=Nor(1.0*GetIntervalTime(L)/1000.0,0.0);
                break;
            case 4:
                N=Nor(0.0,1.0*GetIntervalTime(L)/1000.0);
                break;
            }
            CrashWord& CW(L);
            if(!CW.CrashWithWall(PlaLoc,EF[0].GetRateWH()*0.075,0.075,N(0),N(1)))
            {
                VerTool::Translation(EF[0],N(0),N(1),0.0);
                PlaLoc+=N;
            }
            if(CW.CrashWithHead(PlaLoc,EF[0].GetRateWH()*0.01,0.04))
            {
                HoldHand=true;
                CW.CrashHead.clear();
            }
        }
        if(!Unbeatable)
        {
            if(CW.CrashWithPool(PlaLoc,EF[0].GetRateWH()*0.01,0.05))
            {
                Live-=1;
                if(Live==0)
                {
                    CW.Active=false;
                    CreatePlugin<Screen1>(L);
                }else{
                    Unbeatable=true;
                    WaitTime=0;
                }
            }
        }else if( WaitTime>2000  )
        {
            Unbeatable=false;
        }
        if(HoldHand)        TargetAngle+=GetIntervalTime(L)*0.0007;
    }else if(Step<3*TitileCount)
    {
        for(auto &I:EB.GetKeyBox())
        {
            if(I->IsKeyButtonUp()&&I->IsKeyEnter())
                Step=3*TitileCount;
        }
    }
    if(CW.Exit)
        ExitPlugin();
}

/*void StageTeach::PreScriptionWindow(PluAdapter& L,unsigned int& Max)
{

}*/
