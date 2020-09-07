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

#ifndef XATTR_H
#define XATTR_H

/**
 * The name of the extended attribute that stores the HSM-related flags
 * for a particular file. 
 */
#define HSM_XATTR_FLAG_NAME "user.hsm.flags"

/**
 * The bit in the HSM flags that indicates that the file is a stub and the
 * data associated with the file has been removed from the local filesystem
 * and is stored solely in the cloud.
 * 
 * @see HSM_XATTR_FLAG_NAME
 */
#define HSM_XATTR_FLAG_STUB 1

/**
 * The bit in the HSM flags that indicates that the file has been recalled
 * from the cloud back to local primary storage. This bit should only be
 * set if the file is also a stub file, and will be unset when the recall is
 * completed.
 * 
 * @see HSM_XATTR_FLAG_NAME
 * @see HSM_XATTR_FLAG_STUB
 */
#define HSM_XATTR_FLAG_RECALL 2

/**
 * The bit in the HSM flags that indicates that the file is "dirty", meaning
 * that the local data in the file has changed and the file needs to be
 * synchronized to the cloud.
 * 
 * @see HSM_XATTR_FLAG_NAME
 */
#define HSM_XATTR_FLAG_DIRTY 4

/**
 * The bit in the HSM flags that indicates that the file has been "lost" - that
 * is, it is a stub file, but the cloud version of it could not be located or
 * retrieved. Manual steps may be required to locate the file(s) and reconnect
 * local filesystem stub(s) with cloud files.
 * 
 * @see HSM_XATTR_FLAG_NAME
 * @see HSM_XATTR_FLAG_STUB
 */
#define HSM_XATTR_FLAG_LOST 8

/**
 * The extended attribute (xattr) that stores the file stat information for
 * a file that has been stubbed to the cloud. This data can be used by
 * applications that need to display the original file stats (rather than
 * those of the stub file). The format of the data is:
 * 
 * /[size (bytes)]/[atime (ns)]/[ctime (ns)]/[mtime (ns)]
 */
#define HSM_XATTR_STAT_NAME "user.hsm.stat"

/**
 * Clear the dirty flag from a file given a file descriptor that points to
 * the file. This marks the file as "clean", meaning that local file contents
 * and cloud contents have been synchronized.
 * 
 * @param fd
 *     The file descriptor of the file that should be marked as clean.
 * 
 * @return 
 *     The number of bytes written to the xattr for storing flags.
 */
ssize_t hsm_clear_dirty(int fd);

/**
 * Clear the "lost" flags on a file given a file descriptor pointing to the
 * file. This clears the status that indicates that the cloud portion of a
 * stubbed file has been lost.
 * 
 * @param fd
 *     The file descriptor of a file whose lost flag should be cleared.
 * 
 * @return 
 *     The number of bytes written to the xattr for storing the flags.
 */
ssize_t hsm_clear_lost(int fd);

/**
 * Clear the "recall" flag from a file given a file descriptor pointing to the
 * file. This indicates that the recall operation on a file is no longer in
 * progress - it has either succeeded, resulting in the stub flag also being
 * cleared, or it has failed, resulting in the lost flag being set.
 * 
 * @param fd
 *     A file descriptor pointing to the file whose recall flag should be
 *     cleared.
 * 
 * @return 
 *     The number of bytes written to the xattr when setting the flags.
 */
ssize_t hsm_clear_recall(int fd);

/**
 * Clear the "stub" flag on a file given a file descriptor pointing to the file
 * whose flag should be cleared. This indicates that the contents of a file
 * has been downloaded from the cloud and places back on the filesystem.
 * 
 * @param fd
 *     A file descriptor pointing to a file whose stub flag should be cleared.
 * 
 * @return 
 *     The number of bytes written to the xattr when storing the flags.
 */
ssize_t hsm_clear_stub(int fd);

/**
 * Retrieve the stored atime value from the xattr for a stub file. For stub
 * files this may be different from the real file that was replaced, so the
 * atime value is stored in an xattr at the time that the file is stubbed.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose atime is being
 *     retrieved.
 * 
 * @return 
 *     The UNIX timestamp for the atime value.
 */
int hsm_get_atime(int fd);

/**
 * Retrieve the stored ctime value from the xattr for a stub file. For stub
 * files this may be different from the real file that was replaced, so the
 * ctime value is stored in an xattr at the time that the file is stubbed.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose ctime is being
 *     retrieved.
 * 
 * @return 
 *     The UNIX timestamp for the ctime value.
 */
int hsm_get_ctime(int fd);

/**
 * Retrieve the stored mtime value from the xattr for a stub file. For stub
 * files this may be different from the real file that was replaced, so the
 * mtime value is stored in an xattr at the time that the file is stubbed.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose mtime is being
 *     retrieved.
 * 
 * @return 
 *     The UNIX timestamp for the mtime value.
 */
int hsm_get_mtime(int fd);

/**
 * Retrieve the stored size value from the xattr for a stub file. For stub
 * files this will be different from the real file that was replaced, so the
 * size value is stored in an xattr at the time that the file is stubbed.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose size is being
 *     retrieved.
 * 
 * @return 
 *     The size, in bytes, of the file.
 */
ssize_t hsm_get_size(int fd);

/**
 * Returns the status of a file as dirty or clean, zero indicating that the file
 * is clean and its contents are synchronized to the cloud, and non-zero
 * indicating that the file is dirty and needs to be synchronized.
 * 
 * @param fd
 *     A file descriptor of a file whose dirty status is being checked.
 * 
 * @return 
 *     Zero if the file is "clean", non-zero if the file is "dirty".
 */
int hsm_is_dirty(int fd);

/**
 * Returns the status of a file as lost, meaning that the file has been stubbed
 * to the cloud, but the cloud version of the file cannot be located. The status
 * will be zero if the file is not lost, or non-zero if the file has been lost.
 * 
 * @param fd
 *     The file descriptor for the file whose lost status should be checked.
 * 
 * @return 
 *     Zero if the file is not lost, or non-zero if the file has been lost.
 */
int hsm_is_lost(int fd);

/**
 * Returns the status of a file as in the process of being recalled, zero
 * indicating that no recall is in process and non-zero indicating that the
 * file is in the process of being recalled.
 * 
 * @param fd
 *     The file descriptor pointing to the file whose recall status is being
 *     checked.
 * 
 * @return 
 *     Zero if the file is not in the process of being recalled, or non-zero if
 *     the file is in the process of being recalled.
 */
int hsm_is_recalled(int fd);

/**
 * Returns the status of a file as a stub, with zero indicating that the file is
 * not a stub and its contents are expected to be present on the local
 * filesystem, and non-zero indicating that the file is a stub and its contents
 * have been removed from the local filesystem and are now solely in the cloud.
 * 
 * @param fd
 *     The file descriptor pointing to the file whose status is being checked
 *     to see if the file is a stub or not.
 * 
 * @return 
 *     Zero if the file is not a stub and expected to be completely present on
 *     the local filesystem; non-zero if the file contents have been removed
 *     from the local filesystem and are stored solely in the cloud.
 */
int hsm_is_stub(int fd);

/**
 * Mark a file as dirty, setting the xattr flag, to indicate that the file
 * contents have been modified on-disk and need to be synchronized to the cloud.
 * 
 * @param fd
 *     The file descriptor pointing to the file whose contents now need to be
 *     synchronized to the cloud.
 * 
 * @return 
 *     The number of bytes written to the xattr that stores HSM-related flags
 *     for the file.
 */
ssize_t hsm_mark_dirty(int fd);

/**
 * Mark a file as lost by setting the appropriate xattr flag on the file, which
 * indicates that the stub file cannot be located or retrieved from its
 * expected location in the cloud.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose cloud counterpart
 *     cannot be located.
 * 
 * @return 
 *     The number of bytes written to the xattr that stores HSM-related flags
 *     for the file.
 */
ssize_t hsm_mark_lost(int fd);

/**
 * Mark a file as in the process of being recalled from the cloud by setting
 * the appropriate xattr bit for the file. This indicates that the contents of
 * a stub file have been requested and queued for download from the cloud.
 * 
 * @param fd
 *     The file descriptor pointing to the stub file whose contents should
 *     be retrieved from the cloud.
 * 
 * @return 
 *     The number of bytes written to the xattr that stores HSM-related flags
 *     for the file.
 */
ssize_t hsm_mark_recall(int fd);

/**
 * Mark a file as a stub, indicating that the contents of the file are being
 * removed from the local filesystem and that only the cloud version of the
 * file will contain the file data.
 * 
 * @param fd
 *     The file descriptor of the file whose contents are being removed from
 *     the local filesystem and will only be present in the cloud.
 * 
 * @return 
 *     The number of bytes written to the xattr that stores HSM-related flags
 *     for the file.
 */
ssize_t hsm_mark_stub(int fd);

ssize_t hsm_set_atime(int fd);

ssize_t hsm_set_ctime(int fd);

ssize_t hsm_set_mtime(int fd);

ssize_t hsm_set_size(int fd);

#endif /* XATTR_H */

