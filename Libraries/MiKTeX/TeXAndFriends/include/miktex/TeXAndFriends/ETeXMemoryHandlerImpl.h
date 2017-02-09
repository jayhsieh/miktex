/* miktex/TeXAndFriends/ETeXMemoryHandlerImpl.h:        -*- C++ -*-

   Copyright (C) 2017 Christian Schenk

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 2, or (at your
   option) any later version.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */

#if defined(_MSC_VER)
#  pragma once
#endif

#if !defined(FC37AFDF33BF45C38B6179E5737B0F56)
#define FC37AFDF33BF45C38B6179E5737B0F56

#include <miktex/TeXAndFriends/config.h>

#include "TeXMemoryHandlerImpl.h"

MIKTEXMF_BEGIN_NAMESPACE;

template<class PROGRAM_CLASS> class ETeXMemoryHandlerImpl :
  public TeXMemoryHandlerImpl<PROGRAM_CLASS>
{
public:
  ETeXMemoryHandlerImpl(PROGRAM_CLASS& program, TeXMFApp& texmfapp) :
    TeXMemoryHandlerImpl<PROGRAM_CLASS>(program, texmfapp)
  {
  }

public:
  void Allocate(const std::unordered_map<std::string, int>& userParams) override
  {
    TeXMemoryHandlerImpl<PROGRAM_CLASS>::Allocate(userParams);
    AllocateArray("eofseen", program.eofseen, program.maxinopen);
    AllocateArray("grpstack", program.grpstack, program.maxinopen);
    AllocateArray("ifstack", program.ifstack, program.maxinopen);
  }

public:
  void Free() override
  {
    TeXMemoryHandlerImpl<PROGRAM_CLASS>::Free();
    FreeArray("eofseen", program.eofseen);
    FreeArray("grpstack", program.grpstack);
    FreeArray("ifstack", program.ifstack);
  }

public:
  void Check() override
  {
    TeXMemoryHandlerImpl<PROGRAM_CLASS>::Check();
    MIKTEX_ASSERT_VALID_HEAP_POINTER_OR_NIL(program.eofseen);
    MIKTEX_ASSERT_VALID_HEAP_POINTER_OR_NIL(program.grpstack);
    MIKTEX_ASSERT_VALID_HEAP_POINTER_OR_NIL(program.ifstack);
  }
};

MIKTEXMF_END_NAMESPACE;

#endif
