/*
 * Copyright (c) 2022, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPMC_H
#define SPMC_H

#include <stdint.h>

#include <lib/psci/psci.h>
#include <lib/spinlock.h>
#include "spm_common.h"

/*
 * Ranges of FF-A IDs for Normal world and Secure world components. The
 * convention matches that used by other SPMCs i.e. Hafnium and OP-TEE.
 */
#define FFA_NWD_ID_BASE		0x0
#define FFA_NWD_ID_LIMIT	0x7FFF
#define FFA_SWD_ID_BASE		0x8000
#define FFA_SWD_ID_LIMIT	SPMD_DIRECT_MSG_ENDPOINT_ID - 1
#define FFA_SWD_ID_MASK		0x8000

/* ID 0 is reserved for the normal world entity, (Hypervisor or OS Kernel). */
#define FFA_NWD_ID		U(0)
/* First ID is reserved for the SPMC */
#define FFA_SPMC_ID		U(FFA_SWD_ID_BASE)
/* SP IDs are allocated after the SPMC ID */
#define FFA_SP_ID_BASE		(FFA_SPMC_ID + 1)
/* Align with Hafnium implementation */
#define INV_SP_ID		0x7FFF

/* FF-A warm boot types. */
#define FFA_WB_TYPE_S2RAM	0
#define FFA_WB_TYPE_NOTS2RAM	1

/*
 * Runtime states of an execution context as per the FF-A v1.1 specification.
 */
enum sp_runtime_states {
	RT_STATE_WAITING,
	RT_STATE_RUNNING,
	RT_STATE_PREEMPTED,
	RT_STATE_BLOCKED
};

/*
 * Runtime model of an execution context as per the FF-A v1.1 specification. Its
 * value is valid only if the execution context is not in the waiting state.
 */
enum sp_runtime_model {
	RT_MODEL_DIR_REQ,
	RT_MODEL_RUN,
	RT_MODEL_INIT,
	RT_MODEL_INTR
};

enum sp_runtime_el {
	EL1 = 0,
	S_EL0,
	S_EL1
};

enum sp_execution_state {
	SP_STATE_AARCH64 = 0,
	SP_STATE_AARCH32
};

/*
 * Execution context members for an SP. This is a bit like struct
 * vcpu in a hypervisor.
 */
struct sp_exec_ctx {
	/*
	 * Store the stack address to restore C runtime context from after
	 * returning from a synchronous entry into the SP.
	 */
	uint64_t c_rt_ctx;

	/* Space to maintain the architectural state of an SP. */
	cpu_context_t cpu_ctx;

	/* Track the current runtime state of the SP. */
	enum sp_runtime_states rt_state;

	/* Track the current runtime model of the SP. */
	enum sp_runtime_model rt_model;
};

/*
 * Structure to describe the cumulative properties of an SP.
 */
struct secure_partition_desc {
	/*
	 * Execution contexts allocated to this endpoint. Ideally,
	 * we need as many contexts as there are physical cpus only
	 * for a S-EL1 SP which is MP-pinned.
	 */
	struct sp_exec_ctx ec[PLATFORM_CORE_COUNT];

	/* ID of the Secure Partition. */
	uint16_t sp_id;

	/* Runtime EL. */
	enum sp_runtime_el runtime_el;

	/* Partition UUID. */
	uint32_t uuid[4];

	/* Partition Properties. */
	uint32_t properties;

	/* Supported FF-A Version. */
	uint32_t ffa_version;

	/* Execution State. */
	enum sp_execution_state execution_state;

	/* Secondary entrypoint. Only valid for a S-EL1 SP. */
	uintptr_t secondary_ep;
};

/*
 * This define identifies the only SP that will be initialised and participate
 * in FF-A communication. The implementation leaves the door open for more SPs
 * to be managed in future but for now it is reasonable to assume that either a
 * single S-EL0 or a single S-EL1 SP will be supported. This define will be used
 * to identify which SP descriptor to initialise and manage during SP runtime.
 */
#define ACTIVE_SP_DESC_INDEX	0

/*
 * Structure to describe the cumulative properties of the Hypervisor and
 * NS-Endpoints.
 */
struct ns_endpoint_desc {
	/*
	 * ID of the NS-Endpoint or Hypervisor.
	 */
	uint16_t ns_ep_id;

	/*
	 * Supported FF-A Version.
	 */
	uint32_t ffa_version;
};

/* Setup Function for different SP types. */
void spmc_sp_common_setup(struct secure_partition_desc *sp,
			  entry_point_info_t *ep_info);
void spmc_el1_sp_setup(struct secure_partition_desc *sp,
		       entry_point_info_t *ep_info);
void spmc_sp_common_ep_commit(struct secure_partition_desc *sp,
			      entry_point_info_t *ep_info);

/*
 * Helper function to perform a synchronous entry into a SP.
 */
uint64_t spmc_sp_synchronous_entry(struct sp_exec_ctx *ec);

/*
 * Helper function to obtain the descriptor of the current SP on a physical cpu.
 */
struct secure_partition_desc *spmc_get_current_sp_ctx(void);

/*
 * Helper function to obtain the execution context of an SP on a
 * physical cpu.
 */
struct sp_exec_ctx *spmc_get_sp_ec(struct secure_partition_desc *sp);

/*
 * Helper function to obtain the index of the execution context of an SP on a
 * physical cpu.
 */
unsigned int get_ec_index(struct secure_partition_desc *sp);

uint64_t spmc_ffa_error_return(void *handle, int error_code);

/*
 * Ensure a partition ID does not clash and follows the secure world convention.
 */
bool is_ffa_secure_id_valid(uint16_t partition_id);

#endif /* SPMC_H */
