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

#ifndef CCNS3_CCNXMESSAGEPORTALFACTORY_H
#define CCNS3_CCNXMESSAGEPORTALFACTORY_H

#include "ns3/ccnx-l3-protocol.h"
#include "ns3/ccnx-portal-factory.h"

namespace ns3 {
namespace ccnx {

/**
 * @ingroup ccnx-portal
 *
 * A factory to aggregate to an ns3::Node.  Used to create CCNxMessagePortal instances.
 */
class CCNxMessagePortalFactory : public CCNxPortalFactory
{
public:
  static TypeId GetTypeId (void);

  /**
   * Constructor to create CCNxMessagePortalFactory.
   */
  CCNxMessagePortalFactory ();

  /**
   * Destructor for CCNxMessagePortalFactory.
   */
  virtual ~CCNxMessagePortalFactory ();

  /**
   * Set the associated CCNx L3 protocol.
   *
   * @param [in] ccnx The CCNx L3 protocol
   */
  void SetCCNx (Ptr<CCNxL3Protocol> ccnx);

  /**
   * Implements a method to create a MessagePortal
   *
   * When an application wants to create a Portal, it will use the RTTI system
   * to get the concrete portal factory aggregated to the node.  It will then pass
   * that TypeId to CCNxPortal::CreatePortal() to create a portal of the
   * associated concrete class.  See example below.
   *
   * @return smart pointer to CCNxPortal
   *
   * @code
   * Ptr<CCNxPortal>
   * foo(Ptr<Node> node)
   * {
   *   TypeId tid = TypeId::LookupByName ("ns3::ccnx::CCNxMessagePortalFactory");
   *   Ptr<CCNxPortal> portal = CCNxPortal::CreatePortal (node, tid);
   *   return portal;
   * }
   * @endcode
   */
  virtual Ptr<CCNxPortal> CreatePortal (void);

private:
  /**
   * Associated L3 protocol
   */
  Ptr<CCNxL3Protocol> m_ccnx;

};
}
}

#endif //CCNS3_CCNXMESSAGEPORTALFACTORY_H
