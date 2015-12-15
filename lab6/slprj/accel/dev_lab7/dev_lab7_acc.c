#include "__cf_dev_lab7.h"
#include <math.h>
#include "dev_lab7_acc.h"
#include "dev_lab7_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
void dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( uint32_T * piLeft , real_T u
, const real_T * pData , uint32_T iHi ) { uint32_T iRght ; * piLeft = 0U ;
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
void mdlOutputs ( SimStruct * S , int_T tid ) { real_T bz13nfv5mb ; real_T
jenllzyhil ; real_T pad3gmq0qi ; real_T lqto0dcijk ; real_T cpnazru4ny ;
real_T ixmh4gb3df ; real_T ratio ; real_T e05vw1111z ; real_T ehvg2jhmzp ;
int32_T smplsInteg ; real_T cigjwaifn1 ; co5gar2uno * _rtB ; mvbqr0wtxd *
_rtP ; iycc0zfqd5 * _rtDW ; _rtDW = ( ( iycc0zfqd5 * ) ssGetRootDWork ( S ) )
; _rtP = ( ( mvbqr0wtxd * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( co5gar2uno
* ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 0 , tid ) ) {
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , tid ) ) { RandSrc_U_D ( & e05vw1111z , & _rtP -> P_0
, 1 , & _rtP -> P_1 , 1 , _rtDW -> cognva34ow , 1 , 1 ) ; _rtB -> mheicpc1xe
= muDoubleScalarCeil ( e05vw1111z ) ; } if ( ssIsSampleHit ( S , 0 , tid ) )
{ if ( ssIsSpecialSampleHit ( S , 2 , 0 , tid ) ) { _rtB -> kfd51wo2wu =
_rtDW -> mid43ech3c ; } e05vw1111z = ( _rtDW -> fs1apyfxv3 < _rtP -> P_6 ) &&
( _rtDW -> fs1apyfxv3 >= 0 ) ? _rtP -> P_4 : 0.0 ; if ( _rtDW -> fs1apyfxv3
>= _rtP -> P_5 - 1.0 ) { _rtDW -> fs1apyfxv3 = 0 ; } else { _rtDW ->
fs1apyfxv3 ++ ; } ehvg2jhmzp = ( _rtDW -> jsprpznjsv < _rtP -> P_10 ) && (
_rtDW -> jsprpznjsv >= 0 ) ? _rtP -> P_8 : 0.0 ; if ( _rtDW -> jsprpznjsv >=
_rtP -> P_9 - 1.0 ) { _rtDW -> jsprpznjsv = 0 ; } else { _rtDW -> jsprpznjsv
++ ; } switch ( ( int32_T ) _rtB -> kfd51wo2wu ) { case 0 : e05vw1111z = _rtB
-> b0zzzsbziv ; break ; case 1 : break ; case 2 : e05vw1111z = ehvg2jhmzp ;
break ; default : e05vw1111z += ehvg2jhmzp ; break ; } if (
ssIsSpecialSampleHit ( S , 1 , 0 , tid ) ) { _rtB -> o3ta12ismp = e05vw1111z
; } } if ( ssIsSampleHit ( S , 1 , tid ) ) { e05vw1111z = 0.0 ; ehvg2jhmzp =
0.0 ; ratio = 0.0 ; _rtDW -> amahe1io43 [ _rtDW -> iqvxnbaj4g ] = _rtB ->
mheicpc1xe ; if ( _rtDW -> iqvxnbaj4g == 6 ) { _rtDW -> iqvxnbaj4g = 0 ; }
else { _rtDW -> iqvxnbaj4g ++ ; } if ( _rtDW -> owuobecm3y < 6 ) { _rtDW ->
owuobecm3y ++ ; } else { if ( _rtDW -> jz0daj5ki5 ) { ehvg2jhmzp = 1.0 ; if (
_rtDW -> amahe1io43 [ _rtDW -> iqvxnbaj4g ] != _rtB -> o3ta12ismp ) {
e05vw1111z = 1.0 ; } } } _rtDW -> enlog4tcgd += ehvg2jhmzp ; _rtDW ->
bm2v1ffu1m += e05vw1111z ; if ( _rtDW -> enlog4tcgd > 0.0 ) { ratio = _rtDW
-> bm2v1ffu1m / _rtDW -> enlog4tcgd ; } _rtB -> lqokkdcoil [ 0U ] = ratio ;
_rtB -> lqokkdcoil [ 1U ] = _rtDW -> bm2v1ffu1m ; _rtB -> lqokkdcoil [ 2U ] =
_rtDW -> enlog4tcgd ; ssCallAccelRunBlock ( S , 1 , 11 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 1 , 12 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 0 , tid ) ) { if ( ssIsSpecialSampleHit ( S , 1 , 0 , tid
) ) { _rtB -> n4in1ql04u = _rtDW -> fehuh4zhrz ; } { uint32_T iLeft ;
dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , _rtB -> n4in1ql04u ,
_rtP -> P_13 , 3U ) ; bz13nfv5mb = _rtP -> P_14 [ iLeft ] ; } if ( _rtDW ->
gj1vc1msl0 != 0 ) { _rtDW -> l0yyllc4fz = muDoubleScalarSin ( _rtP -> P_17 *
ssGetTaskTime ( S , 0 ) ) ; _rtDW -> a1tzbq3xxl = muDoubleScalarCos ( _rtP ->
P_17 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> gj1vc1msl0 = 0 ; } ehvg2jhmzp = (
( ( _rtDW -> l0yyllc4fz * _rtP -> P_21 + _rtDW -> a1tzbq3xxl * _rtP -> P_20 )
* _rtP -> P_19 + ( _rtDW -> a1tzbq3xxl * _rtP -> P_21 - _rtDW -> l0yyllc4fz *
_rtP -> P_20 ) * _rtP -> P_18 ) * _rtP -> P_15 + _rtP -> P_16 ) * bz13nfv5mb
; if ( _rtDW -> plr1a2gssn != 0 ) { _rtDW -> kjppf5hgtf = muDoubleScalarSin (
_rtP -> P_24 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> j2u2o3513d =
muDoubleScalarCos ( _rtP -> P_24 * ssGetTaskTime ( S , 0 ) ) ; _rtDW ->
plr1a2gssn = 0 ; } e05vw1111z = ( ( _rtDW -> kjppf5hgtf * _rtP -> P_28 +
_rtDW -> j2u2o3513d * _rtP -> P_27 ) * _rtP -> P_26 + ( _rtDW -> j2u2o3513d *
_rtP -> P_28 - _rtDW -> kjppf5hgtf * _rtP -> P_27 ) * _rtP -> P_25 ) * _rtP
-> P_22 + _rtP -> P_23 ; { uint32_T iLeft ;
dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , _rtB -> n4in1ql04u ,
_rtP -> P_29 , 3U ) ; jenllzyhil = _rtP -> P_30 [ iLeft ] ; } _rtB ->
obyii5ppuk = e05vw1111z * jenllzyhil + ehvg2jhmzp ; if ( ssIsSpecialSampleHit
( S , 2 , 0 , tid ) ) { _rtB -> atpl5de22t = _rtDW -> fyunq1bp3r ; }
ssCallAccelRunBlock ( S , 1 , 22 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , tid ) ) { if ( _rtDW -> hxyq0mzfj0 == 0 ) { _rtB ->
bbvpt3fig0 = _rtB -> mheicpc1xe ; } else { _rtB -> bbvpt3fig0 = _rtDW ->
ji2bhgkln1 ; } if ( _rtDW -> ndtujtqlbh == 0 ) { e05vw1111z = _rtB ->
mheicpc1xe ; } else { e05vw1111z = _rtDW -> kqoq5uhc4h ; } _rtB -> j42ruxlxmi
= _rtP -> P_35 * _rtDW -> jvbpw4xait + e05vw1111z ; } if ( ssIsSampleHit ( S
, 0 , tid ) ) { if ( _rtDW -> jxn2lsoxxb != 0 ) { _rtDW -> gace2bfytg =
muDoubleScalarSin ( _rtP -> P_38 * ssGetTaskTime ( S , 0 ) ) ; _rtDW ->
pchiqw4btv = muDoubleScalarCos ( _rtP -> P_38 * ssGetTaskTime ( S , 0 ) ) ;
_rtDW -> jxn2lsoxxb = 0 ; } e05vw1111z = ( ( _rtDW -> gace2bfytg * _rtP ->
P_42 + _rtDW -> pchiqw4btv * _rtP -> P_41 ) * _rtP -> P_40 + ( _rtDW ->
pchiqw4btv * _rtP -> P_42 - _rtDW -> gace2bfytg * _rtP -> P_41 ) * _rtP ->
P_39 ) * _rtP -> P_36 + _rtP -> P_37 ; RandSrc_GZ_D ( & cigjwaifn1 , & _rtP
-> P_43 , 1 , & _rtP -> P_44 , 1 , _rtDW -> fieiqzxkt5 , 1 , 1 ) ; _rtDW ->
ina0upln41 = muDoubleScalarSqrt ( _rtP -> P_45 ) ; cigjwaifn1 = _rtDW ->
ina0upln41 * cigjwaifn1 + _rtB -> obyii5ppuk ; e05vw1111z *= cigjwaifn1 ; if
( ssIsSampleHit ( S , 0 , tid ) ) { smplsInteg = _rtDW -> g3nlzybcfv ; if (
_rtDW -> ahepqdyksq < 0 ) { _rtDW -> ahepqdyksq ++ ; } else { _rtDW ->
in05qn1wgm += e05vw1111z ; smplsInteg = _rtDW -> g3nlzybcfv + 1 ; _rtDW ->
g3nlzybcfv ++ ; } if ( smplsInteg == 1000 ) { _rtDW -> ldhjc00ntq = _rtDW ->
in05qn1wgm ; _rtDW -> in05qn1wgm = 0.0 ; _rtDW -> g3nlzybcfv = 0 ; } } if (
_rtDW -> anqiega1c3 != 0 ) { _rtDW -> osvofguzys = muDoubleScalarSin ( _rtP
-> P_48 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> ipvl2rh3k5 = muDoubleScalarCos
( _rtP -> P_48 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> anqiega1c3 = 0 ; }
cigjwaifn1 *= ( ( _rtDW -> osvofguzys * _rtP -> P_52 + _rtDW -> ipvl2rh3k5 *
_rtP -> P_51 ) * _rtP -> P_50 + ( _rtDW -> ipvl2rh3k5 * _rtP -> P_52 - _rtDW
-> osvofguzys * _rtP -> P_51 ) * _rtP -> P_49 ) * _rtP -> P_46 + _rtP -> P_47
; if ( ssIsSampleHit ( S , 0 , tid ) ) { smplsInteg = _rtDW -> omg5ievcub ;
if ( _rtDW -> elyjwa3ywi < 0 ) { _rtDW -> elyjwa3ywi ++ ; } else { _rtDW ->
m2m3e4nf0i += cigjwaifn1 ; smplsInteg = _rtDW -> omg5ievcub + 1 ; _rtDW ->
omg5ievcub ++ ; } if ( smplsInteg == 1000 ) { _rtDW -> jm4mglu3hd = _rtDW ->
m2m3e4nf0i ; _rtDW -> m2m3e4nf0i = 0.0 ; _rtDW -> omg5ievcub = 0 ; } } } if (
ssIsSampleHit ( S , 2 , tid ) ) { if ( ssIsSampleHit ( S , 2 , tid ) ) {
pad3gmq0qi = _rtDW -> ldhjc00ntq ; } if ( ssIsSampleHit ( S , 2 , tid ) ) {
lqto0dcijk = _rtDW -> jm4mglu3hd ; } { uint32_T iLeft ;
dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , pad3gmq0qi , _rtP ->
P_53 , 2U ) ; cpnazru4ny = _rtP -> P_54 [ iLeft ] ; } { uint32_T iLeft ;
dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , lqto0dcijk , _rtP ->
P_55 , 2U ) ; ixmh4gb3df = _rtP -> P_56 [ iLeft ] ; } { uint32_T iRowIndex1 ,
iColumnIndex1 ; dev_lab7_acc_BINARYSEARCH_real_T_Near_iL ( & ( iRowIndex1 ) ,
cpnazru4ny , _rtP -> P_57 , 2U ) ; dev_lab7_acc_BINARYSEARCH_real_T_Near_iL (
& ( iColumnIndex1 ) , ixmh4gb3df , _rtP -> P_58 , 2U ) ; _rtB -> gvnhuyndv3 =
_rtP -> P_59 [ iRowIndex1 + 3 * iColumnIndex1 ] ; } } UNUSED_PARAMETER ( tid
) ; } static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) { co5gar2uno *
_rtB ; mvbqr0wtxd * _rtP ; _rtP = ( ( mvbqr0wtxd * ) ssGetDefaultParam ( S )
) ; _rtB = ( ( co5gar2uno * ) _ssGetBlockIO ( S ) ) ; _rtB -> b0zzzsbziv =
_rtP -> P_3 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T HoldSine ;
co5gar2uno * _rtB ; mvbqr0wtxd * _rtP ; iycc0zfqd5 * _rtDW ; _rtDW = ( (
iycc0zfqd5 * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( mvbqr0wtxd * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( co5gar2uno * ) _ssGetBlockIO ( S ) ) ;
if ( ssIsSampleHit ( S , 0 , tid ) ) { ssCallAccelRunBlock ( S , 1 , 0 ,
SS_CALL_MDL_UPDATE ) ; } if ( ssIsSampleHit ( S , 2 , tid ) ) { _rtDW ->
mid43ech3c = _rtB -> gvnhuyndv3 ; } if ( ssIsSampleHit ( S , 1 , tid ) ) {
_rtDW -> fehuh4zhrz = _rtB -> j42ruxlxmi ; } if ( ssIsSampleHit ( S , 0 , tid
) ) { HoldSine = _rtDW -> l0yyllc4fz ; _rtDW -> l0yyllc4fz = _rtDW ->
l0yyllc4fz * _rtP -> P_19 + _rtDW -> a1tzbq3xxl * _rtP -> P_18 ; _rtDW ->
a1tzbq3xxl = _rtDW -> a1tzbq3xxl * _rtP -> P_19 - HoldSine * _rtP -> P_18 ;
HoldSine = _rtDW -> kjppf5hgtf ; _rtDW -> kjppf5hgtf = _rtDW -> kjppf5hgtf *
_rtP -> P_26 + _rtDW -> j2u2o3513d * _rtP -> P_25 ; _rtDW -> j2u2o3513d =
_rtDW -> j2u2o3513d * _rtP -> P_26 - HoldSine * _rtP -> P_25 ; } if (
ssIsSampleHit ( S , 2 , tid ) ) { _rtDW -> fyunq1bp3r = _rtB -> gvnhuyndv3 ;
} if ( ssIsSampleHit ( S , 1 , tid ) ) { _rtDW -> jvbpw4xait = _rtB ->
bbvpt3fig0 ; if ( ssIsSampleHit ( S , 1 , tid ) ) { if ( _rtDW -> hxyq0mzfj0
== 0 ) { _rtDW -> ji2bhgkln1 = _rtB -> mheicpc1xe ; } _rtDW -> hxyq0mzfj0 ++
; if ( _rtDW -> hxyq0mzfj0 == 2 ) { _rtDW -> hxyq0mzfj0 = 0 ; } if ( _rtDW ->
ndtujtqlbh == 0 ) { _rtDW -> kqoq5uhc4h = _rtB -> mheicpc1xe ; } _rtDW ->
ndtujtqlbh ++ ; if ( _rtDW -> ndtujtqlbh == 2 ) { _rtDW -> ndtujtqlbh = 0 ; }
} } if ( ssIsSampleHit ( S , 0 , tid ) ) { HoldSine = _rtDW -> gace2bfytg ;
_rtDW -> gace2bfytg = _rtDW -> gace2bfytg * _rtP -> P_40 + _rtDW ->
pchiqw4btv * _rtP -> P_39 ; _rtDW -> pchiqw4btv = _rtDW -> pchiqw4btv * _rtP
-> P_40 - HoldSine * _rtP -> P_39 ; HoldSine = _rtDW -> osvofguzys ; _rtDW ->
osvofguzys = _rtDW -> osvofguzys * _rtP -> P_50 + _rtDW -> ipvl2rh3k5 * _rtP
-> P_49 ; _rtDW -> ipvl2rh3k5 = _rtDW -> ipvl2rh3k5 * _rtP -> P_50 - HoldSine
* _rtP -> P_49 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal
( S , 0 , 340649926U ) ; ssSetChecksumVal ( S , 1 , 1341717814U ) ;
ssSetChecksumVal ( S , 2 , 2370053180U ) ; ssSetChecksumVal ( S , 3 ,
194639184U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.6" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
iycc0zfqd5 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( co5gar2uno ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
mvbqr0wtxd ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & ojbj0mxp5y ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void
mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
