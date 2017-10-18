
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
PtrDefine(name##Vector)

#define VectorAndPtrDefine(name) \
VectorAndPtrDefineRename(name, name)