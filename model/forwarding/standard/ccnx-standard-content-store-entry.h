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


#ifndef CCNS3SIM_MODEL_FORWARDING_STANDARD_CCNX_STANDARD_CONTENT_STORE_ENTRY_H_
#define CCNS3SIM_MODEL_FORWARDING_STANDARD_CCNX_STANDARD_CONTENT_STORE_ENTRY_H_

#include "ns3/simple-ref-count.h"
#include "ns3/ccnx-packet.h"

namespace ns3 {
namespace ccnx {

/**
 * @ingroup ccnx-standard-forwarder
 *
 *
 */
class CCNxStandardContentStoreEntry : public SimpleRefCount<CCNxStandardContentStoreEntry>
{
public:
  /**
   * Creates a ContentStore entry for a content object.
   *
   * @param contentObject The content object to store
   */
  CCNxStandardContentStoreEntry (Ptr<CCNxPacket> contentObject);

  /**
   * Virtual destructor for inheritance
   */
  virtual ~CCNxStandardContentStoreEntry ();

  /**
   * Returns the stored content object.
   *
   * This does not affect the usage count.  you must call `IncrementUseCount` if the
   * content object satisfies an interest.
   * @return
   */
  Ptr<CCNxPacket> GetPacket () const;

  /**
   * Checks if the content object is past its ExpiryTime
   *
   * If the content object does not have an Expiry time, it will always return false.
   *
   * @return true ContentObject is expired
   * @return false ContentObject is not expired
   */
  bool IsExpired () const;

  /**
   * Checks if the content object is past its RecommendedCacheTime.
   *
   *
   * @return true ContentObject is past its RecommendedCacheTime
   * @return false ContentObject is not past its RecommendedCacheTime
   */
  bool IsStale () const;

  /**
   * Increment the usage count of this record.  Used to track how many times a record
   * is used to satisfy an Interest.
   */
  void IncrementUseCount ();

  /**
   * Returns the usage count.
   *
   * @see IncrementUseCount
   * @return The number of times the record was used to satisfy an Interest
   */
  uint64_t GetUseCount ();




private:
  Ptr<CCNxPacket> m_contentObject;
  uint64_t m_useCount;


};

}   /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_FORWARDING_STANDARD_CCNX_STANDARD_CONTENT_STORE_ENTRY_H_ */
