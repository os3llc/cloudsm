/**
 * Implementations of functions dealing with xattr-related
 * HSM functionality for the CloudSM project.
 */

#include "common/hsm_xattr.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>

static uint8_t get_flags(int fd) {
    uint8_t flags = 0;
    ssize_t xasize = fgetxattr(fd, HSM_XATTR_FLAG_NAME, &flags, sizeof(flags));
    return flags;
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
	return (get_falgs(fd) & HSM_XATTR_FLAG_STUB);
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

