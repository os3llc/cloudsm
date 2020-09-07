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

#ifndef CONF_H
#define CONF_H

#include <filesystem>
#include <string>

using namespace std;

/**
 * A class that implements the required methods for gathering configuration
 * information from the CloudSM configuration file.
 */
class conf {
public:
    
    /**
     * Default constructor, which takes no arguments, assuming the default
     * configuration file location.
     */
    conf();
    
    /**
     * Constructor that takes a string
     */
    conf(string config_file);
    
    /**
     * Constructor which copies another conf class.
     * 
     * @param orig
     *     The conf class whose settings are being copied.
     */
    conf(const conf& orig);
    
    /**
     * Returns the location of the configuration file.
     * 
     * @return 
     *     The absolute path to the configuration file.
     */
    string get_config_file();
    
    /**
     * Class destructor.
     */
    virtual ~conf();
    
private:
    
    /**
     * The string containing the filesystem path to the configuration file.
     */
    string config_file;

};

#endif /* CONF_H */

