/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (C) 2007-2011 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * RELIC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with RELIC. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file
 *
 * Interface of the low-level prime field arithmetic module.
 *
 * @version $Id: relic_pp_low.h 838 2011-07-22 01:03:12Z dfaranha $
 * @ingroup fp
 */

#ifndef RELIC_PP_LOW_H
#define RELIC_PP_LOW_H

#include "relic_pp.h"

/*============================================================================*/
/* Function prototypes                                                        */
/*============================================================================*/

/**
 * Adds two quadratic extension field elements of the same size.
 * Computes c = a + b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_addn_low(fp2_t c, fp2_t a, fp2_t b);

/**
 * Adds two quadratic extension field elements of the same size with integrated
 * modular reduction. Computes c = a + b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_addm_low(fp2_t c, fp2_t a, fp2_t b);

/**
 * Adds two double-precision quadratic extension field elements of the same
 * size. Computes c = a + b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_addd_low(dv2_t c, dv2_t a, dv2_t b);

/**
 * Adds two double-precision quadratic extension field elements of the same size
 * and corrects the result by conditionally adding 2^(FP_DIGS * WORD) * p.
 * Computes c = a + b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_addc_low(dv2_t c, dv2_t a, dv2_t b);

/**
 * Subtracts a quadratic extension field element from another of the same size.
 * Computes c = a - b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element.
 * @param[in] b				- the field element to subtract.
 */
void fp2_subn_low(fp2_t c, fp2_t a, fp2_t b);

/**
 * Subtracts a quadratic extension field element from another of the same size
 * with integrated modular reduction. Computes c = a - b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element.
 * @param[in] b				- the field element to subtract.
 */
void fp2_subm_low(fp2_t c, fp2_t a, fp2_t b);

/**
 * Subtracts a double-precision quadratic extension field element from another
 * of the same size. Computes c = a - b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_subd_low(dv2_t c, dv2_t a, dv2_t b);

/**
 * Subtracts a double-precision quadratic extension field element from another
 * of the same size and  corrects the result by conditionally adding
 * 2^(FP_DIGS * WORD) * p. Computes c = a - b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to add.
 * @param[in] b				- the second field element to add.
 */
void fp2_subc_low(dv2_t c, dv2_t a, dv2_t b);

/**
 * Doubles a quadratic extension field element. Computes c = a + a.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to multiply.
 */
void fp2_dbln_low(fp2_t c, fp2_t a);

/**
 * Doubles a quadratic extension field element with integrated modular
 * reduction. Computes c = a + a.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the field element to double.
 */
void fp2_dblm_low(fp2_t c, fp2_t a);

/**
 * Multiplies a quadratic extension field element by the quadratic/cubic
 * non-residue. Computes c = a * E.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the field element to multiply.
 */
void fp2_norm_low(fp2_t c, fp2_t a);

/**
 * Multiplies a double-precision quadratic extension field element by the
 * quadratic/cubic non-residue. Computes c = a * E.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the field element to multiply.
 */
void fp2_nord_low(dv2_t c, dv2_t a);

/**
 * Multiplies two quadratic extension field elements of the same size.
 * Computes c = a * b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to multiply.
 * @param[in] b				- the second field element to multiply.
 */
void fp2_muln_low(dv2_t c, fp2_t a, fp2_t b);

/**
 * Multiplies two quadratic extension elements of the same size and corrects
 * the result by adding (2^(FP_DIGS * WORD) * p)/4. This function should only
 * be used when the FP_SPACE optimization is detected. Computes c = a * b.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to multiply.
 * @param[in] b				- the second field element to multiply.
 */
void fp2_mulc_low(dv2_t c, fp2_t a, fp2_t b);

/**
 * Multiplies two quadratic extension field elements of the same size with
 * embedded modular reduction. Computes c = (a * b) mod p.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the first field element to multiply.
 * @param[in] b				- the second field element to multiply.
 */
void fp2_mulm_low(fp2_t c, fp2_t a, fp2_t b);

/**
 * Squares a quadratic extension element. Computes c = a * a.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the field element to square.
 */
void fp2_sqrn_low(dv2_t c, fp2_t a);

/**
 * Squares a quadratic extension field element with integrated modular
 * reduction. Computes c = (a * a) mod p.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the field element to square.
 */
void fp2_sqrm_low(fp2_t c, fp2_t a);

/**
 * Reduces a quadratic extension element modulo the configured prime p.
 * Computes c = a mod p.
 *
 * @param[out] c			- the result.
 * @param[in] a				- the digit vector to reduce.
 */
void fp2_rdcn_low(fp2_t c, dv2_t a);

#endif /* !RELIC_FP_LOW_H */
