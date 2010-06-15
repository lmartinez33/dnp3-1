#include "DOTerminalExtension.h"

#include <APL/Util.h>
#include <APL/Exception.h>
#include <APL/Parsing.h>

#include <sstream>
#include <boost/bind.hpp>

using namespace std;
using namespace boost;

namespace apl
{
	void DOTerminalExtension::_BindToTerminal(ITerminal* apTerminal)
	{
		CommandNode cmd;

		cmd.mName = "bi";
		cmd.mUsage = "queue bi <index> <0|1> <quality>";
		cmd.mDesc = "Queues a binary input value into the transaction buffer";
		cmd.mHandler = boost::bind(&DOTerminalExtension::HandleQueueBinary, this, _1);
		apTerminal->BindCommand(cmd, "queue bi");

		cmd.mName = "ai";
		cmd.mUsage = "queue ai <index> <value> <quality>";
		cmd.mDesc = "Queues an analog input value into the transaction buffer";
		cmd.mHandler = boost::bind(&DOTerminalExtension::HandleQueueAnalog, this, _1);
		apTerminal->BindCommand(cmd, "queue ai");

		cmd.mName = "c";
		cmd.mUsage = "queue c <index> <value> <quality>";
		cmd.mDesc = "Queues an counter value into the transaction buffer";
		cmd.mHandler = boost::bind(&DOTerminalExtension::HandleQueueCounter, this, _1);
		apTerminal->BindCommand(cmd, "queue c");

		cmd.mName = "flush";
		cmd.mUsage = "flush";
		cmd.mDesc = "Flushes the output queues to the data observer (an optional number of times).";
		cmd.mHandler = boost::bind(&DOTerminalExtension::HandleDoTransaction, this, _1);
		apTerminal->BindCommand(cmd, "flush");
	}

	retcode DOTerminalExtension::HandleDoTransaction(std::vector<std::string>& arArgs)
	{	
		if(arArgs.size() > 0) return BAD_ARGUMENTS;
		mBuffer.FlushUpdates(mpObserver);
		return SUCCESS;
	}
		
}
