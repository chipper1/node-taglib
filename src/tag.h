#ifndef NODE_TAGLIB_TAG_H
#define NODE_TAGLIB_TAG_H

#include <fileref.h>
#include <tag.h>
#include <node.h>
#include <sys/time.h>

namespace node_taglib {
class Tag : public node::ObjectWrap {
  TagLib::Tag * tag;
  TagLib::FileRef * fileRef;
  static TagLib::String NodeStringToTagLibString( v8::Local<v8::Value> s);
  static v8::Handle<v8::Value> TagLibStringToString( TagLib::String s );

  //static v8::Persistent<v8::FunctionTemplate> pft;

    public:
    static void Initialize(v8::Handle<v8::Object> target);
    Tag(TagLib::FileRef * fileRef);
    ~Tag();

    static v8::Handle<v8::Value> GetTitle(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetTitle(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetArtist(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetArtist(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetAlbum(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetAlbum(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetYear(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetYear(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetComment(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetComment(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetTrack(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetTrack(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> GetGenre(v8::Local<v8::String> property, const v8::AccessorInfo& info);
    static void SetGenre(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::AccessorInfo& info);

    static v8::Handle<v8::Value> IsEmpty(const v8::Arguments &args);
    static v8::Handle<v8::Value> SyncSaveTag(const v8::Arguments &args);
    static v8::Handle<v8::Value> SyncTag(const v8::Arguments &args);
    static v8::Handle<v8::Value> AsyncTag(const v8::Arguments &args);
    static void AsyncTagRead(uv_work_t *req);
    static void AsyncTagReadAfter(uv_work_t *req);

    static v8::Handle<v8::Value> Dispose(const v8::Arguments &args);
};

struct AsyncTagBaton {
    uv_work_t request;
    TagLib::FileName path;
    Tag *tag;
    v8::Persistent<v8::Function> callback;
    int error;
    suseconds_t startTime;
};


int CreateFileRef(TagLib::FileName path, TagLib::FileRef **ref);
v8::Handle<v8::String> ErrorToString(int error);
}
#endif
