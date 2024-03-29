/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */

#ifndef CCNX_MODEL_ROUTING_NFP_NFP_SEQNUM_H_
#define CCNX_MODEL_ROUTING_NFP_NFP_SEQNUM_H_

#include <stdint.h>

namespace ns3 {
namespace ccnx {

/**
 * \ingroup nfp-routing
 *
 * NFP uses 32-bit and 16-bit sequence numbers.  This class encapsulates those sequence numbers
 * to make it easy to do comparisons.
 *
 * Sequence numbers are managed as per RFC 1982.  In particular, this is the 1/2 - 1 wrap-around
 * rule to determine if another sequece number is greater than or less than another (of similar width).
 *
 * int32_t delta = int32_t ( au32 - bu32 );
 * int16_t delta = int16_t ( au16 - bu16 );
 *
 * If delta is negative, a < b.  If delta is positive a > b.  If delta is 0, a == b.
 */
class NfpSeqnum
{
public:
  /**
   * Compares two unsigned sequence numbers as per RFC 1982.
   *
   * @param a First sequence number
   * @param b Second sequence number
   * @return -1 if a < b, 0 if a = b, +1 if a > b
   */
  static int Compare (uint32_t a, uint32_t b);

  /**
   * Compares two unsigned sequence numbers as per RFC 1982.
   *
   * @param a First sequence number
   * @param b Second sequence number
   * @return -1 if a < b, 0 if a = b, +1 if a > b
   */
  static int Compare (uint16_t a, uint16_t b);
};

}   /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNX_MODEL_ROUTING_NFP_NFP_SEQNUM_H_ */
