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
#include "iox2/sample_mut.hpp"
#include "iox2/service_name.hpp"
#include "iox2/service_type.hpp"
#include "transmission_data.hpp"

#include <chrono>
#include <ctime>
#include <iostream>
#include <utility>

constexpr iox::units::Duration CYCLE_TIME = iox::units::Duration::fromMicroseconds(1);

auto main() -> int {
    using namespace iox2;
    auto node = NodeBuilder().create<ServiceType::Ipc>().expect("successful node creation");

    auto service = node.service_builder(ServiceName::create("MyMessageServiceName").expect("valid service name"))
                       .publish_subscribe<TransmissionData>()
                       .open_or_create()
                       .expect("Creating/opening service successfully");

    auto publisher = service.publisher_builder().create().expect("Created publisher successfully");

    auto counter = 0;
    // std::time_t result = std::time(nullptr);
    while (node.wait(CYCLE_TIME).has_value()) {
        counter += 1;
        // std::localtime(&result);

        auto now = std::chrono::high_resolution_clock::now();
        auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    
        auto sample = publisher.loan_uninit().expect("acquire sample");

        sample.write_payload(TransmissionData {counter, nanoseconds}); // NOLINT
        auto initialized_sample = assume_init(std::move(sample));

        send(std::move(initialized_sample)).expect("send successful");

        std::cout << "Send sample " << counter << "..." << std::endl;
    }

    std::cout << "exit" << std::endl;

    return 0;
}
