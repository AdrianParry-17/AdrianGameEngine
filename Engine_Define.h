#ifndef __ENGINE_DEFINE_H__
#define __ENGINE_DEFINE_H__

#define ENGINE_ABS(x) (((x) < 0) ? (-(x)) : (x))

#define ENGINE_MIN(a, b) (((b) < (a)) ? (b) : (a))
#define ENGINE_MAX(a, b) (((b) > (a)) ? (b) : (a))

#define ENGINE_CLAMP(a, b, x) (((b) < (a)) ? (((x) < (b)) ? (b) : (((x) > (a)) ? (a) : (x))) : (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x))))
// This only work if a <= b. It's recommend to use ENGINE_CLAMP for safer.
#define ENGINE_FAST_CLAMP(a, b, x) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

// Call this inside a class (in public scope) with the class type to make it not copyable via copy constuction.
#define ENGINE_NOT_COPYABLE(Type) Type(const Type&)=delete;Type(Type&&)=delete;
// Call this inside a class (in public scope) with the class type to make it not assignable via assign operator '='.
#define ENGINE_NOT_ASSIGNABLE(Type) void operator=(const Type&)=delete;void operator=(Type&&)=delete;

#define ENGINE_DEFINE_ENUM_OPERATORS(Type) inline Type operator~ (Type a) { return (Type)(~(unsigned long long)a); } \
    inline Type operator| (Type a, Type b) { return (Type)((unsigned long long)a | (unsigned long long)b); } \
    inline Type operator& (Type a, Type b) { return (Type)((unsigned long long)a & (unsigned long long)b); } \
    inline Type operator^ (Type a, Type b) { return (Type)((unsigned long long)a ^ (unsigned long long)b); } \
    inline Type& operator|= (Type& a, Type b) { return (Type&)((unsigned long long&)a |= (unsigned long long)b); } \
    inline Type& operator&= (Type& a, Type b) { return (Type&)((unsigned long long&)a &= (unsigned long long)b); } \
    inline Type& operator^= (Type& a, Type b) { return (Type&)((unsigned long long&)a ^= (unsigned long long)b); }


#endif // __ENGINE_DEFINE_H__