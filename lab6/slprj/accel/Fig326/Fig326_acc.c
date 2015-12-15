#include "__cf_Fig326.h"
#include <math.h>
#include "Fig326_acc.h"
#include "Fig326_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
void Fig326_acc_BINARYSEARCH_real_T_Near_iL ( uint32_T * piLeft , real_T u ,
const real_T * pData , uint32_T iHi ) { uint32_T iRght ; * piLeft = 0U ;
iRght = iHi ; if ( u <= pData [ 0 ] ) { } else if ( u >= pData [ iHi ] ) { *
piLeft = iHi ; } else { uint32_T i ; while ( ( iRght - * piLeft ) > 1U ) { i
= ( * piLeft + iRght ) >> 1 ; if ( u < pData [ i ] ) { iRght = i ; } else { *
piLeft = i ; } } { real_T diffLeft , diffRght ; diffLeft = u - pData [ *
piLeft ] ; diffRght = pData [ iRght ] - u ; if ( diffRght <= diffLeft ) { *
piLeft = iRght ; } } } } void RandSrcInitState_U_64 ( const uint32_T seed [ ]
, real_T state [ ] , int32_T nChans ) { int32_T i ; uint32_T j ; int32_T k ;
int32_T n ; real_T d ; for ( i = 0 ; i < nChans ; i ++ ) { j = seed [ i ] !=
0U ? seed [ i ] : 2147483648U ; state [ 35 * i + 34 ] = j ; for ( k = 0 ; k <
32 ; k ++ ) { d = 0.0 ; for ( n = 0 ; n < 53 ; n ++ ) { j ^= j << 13 ; j ^= j
>> 17 ; j ^= j << 5 ; d = ( real_T ) ( ( int32_T ) ( j >> 19 ) & 1 ) + ( d +
d ) ; } state [ 35 * i + k ] = ldexp ( d , - 53 ) ; } state [ 35 * i + 32 ] =
0.0 ; state [ 35 * i + 33 ] = 0.0 ; } } void RandSrcInitState_GZ ( const
uint32_T seed [ ] , uint32_T state [ ] , int32_T nChans ) { int32_T i ; for (
i = 0 ; i < nChans ; i ++ ) { state [ i << 1 ] = 362436069U ; state [ ( i <<
1 ) + 1 ] = seed [ i ] == 0U ? 521288629U : seed [ i ] ; } } void RandSrc_U_D
( real_T y [ ] , const real_T minVec [ ] , int32_T minLen , const real_T
maxVec [ ] , int32_T maxLen , real_T state [ ] , int32_T nChans , int32_T
nSamps ) { int32_T one ; int32_T lsw ; int8_T * onePtr ; int32_T chan ;
real_T min ; real_T max ; int32_T samps ; real_T d ; int32_T i ; uint32_T j ;
int32_T ii [ 2 ] ; one = 1 ; onePtr = ( int8_T * ) & one ; lsw = ( onePtr [
0U ] == 0 ) ; for ( chan = 0 ; chan < nChans ; chan ++ ) { min = minVec [
minLen > 1 ? chan : 0 ] ; max = maxVec [ maxLen > 1 ? chan : 0 ] ; max -= min
; i = ( int32_T ) ( ( uint32_T ) state [ chan * 35 + 33 ] & 31U ) ; j = (
uint32_T ) state [ chan * 35 + 34 ] ; for ( samps = 0 ; samps < nSamps ;
samps ++ ) { d = state [ ( ( i + 20 ) & 31 ) + chan * 35 ] ; d -= state [ ( (
i + 5 ) & 31 ) + chan * 35 ] ; d -= state [ chan * 35 + 32 ] ; if ( d >= 0.0
) { state [ chan * 35 + 32 ] = 0.0 ; } else { d ++ ; state [ chan * 35 + 32 ]
= 1.1102230246251565E-16 ; } state [ chan * 35 + i ] = d ; i = ( i + 1 ) & 31
; memcpy ( ( void * ) & ii [ 0U ] , ( void * ) & d , sizeof ( real_T ) ) ; ii
[ lsw ] ^= j ; j ^= j << 13 ; j ^= j >> 17 ; j ^= j << 5 ; ii [ lsw ^ 1 ] ^=
j & 1048575U ; memcpy ( ( void * ) & d , ( void * ) & ii [ 0U ] , sizeof (
real_T ) ) ; y [ chan * nSamps + samps ] = max * d + min ; } state [ chan *
35 + 33 ] = i ; state [ chan * 35 + 34 ] = j ; } } void RandSrc_GZ_D ( real_T
y [ ] , const real_T mean [ ] , int32_T meanLen , const real_T xstd [ ] ,
int32_T xstdLen , uint32_T state [ ] , int32_T nChans , int32_T nSamps ) {
int32_T i ; int32_T j ; real_T r ; real_T x ; real_T s ; real_T y_p ; int32_T
chan ; real_T std ; uint32_T icng ; uint32_T jsr ; int32_T samp ; real_T
mean_p ; static const real_T vt [ 65 ] = { 0.340945 , 0.4573146 , 0.5397793 ,
0.6062427 , 0.6631691 , 0.7136975 , 0.7596125 , 0.8020356 , 0.8417227 ,
0.8792102 , 0.9148948 , 0.9490791 , 0.9820005 , 1.0138492 , 1.044781 ,
1.0749254 , 1.1043917 , 1.1332738 , 1.161653 , 1.189601 , 1.2171815 ,
1.2444516 , 1.2714635 , 1.298265 , 1.3249008 , 1.3514125 , 1.3778399 ,
1.4042211 , 1.4305929 , 1.4569915 , 1.4834527 , 1.5100122 , 1.5367061 ,
1.5635712 , 1.5906454 , 1.617968 , 1.6455802 , 1.6735255 , 1.7018503 ,
1.7306045 , 1.7598422 , 1.7896223 , 1.8200099 , 1.851077 , 1.8829044 ,
1.9155831 , 1.9492166 , 1.9839239 , 2.0198431 , 2.0571356 , 2.095993 ,
2.136645 , 2.1793713 , 2.2245175 , 2.2725186 , 2.3239338 , 2.3795008 ,
2.4402218 , 2.5075117 , 2.5834658 , 2.6713916 , 2.7769942 , 2.7769942 ,
2.7769942 , 2.7769942 } ; for ( chan = 0 ; chan < nChans ; chan ++ ) { std =
xstd [ xstdLen > 1 ? chan : 0 ] ; icng = state [ chan << 1 ] ; jsr = state [
( chan << 1 ) + 1 ] ; mean_p = mean [ meanLen > 1 ? chan : 0 ] ; for ( samp =
0 ; samp < nSamps ; samp ++ ) { icng = 69069U * icng + 1234567U ; jsr ^= jsr
<< 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; i = ( int32_T ) ( icng + jsr ) ;
j = ( i & 63 ) + 1 ; r = ( real_T ) i * 4.6566128730773926E-10 * vt [ j ] ;
if ( ! ( muDoubleScalarAbs ( r ) <= vt [ j - 1 ] ) ) { x = (
muDoubleScalarAbs ( r ) - vt [ j - 1 ] ) / ( vt [ j ] - vt [ j - 1 ] ) ; icng
= 69069U * icng + 1234567U ; jsr ^= jsr << 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr
<< 5 ; y_p = ( real_T ) ( int32_T ) ( icng + jsr ) * 2.328306436538696E-10 +
0.5 ; s = x + y_p ; if ( s > 1.301198 ) { r = r < 0.0 ? 0.4878992 * x -
0.4878992 : 0.4878992 - 0.4878992 * x ; } else { if ( ! ( s <= 0.9689279 ) )
{ x = 0.4878992 - 0.4878992 * x ; if ( y_p > 12.67706 - muDoubleScalarExp ( -
0.5 * x * x ) * 12.37586 ) { r = r < 0.0 ? - x : x ; } else { if ( ! (
muDoubleScalarExp ( - 0.5 * vt [ j ] * vt [ j ] ) + y_p * 0.01958303 / vt [ j
] <= muDoubleScalarExp ( - 0.5 * r * r ) ) ) { do { icng = 69069U * icng +
1234567U ; jsr ^= jsr << 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; x =
muDoubleScalarLog ( ( real_T ) ( int32_T ) ( icng + jsr ) *
2.328306436538696E-10 + 0.5 ) / 2.776994 ; icng = 69069U * icng + 1234567U ;
jsr ^= jsr << 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; } while (
muDoubleScalarLog ( ( real_T ) ( int32_T ) ( icng + jsr ) *
2.328306436538696E-10 + 0.5 ) * - 2.0 <= x * x ) ; r = r < 0.0 ? x - 2.776994
: 2.776994 - x ; } } } } } y [ chan * nSamps + samp ] = std * r + mean_p ; }
state [ chan << 1 ] = icng ; state [ ( chan << 1 ) + 1 ] = jsr ; } } static
void mdlOutputs ( SimStruct * S , int_T tid ) { real_T fvimbxewdo ; real_T
oswy5tazer ; real_T iwdwh41djf ; real_T datqelljdf ; real_T j1dhccl2er ;
real_T kyqcyh0rck ; real_T itmnht30kk ; real_T fzze1m1lro ; real_T ewc2c43fld
; real_T j02d3xwrmr ; real_T feh5yola42 ; real_T ouvkq3y043 ; int32_T
smplsInteg ; real_T cigjwaifn1 ; jrxlzum13n * _rtB ; ew4gpdq31k * _rtP ;
og2b2mtum5 * _rtDW ; _rtDW = ( ( og2b2mtum5 * ) ssGetRootDWork ( S ) ) ; _rtP
= ( ( ew4gpdq31k * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( jrxlzum13n * )
_ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 0 , tid ) ) { if (
ssIsSpecialSampleHit ( S , 2 , 0 , tid ) ) { _rtB -> hzzqwpds2j = _rtDW ->
bjcskgrt05 ; } if ( _rtDW -> l410sg5zpv != 0 ) { _rtDW -> gbgkgxsafq =
muDoubleScalarSin ( _rtP -> P_3 * ssGetTaskTime ( S , 0 ) ) ; _rtDW ->
gsm5zpqka5 = muDoubleScalarCos ( _rtP -> P_3 * ssGetTaskTime ( S , 0 ) ) ;
_rtDW -> l410sg5zpv = 0 ; } if ( _rtDW -> lt04wz3kw1 != 0 ) { _rtDW ->
i1siadxfat = muDoubleScalarSin ( _rtP -> P_10 * ssGetTaskTime ( S , 0 ) ) ;
_rtDW -> ed5zfvmsqz = muDoubleScalarCos ( _rtP -> P_10 * ssGetTaskTime ( S ,
0 ) ) ; _rtDW -> lt04wz3kw1 = 0 ; } if ( ssIsSpecialSampleHit ( S , 2 , 0 ,
tid ) ) { _rtB -> ey1aedl4hv = _rtDW -> l3pp1uxdln ; } _rtB -> n053ccfjfp = (
( ( _rtDW -> gbgkgxsafq * _rtP -> P_7 + _rtDW -> gsm5zpqka5 * _rtP -> P_6 ) *
_rtP -> P_5 + ( _rtDW -> gsm5zpqka5 * _rtP -> P_7 - _rtDW -> gbgkgxsafq *
_rtP -> P_6 ) * _rtP -> P_4 ) * _rtP -> P_1 + _rtP -> P_2 ) * _rtB ->
hzzqwpds2j + ( ( ( _rtDW -> i1siadxfat * _rtP -> P_14 + _rtDW -> ed5zfvmsqz *
_rtP -> P_13 ) * _rtP -> P_12 + ( _rtDW -> ed5zfvmsqz * _rtP -> P_14 - _rtDW
-> i1siadxfat * _rtP -> P_13 ) * _rtP -> P_11 ) * _rtP -> P_8 + _rtP -> P_9 )
* _rtB -> ey1aedl4hv ; ssCallAccelRunBlock ( S , 7 , 7 , SS_CALL_MDL_OUTPUTS
) ; } if ( ssIsSampleHit ( S , 1 , tid ) ) { RandSrc_U_D ( & kyqcyh0rck , &
_rtP -> P_16 , 1 , & _rtP -> P_17 , 1 , _rtDW -> iusuifohjm , 1 , 1 ) ; _rtB
-> ogwkxmckxq = muDoubleScalarCeil ( kyqcyh0rck ) ; } if ( ssIsSampleHit ( S
, 0 , tid ) ) { if ( ssIsSpecialSampleHit ( S , 2 , 0 , tid ) ) { _rtB ->
ch1gjwwztq = _rtDW -> knlr0yhwqq ; } itmnht30kk = ( _rtDW -> phxfqcb203 <
_rtP -> P_22 ) && ( _rtDW -> phxfqcb203 >= 0 ) ? _rtP -> P_20 : 0.0 ; if (
_rtDW -> phxfqcb203 >= _rtP -> P_21 - 1.0 ) { _rtDW -> phxfqcb203 = 0 ; }
else { _rtDW -> phxfqcb203 ++ ; } j1dhccl2er = ( _rtDW -> bd23rqa2xo < _rtP
-> P_26 ) && ( _rtDW -> bd23rqa2xo >= 0 ) ? _rtP -> P_24 : 0.0 ; if ( _rtDW
-> bd23rqa2xo >= _rtP -> P_25 - 1.0 ) { _rtDW -> bd23rqa2xo = 0 ; } else {
_rtDW -> bd23rqa2xo ++ ; } j02d3xwrmr = itmnht30kk + j1dhccl2er ; fzze1m1lro
= ( _rtDW -> jwncj5lzey < _rtP -> P_30 ) && ( _rtDW -> jwncj5lzey >= 0 ) ?
_rtP -> P_28 : 0.0 ; if ( _rtDW -> jwncj5lzey >= _rtP -> P_29 - 1.0 ) { _rtDW
-> jwncj5lzey = 0 ; } else { _rtDW -> jwncj5lzey ++ ; } feh5yola42 =
itmnht30kk + fzze1m1lro ; ouvkq3y043 = j1dhccl2er + fzze1m1lro ; ewc2c43fld =
( _rtDW -> ipd02wr3lj < _rtP -> P_34 ) && ( _rtDW -> ipd02wr3lj >= 0 ) ? _rtP
-> P_32 : 0.0 ; if ( _rtDW -> ipd02wr3lj >= _rtP -> P_33 - 1.0 ) { _rtDW ->
ipd02wr3lj = 0 ; } else { _rtDW -> ipd02wr3lj ++ ; } switch ( ( int32_T )
_rtB -> ch1gjwwztq ) { case 0 : itmnht30kk = _rtB -> jvcwwzufb3 ; break ;
case 1 : break ; case 2 : itmnht30kk = j1dhccl2er ; break ; case 3 :
itmnht30kk = j02d3xwrmr ; break ; case 4 : itmnht30kk = fzze1m1lro ; break ;
case 5 : itmnht30kk = feh5yola42 ; break ; case 6 : itmnht30kk = ouvkq3y043 ;
break ; case 7 : itmnht30kk = j02d3xwrmr + fzze1m1lro ; break ; case 8 :
itmnht30kk = ewc2c43fld ; break ; case 9 : itmnht30kk += ewc2c43fld ; break ;
case 10 : itmnht30kk = j1dhccl2er + ewc2c43fld ; break ; case 11 : itmnht30kk
= j02d3xwrmr + ewc2c43fld ; break ; case 12 : itmnht30kk = fzze1m1lro +
ewc2c43fld ; break ; case 13 : itmnht30kk = feh5yola42 + ewc2c43fld ; break ;
case 14 : itmnht30kk = ouvkq3y043 + ewc2c43fld ; break ; default : itmnht30kk
= _rtB -> gbpuebvspf ; break ; } if ( ssIsSpecialSampleHit ( S , 1 , 0 , tid
) ) { _rtB -> iy32qtpv3u = itmnht30kk ; } } if ( ssIsSampleHit ( S , 1 , tid
) ) { itmnht30kk = 0.0 ; j1dhccl2er = 0.0 ; j02d3xwrmr = 0.0 ; _rtDW ->
g2y0oiaaxq [ _rtDW -> jlt4j1ea1r ] = _rtB -> ogwkxmckxq ; if ( _rtDW ->
jlt4j1ea1r == 16 ) { _rtDW -> jlt4j1ea1r = 0 ; } else { _rtDW -> jlt4j1ea1r
++ ; } if ( _rtDW -> opr3odmnd2 < 16 ) { _rtDW -> opr3odmnd2 ++ ; } else { if
( _rtDW -> jhl4mjiver ) { j1dhccl2er = 1.0 ; if ( _rtDW -> g2y0oiaaxq [ _rtDW
-> jlt4j1ea1r ] != _rtB -> iy32qtpv3u ) { itmnht30kk = 1.0 ; } } } _rtDW ->
h22opaprmm += j1dhccl2er ; _rtDW -> bmhlf0kzcm += itmnht30kk ; if ( _rtDW ->
h22opaprmm > 0.0 ) { j02d3xwrmr = _rtDW -> bmhlf0kzcm / _rtDW -> h22opaprmm ;
} _rtB -> blytzuwrcl [ 0U ] = j02d3xwrmr ; _rtB -> blytzuwrcl [ 1U ] = _rtDW
-> bmhlf0kzcm ; _rtB -> blytzuwrcl [ 2U ] = _rtDW -> h22opaprmm ;
ssCallAccelRunBlock ( S , 7 , 30 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , tid ) ) { if ( _rtDW -> f5y2hmgdie == 0 ) { _rtB -> nadknklnh3 =
_rtB -> ogwkxmckxq ; } else { _rtB -> nadknklnh3 = _rtDW -> mb23qjo0ed ; } if
( _rtDW -> lijl4veot5 == 0 ) { _rtB -> b2c2rilxke = _rtB -> ogwkxmckxq ; }
else { _rtB -> b2c2rilxke = _rtDW -> hystmkl4hv ; } if ( _rtDW -> esa5eejvtg
== 0 ) { _rtB -> nnpmle30v2 = _rtB -> ogwkxmckxq ; } else { _rtB ->
nnpmle30v2 = _rtDW -> o2laygc4pj ; } if ( _rtDW -> jznz54vwad == 0 ) {
kyqcyh0rck = _rtB -> ogwkxmckxq ; } else { kyqcyh0rck = _rtDW -> htm4zhsddn ;
} } kyqcyh0rck += ( _rtP -> P_46 * _rtDW -> iqmttsgpy4 [ 0 ] + _rtP -> P_40 *
_rtDW -> b5xqcwsvpa [ 0 ] ) + _rtP -> P_45 * _rtDW -> ot4zbi2yjr ; if (
ssIsSpecialSampleHit ( S , 2 , 1 , tid ) ) { _rtB -> h11dfiqumt = kyqcyh0rck
; } } if ( ssIsSampleHit ( S , 2 , tid ) ) { { uint32_T iLeft ;
Fig326_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , _rtB -> h11dfiqumt ,
_rtP -> P_47 , 15U ) ; _rtB -> dgnxyk34os = _rtP -> P_48 [ iLeft ] ; } {
uint32_T iLeft ; Fig326_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , _rtB
-> h11dfiqumt , _rtP -> P_49 , 15U ) ; _rtB -> oa35m5e2pz = _rtP -> P_50 [
iLeft ] ; } } if ( ssIsSampleHit ( S , 0 , tid ) ) { if ( _rtDW -> maaf4uejih
!= 0 ) { _rtDW -> gy02vnwilg = muDoubleScalarSin ( _rtP -> P_53 *
ssGetTaskTime ( S , 0 ) ) ; _rtDW -> pmsdeid1mj = muDoubleScalarCos ( _rtP ->
P_53 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> maaf4uejih = 0 ; } itmnht30kk = (
( _rtDW -> gy02vnwilg * _rtP -> P_57 + _rtDW -> pmsdeid1mj * _rtP -> P_56 ) *
_rtP -> P_55 + ( _rtDW -> pmsdeid1mj * _rtP -> P_57 - _rtDW -> gy02vnwilg *
_rtP -> P_56 ) * _rtP -> P_54 ) * _rtP -> P_51 + _rtP -> P_52 ; RandSrc_GZ_D
( & cigjwaifn1 , & _rtP -> P_58 , 1 , & _rtP -> P_59 , 1 , _rtDW ->
d3jd3vbbrd , 1 , 1 ) ; _rtDW -> dtv05qev3p = muDoubleScalarSqrt ( _rtP ->
P_61 * 0.002 / ( muDoubleScalarPower ( 10.0 , ( _rtP -> P_60 +
3.0102999566398121 ) / 10.0 ) * 2.0E-6 ) ) ; cigjwaifn1 = _rtDW -> dtv05qev3p
* cigjwaifn1 / 1.4142135623730951 + _rtB -> n053ccfjfp ; itmnht30kk *=
cigjwaifn1 ; if ( ssIsSampleHit ( S , 0 , tid ) ) { smplsInteg = _rtDW ->
p5bnrxbe0k ; if ( _rtDW -> m0fny0gozu < 0 ) { _rtDW -> m0fny0gozu ++ ; } else
{ _rtDW -> fw0e3vuztv += itmnht30kk ; smplsInteg = _rtDW -> p5bnrxbe0k + 1 ;
_rtDW -> p5bnrxbe0k ++ ; } if ( smplsInteg == 2000 ) { _rtDW -> pika52konh =
_rtDW -> fw0e3vuztv ; _rtDW -> fw0e3vuztv = 0.0 ; _rtDW -> p5bnrxbe0k = 0 ; }
} if ( _rtDW -> ktd4nh1i1g != 0 ) { _rtDW -> fv2y5zeqpe = muDoubleScalarSin (
_rtP -> P_64 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> locc532n0v =
muDoubleScalarCos ( _rtP -> P_64 * ssGetTaskTime ( S , 0 ) ) ; _rtDW ->
ktd4nh1i1g = 0 ; } cigjwaifn1 *= ( ( _rtDW -> fv2y5zeqpe * _rtP -> P_68 +
_rtDW -> locc532n0v * _rtP -> P_67 ) * _rtP -> P_66 + ( _rtDW -> locc532n0v *
_rtP -> P_68 - _rtDW -> fv2y5zeqpe * _rtP -> P_67 ) * _rtP -> P_65 ) * _rtP
-> P_62 + _rtP -> P_63 ; if ( ssIsSampleHit ( S , 0 , tid ) ) { smplsInteg =
_rtDW -> mfcnxstsmw ; if ( _rtDW -> h1lbkakwji < 0 ) { _rtDW -> h1lbkakwji ++
; } else { _rtDW -> aixuz1pnwn += cigjwaifn1 ; smplsInteg = _rtDW ->
mfcnxstsmw + 1 ; _rtDW -> mfcnxstsmw ++ ; } if ( smplsInteg == 2000 ) { _rtDW
-> dibjlvagzj = _rtDW -> aixuz1pnwn ; _rtDW -> aixuz1pnwn = 0.0 ; _rtDW ->
mfcnxstsmw = 0 ; } } } if ( ssIsSampleHit ( S , 2 , tid ) ) { if (
ssIsSampleHit ( S , 2 , tid ) ) { fvimbxewdo = _rtDW -> pika52konh ; } if (
ssIsSampleHit ( S , 2 , tid ) ) { oswy5tazer = _rtDW -> dibjlvagzj ; } {
uint32_T iLeft ; Fig326_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) ,
fvimbxewdo , _rtP -> P_69 , 3U ) ; iwdwh41djf = _rtP -> P_70 [ iLeft ] ; } {
uint32_T iLeft ; Fig326_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) ,
oswy5tazer , _rtP -> P_71 , 3U ) ; datqelljdf = _rtP -> P_72 [ iLeft ] ; } {
uint32_T iRowIndex1 , iColumnIndex1 ; Fig326_acc_BINARYSEARCH_real_T_Near_iL
( & ( iRowIndex1 ) , iwdwh41djf , _rtP -> P_73 , 3U ) ;
Fig326_acc_BINARYSEARCH_real_T_Near_iL ( & ( iColumnIndex1 ) , datqelljdf ,
_rtP -> P_74 , 3U ) ; _rtB -> fwizrt5npq = _rtP -> P_75 [ iRowIndex1 + 4 *
iColumnIndex1 ] ; } } UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID3
( SimStruct * S , int_T tid ) { jrxlzum13n * _rtB ; ew4gpdq31k * _rtP ; _rtP
= ( ( ew4gpdq31k * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( jrxlzum13n * )
_ssGetBlockIO ( S ) ) ; _rtB -> jvcwwzufb3 = _rtP -> P_19 ; _rtB ->
gbpuebvspf = _rtP -> P_36 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T HoldSine ;
jrxlzum13n * _rtB ; ew4gpdq31k * _rtP ; og2b2mtum5 * _rtDW ; _rtDW = ( (
og2b2mtum5 * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( ew4gpdq31k * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( jrxlzum13n * ) _ssGetBlockIO ( S ) ) ;
if ( ssIsSampleHit ( S , 2 , tid ) ) { _rtDW -> bjcskgrt05 = _rtB ->
dgnxyk34os ; } if ( ssIsSampleHit ( S , 0 , tid ) ) { HoldSine = _rtDW ->
gbgkgxsafq ; _rtDW -> gbgkgxsafq = _rtDW -> gbgkgxsafq * _rtP -> P_5 + _rtDW
-> gsm5zpqka5 * _rtP -> P_4 ; _rtDW -> gsm5zpqka5 = _rtDW -> gsm5zpqka5 *
_rtP -> P_5 - HoldSine * _rtP -> P_4 ; HoldSine = _rtDW -> i1siadxfat ; _rtDW
-> i1siadxfat = _rtDW -> i1siadxfat * _rtP -> P_12 + _rtDW -> ed5zfvmsqz *
_rtP -> P_11 ; _rtDW -> ed5zfvmsqz = _rtDW -> ed5zfvmsqz * _rtP -> P_12 -
HoldSine * _rtP -> P_11 ; } if ( ssIsSampleHit ( S , 2 , tid ) ) { _rtDW ->
l3pp1uxdln = _rtB -> oa35m5e2pz ; _rtDW -> knlr0yhwqq = _rtB -> fwizrt5npq ;
} if ( ssIsSampleHit ( S , 1 , tid ) ) { if ( _rtDW -> f5y2hmgdie == 0 ) {
_rtDW -> mb23qjo0ed = _rtB -> ogwkxmckxq ; } _rtDW -> f5y2hmgdie ++ ; if (
_rtDW -> f5y2hmgdie == 4 ) { _rtDW -> f5y2hmgdie = 0 ; } _rtDW -> b5xqcwsvpa
[ 0U ] = _rtDW -> b5xqcwsvpa [ 1U ] ; _rtDW -> b5xqcwsvpa [ 1 ] = _rtB ->
nadknklnh3 ; if ( ssIsSampleHit ( S , 1 , tid ) ) { if ( _rtDW -> lijl4veot5
== 0 ) { _rtDW -> hystmkl4hv = _rtB -> ogwkxmckxq ; } _rtDW -> lijl4veot5 ++
; if ( _rtDW -> lijl4veot5 == 4 ) { _rtDW -> lijl4veot5 = 0 ; } if ( _rtDW ->
esa5eejvtg == 0 ) { _rtDW -> o2laygc4pj = _rtB -> ogwkxmckxq ; } _rtDW ->
esa5eejvtg ++ ; if ( _rtDW -> esa5eejvtg == 4 ) { _rtDW -> esa5eejvtg = 0 ; }
if ( _rtDW -> jznz54vwad == 0 ) { _rtDW -> htm4zhsddn = _rtB -> ogwkxmckxq ;
} _rtDW -> jznz54vwad ++ ; if ( _rtDW -> jznz54vwad == 4 ) { _rtDW ->
jznz54vwad = 0 ; } } _rtDW -> ot4zbi2yjr = _rtB -> nnpmle30v2 ; _rtDW ->
iqmttsgpy4 [ 0U ] = _rtDW -> iqmttsgpy4 [ 1U ] ; _rtDW -> iqmttsgpy4 [ 1U ] =
_rtDW -> iqmttsgpy4 [ 2U ] ; _rtDW -> iqmttsgpy4 [ 2 ] = _rtB -> b2c2rilxke ;
} if ( ssIsSampleHit ( S , 0 , tid ) ) { HoldSine = _rtDW -> gy02vnwilg ;
_rtDW -> gy02vnwilg = _rtDW -> gy02vnwilg * _rtP -> P_55 + _rtDW ->
pmsdeid1mj * _rtP -> P_54 ; _rtDW -> pmsdeid1mj = _rtDW -> pmsdeid1mj * _rtP
-> P_55 - HoldSine * _rtP -> P_54 ; HoldSine = _rtDW -> fv2y5zeqpe ; _rtDW ->
fv2y5zeqpe = _rtDW -> fv2y5zeqpe * _rtP -> P_66 + _rtDW -> locc532n0v * _rtP
-> P_65 ; _rtDW -> locc532n0v = _rtDW -> locc532n0v * _rtP -> P_66 - HoldSine
* _rtP -> P_65 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal
( S , 0 , 701304320U ) ; ssSetChecksumVal ( S , 1 , 311245901U ) ;
ssSetChecksumVal ( S , 2 , 835817445U ) ; ssSetChecksumVal ( S , 3 ,
607501608U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.6" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
og2b2mtum5 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( jrxlzum13n ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
ew4gpdq31k ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & f0i0cjy5ej ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void
mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
