/**
 * Header containing common definitions for HSM-related
 * extended attributes.
 */

#ifndef COMMON_HSM_XATTR_H
#define COMMON_HSM_XATTR_H

#include "config.h"

#define HSM_XATTR_FLAG_NAME "user.hsm.flags"

#define HSM_XATTR_FLAG_STUB 1

#define HSM_XATTR_FLAG_RECALL 2

#define HSM_XATTR_FLAG_DIRTY 4

#define HSM_XATTR_FLAG_LOST 8

ssize_t hsm_clear_dirty(int fd);

ssize_t hsm_clear_lost(int fd);

ssize_t hsm_clear_recall(int fd);

ssize_t hsm_clear_stub(int fd);

int hsm_is_dirty(int fd);

int hsm_is_lost(int fd);

int hsm_is_recalled(int fd);

int hsm_is_stub(int fd);

ssize_t hsm_mark_dirty(int fd);

ssize_t hsm_mark_lost(int fd);

ssize_t hsm_mark_recall(int fd);

ssize_t hsm_mark_stub(int fd);

#endif
