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

#include "ns3/test.h"
#include "ns3/ccnx-connection-device.h"
#include "ns3/virtual-net-device.h"

#include "../../TestMacros.h"

using namespace ns3;
using namespace ns3::ccnx;

namespace TestSuiteCCNxConnectionDevice {

BeginTest (Constructor)
{
  Ptr<CCNxConnectionDevice> conn = Create<CCNxConnectionDevice> ();

  bool exists = (conn);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Got null pointer");
}
EndTest ()

BeginTest (GetSetProtocolNumber)
{
  Ptr<CCNxConnectionDevice> conn = Create<CCNxConnectionDevice> ();

  bool exists = (conn);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Got null pointer");

  conn->SetProtocolNumber (0x0801);

  bool truth = (conn->GetProtocolNumber () == 0x0801);
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Ethertype should be the same");
}
EndTest ()

BeginTest (GetSetNextHop)
{
  Ptr<CCNxConnectionDevice> conn = Create<CCNxConnectionDevice> ();

  bool exists = (conn);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Got null pointer");

  uint8_t buffer[6] = { 0x11, 0x00, 0, 0, 0, 0 };
  Mac48Address addr = Mac48Address::Allocate ();
  addr.CopyFrom (buffer);

  conn->SetNexthop (addr);

  bool truth = (conn->GetNexthop () == addr);
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Next hop address should be the same");
}
EndTest ()

BeginTest (GetSetOutputDevice)
{
  Ptr<CCNxConnectionDevice> conn = Create<CCNxConnectionDevice> ();

  bool exists = (conn);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Got null pointer");

  Ptr<VirtualNetDevice> tap = CreateObject<VirtualNetDevice> ();
  conn->SetOutputDevice (tap);

  bool truth = (conn->GetOutputDevice () == tap);
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Output Device should be the same");
}
EndTest ()

int sendCount = 0;

static bool
SendCallback (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber)
{
  ++sendCount;
  return true;
}

BeginTest (Send)
{
  Ptr<CCNxName> name = Create<CCNxName> ("ccnx:/name=foo/name=bar");
  Ptr<CCNxInterest> interest = Create<CCNxInterest> (name);
  Ptr<CCNxPacket> packet = CCNxPacket::CreateFromMessage (interest);

  Ptr<CCNxConnectionDevice> conn = Create<CCNxConnectionDevice> ();

  Ptr<VirtualNetDevice> tap = CreateObject<VirtualNetDevice> ();
  VirtualNetDevice::SendCallback sendCb = MakeCallback (&SendCallback);
  tap->SetSendCallback (sendCb);

  conn->SetOutputDevice (tap);

  uint8_t buffer[6] = { 0x11, 0x00, 0, 0, 0, 0 };
  Mac48Address addr = Mac48Address::Allocate ();
  addr.CopyFrom (buffer);
  conn->SetNexthop (addr);

  conn->SetProtocolNumber (0x0801);

  conn->Send (packet,conn);

  bool truth = (sendCount == 1);
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Send count should be one");
}
EndTest ()

/**
 * @ingroup ccnx-test
 *
 * Test Suite for CCNxConnectionDevice
 */
static class TestSuiteCCNxConnectionDevice : public TestSuite
{
public:
  TestSuiteCCNxConnectionDevice () : TestSuite ("ccnx-connection-device", UNIT)
  {
    AddTestCase (new Constructor (), TestCase::QUICK);
    AddTestCase (new GetSetProtocolNumber (), TestCase::QUICK);
    AddTestCase (new GetSetNextHop (), TestCase::QUICK);
    AddTestCase (new GetSetOutputDevice (), TestCase::QUICK);
    AddTestCase (new Send (), TestCase::QUICK);
  }
} g_TestSuiteCCNxConnectionDevice;

} // namespace TestSuiteCCNxConnectionDevice
