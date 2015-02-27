#include <gl/gl.h>
#include "figureset.h"
namespace PO
{
    VertexInfo& VertexInfo::Pick ( const VertexInfo& VI)
    {
        DrawType=VI.DrawType;
        DrawOrder=VI.DrawOrder;
        Dimensional=VI.Dimensional;
        Vertex=VI.Vertex;
        MaxOrder=VI.MaxOrder;
        return *this;
    }
    TexCoorInfo& TexCoorInfo::operator= (const TexCoorInfo& TC)
    {
        size_t Size=TC.TexCoor.size()/2;
        if(Size>0)
        {
            TexCoor.resize(Size*2);
            for(size_t I=0;I<Size;I)
            {
                TexCoor[I*2]=TC.TexCoor[I*2]/TC.RateW*RateW;
                TexCoor[I*2+1]=TC.TexCoor[I*2]/TC.RateH*RateH;
            }
        }
        return *this;
    }
    Draw_Vertex::Draw_Vertex(Render& R,const VertexInfo& VI):Ready(R.Ver_Arr_En)
    {
        if(VI.Avalible())
        {
            if(!Ready)
            {
                glEnableClientState(GL_VERTEX_ARRAY);
                Ready=true;
            }
            glVertexPointer(VI.Dimensional,GL_FLOAT,0,&VI.Vertex[0]);
            glDrawElements(VI.DrawType,VI.DrawOrder.size(),GL_UNSIGNED_INT,&VI.DrawOrder[0]);
        }else if(Ready)
        {
            glDisableClientState(GL_VERTEX_ARRAY);
            Ready=false;
        }
    }
    Draw_Vertex::~Draw_Vertex()
    {
        if(Ready)
        {
            glDisableClientState(GL_VERTEX_ARRAY);
            Ready=false;
        }
    }

    Draw_Color::Draw_Color(Render& R,const VertexInfo& VI,const ColorInfo& GI):Ready(R.Col_Arr_En)
    {
        if(GI==VI)
        {
            if(!Ready)
            {
                glEnableClientState(GL_COLOR_ARRAY);
                Ready=true;
            }
            glColorPointer(GI.Dimensional,GL_FLOAT,0,&GI.Color[0]);
        }else if(Ready)
        {
            glEnableClientState(GL_COLOR_ARRAY);
            Ready=false;
        }
    }

    Draw_Color::~Draw_Color()
    {
        if(Ready)
        {
            glDisableClientState(GL_COLOR_ARRAY);
            Ready=false;
        }
    }

    Draw_Normal::Draw_Normal(Render& R,const VertexInfo& VI,const NormalInfo& NI):Ready(R.Nor_Arr_En)
    {
        if(NI==VI)
        {
            if(!Ready)
            {
                glEnableClientState(GL_NORMAL_ARRAY);
                Ready=true;
            }
            glNormalPointer(GL_FLOAT,0,&NI.Normal[0]);
        }else if(Ready)
        {
            glDisableClientState(GL_NORMAL_ARRAY);
            Ready=false;
        }
    }

    Draw_Normal::~Draw_Normal()
    {
        if(Ready)
        {
            glDisableClientState(GL_NORMAL_ARRAY);
            Ready=false;
        }
    }

    Draw_TexCoor::Draw_TexCoor(Render& R,const VertexInfo& VI,const TexCoorInfo& TI):Ready(R.Tex_Coo_Arr_En)
    {
        if(TI==VI)
        {
            if(!Ready)
            {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                Ready=true;
            }
            glTexCoordPointer(2,GL_FLOAT,0,&TI.TexCoor[0]);
        }else if(Ready)
        {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            Ready=false;
        }
    }

    Draw_TexCoor::~Draw_TexCoor()
    {
        if(Ready)
        {
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            Ready=false;
        }
    }

    namespace VerTool
    {
        void Translation(VertexInfo& VI,float X,float Y,float Z)
        {
            if(!VI.Vertex.empty())
            {
                size_t Tem=VI.Vertex.size()/2;
                if(VI.Dimensional==2)
                {
                    for(size_t i=0;i<Tem;++i)
                    {
                        VI.Vertex[i*2]+=X;
                        VI.Vertex[i*2+1]+=Y;
                    }
                }else if(VI.Dimensional==3)
                {
                    for(size_t i=0;i<Tem;++i)
                    {
                        VI.Vertex[i*3]+=X;
                        VI.Vertex[i*3+1]+=Y;
                        VI.Vertex[i*3+2]+=Z;
                    }
                }
            }
        }

        void SetRect(VertexInfo& VI,float SX,float SY,float WX,float WY,float HX,float HY)
        {
            VI.Dimensional=2;
            VI.Vertex.resize(8);
            VI.DrawOrder.resize(6);
            VI.DrawType=GL_TRIANGLES;
            VI.MaxOrder=4;
            VI.Vertex[0]=SX;VI.Vertex[1]=SY;VI.Vertex[2]=SX+WX;VI.Vertex[3]=SY+WY;
            VI.Vertex[4]=SX+WX+HX;VI.Vertex[5]=SY+WY+HY;VI.Vertex[6]=SX+HX;VI.Vertex[7]=SY+HY;
            VI.DrawOrder[0]=0;VI.DrawOrder[1]=1;VI.DrawOrder[2]=2;
            VI.DrawOrder[3]=0;VI.DrawOrder[4]=2;VI.DrawOrder[5]=3;
        }
        void SetLine(VertexInfo& VI,float SX,float SY,float EX,float EY)
        {
            VI.Dimensional=2;
            VI.Vertex.resize(4);
            VI.DrawOrder.resize(2);
            VI.DrawType=GL_LINES;
            VI.MaxOrder=2;
            VI.Vertex[0]=SX;VI.Vertex[1]=SY;VI.Vertex[2]=EX;VI.Vertex[3]=EY;
            VI.DrawOrder[0]=0;VI.DrawOrder[1]=1;
        }
        void AddLine(VertexInfo& VI,float SX,float SY,float EX,float EY)
        {
            if(VI.DrawType==GL_LINES&&VI.Dimensional==2)
            {
                size_t i=VI.Vertex.size();
                VI.Vertex.resize( i+4 );
                VI.Vertex[i]=SX;VI.Vertex[i+1]=SY;VI.Vertex[i+2]=EX;VI.Vertex[i+3]=EY;
                size_t Y=VI.DrawOrder.size();
                VI.DrawOrder.resize(Y+2);
                VI.DrawOrder[Y]=i/2;VI.DrawOrder[Y+1]=i/2+1;
            }else SetLine(VI,SX,SY,EX,EY);
        }

        void SetLineLoop(VertexInfo& VI,float SX,float SY,float EX,float EY)
        {
            VI.Dimensional=2;
            VI.Vertex.resize(4);
            VI.DrawOrder.resize(2);
            VI.DrawType=GL_LINE_LOOP;
            VI.MaxOrder=2;
            VI.Vertex[0]=SX;VI.Vertex[1]=SY;VI.Vertex[2]=EX;VI.Vertex[3]=EY;
            VI.DrawOrder[0]=0;VI.DrawOrder[1]=1;
        }

        void AddLineLoop(VertexInfo& VI,float X,float Y)
        {
            if(VI.DrawType==GL_LINE_LOOP&&VI.Dimensional==2)
            {
                size_t i=VI.Vertex.size();
                VI.Vertex.resize( i+2 );
                VI.Vertex[i]=X;VI.Vertex[i+1]=Y;
                VI.DrawOrder.push_back(i/2);
            }
        }
    }
    namespace ColTool
    {
        void Paint(VertexInfo& VI,ColorInfo& CI,float R,float G,float B)
        {
            size_t Io=VI.Vertex.size()/VI.Dimensional;
            CI.Dimensional=3;
            CI.Color.resize(Io*3);
            for(size_t i=0;i<Io;++i)
                CI.Color[i*3]=R;
            for(size_t i=0;i<Io;++i)
                CI.Color[i*3+1]=G;
            for(size_t i=0;i<Io;++i)
                CI.Color[i*3+1]=B;
        }
        void Paint(VertexInfo& VI,ColorInfo& CI,float R,float G,float B,float A)
        {
            size_t Io=VI.Vertex.size()/VI.Dimensional;
            CI.Dimensional=4;
            CI.Color.resize(Io*4);
            for(size_t i=0;i<Io;++i)
                CI.Color[i*4]=R;
            for(size_t i=0;i<Io;++i)
                CI.Color[i*4+1]=G;
            for(size_t i=0;i<Io;++i)
                CI.Color[i*4+2]=B;
            for(size_t i=0;i<Io;++i)
                CI.Color[i*4+3]=A;
        }
        void Cover(ColorInfo& CI,float A)
        {
            if(CI.Dimensional==4)
            {
                size_t Si=CI.Color.size()/4;
                if(Si>0)
                {
                    for(size_t i=0;i<Si;++i)
                        CI.Color[i*4+3]=A;
                }
            }
        }
    }
    namespace NorTool
    {
        void EqualNormal(VertexInfo&,ColorInfo&,float X,float Y,float Z){}
    }
    namespace TexTool
    {
        void VerRotEqu2D(VertexInfo& VI,TexCoorInfo& TI,float Rotate,float SX,float SY)
        {
            if(VI.Dimensional==2)
            {
                size_t Size=VI.Vertex.size()/VI.Dimensional;
                if(Size>0)
                {
                    TI.TexCoor.resize(VI.Vertex.size());
                    float XC=VI.Vertex[0],YC=VI.Vertex[1];
                    TI.TexCoor[0]=SX;TI.TexCoor[1]=SY;
                    for(size_t i=1;i<Size;++i)
                    {
                        TI.TexCoor[i*2]=VI.Vertex[i*2]-XC+SX;
                        TI.TexCoor[i*2+1]=VI.Vertex[i*2+1]-YC+SY;
                    }
                }
            }
        }

        void TexRotEqu(VertexInfo& VI,TexCoorInfo& TI,const GraphicTexture& GT,float SX,float SY,float Size)
        {
            TI.TexCoor.resize(8);
            TI.TexCoor[0]=0.0;TI.TexCoor[1]=0.0;TI.TexCoor[2]=GT.GetRateW();TI.TexCoor[3]=0.0;
            TI.TexCoor[4]=GT.GetRateW();TI.TexCoor[5]=GT.GetRateH();TI.TexCoor[6]=0.0;TI.TexCoor[7]=GT.GetRateH();
            VerTool::SetRect(VI,SX-Size*GT.GetRateWH()/2.0,SY+Size/2.0,Size*GT.GetRateWH(),0.0,0.0,-Size);
        }
    }
}
