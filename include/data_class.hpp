// Copyright (c) 2014 David Turnbull AE9RB
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef MRUBY_DATA_CLASS_HPP
#define MRUBY_DATA_CLASS_HPP

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/class.h"
#include <type_traits>

// Hook up a C++ class to mruby memory model

template <class T>
struct DataClass {

    void *
    operator new(size_t size, mrb_state *mrb, mrb_value &v)
    {
        DataClass *t = (DataClass*)DATA_PTR(v);
        if (t) destroy_hook(mrb, t);
        void *ptr = mrb_malloc(mrb, size);
        DATA_TYPE(v) = &data_type;
        DATA_PTR(v) = ptr;
        return ptr;
    }

    virtual void destroy(mrb_state *mrb) {};
    virtual ~DataClass() {};

    // Prevent accidental use of delete(obj).
    void
    operator delete(void* ptr)
    {
        mrb_assert(false);
    }

private:

    static struct mrb_data_type data_type;

    static void
    destroy_hook(mrb_state *mrb, void* ptr)
    {
        DataClass *obj = reinterpret_cast<DataClass*>(ptr);
        obj->destroy(mrb);
        obj->~DataClass();
        mrb_free(mrb, obj);
    }

};

template <class T>
struct mrb_data_type DataClass<T>::data_type = {
    T::struct_name, DataClass<T>::destroy_hook
};

// DataClass method
#define DCmethod(klass, method) \
[](mrb_state *mrb, mrb_value v)->mrb_value { \
    return ((klass*)DATA_PTR(v))->method(mrb); \
}

// DataClass initializer
#define DCinit(klass) \
[](mrb_state *mrb, mrb_value v)->mrb_value { \
    new(mrb, v) klass(mrb); \
    return v; \
}

// Create new DataClass of "this" from within implementation
#define DCnew(mrb) \
[](mrb_state *mrb)->mrb_value { \
    mrb_value v; \
    new(mrb, v) (typename std::remove_reference<decltype(*this)>::type)(mrb); \
    return v; \
}

#endif /* MRUBY_DATA_CLASS_HPP */
