#if LAB >= 4
// User-level IPC library routines

#include "lib.h"

// Send val to whom.  This function keeps trying until
// it succeeds.  It should panic() on any error other than
// -E_IPC_NOT_RECV.  
//
// Hint: use sys_yield() to be CPU-friendly.
void
ipc_send(u_int whom, u_int val)
{
#if SOL >= 4
	int r;

	while ((r=sys_ipc_can_send(whom, val)) == -E_IPC_NOT_RECV)
		sys_yield();
	if(r == 0)
		return;
	panic("error in ipc_send: %e", r);
#else
	// Your code here.
	panic("ipc_send not implemented");
#endif
}

// Receive a value.  Return the value and store the caller's envid
// in *whom.  
//
// Hint: use env to discover the value and who sent it.
u_int
ipc_recv(u_int *whom)
{
#if SOL >= 4
	sys_ipc_recv();
	*whom = env->env_ipc_from;
	return env->env_ipc_value;
#else
	// Your code here
	panic("ipc_recv not implemented");
	return 0;
#endif
}

#endif