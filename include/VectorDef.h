
#define PtrDefineRename(name, base) \
typedef std::unique_ptr<base> name##UP; \
typedef std::shared_ptr<base> name##SP

#define PtrDefine(name) \
PtrDefineRename(name, name)

#define VectorDefineRename(name, base) \
typedef std::vector<base> name##Vector

#define VectorDefine(name) \
VectorDefineRename(name, name)

#define VectorAndPtrDefineRename(name, base) \
VectorDefineRename(name, base); \
PtrDefineRename(name, base); \
PtrDefine(name##Vector); \
VectorDefine(name##UP); \
VectorDefine(name##SP); \
PtrDefine(name##UPVector); \
PtrDefine(name##SPVector)


#define VectorAndPtrDefine(name) \
VectorAndPtrDefineRename(name, name)


template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
static_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    auto d = static_cast<Derived *>(p.release());
    return std::unique_ptr<Derived, Del>(d, std::move(p.get_deleter()));
}

template<typename Derived, typename Base, typename Del>
std::unique_ptr<Derived, Del> 
dynamic_unique_ptr_cast( std::unique_ptr<Base, Del>&& p )
{
    if(Derived *result = dynamic_cast<Derived *>(p.get())) {
        p.release();
        return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
    }
    return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
}