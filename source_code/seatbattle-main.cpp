
#include "plugin/welcome.h"
#include "plugin/allplugin.h"
#include "po/po.h"
using namespace PO;
#include <iostream>
using namespace std;


int main(int Count,char** Arv)
{
    return PO::Loop(cout,
         [](POContext& POC)
         {
             auto Po=CreateGraphicInfo();
             Po->SetTitle("Í·µÄÆæÃîÖ®ÂÃ"_ToUTF8);
             Po->SetWindow(800,600);
             auto Pl=CreateModual<FontManager>("font/fksnjt.ttc",60);
             auto PL=IncludeModual( Pl,CreateModual<ImageManager>() );
             auto PL2=IncludeModual(PL,CreateModual<CrashWord>());
             auto Yi=POC.CreateRender(Po,PL2);
             CreatePlugin<Welcome>(Yi,Yi);
                glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         }
         );
}
