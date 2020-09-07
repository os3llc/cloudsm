/*
 * Copyright 2020 OS3 LLC.
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

/* 
 * File:   s3.h
 * Author: nick_couchman
 *
 * Created on September 7, 2020, 7:26 AM
 */

#ifndef S3_H
#define S3_H

#include <stdbool.h>
#include <string>

using namespace std;

class s3 {
public:
    
    /**
     * Empty s3 class constructor.
     */
    s3();
    
    /**
     * Constructor for s3 which takes all of the available fields.
     * 
     * @param bucket
     *     The bucket where data will be stored.
     * 
     * @param prefix
     *     The prefix within the bucket that will serve as the base for the
     *     data.
     * 
     * @param access_key
     *     The access key to use to access the S3 bucket.
     * 
     * @param secret_key
     *     The access secret key to use to access the S3 bucket.
     */
    s3(string bucket, string prefix, string access_key, string secret_key);
    
    /**
     * A constructor that takes only the S3 bucket and prefix. This is useful
     * for situations where this code is run within an EC2 instance and a role
     * is assigned to the instance and an access key and secret key are not
     * required.
     * 
     * @param bucket
     *     The S3 bucket where data will be stored.
     * 
     * @param prefix
     *     The prefix within the S3 bucket that will be used as the base for
     *     storing data.
     */
    s3(string bucket, string prefix);
    
    /**
     * Constructor for s3 class that copies an existing s3 class object.
     */
    s3(const s3& orig);
    
    /**
     * Upload the file specified by the file descriptor, returning the number
     * of bytes uploaded, or -1 if the upload fails.
     * 
     * @param fd
     *     The file descriptor of the file that should be uploaded.
     * 
     * @return 
     *     The number of bytes uploaded, or -1 if an error occurs.
     */
    int upload_file(int fd);
    
    /**
     * Download the file specified by the file descriptor into the location on
     * the filesystem, returning the number of bytes downloaded, or -1 if an
     * error occurs downloading the file. The key of the file in the S3 bucket
     * will be determined by concatenating the bucket name, base prefix, and
     * then the directory path of the file on the filesystem to get the full S3
     * object key.
     * 
     * @param fd
     *     The file descriptor of the file that should be retrieved from the
     *     S3 bucket.
     * 
     * @return
     *     The number of bytes downloaded, or -1 if an error occurs.
     */
    int download_file(int fd);
    
    /**
     * Destructor for the s3 class.
     */
    virtual ~s3();
    
private:
    
    /**
     * The S3 bucket where data will be stored. This is required.
     */
    string bucket;
    
    /**
     * The prefix within the S3 bucket where the files will be based. This is
     * required.
     */
    string prefix;
    
    /**
     * The access key for the S3 bucket. This is optional in situations where
     * an IAM role is used to access the bucket.
     */
    string access_key;
    
    /**
     * The access secret for the S3 bucket. This is optional in situations where
     * an IAM role is used to access the bucket.
     */
    string secret_key;

};

#endif /* S3_H */

