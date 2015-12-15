#include "__cf_Fig322.h"
#include <math.h>
#include "Fig322_acc.h"
#include "Fig322_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
void Fig322_acc_BINARYSEARCH_real_T_Near_iL ( uint32_T * piLeft , real_T u ,
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
void mdlOutputs ( SimStruct * S , int_T tid ) { real_T aemeay2o1r ; real_T
igumtauha5 ; real_T cjn2ssprvi ; real_T ratio ; real_T mcwsbff2xq ; real_T
kmlhlhef1y ; real_T ofrsvndla4 ; int32_T smplsInteg ; real_T faapseswfi ;
real_T p3xvrsrqbq ; boolean_T fdusals3sg ; boolean_T njr1wmr5i5 ; boolean_T
fwgjk3as20 ; boolean_T f5nmir1vmq ; boolean_T hfdgqiyhg5 ; fedc24kpyi * _rtB
; becphodmrm * _rtP ; i5c3vxuxau * _rtDW ; _rtDW = ( ( i5c3vxuxau * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( becphodmrm * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( fedc24kpyi * ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S ,
1 , tid ) ) { RandSrc_U_D ( & mcwsbff2xq , & _rtP -> P_0 , 1 , & _rtP -> P_1
, 1 , _rtDW -> d311mkkoaa , 1 , 1 ) ; _rtB -> egyhkdbxcz = muDoubleScalarCeil
( mcwsbff2xq ) ; } if ( ssIsSampleHit ( S , 0 , tid ) ) { if (
ssIsSpecialSampleHit ( S , 2 , 0 , tid ) ) { _rtB -> eorrvn3ccu = _rtDW ->
fmwdwfn5wf ; } { uint32_T iLeft ; Fig322_acc_BINARYSEARCH_real_T_Near_iL ( &
( iLeft ) , _rtB -> eorrvn3ccu , _rtP -> P_3 , 3U ) ; aemeay2o1r = _rtP ->
P_4 [ iLeft ] ; } mcwsbff2xq = ( _rtDW -> dgzrgt3mfp < _rtP -> P_8 ) && (
_rtDW -> dgzrgt3mfp >= 0 ) ? _rtP -> P_6 : 0.0 ; if ( _rtDW -> dgzrgt3mfp >=
_rtP -> P_7 - 1.0 ) { _rtDW -> dgzrgt3mfp = 0 ; } else { _rtDW -> dgzrgt3mfp
++ ; } kmlhlhef1y = ( _rtDW -> linxugidmi < _rtP -> P_12 ) && ( _rtDW ->
linxugidmi >= 0 ) ? _rtP -> P_10 : 0.0 ; if ( _rtDW -> linxugidmi >= _rtP ->
P_11 - 1.0 ) { _rtDW -> linxugidmi = 0 ; } else { _rtDW -> linxugidmi ++ ; }
switch ( ( int32_T ) aemeay2o1r ) { case 0 : cjn2ssprvi = _rtB -> kxpqfyui0x
; break ; case 1 : cjn2ssprvi = mcwsbff2xq ; break ; case 2 : cjn2ssprvi =
kmlhlhef1y ; break ; default : cjn2ssprvi = _rtB -> dbvprqiz0k ; break ; } if
( ssIsSpecialSampleHit ( S , 1 , 0 , tid ) ) { _rtB -> jo1kgktok5 =
cjn2ssprvi ; } } if ( ssIsSampleHit ( S , 1 , tid ) ) { mcwsbff2xq = 0.0 ;
kmlhlhef1y = 0.0 ; ratio = 0.0 ; _rtDW -> lre1uqxtnu [ _rtDW -> hor1qgyl4w ]
= _rtB -> egyhkdbxcz ; if ( _rtDW -> hor1qgyl4w == 6 ) { _rtDW -> hor1qgyl4w
= 0 ; } else { _rtDW -> hor1qgyl4w ++ ; } if ( _rtDW -> c2ryi04j0s < 6 ) {
_rtDW -> c2ryi04j0s ++ ; } else { if ( _rtDW -> autfcyfhkp ) { kmlhlhef1y =
1.0 ; if ( _rtDW -> lre1uqxtnu [ _rtDW -> hor1qgyl4w ] != _rtB -> jo1kgktok5
) { mcwsbff2xq = 1.0 ; } } } _rtDW -> prmpwmica2 += kmlhlhef1y ; _rtDW ->
cq3v4o1vh2 += mcwsbff2xq ; if ( _rtDW -> prmpwmica2 > 0.0 ) { ratio = _rtDW
-> cq3v4o1vh2 / _rtDW -> prmpwmica2 ; } _rtB -> cktexkgltx [ 0U ] = ratio ;
_rtB -> cktexkgltx [ 1U ] = _rtDW -> cq3v4o1vh2 ; _rtB -> cktexkgltx [ 2U ] =
_rtDW -> prmpwmica2 ; ssCallAccelRunBlock ( S , 0 , 11 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 0 , 12 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 0 , tid ) ) { if ( ssIsSpecialSampleHit ( S , 1 , 0 , tid
) ) { _rtB -> cg42p33ma0 = _rtDW -> oehkgucdwq ; } { real_T * y = ( real_T *
) & cjn2ssprvi ; real_T time = ssGetTaskTime ( S , 0 ) ; * y = time ; } _rtB
-> k0sku0t2b3 = muDoubleScalarCos ( ( _rtP -> P_17 * cjn2ssprvi + _rtB ->
i3iufndyvs ) + _rtP -> P_18 * _rtB -> cg42p33ma0 ) * _rtP -> P_19 ;
ssCallAccelRunBlock ( S , 0 , 21 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 0 , 22 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsSampleHit ( S , 1 , tid ) ) { if ( _rtDW -> lu5hhot51e == 0 ) { _rtB ->
lpbo2dnu0b = _rtB -> egyhkdbxcz ; } else { _rtB -> lpbo2dnu0b = _rtDW ->
oxjn22yyoo ; } if ( _rtDW -> nv1tjlyya2 == 0 ) { mcwsbff2xq = _rtB ->
egyhkdbxcz ; } else { mcwsbff2xq = _rtDW -> d0olzpztcq ; } igumtauha5 = _rtP
-> P_23 * _rtDW -> fnpwuawce2 + mcwsbff2xq ; { uint32_T iLeft ;
Fig322_acc_BINARYSEARCH_real_T_Near_iL ( & ( iLeft ) , igumtauha5 , _rtP ->
P_24 , 3U ) ; _rtB -> kyi3aspvcm = _rtP -> P_25 [ iLeft ] ; } } if (
ssIsSampleHit ( S , 0 , tid ) ) { RandSrc_GZ_D ( & cjn2ssprvi , & _rtP ->
P_26 , 1 , & _rtP -> P_27 , 1 , _rtDW -> hrunin3pbn , 1 , 1 ) ; _rtDW ->
huj430awvh = muDoubleScalarSqrt ( _rtP -> P_29 * 0.0005 / (
muDoubleScalarPower ( 10.0 , ( _rtP -> P_28 + 3.0102999566398121 ) / 10.0 ) *
5.0E-7 ) ) ; ofrsvndla4 = _rtDW -> huj430awvh * cjn2ssprvi /
1.4142135623730951 + _rtB -> k0sku0t2b3 ; if ( _rtDW -> f5ekitwifw != 0 ) {
_rtDW -> hpya1t2gs1 = muDoubleScalarSin ( _rtP -> P_32 * ssGetTaskTime ( S ,
0 ) ) ; _rtDW -> hxamq1hdtu = muDoubleScalarCos ( _rtP -> P_32 *
ssGetTaskTime ( S , 0 ) ) ; _rtDW -> f5ekitwifw = 0 ; } cjn2ssprvi = ( (
_rtDW -> hpya1t2gs1 * _rtP -> P_36 + _rtDW -> hxamq1hdtu * _rtP -> P_35 ) *
_rtP -> P_34 + ( _rtDW -> hxamq1hdtu * _rtP -> P_36 - _rtDW -> hpya1t2gs1 *
_rtP -> P_35 ) * _rtP -> P_33 ) * _rtP -> P_30 + _rtP -> P_31 ; cjn2ssprvi *=
ofrsvndla4 ; if ( ssIsSampleHit ( S , 0 , tid ) ) { smplsInteg = _rtDW ->
m1nl5uiyzj ; if ( _rtDW -> ld553jatxi < 0 ) { _rtDW -> ld553jatxi ++ ; } else
{ _rtDW -> add1bmezqh += cjn2ssprvi ; smplsInteg = _rtDW -> m1nl5uiyzj + 1 ;
_rtDW -> m1nl5uiyzj ++ ; } if ( smplsInteg == 1000 ) { _rtDW -> byxvbrvczo =
_rtDW -> add1bmezqh ; _rtDW -> add1bmezqh = 0.0 ; _rtDW -> m1nl5uiyzj = 0 ; }
} if ( _rtDW -> k2vuq5wgnl != 0 ) { _rtDW -> fa2wnx4wvo = muDoubleScalarSin (
_rtP -> P_39 * ssGetTaskTime ( S , 0 ) ) ; _rtDW -> of5sk4vtpk =
muDoubleScalarCos ( _rtP -> P_39 * ssGetTaskTime ( S , 0 ) ) ; _rtDW ->
k2vuq5wgnl = 0 ; } cjn2ssprvi = ( ( _rtDW -> fa2wnx4wvo * _rtP -> P_43 +
_rtDW -> of5sk4vtpk * _rtP -> P_42 ) * _rtP -> P_41 + ( _rtDW -> of5sk4vtpk *
_rtP -> P_43 - _rtDW -> fa2wnx4wvo * _rtP -> P_42 ) * _rtP -> P_40 ) * _rtP
-> P_37 + _rtP -> P_38 ; cjn2ssprvi *= ofrsvndla4 ; if ( ssIsSampleHit ( S ,
0 , tid ) ) { smplsInteg = _rtDW -> bbnquujhhr ; if ( _rtDW -> f5hpbdjlvu < 0
) { _rtDW -> f5hpbdjlvu ++ ; } else { _rtDW -> ivfjkwcu2s += cjn2ssprvi ;
smplsInteg = _rtDW -> bbnquujhhr + 1 ; _rtDW -> bbnquujhhr ++ ; } if (
smplsInteg == 1000 ) { _rtDW -> ptmcnny3le = _rtDW -> ivfjkwcu2s ; _rtDW ->
ivfjkwcu2s = 0.0 ; _rtDW -> bbnquujhhr = 0 ; } } } if ( ssIsSampleHit ( S , 2
, tid ) ) { if ( ssIsSampleHit ( S , 2 , tid ) ) { faapseswfi = _rtDW ->
byxvbrvczo ; } if ( ssIsSampleHit ( S , 2 , tid ) ) { p3xvrsrqbq = _rtDW ->
ptmcnny3le ; } fdusals3sg = ( faapseswfi > _rtB -> psvwtqlc53 ) ; njr1wmr5i5
= ! fdusals3sg ; fwgjk3as20 = ( p3xvrsrqbq > _rtB -> psvwtqlc53 ) ;
f5nmir1vmq = ( fdusals3sg && fwgjk3as20 ) ; hfdgqiyhg5 = ! fwgjk3as20 ;
fdusals3sg = ( hfdgqiyhg5 && fdusals3sg ) ; hfdgqiyhg5 = ( njr1wmr5i5 &&
hfdgqiyhg5 ) ; njr1wmr5i5 = ( njr1wmr5i5 && fwgjk3as20 ) ; _rtB -> im3l0otlfm
= ( ( ( real_T ) ( ( f5nmir1vmq ? ( int32_T ) _rtP -> P_50 : 0 ) + (
njr1wmr5i5 ? ( int32_T ) _rtP -> P_52 : 0 ) ) + _rtB -> plz3i52tjf ) + (
real_T ) ( hfdgqiyhg5 ? ( int32_T ) _rtP -> P_51 : 0 ) ) + ( real_T ) (
fdusals3sg ? ( int32_T ) _rtP -> P_53 : 0 ) ; } UNUSED_PARAMETER ( tid ) ; }
static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) { fedc24kpyi * _rtB
; becphodmrm * _rtP ; _rtP = ( ( becphodmrm * ) ssGetDefaultParam ( S ) ) ;
_rtB = ( ( fedc24kpyi * ) _ssGetBlockIO ( S ) ) ; _rtB -> kxpqfyui0x = _rtP
-> P_5 ; _rtB -> dbvprqiz0k = _rtP -> P_14 ; _rtB -> i3iufndyvs = _rtP ->
P_15 ; _rtB -> psvwtqlc53 = _rtP -> P_44 ; _rtB -> plz3i52tjf = _rtP -> P_45
; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { real_T HoldSine ;
fedc24kpyi * _rtB ; becphodmrm * _rtP ; i5c3vxuxau * _rtDW ; _rtDW = ( (
i5c3vxuxau * ) ssGetRootDWork ( S ) ) ; _rtP = ( ( becphodmrm * )
ssGetDefaultParam ( S ) ) ; _rtB = ( ( fedc24kpyi * ) _ssGetBlockIO ( S ) ) ;
if ( ssIsSampleHit ( S , 2 , tid ) ) { _rtDW -> fmwdwfn5wf = _rtB ->
im3l0otlfm ; } if ( ssIsSampleHit ( S , 1 , tid ) ) { _rtDW -> oehkgucdwq =
_rtB -> kyi3aspvcm ; } if ( ssIsSampleHit ( S , 0 , tid ) ) {
ssCallAccelRunBlock ( S , 0 , 22 , SS_CALL_MDL_UPDATE ) ; HoldSine = _rtDW ->
hpya1t2gs1 ; _rtDW -> hpya1t2gs1 = _rtDW -> hpya1t2gs1 * _rtP -> P_34 + _rtDW
-> hxamq1hdtu * _rtP -> P_33 ; _rtDW -> hxamq1hdtu = _rtDW -> hxamq1hdtu *
_rtP -> P_34 - HoldSine * _rtP -> P_33 ; HoldSine = _rtDW -> fa2wnx4wvo ;
_rtDW -> fa2wnx4wvo = _rtDW -> fa2wnx4wvo * _rtP -> P_41 + _rtDW ->
of5sk4vtpk * _rtP -> P_40 ; _rtDW -> of5sk4vtpk = _rtDW -> of5sk4vtpk * _rtP
-> P_41 - HoldSine * _rtP -> P_40 ; } if ( ssIsSampleHit ( S , 1 , tid ) ) {
_rtDW -> fnpwuawce2 = _rtB -> lpbo2dnu0b ; if ( ssIsSampleHit ( S , 1 , tid )
) { if ( _rtDW -> lu5hhot51e == 0 ) { _rtDW -> oxjn22yyoo = _rtB ->
egyhkdbxcz ; } _rtDW -> lu5hhot51e ++ ; if ( _rtDW -> lu5hhot51e == 2 ) {
_rtDW -> lu5hhot51e = 0 ; } if ( _rtDW -> nv1tjlyya2 == 0 ) { _rtDW ->
d0olzpztcq = _rtB -> egyhkdbxcz ; } _rtDW -> nv1tjlyya2 ++ ; if ( _rtDW ->
nv1tjlyya2 == 2 ) { _rtDW -> nv1tjlyya2 = 0 ; } } } UNUSED_PARAMETER ( tid )
; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal
( S , 0 , 1113457104U ) ; ssSetChecksumVal ( S , 1 , 2098822034U ) ;
ssSetChecksumVal ( S , 2 , 4088990588U ) ; ssSetChecksumVal ( S , 3 ,
3195764981U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.6" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
i5c3vxuxau ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( fedc24kpyi ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
becphodmrm ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & bp33a4f1aq ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void
mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
