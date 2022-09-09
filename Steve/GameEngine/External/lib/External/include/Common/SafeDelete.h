#pragma once

template <class Pointer>
static inline void SafeDelete(Pointer** pointer_pp)
{
  if ((*pointer_pp) != nullptr)
    delete (*pointer_pp);
  (*pointer_pp) = nullptr;
}

template <class Pointer>
static inline void SafeDeleteArr(Pointer** pointer_pp)
{
  if ((*pointer_pp) != nullptr)
    delete[](*pointer_pp);
  (*pointer_pp) = nullptr;
}