//  SPDX-License-Identifier: GPL-2.0-only
//
//  IdeaSMC.cpp
//  YogaSMC
//
//  Created by Zhen on 8/25/20.
//  Copyright © 2020 Zhen. All rights reserved.
//

#include "IdeaSMC.hpp"
OSDefineMetaClassAndStructors(IdeaSMC, YogaSMC);

IdeaSMC* IdeaSMC::withDevice(IOService *provider, IOACPIPlatformDevice *device) {
    IdeaSMC* dev = OSTypeAlloc(IdeaSMC);

    OSDictionary* dictionary = OSDictionary::withCapacity(1);

    dev->ec = device;

    if (!dev->init(dictionary) ||
        !dev->attach(provider)) {
        OSSafeReleaseNULL(dev);
    }

    dictionary->release();
    return dev;
}

void IdeaSMC::addVSMCKey() {
    super::addVSMCKey();
    if (ec) {
        addECKeySp(KeyTPCD, "CTMP");
        addECKeySp(KeyTaLC, "CPEC");
        addECKeySp(KeyTaRC, "RSEN");
    } else {
        setProperty("EC", false);
    }
}
