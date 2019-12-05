
#include "common.h"
#include "protocol.h"
#include "pcie_mcc.h"
#include "pcie_msg.h"

#define PCIE_MSG_TEST_PORT 		355

static int32_t remote_id[PCIE_MAX_CHIPNUM];
static void print_usage(void)
{
	printf("pciemcc usage: \n");
}

static int pcie_init(int32_t pcie_dev_id)
{
	int ret = 0;
	ret |= pcie_wait_connect(pcie_dev_id);

	ret |= pcie_open_msgport(pcie_dev_id, PCIE_MSG_TEST_PORT);

	if(ret)
		return -1;
	else
		return 0;
}

static int pcie_deinit(int32_t pcie_dev_id)
{
	int ret = 0;
	ret |= pcie_close_msgport(pcie_dev_id, PCIE_MSG_TEST_PORT);

	if(ret)
		return -1;
	else
		return 0;
}

static int pcie_send_rcv_msg(int32_t pcie_dev_id)
{
	int ret;
	int retry;
	tDebugInfoFrame debug_sndmsg;
	tDebugInfoFrame debug_rcvmsg;

	ret = pcie_send_msg(pcie_dev_id, PCIE_MSG_TEST_PORT, &debug_sndmsg, sizeof(debug_sndmsg));
	if(ret < 0)
		return -1;

	retry = 0;
	while(pcie_recv_msg(pcie_dev_id, PCIE_MSG_TEST_PORT, &debug_rcvmsg, sizeof(debug_rcvmsg)) < 0)
	{
		usleep(10000);
		retry++;

		if(retry >= 100)
		{
			printf("Don't receive msg, timeout\n");
			break;
		}
	}

	return 0;
}

static int msg_test(void)
{
	int i;
	int ret;
	int32_t count;

	for(i=0; i<PCIE_MAX_CHIPNUM; i++)
	{
		remote_id[i] = 0;
	}

	ret = pcie_get_remoteid(remote_id, &count);
	if(ret < 0)
	{
		return -1;
	}

	for(i=0; i<count; i++)
	{
		pcie_init(remote_id[i]);
		pcie_send_rcv_msg(remote_id[i]);
		pcie_deinit(remote_id[i]);
	}

	return 0;
}
int main(int argc, char **argv)
{

	print_usage();

	msg_test();

	return 0;
}
