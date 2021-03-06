/*
 * Copyright © 2016-2017 VMware, Inc.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, without
 * warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */


#pragma once
#include <stdint.h>

#include "../../common/includes.h"
#include <dce/dcethread.h>
#include <dce/lrpc.h>
#include <dce/rpc.h>

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <shadow.h>

#include <pmd.h>
#include "defines.h"
#include "structs.h"
#include "pmdsecurity.h"
#include "prototypes.h"

#include<ldap.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

