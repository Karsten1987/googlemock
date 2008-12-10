// Copyright 2007, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)

// Google Mock - a framework for writing C++ mock classes.
//
// This file tests the built-in actions generated by a script.

#include <gmock/gmock-generated-actions.h>

#include <functional>
#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace testing {
namespace gmock_generated_actions_test {

using ::std::plus;
using ::std::string;
using ::std::tr1::get;
using ::std::tr1::make_tuple;
using ::std::tr1::tuple;
using ::std::tr1::tuple_element;
using testing::_;
using testing::Action;
using testing::ActionInterface;
using testing::ByRef;
using testing::DoAll;
using testing::Invoke;
using testing::InvokeArgument;
using testing::Return;
using testing::SetArgumentPointee;
using testing::Unused;
using testing::WithArg;
using testing::WithArgs;
using testing::WithoutArgs;

// Sample functions and functors for testing Invoke() and etc.
int Nullary() { return 1; }

class NullaryFunctor {
 public:
  int operator()() { return 2; }
};

bool g_done = false;
void VoidNullary() { g_done = true; }

class VoidNullaryFunctor {
 public:
  void operator()() { g_done = true; }
};

bool Unary(int x) { return x < 0; }

const char* Plus1(const char* s) { return s + 1; }

void VoidUnary(int n) { g_done = true; }

bool ByConstRef(const string& s) { return s == "Hi"; }

const double g_double = 0;
bool ReferencesGlobalDouble(const double& x) { return &x == &g_double; }

string ByNonConstRef(string& s) { return s += "+"; }  // NOLINT

struct UnaryFunctor {
  int operator()(bool x) { return x ? 1 : -1; }
};

const char* Binary(const char* input, short n) { return input + n; }  // NOLINT

void VoidBinary(int, char) { g_done = true; }

int Ternary(int x, char y, short z) { return x + y + z; }  // NOLINT

void VoidTernary(int, char, bool) { g_done = true; }

int SumOf4(int a, int b, int c, int d) { return a + b + c + d; }

int SumOfFirst2(int a, int b, Unused, Unused) { return a + b; }

void VoidFunctionWithFourArguments(char, int, float, double) { g_done = true; }

string Concat4(const char* s1, const char* s2, const char* s3,
               const char* s4) {
  return string(s1) + s2 + s3 + s4;
}

int SumOf5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }

struct SumOf5Functor {
  int operator()(int a, int b, int c, int d, int e) {
    return a + b + c + d + e;
  }
};

string Concat5(const char* s1, const char* s2, const char* s3,
               const char* s4, const char* s5) {
  return string(s1) + s2 + s3 + s4 + s5;
}

int SumOf6(int a, int b, int c, int d, int e, int f) {
  return a + b + c + d + e + f;
}

struct SumOf6Functor {
  int operator()(int a, int b, int c, int d, int e, int f) {
    return a + b + c + d + e + f;
  }
};

string Concat6(const char* s1, const char* s2, const char* s3,
               const char* s4, const char* s5, const char* s6) {
  return string(s1) + s2 + s3 + s4 + s5 + s6;
}

string Concat7(const char* s1, const char* s2, const char* s3,
               const char* s4, const char* s5, const char* s6,
               const char* s7) {
  return string(s1) + s2 + s3 + s4 + s5 + s6 + s7;
}

string Concat8(const char* s1, const char* s2, const char* s3,
               const char* s4, const char* s5, const char* s6,
               const char* s7, const char* s8) {
  return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8;
}

string Concat9(const char* s1, const char* s2, const char* s3,
               const char* s4, const char* s5, const char* s6,
               const char* s7, const char* s8, const char* s9) {
  return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;
}

string Concat10(const char* s1, const char* s2, const char* s3,
                const char* s4, const char* s5, const char* s6,
                const char* s7, const char* s8, const char* s9,
                const char* s10) {
  return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10;
}

class Foo {
 public:
  Foo() : value_(123) {}

  int Nullary() const { return value_; }

  short Unary(long x) { return static_cast<short>(value_ + x); }  // NOLINT

  string Binary(const string& str, char c) const { return str + c; }

  int Ternary(int x, bool y, char z) { return value_ + x + y*z; }

  int SumOf4(int a, int b, int c, int d) const {
    return a + b + c + d + value_;
  }

  int SumOfLast2(Unused, Unused, int a, int b) const { return a + b; }

  int SumOf5(int a, int b, int c, int d, int e) { return a + b + c + d + e; }

  int SumOf6(int a, int b, int c, int d, int e, int f) {
    return a + b + c + d + e + f;
  }

  string Concat7(const char* s1, const char* s2, const char* s3,
                 const char* s4, const char* s5, const char* s6,
                 const char* s7) {
    return string(s1) + s2 + s3 + s4 + s5 + s6 + s7;
  }

  string Concat8(const char* s1, const char* s2, const char* s3,
                 const char* s4, const char* s5, const char* s6,
                 const char* s7, const char* s8) {
    return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8;
  }

  string Concat9(const char* s1, const char* s2, const char* s3,
                 const char* s4, const char* s5, const char* s6,
                 const char* s7, const char* s8, const char* s9) {
    return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9;
  }

  string Concat10(const char* s1, const char* s2, const char* s3,
                  const char* s4, const char* s5, const char* s6,
                  const char* s7, const char* s8, const char* s9,
                  const char* s10) {
    return string(s1) + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9 + s10;
  }
 private:
  int value_;
};

// Tests using Invoke() with a nullary function.
TEST(InvokeTest, Nullary) {
  Action<int()> a = Invoke(Nullary);  // NOLINT
  EXPECT_EQ(1, a.Perform(make_tuple()));
}

// Tests using Invoke() with a unary function.
TEST(InvokeTest, Unary) {
  Action<bool(int)> a = Invoke(Unary);  // NOLINT
  EXPECT_FALSE(a.Perform(make_tuple(1)));
  EXPECT_TRUE(a.Perform(make_tuple(-1)));
}

// Tests using Invoke() with a binary function.
TEST(InvokeTest, Binary) {
  Action<const char*(const char*, short)> a = Invoke(Binary);  // NOLINT
  const char* p = "Hello";
  EXPECT_EQ(p + 2, a.Perform(make_tuple(p, 2)));
}

// Tests using Invoke() with a ternary function.
TEST(InvokeTest, Ternary) {
  Action<int(int, char, short)> a = Invoke(Ternary);  // NOLINT
  EXPECT_EQ(6, a.Perform(make_tuple(1, '\2', 3)));
}

// Tests using Invoke() with a 4-argument function.
TEST(InvokeTest, FunctionThatTakes4Arguments) {
  Action<int(int, int, int, int)> a = Invoke(SumOf4);  // NOLINT
  EXPECT_EQ(1234, a.Perform(make_tuple(1000, 200, 30, 4)));
}

// Tests using Invoke() with a 5-argument function.
TEST(InvokeTest, FunctionThatTakes5Arguments) {
  Action<int(int, int, int, int, int)> a = Invoke(SumOf5);  // NOLINT
  EXPECT_EQ(12345, a.Perform(make_tuple(10000, 2000, 300, 40, 5)));
}

// Tests using Invoke() with a 6-argument function.
TEST(InvokeTest, FunctionThatTakes6Arguments) {
  Action<int(int, int, int, int, int, int)> a = Invoke(SumOf6);  // NOLINT
  EXPECT_EQ(123456, a.Perform(make_tuple(100000, 20000, 3000, 400, 50, 6)));
}

// Tests using Invoke() with a 7-argument function.
TEST(InvokeTest, FunctionThatTakes7Arguments) {
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*)> a =
      Invoke(Concat7);
  EXPECT_EQ("1234567",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7")));
}

// Tests using Invoke() with a 8-argument function.
TEST(InvokeTest, FunctionThatTakes8Arguments) {
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*)> a =
      Invoke(Concat8);
  EXPECT_EQ("12345678",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7", "8")));
}

// Tests using Invoke() with a 9-argument function.
TEST(InvokeTest, FunctionThatTakes9Arguments) {
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*,
                const char*)> a = Invoke(Concat9);
  EXPECT_EQ("123456789",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7", "8", "9")));
}

// Tests using Invoke() with a 10-argument function.
TEST(InvokeTest, FunctionThatTakes10Arguments) {
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*,
                const char*, const char*)> a = Invoke(Concat10);
  EXPECT_EQ("1234567890", a.Perform(make_tuple("1", "2", "3", "4", "5", "6",
                                               "7", "8", "9", "0")));
}

// Tests using Invoke() with functions with parameters declared as Unused.
TEST(InvokeTest, FunctionWithUnusedParameters) {
  Action<int(int, int, double, const string&)> a1 =
      Invoke(SumOfFirst2);
  EXPECT_EQ(12, a1.Perform(make_tuple(10, 2, 5.6, "hi")));

  Action<int(int, int, bool, int*)> a2 =
      Invoke(SumOfFirst2);
  EXPECT_EQ(23, a2.Perform(make_tuple(20, 3, true, static_cast<int*>(NULL))));
}

// Tests using Invoke() with methods with parameters declared as Unused.
TEST(InvokeTest, MethodWithUnusedParameters) {
  Foo foo;
  Action<int(string, bool, int, int)> a1 =
      Invoke(&foo, &Foo::SumOfLast2);
  EXPECT_EQ(12, a1.Perform(make_tuple("hi", true, 10, 2)));

  Action<int(char, double, int, int)> a2 =
      Invoke(&foo, &Foo::SumOfLast2);
  EXPECT_EQ(23, a2.Perform(make_tuple('a', 2.5, 20, 3)));
}

// Tests using Invoke() with a functor.
TEST(InvokeTest, Functor) {
  Action<int(short, char)> a = Invoke(plus<short>());  // NOLINT
  EXPECT_EQ(3, a.Perform(make_tuple(1, 2)));
}

// Tests using Invoke(f) as an action of a compatible type.
TEST(InvokeTest, FunctionWithCompatibleType) {
  Action<long(int, short, char, bool)> a = Invoke(SumOf4);  // NOLINT
  EXPECT_EQ(4321, a.Perform(make_tuple(4000, 300, 20, true)));
}

// Tests using Invoke() with an object pointer and a method pointer.

// Tests using Invoke() with a nullary method.
TEST(InvokeMethodTest, Nullary) {
  Foo foo;
  Action<int()> a = Invoke(&foo, &Foo::Nullary);  // NOLINT
  EXPECT_EQ(123, a.Perform(make_tuple()));
}

// Tests using Invoke() with a unary method.
TEST(InvokeMethodTest, Unary) {
  Foo foo;
  Action<short(long)> a = Invoke(&foo, &Foo::Unary);  // NOLINT
  EXPECT_EQ(4123, a.Perform(make_tuple(4000)));
}

// Tests using Invoke() with a binary method.
TEST(InvokeMethodTest, Binary) {
  Foo foo;
  Action<string(const string&, char)> a = Invoke(&foo, &Foo::Binary);
  string s("Hell");
  EXPECT_EQ("Hello", a.Perform(make_tuple(s, 'o')));
}

// Tests using Invoke() with a ternary method.
TEST(InvokeMethodTest, Ternary) {
  Foo foo;
  Action<int(int, bool, char)> a = Invoke(&foo, &Foo::Ternary);  // NOLINT
  EXPECT_EQ(1124, a.Perform(make_tuple(1000, true, 1)));
}

// Tests using Invoke() with a 4-argument method.
TEST(InvokeMethodTest, MethodThatTakes4Arguments) {
  Foo foo;
  Action<int(int, int, int, int)> a = Invoke(&foo, &Foo::SumOf4);  // NOLINT
  EXPECT_EQ(1357, a.Perform(make_tuple(1000, 200, 30, 4)));
}

// Tests using Invoke() with a 5-argument method.
TEST(InvokeMethodTest, MethodThatTakes5Arguments) {
  Foo foo;
  Action<int(int, int, int, int, int)> a = Invoke(&foo, &Foo::SumOf5);  // NOLINT
  EXPECT_EQ(12345, a.Perform(make_tuple(10000, 2000, 300, 40, 5)));
}

// Tests using Invoke() with a 6-argument method.
TEST(InvokeMethodTest, MethodThatTakes6Arguments) {
  Foo foo;
  Action<int(int, int, int, int, int, int)> a =  // NOLINT
      Invoke(&foo, &Foo::SumOf6);
  EXPECT_EQ(123456, a.Perform(make_tuple(100000, 20000, 3000, 400, 50, 6)));
}

// Tests using Invoke() with a 7-argument method.
TEST(InvokeMethodTest, MethodThatTakes7Arguments) {
  Foo foo;
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*)> a =
      Invoke(&foo, &Foo::Concat7);
  EXPECT_EQ("1234567",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7")));
}

// Tests using Invoke() with a 8-argument method.
TEST(InvokeMethodTest, MethodThatTakes8Arguments) {
  Foo foo;
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*)> a =
      Invoke(&foo, &Foo::Concat8);
  EXPECT_EQ("12345678",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7", "8")));
}

// Tests using Invoke() with a 9-argument method.
TEST(InvokeMethodTest, MethodThatTakes9Arguments) {
  Foo foo;
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*,
                const char*)> a = Invoke(&foo, &Foo::Concat9);
  EXPECT_EQ("123456789",
            a.Perform(make_tuple("1", "2", "3", "4", "5", "6", "7", "8", "9")));
}

// Tests using Invoke() with a 10-argument method.
TEST(InvokeMethodTest, MethodThatTakes10Arguments) {
  Foo foo;
  Action<string(const char*, const char*, const char*, const char*,
                const char*, const char*, const char*, const char*,
                const char*, const char*)> a = Invoke(&foo, &Foo::Concat10);
  EXPECT_EQ("1234567890", a.Perform(make_tuple("1", "2", "3", "4", "5", "6",
                                               "7", "8", "9", "0")));
}

// Tests using Invoke(f) as an action of a compatible type.
TEST(InvokeMethodTest, MethodWithCompatibleType) {
  Foo foo;
  Action<long(int, short, char, bool)> a =  // NOLINT
      Invoke(&foo, &Foo::SumOf4);
  EXPECT_EQ(4444, a.Perform(make_tuple(4000, 300, 20, true)));
}

// Tests ByRef().

// Tests that ReferenceWrapper<T> is copyable.
TEST(ByRefTest, IsCopyable) {
  const string s1 = "Hi";
  const string s2 = "Hello";

  ::testing::internal::ReferenceWrapper<const string> ref_wrapper = ByRef(s1);
  const string& r1 = ref_wrapper;
  EXPECT_EQ(&s1, &r1);

  // Assigns a new value to ref_wrapper.
  ref_wrapper = ByRef(s2);
  const string& r2 = ref_wrapper;
  EXPECT_EQ(&s2, &r2);

  ::testing::internal::ReferenceWrapper<const string> ref_wrapper1 = ByRef(s1);
  // Copies ref_wrapper1 to ref_wrapper.
  ref_wrapper = ref_wrapper1;
  const string& r3 = ref_wrapper;
  EXPECT_EQ(&s1, &r3);
}

// Tests using ByRef() on a const value.
TEST(ByRefTest, ConstValue) {
  const int n = 0;
  // int& ref = ByRef(n);  // This shouldn't compile - we have a
                           // negative compilation test to catch it.
  const int& const_ref = ByRef(n);
  EXPECT_EQ(&n, &const_ref);
}

// Tests using ByRef() on a non-const value.
TEST(ByRefTest, NonConstValue) {
  int n = 0;

  // ByRef(n) can be used as either an int&,
  int& ref = ByRef(n);
  EXPECT_EQ(&n, &ref);

  // or a const int&.
  const int& const_ref = ByRef(n);
  EXPECT_EQ(&n, &const_ref);
}

struct Base {
  bool operator==(const Base&) { return true; }
};

struct Derived : public Base {
  bool operator==(const Derived&) { return true; }
};

// Tests explicitly specifying the type when using ByRef().
TEST(ByRefTest, ExplicitType) {
  int n = 0;
  const int& r1 = ByRef<const int>(n);
  EXPECT_EQ(&n, &r1);

  // ByRef<char>(n);  // This shouldn't compile - we have a negative
                      // compilation test to catch it.


  Derived d;
  Derived& r2 = ByRef<Derived>(d);
  EXPECT_EQ(&d, &r2);

  const Derived& r3 = ByRef<const Derived>(d);
  EXPECT_EQ(&d, &r3);

  Base& r4 = ByRef<Base>(d);
  EXPECT_EQ(&d, &r4);

  const Base& r5 = ByRef<const Base>(d);
  EXPECT_EQ(&d, &r5);

  // The following shouldn't compile - we have a negative compilation
  // test for it.
  //
  // Base b;
  // ByRef<Derived>(b);
}

// Tests InvokeArgument<N>(...).

// Tests using InvokeArgument with a nullary function.
TEST(InvokeArgumentTest, Function0) {
  Action<int(int, int(*)())> a = InvokeArgument<1>();  // NOLINT
  EXPECT_EQ(1, a.Perform(make_tuple(2, &Nullary)));
}

// Tests using InvokeArgument with a unary function.
TEST(InvokeArgumentTest, Functor1) {
  Action<int(UnaryFunctor)> a = InvokeArgument<0>(true);  // NOLINT
  EXPECT_EQ(1, a.Perform(make_tuple(UnaryFunctor())));
}

// Tests using InvokeArgument with a 5-ary function.
TEST(InvokeArgumentTest, Function5) {
  Action<int(int(*)(int, int, int, int, int))> a =  // NOLINT
      InvokeArgument<0>(10000, 2000, 300, 40, 5);
  EXPECT_EQ(12345, a.Perform(make_tuple(&SumOf5)));
}

// Tests using InvokeArgument with a 5-ary functor.
TEST(InvokeArgumentTest, Functor5) {
  Action<int(SumOf5Functor)> a =  // NOLINT
      InvokeArgument<0>(10000, 2000, 300, 40, 5);
  EXPECT_EQ(12345, a.Perform(make_tuple(SumOf5Functor())));
}

// Tests using InvokeArgument with a 6-ary function.
TEST(InvokeArgumentTest, Function6) {
  Action<int(int(*)(int, int, int, int, int, int))> a =  // NOLINT
      InvokeArgument<0>(100000, 20000, 3000, 400, 50, 6);
  EXPECT_EQ(123456, a.Perform(make_tuple(&SumOf6)));
}

// Tests using InvokeArgument with a 6-ary functor.
TEST(InvokeArgumentTest, Functor6) {
  Action<int(SumOf6Functor)> a =  // NOLINT
      InvokeArgument<0>(100000, 20000, 3000, 400, 50, 6);
  EXPECT_EQ(123456, a.Perform(make_tuple(SumOf6Functor())));
}

// Tests using InvokeArgument with a 7-ary function.
TEST(InvokeArgumentTest, Function7) {
  Action<string(string(*)(const char*, const char*, const char*,
                          const char*, const char*, const char*,
                          const char*))> a =
      InvokeArgument<0>("1", "2", "3", "4", "5", "6", "7");
  EXPECT_EQ("1234567", a.Perform(make_tuple(&Concat7)));
}

// Tests using InvokeArgument with a 8-ary function.
TEST(InvokeArgumentTest, Function8) {
  Action<string(string(*)(const char*, const char*, const char*,
                          const char*, const char*, const char*,
                          const char*, const char*))> a =
      InvokeArgument<0>("1", "2", "3", "4", "5", "6", "7", "8");
  EXPECT_EQ("12345678", a.Perform(make_tuple(&Concat8)));
}

// Tests using InvokeArgument with a 9-ary function.
TEST(InvokeArgumentTest, Function9) {
  Action<string(string(*)(const char*, const char*, const char*,
                          const char*, const char*, const char*,
                          const char*, const char*, const char*))> a =
      InvokeArgument<0>("1", "2", "3", "4", "5", "6", "7", "8", "9");
  EXPECT_EQ("123456789", a.Perform(make_tuple(&Concat9)));
}

// Tests using InvokeArgument with a 10-ary function.
TEST(InvokeArgumentTest, Function10) {
  Action<string(string(*)(const char*, const char*, const char*,
                          const char*, const char*, const char*,
                          const char*, const char*, const char*,
                          const char*))> a =
      InvokeArgument<0>("1", "2", "3", "4", "5", "6", "7", "8", "9", "0");
  EXPECT_EQ("1234567890", a.Perform(make_tuple(&Concat10)));
}

// Tests using InvokeArgument with a function that takes a pointer argument.
TEST(InvokeArgumentTest, ByPointerFunction) {
  Action<const char*(const char*(*)(const char* input, short n))> a =  // NOLINT
      InvokeArgument<0>(static_cast<const char*>("Hi"), 1);
  EXPECT_STREQ("i", a.Perform(make_tuple(&Binary)));
}

// Tests using InvokeArgument with a function that takes a const char*
// by passing it a C-string literal.
TEST(InvokeArgumentTest, FunctionWithCStringLiteral) {
  Action<const char*(const char*(*)(const char* input, short n))> a =  // NOLINT
      InvokeArgument<0>("Hi", 1);
  EXPECT_STREQ("i", a.Perform(make_tuple(&Binary)));
}

// Tests using InvokeArgument with a function that takes a const reference.
TEST(InvokeArgumentTest, ByConstReferenceFunction) {
  Action<bool(bool(*function)(const string& s))> a =  // NOLINT
      InvokeArgument<0>(string("Hi"));
  // When action 'a' is constructed, it makes a copy of the temporary
  // string object passed to it, so it's OK to use 'a' later, when the
  // temporary object has already died.
  EXPECT_TRUE(a.Perform(make_tuple(&ByConstRef)));
}

// Tests using InvokeArgument with ByRef() and a function that takes a
// const reference.
TEST(InvokeArgumentTest, ByExplicitConstReferenceFunction) {
  Action<bool(bool(*)(const double& x))> a =  // NOLINT
      InvokeArgument<0>(ByRef(g_double));
  // The above line calls ByRef() on a const value.
  EXPECT_TRUE(a.Perform(make_tuple(&ReferencesGlobalDouble)));

  double x = 0;
  a = InvokeArgument<0>(ByRef(x));  // This calls ByRef() on a non-const.
  EXPECT_FALSE(a.Perform(make_tuple(&ReferencesGlobalDouble)));
}

// Tests using WithoutArgs with an action that takes no argument.
TEST(WithoutArgsTest, NoArg) {
  Action<int(int n)> a = WithoutArgs(Invoke(Nullary));  // NOLINT
  EXPECT_EQ(1, a.Perform(make_tuple(2)));
}

// Tests using WithArgs and WithArg with an action that takes 1 argument.
TEST(WithArgsTest, OneArg) {
  Action<bool(double x, int n)> a = WithArgs<1>(Invoke(Unary));  // NOLINT
  EXPECT_TRUE(a.Perform(make_tuple(1.5, -1)));
  EXPECT_FALSE(a.Perform(make_tuple(1.5, 1)));

  // Also tests the synonym WithArg.
  Action<bool(double x, int n)> b = WithArg<1>(Invoke(Unary));  // NOLINT
  EXPECT_TRUE(a.Perform(make_tuple(1.5, -1)));
  EXPECT_FALSE(a.Perform(make_tuple(1.5, 1)));

}

// Tests using WithArgs with an action that takes 2 arguments.
TEST(WithArgsTest, TwoArgs) {
  Action<const char*(const char* s, double x, int n)> a =
      WithArgs<0, 2>(Invoke(Binary));
  const char s[] = "Hello";
  EXPECT_EQ(s + 2, a.Perform(make_tuple(s, 0.5, 2)));
}

// Tests using WithArgs with an action that takes 3 arguments.
TEST(WithArgsTest, ThreeArgs) {
  Action<int(int, double, char, short)> a =  // NOLINT
      WithArgs<0, 2, 3>(Invoke(Ternary));
  EXPECT_EQ(123, a.Perform(make_tuple(100, 6.5, 20, 3)));
}

// Tests using WithArgs with an action that takes 4 arguments.
TEST(WithArgsTest, FourArgs) {
  Action<string(const char*, const char*, double, const char*, const char*)> a =
      WithArgs<4, 3, 1, 0>(Invoke(Concat4));
  EXPECT_EQ("4310", a.Perform(make_tuple("0", "1", 2.5, "3", "4")));
}

// Tests using WithArgs with an action that takes 5 arguments.
TEST(WithArgsTest, FiveArgs) {
  Action<string(const char*, const char*, const char*,
                const char*, const char*)> a =
      WithArgs<4, 3, 2, 1, 0>(Invoke(Concat5));
  EXPECT_EQ("43210", a.Perform(make_tuple("0", "1", "2", "3", "4")));
}

// Tests using WithArgs with an action that takes 6 arguments.
TEST(WithArgsTest, SixArgs) {
  Action<string(const char*, const char*, const char*)> a =
      WithArgs<0, 1, 2, 2, 1, 0>(Invoke(Concat6));
  EXPECT_EQ("012210", a.Perform(make_tuple("0", "1", "2")));
}

// Tests using WithArgs with an action that takes 7 arguments.
TEST(WithArgsTest, SevenArgs) {
  Action<string(const char*, const char*, const char*, const char*)> a =
      WithArgs<0, 1, 2, 3, 2, 1, 0>(Invoke(Concat7));
  EXPECT_EQ("0123210", a.Perform(make_tuple("0", "1", "2", "3")));
}

// Tests using WithArgs with an action that takes 8 arguments.
TEST(WithArgsTest, EightArgs) {
  Action<string(const char*, const char*, const char*, const char*)> a =
      WithArgs<0, 1, 2, 3, 0, 1, 2, 3>(Invoke(Concat8));
  EXPECT_EQ("01230123", a.Perform(make_tuple("0", "1", "2", "3")));
}

// Tests using WithArgs with an action that takes 9 arguments.
TEST(WithArgsTest, NineArgs) {
  Action<string(const char*, const char*, const char*, const char*)> a =
      WithArgs<0, 1, 2, 3, 1, 2, 3, 2, 3>(Invoke(Concat9));
  EXPECT_EQ("012312323", a.Perform(make_tuple("0", "1", "2", "3")));
}

// Tests using WithArgs with an action that takes 10 arguments.
TEST(WithArgsTest, TenArgs) {
  Action<string(const char*, const char*, const char*, const char*)> a =
      WithArgs<0, 1, 2, 3, 2, 1, 0, 1, 2, 3>(Invoke(Concat10));
  EXPECT_EQ("0123210123", a.Perform(make_tuple("0", "1", "2", "3")));
}

// Tests using WithArgs with an action that is not Invoke().
class SubstractAction : public ActionInterface<int(int, int)> {  // NOLINT
 public:
  virtual int Perform(const tuple<int, int>& args) {
    return get<0>(args) - get<1>(args);
  }
};

TEST(WithArgsTest, NonInvokeAction) {
  Action<int(const string&, int, int)> a =  // NOLINT
      WithArgs<2, 1>(MakeAction(new SubstractAction));
  EXPECT_EQ(8, a.Perform(make_tuple("hi", 2, 10)));
}

// Tests using WithArgs to pass all original arguments in the original order.
TEST(WithArgsTest, Identity) {
  Action<int(int x, char y, short z)> a =  // NOLINT
      WithArgs<0, 1, 2>(Invoke(Ternary));
  EXPECT_EQ(123, a.Perform(make_tuple(100, 20, 3)));
}

// Tests using WithArgs with repeated arguments.
TEST(WithArgsTest, RepeatedArguments) {
  Action<int(bool, int m, int n)> a =  // NOLINT
      WithArgs<1, 1, 1, 1>(Invoke(SumOf4));
  EXPECT_EQ(4, a.Perform(make_tuple(false, 1, 10)));
}

// Tests using WithArgs with reversed argument order.
TEST(WithArgsTest, ReversedArgumentOrder) {
  Action<const char*(short n, const char* input)> a =  // NOLINT
      WithArgs<1, 0>(Invoke(Binary));
  const char s[] = "Hello";
  EXPECT_EQ(s + 2, a.Perform(make_tuple(2, s)));
}

// Tests using WithArgs with compatible, but not identical, argument types.
TEST(WithArgsTest, ArgsOfCompatibleTypes) {
  Action<long(short x, int y, double z, char c)> a =  // NOLINT
      WithArgs<0, 1, 3>(Invoke(Ternary));
  EXPECT_EQ(123, a.Perform(make_tuple(100, 20, 5.6, 3)));
}

// Tests using WithArgs with an action that returns void.
TEST(WithArgsTest, VoidAction) {
  Action<void(double x, char c, int n)> a = WithArgs<2, 1>(Invoke(VoidBinary));
  g_done = false;
  a.Perform(make_tuple(1.5, 'a', 3));
  EXPECT_TRUE(g_done);
}

// Tests DoAll(a1, a2).
TEST(DoAllTest, TwoActions) {
  int n = 0;
  Action<int(int*)> a = DoAll(SetArgumentPointee<0>(1),  // NOLINT
                              Return(2));
  EXPECT_EQ(2, a.Perform(make_tuple(&n)));
  EXPECT_EQ(1, n);
}

// Tests DoAll(a1, a2, a3).
TEST(DoAllTest, ThreeActions) {
  int m = 0, n = 0;
  Action<int(int*, int*)> a = DoAll(SetArgumentPointee<0>(1),  // NOLINT
                                    SetArgumentPointee<1>(2),
                                    Return(3));
  EXPECT_EQ(3, a.Perform(make_tuple(&m, &n)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
}

// Tests DoAll(a1, a2, a3, a4).
TEST(DoAllTest, FourActions) {
  int m = 0, n = 0;
  char ch = '\0';
  Action<int(int*, int*, char*)> a =  // NOLINT
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            Return(3));
  EXPECT_EQ(3, a.Perform(make_tuple(&m, &n, &ch)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', ch);
}

// Tests DoAll(a1, a2, a3, a4, a5).
TEST(DoAllTest, FiveActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0';
  Action<int(int*, int*, char*, char*)> action =  // NOLINT
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
}

// Tests DoAll(a1, a2, ..., a6).
TEST(DoAllTest, SixActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0', c = '\0';
  Action<int(int*, int*, char*, char*, char*)> action =  // NOLINT
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            SetArgumentPointee<4>('c'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b, &c)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
  EXPECT_EQ('c', c);
}

// Tests DoAll(a1, a2, ..., a7).
TEST(DoAllTest, SevenActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0', c = '\0', d = '\0';
  Action<int(int*, int*, char*, char*, char*, char*)> action =  // NOLINT
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            SetArgumentPointee<4>('c'),
            SetArgumentPointee<5>('d'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b, &c, &d)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
  EXPECT_EQ('c', c);
  EXPECT_EQ('d', d);
}

// Tests DoAll(a1, a2, ..., a8).
TEST(DoAllTest, EightActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0', c = '\0', d = '\0', e = '\0';
  Action<int(int*, int*, char*, char*, char*, char*,  // NOLINT
             char*)> action =
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            SetArgumentPointee<4>('c'),
            SetArgumentPointee<5>('d'),
            SetArgumentPointee<6>('e'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b, &c, &d, &e)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
  EXPECT_EQ('c', c);
  EXPECT_EQ('d', d);
  EXPECT_EQ('e', e);
}

// Tests DoAll(a1, a2, ..., a9).
TEST(DoAllTest, NineActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0', c = '\0', d = '\0', e = '\0', f = '\0';
  Action<int(int*, int*, char*, char*, char*, char*,  // NOLINT
             char*, char*)> action =
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            SetArgumentPointee<4>('c'),
            SetArgumentPointee<5>('d'),
            SetArgumentPointee<6>('e'),
            SetArgumentPointee<7>('f'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b, &c, &d, &e, &f)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
  EXPECT_EQ('c', c);
  EXPECT_EQ('d', d);
  EXPECT_EQ('e', e);
  EXPECT_EQ('f', f);
}

// Tests DoAll(a1, a2, ..., a10).
TEST(DoAllTest, TenActions) {
  int m = 0, n = 0;
  char a = '\0', b = '\0', c = '\0', d = '\0';
  char e = '\0', f = '\0', g = '\0';
  Action<int(int*, int*, char*, char*, char*, char*,  // NOLINT
             char*, char*, char*)> action =
      DoAll(SetArgumentPointee<0>(1),
            SetArgumentPointee<1>(2),
            SetArgumentPointee<2>('a'),
            SetArgumentPointee<3>('b'),
            SetArgumentPointee<4>('c'),
            SetArgumentPointee<5>('d'),
            SetArgumentPointee<6>('e'),
            SetArgumentPointee<7>('f'),
            SetArgumentPointee<8>('g'),
            Return(3));
  EXPECT_EQ(3, action.Perform(make_tuple(&m, &n, &a, &b, &c, &d, &e, &f, &g)));
  EXPECT_EQ(1, m);
  EXPECT_EQ(2, n);
  EXPECT_EQ('a', a);
  EXPECT_EQ('b', b);
  EXPECT_EQ('c', c);
  EXPECT_EQ('d', d);
  EXPECT_EQ('e', e);
  EXPECT_EQ('f', f);
  EXPECT_EQ('g', g);
}

}  // namespace gmock_generated_actions_test
}  // namespace testing
