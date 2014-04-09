/*  This file is part of the Vc library. {{{

    Copyright (C) 2013 Matthias Kretz <kretz@kde.org>

    Vc is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    Vc is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Vc.  If not, see <http://www.gnu.org/licenses/>.

}}}*/

#define VC_NEWTEST
#include "unittest.h"
#include "../common/simd_array.h"

using namespace Vc;

#define SIMD_ARRAY_LIST                                                                            \
    (SIMD_ARRAYS(32),                                                                              \
     SIMD_ARRAYS(17),                                                                              \
     SIMD_ARRAYS(16),                                                                              \
     SIMD_ARRAYS(9),                                                                               \
     SIMD_ARRAYS(8),                                                                               \
     SIMD_ARRAYS(5),                                                                               \
     SIMD_ARRAYS(4),                                                                               \
     SIMD_ARRAYS(3),                                                                               \
     SIMD_ARRAYS(2),                                                                               \
     SIMD_ARRAYS(1))

template<typename T, size_t N> constexpr size_t captureN(simd_array<T, N>) { return N; }

TEST_BEGIN(V, createArray, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    typedef typename V::VectorEntryType VT;
    typedef typename V::vector_type Vec;
    V array;

    COMPARE(array.size(), captureN(V()));
    VERIFY(sizeof(array) >= array.size() * sizeof(VT));
    VERIFY(sizeof(array) <= 2 * array.size() * sizeof(VT));
TEST_END

TEST_BEGIN(V, broadcast, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    V array = 0;
    array = 1;
    V v0{T(1)};
    V v1 = T(2);
    v0 = 2;
    v1 = 3;
    COMPARE(V(), V(0));
TEST_END

TEST_BEGIN(V, broadcast_equal, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    V a = 0;
    V b = 0;
    COMPARE(a, b);
    a = 1;
    b = 1;
    COMPARE(a, b);
TEST_END

TEST_BEGIN(V, broadcast_not_equal, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    V a = 0;
    V b = 1;
    VERIFY(all_of(a != b));
    VERIFY(all_of(a < b));
    VERIFY(all_of(a <= b));
    VERIFY(none_of(a > b));
    VERIFY(none_of(a >= b));
    a = 1;
    VERIFY(all_of(a <= b));
    VERIFY(all_of(a >= b));
TEST_END

TEST_BEGIN(V, arithmetics, SIMD_ARRAY_LIST)
{
    V a = 0;
    V b = 1;
    V c = 10;
    COMPARE(a + b, b);
    COMPARE(c + b, V{11});
    COMPARE(c - b, V{9});
    COMPARE(b - a, b);
    COMPARE(b * a, a);
    COMPARE(b * b, b);
    COMPARE(c * b, c);
    COMPARE(c * c, V{100});
    COMPARE(c / c, b);
    COMPARE(a / c, a);
    COMPARE(c / b, c);
}
TEST_END

TEST_BEGIN(V, indexesFromZero, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    V a(Vc::IndexesFromZero);
    for (std::size_t i = 0; i < a.size(); ++i) {
        COMPARE(a[i], T(i));
    }
TEST_END

TEST_BEGIN(V, load, SIMD_ARRAY_LIST)
    typedef typename V::EntryType T;
    Vc::Memory<V, V::Size + 2> data;
    for (size_t i = 0; i < data.entriesCount(); ++i) {
        data[i] = T(i);
    }

    V a{ &data[0] };
    V b(Vc::IndexesFromZero);
    COMPARE(a, b);

    b.load(&data[0]);
    COMPARE(a, b);

    a.load(&data[1], Vc::Unaligned);
    COMPARE(a, b + 1);

    b = decltype(b)(&data[2], Vc::Unaligned | Vc::Streaming);
    COMPARE(a, b - 1);
TEST_END

TEST_BEGIN(A,
           load_converting,
           (simd_array<float, 32>,
            simd_array<float, 17>,
            simd_array<float, 16>,
            simd_array<float, 8>,
            simd_array<float, 4>,
            simd_array<float, 3>,
            simd_array<float, 2>,
            simd_array<float, 1>))
{
    Vc::Memory<double_v, 34> data;
    for (size_t i = 0; i < data.entriesCount(); ++i) {
        data[i] = double(i);
    }

    A a{ &data[0] };
    A b(Vc::IndexesFromZero);
    COMPARE(a, b);

    b.load(&data[1], Vc::Unaligned);
    COMPARE(a + 1, b);

    a = A(&data[2], Vc::Unaligned | Vc::Streaming);
    COMPARE(a, b + 1);
}
TEST_END

TEST_BEGIN(V, store, SIMD_ARRAY_LIST)
{
    typedef typename V::EntryType T;
    Vc::Memory<V, 34> data;
    data = V::Zero();

    V a(Vc::IndexesFromZero);
    a.store(&data[0], Vc::Aligned);
    for (size_t i = 0; i < V::Size; ++i) COMPARE(data[i], i);
    a.store(&data[1], Vc::Unaligned);
    for (size_t i = 0; i < V::Size; ++i) COMPARE(data[i + 1], i);
    a.store(&data[0], Vc::Aligned | Vc::Streaming);
    for (size_t i = 0; i < V::Size; ++i) COMPARE(data[i], i);
    a.store(&data[1], Vc::Unaligned | Vc::Streaming);
    for (size_t i = 0; i < V::Size; ++i) COMPARE(data[i + 1], i);
}
TEST_END