#ifndef RENDERFUNCTIONCHECK_H_INCLUDED
#define RENDERFUNCTIONCHECK_H_INCLUDED
namespace PO
{
    class RenderBase;
    template<typename T>
    struct PreRenderFunctionCheck
    {
        template<typename Y,void (Y::*)( RenderBase& ) > struct FunctionLegal;
        template<typename Y> static char Function( FunctionLegal<Y,&Y::PreRender>* );
        template<typename Y> static long Function( ... );
        enum{
            resoult= (sizeof( Function<T>(nullptr) )== sizeof(char))
        };
    };

    template<typename T>
    struct PosRenderFunctionCheck
    {
        template<typename Y,void (Y::*)( RenderBase& ) > struct FunctionLegal;
        template<typename Y> static char Function( FunctionLegal<Y,Y::PosRender>* );
        template<typename Y> static long Function( ... );
        enum{
            resoult= (sizeof( Function<T>(nullptr) )== sizeof(char))
        };
    };
}


#endif // RENDERFUNCTIONCHECK_HPP_INCLUDED
