#ifndef FUNCTIONDETECT_H_INCLUDED
#define FUNCTIONDETECT_H_INCLUDED

#define MEMBER_FUNCTION_DETECTOR(Pre,FunName,ReturnType, ParaNameList  , ... )  \
    struct FUNCTION_DETECTOR_STRCUT##Pre##FunName{ \
        template<typename L , ReturnType (L::*)( __VA_ARGS__ ) > struct Plu{}; \
        template<typename SS> static char Fun_Detect(  Plu<SS,&SS:: FunName >* ); \
        template<typename SS> static long Fun_Detect(  ... ); \
        template<bool,typename __PO__GivingType> struct RunStruct{\
            static ReturnType FunName(__PO__GivingType& __PO__PreGivingTypeName,##__VA_ARGS__ ){  return __PO__PreGivingTypeName . FunName ParaNameList ;  }\
        };\
        template<typename __PO__GivingType> struct RunStruct<false,__PO__GivingType>{\
            static ReturnType FunName(__PO__GivingType& __PO__PreGivingTypeName , ##__VA_ARGS__ ) {  };\
        };\
    };

#define MEMBER_FUNCTION_DETECT_RESOULT(Pre,FunName,Type) (sizeof( FUNCTION_DETECTOR_STRCUT##Pre##FunName::Fun_Detect<Type>(nullptr)) == sizeof(char))
#define MEMBER_FUNCTION_PROCESS(Pre,FunName,Type,...) \
    FUNCTION_DETECTOR_STRCUT##Pre##FunName::RunStruct<MEMBER_FUNCTION_DETECT_RESOULT(Pre,FunName,Type),Type>::FunName(__VA_ARGS__)
#endif // FUNCTIONDETECT_H_INCLUDED
