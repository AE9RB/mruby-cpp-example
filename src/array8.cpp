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

#include "data_class.hpp"

struct Array8 : DataClass<Array8>
{
    static constexpr const char* struct_name = "Array8";

    static const mrb_int SIZE = 8;
    mrb_float *data;

    Array8(mrb_state *mrb)
    {
        data = (mrb_float*)mrb_malloc(mrb, sizeof(mrb_float) * SIZE);
    }

    void destroy(mrb_state *mrb) {
        mrb_free(mrb, data);
    }

    mrb_value
    get_element(mrb_state *mrb)
    {
        mrb_int i;
        mrb_get_args(mrb, "i", &i);
        if (i<0 || i>=SIZE) mrb_raise(mrb, E_INDEX_ERROR, "index is out of array");
        return mrb_float_value(mrb, data[i]);
    }

    mrb_value
    set_element(mrb_state *mrb)
    {
        mrb_int i;
        mrb_float f;
        mrb_get_args(mrb, "if", &i, &f);
        if (i<0 || i>=SIZE) mrb_raise(mrb, E_INDEX_ERROR, "index is out of array");
        data[i] = f;
        return mrb_float_value(mrb, f);
    }

};

extern "C"
void
mrb_mruby_cpp_example_gem_init(mrb_state* mrb)
{
    RClass *array8;

    array8 = mrb_define_class(mrb, "Array8", mrb->object_class);
    MRB_SET_INSTANCE_TT(array8, MRB_TT_DATA);

    mrb_define_method(mrb, array8, "initialize", DCinit(Array8), MRB_ARGS_NONE());

    mrb_define_method(mrb, array8, "[]", DCmethod(Array8, get_element), MRB_ARGS_REQ(1));
    mrb_define_method(mrb, array8, "[]=", DCmethod(Array8, set_element), MRB_ARGS_REQ(2));
}

extern "C"
void
mrb_mruby_cpp_example_gem_final(mrb_state* mrb)
{
}
