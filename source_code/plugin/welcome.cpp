#include "welcome.h"
/*
PO::Picture P;
PO::NumberText NT;
PO::StaticText ST[4];
unsigned int Step=0;
PO::FigurePattern FP;
unsigned int Button[2];
PO::MouseSensitive MS;
Vertex<2> MouseL;
*/
using namespace PO;
void Welcome::Respond(const PO::EventBox& EB,PluAdapter& L)
{
    if(!Translation&&!Exit)
    {
        for(auto& E:EB.GetMouseBox())
        {
                GetMouseLocation(L,MouseL,E);
                if(E->IsMouseButtonUp()&&E->IsMouseButtonLeft())
                {
                    if(MouseL(0)>-1.0&&MouseL(0)<-0.5&&MouseL(1)<0.8&&MouseL(1)>0.0)
                        Translation=true;
                    if(MS.SingleRespond(MouseL,Button[1]))
                        Exit=true;
                }
        }
        if(MS.SingleRespond(MouseL,Button[0]))
        {
            Vertex<2> P;
            MS.GetLocation(Button[0],P);
            auto I=P-MouseL;
            if(I(0)>0.2) I(0)-=0.2; else if(I(0)<-0.2) I(0)+=0.2;
            if(I(1)>0.1) I(1)-=0.1; else if(I(1)<-0.1) I(1)+=0.1;
            P+=I;
            MS.Change(Button[0],P);
            VerTool::Translation(ST[0],I(0),I(1),0.0);
            GetScreen2D(L,I(0),I(1));
            if(P(0)-0.2<-I(0)||P(0)+0.2>I(0)||P(1)-0.1<-I(1)||P(1)+0.1>I(1))
                ShowAdvice=true;
        }
    }
}
Welcome::Welcome(PluAdapter RP)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    P[0].Create(RP,"image/background/back-1.jpg");
    P[1].Create(RP,"image/wel-1.jpg");
    P[2].Create(RP,"image/wel-2.jpg");
    TexTool::TexRotEqu(P[0],P[0],P[0],0.0,0.0,2.0);
    ColTool::Paint(P[0],P[0],1.0,1.0,1.0,1.0);
    TexTool::TexRotEqu(P[1],P[1],P[1],0.8,-0.4,0.5);
    ColTool::Paint(P[1],P[1],1.0,1.0,1.0,1.0);
    TexTool::TexRotEqu(P[2],P[2],P[2],0.0,0.0,2.0);
    ColTool::Paint(P[2],P[2],1.0,1.0,1.0,1.0);


    VerTool::SetRect(Screen,-1.0,1.0,2.0,0.0,0.0,-2.0);
    ColTool::Paint(Screen,Screen,0.0,0.0,0.0,0.0);
    PI.Pick(ST[0]);
    //PO::Pattern::Pic::SetEqualRectangle(P[0],2.0);
    float X,Y;
    GetScreen2D(RP,X,Y);
    //Pattern::Fig::AddRectance2D(FP,Ver(-X,Y),Nor(2*X,0.0),Nor(0.0,-2*Y),Col(0.0,0.0,0.0,0.0));
    //PO::Pattern::Pic::SetEqualRectangle(P[1],0.5,Ver(0.8,-0.5));
    ST[0].CreateStaticText(RP,"开始游戏");
    ST[1].CreateStaticText(RP,"离开游戏");
    ST[2].CreateStaticText(RP,"点我的脸啦~BAKA");

    VerTool::SetRect(Screen,-2.0,1.0,4.0,0.0,0.0,-2.0);
    ColTool::Paint(Screen,Screen,0.0,0.0,0.0,0.0);

    TexTool::TexRotEqu(ST[0],ST[0],ST[0],0.0,0.0,0.2);
    ColTool::Paint(ST[0],ST[0],0.8,0.4,0.4,1.0);

    TexTool::TexRotEqu(ST[1],ST[1],ST[1],0.0,0.0,0.1);
    ColTool::Paint(ST[1],ST[1],0.8,0.4,0.4,1.0);

    TexTool::TexRotEqu(ST[2],ST[2],ST[2],0.0,0.0,0.1);
    ColTool::Paint(ST[2],ST[2],0.8,0.4,0.4,1.0);

    VerTool::Translation(ST[0],0.0,-0.3,0.0);
    VerTool::Translation(ST[1],0.0,-0.5,0.0);
    VerTool::Translation(ST[2],0.8,-0.8,0.0);

    MS.Insert( Button[0],0.0,-0.3,[&](float X,float Y)->bool
                                        {
                                            float XP=ST[0].GetWidth()/4*0.2;
                                            float YP=0.1;
                                            if( X>-XP&&X<XP&&Y>-YP&&Y<YP )return true;
                                            else return false;
                                        }
            );
    MS.Insert( Button[1],0.0,-0.5,[&](float X,float Y)->bool
                                        {
                                            float XP=ST[1].GetWidth()/4*0.1;
                                            float YP=0.05;
                                            if( X>-XP&&X<XP&&Y>-YP&&Y<YP )return true;
                                            else return false;
                                        }
            );

}
void Welcome::Layer2D(PluAdapter& RE)
{

    P[0].DrawPicture(RE);
    for(int i=0;i<2;++i)
    {
        ST[i].DrawText(RE);

    }


    //if(ShowAdvice) {P[1].DrawPicture();ST[2].DrawText();}
    //NT.Connect(RE,MouseL(0));
    //NT.DrawNumber(PO::Pattern::Fon::Rectangle2D,0.1f,MouseL,Col(1.0,1.0,1.0,1.0));
    //NT.Connect(RE,MouseL(1));
    //NT.DrawNumber(PO::Pattern::Fon::Rectangle2D,0.1f,MouseL+Nor(0.0,0.1),Col(1.0,1.0,1.0,1.0));

    //ST[0].DrawText();
    //ST[1].DrawText();

    if(ShowAdvice) {ST[2].DrawText(RE);P[1].DrawPicture(RE);}
            Draw_Color DC(RE,Screen,Screen);
    Draw_Vertex DV(RE,Screen);
    if(Translation)
    {
        WaitTime+=GetIntervalTime(RE);
        ColTool::Cover(Screen,WaitTime/1000.0);
        if(WaitTime>=1200)
        {
            ExitPlugin();
            CreatePlugin<StageTeach>(RE);
        }
    }else if(Exit)
    {
        int Y,L;
        GetWindowSize(RE,Y,L);
        float X,K;
        GetScreen2D(RE,X,K);
        if(L==400)
        {
            WaitTime+=GetIntervalTime(RE);
            if(!Showzima)
            {
                //P[3].Create(RE,"image/wel-2.jpg");
                //Pattern::Pic::SetEqualRectangle(P[3],2.0);
                Showzima=true;
            }
            if(Showzima){
                P[2].DrawPicture(RE);
            }
            if(WaitTime>2000)
                ExitRender(RE);
        }else{
            if(L<400) L=400;
            else if(L>400){L-=GetIntervalTime(RE);if(L<400) L=400;}
            ResetWindowSize(RE,Y,L);
            SetScreen2D(RE,X,1.0);
        }
    }

}

