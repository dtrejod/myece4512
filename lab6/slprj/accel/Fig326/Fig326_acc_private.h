#include "__cf_Fig326.h"
#ifndef RTW_HEADER_Fig326_acc_private_h_
#define RTW_HEADER_Fig326_acc_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#if !defined(ss_VALIDATE_MEMORY)
#define ss_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(S, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
extern void RandSrcInitState_U_64 ( const uint32_T seed [ ] , real_T state [
] , int32_T nChans ) ; extern void RandSrcInitState_GZ ( const uint32_T seed
[ ] , uint32_T state [ ] , int32_T nChans ) ; extern void RandSrc_U_D (
real_T y [ ] , const real_T minVec [ ] , int32_T minLen , const real_T maxVec
[ ] , int32_T maxLen , real_T state [ ] , int32_T nChans , int32_T nSamps ) ;
extern void RandSrc_GZ_D ( real_T y [ ] , const real_T mean [ ] , int32_T
meanLen , const real_T xstd [ ] , int32_T xstdLen , uint32_T state [ ] ,
int32_T nChans , int32_T nSamps ) ; void
Fig326_acc_BINARYSEARCH_real_T_Near_iL ( uint32_T * piLeft , real_T u , const
real_T * pData , uint32_T iHi ) ;
#endif
