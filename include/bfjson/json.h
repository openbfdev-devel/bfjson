/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright(c) 2023 John Sanpe <sanpeqf@gmail.com>
 */

#ifndef _BFJSON_JSON_H_
#define _BFJSON_JSON_H_

#include <bfjson/config.h>
#include <bfdev/allocator.h>
#include <bfdev/bitflags.h>
#include <bfdev/list.h>

BFDEV_BEGIN_DECLS

enum bfjson_flags {
    __BFJSON_IS_ARRAY = 0,
    __BFJSON_IS_OBJECT,
    __BFJSON_IS_STRING,
    __BFJSON_IS_NUMBER,
    __BFJSON_IS_NULL,
    __BFJSON_IS_TRUE,
    __BFJSON_IS_FALSE,

    BFJSON_IS_ARRAY   = BFDEV_BIT(__BFJSON_IS_ARRAY),
    BFJSON_IS_OBJECT  = BFDEV_BIT(__BFJSON_IS_OBJECT),
    BFJSON_IS_STRING  = BFDEV_BIT(__BFJSON_IS_STRING),
    BFJSON_IS_NUMBER  = BFDEV_BIT(__BFJSON_IS_NUMBER),
    BFJSON_IS_NULL    = BFDEV_BIT(__BFJSON_IS_NULL),
    BFJSON_IS_TRUE    = BFDEV_BIT(__BFJSON_IS_TRUE),
    BFJSON_IS_FALSE   = BFDEV_BIT(__BFJSON_IS_FALSE),
};

/**
 * struct bfjson_node - Describe a json structure.
 * @parent: point to the parent structure.
 * @sibling: list nodes hung on @child.
 * @flags: attributes bitmap.
 * @name: the name of the node.
 */
struct bfjson_node {
    struct bfjson_node *parent;
    struct bfdev_list_head sibling;
    unsigned long flags;
    const char *name;

    union {
        struct bfdev_list_head child;
        long number;
        char *string;
    };
};

BFDEV_BITFLAGS_STRUCT(bfjson, struct bfjson_node, flags)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, array, __BFJSON_IS_ARRAY)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, object, __BFJSON_IS_OBJECT)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, string, __BFJSON_IS_STRING)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, number, __BFJSON_IS_NUMBER)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, null, __BFJSON_IS_NULL)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, true, __BFJSON_IS_TRUE)
BFDEV_BITFLAGS_STRUCT_FLAG(bfjson, struct bfjson_node, flags, false, __BFJSON_IS_FALSE)

/**
 * bfjson_decode() - Decode json to syntax tree.
 * @alloc: allocator callback.
 * @buff: the json data to be decode.
 * @root: syntax tree root node pointer.
 */
extern int
bfjson_decode(const struct bfdev_alloc *alloc, const char *buff,
                  struct bfjson_node **root);

/**
 * bfjson_encode() - Encode syntax tree to json.
 * @root: syntax tree root node pointer.
 * @buff: buffer for outputting json.
 * @size: the size of @buff.
 */
extern int
bfjson_encode(const struct bfjson_node *root, char *buff, int size);

/**
 * bfjson_release() - Release json syntax tree.
 * @alloc: allocator callback.
 * @root: syntax tree root node pointer.
 */
extern void
bfjson_release(const struct bfdev_alloc *alloc,
                   struct bfjson_node *root);

BFDEV_END_DECLS

#endif /* _BFJSON_JSON_H_ */
