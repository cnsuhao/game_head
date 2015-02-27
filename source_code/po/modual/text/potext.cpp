#include "potext.h"
using namespace std;
namespace PO
{
    //std::wstringstream NumberText::WSS;
    /*namespace Pattern{
        namespace Fon{
        void SetRectangle2D(StaticText& ST,float Size,const Vertex<2>& Sh,const Color<4>& Co)
        {
            Pattern::Tex::SetEqualRectangle(ST.STP,*ST.GetData()->GetGraphic(),Size,Sh,Co);
        }
        void Rectangle2D(DynamicTextFigure& ST,std::shared_ptr<SingleCharStruct>& Te,float Size,Vertex<2> Sh,Color<4> Co)
        {
            auto Tem=Te->GetGraphic();
            if(ST.RenderedWidth==0)
            {
                ST.clear();
                ST.TP.GLP.DrawOrder.resize(6);
                ST.TP.GLP.DrawOrder[0]=0;
                ST.TP.GLP.DrawOrder[1]=1;
                ST.TP.GLP.DrawOrder[2]=2;
                ST.TP.GLP.DrawOrder[3]=0;
                ST.TP.GLP.DrawOrder[4]=2;
                ST.TP.GLP.DrawOrder[5]=3;

                ST.TP.GLP.DrawType=GL_TRIANGLES;
                ST.TP.GLP.VectorSize=2;

                ST.TP.GLP.Color.resize( 16 );
                for(int i=0; i<4; i+=1)
                    for(int k=0; k<4; ++k)
                        ST.TP.GLP.Color[i*4+k]=Co(k);

                ST.TP.GLP.Normal.resize( 4*3  );
                for(int i=0; i<12; i+=4)
                {
                    if(i%3==2)
                        ST.TP.GLP.Normal[i]=-1.0;
                    else ST.TP.GLP.Normal[i]=0.0;
                }
                ST.TP.GLP.Vector.resize( 2*4 );
                ST.TP.GLP.Vector[1]=Sh(1);
                ST.TP.GLP.Vector[3]=Sh(1);
                ST.TP.GLP.Vector[5]=Sh(1)-Size;
                ST.TP.GLP.Vector[7]=Sh(1)-Size;

                ST.TP.TextureCoor.resize( 2*4 );

                ST.TP.TextureCoor[0]=0.0;
                ST.TP.TextureCoor[1]=0.0;
                ST.TP.TextureCoor[3]=0.0;
                ST.TP.TextureCoor[6]=0.0;
            }
            int Width=Te->GetWidth();
            ST.TP.TextureCoor[2]=Tem->GetRateW();
            ST.TP.TextureCoor[4]=Tem->GetRateW();
            ST.TP.TextureCoor[5]=Tem->GetRateH();
            ST.TP.TextureCoor[7]=Tem->GetRateH();

            ST.TP.GLP.Vector[0]=Sh(0)+ST.RenderedWidth*Size*0.5;
            ST.TP.GLP.Vector[2]=Sh(0)+(ST.RenderedWidth+Width)*Size*0.5;
            ST.TP.GLP.Vector[4]=ST.TP.GLP.Vector[2];
            ST.TP.GLP.Vector[6]=ST.TP.GLP.Vector[0];
        }
        }
    }*/
}
