/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2013      Mellanox Technologies, Inc.
 *                         All rights reserved.
 * Copyright (c) 2015      Los Alamos National Security, LLC. All rights
 *                         reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */
#include "oshmem_config.h"
#include "opal/util/output.h"
#include "oshmem/mca/memheap/memheap.h"
#include "oshmem/mca/memheap/base/base.h"
#include "oshmem/mca/memheap/buddy/memheap_buddy.h"
#include "memheap_buddy_component.h"

static int mca_memheap_buddy_component_close(void);
static mca_memheap_base_module_t* mca_memheap_buddy_component_init(memheap_context_t *,
                                                                   int *);

static int _basic_open(void);

mca_memheap_base_component_t mca_memheap_buddy_component = {
    .memheap_version = {
        MCA_MEMHEAP_BASE_VERSION_2_0_0,

        .mca_component_name = "buddy",
        MCA_BASE_MAKE_VERSION(component, OSHMEM_MAJOR_VERSION, OSHMEM_MINOR_VERSION,
                              OSHMEM_RELEASE_VERSION),

        .mca_open_component = _basic_open,
        .mca_close_component = mca_memheap_buddy_component_close,
    },
    .memheap_data = {
        /* The component is checkpoint ready */
        MCA_BASE_METADATA_PARAM_CHECKPOINT
    },
    .memheap_init = mca_memheap_buddy_component_init,
};

/* Open component */
static int _basic_open(void)
{
    return OSHMEM_SUCCESS;
}

/* Initialize component */
mca_memheap_base_module_t* mca_memheap_buddy_component_init(memheap_context_t *context,
                                                            int *priority)
{
    int rc;

    *priority = memheap_buddy.priority;
    rc = mca_memheap_buddy_module_init(context);
    if (OSHMEM_SUCCESS != rc) {
        return NULL ;
    }

    return &(memheap_buddy.super);
}

/*
 * This function is automaticaly called from mca_base_components_close.
 * It releases the component's allocated memory.
 */
int mca_memheap_buddy_component_close()
{
    mca_memheap_buddy_finalize();
    return OSHMEM_SUCCESS;
}
