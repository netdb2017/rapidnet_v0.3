/* A RapidNet application. Generated by RapidNet compiler. */

#include "epidemic.h"
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
using namespace ns3::rapidnet::epidemic;

const string Epidemic::EBITVECTORREPLY = "eBitVectorReply";
const string Epidemic::EBITVECTORREQUEST = "eBitVectorRequest";
const string Epidemic::ELINKADD = "eLinkAdd";
const string Epidemic::ELINKDISCOVERYADD = "eLinkDiscoveryAdd";
const string Epidemic::ELINKDISCOVERYDEL = "eLinkDiscoveryDel";
const string Epidemic::EMESSAGE = "eMessage";
const string Epidemic::EMESSAGEBEGIN = "eMessageBegin";
const string Epidemic::EMESSAGEDEL = "eMessageDel";
const string Epidemic::EMESSAGEEND = "eMessageEnd";
const string Epidemic::EMESSAGEINJECT = "eMessageInject";
const string Epidemic::EMESSAGEINJECTORIGINAL = "eMessageInjectOriginal";
const string Epidemic::EMESSAGELOC = "eMessageLoc";
const string Epidemic::EMESSAGENEW = "eMessageNew";
const string Epidemic::LINK = "link";
const string Epidemic::PERIODIC = "periodic";
const string Epidemic::R11_ECAPERIODIC = "r11_ecaperiodic";
const string Epidemic::R29_ECAPERIODIC = "r29_ecaperiodic";
const string Epidemic::TLINK = "tLink";
const string Epidemic::TMESSAGE = "tMessage";
const string Epidemic::TSUMMARYVEC = "tSummaryVec";

NS_LOG_COMPONENT_DEFINE ("Epidemic");
NS_OBJECT_ENSURE_REGISTERED (Epidemic);

TypeId
Epidemic::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::rapidnet::epidemic::Epidemic")
    .SetParent<DiscoveryEpidemic> ()
    .AddConstructor<Epidemic> ()
    ;
  return tid;
}

Epidemic::Epidemic()
{
  NS_LOG_FUNCTION_NOARGS ();
}

Epidemic::~Epidemic()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
Epidemic::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  DiscoveryEpidemic::DoDispose ();
}

void
Epidemic::StartApplication (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  DiscoveryEpidemic::StartApplication ();
  m_event_r11_ecaperiodic=
    Simulator::Schedule (Seconds (0), &Epidemic::R11_ecaperiodic, this);
  m_event_r29_ecaperiodic=
    Simulator::Schedule (Seconds (0), &Epidemic::R29_ecaperiodic, this);
  m_count_r11_ecaperiodic = 0;
  RAPIDNET_LOG_INFO("Epidemic Application Started");
}

void
Epidemic::StopApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();

  DiscoveryEpidemic::StopApplication ();
  Simulator::Cancel(m_event_r11_ecaperiodic);
  Simulator::Cancel(m_event_r29_ecaperiodic);
  RAPIDNET_LOG_INFO("Epidemic Application Stopped");
}

void
Epidemic::InitDatabase ()
{
  //DiscoveryEpidemic::InitDatabase ();

  AddRelationWithKeys (LINK, attrdeflist (
    attrdef ("link_attr1", IPV4),
    attrdef ("link_attr2", IPV4)),
    Seconds (5));

  AddRelationWithKeys (TLINK, attrdeflist (
    attrdef ("tLink_attr1", IPV4),
    attrdef ("tLink_attr2", IPV4)));

  AddRelationWithKeys (TMESSAGE, attrdeflist (
    attrdef ("tMessage_attr1", IPV4),
    attrdef ("tMessage_attr2", IPV4),
    attrdef ("tMessage_attr3", IPV4),
    attrdef ("tMessage_attr4", STR)));

  AddRelationWithKeys (TSUMMARYVEC, attrdeflist (
    attrdef ("tSummaryVec_attr1", IPV4)));

}

void
Epidemic::DemuxRecv (Ptr<Tuple> tuple)
{
  DiscoveryEpidemic::DemuxRecv (tuple);

  if (IsRecvEvent (tuple, ELINKDISCOVERYADD))
    {
      R01_eca (tuple);
    }
  if (IsRecvEvent (tuple, ELINKDISCOVERYDEL))
    {
      R02_eca (tuple);
    }
  if (IsInsertEvent (tuple, TLINK))
    {
      R03Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEINJECT))
    {
      R04_eca (tuple);
    }
  if (IsInsertEvent (tuple, TMESSAGE))
    {
      R05Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, R11_ECAPERIODIC))
    {
      R11_eca (tuple);
    }
  if (IsRecvEvent (tuple, ELINKADD))
    {
      R12_eca (tuple);
    }
  if (IsRecvEvent (tuple, EBITVECTORREQUEST))
    {
      R13_eca (tuple);
    }
  if (IsRecvEvent (tuple, EBITVECTORREPLY))
    {
      R14_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEINJECTORIGINAL))
    {
      R21_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEINJECT))
    {
      R22_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEINJECT))
    {
      R23_eca (tuple);
    }
  if (IsInsertEvent (tuple, TMESSAGE))
    {
      R24Eca0Ins (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGENEW))
    {
      R25_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGE))
    {
      R26_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGELOC))
    {
      R27_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGELOC))
    {
      R28_eca (tuple);
    }
  if (IsRecvEvent (tuple, R29_ECAPERIODIC))
    {
      R29_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEDEL))
    {
      R2A_eca (tuple);
    }
  if (IsRecvEvent (tuple, EMESSAGEDEL))
    {
      R2B_eca (tuple);
    }
}

void
Epidemic::R01_eca (Ptr<Tuple> eLinkDiscoveryAdd)
{
  RAPIDNET_LOG_INFO ("R01_eca triggered");

  Ptr<Tuple> result = eLinkDiscoveryAdd;

  result = result->Project (
    TLINK,
    strlist ("eLinkDiscoveryAdd_attr1",
      "eLinkDiscoveryAdd_attr2",
      "eLinkDiscoveryAdd_attr3"),
    strlist ("tLink_attr1",
      "tLink_attr2",
      "tLink_attr3"));

  Insert (result);
}

void
Epidemic::R02_eca (Ptr<Tuple> eLinkDiscoveryDel)
{
  RAPIDNET_LOG_INFO ("R02_eca triggered");

  Ptr<Tuple> result = eLinkDiscoveryDel;

  result = result->Project (
    TLINK,
    strlist ("eLinkDiscoveryDel_attr1",
      "eLinkDiscoveryDel_attr2",
      "eLinkDiscoveryDel_attr3"),
    strlist ("tLink_attr1",
      "tLink_attr2",
      "tLink_attr3"));

  Delete (result);
}

void
Epidemic::R03Eca0Ins (Ptr<Tuple> tLink)
{
  RAPIDNET_LOG_INFO ("R03Eca0Ins triggered");

  Ptr<Tuple> result = tLink;

  result = result->Project (
    ELINKADD,
    strlist ("tLink_attr1",
      "tLink_attr2",
      "tLink_attr3"),
    strlist ("eLinkAdd_attr1",
      "eLinkAdd_attr2",
      "eLinkAdd_attr3"));

  SendLocal (result);
}

void
Epidemic::R04_eca (Ptr<Tuple> eMessageInject)
{
  RAPIDNET_LOG_INFO ("R04_eca triggered");

  Ptr<Tuple> result = eMessageInject;

  result->Assign (Assignor::New ("$1",
    VarExpr::New ("eMessageInject_attr1")));

  result = result->Project (
    EMESSAGEBEGIN,
    strlist ("eMessageInject_attr1",
      "$1",
      "eMessageInject_attr2",
      "eMessageInject_attr3",
      "eMessageInject_attr4"),
    strlist ("eMessageBegin_attr1",
      "eMessageBegin_attr2",
      "eMessageBegin_attr3",
      "eMessageBegin_attr4",
      "eMessageBegin_attr5"));

  SendLocal (result);
}

void
Epidemic::R05Eca0Ins (Ptr<Tuple> tMessage)
{
  RAPIDNET_LOG_INFO ("R05Eca0Ins triggered");

  Ptr<Tuple> result = tMessage;

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("Local"),
      VarExpr::New ("tMessage_attr3"))));

  result = result->Project (
    EMESSAGEEND,
    strlist ("Local",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"),
    strlist ("eMessageEnd_attr1",
      "eMessageEnd_attr2",
      "eMessageEnd_attr3",
      "eMessageEnd_attr4",
      "eMessageEnd_attr5"));

  SendLocal (result);
}

void
Epidemic::R11_ecaperiodic ()
{
  RAPIDNET_LOG_INFO ("R11_ecaperiodic triggered");

  SendLocal (tuple (R11_ECAPERIODIC, attrlist (
    attr ("r11_ecaperiodic_attr1", Ipv4Value, GetAddress ()),
    attr ("r11_ecaperiodic_attr2", Int32Value, rand ()))));

  if (++m_count_r11_ecaperiodic < 1)
    {
      m_event_r11_ecaperiodic = Simulator::Schedule (Seconds(0),
        &Epidemic::R11_ecaperiodic, this);
    }
}

void
Epidemic::R11_eca (Ptr<Tuple> r11_ecaperiodic)
{
  RAPIDNET_LOG_INFO ("R11_eca triggered");

  Ptr<Tuple> result = r11_ecaperiodic;

  result->Assign (Assignor::New ("SummaryVec",
    FSvCreate::New (
)));

  result = result->Project (
    TSUMMARYVEC,
    strlist ("r11_ecaperiodic_attr1",
      "SummaryVec"),
    strlist ("tSummaryVec_attr1",
      "tSummaryVec_attr2"));

  Insert (result);
}

void
Epidemic::R12_eca (Ptr<Tuple> eLinkAdd)
{
  RAPIDNET_LOG_INFO ("R12_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TSUMMARYVEC)->Join (
    eLinkAdd,
    strlist ("tSummaryVec_attr1"),
    strlist ("eLinkAdd_attr1"));

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    EBITVECTORREQUEST,
    strlist ("eLinkAdd_attr2",
      "Local",
      "tSummaryVec_attr2",
      "eLinkAdd_attr2"),
    strlist ("eBitVectorRequest_attr1",
      "eBitVectorRequest_attr2",
      "eBitVectorRequest_attr3",
      RN_DEST));

  Send (result);
}

void
Epidemic::R13_eca (Ptr<Tuple> eBitVectorRequest)
{
  RAPIDNET_LOG_INFO ("R13_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TSUMMARYVEC)->Join (
    eBitVectorRequest,
    strlist ("tSummaryVec_attr1"),
    strlist ("eBitVectorRequest_attr1"));

  result->Assign (Assignor::New ("SummaryVec_3",
    FSvAndNot::New (
      VarExpr::New ("eBitVectorRequest_attr3"),
      VarExpr::New ("tSummaryVec_attr2"))));

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    EBITVECTORREPLY,
    strlist ("eBitVectorRequest_attr2",
      "Local",
      "SummaryVec_3",
      "eBitVectorRequest_attr2"),
    strlist ("eBitVectorReply_attr1",
      "eBitVectorReply_attr2",
      "eBitVectorReply_attr3",
      RN_DEST));

  Send (result);
}

void
Epidemic::R14_eca (Ptr<Tuple> eBitVectorReply)
{
  RAPIDNET_LOG_INFO ("R14_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TMESSAGE)->Join (
    eBitVectorReply,
    strlist ("tMessage_attr1"),
    strlist ("eBitVectorReply_attr1"));

  result->Assign (Assignor::New ("Result",
    FSvIn::New (
      VarExpr::New ("eBitVectorReply_attr3"),
      VarExpr::New ("tMessage_attr4"))));

  result = result->Select (Selector::New (
    Operation::New (RN_EQ,
      VarExpr::New ("Result"),
      ValueExpr::New (Int32Value::New (1)))));

  result = result->Project (
    EMESSAGE,
    strlist ("eBitVectorReply_attr2",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5",
      "eBitVectorReply_attr2"),
    strlist ("eMessage_attr1",
      "eMessage_attr2",
      "eMessage_attr3",
      "eMessage_attr4",
      "eMessage_attr5",
      RN_DEST));

  Send (result);
}

void
Epidemic::R21_eca (Ptr<Tuple> eMessageInjectOriginal)
{
  RAPIDNET_LOG_INFO ("R21_eca triggered");

  Ptr<Tuple> result = eMessageInjectOriginal;

  result->Assign (Assignor::New ("ID",
    FRand::New (
)));

  result->Assign (Assignor::New ("T_begin",
    FNow::New (
)));

  result = result->Project (
    EMESSAGEINJECT,
    strlist ("eMessageInjectOriginal_attr1",
      "eMessageInjectOriginal_attr2",
      "ID",
      "T_begin"),
    strlist ("eMessageInject_attr1",
      "eMessageInject_attr2",
      "eMessageInject_attr3",
      "eMessageInject_attr4"));

  SendLocal (result);
}

void
Epidemic::R22_eca (Ptr<Tuple> eMessageInject)
{
  RAPIDNET_LOG_INFO ("R22_eca triggered");

  Ptr<Tuple> result = eMessageInject;

  result->Assign (Assignor::New ("$1",
    VarExpr::New ("eMessageInject_attr1")));

  result = result->Project (
    TMESSAGE,
    strlist ("eMessageInject_attr1",
      "$1",
      "eMessageInject_attr2",
      "eMessageInject_attr3",
      "eMessageInject_attr4"),
    strlist ("tMessage_attr1",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"));

  Insert (result);
}

void
Epidemic::R23_eca (Ptr<Tuple> eMessageInject)
{
  RAPIDNET_LOG_INFO ("R23_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TSUMMARYVEC)->Join (
    eMessageInject,
    strlist ("tSummaryVec_attr1"),
    strlist ("eMessageInject_attr1"));

  result->Assign (Assignor::New ("SummaryVecUpdate",
    FSvAppend::New (
      VarExpr::New ("tSummaryVec_attr2"),
      VarExpr::New ("eMessageInject_attr3"))));

  result = result->Project (
    TSUMMARYVEC,
    strlist ("eMessageInject_attr1",
      "SummaryVecUpdate"),
    strlist ("tSummaryVec_attr1",
      "tSummaryVec_attr2"));

  Insert (result);
}

void
Epidemic::R24Eca0Ins (Ptr<Tuple> tMessage)
{
  RAPIDNET_LOG_INFO ("R24Eca0Ins triggered");

  Ptr<Tuple> result = tMessage;

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Select (Selector::New (
    Operation::New (RN_NEQ,
      VarExpr::New ("Local"),
      VarExpr::New ("tMessage_attr3"))));

  result = result->Project (
    EMESSAGENEW,
    strlist ("Local",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"),
    strlist ("eMessageNew_attr1",
      "eMessageNew_attr2",
      "eMessageNew_attr3",
      "eMessageNew_attr4",
      "eMessageNew_attr5"));

  SendLocal (result);
}

void
Epidemic::R25_eca (Ptr<Tuple> eMessageNew)
{
  RAPIDNET_LOG_INFO ("R25_eca triggered");

  Ptr<Tuple> result = eMessageNew;

  result->Assign (Assignor::New ("Broadcast",
    BROADCAST_ADDRESS));

  result = result->Project (
    EMESSAGE,
    strlist ("Broadcast",
      "eMessageNew_attr2",
      "eMessageNew_attr3",
      "eMessageNew_attr4",
      "eMessageNew_attr5",
      "Broadcast"),
    strlist ("eMessage_attr1",
      "eMessage_attr2",
      "eMessage_attr3",
      "eMessage_attr4",
      "eMessage_attr5",
      RN_DEST));

  Send (result);
}

void
Epidemic::R26_eca (Ptr<Tuple> eMessage)
{
  RAPIDNET_LOG_INFO ("R26_eca triggered");

  Ptr<Tuple> result = eMessage;

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    EMESSAGELOC,
    strlist ("Local",
      "eMessage_attr2",
      "eMessage_attr3",
      "eMessage_attr4",
      "eMessage_attr5",
      "Local"),
    strlist ("eMessageLoc_attr1",
      "eMessageLoc_attr2",
      "eMessageLoc_attr3",
      "eMessageLoc_attr4",
      "eMessageLoc_attr5",
      RN_DEST));

  Send (result);
}

void
Epidemic::R27_eca (Ptr<Tuple> eMessageLoc)
{
  RAPIDNET_LOG_INFO ("R27_eca triggered");

  Ptr<Tuple> result = eMessageLoc;

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    TMESSAGE,
    strlist ("Local",
      "eMessageLoc_attr2",
      "eMessageLoc_attr3",
      "eMessageLoc_attr4",
      "eMessageLoc_attr5"),
    strlist ("tMessage_attr1",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"));

  Insert (result);
}

void
Epidemic::R28_eca (Ptr<Tuple> eMessageLoc)
{
  RAPIDNET_LOG_INFO ("R28_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TSUMMARYVEC)->Join (
    eMessageLoc,
    strlist ("tSummaryVec_attr1"),
    strlist ("eMessageLoc_attr1"));

  result->Assign (Assignor::New ("SummaryVecUpdate",
    FSvAppend::New (
      VarExpr::New ("tSummaryVec_attr2"),
      VarExpr::New ("eMessageLoc_attr4"))));

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    TSUMMARYVEC,
    strlist ("Local",
      "SummaryVecUpdate"),
    strlist ("tSummaryVec_attr1",
      "tSummaryVec_attr2"));

  Insert (result);
}

void
Epidemic::R29_ecaperiodic ()
{
  RAPIDNET_LOG_INFO ("R29_ecaperiodic triggered");

  SendLocal (tuple (R29_ECAPERIODIC, attrlist (
    attr ("r29_ecaperiodic_attr1", Ipv4Value, GetAddress ()),
    attr ("r29_ecaperiodic_attr2", Int32Value, rand ()))));

  m_event_r29_ecaperiodic = Simulator::Schedule (Seconds(1),
    &Epidemic::R29_ecaperiodic, this);
}

void
Epidemic::R29_eca (Ptr<Tuple> r29_ecaperiodic)
{
  RAPIDNET_LOG_INFO ("R29_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TMESSAGE)->Join (
    r29_ecaperiodic,
    strlist ("tMessage_attr1"),
    strlist ("r29_ecaperiodic_attr1"));

  result->Assign (Assignor::New ("Now",
    FNow::New (
)));

  result->Assign (Assignor::New ("T_exist",
    FDiffTime::New (
      VarExpr::New ("Now"),
      VarExpr::New ("tMessage_attr5"))));

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Select (Selector::New (
    Operation::New (RN_GT,
      VarExpr::New ("T_exist"),
      ValueExpr::New (Int32Value::New (120)))));

  result = result->Project (
    EMESSAGEDEL,
    strlist ("Local",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"),
    strlist ("eMessageDel_attr1",
      "eMessageDel_attr2",
      "eMessageDel_attr3",
      "eMessageDel_attr4",
      "eMessageDel_attr5"));

  SendLocal (result);
}

void
Epidemic::R2A_eca (Ptr<Tuple> eMessageDel)
{
  RAPIDNET_LOG_INFO ("R2A_eca triggered");

  Ptr<Tuple> result = eMessageDel;

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    TMESSAGE,
    strlist ("Local",
      "eMessageDel_attr2",
      "eMessageDel_attr3",
      "eMessageDel_attr4",
      "eMessageDel_attr5"),
    strlist ("tMessage_attr1",
      "tMessage_attr2",
      "tMessage_attr3",
      "tMessage_attr4",
      "tMessage_attr5"));

  Delete (result);
}

void
Epidemic::R2B_eca (Ptr<Tuple> eMessageDel)
{
  RAPIDNET_LOG_INFO ("R2B_eca triggered");

  Ptr<RelationBase> result;

  result = GetRelation (TSUMMARYVEC)->Join (
    eMessageDel,
    strlist ("tSummaryVec_attr1"),
    strlist ("eMessageDel_attr1"));

  result->Assign (Assignor::New ("SummaryVecUpdate",
    FSvRemove::New (
      VarExpr::New ("tSummaryVec_attr2"),
      VarExpr::New ("eMessageDel_attr4"))));

  result->Assign (Assignor::New ("Local",
    LOCAL_ADDRESS));

  result = result->Project (
    TSUMMARYVEC,
    strlist ("Local",
      "SummaryVecUpdate"),
    strlist ("tSummaryVec_attr1",
      "tSummaryVec_attr2"));

  Insert (result);
}

