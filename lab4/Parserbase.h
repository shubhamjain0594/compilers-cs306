// Generated by Bisonc++ V4.05.00 on Sat, 28 Mar 2015 19:18:08 +0530

#ifndef ParserBase_h_included
#define ParserBase_h_included

#include <exception>
#include <vector>
#include <iostream>

// $insert preincludes
#include "headers.cc"
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace // anonymous
{
    struct PI__;
}


// $insert polymorphic
enum class Tag__
{
    DEC_STR,
    EXP_LIST,
    ABST,
    TYPE_FLOAT,
    TYPE_INT,
    ARRAY,
    STMT_LIST,
    TYPE_STRING,
    EXP,
    STMT,
};

namespace Meta__
{
    template <Tag__ tag>
    struct TypeOfBase;

    template <typename Tp_>
    struct TagOf;

// $insert polymorphicSpecializations
    template <>
    struct TagOf<decl_struct *>
    {
        static Tag__ const tag = Tag__::DEC_STR;
    };

    template <>
    struct TagOf<exp_node_list*>
    {
        static Tag__ const tag = Tag__::EXP_LIST;
    };

    template <>
    struct TagOf<abstract_astnode*>
    {
        static Tag__ const tag = Tag__::ABST;
    };

    template <>
    struct TagOf<float*>
    {
        static Tag__ const tag = Tag__::TYPE_FLOAT;
    };

    template <>
    struct TagOf<int*>
    {
        static Tag__ const tag = Tag__::TYPE_INT;
    };

    template <>
    struct TagOf<array_ref_node*>
    {
        static Tag__ const tag = Tag__::ARRAY;
    };

    template <>
    struct TagOf<stmt_node_list*>
    {
        static Tag__ const tag = Tag__::STMT_LIST;
    };

    template <>
    struct TagOf<string>
    {
        static Tag__ const tag = Tag__::TYPE_STRING;
    };

    template <>
    struct TagOf<exp_node*>
    {
        static Tag__ const tag = Tag__::EXP;
    };

    template <>
    struct TagOf<stmt_node*>
    {
        static Tag__ const tag = Tag__::STMT;
    };

    template <>
    struct TypeOfBase<Tag__::DEC_STR>
    {
        typedef decl_struct * DataType;
    };

    template <>
    struct TypeOfBase<Tag__::EXP_LIST>
    {
        typedef exp_node_list* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::ABST>
    {
        typedef abstract_astnode* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::TYPE_FLOAT>
    {
        typedef float* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::TYPE_INT>
    {
        typedef int* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::ARRAY>
    {
        typedef array_ref_node* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::STMT_LIST>
    {
        typedef stmt_node_list* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::TYPE_STRING>
    {
        typedef string DataType;
    };

    template <>
    struct TypeOfBase<Tag__::EXP>
    {
        typedef exp_node* DataType;
    };

    template <>
    struct TypeOfBase<Tag__::STMT>
    {
        typedef stmt_node* DataType;
    };


        // determining the nature of a polymorphic semantic value:
        // if it's a class-type, use 'Type const &' as returntype of const
        // functions; if it's a built-in type (like 'int') use Type:

    struct ClassType
    {
        char _[2];
    };
    
    struct BuiltinType
    {
        char _;
    };

    template <typename T>
    BuiltinType test(...);

    template <typename T>
    ClassType test(void (T::*)());

    template <Tag__ tg_>
    struct TypeOf: public TypeOfBase<tg_>
    {
        typedef typename TypeOfBase<tg_>::DataType DataType;
        enum: bool 
        { 
            isBuiltinType = sizeof(test<DataType>(0)) == sizeof(BuiltinType)
        };

        typedef typename std::conditional<
                    isBuiltinType, DataType, DataType const &
                >::type ReturnType;
    };

        // The Base class: 
        // Individual semantic value classes are derived from this class.
        // This class offers a member returning the value's Tag__
        // and two member templates get() offering const/non-const access to
        // the actual semantic value type.
    class Base
    {
        Tag__ d_tag;
    
        protected:
            Base(Tag__ tag);

        public:
            Base(Base const &other) = delete;
            virtual ~Base();

            Tag__ tag() const;
    
            template <Tag__ tg_>
            typename TypeOf<tg_>::ReturnType get() const;
    
            template <Tag__ tg_>
            typename TypeOf<tg_>::DataType &get();
    };
    
        // The class Semantic is derived from Base. It stores a particular
        // semantic value type. The stored data are declared 'mutable' to
        // allow the definitions of a const and non-const conversion operator.
        // This way, const objects continue to offer non-modifiable data
    template <Tag__ tg_>
    class Semantic: public Base
    {
        typedef typename TypeOf<tg_>::DataType DataType;
    
        mutable DataType d_data;
    
        public:
            typedef typename TypeOf<tg_>::ReturnType ReturnType;
    
                // The default constructor and constructors for 
                // defined data types are available
            Semantic();
            Semantic(DataType const &data);
            Semantic(DataType &&tmp);

                // Conversion operators allow const/non-const access to d_data
            operator ReturnType() const;
            operator DataType &();
    };

        // The class Stype wraps the shared_ptr holding a pointer to Base.
        // It becomes the polymorphic STYPE__
        // Constructors expect (l/r-value) references to defined semantic
        // value types.
        // It also wraps Base's get members, allowing constructions like
        // $$.get<INT> to be used, rather than $$->get<INT>.
        // Furthermore, its operator= can be used to assign a Semantic *
        // directly to the SType object. The free functions (in the parser's
        // namespace (if defined)) semantic__ can be used to obtain a 
        // Semantic *. 
    class SType: public std::shared_ptr<Base>
    {
        public:
            SType() = default;
            SType(SType const &other) = default;
            SType(SType &&tmp) = default;
        
            SType &operator=(SType const &rhs) = default;
            SType &operator=(SType &&tmp) = default;
            template <typename Tp_>
            SType &operator=(Tp_ &&value);

            Tag__ tag() const;

                // this get()-member checks for 0-pointer and correct tag 
                // in shared_ptr<Base>, and may throw a logic_error
            template <Tag__ tg_>                    
            typename TypeOf<tg_>::ReturnType get() const;
    
                // this get()-member checks for 0-pointer and correct tag 
                // in shared_ptr<Base>, and resets the shared_ptr's Base * 
                // to point to Meta::__Semantic<tg_>() if not
            template <Tag__ tg_>
            typename TypeOf<tg_>::DataType &get();

                // the data()-members do not check, and may result in a 
                // bad_cast exception or segfault if used incorrectly

            template <Tag__ tg_>
            typename TypeOf<tg_>::ReturnType data() const;

            template <Tag__ tg_>
            typename TypeOf<tg_>::DataType &data();
    };

}  // namespace Meta__

class ParserBase
{
    public:
// $insert tokens

    // Symbolic tokens:
    enum Tokens__
    {
        IDENTIFIER = 277,
        INT_CONSTANT,
        STRING_LITERAL,
        FLOAT_CONSTANT,
        VOID = 282,
        INT,
        FLOAT,
        AND_OP = 286,
        OR_OP,
        EQ_OP,
        NE_OP,
        LE_OP,
        GE_OP,
        IF,
        ELSE,
        WHILE,
        FOR,
        RETURN,
        INC_OP,
    };

// $insert STYPE
    typedef Meta__::SType STYPE__;
	public: static STYPE__  d_val__;


    private:
        int d_stackIdx__;
        std::vector<size_t>   d_stateStack__;
        std::vector<STYPE__>  d_valueStack__;

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            DEFAULT_RECOVERY_MODE__,
            UNEXPECTED_TOKEN__,
        };
        bool        d_debug__;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        int         d_token__;
        int         d_nextToken__;
        size_t      d_state__;
        STYPE__    *d_vsp__;
        STYPE__     d_nextVal__;

        ParserBase();

        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        void clearin();
        bool debug() const;
        void pop__(size_t count = 1);
        void push__(size_t nextState);
        void popToken__();
        void pushToken__(int token);
        void reduce__(PI__ const &productionInfo);
        void errorVerbose__();
        size_t top__() const;

    public:
        void setDebug(bool mode);
}; 

inline bool ParserBase::debug() const
{
    return d_debug__;
}

inline void ParserBase::setDebug(bool mode)
{
    d_debug__ = mode;
}

inline void ParserBase::ABORT() const
{
    throw PARSE_ABORT__;
}

inline void ParserBase::ACCEPT() const
{
    throw PARSE_ACCEPT__;
}

inline void ParserBase::ERROR() const
{
    throw UNEXPECTED_TOKEN__;
}

// $insert polymorphicInline
namespace Meta__
{

inline Base::Base(Tag__ tag)
:
    d_tag(tag)
{}

inline Tag__ Base::tag() const
{
    return d_tag;
}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic()
:
    Base(tg_),
    d_data(typename TypeOf<tg_>::DataType())
{}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic(typename TypeOf<tg_>::DataType const &data)
:
    Base(tg_),
    d_data(data)
{}

template <Tag__ tg_>
inline Semantic<tg_>::Semantic(typename TypeOf<tg_>::DataType &&tmp)
:
    Base(tg_),
    d_data(std::move(tmp))
{}

template <Tag__ tg_>
inline Semantic<tg_>::operator ReturnType() const
{
    return d_data;
}

template <Tag__ tg_>
inline Semantic<tg_>::operator typename Semantic<tg_>::DataType &()
{
    return d_data;
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::ReturnType Base::get() const
{
    return dynamic_cast<Semantic<tg_> const &>(*this);
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::DataType &Base::get()
{
    return dynamic_cast<Semantic<tg_> &>(*this);
}

inline Tag__ SType::tag() const
{
    return std::shared_ptr<Base>::get()->tag();
}
    
template <Tag__ tg_>
inline typename TypeOf<tg_>::ReturnType SType::get() const
{
    if (std::shared_ptr<Base>::get() == 0  || tag() != tg_)
        throw std::logic_error("undefined semantic value requested");

    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::DataType &SType::get()
{
                    // if we're not yet holding a (tg_) value, initialize to 
                    // a Semantic<tg_> holding a default value
    if (std::shared_ptr<Base>::get() == 0 || tag() != tg_)
        reset(new Semantic<tg_>());

    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::ReturnType SType::data() const
{
    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <Tag__ tg_>
inline typename TypeOf<tg_>::DataType &SType::data()
{
    return std::shared_ptr<Base>::get()->get<tg_>();
}

template <bool, typename Tp_>
struct Assign;

template <typename Tp_>
struct Assign<true, Tp_>
{
    static SType &assign(SType *lhs, Tp_ &&tp);
};

template <typename Tp_>
struct Assign<false, Tp_>
{
    static SType &assign(SType *lhs, Tp_ const &tp);
};

template <>
struct Assign<false, SType>
{
    static SType &assign(SType *lhs, SType const &tp);
};

template <typename Tp_>
inline SType &Assign<true, Tp_>::assign(SType *lhs, Tp_ &&tp)
{
    lhs->reset(new Semantic<TagOf<Tp_>::tag>(std::move(tp)));
    return *lhs;
}

template <typename Tp_>
inline SType &Assign<false, Tp_>::assign(SType *lhs, Tp_ const &tp)
{
    lhs->reset(new Semantic<TagOf<Tp_>::tag>(tp));
    return *lhs;
}

inline SType &Assign<false, SType>::assign(SType *lhs, SType const &tp)
{
    return lhs->operator=(tp);
}

template <typename Tp_>
inline SType &SType::operator=(Tp_ &&rhs) 
{
    return Assign<
                std::is_rvalue_reference<Tp_ &&>::value, 
                typename std::remove_reference<Tp_>::type
           >::assign(this, std::forward<Tp_>(rhs));
}

} // namespace Meta__

// As a convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define Parser ParserBase


#endif


