
/*
    pbrt source code Copyright(c) 1998-2012 Matt Pharr and Greg Humphreys.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef PBRT_CORE_MEMORY_H
#define PBRT_CORE_MEMORY_H

// core/memory.h*
#include "pbrt.h"

namespace pbrt
{

// Memory Declarations
class ReferenceCounted {
public:
    ReferenceCounted() { nReferences = 0; }
    AtomicInt32 nReferences;
private:
    ReferenceCounted(const ReferenceCounted &);
    ReferenceCounted &operator=(const ReferenceCounted &);
};


template <typename T> class Reference {
public:
    // Reference Public Methods
    Reference(T *p = NULL) {
        ptr = p;
        if (ptr) AtomicAdd(&ptr->nReferences, 1);
    }
    Reference(const Reference<T> &r) {
        ptr = r.ptr;
        if (ptr) AtomicAdd(&ptr->nReferences, 1);
    }
    Reference &operator=(const Reference<T> &r) {
        if (r.ptr) AtomicAdd(&r.ptr->nReferences, 1);
        if (ptr && AtomicAdd(&ptr->nReferences, -1) == 0) delete ptr;
        ptr = r.ptr;
        return *this;
    }
    Reference &operator=(T *p) {
        if (p) AtomicAdd(&p->nReferences, 1);
        if (ptr && AtomicAdd(&ptr->nReferences, -1) == 0) delete ptr;
        ptr = p;
        return *this;
    }
    ~Reference() {
        if (ptr && AtomicAdd(&ptr->nReferences, -1) == 0)
            delete ptr;
    }
    T *operator->() { return ptr; }
    const T *operator->() const { return ptr; }
    operator bool() const { return ptr != NULL; }
    const T *GetPtr() const { return ptr; }
private:
    T *ptr;
};

} // namespace

#endif // PBRT_CORE_MEMORY_H
