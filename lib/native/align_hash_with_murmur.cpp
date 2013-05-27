#include <ruby.h>

#include "ulib/hash_func.h"
#include "ulib/hash_align.h"
#include "ulib/math_rand_prot.h"

#include "smhasher/MurmurHash3.cpp"

using namespace ulib;

#define GetCallbackStruct(obj)	(Check_Type(obj, T_DATA), (RCallback*)DATA_PTR(obj))

#define hash_key_struct uint32_t
#define hash_struct align_hash_map<hash_key_struct, VALUE*>

typedef struct {
    hash_struct *hash_map;
} RCallback;

extern "C" {
    static hash_key_struct
    key_hash(VALUE *value) {
        hash_key_struct result;
        MurmurHash3_x86_32(RSTRING_PTR(&value), RSTRING_LEN(&value), 0123, &result);
        return result;
    }

    static void
    mark_hash_map_values(RCallback *incoming) {
            for(hash_struct::iterator it = incoming->hash_map->begin(); it != incoming->hash_map->end(); ++it) {
                rb_gc_mark(it.key());
                rb_gc_mark(*it.value());
            }
    }

    static void
    free_hash_callback(RCallback* cb) {
        delete cb->hash_map;
    }
    
    static VALUE
    callback_alloc( VALUE klass )
    {
        RCallback* cbs;
        VALUE current_instance = Data_Make_Struct(klass, RCallback, mark_hash_map_values, free_hash_callback, cbs);
        cbs->hash_map = new hash_struct();
        return current_instance;
    }
        
    static VALUE
    rb_ah_hash_set(VALUE cb, VALUE set_this, VALUE to_this) {
        RCallback* cbs = GetCallbackStruct(cb);
        cbs->hash_map->insert(key_hash(&set_this), &to_this, true);
        return to_this;
    }
    
    static VALUE
    rb_ah_hash_get_value(VALUE cb, VALUE get_this) {
        RCallback* cbs = GetCallbackStruct(cb);
        uint32_t hash = key_hash(&get_this);
        if (cbs->hash_map->contain(hash)) {
            return *cbs->hash_map->find(hash).value();
        } else {
            return Qnil;
        }
    }
    
    static VALUE rb_ah_hash_size(VALUE cb) {
        RCallback* cbs = GetCallbackStruct(cb);
        return INT2FIX(cbs->hash_map->size());
    }
    
    void
    Init_align_hash_with_murmur(void) {
        VALUE klass = rb_define_class("AlignHashWithMurmur", rb_cObject);
    
        rb_define_alloc_func(klass, callback_alloc);
        rb_define_method(klass, "[]=", RUBY_METHOD_FUNC(rb_ah_hash_set), 2);
        rb_define_method(klass, "[]", RUBY_METHOD_FUNC(rb_ah_hash_get_value), 1);
        rb_define_method(klass, "size", RUBY_METHOD_FUNC(rb_ah_hash_size), 0);
        rb_define_method(klass, "length", RUBY_METHOD_FUNC(rb_ah_hash_size), 0);
    }
}