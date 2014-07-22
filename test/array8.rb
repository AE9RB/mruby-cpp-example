# Copyright (c) 2014 David Turnbull AE9RB
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.

assert("Array8 set and get") do
  a = Array8.new
  a[0] = 1.1
  a[1] = 9
  a[7] = 2.2
  assert_float 1.1, a[0]
  assert_float 9.0, a[1]
  assert_float 2.2, a[7]
end

assert("Array8 valid type") do
  a = Array8.new
  assert_raise(TypeError) { a[0] = "foo" }
  assert_raise(TypeError) { a[:foo] = 9.9 }
end

assert("Array8 valid range") do
  a = Array8.new
  assert_raise(IndexError) { a[-1] }
  assert_raise(IndexError) { a[8] }
end
