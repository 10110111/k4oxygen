#ifndef OXYGNE_TYPE_HELPER_20160608
#define OXYGNE_TYPE_HELPER_20160608

namespace Oxygen
{

#define DECLARE_ENUM(Class,Enum) template<> struct EnumIsDeclared<Class::Enum>{ static const bool value=true; typedef Class EnclosingClass; };
template<typename T> struct EnumIsDeclared { static const bool value=false; };

template<bool B, class T=void> struct enable_if{};
template<class T>              struct enable_if<true,T> { typedef T type; };

}

#endif
