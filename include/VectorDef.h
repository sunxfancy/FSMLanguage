
#define PtrDefineRename(name, base) \
typedef base* name##P

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
VectorDefine(name##P); \
PtrDefine(name##PVector)


#define VectorAndPtrDefine(name) \
VectorAndPtrDefineRename(name, name)
