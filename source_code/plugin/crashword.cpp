#include "crashword.h"
float Abs( float Y ){if(Y<0) return -Y;return Y;}
bool CrashPlu::CrashWith(const Vertex<2>& Ve,float EW,float EH)
{
    if(Abs( Location(0)-Ve(0) )<EW/2.0+W/2.0&&Abs(Location(1)-Ve(1))<EH/2.0+H/2.0)
        return true;
    return false;
}
bool CrashWord::CrashWithPool(const Vertex<2>& Ve,float EW,float EH)
{
    for(auto& L:CrashPool)
        if(L.CrashWith(Ve,EW,EH))
            return true;
    return false;
}
bool CrashWord::CrashWithHead(const Vertex<2>& Ve,float EW,float EH)
{
    for(auto& L:CrashHead)
        if(L.CrashWith(Ve,EW,EH))
            return true;
    return false;
}
bool CrashWord::CrashWithWall(const Vertex<2>& Ve,float EW,float EH,float& TX,float& TY)
{
    bool Crash=false;
    if(Ve(0)-EW+TX<SX||Ve(0)+EW+TX>EX)
    {
        TX=-TX;
        Crash=true;
    }
    if(Ve(1)-EH+TY<SY||Ve(1)+EH+TY>EY)
    {
        TY=-TY;
        Crash=true;
    }
    return Crash;
}

bool CrashWord::CrashWithWall2(const Vertex<2>& Ve,float EW,float EH)
{
    if(Ve(0)-EW<SX2||Ve(0)+EW>EX2||Ve(1)-EH<SY2||Ve(1)+EH>EY2)
        return true;
    return false;

}
bool CrashWord::CrashWithWall2(const Vertex<2>& Ve,float EW,float EH,float& TX,float& TY,long Time)
{
    float SpX=TX*Time/1000.0;
    float SpY=TY*Time/1000.0;
    bool Crash=false;
    if(Ve(0)-EW+SpX<SX2||Ve(0)+EW+SpX>EX2)
    {
        TX=-TX;
        Crash=true;
    }
    if(Ve(1)-EH+SpY<SY2||Ve(1)+EH+SpY>EY2)
    {
        TY=-TY;
        Crash=true;
    }
    return Crash;
}
void CrashWord::PosRender(PO::Render::ModualAdapter& L)
{
    if(Active)
    {
        PO::Render& R(L);
        for(auto Po=CrashPool.begin();Po!=CrashPool.end();)
        {
            if(!CrashWithWall2(Po->Location,Po->W,Po->H))
            {
                Po->Move(R.GetIntervalTime());
                ++Po;
            }else{
                CrashPool.erase(Po++);
            }
        }
        for(auto& Po:CrashHead)
        {
            CrashWithWall2(Po.Location,Po.W,Po.H,Po.Speed(0),Po.Speed(1),R.GetIntervalTime());
            if(Po.Speed(0)>0.0)
                for(auto& I:CrashWall)
                {
                    if(I.CrashWith(Po.Location,Po.W,Po.H))
                        Po.Speed(0)=Po.Speed(0)<0?Po.Speed(0):-Po.Speed(0);
                }
            Po.Move(R.GetIntervalTime());
        }
    }
}
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
