/// File: Header for the test case parser and manager
///
// Copyright (C) Microsoft Corporation
// SPDX-License-Identifier: MIT

#ifndef _X86_EXECUTOR_TC_H_
#define _X86_EXECUTOR_TC_H_

#include <linux/types.h>

#define MAX_ACTORS 16
#define MAX_SECTIONS MAX_ACTORS
#define MAX_SYMBOLS 128
#define MAX_EXPANDED_SECTION_SIZE (4096 * 4)
#define MAX_SECTION_SIZE 4096 // NOTE: must be exactly 1 page to detect sysfs buffering
#define MAX_MEASUREMENT_CODE_SIZE (4096 * 2)
#define TC_HEADER_SIZE (2 * sizeof(uint64_t))

typedef uint64_t section_size_t;
typedef uint64_t section_metadata_reserved_t;
typedef uint64_t section_id_t;
typedef uint64_t symbol_offset_t;
typedef uint64_t symbol_id_t;

typedef struct
{
    uint32_t actor_type;
    uint32_t actor_subid;
} actor_id_t;

typedef struct
{
    actor_id_t owner_id;
    section_size_t size;
    section_metadata_reserved_t reserved;
} tc_section_metadata_entry_t;

typedef struct
{
    char code[MAX_SECTION_SIZE];
} tc_section_t;

typedef struct
{
    actor_id_t owner_id;
    symbol_offset_t offset;
    symbol_id_t id;
} tc_symbol_entry_t;

typedef struct
{
    size_t symbol_table_size;
    size_t metadata_size;
    size_t sections_size;
    tc_symbol_entry_t *symbol_table;
    tc_section_metadata_entry_t *metadata;
    tc_section_t *sections;
} test_case_t;

extern size_t n_actors;
extern int loaded_tc_size;

// Outdated variables - to be removed soon
extern char *test_case_main;
extern char *measurement_code;
extern char *measurement_template;

ssize_t parse_test_case_buffer(const char *buf, size_t count, bool *finished);
bool tc_parsing_completed(void);
int init_test_case_manager(void);
void free_test_case_manager(void);

#endif // _X86_EXECUTOR_TC_H_
