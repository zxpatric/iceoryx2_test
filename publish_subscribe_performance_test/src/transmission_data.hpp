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

#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>

struct TransmissionData {
    std::int32_t val;
    // std::time_t tov;
    std::chrono::nanoseconds tov;
};

inline auto operator<<(std::ostream& stream, const TransmissionData& data) -> std::ostream& {
    stream << "TransmissionData { Value: " << data.val << ", TransmissionTime: " << data.tov.count() << " }";
    return stream;
}
