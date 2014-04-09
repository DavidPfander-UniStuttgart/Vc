/*  This file is part of the Vc library. {{{
Copyright © 2014 Matthias Kretz <kretz@kde.org>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

// load ctors{{{1
explicit Vc_INTRINSIC Vector(const EntryType *x)
{
    load(x);
}
template <typename Flags, typename = enable_if<Traits::IsLoadStoreFlag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const EntryType *x, Flags flags)
{
    load(x, flags);
}
template <
    typename U,
    typename Flags = DefaultLoadTag,
    typename = enable_if<std::is_arithmetic<U>::value &&Traits::IsLoadStoreFlag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const U *x, Flags flags = Flags())
{
    load(x, flags);
}
// load member functions{{{1
Vc_INTRINSIC void load(const EntryType *mem)
{
    load(mem, DefaultLoadTag());
}
template <typename Flags, typename = enable_if<Traits::IsLoadStoreFlag<Flags>::value>>
Vc_INTRINSIC void load(const EntryType *mem, Flags flags)
{
    load<EntryType, Flags>(mem, flags);
}
template <
    typename U,
    typename Flags = DefaultLoadTag,
    typename = enable_if<std::is_arithmetic<U>::value &&Traits::IsLoadStoreFlag<Flags>::value>>
Vc_INTRINSIC_L void load(const U *mem, Flags = Flags()) Vc_INTRINSIC_R;
//}}}1

// vim: foldmethod=marker