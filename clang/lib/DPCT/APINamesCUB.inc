//===------------------------- APINamesCUB.inc ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// cub::DeviceReduce::Sum
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceReduce::Sum"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
                "cub::DeviceReduce::Sum",
                MEMBER_CALL(
                    QUEUESTR, false, "fill", ARG(3),
                    CALL(
                        "oneapi::dpl::reduce",
                        CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                        ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(4))),
                    LITERAL("1")),
                false, "wait")))))

// cub::DeviceReduce::Reduce
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceReduce::Reduce"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
                "cub::DeviceReduce::Reduce",
                MEMBER_CALL(QUEUESTR, false, "fill", ARG(3),
                            CALL("oneapi::dpl::reduce",
                                 CALL("oneapi::dpl::execution::device_policy",
                                      QUEUESTR),
                                 ARG(2),
                                 BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(4)),
                                 ARG(6), ARG(5)),
                            LITERAL("1")),
                false, "wait")))))

// cub::DeviceReduceByKey
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceReduce::ReduceByKey"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
                "cub::DeviceReduce::ReduceByKey",
                MEMBER_CALL(
                    QUEUESTR, false, "fill", ARG(6),
                    CALL("std::distance", ARG(3),
                         MEMBER_EXPR(
                             CALL("oneapi::dpl::reduce_by_key",
                                  CALL("oneapi::dpl::execution::device_policy",
                                       QUEUESTR),
                                  ARG(2),
                                  BO(BinaryOperatorKind::BO_Add, ARG(2),
                                     ARG(8)),
                                  ARG(4), ARG(3), ARG(5),
                                  CALL(TEMPLATED_NAME(
                                      "std::equal_to",
                                      TYPENAME(STATIC_MEMBER_EXPR(
                                          TEMPLATED_NAME("std::iterator_traits",
                                                         CALL("decltype",
                                                              ARG(2))),
                                          LITERAL("value_type"))))),
                                  ARG(7)),
                             false, LITERAL("first"))),
                    LITERAL("1")),
                false, "wait")))))

// cub::DeviceScan::ExclusiveSum
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceScan::ExclusiveSum"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(CALL_FACTORY_ENTRY(
                "cub::DeviceScan::ExclusiveSum",
                CALL("oneapi::dpl::exclusive_scan",
                     CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                     ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(4)),
                     ARG(3), LITERAL("0")))))))

// cub::DeviceScan::InclusiveSum
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceScan::InclusiveSum"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(CALL_FACTORY_ENTRY(
                "cub::DeviceScan::InclusiveSum",
                CALL("oneapi::dpl::inclusive_scan",
                     CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                     ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(4)),
                     ARG(3)))))))

// cub::DeviceScan::ExclusiveScan
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceScan::ExclusiveScan"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(CALL_FACTORY_ENTRY(
                "cub::DeviceScan::ExclusiveScan",
                CALL("oneapi::dpl::exclusive_scan",
                     CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                     ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(6)),
                     ARG(3), ARG(5), ARG(4)))))))

// cub::DeviceScan::InclusiveScan
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceScan::InclusiveScan"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(CALL_FACTORY_ENTRY(
                "cub::DeviceScan::InclusiveScan",
                CALL("oneapi::dpl::inclusive_scan",
                     CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                     ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(5)),
                     ARG(3), ARG(4)))))))

// cub::DeviceSelect::Flagged
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceSelect::Flagged"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Utils,
        REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
            "cub::DeviceSelect::Flagged",
            MEMBER_CALL(
                QUEUESTR, false, "fill", ARG(5),
                BO(BinaryOperatorKind::BO_Sub,
                   CALL("dpct::copy_if",
                        CALL("oneapi::dpl::execution::device_policy", QUEUESTR),
                        ARG(2), BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(6)),
                        ARG(3), ARG(4),
                        LITERAL("[](const auto &t) -> bool { return t; }")),
                   ARG(4)),
                LITERAL("1")),
            false, "wait"))))

// cub::DeviceSelect::Unique
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceSelect::Unique"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Execution,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Algorithm,
            REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
                "cub::DeviceSelect::Unique",
                MEMBER_CALL(
                    QUEUESTR, false, "fill", ARG(4),
                    BO(BinaryOperatorKind::BO_Sub,
                       CALL("oneapi::dpl::unique_copy",
                            CALL("oneapi::dpl::execution::device_policy",
                                 QUEUESTR),
                            ARG(2),
                            BO(BinaryOperatorKind::BO_Add, ARG(2), ARG(5)),
                            ARG(3)),
                       ARG(3)),
                    LITERAL("1")),
                false, "wait")))))

// cub::DeviceRunLengthEncode::Encode
CONDITIONAL_FACTORY_ENTRY(
    CheckCubRedundantFunctionCall(),
    REMOVE_API_FACTORY_ENTRY("cub::DeviceRunLengthEncode::Encode"),
    HEADER_INSERT_FACTORY(
        HeaderType::HT_DPL_Utils,
        HEADER_INSERT_FACTORY(
            HeaderType::HT_DPL_Execution,
            HEADER_INSERT_FACTORY(
                HeaderType::HT_DPL_Algorithm,
                REMOVE_CUB_TEMP_STORAGE_FACTORY(MEMBER_CALL_FACTORY_ENTRY(
                    "cub::DeviceRunLengthEncode::Encode",
                    MEMBER_CALL(
                        QUEUESTR, false, "fill", ARG(5),
                        BO(BinaryOperatorKind::BO_Sub,
                           MEMBER_EXPR(
                               CALL(
                                   "oneapi::dpl::reduce_by_segment",
                                   CALL("oneapi::dpl::execution::device_policy",
                                        QUEUESTR),
                                   ARG(2),
                                   BO(BinaryOperatorKind::BO_Add, ARG(2),
                                      ARG(6)),
                                   MEMBER_CALL(
                                       CALL("dpct::device_vector<size_t>",
                                            ARG(6), LITERAL("1")),
                                       false, "begin"),
                                   ARG(3), ARG(4)),
                               false, LITERAL("first")),
                           ARG(3)),
                        LITERAL("1")),
                    false, "wait"))))))
