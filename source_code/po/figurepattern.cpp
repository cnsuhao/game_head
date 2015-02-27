#include "figurepattern.h"
namespace PO
{
namespace Pattern
{
namespace Fig
{
void DrawFigurePattern( const FigurePattern& GP )
{
    if(!GP.DrawOrder.empty())
    {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(GP.VectorSize,GL_FLOAT,0,&GP.Vector[0]);
        if(!GP.Color.empty())
        {
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(4,GL_FLOAT,0,&GP.Color[0]);
        }
        if(!GP.Normal.empty())
        {
            glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT,0,&GP.Normal[0]);
        }
        glDrawElements(GP.DrawType,GP.DrawOrder.size(),GL_UNSIGNED_INT,&GP.DrawOrder[0]);
        if(!GP.Color.empty()) glDisableClientState(GL_COLOR_ARRAY);
        if(!GP.Normal.empty()) glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

void AddLine(FigurePattern& GP,const Vertex<2>& Start,const Vertex<2>& End, const Color<4>& C)
{
    if(GP.DrawType!=GL_LINES&&GP.VectorSize!=2)
    {
        GP.clear();
        GP.DrawType=GL_LINES;
        GP.VectorSize=2;
        GP.VectorCenter.resize(2);
    }

    GP.VectorCenter[0]=(Start(0)+End(0))/2.0;
    GP.VectorCenter[1]=(Start(1)+End(1))/2.0;

    size_t Sta=GP.Color.size();
    GP.Color.resize( Sta+8 );
    for(size_t i=Sta; i<Sta+8; i+=4)
        for(int k=0; k<4; ++k)
            GP.Color[i+k]=C(k);

    Sta=GP.Vector.size();
    GP.Vector.resize( Sta+2*2 );

    for(size_t k=0; k<2; ++k)
        GP.Vector[Sta+k]=Start(k);
    for(size_t k=0; k<2; ++k)
        GP.Vector[Sta+2+k]=End(k);

    Sta=GP.Color.size()/4;
    GP.DrawOrder.push_back(Sta-2);
    GP.DrawOrder.push_back(Sta-1);
    GP.MaxDraw=Sta;
}

void AddRectance2D( FigurePattern& GP ,const Vertex<2>& PC, const Normal<2>& T, const Normal<2>& D,const Color<4>& C)
{
    if(GP.DrawType!=GL_TRIANGLES&&GP.VectorSize!=2)
    {
        GP.clear();
        GP.DrawType=GL_TRIANGLES;
        GP.VectorSize=2;
        GP.VectorCenter.resize(2);
    }

    GP.VectorCenter[0]=PC(0)+T(0)/2+D(0)/2;
    GP.VectorCenter[1]=PC(1)+T(1)/2+D(1)/2;

    size_t Size=GP.Color.size();
    GP.Color.resize( Size+16 );
    for(size_t i=Size; i<Size+16; i+=4)
        for(int k=0; k<4; ++k)
            GP.Color[i+k]=C(k);
    Size=GP.Normal.size();
    GP.Normal.resize( Size+4*3  );
    for(int i=0; i<12; i+=4)
    {
        if(i%3==2)
            GP.Normal[Size+i]=-1.0;
        else GP.Normal[Size+i]=0.0;
    }
    Size=GP.Vector.size();
    GP.Vector.resize( Size+2*4 );

    for(int i=0; i<2; ++i)
        GP.Vector[Size+i] = PC(i);

    for(int i=0; i<2; ++i)
        GP.Vector[Size+2+i] = PC(i)+T(i);

    for(int i=0; i<2; ++i)
        GP.Vector[Size+4+i] = PC(i)+T(i)+D(i);
    for(int i=0; i<2; ++i)
        GP.Vector[Size+6+i] = PC(i)+D(i);

    Size=GP.DrawOrder.size();
    GP.DrawOrder.resize(Size+6);

    GP.DrawOrder[Size]=( GP.MaxDraw );
    GP.DrawOrder[Size+1]=( GP.MaxDraw+2 );
    GP.DrawOrder[Size+2]=( GP.MaxDraw+1 );

    GP.DrawOrder[Size+3]=( GP.MaxDraw );
    GP.DrawOrder[Size+4]=( GP.MaxDraw+3 );
    GP.DrawOrder[Size+5]=( GP.MaxDraw+2 );
    GP.MaxDraw+=4;
}

void Transltae(FigurePattern& GP,const Normal<2>& PL)
{
    if(GP.VectorSize==2)
    {
        size_t Size=GP.Vector.size()/2;
        for(size_t i=0;i<Size;++i)
        {
            GP.Vector[i*2]+=PL(0);
            GP.Vector[i*2+1]+=PL(1);
        }
    }
}

void Reset(FigurePattern& PL,const Vertex<2>& L)
{
    if(PL.VectorSize==2)
    {
        size_t Size=PL.Vector.size()/2;
        for(size_t i=0;i<Size;++i)
        {
            PL.Vector[i*2]=PL.Vector[i*2]-PL.VectorCenter[0]+L(0);
            PL.Vector[i*2+1]=PL.Vector[i*2+1]-PL.VectorCenter[1]+L(1);
        }
        PL.VectorCenter[0]=L(0);
        PL.VectorCenter[1]=L(1);
    }
}

void Reset(FigurePattern& PL,const Color<4>& L)
{
    size_t o=PL.Color.size()/4;
    for(size_t i=0;i<o;++i)
        for(int k=0;k<4;++k)
            PL.Color[i*4+k]=L(k);
}
}
}
}
