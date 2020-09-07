/*
 * Copyright 2020 nick_couchman.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "common/xattr.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>

/**
 * Retrieve the HSM flags for a particular file by reading the extended
 * attribute containing the flags. If nothing is read the default of 0
 * will be returned, indicating no flags are set.
 * 
 * @param fd
 *     The file descriptor pointing to the file whose extended attribute is
 *     being queried for HSM-related flags.
 * 
 * @return 
 *     The flags set on a particular file, or 0 if no flags are set.
 */
static uint8_t get_flags(int fd) {
    uint8_t flags = 0;
    fgetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags));
    return flags;
}

/**
 * Retrieve the file stat info for a particular stub file as stored in the
 * extended attribute. This reads the data out of the extended attribute and
 * allocates a character array for it, storing the value in the character array.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose extended attributes
 *     are being queried.
 * 
 * @return 
 *     A character array with the data from the stat extended attribute, or
 *     NULL if no data is present.
 */
static char* get_stats(int fd) {
    ssize_t xa_size = fgetxattr(fd, HSM_XATTR_STAT_NAME, NULL, 0);
    if (xa_size > 0) {
        char* stats = malloc(xa_size);
        fgetxattr(fd, HSM_XATTR_STAT_NAME, stats, xa_size);
        return stats;
    }
    return NULL;
}

ssize_t hsm_clear_dirty(int fd) {
	uint8_t flags = get_flags(fd);
	flags ~= HSM_XATTR_FLAG_DIRTY;
	return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_clear_lost(int fd) {
    uint8_t flags = get_flags(fd);
    flags ~= HSM_XATTR_FLAG_LOST;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_clear_recall(int fd) {
    uint8_t flags = get_flags(fd);
    flags ~= HSM_XATTR_FLAG_RECALL;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_clear_stub(int fd) {
    uint8_t flags = get_flags(fd);
    flags ~= HSM_XATTR_FLAG_STUB;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

int hsm_is_dirty(int fd) {
	return (get_flags(fd) & HSM_XATTR_FLAG_DIRTY);
}

int hsm_is_lost(int fd) {
	return (get_flags(fd) & HSM_XATTR_FLAG_LOST);
}

int hsm_is_recalled(int fd) {
	return (get_flags(fd) & HSM_XATTR_FLAG_RECALL);
}

int hsm_is_stub(int fd) {
	return (get_flags(fd) & HSM_XATTR_FLAG_STUB);
}

ssize_t hsm_mark_dirty(int fd) {
    uint8_t flags = get_flags(fd);
    flags |= HSM_XATTR_FLAG_DIRTY;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_mark_lost(int fd) {
    uint8_t flags = get_flags(fd);
    flags |= HSM_XATTR_FLAG_LOST;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_mark_recall(int fd) {
    uint8_t flags = get_flags(fd);
    flags |= HSM_XATTR_FLAG_RECALL;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}

ssize_t hsm_mark_stub(int fd) {
    uint8_t flags = get_flags(fd);
    flags |= HSM_XATTR_FLAG_STUB;
    return fsetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags), 0);
}