## Example C++ mruby gem (mrbgem)

Demonstrates an easy way to build mruby extensions using C++. Inheriting
DataClass (from data_class.hpp) enables your C++ object to exist in mruby
managed memory. The C++ constructor can accept YourClass.new() arguments and
the destructor will be called automatically by the garbage collector.

The Array8 class is a simple array of 8 floats with an element setter and
getter. It is a minimal example to completely demonstrate how to build an
mrbgem with C++ using DataClass.

Note that if you use C++ new and delete the memory comes from your stdlib heap
instead of the mruby heap. This includes C++ containers as they call new and
delete. This is usually not a problem, but it's something to be aware of
if you are allocating lots of memory for internal use. If possible, use of the
mruby allocators is preferred. e.g. mrb_malloc, mrb_free, et al.

Memory allocation in mruby requires the context (mrb_state). Due to
limitations of the C++ language, it is not possible to pass this directly
to a destructor. If you have memory allocated on the mruby heap in your
constructor, you can free it in the virtual method destroy() which is
automatically called immediately before C++ object destruction.

## License

Copyright (c) 2014 David Turnbull AE9RB

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
