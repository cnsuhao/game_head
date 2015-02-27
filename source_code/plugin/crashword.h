#ifndef CRASHWORD_H_INCLUDED
#define CRASHWORD_H_INCLUDED
#include <vector>
#include "../po/elementfigure.h"
#include "../po/render.h"
#include "../po/figureset.h"
struct CrashPlu
{
    Vertex<2> Location;
    float W;
    float H;
    float R=1.0,G=1.0,B=1.0,A=1.0;
    Normal<2> Speed;
    bool CrashWith(const Vertex<2>& Ve,float W,float H);
};
struct CrashPluInfo:public CrashPlu,public PO::Info<PO::VertexInfo,PO::ColorInfo>
{
    CrashPluInfo(const CrashPlu& Cp):CrashPlu(Cp)
    {
        PO::VerTool::SetRect(*this,Location(0)-W/2.0,Location(1)+H/2.0,W,0.0,0.0,-H);
        PO::ColTool::Paint(*this,R,G,B,A);
    }
    void Move(long T)
    {
        Location+=Speed*(T/1000.0);
        PO::VerTool::Translation(*this,Speed(0)*(T/1000.0),Speed(1)*(T/1000.0),0.0);
    }
    void Draw(PO::Render& R)
    {
        PO::Draw_Color DC(R,*this,*this);
        PO::Draw_Vertex DV(R,*this);
    }
};
struct CrashWord
{
    std::list<CrashPluInfo> CrashPool;
    std::list<CrashPluInfo> CrashHead;
    std::list<CrashPluInfo> CrashWall;
    float SX,EX,SY,EY;
    float SX2,EX2,SY2,EY2;
    bool Active=true;
    bool PreExitFinish=false;
    bool Exit=false;
    bool CrashWallAble=false;
    bool CrashWithPool(const Vertex<2>& Ve,float W,float H);
    bool CrashWithHead(const Vertex<2>& Ve,float W,float H);
    bool CrashWithWall(const Vertex<2>& Ve,float W,float H,float& TX,float& TY);
    bool CrashWithWall2(const Vertex<2>& Ve,float W,float H,float& TX,float& TY,long T);
    bool CrashWithWall2(const Vertex<2>& Ve,float W,float H);
    void SetWall(float X,float X2,float Y,float Y2)
    {
        SX=X;EX=X2;SY=Y;EY=Y2;
    }
    void SetWall2(float X,float X2,float Y,float Y2)
    {
        SX2=X;EX2=X2;SY2=Y;EY2=Y2;
    }
    void PosRender(PO::Render::ModualAdapter& L);
    void Reset()
    {
        CrashPool.clear();
        CrashHead.clear();
        Active=true;
        PreExitFinish=false;
        Exit=false;
    }
};


#endif // CRASHWORD_H_INCLUDED
