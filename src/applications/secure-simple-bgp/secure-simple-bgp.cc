/* A RapidNet application. Generated by RapidNet compiler. */

#include "secure-simple-bgp.h"
#include <cstdlib>
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/type-ids.h"
#include "ns3/rapidnet-types.h"
#include "ns3/rapidnet-utils.h"
#include "ns3/assignor.h"
#include "ns3/selector.h"
#include "ns3/rapidnet-functions.h"

using namespace std;
using namespace ns3;
using namespace ns3::rapidnet;
using namespace ns3::rapidnet::securesimplebgp;

const string SecureSimpleBgp::ACCEPTROUTE = "acceptRoute";
const string SecureSimpleBgp::ADVERTISE = "advertise";
const string SecureSimpleBgp::CARRYTRAFFIC = "carryTraffic";
const string SecureSimpleBgp::NEIGHBOR = "neighbor";
const string SecureSimpleBgp::ROUTE = "route";

NS_LOG_COMPONENT_DEFINE ("SecureSimpleBgp");
NS_OBJECT_ENSURE_REGISTERED (SecureSimpleBgp);

TypeId
SecureSimpleBgp::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::securesimplebgp::SecureSimpleBgp")
    .SetParent<RapidNetApplicationBase> ()
    .AddConstructor<SecureSimpleBgp> ()
    ;
  return tid;
}

SecureSimpleBgp::SecureSimpleBgp()
{
  NS_LOG_FUNCTION_NOARGS ();
}

SecureSimpleBgp::~SecureSimpleBgp()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
SecureSimpleBgp::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::DoDispose ();
}

void
SecureSimpleBgp::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StartApplication ();
  SendlogInit ();
  RAPIDNET_LOG_INFO("SecureSimpleBgp Application Started");
}

void
SecureSimpleBgp::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  RapidNetApplicationBase::StopApplication ();
  RAPIDNET_LOG_INFO("SecureSimpleBgp Application Stopped");
}

void
SecureSimpleBgp::InitDatabase ()
{
  //RapidNetApplicationBase::InitDatabase ();

  AddRelationWithKeys (ACCEPTROUTE, attrdeflist (
    attrdef ("acceptRoute_attr2", IPV4),
    attrdef ("acceptRoute_attr3", IPV4)));

  AddRelationWithKeys (CARRYTRAFFIC, attrdeflist (
    attrdef ("carryTraffic_attr2", IPV4),
    attrdef ("carryTraffic_attr3", IPV4)));

  AddRelationWithKeys (NEIGHBOR, attrdeflist (
    attrdef ("neighbor_attr1", IPV4),
    attrdef ("neighbor_attr2", IPV4)));

  AddRelationWithKeys (ROUTE, attrdeflist (
    attrdef ("route_attr3", LIST)));

}

void
SecureSimpleBgp::DemuxRecv (Ptr<Tuple> tuple)
{
  RapidNetApplicationBase::DemuxRecv (tuple);

  if (IsInsertEvent (tuple, NEIGHBOR))
    {
      Z1Eca0Ins (tuple);
    }
  if (IsDeleteEvent (tuple, NEIGHBOR))
    {
      Z1Eca0Del (tuple);
    }
  if (IsRecvEvent (tuple, ADVERTISE))
    {
      Z2_eca (tuple);
    }
  if (IsInsertEvent (tuple, NEIGHBOR))
    {
      Z3Eca0Ins (tuple);
    }
  if (IsInsertEvent (tuple, ROUTE))
    {
      Z3Eca1Ins (tuple);
    }
  if (IsInsertEvent (tuple, CARRYTRAFFIC))
    {
      Z3Eca2Ins (tuple);
    }
}

void
SecureSimpleBgp::Z1Eca0Ins (Ptr<Tuple> neighbor)
{
  RAPIDNET_LOG_INFO ("Z1Eca0Ins triggered");

  Ptr<Tuple> result = neighbor;

  result->Assign (Assignor::New ("P1",
    FAppend::New (
      VarExpr::New ("neighbor_attr1"))));

  result->Assign (Assignor::New ("P2",
    FAppend::New (
      VarExpr::New ("neighbor_attr2"))));

  result->Assign (Assignor::New ("P",
    FConcat::New (
      VarExpr::New ("P1"),
      VarExpr::New ("P2"))));

  result = result->Project (
    ROUTE,
    strlist ("neighbor_attr1",
      "neighbor_attr2",
      "P"),
    strlist ("route_attr1",
      "route_attr2",
      "route_attr3"));

  Insert (result);
}

void
SecureSimpleBgp::Z1Eca0Del (Ptr<Tuple> neighbor)
{
  RAPIDNET_LOG_INFO ("Z1Eca0Del triggered");

  Ptr<Tuple> result = neighbor;

  result->Assign (Assignor::New ("P1",
    FAppend::New (
      VarExpr::New ("neighbor_attr1"))));

  result->Assign (Assignor::New ("P2",
    FAppend::New (
      VarExpr::New ("neighbor_attr2"))));

  result->Assign (Assignor::New ("P",
    FConcat::New (
      VarExpr::New ("P1"),
      VarExpr::New ("P2"))));

  result = result->Project (
    ROUTE,
    strlist ("neighbor_attr1",
      "neighbor_attr2",
      "P"),
    strlist ("route_attr1",
      "route_attr2",
      "route_attr3"));

  Delete (result);
}

void
SecureSimpleBgp::Z2_eca (Ptr<Tuple> advertise)
{
  RAPIDNET_LOG_INFO ("Z2_eca triggered");

  if(!Verify (advertise, "advertise_attr4"))
    {
      RAPIDNET_LOG_WARN ("Verification failed!\n");
      return;
    }

  Ptr<RelationBase> result;

  result = GetRelation (ACCEPTROUTE)->Join (
    advertise,
    strlist ("acceptRoute_attr2", "acceptRoute_attr3", "acceptRoute_attr1"),
    strlist ("advertise_attr4", "advertise_attr1", "advertise_attr3"));

  result = result->Project (
    ROUTE,
    strlist ("advertise_attr3",
      "advertise_attr1",
      "advertise_attr2"),
    strlist ("route_attr1",
      "route_attr2",
      "route_attr3"));

  Insert (result);
}

void
SecureSimpleBgp::Z3Eca0Ins (Ptr<Tuple> neighbor)
{
  RAPIDNET_LOG_INFO ("Z3Eca0Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (ROUTE)->Join (
    neighbor,
    strlist ("route_attr1"),
    strlist ("neighbor_attr1"));

  result = GetRelation (CARRYTRAFFIC)->Join (
    result,
    strlist ("carryTraffic_attr2", "carryTraffic_attr3", "carryTraffic_attr1"),
    strlist ("neighbor_attr2", "route_attr2", "neighbor_attr1"));

  result->Assign (Assignor::New ("P0",
    FAppend::New (
      VarExpr::New ("neighbor_attr2"))));

  result->Assign (Assignor::New ("P1",
    FConcat::New (
      VarExpr::New ("P0"),
      VarExpr::New ("route_attr3"))));

  result = result->Project (
    ADVERTISE,
    strlist ("route_attr2",
      "P1",
      "neighbor_attr2",
      "neighbor_attr1",
      "neighbor_attr2"),
    strlist ("advertise_attr1",
      "advertise_attr2",
      "advertise_attr3",
      "advertise_attr4",
      RN_DEST));

  Sign (result);
  Send (result);
}

void
SecureSimpleBgp::Z3Eca1Ins (Ptr<Tuple> route)
{
  RAPIDNET_LOG_INFO ("Z3Eca1Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (NEIGHBOR)->Join (
    route,
    strlist ("neighbor_attr1"),
    strlist ("route_attr1"));

  result = GetRelation (CARRYTRAFFIC)->Join (
    result,
    strlist ("carryTraffic_attr2", "carryTraffic_attr3", "carryTraffic_attr1"),
    strlist ("neighbor_attr2", "route_attr2", "route_attr1"));

  result->Assign (Assignor::New ("P0",
    FAppend::New (
      VarExpr::New ("neighbor_attr2"))));

  result->Assign (Assignor::New ("P1",
    FConcat::New (
      VarExpr::New ("P0"),
      VarExpr::New ("route_attr3"))));

  result = result->Project (
    ADVERTISE,
    strlist ("route_attr2",
      "P1",
      "neighbor_attr2",
      "route_attr1",
      "neighbor_attr2"),
    strlist ("advertise_attr1",
      "advertise_attr2",
      "advertise_attr3",
      "advertise_attr4",
      RN_DEST));

  Sign (result);
  Send (result);
}

void
SecureSimpleBgp::Z3Eca2Ins (Ptr<Tuple> carryTraffic)
{
  RAPIDNET_LOG_INFO ("Z3Eca2Ins triggered");

  Ptr<RelationBase> result;

  result = GetRelation (NEIGHBOR)->Join (
    carryTraffic,
    strlist ("neighbor_attr2", "neighbor_attr1"),
    strlist ("carryTraffic_attr2", "carryTraffic_attr1"));

  result = GetRelation (ROUTE)->Join (
    result,
    strlist ("route_attr2", "route_attr1"),
    strlist ("carryTraffic_attr3", "carryTraffic_attr1"));

  result->Assign (Assignor::New ("P0",
    FAppend::New (
      VarExpr::New ("carryTraffic_attr2"))));

  result->Assign (Assignor::New ("P1",
    FConcat::New (
      VarExpr::New ("P0"),
      VarExpr::New ("route_attr3"))));

  result = result->Project (
    ADVERTISE,
    strlist ("carryTraffic_attr3",
      "P1",
      "carryTraffic_attr2",
      "carryTraffic_attr1",
      "carryTraffic_attr2"),
    strlist ("advertise_attr1",
      "advertise_attr2",
      "advertise_attr3",
      "advertise_attr4",
      RN_DEST));

  Sign (result);
  Send (result);
}

