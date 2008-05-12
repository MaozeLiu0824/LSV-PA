/**CFile****************************************************************

  FileName    [saig.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Sequential AIG package.]

  Synopsis    [External declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - June 20, 2005.]

  Revision    [$Id: saig.h,v 1.00 2005/06/20 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __SAIG_H__
#define __SAIG_H__

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////

#include "aig.h"

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////

static inline int          Saig_ManPiNum( Aig_Man_t * p )          { return p->nTruePis;                     }
static inline int          Saig_ManPoNum( Aig_Man_t * p )          { return p->nTruePos;                     }
static inline int          Saig_ManCiNum( Aig_Man_t * p )          { return p->nTruePis + p->nRegs;          }
static inline int          Saig_ManCoNum( Aig_Man_t * p )          { return p->nTruePos + p->nRegs;          }
static inline int          Saig_ManRegNum( Aig_Man_t * p )         { return p->nRegs;                        }
static inline Aig_Obj_t *  Saig_ManLo( Aig_Man_t * p, int i )      { return (Aig_Obj_t *)Vec_PtrEntry(p->vPis, Saig_ManPiNum(p)+i);   }
static inline Aig_Obj_t *  Saig_ManLi( Aig_Man_t * p, int i )      { return (Aig_Obj_t *)Vec_PtrEntry(p->vPos, Saig_ManPoNum(p)+i);   }

static inline int          Saig_ObjIsPi( Aig_Man_t * p, Aig_Obj_t * pObj )    { return Aig_ObjIsPi(pObj) && Aig_ObjPioNum(pObj) < Saig_ManPiNum(p); }
static inline int          Saig_ObjIsPo( Aig_Man_t * p, Aig_Obj_t * pObj )    { return Aig_ObjIsPo(pObj) && Aig_ObjPioNum(pObj) < Saig_ManPoNum(p); }
static inline int          Saig_ObjIsLo( Aig_Man_t * p, Aig_Obj_t * pObj )    { return Aig_ObjIsPi(pObj) && Aig_ObjPioNum(pObj) >= Saig_ManPiNum(p); }
static inline int          Saig_ObjIsLi( Aig_Man_t * p, Aig_Obj_t * pObj )    { return Aig_ObjIsPo(pObj) && Aig_ObjPioNum(pObj) >= Saig_ManPoNum(p); }

// iterator over the primary inputs/outputs
#define Saig_ManForEachPi( p, pObj, i )                                           \
    Vec_PtrForEachEntryStop( p->vPis, pObj, i, Saig_ManPiNum(p) )
#define Saig_ManForEachPo( p, pObj, i )                                           \
    Vec_PtrForEachEntryStop( p->vPos, pObj, i, Saig_ManPoNum(p) )
// iterator over the latch inputs/outputs
#define Saig_ManForEachLo( p, pObj, i )                                           \
    for ( i = 0; (i < Saig_ManRegNum(p)) && (((pObj) = Vec_PtrEntry(p->vPis, i+Saig_ManPiNum(p))), 1); i++ )
#define Saig_ManForEachLi( p, pObj, i )                                           \
    for ( i = 0; (i < Saig_ManRegNum(p)) && (((pObj) = Vec_PtrEntry(p->vPos, i+Saig_ManPoNum(p))), 1); i++ )
// iterator over the latch input and outputs
#define Saig_ManForEachLiLo( p, pObjLi, pObjLo, i )                               \
    for ( i = 0; (i < Saig_ManRegNum(p)) && (((pObjLi) = Saig_ManLi(p, i)), 1)    \
        && (((pObjLo)=Saig_ManLo(p, i)), 1); i++ )

////////////////////////////////////////////////////////////////////////
///                    FUNCTION DECLARATIONS                         ///
////////////////////////////////////////////////////////////////////////

/*=== saigBmc.c ==========================================================*/
extern int               Saig_ManBmcSimple( Aig_Man_t * pAig, int nFrames, int nSizeMax, int nBTLimit, int fRewrite, int fVerbose, int * piFrame );
/*=== saigCone.c ==========================================================*/
extern void              Saig_ManPrintCones( Aig_Man_t * p );
/*=== saigInter.c ==========================================================*/
extern int               Saig_Interpolate( Aig_Man_t * pAig, int nConfLimit, int fRewrite, int fTransLoop, int fVerbose, int * pDepth );
/*=== saigPhase.c ==========================================================*/
extern Aig_Man_t *       Saig_ManPhaseAbstract( Aig_Man_t * p, Vec_Int_t * vInits, int nFrames, int fIgnore, int fPrint, int fVerbose );
/*=== saigRetFwd.c ==========================================================*/
extern Aig_Man_t *       Saig_ManRetimeForward( Aig_Man_t * p, int nMaxIters, int fVerbose );
/*=== saigRetMin.c ==========================================================*/
extern Aig_Man_t *       Saig_ManRetimeDupForward( Aig_Man_t * p, Vec_Ptr_t * vCut );
extern Aig_Man_t *       Saig_ManRetimeMinArea( Aig_Man_t * p, int nMaxIters, int fForwardOnly, int fBackwardOnly, int fInitial, int fVerbose );
/*=== saigRetStep.c ==========================================================*/
extern void              Saig_ManRetimeSteps( Aig_Man_t * p, int nSteps, int fForward );
/*=== saigScl.c ==========================================================*/
extern void              Saig_ManReportUselessRegisters( Aig_Man_t * pAig );

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

