/*
 * Copyright (C) 2025 LineageOS Project
 *
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <fstream>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <string.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;

std::vector<string> ro_props_default_source_order = {
    "",
    "bootimage.",
    "odm.",
    "product.",
    "system.",
    "system_ext.",
    "vendor."
};

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info *pi;

    pi = (prop_info *)__system_property_find(prop);

    if (pi)
	__system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void load_dalvikvm_properties() {
  struct sysinfo sys;
  sysinfo(&sys);
  if (sys.totalram > 6144ull * 1024 * 1024) {
    // 8GB RAM - max multitasking
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "640m");
    property_override("dalvik.vm.heapsize", "1536m");
    property_override("dalvik.vm.heaptargetutilization", "0.75");
    property_override("dalvik.vm.heapminfree", "8m");
    property_override("dalvik.vm.heapmaxfree", "32m");
    
    property_override("ro.lmk.psi_complete_stall_ms", "180");
    property_override("ro.lmk.psi_partial_stall_ms", "90");
    property_override("ro.lmk.thrashing_limit", "40");
    property_override("ro.lmk.thrashing_limit_critical", "45");
    property_override("ro.lmk.thrashing_limit_decay", "15");
    property_override("ro.lmk.filecache_min_kb", "300000");
    property_override("ro.lmk.kill_timeout_ms", "1500");
    }
  else if (sys.totalram > 4096ull * 1024 * 1024) {
    // 6GB RAM - balanced multitasking
    property_override("dalvik.vm.heapstartsize", "16m");
    property_override("dalvik.vm.heapgrowthlimit", "512m");
    property_override("dalvik.vm.heapsize", "1024m");
    property_override("dalvik.vm.heaptargetutilization", "0.70");
    property_override("dalvik.vm.heapminfree", "4m");
    property_override("dalvik.vm.heapmaxfree", "16m");
    
    property_override("ro.lmk.psi_complete_stall_ms", "150");
    property_override("ro.lmk.psi_partial_stall_ms", "70");
    property_override("ro.lmk.thrashing_limit", "35");
    property_override("ro.lmk.thrashing_limit_critical", "40");
    property_override("ro.lmk.thrashing_limit_decay", "20");
    property_override("ro.lmk.filecache_min_kb", "256000");
    property_override("ro.lmk.kill_timeout_ms", "1000");
    }
  else {
    // 4GB RAM - battery friendly
    property_override("dalvik.vm.heapstartsize", "8m");
    property_override("dalvik.vm.heapgrowthlimit", "256m");
    property_override("dalvik.vm.heapsize", "512m");
    property_override("dalvik.vm.heaptargetutilization", "0.65");
    property_override("dalvik.vm.heapminfree", "2m");
    property_override("dalvik.vm.heapmaxfree", "8m");
    
    property_override("ro.lmk.psi_complete_stall_ms", "120");
    property_override("ro.lmk.psi_partial_stall_ms", "50");
    property_override("ro.lmk.swap_free_low_percentage", "20");
    property_override("ro.lmk.thrashing_limit", "25");
    property_override("ro.lmk.thrashing_limit_decay", "25");
    property_override("ro.lmk.filecache_min_kb", "200000");
    property_override("ro.lmk.kill_timeout_ms", "1000");
  }
}

void vendor_load_properties() {
  // dalvikvm props
  load_dalvikvm_properties();
}
