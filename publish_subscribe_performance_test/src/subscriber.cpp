// Copyright (c) 2024 Contributors to the Eclipse Foundation
//
// See the NOTICE file(s) distributed with this work for additional
// information regarding copyright ownership.
//
// This program and the accompanying materials are made available under the
// terms of the Apache Software License 2.0 which is available at
// https://www.apache.org/licenses/LICENSE-2.0, or the MIT license
// which is available at https://opensource.org/licenses/MIT.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "iox/duration.hpp"
#include "iox2/node.hpp"
#include "iox2/service_name.hpp"
#include "iox2/service_type.hpp"
#include "transmission_data.hpp"

#include <iostream>

constexpr iox::units::Duration CYCLE_TIME = iox::units::Duration::fromNanoseconds(1);

auto main() -> int {
    using namespace iox2;
    auto node = NodeBuilder().create<ServiceType::Ipc>().expect("successful node creation");

    auto service = node.service_builder(ServiceName::create("MyMessageServiceName").expect("valid service name"))
                       .publish_subscribe<TransmissionData>()
                       .open_or_create()
                       .expect("Creating/opening service successfully");

    auto subscriber = service.subscriber_builder().create().expect("Created subscriber successfully");

    long int delay = 0;
    while (node.wait(CYCLE_TIME).has_value()) {
        auto sample = subscriber.receive().expect("receive succeeds");
        while (sample.has_value()) {
            auto now = std::chrono::high_resolution_clock::now();
            auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
            auto data = sample->payload();
            std::cout << "received @ " << nanoseconds << ": " << data << " with delay of " << nanoseconds - data.tov.count() << " nanoseconds" << std::endl;
            sample = subscriber.receive().expect("receive succeeds");
        }
    }

    std::cout << "exit" << std::endl;

    return 0;
}
